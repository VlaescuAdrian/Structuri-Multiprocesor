#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>



int main() {
	
	int n, number_threads;
	printf("Introduceti SIZE-ul matricilor (N):\n");
	scanf("%d", &n);
	
	
	int a[n][n], b[n][n], c[n][n], i, j, k;
	
	struct timeval tv1, tv2;
    struct timezone tz;
	double elapsed; 
	
	omp_set_num_threads(omp_get_num_procs());
	
	for (i = 0 ; i < n ; i++) {
		for (j = 0 ; j < n ; j++) {
			a[i][j] = i + j;
			b[i][j] = abs(i - j);
			c[i][j] = 0;
		}
	}
	
	gettimeofday(&tv1, &tz);
    #pragma omp parallel shared(a,b,c) private(i,j,k) 
		{
	#pragma omp for  schedule(static)
		for (i = 0; i < n; ++i) {
			for (j = 0; j < n; ++j) {
				for (k = 0; k < n; ++k) {
					c[i][j] += a[i][k] * b[k][j];
				}
			}
		}
		number_threads = omp_get_num_threads();
		}
	
	gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
	
	for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%d\t",c[i][j]);
        }
        printf("\n");
    }
	
	printf("\n\nInmultirea matricilor s-a efectuat in  = %f secunde.\n", elapsed);
	printf("\n\nInmultirea matricilor s-a efectuat pe %d threaduri\n", number_threads);
	
	
	
	return 0;
}