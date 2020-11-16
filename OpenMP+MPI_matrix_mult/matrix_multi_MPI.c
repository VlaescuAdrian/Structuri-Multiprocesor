#include <mpi.h>
#include <stdio.h>

#define SIZE 4
#define MASTER 0

int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];

void fill_matrix(int m[SIZE][SIZE])
{

  int i, j;
  for (i=0; i<SIZE; i++)
    for (j=0; j<SIZE; j++)
      m[i][j] = i + j;

}

void print_matrix(int m[SIZE][SIZE])
{
  printf("\n");
  int i, j = 0;
  for (i = 0 ; i < SIZE ; i++) {
    for (j = 0 ; j < SIZE ; j++)
      printf("%d ", m[i][j]);
    printf("\n");
  }
  printf("\n");

}

void multiply_matrix(int A[SIZE][SIZE], int B[SIZE][SIZE], int C[SIZE][SIZE], int from, int to)
{
  int i,j,k;

  for (i = from ; i < to ; i++) 
    for (j = 0 ; j < SIZE ; j++) {
      C[i][j]=0;
      for (k = 0 ; k < SIZE ; k++)
	C[i][j] += A[i][k]*B[k][j];
    }

}


int main(int argc, char *argv[])
{
  int curr_rank, P, from, to;
  MPI_Status status;
  
  MPI_Init (&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &curr_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &P);



  if (SIZE % P != 0) {
    if (curr_rank == MASTER) 
	printf("Matrix size should be a multiple of number of processors\n");
    MPI_Finalize();
    exit(-1);
  }


  from = curr_rank * SIZE/P;
  to = (curr_rank+1) * SIZE/P;


  if (curr_rank == MASTER) {
    fill_matrix(A);
    fill_matrix(B);
    printf("===============================\n\n");
    printf("Matrix A is: ");
    print_matrix(A);
    printf("Matrix B is: ");
    print_matrix(B);
    printf("=========Final Result==========\n\n");
    printf("Matrix C is: ");
  }

  MPI_Bcast (B, SIZE*SIZE, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Scatter (A, SIZE*SIZE/P, MPI_INT, A[from], SIZE*SIZE/P, MPI_INT, 0, MPI_COMM_WORLD);
  
  multiply_matrix(A, B, C, from, to);

  MPI_Gather (C[from], SIZE*SIZE/P, MPI_INT, C, SIZE*SIZE/P, MPI_INT, 0, MPI_COMM_WORLD);

  if (curr_rank == MASTER) {
    print_matrix(C);
  }

  MPI_Finalize();
  return 0;
}




