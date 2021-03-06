/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);
void transpose_32_32_v1(int M, int N, int A[N][M], int B[M][N]);
void transpose_32_32_v2(int M, int N, int A[N][M], int B[M][N]);
void transpose_64_64_v1(int M, int N, int A[N][M], int B[M][N]);
void transpose_64_64_v2(int M, int N, int A[N][M], int B[M][N]);
void transpose_61_67(int M, int N, int A[N][M], int B[M][N]);
/*
   transpose_32_32 - transpose function for 32 x 32 matrix
 */
void transpose_32_32_v1(int M, int N, int A[N][M], int B[M][N])
{
	int i, j, ii, jj, tmp;
	int block_size = 8;
	int blk_num_per = M / block_size;
	for (i = 0; i < blk_num_per ; i++) {
		for (j = 0; j < blk_num_per; j++) {
			for (ii = i*block_size; ii < i*block_size + block_size; ii++) {
				for (jj = j*block_size; jj < j*block_size + block_size; jj++) {
					tmp = A[ii][jj];
					B[jj][ii] = tmp;
				}
			}
		}
	}
}

void transpose_32_32_v2(int M, int N, int A[N][M], int B[M][N])
{	
	int i, j, k, t0, t1, t2, t3, t4, t5, t6, t7;
	for (i = 0; i < N; i += 8) {
		for (j = 0; j < M; j += 8) {
			for (k = 0; k < 8; k ++) {
				t0 = A[i + k][j];
				t1 = A[i + k][j + 1];
				t2 = A[i + k][j + 2];
				t3 = A[i + k][j + 3];
				t4 = A[i + k][j + 4];
				t5 = A[i + k][j + 5];
				t6 = A[i + k][j + 6];
				t7 = A[i + k][j + 7];
				B[j][i + k] = t0;
				B[j + 1][i + k] = t1;
				B[j + 2][i + k] = t2;
				B[j + 3][i + k] = t3;
				B[j + 4][i + k] = t4;
				B[j + 5][i + k] = t5;
				B[j + 6][i + k] = t6;
				B[j + 7][i + k] = t7;

			}
		}
	}

}

/*
   transpose_64_64 - tranpose function for 64 x 64 matrix
 */
/* My original version */
void transpose_64_64_v1(int M, int N, int A[N][M], int B[M][N])
{
	int i, j, k, t0, t1, t2, t3;
	for (i = 0; i < N; i += 4) {
		for (j = 0; j < M; j += 4) {
			for (k = 0; k < 4; k++) {
				t0 = A[i + k][j];
				t1 = A[i + k][j + 1];
				t2 = A[i + k][j + 2];
				t3 = A[i + k][j + 3];
				B[j][i + k] = t0;
				B[j + 1][i + k] = t1;
				B[j + 2][i + k] = t2;
				B[j + 3][i + k] = t3;
			}
		}
	}
}

/* refer to https://zhuanlan.zhihu.com/p/28585726 */
void transpose_64_64_v2(int M, int N, int A[N][M], int B[M][N])
{
	int i, j, k, t0, t1, t2, t3, t4, t5, t6, t7;
	for (i = 0;i < N; i += 8) {
		for (j = 0; j < M; j += 8) {
			for (k = j; k < j + 4; k++) {
				t0 = A[k][i];
				t1 = A[k][i + 1];
				t2 = A[k][i + 2];
				t3 = A[k][i + 3];
				t4 = A[k][i + 4];
				t5 = A[k][i + 5];
				t6 = A[k][i + 6];
				t7 = A[k][i + 7];

				B[i][k] = t0;
				B[i][k + 4] = t4;
				B[i + 1][k] = t1;
				B[i + 1][k + 4] = t5;
				B[i + 2][k] = t2;
				B[i + 2][k + 4] = t6;
				B[i + 3][k] = t3;
				B[i + 3][k + 4] = t7;
			}
			for (k = i; k < i + 4; k++) {
				t0 = A[j + 4][k];
				t1 = A[j + 5][k];
				t2 = A[j + 6][k];
				t3 = A[j + 7][k];
				t4 = B[k][j + 4];
				t5 = B[k][j + 5];
				t6 = B[k][j + 6];
				t7 = B[k][j + 7];

				B[k][j + 4] = t0;
				B[k][j + 5] = t1;
				B[k][j + 6] = t2;
				B[k][j + 7] = t3;
				B[k + 4][j] = t4;
				B[k + 4][j + 1] = t5;
				B[k + 4][j + 2] = t6;
				B[k + 4][j + 3] = t7;
			}
			for (k = i + 4;k < i + 8;k++)
			{
				t0 = A[j + 4][k];
				t1 = A[j + 5][k];
				t2 = A[j + 6][k];
				t3 = A[j + 7][k];
				B[k][j + 4] = t0;
				B[k][j + 5] = t1;
				B[k][j + 6] = t2;
				B[k][j + 7] = t3;
			}
		}
	}
}

/*
   transpose_61_67 transpose function for 61 x 67 matrix
 */
/* refer to https://zhuanlan.zhihu.com/p/28585726 */
void transpose_61_67(int M, int N, int A[N][M], int B[M][N])
{
	int i, j, k, h;
	for (i = 0; i < N; i += 16)
	{
		for (j = 0; j < M; j += 16)
		{
			for (k = i; k < i + 16 && k < N; k++)
			{
				for (h = j; h < j + 16 && h < M; h++)
				{
					B[h][k] = A[k][h];
				}
			}
		}
	}
}


/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
	if (M == 32 && N == 32)
		transpose_32_32_v2(M, N, A, B);
	else if (M == 64 && N == 64)
		transpose_64_64_v2(M, N, A, B);
	else if (M == 61 && N == 67)
		transpose_61_67(M, N, A, B);
	else
		printf("Do nothing\n");
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 


/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

