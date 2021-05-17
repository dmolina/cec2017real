from pathlib import Path

import os
import sys

import numpy as np
import pandas as pd

def main():

    if len(sys.argv) == 1:
        dir="."
    else:
        dir = sys.argv[1]

    path = Path(dir)

    if not path.is_dir():
        print(f"Error, directory '{dir}' does not exist", file=sys.stderr)
        exit(1)

    print(f"Working in '{dir}'")
    os.chdir(dir)
    path = Path('.')

    fnames = [file.name for file in path.iterdir() if "txt" in file.name]
    globaldf = pd.DataFrame({"funcid": [], "dim": [], "milestone": [], "error": []})
    dict = {"milestone": []}

    for i in range(1, 31):
        dict.update({"F{:02d}".format(i): []})

    dict.update({"dimension": []})

    for fname in fnames:
        df = pd.read_csv(fname)
        globaldf = globaldf.append(df)

    def funformat(funid):
        return "F{:02d}".format(funid)

    dim_df = globaldf.groupby(['dim'])

    for (dim, df) in dim_df:
        milestones = [int(mil) for mil in np.unique(df.milestone)]
        funs = [int(fun) for fun in np.unique(df.funcid)]
        output_df = pd.DataFrame(dict)

        if len(milestones) != 14:
            print(f"Error in milestones: {milestones}", file=sys.stderr)
            exit(1)

        if len(funs) != 30:
            expected = {i for i in range(1, 31)}
            missing = expected-set(funs)
            print(f"Missing data of functions: {missing}", file=sys.stderr)
            exit(1)

        mean_df = df.groupby(['funcid', 'milestone']).mean().reset_index().sort_values(by=['milestone', 'funcid'])

        if mean_df.shape[1] != 4:
            print(f"Error, files has a column missing in dimension {dim}", file=sys.stderr)
            exit(1)

        if mean_df.shape[0] != 420:
            print(f"Error, there are some missing data in dimension {dim}", file=sys.stderr)
            exit(1)

        for milestone in milestones:
            mildf = mean_df[mean_df.milestone == milestone]
            dict = {'milestone': [milestone], 'dimension': [dim]}

            for (funid,(_, row)) in zip(funs, mildf.iterrows()):
                assert(row.funcid == funid)
                funcol = funformat(funid)
                value = float(row.error)
                dict.update({funcol: value})

            df_row = pd.DataFrame(dict)
            output_df = pd.concat([output_df, pd.DataFrame(dict)])

        fname = "results_cec2017_{}.xlsx".format(int(dim))
        print(fname)
        output_df.to_excel(fname)

    # Hago la media de todas

if __name__ == '__main__':
    main()
