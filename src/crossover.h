#ifndef CROSSOVER_H
#define CROSSOVER_H

#include "chromosome.h"
#include "utility.hpp"

class Crossover{
    public:
        Crossover();

        static auto ApplyOnePoint(const Chromosome& chromosome1, const Chromosome& chromosome2);
        static auto ApplyTwoPoint(const Chromosome& chromosome1, const Chromosome& chromosome2);
        static auto ApplyUniform(const Chromosome& chromosome1, const Chromosome& chromosome2);

        static auto ApplyPartiallyMapped(const Chromosome& chromosome1, const Chromosome& chromosome2) -> std::pair<Chromosome, Chromosome>;

        static auto GetTwoCrossoverPointIndices(const unsigned int& chromosomeSize) -> std::pair<unsigned int, unsigned int>;
};

#endif