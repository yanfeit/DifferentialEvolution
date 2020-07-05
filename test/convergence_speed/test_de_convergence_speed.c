#include "de.h"
#include "mtwister.h"

/*
Test the convergence of DE using different strategies, 
Use Griewank function to do the test.
*/

void test_convergence_strategy_Griewank(size_t d, FILE *fp)
{
    // fprintf(stdout, "------ TEST Griewank Function --------------\n");
    size_t i, j, k;

    // size_t d = 512;
    size_t its = 3000;
    size_t popsize = d * 10;
    double mut = 0.5;
    double crossp = 0.7;
    int refreshrate = -1;
    unsigned long seed = time(NULL);
    int strategy = 1;
    /*
    fprintf(stdout, "Dimension : %zu: \n", d);
    fprintf(stdout, "Size of the population : %zu\n", popsize);
    fprintf(stdout, "Maximum number of iterations : %zu\n", its);
    fprintf(stdout, "Mutation factor : %f\n", mut);
    fprintf(stdout, "Crossover parameter : %f\n", crossp);
	fprintf(stdout, "Refresh rate : %d\n", refreshrate);
	fprintf(stdout, "Strtegy : %d\n", strategy);
	fprintf(stdout, "seed : %d\n", seed);
    */
    De_func_Griewank_params args;
    De_func_Griewank_params_set(&args, d);

    // The format of the bound is like
    // {x1_min, x1_max, x2_min, x2_max, ..., xd_min, xd_max}
    double *bounds = (double *)malloc(2 * d * sizeof(double));

    for (i = 0; i < d; ++i)
    {
        bounds[2 * i] = -600;
        bounds[2 * i + 1] = 600;
    }

    De_worker res;
    De_worker_alloc(&res, d);

    De_optimizer(De_func_Griewank, (void *)&args, bounds, &res, d, mut, crossp, popsize, its, strategy, refreshrate, seed, fp);

    De_worker_print(&res, fp);
    De_worker_free(&res);
    free(bounds);
    bounds = NULL;
    /*
    fprintf(stdout, "------ END of TEST Griewank Function -------\n");
    */
}

int main(int argc, char **argv)
{
    size_t i, j;

    int dims[5] = {16, 32, 64, 128, 256};

    for (j = 0; j < 5; ++j)
    {
        clock_t pass = clock();

        for (i = 0; i < 10; ++i)
        {
            test_convergence_strategy_Griewank(dims[j], NULL);
        }
        pass = clock() - pass;
        double time_taken = ((double)pass) / CLOCKS_PER_SEC / 10.0;
        printf("take %f seconds to execute per time\n", time_taken);
    }
}