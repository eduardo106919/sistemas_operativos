#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_VALUE 100

int main(void) {
    srand(time(0));

    // generate random matrix
    int **matrix = create_matrix();
    int value = 0;

    // print matrix
    print_matrix(matrix);


    value = rand() % MAX_VALUE;
    printf("searching for %d\n", value);

    bool row = value_exists(matrix, value);
    if (row == true)
        printf("value %d found in the matrix\n", value);
    else
        printf("value %d not found in the matrix\n", value);

    value = rand() % MAX_VALUE;
    printf("searching for %d\n", value);

    row = value_exists(matrix, value);
    if (row == true)
        printf("value %d found in the matrix\n", value);
    else
        printf("value %d not found in the matrix\n", value);

    value = rand() % MAX_VALUE;
    printf("searching for %d\n", value);

    row = value_exists(matrix, value);
    if (row == true)
        printf("value %d found in the matrix\n", value);
    else
        printf("value %d not found in the matrix\n", value);


    // free the matrix
    destroy_matrix(matrix);

    return 0;
}