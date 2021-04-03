extern "C" {
#include "cec17.h"
}
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<double> sol;
  int dim = 10;

  for (int funcid = 1; funcid <= 30; funcid++) {
    vector<double> sol(dim);
    double fitness;

    cec17_init("test", funcid, dim);

    for (int i = 0; i < dim; i++) {
      sol[i] = i;
    }

    fitness = cec17_fitness(&sol[0]);
    cout <<"Fitness[F" <<funcid <<"]: " << scientific <<cec17_error(fitness) <<endl;
  }

}
