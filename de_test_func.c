#include "de.h"

/*
Ackley Function, f(x) = -a * exp(-b \sqrt(1/d * \sum x_i^2))
                        - exp(1/d \sum cos(cx_i))
                        + a
                        + exp(1)
Recommended variable values are: a = 20, b = 0.2 and c = 2π.
*/
double De_func_Ackley(double *x,
                      void *params)
{
    De_func_Ackley_params *args = (De_func_Ackley_params *)params;

    size_t d = args->d;
    double a = args->a;
    double b = args->b;
    double c = args->c;

    double dinv = 1.0 / ((double) d);

    double sum_x2 = 0.0;
    double sum_cos_cx = 0.0;

    double res;

    size_t i = 0;

    for (i = 0; i < d; ++i)
    {   
        sum_x2 += x[i]*x[i];
        sum_cos_cx += cos(c * x[i]);
    }

    res = -a * exp(-b * sqrt(dinv * sum_x2) ) -
    exp( dinv * sum_cos_cx ) + a + exp(1.0);

    return res;
}

void De_func_Ackley_params_set(De_func_Ackley_params *args,
                               const size_t d,
                               const double a,
                               const double b, 
                               const double c)
{
    args->d = d;
    args->a = a;
    args->b = b;
    args->c = c;
}                               


// ----------------- Bukin Function -------------
/*
Bukin Function, f(x) = 100 * \sqrt(|x_2 - 0.01 x_1^2|) + 0.01 |x_1 + 10|
The function is usually evaluated on the rectangle x1 \in [-15, -5], x2 \in [-3, 3].
The minimum locates at x = (-10, 1), f(x) = 0
*/
void De_func_Bukin_params_set(De_func_Bukin_params *args,
                              const size_t d)
{
    args->d = d;
}

double De_func_Bukin(double *x,
                     void *params)
{
    De_func_Bukin_params *args = (De_func_Bukin_params *) params;

    size_t d = args->d;

    double res;

    res = 100.0 * sqrt( fabs(x[1] - 0.01 * x[0] * x[0]) ) + 0.01 * fabs(x[0] + 10.0);

    return res;
}
// ----------------- Bukin Function -------------


// ----------------- Schwefel Function ----------
/*
Schefel Function,
f(x) = 418.9829 * d - \sum x_i sin(\sqrt(|x_i|))
The function is usually evaluated on the hypercube xi \in [-500, 500], for all i = 1, …, d.
The minimum locates at x = (420.9687, 420.9687), f(x) = 0
More info: https://www.sfu.ca/~ssurjano/schwef.html
*/

void De_func_Schwefel_params_set(De_func_Schwefel_params *args,
                                 const size_t d)
{
    args->d = d;
}

double De_func_Schwefel(double *x,
                        void *params)
{
    De_func_Schwefel_params *args = (De_func_Schwefel_params *) params;
    
    size_t d = args->d;
    size_t i;

    double res = 418.9829 * (double) d;

    for (i = 0; i < d; ++i)
        res -= x[i] * sin(sqrt( fabs(x[i]) ));

    return res;
}
// ----------------- Schwefel Function ----------

// ----------------Rastrigin Function -----------
/*
Rastrigin Function,
f(x) = 10 * d - \sum [x_i^2 - 10.0 * cos(2 * pi * x_i)]
The function is usuall evaluated on the hypercube x_i \in [-5.12, 5.12], for all i = 1, ..., d
The minimum locates at x = (0, ..., 0), f(x) = 0.
More info: https://www.sfu.ca/~ssurjano/rastr.html
*/

void De_func_Rastrigin_params_set(De_func_Rastrigin_params *args,
                                  const size_t d)
{
    args->d = d;
}

double De_func_Rastrigin(double *x,
                         void *params)
{
    De_func_Rastrigin_params *args = (De_func_Rastrigin_params *) params;
    size_t d = args->d;
    size_t i;

    double res = 10.0 * ((double) d);

    for (i = 0; i < d; ++i)
        res += ( x[i] * x[i] - 10.0 * cos(2 * PI * x[i]) );

    return res;
}
// ----------------Rastrigin Function -----------

// ---------------- Langermann Function ------------
/*
Langermann Function,
f(x) = \sum_i^m c_i exp( 1/pi sum_j^d (x_j - A_ij)^2 ) cos (\pi * \sum_j^d (x_j - A_ij)^2 )
The function is usually evaluated on the hypercube xi \in [0, 10], for all i = 1, ... , d.
More info: https://www.sfu.ca/~ssurjano/langer.html
*/

void De_func_Langermann_params_set(De_func_Langermann_params *args)
{
    args->d = 2;
    args->m = 5;
}

double De_func_Langermann(double *x,
                          void *params)
{
    De_func_Langermann_params *args = (De_func_Langermann_params *) params;
    size_t d = args->d;
    size_t m = args->m;

    double c[5] = {1.0, 2.0, 5.0, 2.0, 3.0};
    double A[5][2] = {{3.0, 5.0},
                      {5.0, 2.0},
                      {2.0, 1.0},
                      {1.0, 4.0},
                      {7.0, 9.0}};
    size_t i, j;

    double invPI = 1.0 / PI;
    double temp, temp2, res = 0.0;
    
    for (i = 0; i < m; ++i){
        temp = 0.0;
        for (j = 0; j < d; ++j){
            temp2 = x[j] - A[i][j];
            temp += temp2*temp2;
        }
        res += c[i] * exp(-invPI * temp) * cos(PI * temp);
    }
    return res;
}

// ---------------- Langermann Function ------------

// ---------------- Griewank Function --------------
/*
Griewank Function,
f(x) = \sum x_i^2/4000 - \prod cos(x_i/sqrt(i)) + 1
The function is usually evaluated on the hypercube x_i \in [-600, 600], for all i = 1, ..., d.
More info: https://www.sfu.ca/~ssurjano/griewank.html
*/

void De_func_Griewank_params_set(De_func_Griewank_params *args, const size_t d)
{
    args->d = d;
}

double De_func_Griewank(double *x,
                        void *params)
{
    De_func_Griewank_params *args = (De_func_Griewank_params *) params;
    size_t i, d = args->d;

    double part1 = 0.0;
    double part2 = 1.0;

    for (i = 0; i < d; ++i)
    {
        part1 += x[i]*x[i] / 4000.0;
        part2 *= cos(x[i]/sqrt((double) (i+1)));
    }

    return part1 - part2 + 1.0;
}

// ---------------- Griewank Function --------------