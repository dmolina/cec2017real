#ifndef _CEC17

/**
 * Inicia la función de evaluación y la dimensión.
 * @param funcid debe ser entre 1 y 30.
 * @param dimension debe ser 2, 5, 10, 30, o 50.
 */
void cec17_setfun(int fid, int dimension);

/**
 * Devuelve el error asociado al fitness.
 * @param fitness a comparar.
 * @return error (fitness - optimum).
 */
double cec17_error(double fitness);

/**
 * Devuelve el resultado de evaluar la solución.
 *
 * @param sol solución a evaluar (debe coincidir con la dimensión de la función actual).
 * @return fitness.
 */
double cec17_fitness(double *sol);

#endif