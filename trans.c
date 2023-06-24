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
    // Case 1: 32x32
    // Since there are 5 block bits, we have a block of size 32 bytes, which can 
    // store 8 integers at a time. So we will transpose the matrix using 8x8 blocks.
    int i, j, k, tmp, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
    if(N == 32) {
        for (i = 0; i < 32; i+=8)
        {
            for (j = 0; j < 32; j+=8)
            {
                for (k = i; k < i + 8; k++)
                {
                    tmp = A[k][j];
                    tmp1 = A[k][j+1];
                    tmp2 = A[k][j+2];
                    tmp3 = A[k][j+3];
                    tmp4 = A[k][j+4];
                    tmp5 = A[k][j+5];
                    tmp6 = A[k][j+6];
                    tmp7 = A[k][j+7];
                    B[j][k] = tmp;
                    B[j+1][k] = tmp1;
                    B[j+2][k] = tmp2;
                    B[j+3][k] = tmp3;
                    B[j+4][k] = tmp4;
                    B[j+5][k] = tmp5;
                    B[j+6][k] = tmp6;
                    B[j+7][k] = tmp7;
                }
            }   
        }
    }

    // Case 2: 64x64
    // We can use the same aproach as in 32x32, just repeated 4 times,
    // i.e. we use 4 blocks of size 32x32.

    else if(N == 64) { // Hardcoded 4 blocks since nobody cares(A11-B11 A22-B22 A12-B21 A21-B12)
        for (i = 0; i < 32; i+=8)
        {
            for (j = 0; j < 32; j+=8)
            {
                for (k = i; k < i + 8; k++)
                {
                    tmp = A[k][j];
                    tmp1 = A[k][j+1];
                    tmp2 = A[k][j+2];
                    tmp3 = A[k][j+3];
                    tmp4 = A[k][j+4];
                    tmp5 = A[k][j+5];
                    tmp6 = A[k][j+6];
                    tmp7 = A[k][j+7];
                    B[j][k] = tmp;
                    B[j+1][k] = tmp1;
                    B[j+2][k] = tmp2;
                    B[j+3][k] = tmp3;
                    B[j+4][k] = tmp4;
                    B[j+5][k] = tmp5;
                    B[j+6][k] = tmp6;
                    B[j+7][k] = tmp7;
                }
            }   
        }
        for (i = 32; i < 64; i+=8)
        {
            for (j = 32; j < 64; j+=8)
            {
                for (k = i; k < i + 8; k++)
                {
                    tmp = A[k][j];
                    tmp1 = A[k][j+1];
                    tmp2 = A[k][j+2];
                    tmp3 = A[k][j+3];
                    tmp4 = A[k][j+4];
                    tmp5 = A[k][j+5];
                    tmp6 = A[k][j+6];
                    tmp7 = A[k][j+7];
                    B[j][k] = tmp;
                    B[j+1][k] = tmp1;
                    B[j+2][k] = tmp2;
                    B[j+3][k] = tmp3;
                    B[j+4][k] = tmp4;
                    B[j+5][k] = tmp5;
                    B[j+6][k] = tmp6;
                    B[j+7][k] = tmp7;
                }
            }   
        }
        for (i = 0; i < 32; i+=8)
        {
            for (j = 32; j < 64; j+=8)
            {
                for (k = i; k < i + 8; k++)
                {
                    tmp = A[k][j];
                    tmp1 = A[k][j+1];
                    tmp2 = A[k][j+2];
                    tmp3 = A[k][j+3];
                    tmp4 = A[k][j+4];
                    tmp5 = A[k][j+5];
                    tmp6 = A[k][j+6];
                    tmp7 = A[k][j+7];
                    B[j][k] = tmp;
                    B[j+1][k] = tmp1;
                    B[j+2][k] = tmp2;
                    B[j+3][k] = tmp3;
                    B[j+4][k] = tmp4;
                    B[j+5][k] = tmp5;
                    B[j+6][k] = tmp6;
                    B[j+7][k] = tmp7;
                }
            }   
        }
        for (i = 32; i < 64; i+=8)
        {
            for (j = 0; j < 32; j+=8)
            {
                for (k = i; k < i + 8; k++)
                {
                    tmp = A[k][j];
                    tmp1 = A[k][j+1];
                    tmp2 = A[k][j+2];
                    tmp3 = A[k][j+3];
                    tmp4 = A[k][j+4];
                    tmp5 = A[k][j+5];
                    tmp6 = A[k][j+6];
                    tmp7 = A[k][j+7];
                    B[j][k] = tmp;
                    B[j+1][k] = tmp1;
                    B[j+2][k] = tmp2;
                    B[j+3][k] = tmp3;
                    B[j+4][k] = tmp4;
                    B[j+5][k] = tmp5;
                    B[j+6][k] = tmp6;
                    B[j+7][k] = tmp7;
                }
            }   
        }

        // Yet wrong answer, did not figure out

    }
    // Case: 61x67
    // Best result is seen by using same method as in 32x32 but with blocks of size 16
    else
    {
        for (int k1 = 0; k1 < N; k1 += 16)
    {
      for (int k2 = 0; k2 < M; k2 += 16)
      {
        for (int i = k1; i < k1 + 16 && i < N; i++)
        {
          for (int j = k2; j < k2 + 16 && j < M; j++)
          {
            B[j][i] = A[i][j];
          }
        }
      }
    }
        
    }

  
    



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
    //registerTransFunction(trans, trans_desc); 

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

