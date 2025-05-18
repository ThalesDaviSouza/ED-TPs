#ifndef REGISTRO_H
#define REGISTRO_H
using namespace std;

class Registro{
  public:
    Registro()
    : mps(0), cost(0), cmp(0), moves(0), calls(0) {}
    Registro(int mps, double cost, int cmp, int moves, int calls)
    : mps(mps), cost(cost), cmp(cmp), moves(moves), calls(calls) { }
    int mps;
    double cost;
    int cmp;
    int moves;
    int calls;
};

#endif