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
	int i, j, ir, jr, tmp;
	printf("Hey yo! 😄\n");
    for (ir = 4; ir <= N; ir += 4) {
        for (jr = 4; jr <= M; jr += 4) {
	    for(i = 0; i < ir; i++){
		for(j = 0; j < jr; j++){
            	    tmp = A[i][j];
            	    B[j][i] = tmp;
		    printf("%d \n", i);
		    printf("%d \n", j);
		}
	    } 
	    ir += 4;
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
    int i, j, ir, jr, tmp;
	jr = 8;
	ir = 8;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
	    for(; i < ir; i++){
		for(; j < jr; j++){
            	    tmp = A[i][j];
            	    B[j][i] = tmp;
		}
	    }
	    jr += 8;
        }
	ir += 8;
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
#ifndef DEBUG
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}
#endif

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


/* -----------------------------------------------------------------
				'||'''|. '||''''| '||     '||''''| |''||''| '||''''|
				 ||   ||  ||   .   ||      ||   .     ||     ||   .
				 ||   ||  ||'''|   ||      ||'''|     ||     ||'''|
				 ||   ||  ||       ||      ||         ||     ||
				.||...|' .||....| .||...| .||....|   .||.   .||....|
				
				
								|''||''| '||  ||` |''||''| .|'''|
								   ||     ||  ||     ||    ||
								   ||     ||''||     ||    `|'''|,
								   ||     ||  ||     ||     .   ||
								  .||.   .||  ||. |..||..|  |...|'

  ---------------------------------------------------------------- */ 


// To enable debugging (i.e. run this main), enter the following:
// $ gcc trans.c -o trans-test -D DEBUG
// To run it with the matrix you specified in main(), enter:
// $ ./trans-test 
// PROFIT??? 



#ifdef DEBUG

int main()
{
	// These defines have syntacical reasons, don't mind them
	#define ROWS 4 
	#define COLS 2

	int M = COLS;
	int N = ROWS; 
	int A[ROWS][COLS] = {{5, 7}, {3, 2}, {1, 6}, {9, 2}}; // Fill up A
	int B[M][N];

	printf("A: %d \n", A[2][0]);
	transpose_submit(M, N, A, B);
}


#endif






