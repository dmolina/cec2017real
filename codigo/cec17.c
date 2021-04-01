#include <assert.h>
#include <stdio.h>

void cec17_test_func(double *x, double *f, int nx, int mx,int func_num);

static int dimension;
static int funcid;
static int count;
static int ratios[] = {1, 2, 3, 5, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
static int max_evals;
static int max_ratios = 14;
static int last_ratio = 0;
static char fname[300];
static double best;
static FILE *output  = NULL;

void cec17_setfun(int fid, int size) {
  assert (fid > 0 && fid <= 30);
  assert (size == 2 || size == 5 || size == 10 || size == 30 || size == 50);
  funcid = fid;
  dimension = size;
  count = 0;
  last_ratio = 0;

  if (output != NULL) {
    fclose(output);
  }
  output = NULL;
  sprintf(fname, "results_%d_%d.txt", fid, size);
  max_evals = 10000*dimension;
}

double cec17_error(double fitness) {
  const double optimum = funcid*100;
  assert (fitness >= optimum);
  return fitness - optimum;
}

double cec17_fitness(double *sol) {
  double fit;
  int ratio;

  cec17_test_func(sol, &fit, dimension, 1, funcid);
  count += 1;
  assert(count <= max_evals);

  if (count == 1 || fit < best) {
    best = fit;
  }

  ratio = count*100/max_evals;

  if (ratio >= ratios[last_ratio]) {
    if (output == NULL) {
      int exists = 0;
      FILE *ver = fopen(fname, "r");
      if (ver != NULL) {
        exists = 1;
        fclose(ver);
      }

      output = fopen(fname, "a");

      if (!exists) {
        fprintf(output, "funcid,dim,milestone,error\n");
      }
    }

    fprintf(output, "%d,%d,%d,%e\n", funcid, dimension, ratio, cec17_error(best));
    last_ratio += 1;

    if (last_ratio >= max_ratios) {
      fclose(output);
      output = NULL;
      last_ratio = 0;
    }

  }

  return fit;
}
