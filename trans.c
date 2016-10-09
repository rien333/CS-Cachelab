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
#ifdef DEBUG
#include <stdlib.h>
#endif
#include "cachelab.h"

#ifdef DEBUG

int randrange(int min, int max)
{
	return (rand() % (max + 1 - min)) + min;
}

// Fill array with random elements
void fill_array(int N, int M, int A[N][M])
{
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			A[i][j] = randrange(0, 15);
		}
	}
}

void print_array(int N, int M, int A[N][M]) {
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			int num = A[i][j];
			if(num > 9  && num < 20) {
				printf("%d ", num);
			}
			else if(num > 20 || num < 0) {
				printf("0  ");
				continue;
			}
			else {
				printf("%d  ", num);
			}
		}
		printf("\n");
	}
	printf("\n");
}
#endif

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
	int i, j, ir, jr;

	int temp1,temp2,temp3,temp4;
	#define BLOCKSIZE4 4
	#define BLOCKSIZE8 8
//	if((N==67 && M==61) || (N==32 && M==32)) {
		if(1) {
		int temp5,temp6,temp7,temp8;
		for (ir = 0; ir < M; ir += BLOCKSIZE8) {
			for (jr = 0; jr < N; jr += BLOCKSIZE8) {
				for (i = jr; (i < jr + BLOCKSIZE8); ++i) {
					if(i >= N) { // Continue when going out of bounds
						continue;
					}
					for (j = ir; (j < ir + BLOCKSIZE8); ++j) {
						if(j >= M) {
							continue;
						}
						if (i != j) {
					    B[j][i] = A[i][j];	//When not a diagonal element, perform the normal transpose
						}
						else { 
							// if's are cache friendlier than switches
							if ((i%BLOCKSIZE8)==0) {
								temp1=A[i][j];
							}
							else if ((i%BLOCKSIZE8)==1) {
								temp2=A[i][j];
							}
							else if ((i%BLOCKSIZE8)==2) {
								temp3=A[i][j];
							}
							else if ((i%BLOCKSIZE8)==3) {
								temp4=A[i][j];
							}
							else if ((i%BLOCKSIZE8)==4) {
								temp5=A[i][j];
							}
							else if ((i%BLOCKSIZE8)==5) {
								temp6=A[i][j];
							}
							else if ((i%BLOCKSIZE8)==6) {
								temp7=A[i][j];
							}
							else if ((i%BLOCKSIZE8)==7) {
								temp8=A[i][j];
							}
						}
					}
		    }
				// Block is over
				if(ir==jr) { // on diagonal
					i = 0; // reuse i
					for(; i < BLOCKSIZE8; i++) {
						if(i == 0)	{
							B[ir+i][ir+i]=temp1;
						}
						else if(i == 1)	{
							B[ir+i][ir+i]=temp2;
						}
						else if(i == 2)	{
							B[ir+i][ir+i]=temp3;
						}
						else if(i == 3)	{
							B[ir+i][ir+i]=temp4;
						}
						else if(i == 4)	{
							B[ir+i][ir+i]=temp5;
						}
						else if(i == 5)	{
							B[ir+i][ir+i]=temp6;
						}
						else if(i == 6)	{
							B[ir+i][ir+i]=temp7;
						}
						else if(i == 7)	{
							B[ir+i][ir+i]=temp8;
						}
					}  
				}
			}
		}
	} // end 67x61 / 32x32
	else if(N==64 && M==64) { 
		for (ir = 0; ir < N; ir += BLOCKSIZE4) {
			for (jr = 0; jr < M; jr += BLOCKSIZE4) {
				for(i = ir; i < ir + BLOCKSIZE4; ++i) {
					for(j = jr; j < jr + BLOCKSIZE4; ++j) {
						if (i != j) {
					    B[j][i] = A[i][j];	// When not a diagonal element, perform the normal transpose
						}
						else {
							if ((i%BLOCKSIZE4)==0) {
								temp1=A[i][j];
							}
							else if ((i%BLOCKSIZE4)==1) {
								temp2=A[i][j];
							}
							else if ((i%BLOCKSIZE4)==2) {
								temp3=A[i][j];
							}
							else if ((i%BLOCKSIZE4)==3) {
								temp4=A[i][j];
							}
						}
					}
		    }
				// Block is over
				if(ir==jr) { // on diagonal
					i = 0; // reuse i
					for(; i < BLOCKSIZE4; i++) {
						if(i == 0)	{
							B[ir+i][ir+i]=temp1;
						}
						else if(i == 1)	{
							B[ir+i][ir+i]=temp2;
						}
						else if(i == 2)	{
							B[ir+i][ir+i]=temp3;
						}
						else if(i == 3)	{
							B[ir+i][ir+i]=temp4;
						}
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
char trans_desc[] = "Simple jr-wise scan transpose";
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
	int M = 64;
	int N = 64; 
//	int A[N][M] = {{5, 7}, {3, 2}, {1, 6}, {9, 2}}; // Fill up A

	int A[N][M];
	int B[M][N];

	fill_array(N, M, A);
//	print_array(N, M, A);
	transpose_submit(M, N, A, B);

	printf("\n\t------------------------------------------------------------------------------------ \n\n");
//	print_array(M, N, B);
	printf("Correct: %d\n", is_transpose(M, N, A, B));
//	printf("Correct matrix: \n");
//	trans(M, N, A, B);
//	print_array(M, N, B);
}


#endif






