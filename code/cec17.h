#ifndef _CEC17

#define _CEC17 1

#if defined(WIN32) || defined(_WIN32) || defined (_WIN64)
#define PATH_SEPARATOR '\\'
#else
#define PATH_SEPARATOR '/'
#endif


/**
 * Inicia la función de evaluación y la dimensión.
 * @param algname (results will be copy to results_algname directory).
 * @param funcid debe ser entre 1 y 30.
 * @param dimension debe ser 2, 5, 10, 30, o 50.
 */
void cec17_init(const char *algname, int funcid, int dimension);

/**
 * Desactiva el guardar en fichero, y muestra por pantalla.
 */
void cec17_print_output(void);

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
