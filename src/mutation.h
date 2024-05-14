#ifndef MUTATION_H
#define MUTATION_H

#include "chromosome.h"

class Mutation{
    public:
        Mutation();

        static void ApplySwap(Chromosome& chromosome, float mutationRate);
        static void ApplyScramble(Chromosome& chromosome, float mutationRate);
        static void ApplyInversion(Chromosome& chromosome, float mutationRate);
};

#endif