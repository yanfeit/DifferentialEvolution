#include "de.h"
#include "mtwister.h"

void test_De_func_Ackley()
{
    printf("------ TEST Ackley Function --------------\n");

    size_t i, j, k;

    size_t its = 1000;
    double mut = 0.8;
    double crossp = 0.7;
    size_t popsize = 100;
    size_t d = 10;

    printf("Dimension : %zu: \n", d);
    printf("Size of the population : %zu\n", popsize);
    printf("Maximum number of iterations : %zu\n", its);
    printf("Mutation factor : %f\n", mut);
    printf("Crossover parameter : %f\n", crossp);

    De_func_Ackley_params args;
    De_func_Ackley_params_set(&args, d, 20.0, 0.2, 2 * PI);

    // The format of the bound is like
    // {x1_min, x1_max, x2_min, x2_max, ..., xd_min, xd_max}
    double *bounds = (double *)malloc(2 * d * sizeof(double));

    for (i = 0; i < d; ++i)
    {
        bounds[2 * i] = -32.768;
        bounds[2 * i + 1] = 32.768;
    }

    De_worker res;
    De_worker_alloc(&res, d);

    De_optimizer(De_func_Ackley, (void *)&args, bounds, &res, d, mut, crossp, popsize, its, 2, 0, time(NULL), stdout);

    De_worker_print(&res, stdout);
    De_worker_free(&res);
    free(bounds);
    printf("The minimun locates at x = (0, ..., 0) and f(x) = 0.0\n");
    printf("------ END of TEST Ackley Function -------\n");
}

void test_De_func_Bukin()
{
    printf("------ TEST Bukin Function --------------\n");

    size_t i, j, k;

    size_t its = 1000;
    double mut = 0.8;
    double crossp = 0.7;
    size_t popsize = 20;
    size_t d = 2;

    printf("Dimension : %zu: \n", d);
    printf("Size of the population : %zu\n", popsize);
    printf("Maximum number of iterations : %zu\n", its);
    printf("Mutation factor : %f\n", mut);
    printf("Crossover parameter : %f\n", crossp);

    De_func_Bukin_params args;
    De_func_Bukin_params_set(&args, d);

    // The format of the bound is like
    // {x1_min, x1_max, x2_min, x2_max, ..., xd_min, xd_max}
    double *bounds = (double *)malloc(2 * d * sizeof(double));

    bounds[0] = -15.0;
    bounds[1] = -5.0;
    bounds[2] = -3.0;
    bounds[3] = 3.0;

    De_worker res;
    De_worker_alloc(&res, d);

    De_optimizer(De_func_Bukin, (void *)&args, bounds, &res, d, mut, crossp, popsize, its, 2, 0, 3, stdout);

    De_worker_print(&res, stdout);
    De_worker_free(&res);
    free(bounds);
    printf("The minimun locates at x = (-10, 1) and f(x) = 0.0\n");
    printf("------ END of TEST Bukin Function -------\n");
}

void test_De_func_Schwefel()
{
    printf("------ TEST Schwefel Function --------------\n");

    size_t i, j, k;

    size_t its = 1000;
    double mut = 0.8;
    double crossp = 0.7;
    size_t popsize = 40;
    size_t d = 4;

    printf("Dimension : %zu: \n", d);
    printf("Size of the population : %zu\n", popsize);
    printf("Maximum number of iterations : %zu\n", its);
    printf("Mutation factor : %f\n", mut);
    printf("Crossover parameter : %f\n", crossp);

    De_func_Schwefel_params args;
    De_func_Schwefel_params_set(&args, d);

    // The format of the bound is like
    // {x1_min, x1_max, x2_min, x2_max, ..., xd_min, xd_max}
    double *bounds = (double *)malloc(2 * d * sizeof(double));

    bounds[0] = -500.0;
    bounds[1] = 500.0;
    bounds[2] = -500.0;
    bounds[3] = 500.0;
    bounds[4] = -500.0;
    bounds[5] = 500.0;
    bounds[6] = -500.0;
    bounds[7] = 500.0;

    De_worker res;
    De_worker_alloc(&res, d);

    De_optimizer(De_func_Schwefel, (void *)&args, bounds, &res, d, mut, crossp, popsize, its, 2, 0, 3, stdout);

    De_worker_print(&res, stdout);
    De_worker_free(&res);
    free(bounds);
    printf("The minimun locates at x = (420.9687, ..., 420.9687) and f(x) = 0.0\n");
    printf("------ END of TEST Schwefel Function -------\n");
}

void test_De_func_Rastrigin()
{
    printf("------ TEST Rastrigin Function --------------\n");

    size_t i, j, k;

    size_t its = 1000;
    double mut = 0.8;
    double crossp = 0.7;
    size_t popsize = 80;
    size_t d = 8;

    printf("Dimension : %zu: \n", d);
    printf("Size of the population : %zu\n", popsize);
    printf("Maximum number of iterations : %zu\n", its);
    printf("Mutation factor : %f\n", mut);
    printf("Crossover parameter : %f\n", crossp);

    De_func_Rastrigin_params args;
    De_func_Rastrigin_params_set(&args, d);

    // The format of the bound is like
    // {x1_min, x1_max, x2_min, x2_max, ..., xd_min, xd_max}
    double *bounds = (double *)malloc(2 * d * sizeof(double));

    for (i = 0; i < d; ++i)
    {
        bounds[2 * i] = -5.12;
        bounds[2 * i + 1] = 5.12;
    }

    De_worker res;
    De_worker_alloc(&res, d);

    De_optimizer(De_func_Rastrigin, (void *)&args, bounds, &res, d, mut, crossp, popsize, its, 2, 0, 3, stdout);

    De_worker_print(&res, stdout);
    De_worker_free(&res);
    free(bounds);
    printf("The minimun locates at x = (0, ..., 0) and f(x) = 0.0\n");
    printf("------ END of TEST Rastrigin Function -------\n");
}

void test_De_func_Langermann()
{
    printf("------ TEST Langermann Function --------------\n");

    size_t i, j, k;

    size_t its = 1000;
    double mut = 0.8;
    double crossp = 0.7;
    size_t popsize = 20;
    size_t d = 2;

    printf("Dimension : %zu: \n", d);
    printf("Size of the population : %zu\n", popsize);
    printf("Maximum number of iterations : %zu\n", its);
    printf("Mutation factor : %f\n", mut);
    printf("Crossover parameter : %f\n", crossp);

    De_func_Langermann_params args;
    De_func_Langermann_params_set(&args);

    // The format of the bound is like
    // {x1_min, x1_max, x2_min, x2_max, ..., xd_min, xd_max}
    double *bounds = (double *)malloc(2 * d * sizeof(double));

    for (i = 0; i < d; ++i)
    {
        bounds[2 * i] = 0;
        bounds[2 * i + 1] = 10;
    }

    De_worker res;
    De_worker_alloc(&res, d);

    De_optimizer(De_func_Langermann, (void *)&args, bounds, &res, d, mut, crossp, popsize, its, 2, 0, 3, stdout);

    De_worker_print(&res, stdout);
    De_worker_free(&res);
    free(bounds);
    printf("I don't know what the minimum it is :-)\n");
    printf("------ END of TEST Langermann Function -------\n");
}

void test_De_func_Griewank()
{
    printf("------ TEST Griewank Function --------------\n");

    size_t i, j, k;

    size_t its = 1000;
    double mut = 0.8;
    double crossp = 0.7;
    size_t popsize = 80;
    size_t d = 8;

    printf("Dimension : %zu: \n", d);
    printf("Size of the population : %zu\n", popsize);
    printf("Maximum number of iterations : %zu\n", its);
    printf("Mutation factor : %f\n", mut);
    printf("Crossover parameter : %f\n", crossp);

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

    FILE *ofp;
    char outputFilename[] = "Griewank.txt";
    ofp = fopen(outputFilename, "w");
    if (ofp == NULL)
    {
        fprintf(stderr, "Can't open output file %s!\n", outputFilename);
    }

    De_optimizer(De_func_Griewank, (void *)&args, bounds, &res, d, mut, crossp, popsize, its, 2, 1, 3, ofp);
    fclose(ofp);

    De_worker_print(&res, stdout);
    De_worker_free(&res);
    free(bounds);
    printf("The minimun locates at x = (0, ..., 0) and f(x) = 0.0\n");
    printf("------ END of TEST Griewank Function -------\n");
}

int main(int argc, char **argv)
{

    test_De_func_Ackley();
    test_De_func_Bukin();
    test_De_func_Schwefel();
    test_De_func_Rastrigin();
    test_De_func_Langermann();
    test_De_func_Griewank();
    return 0;
}