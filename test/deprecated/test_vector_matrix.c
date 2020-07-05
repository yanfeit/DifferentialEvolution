#include "de.h"

int main(int argc, char** argv)
{
    De_vector a;
    double x[10] = {0.1, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t size = 10;
    De_vector_alloc(&a, size);
    De_vector_set(&a, x, size);
    De_vector_print(&a);
    De_vector_free(&a);

    De_matrix b;
    double y[4][3] = {{1, 2, 3},{3, 4, 5}, {7, 8, 9}, {3, 6, 9}};

    size_t m = 4, n = 3;
    De_matrix_alloc(&b, m, n);
    b.x[0][0] = 1.0;
    b.x[0][1] = 2.0;
    b.x[0][2] = 3.0;
    b.x[1][0] = 4.0;
    b.x[1][1] = 5.0;
    b.x[1][2] = 6.0;
    b.x[2][0] = 7.0;
    b.x[2][1] = 8.0;
    b.x[2][2] = 9.0;
    b.x[3][0] = 10.0;
    b.x[3][1] = 11.0;
    b.x[3][2] = 12.0;

    De_matrix_print(&b);
    De_matrix_free(&b);
    return 0;
}