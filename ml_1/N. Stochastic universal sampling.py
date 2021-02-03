
import numpy as np

def sus(fitness: np.ndarray, n: int, start: float) -> list:
    """Selects exactly `n` indices of `fitness` using Stochastic universal sampling alpgorithm. 

    Args:
        fitness: one-dimensional array, fitness values of the population, sorted in descending order
        n: number of individuals to keep
        start: minimal cumulative fitness value

    Return:
        Indices of the new population"""

    totalFitness = np.sum(fitness)
    distanceBetweenPointers = totalFitness / n
    pointers = [start + i*distanceBetweenPointers for i in range(0, n)]
    fitnessCumsum = np.cumsum(fitness)

    newPopulationIndexes = []
    for point in pointers:
        index = 0
        while fitnessCumsum[index] < point:
            index += 1
        newPopulationIndexes.append(index)
    return newPopulationIndexes 

# fitness = np.array([10, 4, 3, 2, 1])
# print(*fitness[sus(fitness, 3, 6)])
# 
# 
# 10 4 1
            