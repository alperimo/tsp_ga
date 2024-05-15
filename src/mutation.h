#ifndef MUTATION_H
#define MUTATION_H

#include "chromosome.h"

class Mutation{
    public:
        Mutation();

        static void ApplySwap(Chromosome& chromosome);
        static void ApplyScramble(Chromosome& chromosome);
        static void ApplyInversion(Chromosome& chromosome);
};

#endif