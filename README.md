# README

This software contains the source code of the CEC'2017 benchmark for bounds
contraints in 
[https://github.com/P-N-Suganthan/CEC2017-BoundContrained](https://github.com/P-N-Suganthan/CEC2017-BoundContrained). 

That benchmark is available for researchers, and for students.

In addition to original benchmark code it contains:

- A file cec17.c with several functions, including a fitness functions that
store in external files, with filename *results_<funcid>_<dimension>.txt* in a
directory *results_<algname>*.

- A script, extrae.py to 

# INSTALLL

It requires the [CMake](https://cmake.org/) tool to compile the source code in a shared library.

```sh
$ cmake .
```

# Usage

The steps of using:

1. Configure the function, this is done with function cec17_init, with the
   algorithm name (used to calculate the output directory), the function id, and
   the dimension.
   
2. Run the algorithm with cec17_fitness to evaluations solutions (must have
   length equals to dimension). You can use a double * or a vector<double>.

3. After the experimental is done, you can run the extract.py script to
   generate an Excel file with all mean values.
   
4. Use [tacolab](https://tacolab.org/bench) to compare. You can select your
   algorithms for comparisons (PSO and DE are classic algorithms, the other are
   more advanced), submitting the excel file with a name of algorithm (that will
   appears at the comparisons tables).
   
5. You can download the comparisons tables in Excel and/or latex format.

# Experimental conditions

- Stopping criterion: the algorithm must stop when a maximum number of
  evaluations is achieved. The maximum number of evaluations is 10000*dimension
  (100,000 for dimension 10, 300,000 for dimension 30, ...).

- Run: The algorithm must be run for 51 times, with different seed values.

- Number of functions: 1-30.

- Dimensions: 10, 30, 50, 100.

# Wrappers

We have included a wrapper in Python, and we are open to  wrapper in more
languages, feel free to submit a pull  request.

# Examples

in `code/` there are several example functions. In the following, I in

```c++
extern "C" {
#include "cec17.h"
}
#include <iostream>
#include <vector>
#include <random>

using namespace std;

int main() {
  vector<double> sol;
  int dim = 10;
  int seed = 42;
  std::uniform_real_distribution<> dis(-100.0, 100.0);

  for (int funcid = 1; funcid <= 30; funcid++) {
    vector<double> sol(dim);
    vector<double> bestsol(dim);
    double fitness;
    double best = -1;

    // Set the function to use in fitness
    cec17_init("random", funcid, dim);
    // If it is commented the output is print in console, instead of external files.
    // cec17_print_output();

    std::mt19937 gen(seed); // Start seed
    int evals = 0;

    while (evals < 10000*dim) {
      // Generate random solution
      for (int i = 0; i < dim; i++) {
        sol[i] = dis(gen);
      }

      // Evaluate the solution
      fitness = cec17_fitness(&sol[0]);
      // Increase count
      evals += 1;

      // Calculate the best one
      if (evals == 1 || fitness < best) {
        best = fitness;
        bestsol = sol;
      }
    }

    // Show the error of the best solution
    cout <<"Best Random[F" <<funcid <<"]: " << scientific <<cec17_error(best) <<endl;
  }

}

```

# LICENSE

This source code includes the source code freely available at
[https://github.com/P-N-Suganthan/CEC2017-BoundContrained](https://github.com/P-N-Suganthan/CEC2017-BoundContrained),
with its license.
The rest of source code is available as [MIT LICENSE](https://mit-license.org/).

# About Function F2

The function F02 was removed from benchmark because there were inconsistencies
between implementations. However, in this code we have included it because it
was included in [tacolab](https://www.tacolab.org).

# API

API obtained by the doxygen and thanks to (https://delight-im.github.io/Javadoc-to-Markdown/).

### `void cec17_init(const char *algname, int funcid, int dimension)`

Init the fitness function and dimension.

 * **Parameters:**
   * `algname` — (results will be copy to results_algname directory).
   * `funcid` — must be between 1 and 30.
   * `dimension` — must be 2, 5, 10, 30, 50, or 100.

### `void cec17_print_output(void)`

Desactivate the output to external files, instead it will be shown at the console.

### `double cec17_error(double fitness)`

Return the error related with the fitness.

 * **Parameters:** `fitness` — to compare.
 * **Returns:** error (fitness - optimum).

### `double cec17_fitness(double *sol)`

The fitness function to  evaluate from the solution.

 * **Parameters:** `sol` — solution to evaluate. 
 * **Returns:** fitness value.

