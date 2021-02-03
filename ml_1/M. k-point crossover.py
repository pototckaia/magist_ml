import numpy as np
from typing import Tuple

def single_point_crossover(a: np.ndarray, b: np.ndarray, point: int) -> Tuple[np.ndarray, np.ndarray]:
    """Performs single point crossover of `a` and `b` using `point` as crossover point.
    Chromosomes to the right of the `point` are swapped

    Args:
        a: one-dimensional array, first parent
        b: one-dimensional array, second parent
        point: crossover point

    Return:
        Two np.ndarray objects -- the offspring"""

    new_a = np.concatenate((a[:point+1], b[point+1:]))
    new_b = np.concatenate((b[:point+1], a[point+1:]))
    return new_a, new_b


def two_point_crossover(a: np.ndarray, b: np.ndarray, first: int, second: int) -> Tuple[np.ndarray, np.ndarray]:
    """Performs two point crossover of `a` and `b` using `first` and `second` as crossover points.
    Chromosomes between `first` and `second` are swapped

    Args:
        a: one-dimensional array, first parent
        b: one-dimensional array, second parent
        first: first crossover point
        second: second crossover point

    Return:
        Two np.ndarray objects -- the offspring"""

    aa, bb = single_point_crossover(a[:second], b[:second], first)
    new_a = np.concatenate((aa, a[second:]))
    new_b = np.concatenate((bb, b[second:]))
    return new_a, new_b


def k_point_crossover(a: np.ndarray, b: np.ndarray, points: np.ndarray) -> Tuple[np.ndarray, np.ndarray]:
    """Performs k point crossover of `a` and `b` using `points` as crossover points.
    Chromosomes between each even pair of points are swapped

    Args:
        a: one-dimensional array, first parent
        b: one-dimensional array, second parent
        points: one-dimensional array, crossover points

    Return:
        Two np.ndarray objects -- the offspring"""

    points = np.concatenate(([0], points, [len(a)]))
    new_a, new_b = np.array([], dtype=a.dtype), np.array([], dtype=a.dtype)
    for p_start, p_mid, p_end in zip(points[:-1:2], points[1::2], points[2::2]):
        aa, bb = single_point_crossover(a[p_start:p_end], b[p_start:p_end], p_mid - p_start)
        new_a = np.concatenate((new_a, aa))
        new_b = np.concatenate((new_b, bb))

    if len(points) % 2 == 0:
        new_a = np.concatenate((new_a, a[points[-2]:]))
        new_b = np.concatenate((new_b, b[points[-2]:]))

    return new_a, new_b



# a = np.array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])
# b = np.array([9, 8, 7, 6, 5, 4, 3, 2, 1, 0])
# print('a, ', a)
# print('b, ', b)
# prep = lambda x: ' '.join(map(str, x))
# print(*map(prep, single_point_crossover(a, b, 4)), '', sep='\n')
# print(*map(prep, two_point_crossover(a, b, 2, 7)), '', sep='\n')
# print(*map(prep, k_point_crossover(a, b, np.array([1, 5, 8]))), '', sep='\n')
# print(*map(prep, k_point_crossover(a, b, np.array([1, 5]))), '', sep='\n')
# print(*map(prep, k_point_crossover(a, b, np.array([1, 4, 6, 8]))), '', sep='\n')

# 0 1 2 3 4 4 3 2 1 0
# 9 8 7 6 5 5 6 7 8 9

# 0 1 2 6 5 4 3 7 8 9
# 9 8 7 3 4 5 6 2 1 0

# 0 1 7 6 5 5 6 7 8 0
# 9 8 2 3 4 4 3 2 1 9

# 0 1 7 6 5 5 6 7 8 9
# 9 8 2 3 4 4 3 2 1 0

# 0 1 7 6 4 5 6 2 8 9
# 9 8 2 3 5 4 3 7 1 0

