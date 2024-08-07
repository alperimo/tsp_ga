#include "crossover.h"
#include <unordered_map>
#include <iostream>

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


// Swap the genes between the crossover points and copy the rest of the genes
auto Crossover::ApplyTwoPoint(const Chromosome& chromosome1, const Chromosome& chromosome2){
    auto chromosomeSize = chromosome1.GetSize();
    
    auto [crossoverPointIndex1, crossoverPointIndex2] = GetTwoCrossoverPointIndices(chromosomeSize);
    
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

    // TODO: What about returning the pointers of the chromosomes instead of copying them?
    return std::make_tuple(childChromosome1, childChromosome2, crossoverPointIndex1, crossoverPointIndex2);
}

auto Crossover::ApplyUniform(const Chromosome& chromosome1, const Chromosome& chromosome2){
    // TODO
}

/*
    1 5 9 3 7 4 6 2 8 -> 1 5 9 | 3 7 4 | 6 2 8 -> x x x | 5 1 6 | x x x -> x x 9 | 5 1 6 | x 2 8
    3 8 2 5 1 6 9 7 4 -> 3 8 2 | 5 1 6 | 9 7 4 -> x x x | 3 7 4 | x x x -> x 8 2 | 3 7 4 | 9 x x
*/
auto Crossover::ApplyPartiallyMapped(const Chromosome& chromosome1, const Chromosome& chromosome2) -> std::pair<Chromosome, Chromosome>{
    auto chromosomeSize = chromosome1.GetSize();

    auto [childChromosome1, childChromosome2, crossoverPointIndex1, crossoverPointIndex2] = ApplyTwoPoint(chromosome1, chromosome2);

    auto solveConflicts = [&](Chromosome& childChromosome, const Chromosome& parentChromosome){
        auto swappedGensMap = std::unordered_map<unsigned int, unsigned int>();

        for (unsigned int geneIndex = crossoverPointIndex1; geneIndex <= crossoverPointIndex2; geneIndex++){
            auto gene1 = childChromosome.GetGene(geneIndex);
            auto gene2 = parentChromosome.GetGene(geneIndex);

            if (gene1 == gene2){
                continue;
            }

            swappedGensMap[gene1] = gene2;
        }
        
        // Important: For id based genes/points, we have to start geneIndex from 1.
        for (unsigned int geneIndex = 1; geneIndex < chromosomeSize; geneIndex++){
            if (geneIndex >= crossoverPointIndex1 && geneIndex <= crossoverPointIndex2){
                continue;
            }

            auto gene = childChromosome.GetGene(geneIndex);

            // By looking up the swappedGensMap, we iterate until we find the original replacement gene. (5->1->6) => 5->6
            if (swappedGensMap.find(gene) != swappedGensMap.end()){
                auto swappedGene = swappedGensMap[gene];
                
                while(swappedGensMap.find(swappedGene) != swappedGensMap.end()){
                    swappedGene = swappedGensMap[swappedGene];
                }

                childChromosome.SetGene(geneIndex, swappedGene);
            }
        }
    };

    solveConflicts(childChromosome1, chromosome1);
    solveConflicts(childChromosome2, chromosome2);

    return std::make_pair(childChromosome1, childChromosome2);
}

/*
    1 5 9 3 7 4 6 2 8 -> 1 5 9 | 3 7 4 | 6 2 8 -> x x x | 3 7 4 | x x x
    3 8 2 5 1 6 9 7 4 -> 3 8 2 | 5 1 6 | 9 7 4 -> y y y | 5 1 6 | y1 y2 y3

    Transfer the genes in the second chromosome that are not between the crossover points of the first chromosome to the first chromosome
    by starting most-right side of second crossover point of the second (index of y1 represented by offspringGeneIndex) until we reach 
    the left side of the first crossover point of the first chromosome. 
*/
auto Crossover::ApplyOrderBased(const Chromosome& chromosome1, const Chromosome& chromosome2) -> std::pair<Chromosome, Chromosome>{
    auto chromosomeSize = chromosome1.GetSize();

    auto [crossoverPointIndex1, crossoverPointIndex2] = GetTwoCrossoverPointIndices(chromosomeSize);

    std::cout << "Crossover Point 1: " << crossoverPointIndex1 << ", Crossover Point 2: " << crossoverPointIndex2 << std::endl;

    auto generateChildChromosome = [&](const Chromosome& offspring, const Chromosome& otherOffspring){
        std::cout << "----------------------------------------------------------" << std::endl;
        Chromosome childChromosome = offspring;

        // Point indices they are located between the crossover points of offspring, will have the value 1 in the map so that we can check the existence of the gene in O(1) time
        auto genesMapBetweenCrossoverPoints = std::unordered_map<unsigned int, unsigned int>();
        for (unsigned int geneIndex = crossoverPointIndex1; geneIndex <= crossoverPointIndex2; geneIndex++){
            genesMapBetweenCrossoverPoints[offspring.GetGene(geneIndex)] = 1;
        }

        unsigned int transferredGeneCount = 0;
        unsigned int otherOffspringGeneIndex = crossoverPointIndex2 + 1;
        unsigned int offspringGeneIndex = crossoverPointIndex2 + 1;
        // We should keep iterating until we reach the chromosomeSize - (total genes between crossover points) - 1 (minus 1 because we will already add the starting point index to the beginning)
        while (offspringGeneIndex != crossoverPointIndex1){
            // Go back to the beginning of chromosome if we reach the end (otherOffspringGeneIndex should be 1 cause 0 is starting point index)
            if (otherOffspringGeneIndex == chromosomeSize){
                otherOffspringGeneIndex = 1;
            }

            if (otherOffspringGeneIndex >= crossoverPointIndex1 && otherOffspringGeneIndex <= crossoverPointIndex2){
                otherOffspringGeneIndex++;
                continue;
            }

            // Go back to the beginning of chromosome if we reach the end (offspringGeneIndex should be 1 cause 0 is starting point index)
            if (offspringGeneIndex == chromosomeSize){
                offspringGeneIndex = 1;
            }

            // If the gene of otherOffspring is not between the crossover points of offspring, transfer it with the gene in the same index of offspring
            auto geneOfOtherOffspring = otherOffspring.GetGene(otherOffspringGeneIndex);
            if (genesMapBetweenCrossoverPoints.find(geneOfOtherOffspring) == genesMapBetweenCrossoverPoints.end()){
                childChromosome.SetGene(offspringGeneIndex, geneOfOtherOffspring);
                transferredGeneCount++;
                //std::cout << "otherOffspringGeneIndex: " << otherOffspringGeneIndex << ", Transferred Gene: " << geneOfOtherOffspring << " to offspringGeneIndex: " << offspringGeneIndex << ", transferredGeneCount: " << transferredGeneCount << std::endl;
                offspringGeneIndex++;
            }else{
                //std::cout << "otherOffspringGeneIndex: " << otherOffspringGeneIndex << ", Gene: " << geneOfOtherOffspring << " is between crossover points, so will be skipped" << std::endl;
            }
            
            otherOffspringGeneIndex++;
        }

        return childChromosome;
    };

    auto childChromosome1 = generateChildChromosome(chromosome1, chromosome2);
    auto childChromosome2 = generateChildChromosome(chromosome2, chromosome1);

    return std::make_pair(childChromosome1, childChromosome2);
}

auto Crossover::ApplyCycleBased(const Chromosome& chromosome1, const Chromosome& chromosome2) -> std::pair<Chromosome, Chromosome>{
    auto chromosomeSize = chromosome1.GetSize();

    auto generateChildChromosome = [chromosomeSize](const Chromosome& priorChromosome, const Chromosome& otherChromosome){
        Chromosome childChromosome(chromosomeSize);
        
        childChromosome.SetGene(0, priorChromosome.GetGene(0));

        auto priorChrGenPositions = std::unordered_map<unsigned int, unsigned int>();
        // We are starting from index 1, because first index 0 is equal for each chromosome anyway.
        for (auto geneIndex = 1u; geneIndex < chromosomeSize; geneIndex++){
            priorChrGenPositions[priorChromosome.GetGene(geneIndex)] = geneIndex;
        }

        auto startGene = priorChromosome.GetGene(1);
        
        auto currentGeneIndex = 1u;

        // To prevent the beginnings which have already cycle when genes in the starting index (1) are same. 
        while (startGene == otherChromosome.GetGene(currentGeneIndex)){
            childChromosome.SetGene(currentGeneIndex, startGene);
            startGene = priorChromosome.GetGene(++currentGeneIndex);
            if (currentGeneIndex >= chromosomeSize - 1)
                return priorChromosome;
        }

        if (startGene != otherChromosome.GetGene(currentGeneIndex)){
            childChromosome.SetGene(currentGeneIndex, priorChromosome.GetGene(currentGeneIndex));
        }

        auto geneInOtherChr = otherChromosome.GetGene(currentGeneIndex);
        // Until we return the gene that we have already in the beginning in priorChromosome.
        while (startGene != geneInOtherChr){
            try{
                currentGeneIndex = priorChrGenPositions.at(geneInOtherChr);
                childChromosome.SetGene(currentGeneIndex, geneInOtherChr);
                geneInOtherChr = otherChromosome.GetGene(currentGeneIndex);
            }catch(const std::out_of_range& e){
                std::cerr << "Exception on Applying Cycle Based Crossover: " << e.what() << std::endl;
                return priorChromosome;
            }
        }

        auto& childChromosomeGenes = childChromosome.GetGenes();
        std::for_each(childChromosomeGenes.begin(), childChromosomeGenes.end(), [&](unsigned int& gene){
            auto geneIndex = static_cast<unsigned int>(&gene - &childChromosomeGenes.front());
            // We consider genes with 0 value as empty, so we fill them with the genes in the other chromosome.
            if (childChromosome.GetGene(geneIndex) == 0){
                childChromosome.SetGene(geneIndex, otherChromosome.GetGene(geneIndex));
            }
        });

        return childChromosome;
    };

    auto childChromosome1 = generateChildChromosome(chromosome1, chromosome2);
    auto childChromosome2 = generateChildChromosome(chromosome2, chromosome1);

    return std::make_pair(childChromosome1, childChromosome2);
}

auto Crossover::GetTwoCrossoverPointIndices(const unsigned int& chromosomeSize) -> std::pair<unsigned int, unsigned int>{
    unsigned int crossoverPointIndex1 = std::max(1u, Utility::rand<unsigned int>() % chromosomeSize);
    unsigned int crossoverPointIndex2 = std::max(1u, Utility::rand<unsigned int>() % chromosomeSize);

    while(crossoverPointIndex1 == crossoverPointIndex2){
        crossoverPointIndex2 = std::max(1u, Utility::rand<unsigned int>() % chromosomeSize);
    }

    if (crossoverPointIndex1 > crossoverPointIndex2){
        std::swap(crossoverPointIndex1, crossoverPointIndex2);
    }

    return std::make_pair(crossoverPointIndex1, crossoverPointIndex2);
}