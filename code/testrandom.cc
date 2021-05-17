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

    cec17_init("random", funcid, dim);

    cerr <<"Warning: output by console, if you want to create the output file you have to comment cec17_print_output()" <<endl;
    cec17_print_output(); // Comment to generate the output file

    std::mt19937 gen(seed); // Inicio semilla
    int evals = 0;

    while (evals < 10000*dim) {
      for (int i = 0; i < dim; i++) {
        sol[i] = dis(gen);
      }

      fitness = cec17_fitness(&sol[0]);
      evals += 1;

      if (evals == 1 || fitness < best) {
        best = fitness;
        bestsol = sol;
      }
    }

    cout <<"Best Random[F" <<funcid <<"]: " << scientific <<cec17_error(best) <<endl;
  }

}
