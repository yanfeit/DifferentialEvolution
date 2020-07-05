#include "de.h"
#include "mtwister.h"

/*
Test the convergence of DE using different strategies, 
Use Schwefel function to do the test.
*/

void test_convergence_strategy_Schwefel(int strategy, FILE *fp)
{
    fprintf(stdout, "------ TEST Schwefel Function --------------\n");
    size_t i, j, k;

    size_t d = 16;
    size_t its = 3000;
    size_t popsize = d * 10;
    double mut = 0.5;
    double crossp = 0.7;
    int refreshrate = 10;
    unsigned long seed = 3;
    // int strategy = 1;

    fprintf(stdout, "Dimension : %zu: \n", d);
    fprintf(stdout, "Size of the population : %zu\n", popsize);
    fprintf(stdout, "Maximum number of iterations : %zu\n", its);
    fprintf(stdout, "Mutation factor : %f\n", mut);
    fprintf(stdout, "Crossover parameter : %f\n", crossp);
    fprintf(stdout, "Refresh rate : %d\n", refreshrate);
    fprintf(stdout, "Strtegy : %d\n", strategy);
    fprintf(stdout, "seed : %d\n", seed);

    De_func_Schwefel_params args;
    De_func_Schwefel_params_set(&args, d);

    // The format of the bound is like
    // {x1_min, x1_max, x2_min, x2_max, ..., xd_min, xd_max}
    double *bounds = (double *)malloc(2 * d * sizeof(double));

    for (i = 0; i < d; ++i)
    {
        bounds[2 * i] = -500;
        bounds[2 * i + 1] = 500;
    }

    De_worker res;
    De_worker_alloc(&res, d);

    De_optimizer(De_func_Schwefel, (void *)&args, bounds, &res, d, mut, crossp, popsize, its, strategy, refreshrate, seed, fp);

    De_worker_print(&res, stdout);
    De_worker_free(&res);
    free(bounds);
    bounds = NULL;
    fprintf(stdout, "------ END of TEST Schwefel Function -------\n");
}

int main(int argc, char **argv)
{
    size_t i;

    int strategies[5] = {1, 2, 3, 4, 5};

    char outputFilename[5][128] = {
        "strategy1Schwefel.csv",
        "strategy2Schwefel.csv",
        "strategy3Schwefel.csv",
        "strategy4Schwefel.csv",
        "strategy5Schwefel.csv",
    };

    FILE *ofp;

    for (i = 0; i < 5; ++i)
    {
        ofp = fopen(outputFilename[i], "w");
        test_convergence_strategy_Schwefel(strategies[i], ofp);
        fclose(ofp);
    }
}