#include "crossover.h"
#include "utility.hpp"

Crossover::Crossover()
{
}

auto Crossover::ApplyOnePoint(const Chromosome& chromosome1, const Chromosome& chromosome2)
{
    auto chromosomeSize = chromosome1.GetSize();
    unsigned int crossoverPointIndex = std::max(1u, Utility::rand<unsigned int>() % chromosomeSize);

    Chromosome childChromosome1;
    Chromosome childChromosome2;

    for (unsigned int geneIndex = 0; geneIndex < chromosomeSize; geneIndex++){
        if (geneIndex < crossoverPointIndex){
            childChromosome1.AddGene(chromosome1.GetGene(geneIndex));
            childChromosome2.AddGene(chromosome2.GetGene(geneIndex));
        } else {
            childChromosome1.AddGene(chromosome2.GetGene(geneIndex));
            childChromosome2.AddGene(chromosome1.GetGene(geneIndex));
        }
    }

    return std::make_pair(childChromosome1, childChromosome2);
}

auto Crossover::ApplyTwoPoint(const Chromosome& chromosome1, const Chromosome& chromosome2){
    auto chromosomeSize = chromosome1.GetSize();
    
    unsigned int crossoverPointIndex1 = std::max(1u, Utility::rand<unsigned int>() % chromosomeSize);
    unsigned int crossoverPointIndex2 = std::max(1u, Utility::rand<unsigned int>() % chromosomeSize);

    while(crossoverPointIndex1 == crossoverPointIndex2){
        crossoverPointIndex2 = std::max(1u, Utility::rand<unsigned int>() % chromosomeSize);
    }

    if (crossoverPointIndex1 > crossoverPointIndex2){
        std::swap(crossoverPointIndex1, crossoverPointIndex2);
    }

    Chromosome childChromosome1;
    Chromosome childChromosome2;

    for (unsigned int geneIndex = 0; geneIndex < chromosomeSize; geneIndex++){
        if (geneIndex < crossoverPointIndex1 || geneIndex > crossoverPointIndex2){
            childChromosome1.AddGene(chromosome1.GetGene(geneIndex));
            childChromosome2.AddGene(chromosome2.GetGene(geneIndex));
        } else {
            childChromosome1.AddGene(chromosome2.GetGene(geneIndex));
            childChromosome2.AddGene(chromosome1.GetGene(geneIndex));
        }
    }

    return std::make_pair(childChromosome1, childChromosome2);
}

auto Crossover::ApplyUniform(const Chromosome& chromosome1, const Chromosome& chromosome2){
    // TODO
}