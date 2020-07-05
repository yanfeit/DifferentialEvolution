#ifndef __DE_H__
#define __DE_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "mtwister.h"

#define PI 3.1415926535897932384626433

// Differential Evolution Strategy, only include bin scenarios.
enum {
    DE_BEST_1_BIN = 1,
    DE_RAND_1_BIN = 2,
    DE_RANDTOBEST_1_BIN = 3,
    DE_BEST_2_BIN = 4,
    DE_RAND_2_BIN = 5
};

// ----------------- DE WORKER ------------------
/*
What is De_worker ?
Namely, a Differential Evolution Algorithm's worker
De acts like the namespace in C++ which does not exist in C language ~~
It contains a parameter vector x and its evaluation 
f(x) as the result. 
vec : parameter vector, the length is dimension of the problem.
res : its evaluation f(x).
*/

typedef struct
{
    double *x;
    double fx;
    size_t d;
} De_worker;

/*
Memory allocation for De_worker.
*/
void De_worker_alloc(De_worker *worker, const size_t d);

/*
Set De_worker's parameters
*/
void De_worker_set(De_worker *worker,
                   const double *x,
                   const size_t d);

/*
Print De_worker's information
*/
void De_worker_print(De_worker *worker, FILE *fp);

/*
Free memory of the De_worker
*/
void De_worker_free(De_worker *worker);
// ----------------- DE WORKER ------------------

// --------- Dynamic Vector And Matrix ----------
typedef struct
{
    double *x;
    size_t size;
} De_vector;

void De_vector_alloc(De_vector *vec, const size_t size);

void De_vector_set(De_vector *vec,
                   const double *x,
                   const size_t size);

void De_vector_print(De_vector *vec, FILE *fp);

void De_vector_free(De_vector *vec);

typedef struct
{
    double **x;
    size_t m; // number of rows
    size_t n; // number of columns
} De_matrix;

void De_matrix_alloc(De_matrix *mat,
                     const size_t m,
                     const size_t n);

void De_matrix_set(De_matrix *mat,
                   const double **x,
                   const size_t m,
                   const size_t n);

void De_matrix_print(De_matrix *mat, FILE *fp);

void De_matrix_free(De_matrix *mat);
// --------- Dynamic Vector And Matrix ----------

/*
Differential Evolution Optimizer.
objf     : objective function, f(x, params)
args     : the parameters of the objective function
bounds   : vector x's low bounds and high bounds, 
           such as [x1_min, x1_max, x2_min, x2_max, ..., xd_min, xd_max]
res      : result, x and f(x)
d        : dimension
mut      : mutation parameter
crossp   : crossover parameter
popsize  : size of the population pool
its      : iteration times
strategy : minimization strategy
refresh  : refreshing rate of output to screen
seed     : seed of the random number generator
fp       : where to output
*/
void De_optimizer(double (*objf)(double *, void *),
                  void *args,
                  const double *bounds,
                  De_worker *res,
                  const size_t d,
                  const double mut,
                  const double crossp,
                  const size_t popsize,
                  const size_t its,
                  int strategy,
                  int refresh,
                  unsigned long seed,
                  FILE *fp);



// -------------auxillary function --------------

/*
idxsmallest
return the index of the smallest number in the array.
*/
size_t idxsmallest(double *arr, size_t size);

/*
pick3idx
pick 3 indices from 0 to size (exclusivevly).
The index that is chosen is required be different from notpick
*/
void pick3idx(size_t size,
              const size_t notpick,
              size_t *idx_r1,
              size_t *idx_r2,
              size_t *idx_r3,
              MTRand *r);

/*
pick5idx
pick 5 indices from 0 to size (exclusivevly).
The index that is chosen is required be different from notpick
*/
void pick5idx(size_t size,
              const size_t notpick,
              size_t *idx_r1,
              size_t *idx_r2,
              size_t *idx_r3,
              size_t *idx_r4,
              size_t *idx_r5,
              MTRand *r);

// -------------auxillary function --------------

// ----------------- TEST FUNCTION --------------

// ----------------- Ackley Function ------------
/*
Ackley Function, f(x) = -a * exp(-b \sqrt(1/d * \sum x_i^2))
                        - exp(1/d \sum cos(cx_i))
                        + a
                        + exp(1)
Recommended variable values are: a = 20, b = 0.2 and c = 2π.
More info: https://www.sfu.ca/~ssurjano/ackley.html
*/
typedef struct
{
    size_t d;
    double a;
    double b;
    double c;
} De_func_Ackley_params;

void De_func_Ackley_params_set(De_func_Ackley_params *args,
                               const size_t d,
                               const double a,
                               const double b,
                               const double c);

double De_func_Ackley(double *x,
                      void *params);
// ----------------- Ackley Function ------------

// ----------------- Bukin Function -------------
/*
Bukin Function, f(x) = 100 * \sqrt(|x_2 - 0.01 x_1^2|) + 0.01 |x_1 + 10|
The function is usually evaluated on the rectangle x1 \in [-15, -5], x2 \in [-3, 3].
The minimum locates at x = (-10, 1), f(x) = 0
More info: https://www.sfu.ca/~ssurjano/bukin6.html
*/
typedef struct 
{   
    size_t d;
} De_func_Bukin_params;

void De_func_Bukin_params_set(De_func_Bukin_params *args,
                              const size_t d);

double De_func_Bukin(double *x,
                     void *params);
// ----------------- Bukin Function -------------

// ----------------- Schwefel Function ----------
/*
Schefel Function,
f(x) = 418.9829 * d - \sum x_i sin(\sqrt(|x_i|))
The function is usually evaluated on the hypercube xi \in [-500, 500], for all i = 1, ..., d.
The minimum locates at x = (420.9687, 420.9687), f(x) = 0
More info: https://www.sfu.ca/~ssurjano/schwef.html
*/
typedef struct 
{
    size_t d;
} De_func_Schwefel_params;

void De_func_Schwefel_params_set(De_func_Schwefel_params *args,
                                 const size_t d);

double De_func_Schwefel(double *x,
                        void *params);
// ----------------- Schwefel Function ----------

// ----------------Rastrigin Function -----------
/*
Rastrigin Function,
f(x) = 10 * d - \sum [x_i^2 - 10.0 * cos(2 * pi * x_i)]
The function is usuall evaluated on the hypercube x_i \in [-5.12, 5.12], for all i = 1, ..., d
The minimum locates at x = (0, ..., 0), f(x) = 0.
More info: https://www.sfu.ca/~ssurjano/rastr.html
*/
typedef struct 
{
    size_t d;
} De_func_Rastrigin_params;

void De_func_Rastrigin_params_set(De_func_Rastrigin_params *args,
                                  const size_t d);

double De_func_Rastrigin(double *x,
                         void *params);
// ---------------- Rastrigin Function -------------

// ---------------- Langermann Function ------------
/*
Langermann Function,
f(x) = \sum_i^m c_i exp( 1/pi sum_j^d (x_j - A_ij)^2 ) cos (\pi * \sum_j^d (x_j - A_ij)^2 )
The function is usually evaluated on the hypercube xi \in [0, 10], for all i = 1, ... , d.
More info: https://www.sfu.ca/~ssurjano/langer.html
*/
typedef struct 
{
    size_t d;
    size_t m;
} De_func_Langermann_params;

void De_func_Langermann_params_set(De_func_Langermann_params *args);

double De_func_Langermann(double *x,
                          void *params);

// ---------------- Langermann Function ------------

// ---------------- Griewank Function --------------
/*
Griewank Function,
f(x) = \sum x_i^2/4000 - \prod cos(x_i/sqrt(i)) + 1
The function is usually evaluated on the hypercube x_i \in [-600, 600], for all i = 1, ..., d.
More info: https://www.sfu.ca/~ssurjano/griewank.html
*/
typedef struct 
{
    size_t d;
} De_func_Griewank_params;

void De_func_Griewank_params_set(De_func_Griewank_params *args, const size_t d);

double De_func_Griewank(double *x,
                        void *params);

// ---------------- Griewank Function --------------

// ----------------- TEST FUNCTION --------------

#endif /* __DE_H__ */