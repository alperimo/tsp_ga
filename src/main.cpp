#include "tsp_ga.h"

int main()
{
    TspGa tspGa;
    tspGa.InitPopulation();
    tspGa.Solve();

    return 0;
}