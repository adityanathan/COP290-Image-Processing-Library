//MKL
#include "mkl.h"
float *A, *B, *C;

A = new float[matrix_size * matrix_size];
B = new float[matrix_size * matrix_size];
C = new float[matrix_size * matrix_size];

for (int i = 0; i < matrix_size * matrix_size; i++)
{
    A[i] = rand();
    B[i] = rand();
    C[i] = 0;
}

cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
    matrix_size,  matrix_size,  matrix_size, 1.0, A,matrix_size,
    B, matrix_size, 0.0, C, matrix_size);


//OpenBLAS
#include "cblas.h"
void matrix_multiplcation(double *A, int A_width, int A_height,
         double *B, int B_width, int B_height,
         double *AB, bool tA, bool tB, double beta)
{
    int A_height = tA ? A_width  : A_height;
    int A_width  = tA ? A_height : A_width;
    int B_height = tB ? B_width  : B_height;
    int B_width  = tB ? B_height : B_width;
    int m = A_height;
    int n = B_width;
    int k = A_width;
    // Error, width and height should match!
    assert(A_width == B_height);
    int lda = tA ? m : k;
    int ldb = tB ? k : n;
    #define TRANSPOSE(X) ((X) ? CblasTrans : CblasNoTrans)
    // http://www.netlib.org/lapack/explore-html/d7/d2b/dgemm_8f.html
    cblas_dgemm(CblasRowMajor,
                TRANSPOSE(tA), TRANSPOSE(tB),
                m, n, k, 1_0,
                A, lda,
                B, ldb,
                beta,
                AB, n);

    #undef TRANSPOSE(X)
}

//pthreads

// CPP Program to multiply two matrix using pthreads
#include <bits/stdc++.h>
using namespace std;

// maximum size of matrix
#define MAX 4

// maximum number of threads
#define MAX_THREAD 4

int matA[MAX][MAX];
int matB[MAX][MAX];
int matC[MAX][MAX];
int step_i = 0;

void* multi(void* arg)
{
	int core = step_i++;

	// Each thread computes 1/4th of matrix multiplication
	for (int i = core * MAX / 4; i < (core + 1) * MAX / 4; i++)
		for (int j = 0; j < MAX; j++)
			for (int k = 0; k < MAX; k++)
				matC[i][j] += matA[i][k] * matB[k][j];
}

// Driver Code
int main()
{
	// Generating random values in matA and matB
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			matA[i][j] = rand() % 10;
			matB[i][j] = rand() % 10;
		}
	}

	// Displaying matA
	cout << endl
		<< "Matrix A" << endl;
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++)
			cout << matA[i][j] << " ";
		cout << endl;
	}

	// Displaying matB
	cout << endl
		<< "Matrix B" << endl;
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++)
			cout << matB[i][j] << " ";
		cout << endl;
	}

	// declaring four threads
	pthread_t threads[MAX_THREAD];

	// Creating four threads, each evaluating its own part
	for (int i = 0; i < MAX_THREAD; i++) {
		int* p;
		pthread_create(&threads[i], NULL, multi, (void*)(p));
	}

	// joining and waiting for all threads to complete
	for (int i = 0; i < MAX_THREAD; i++)
		pthread_join(threads[i], NULL);

	// Displaying the result matrix
	cout << endl
		<< "Multiplication of A and B" << endl;
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++)
			cout << matC[i][j] << " ";
		cout << endl;
	}
	return 0;
}




//Calling from terminal
//OpenBLAS
gcc test_cblas_dgemm.c -I /your_path/OpenBLAS/include/ -L/your_path/OpenBLAS/lib -lopenblas -lpthread -lgfortran
