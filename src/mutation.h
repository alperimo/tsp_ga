#ifndef MUTATION_H
#define MUTATION_H

#include "chromosome.h"

class Mutation{
    public:
        Mutation();

        static Chromosome ApplySwap(const Chromosome& chromosome, float mutationRate);
        static Chromosome ApplyScramble(const Chromosome& chromosome, float mutationRate);
        static Chromosome ApplyInversion(const Chromosome& chromosome, float mutationRate);
};

#endif