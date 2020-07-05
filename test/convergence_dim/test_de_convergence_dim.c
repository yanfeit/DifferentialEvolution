#include "de.h"
#include "mtwister.h"

/*
Test the convergence of DE when the dimensions of the 
problems gets larger and larger. 
Use Ackley function to do the test.
*/

void test_convergence_dim(size_t d, FILE *fp)
{
    fprintf(stdout, "------ TEST Ackley Function --------------\n");
    size_t i, j, k;

    size_t its = 3000;
    double mut = 0.8;
    double crossp = 0.7;
    size_t popsize = d*10;

    fprintf(stdout, "Dimension : %zu: \n", d);
    fprintf(stdout, "Size of the population : %zu\n", popsize);
    fprintf(stdout, "Maximum number of iterations : %zu\n", its);
    fprintf(stdout, "Mutation factor : %f\n", mut);
    fprintf(stdout, "Crossover parameter : %f\n", crossp);

    De_func_Ackley_params args;
    De_func_Ackley_params_set(&args, d, 20.0, 0.2, 2 * PI);

    // The format of the bound is like
    // {x1_min, x1_max, x2_min, x2_max, ..., xd_min, xd_max}
    double *bounds = (double *)malloc(2 * d * sizeof(double));

    for (i = 0; i < d; ++i)
    {
        bounds[2*i] = -32.768;
        bounds[2*i+1] = 32.768;
    }

    De_worker res;
    De_worker_alloc(&res, d);

    De_optimizer(De_func_Ackley, (void *)&args, bounds, &res, d, mut, crossp, popsize, its, 1, 10, 3, fp);

    De_worker_print(&res, stdout);
    De_worker_free(&res);
    free(bounds);
    bounds = NULL;
    fprintf(stdout, "------ END of TEST Ackley Function -------\n");
}


int main(int argc, char** argv)
{
    size_t i;
	size_t dims[6] = {8, 16, 32, 64, 128, 256};
    char outputFilename[6][128] = {"d8.csv", 
                                   "d16.csv",
                                   "d32.csv",
                                   "d64.csv",
                                   "d128.csv",
                                   "d256.csv"
    };

    FILE* ofp;

    for (i=0; i<6; ++i)
    {
        ofp = fopen(outputFilename[i], "w");
        test_convergence_dim(dims[i], ofp);
        fclose(ofp);
    }
}