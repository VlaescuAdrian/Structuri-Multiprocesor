#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

//Set the matrix dimensions
#define N 32
int main () {


	//Alocarea dinamica pentru A,B,C si P(3D)
    int **A = (int **)calloc(N , sizeof(int *)); 
    for (int i=0; i<N; i++) 
         A[i] = (int *)calloc(N , sizeof(int)); 
    int **B = (int **)calloc(N , sizeof(int *)); 
    for (int i=0; i<N; i++) 
         B[i] = (int *)calloc(N , sizeof(int)); 
	
    int C[N][N] = {0};
	
	int *** P = (int ***)calloc(N,sizeof(int**));

    for (int i = 0; i< N; i++) {

		P[i] = (int **) calloc(N,sizeof(int *));

        for (int j = 0; j < N; j++) {

            P[i][j] = (int *)calloc(N,sizeof(int));
        }

    }
	for (int i = 0 ; i < N ; i++){
		for (int j = 0 ; j < N ; j++){
			A[i][j] = B[i][j] = (i + j);
		}
	}

	time_t t0 = time(0);

	//Algoritmul CREW-PRAM cu n^3 procesoare
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++){
            for (int k = 0; k < N; k++) {
				//Etapa 1
                P[i][j][k] = A[i][k] * B[k][j];
                for (int m = 0; m < (int)log2(N); m++) {
					//Etapa 2
                    if (k % (int)pow(2, m+1) == 0) {
                        P[i][j][k] += P[i][j][k + (int)pow(2, m)];
                    }
                }
            }
        }
    }
	//Etapa 2: reducerea prin insumarea a n elemente ale fiecarui vector din tabloul 2D
	//P[i][j] (in total n^2
	//vectori), folosind n procesoare pentru fiecare vector: Pi,j,0; Pi,j,1; Pi,j,2; .... 
	//Pi,j,n-1, obtinand rezultatul in P[i][j][0]
	for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++){
            for (int k = 0; k < N; k++) {
			 	C[i][j] += P[i][j][k];
			}
		}
	}


	time_t t1 = time(0);
	double datetime_diff_ms = difftime(t1, t0) * 1000.;
	
	printf("\n\nMatrix multiply took %f seconds to execute \n\n", datetime_diff_ms); 

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    } 
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			free(P[i][j]);

		free(P[i]);
	}
	free(P);
	for (int i = 0; i < N; i++) {
	  free(A[i]);
	  free(B[i]);
	}
	free(A);
	free(B);	
}
