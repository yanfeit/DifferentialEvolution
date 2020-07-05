#include "de.h"
#include "mtwister.h"

// ----------------- DE WORKER ------------------
void De_worker_alloc(De_worker *worker, const size_t d)
{
    worker->x = (double *)malloc(d * sizeof(double));
    worker->fx = 0.0;
    worker->d = d;
}

void De_worker_set(De_worker *worker,
                   const double *x,
                   const size_t d)
{
    register size_t i;
    for (i = 0; i < d; ++i)
    {
        worker->x[i] = x[i];
    }
}

void De_worker_print(De_worker *worker, FILE *fp)
{
    if (fp != NULL)
    {
        register size_t i;
        fprintf(fp, "x: ");
        for (i = 0; i < worker->d; ++i)
        {
            fprintf(fp, "%.15f\t", worker->x[i]);
        }
        fprintf(fp, "\n");
        fprintf(fp, "f(x): %.15f", worker->fx);
        fprintf(fp, "\n");
    }
}

void De_worker_free(De_worker *worker)
{
    free(worker->x);
    worker->x = NULL;
}
// ----------------- DE WORKER ------------------

// --------- Dynamic Vector And Matrix ----------

void De_vector_alloc(De_vector *vec, const size_t size)
{
    vec->x = (double *)malloc(size * sizeof(double));
    vec->size = size;
}

void De_vector_set(De_vector *vec,
                   const double *x,
                   const size_t size)
{
    register size_t i;
    for (i = 0; i < size; ++i)
    {
        vec->x[i] = x[i];
    }
}

void De_vector_print(De_vector *vec, FILE *fp)
{
    if (fp != NULL)
    {
        register size_t i;
        fprintf(fp, "Vector : ");
        for (i = 0; i < vec->size; ++i)
        {
            fprintf(fp, "%.15f\t", vec->x[i]);
        }
        fprintf(fp, "\n");
    }
}

void De_vector_free(De_vector *vec)
{
    free(vec->x);
    vec->x = NULL;
}

void De_matrix_alloc(De_matrix *mat,
                     const size_t m,
                     const size_t n)
{
    register size_t i;
    mat->m = m;
    mat->n = n;
    mat->x = (double **)malloc(m * sizeof(double *));

    for (i = 0; i < m; ++i)
    {
        mat->x[i] = (double *)malloc(n * sizeof(double));
    }
}

void De_matrix_set(De_matrix *mat,
                   const double **x,
                   const size_t m,
                   const size_t n)
{
    register size_t i, j;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            mat->x[i][j] = x[i][j];
        }
    }
}

void De_matrix_print(De_matrix *mat, FILE *fp)
{
    if (fp != NULL)
    {
        register size_t i, j;
        fprintf(fp, "Matrix : \n");
        for (i = 0; i < mat->m; ++i)
        {
            for (j = 0; j < mat->n; ++j)
            {
                fprintf(fp, "%.15f \t", mat->x[i][j]);
            }
            fprintf(fp, "\n");
        }
        fprintf(fp, "\n");
    }
}

void De_matrix_free(De_matrix *mat)
{
    register size_t i;
    for (i = 0; i < mat->m; ++i)
    {
        free(mat->x[i]);
        mat->x[i] = NULL;
    }
    free(mat->x);
    mat->x = NULL;
}

// --------- Dynamic Vector And Matrix ----------

// -------------auxillary function --------------

size_t idxsmallest(double *arr, size_t size)
{
    size_t i;
    size_t index = 0;

    for (i = 1; i < size; ++i)
    {
        if (arr[i] < arr[index])
            index = i;
    }

    return index;
}

void pick3idx(size_t size,
              const size_t notpick,
              size_t *idx_r1,
              size_t *idx_r2,
              size_t *idx_r3,
              MTRand *r)
{
    size_t x = notpick;
    while (x == notpick)
    {
        x = (size_t)(genRandLong(r) % ((unsigned long)size));
    }
    *idx_r1 = x;

    while ((x == notpick) || (x == *idx_r1))
    {
        x = (size_t)(genRandLong(r) % ((unsigned long)size));
    }
    *idx_r2 = x;

    while ((x == notpick) || (x == *idx_r1) || (x == *idx_r2))
    {
        x = (size_t)(genRandLong(r) % ((unsigned long)size));
    }
    *idx_r3 = x;
}

void pick5idx(size_t size,
              const size_t notpick,
              size_t *idx_r1,
              size_t *idx_r2,
              size_t *idx_r3,
              size_t *idx_r4,
              size_t *idx_r5,
              MTRand *r)
{
    size_t x = notpick;
    while (x == notpick)
    {
        x = (size_t)(genRandLong(r) % ((unsigned long)size));
    }
    *idx_r1 = x;

    while ((x == notpick) || (x == *idx_r1))
    {
        x = (size_t)(genRandLong(r) % ((unsigned long)size));
    }
    *idx_r2 = x;

    while ((x == notpick) || (x == *idx_r1) || (x == *idx_r2))
    {
        x = (size_t)(genRandLong(r) % ((unsigned long)size));
    }
    *idx_r3 = x;

    while ((x == notpick) || (x == *idx_r1) || (x == *idx_r2) || (x == *idx_r3))
    {
        x = (size_t)(genRandLong(r) % ((unsigned long)size));
    }
    *idx_r4 = x;

    while ((x == notpick) || (x == *idx_r1) || (x == *idx_r2) || (x == *idx_r3) || (x == *idx_r4))
    {
        x = (size_t)(genRandLong(r) % ((unsigned long)size));
    }
    *idx_r5 = x;
}

// -------------auxillary function --------------

// --------- DE Optimization --------------------

/*
Choice of strategy 
This is from Storn & Price's paper
Choice of Stategy
naming-convention for differential evolution algorithm: DE/x/y/z
    DE : stands for Differential Evolution
    x  : a string which denotes the vector to be perturbed
    y  : number of differnce vectors taken for perturbation of x
    z  : crossover method (exp = exponential, bin = binomial)

In the paper, *Reevaluating Exponetial Crossover in Differential Evolution*
by Oyoji Tanabe and Alex Fukunaga. Exponential crossover sometimes performs
quite poorly on the benchmarks. Here exponential crossover strategy is not
realized in this program. 

There are some simple rules worth noting:
    1) mut is usually between 0.5 and 1.0 (in rare cases > 1)
    2) crossp is between 0 and 1 with 0., 0.3, 0.7 and 1. being worth to be tried first
    3) To start off popsize=10*d is a reasonable choice. 
    4) If you inicrease popsize, mut usually has to be decreased
    5) When the DE/best ... schemes fail DE/rand ... usually works and vice versa

strategy 1 : DE/best/1/bin
strategy 2 : DE/rand/1/bin
strategy 3 : DE/rand-to-best/1/bin
strategy 4 : DE/best/2/bin
strategy 5 : DE/rand/2/bin
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
                  FILE *fp)
{
    size_t i, j, k;
    // Mersenne Twister Rand number generator
    MTRand r = seedRand(seed);

    double *diff = (double *)malloc(d * sizeof(double));
    for (i = 0; i < d; ++i)
        diff[i] = bounds[2 * i + 1] - bounds[2 * i];

    // Generate a population pool
    De_matrix pop, pop_denorm;
    De_matrix_alloc(&pop, popsize, d);
    De_matrix_alloc(&pop_denorm, popsize, d);

    for (i = 0; i < popsize; ++i)
    {
        for (j = 0; j < d; ++j)
        {
            pop.x[i][j] = genRand(&r);
        }
    }

    // Denormalization for the population pool
    for (i = 0; i < popsize; ++i)
    {
        for (j = 0; j < d; ++j)
        {
            pop_denorm.x[i][j] = bounds[2 * j] + pop.x[i][j] * diff[j];
        }
    }

    // ---- Compute the fitness ------
    double *fitness = (double *)malloc(popsize * sizeof(double));
    for (i = 0; i < popsize; ++i)
    {
        fitness[i] = objf(pop_denorm.x[i], args);
    }

    // Find out the index of the smallest element in the fitness array.
    size_t best_idx = idxsmallest(fitness, popsize);

    // Find out the vector x corresponding to the smallest fitness
    De_vector best;
    De_vector_alloc(&best, d);
    De_vector_set(&best, pop_denorm.x[best_idx], d);

    size_t r1, r2, r3, r4, r5, rnbri;

    De_vector trial, trial_denorm;

    De_vector_alloc(&trial, d);
    De_vector_alloc(&trial_denorm, d);

    if (fp != NULL)
    {
        fprintf(fp, "Iter NO., best func. min., best vec. in the pool\n");
    }
    for (i = 0; i < its; ++i)
    {

        for (j = 0; j < popsize; ++j)
        {
            if (strategy <= 3)
            {
                pick3idx(popsize, j, &r1, &r2, &r3, &r);
            }
            else
            {
                pick5idx(popsize, j, &r1, &r2, &r3, &r4, &r5, &r);
            }

            for (k = 0; k < d; ++k)
            {
                trial.x[k] = pop.x[j][k];
            }
            rnbri = (size_t)genRandN(&r, (unsigned long)popsize);

            // DE/best/1/bin
            if (strategy == DE_BEST_1_BIN)
            {

                for (k = 0; k < d; ++k)
                {
                    if ((genRand(&r) < crossp) || (k == rnbri))
                    {
                        trial.x[k] = pop.x[best_idx][k] + mut * (pop.x[r2][k] - pop.x[r3][k]);
                        if (trial.x[k] < 0.0)
                            trial.x[k] = 0.0;

                        if (trial.x[k] > 1.0)
                            trial.x[k] = 1.0;
                    }
                }
            }
            // DE/rand/1/bin
            else if (strategy == DE_RAND_1_BIN)
            {
                for (k = 0; k < d; ++k)
                {
                    if ((genRand(&r) < crossp) || (k == rnbri))
                    {
                        trial.x[k] = pop.x[r1][k] + mut * (pop.x[r2][k] - pop.x[r3][k]);
                        if (trial.x[k] < 0.0)
                            trial.x[k] = 0.0;

                        if (trial.x[k] > 1.0)
                            trial.x[k] = 1.0;
                    }
                }
            }
            // DE/rand-to-best/1/bin
            else if (strategy == DE_RANDTOBEST_1_BIN)
            {
                for (k = 0; k < d; ++k)
                {
                    if ((genRand(&r) < crossp) || (k == rnbri))
                    {
                        trial.x[k] = trial.x[k] + mut * (pop.x[best_idx][k] - trial.x[k]) + mut * (pop.x[r1][k] - pop.x[r2][k]);
                        if (trial.x[k] < 0.0)
                            trial.x[k] = 0.0;

                        if (trial.x[k] > 1.0)
                            trial.x[k] = 1.0;
                    }
                }
            }
            // DE/best/2/bin
            else if (strategy == DE_BEST_2_BIN)
            {
                for (k = 0; k < d; ++k)
                {
                    if ((genRand(&r) < crossp) || (k == rnbri))
                    {
                        trial.x[k] = pop.x[best_idx][k] + mut * (pop.x[r1][k] + pop.x[r2][k] -
                                                                 pop.x[r3][k] - pop.x[r4][k]);
                        if (trial.x[k] < 0.0)
                            trial.x[k] = 0.0;

                        if (trial.x[k] > 1.0)
                            trial.x[k] = 1.0;
                    }
                }
            }
            // DE/rand/2/bin
            else
            {
                for (k = 0; k < d; ++k)
                {
                    if ((genRand(&r) < crossp) || (k == rnbri))
                    {
                        trial.x[k] = pop.x[r5][k] + mut * (pop.x[r1][k] + pop.x[r2][k] -
                                                           pop.x[r3][k] - pop.x[r4][k]);
                        if (trial.x[k] < 0.0)
                            trial.x[k] = 0.0;

                        if (trial.x[k] > 1.0)
                            trial.x[k] = 1.0;
                    }
                }
            }

            for (k = 0; k < d; ++k)
                trial_denorm.x[k] = bounds[2 * k] + trial.x[k] * diff[k];

            double f = objf(trial_denorm.x, args);

            // Selection
            if (f < fitness[j])
            {
                fitness[j] = f;
                for (k = 0; k < d; ++k)
                    pop.x[j][k] = trial.x[k];

                if (f < fitness[best_idx])
                {
                    best_idx = j;
                    for (k = 0; k < d; ++k)
                        best.x[k] = trial_denorm.x[k];
                }
            }
        }
        // output to fp, refresh <= 0 will not output
        if (refresh > 0)
        {
            if (i % refresh == 0)
            {
                if (fp != NULL)
                {
                    fprintf(fp, "%d,", i);
                    fprintf(fp, "%15.10f,", fitness[best_idx]);
                    fprintf(fp, "[");
                    for (k = 0; k < d; k++)
                    {
                        fprintf(fp, "%14.7f\t", best.x[k]);
                    }
                    fprintf(fp, "]\n");
                }
            }
        }
    }

    De_worker_set(res, best.x, d);
    res->fx = fitness[best_idx];

    De_vector_free(&trial);
    De_vector_free(&trial_denorm);
    De_vector_free(&best);
    De_matrix_free(&pop);
    De_matrix_free(&pop_denorm);
    free(diff);
    free(fitness);
    diff = NULL;
    fitness = NULL;
}

// --------- DE Optimization --------------------
