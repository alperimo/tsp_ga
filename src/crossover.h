#ifndef CROSSOVER_H
#define CROSSOVER_H

#include "chromosome.h"

class Crossover{
    public:
        Crossover();

        auto ApplyOnePoint(const Chromosome& chromosome1, const Chromosome& chromosome2);
        auto ApplyTwoPoint(const Chromosome& chromosome1, const Chromosome& chromosome2);
        auto ApplyUniform(const Chromosome& chromosome1, const Chromosome& chromosome2);
};

#endif