#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "cec17.h"

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
static char directory[30];
static int print_output = 0;

void cec17_init(const char *algname, int fid, int size) {
  assert (fid > 0 && fid <= 30);
  assert (size == 2 || size == 5 || size == 10 || size == 30 || size == 50 || size == 100);
  funcid = fid;
  dimension = size;
  count = 0;
  last_ratio = 0;

  sprintf(directory, "results_%s", algname);
  sprintf(fname, "%s%cresults_%d_%d.txt", directory, PATH_SEPARATOR, fid, size);
  print_output = 0;
  max_evals = 10000*dimension;
}

void cec17_print_output(void) {
  print_output = 1;
}

double cec17_error(double fitness) {
  const double optimum = funcid*100;
  assert (fitness >= optimum);
  return fitness - optimum;
}

double cec17_fitness(double *sol) {
  double fit;
  static FILE *output  = NULL;
  int ratio;

  cec17_test_func(sol, &fit, dimension, 1, funcid);
  count += 1;

  if (count > max_evals) {
      fprintf(stderr, "Warning: evaluation will be ignored\n");
      return fit;
  }

  if (count == 1 || fit < best) {
    best = fit;
  }

  ratio = count*100/max_evals;

  if (ratio >= ratios[last_ratio]) {
    if (output == NULL && print_output == 0) {
      int exists = 0;
      FILE *ver = fopen(fname, "r");
      if (ver != NULL) {
        exists = 1;
        fclose(ver);
      }

      output = fopen(fname, "a");

      if (output == NULL) {
        fprintf(stderr, "Error, it cannot be possible to create file '%s', the directory '%s' exists?\n", fname, directory);
        exit(1);
      }

      if (!exists) {
        fprintf(output, "funcid,dim,milestone,error\n");
      }
    }

    if (print_output == 1) {
      printf("%d,%d,%d,%e\n", funcid, dimension, ratio, cec17_error(best));
      fflush(stdout);
    }
    else {
      fprintf(output, "%d,%d,%d,%e\n", funcid, dimension, ratio, cec17_error(best));
      fclose(output);
      output = NULL;
    }
    last_ratio += 1;

    if (last_ratio >= max_ratios) {
      last_ratio = 0;
    }

  }

  return fit;
}
