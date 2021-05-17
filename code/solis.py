"""
Local Search method Solis Wets
"""
from numpy.random import uniform
from numpy import clip, zeros

from collections import namedtuple

EAresult = namedtuple("EAresult", "fitness solution evaluations")

def _increm_bias(bias, dif):
    """Increm bias if it is successful"""
    return 0.2*bias+0.4*(dif+bias)

def _dec_bias(bias, dif):
    return bias-0.4*(dif+bias)

def soliswets(function, sol, fitness, lower, upper, maxevals, delta):
    """"
    Implements the solis wets algorithm
    """
    bias = zeros(delta.shape)
    evals = 0

    num_success = 0
    num_failed = 0
    dim = len(sol)

    while evals < maxevals:
        dif = uniform(0, delta, dim)
        newsol = clip(sol+bias+dif, lower, upper)
        new_fitness = function(newsol)
        evals += 1

        if new_fitness < fitness:
            sol = newsol
            fitness = new_fitness
            bias = _increm_bias(bias, dif)
            num_success += 1
            num_failed = 0
        elif evals < maxevals:
            new_sol = clip(sol - bias - dif, lower, upper)
            new_fitness = function(new_sol)
            evals += 1

            if new_fitness < fitness:
                sol = new_sol
                fitness = new_fitness
                bias = _dec_bias(bias, dif)
                num_success += 1
                num_failed = 0
            else:
                bias = 0.5 * bias
                num_success = 0
                num_failed += 1

        if num_success >= 5:
            num_success = 0
            delta *= 2
        elif num_failed >= 3:
            num_failed = 0
            delta /= 2

    return EAresult(solution=sol, fitness=fitness, evaluations=maxevals), delta
