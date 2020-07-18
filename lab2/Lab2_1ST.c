// Name: Manpreet Sokhi
// Date: April 8, 2020
// Title: Lab assignment 2: Multithreading in C and network commands
// Description: This program performs matrix multiplication in C.

/*COEN 146L : Lab1, part 1 SingleThreaded */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>n

#define N 1000
#define M 1000
#define L 1000

pthread_t tids[N];
double matrixA[N][M], matrixB[M][L], matrixC[N][L], matrixD[N][L] = {0.0};

void printMatrix(int nr, int nc, double matrix[nr][nc]);
void *rowCalculator(void *row);
void checkMatrix(int nr, int nc);

int main() {
    srand(time(NULL));
    int i, j, k = 0;

    // filling matrixA with random values
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            matrixA[i][j] = rand()%5; // rand()
        }
    }
    printf("\nafter filling matrixA");

    // filling matrixB with random values
    for (i = 0; i < M; i++) {
        for (j = 0; j < L; j++) {
            matrixB[i][j] = rand()%5; // rand()
        }
    }
    printf("\nafter filling matrixB");

    // single threaded version
    /*
        for(i = 0; i < N; i++)
           for(j = 0; j < L; j++)
               for ( k = 0; k < M; k++)
                     matrixD[i][j] += matrixA[i][k] * matrixB[k][j];
                     */


    // multi-threaded version
    for (i = 0; i < N; i++) {
        int *rowPtr = malloc(sizeof(int)); // pointer for row count
        *rowPtr = i;
        pthread_create(&tids[i], NULL, rowCalculator, rowPtr);
    }

    for (i = 0; i < N; i++) {
        pthread_join(tids[i], NULL);
        // usleep(5000);
    }

    printf("\n\nMatrixA:\n");
    // printMatrix(N, M, matrixA);
    printf("\n\nMatrixB:\n");
    // printMatrix(M, L, matrixB);
    printf("\n\nMatrixC:\n");
    printMatrix(N, L, matrixC);

    printf("\n\nMatrixD:\n");
    // printMatrix(N, L, matrixD);

    checkMatrix(N, L);

    return 0;
}

void printMatrix(int nr, int nc, double matrix[nr][nc]) {
    int i,j;
    for (i = 0; i < nr; i++) {
        for (j = 0; j < nc; j ++) {
            printf("%lf  ", matrix[i][j]);
        }
        printf("\n");
    }
}

void *rowCalculator(void *row) {
    int n = *((int *) row);
    int i, j = 0;
    free(row);

    for (i = 0; i < L; i++) {
        for (j = 0; j < M; j++) {
            matrixC[n][i] += matrixA[n][j] * matrixB[j][i];
        }
    }
}

void checkMatrix (int nr, int nc) {
    int flag = 0;
    int i,j;
    for (i = 0; i < nr; i++) {
        for (j = 0; j < nc; j++) {
            if (matrixC[i][j] != matrixD[i][j]) {
                flag = 1;
                break;
            }
        }
    }

    if (flag == 1) {
        printf("\nFalse\n");
    } else {
        printf("\nTrue\n");
    }
}