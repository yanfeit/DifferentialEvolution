#include "de.h"
#include "mtwister.h"

int main(int argc, char** argv)
{
    size_t i, j, k;

    size_t its = 1000;
    double mut = 0.8;
    double crossp = 0.7;

    size_t popsize = 40;
    size_t d = 4;

    De_func_Ackley_params args;
    De_func_Ackley_params_set(&args, d, 20.0, 0.2, 2*PI);

    // The format of the bound is like
    // {x1_min, x1_max, x2_min, x2_max, ..., xd_min, xd_max}
    double *bounds = (double *) malloc(2 * d * sizeof(double));
    double *diff   = (double *) malloc(d * sizeof(double));

    bounds[0] = -5.0;
    bounds[1] =  5.0;
    bounds[2] = -10.0;
    bounds[3] =  5.0;
    bounds[4] = -10.0;
    bounds[5] =  5.0;
    bounds[6] = -10.0;
    bounds[7] =  5.0;

    for (i = 0; i < d; ++i)
        diff[i] = bounds[2*i+1] - bounds[2*i];

    // Mersenne Twister Rand number generator
    MTRand r = seedRand(time(NULL));

    // Generate a population pool
    De_matrix pop, pop_denorm;

    De_matrix_alloc(&pop, popsize, d);
    De_matrix_alloc(&pop_denorm, popsize, d);
    for (i = 0; i < popsize; ++i){
        for (j = 0; j < d; ++j)
        {
            pop.x[i][j] = genRand(&r);
        }
    }
    De_matrix_print(&pop);

    for (i = 0; i < popsize; ++i){
        for (j = 0; j < d; ++j)
        {
            pop_denorm.x[i][j] = bounds[2*j] + pop.x[i][j] * diff[j];
        }
    }
    De_matrix_print(&pop_denorm);

    // ---- Compute the fitness ------
    double *fitness = (double *) malloc(popsize * sizeof(double));
    for (i = 0; i < popsize; ++i)
    {
        fitness[i] = De_func_Ackley(pop_denorm.x[i], (void*) &args);
    }

    for (i = 0; i < popsize; ++i)
    {
        printf("%f\t", fitness[i]);
    }
    
    size_t best_idx = idxsmallest(fitness, popsize);

    printf("%zu\n", best_idx);

    De_vector best;
    De_vector_alloc(&best, d);

    De_vector_set(&best, pop_denorm.x[best_idx], d);
    De_vector_print(&best);

    for (i = 0; i < its; ++i)
    {
        for (j = 0; j < popsize; ++j)
        {
            size_t a_idx, b_idx, c_idx;
            pick3idx(popsize, j, &a_idx, &b_idx, &c_idx, &r);
            // printf("\n%zu \t %zu \t %zu \n", a_idx, b_idx, c_idx);

            De_vector a, b, c, mutant, trial, trial_denorm;
            De_vector_alloc(&a, d);
            De_vector_alloc(&b, d);
            De_vector_alloc(&c, d);
            De_vector_alloc(&mutant, d);
            De_vector_alloc(&trial, d);
            De_vector_alloc(&trial_denorm, d);

            De_vector_set(&a, pop.x[a_idx], d);
            De_vector_set(&b, pop.x[b_idx], d);
            De_vector_set(&c, pop.x[c_idx], d);

            for (k = 0; k < d; ++k)
            {
                mutant.x[k] = a.x[k] + mut * (b.x[k] - c.x[k]);
                if (mutant.x[k] < 0.0)
                    mutant.x[k] = 0.0;

                if (mutant.x[k] > 1.0) 
                    mutant.x[k] = 1.0;
            }

            size_t rnbri = (size_t) genRandN(&r, (unsigned long)popsize);
            
            // Crossover
            for (k = 0; k < d; ++k)
            {
                if ( (genRand(&r) > crossp) && (k != rnbri) )
                {
                    trial.x[k] = pop.x[j][k];
                }
                else
                {
                    trial.x[k] = mutant.x[k];
                }   
            }

            for (k = 0; k < d; ++k)
            {
                trial_denorm.x[k] = bounds[2*k] + trial.x[k] * diff[k];
            }

            double f = De_func_Ackley(trial_denorm.x, (void*) &args);

            if (f < fitness[j])
            {
                fitness[j] = f;
                for (k = 0; k < d; ++k)
                {
                    pop.x[j][k] = trial.x[k];
                }

                if (f < fitness[best_idx])
                {
                    best_idx = j;
                    for (k = 0; k < d; ++k)
                    {
                        best.x[k] = trial_denorm.x[k];
                    }
                }
            }


            De_vector_free(&a);
            De_vector_free(&b);
            De_vector_free(&c);
            De_vector_free(&mutant);
            De_vector_free(&trial);
            De_vector_free(&trial_denorm);
        }
    }

    De_vector_print(&best);
    printf("%f\n", fitness[best_idx]);



    De_vector_free(&best);
    De_matrix_free(&pop);
    De_matrix_free(&pop_denorm);
    free(bounds);
    free(diff);
}