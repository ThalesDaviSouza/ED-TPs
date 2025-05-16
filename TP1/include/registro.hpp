#ifndef REGISTRO_H
#define REGISTRO_H
using namespace std;

class Registro{
  public:
    Registro(int mps, float cost, int cmp, int moves, int calls)
    : mps(mps), cost(cost), cmp(cmp), moves(moves), calls(calls) { }
    int mps;
    float cost;
    int cmp;
    int moves;
    int calls;
};

#endif