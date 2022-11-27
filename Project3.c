/**
 * @file Project3.c
 * @author Derek Oda & Seth Ball
 * @brief The purpose of this project is to learn how parallel programming can be used to take 
 * advantage of multicore processing resources
 * @version 0.1
 * @date 2022-11-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */


//#define _REENTRANT
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
//#include <sys/ipc.h>
//#include <sys/shm.h>
//#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include <float.h>

#define ROWS 4000
#define COLS 4000
float matrix[ROWS][COLS];

pthread_mutex_t mutexBuffer;

// data to be passes with each thread 
// and to store results
typedef struct thread_data {
    float* mat;
    int rstart;
    int cstart;
    int r;
    int c;
    float result;
} thread_data;

// bestRC will find the best multiple to generate our matrix
// ex if T = 6, R>=C, R = N/C, so R = 3, C = 2
int bestRC(int n)
{
    if(n==1)
        return 1;
    // Initialize the maximum prime factor
    // variable with the lowest one
    int maxPrime = -1;
  
    // Print the number of 2s that divide n
    while (n % 2 == 0) {
        maxPrime = 2;
        n >>= 1; // equivalent to n /= 2
    }
  
    // n must be odd at this point, thus skip
    // the even numbers and iterate only for
    // odd integers
    for (int i = 3; i <= sqrt(n); i += 2) {
        while (n % i == 0) {
            maxPrime = i;
            n = n / i;
        }
    }
  
    // This condition is to handle the case
    // when n is a prime number greater than 2
    if (n > 2)
        maxPrime = n;
  
    return maxPrime;
}// end bestRC

// rowSum will calculate the row sum of the passed section of the 
// matrix, it will be called with a section of the matrix by each thread
void* rowSum(void* args)
{
    thread_data *tdata=(thread_data *)args;
    int rstart = tdata->rstart;
    int cstart = tdata->cstart;
    int r = tdata->r;
    int c = tdata->c;
    float *mat = tdata->mat;
    float res = tdata->result;

    //printf("rstart = %d\n cstart = %d\n r = %d\n c = %d\n",rstart,cstart,r,c);
    for (int b = rstart; b < rstart+r; b++)
    {
        for(int a = cstart; a < cstart+c; a++)
        {
            res = res + mat[a];
        }// end for
    }//end for
    printf("\n%f\n", res);
}// end rowSum

int main(int argc, char *argv[]) {

    // rows per thread
    int R;
    // columns per thread
    int C;
    // i is a counter variable
    int i = 1;
    // T is the number of threads to use, default is 1
    int T = 1;
    // N is the size of the array, default is 100
    int N = 100;
    // V is the value every element in the array should be set to, default is random float
    // between 0 and 100
    srand(time(NULL));
    float V = ((float)rand()/RAND_MAX)*(float)(100.0);
    // VFlag is a flag to determine if the user has set the value of V
    int VFlag = 0;

    while(i < argc) {
        if(strcmp(argv[i], "-t") == 0) 
            T = atoi(argv[i + 1]);
        if(strcmp(argv[i], "-s") == 0) 
            N = atoi(argv[i + 1]);
        if(strcmp(argv[i], "-v") == 0) {
            V = atoi(argv[i + 1]);
            VFlag = 1;
        } // end if
        i += 1;
    } // end for

    R = bestRC(T);
    C = T/R;
    R = N/R;
    C = N/C;
    // used to make sure R >= C
    if(C > R)
    {
        int temp = C;
        C = R;
        R = temp;
    }
    printf("%d\n", N);
    printf("%d\n", C);
    printf("%d\n", R);
    printf("%d\n", DBL_MAX);
    printf("here\n");
    // 2d array for computations
    //float matrix[N][N];
    printf("here\n");
    // 1d array for row sums
    float row_sums[N];

    // 1d array for thread timings
    float thread_time[T];
    printf("here\n");
    // initialize matrix
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            matrix[i][j] = V;
            //printf("%f\n", V);
            //printf("%f\n\n", matrix[i][j]);
        }// end for
    }// end for

    // threads
	pthread_t th[T+1];
	pthread_mutex_init(&mutexBuffer, NULL);
    printf("here\n");
	// create threads
	for(int t = 1; t <= T; t++)
	{
        // create parameters in struct 
        thread_data tdat;
        tdat.rstart = (t-1)*R;
        tdat.cstart = (t-1)*C;
        tdat.r = R;
        tdat.c = C;
        tdat.mat = *matrix;
        tdat.result = 0;
        //printf("%f\n", matrix[0][0]);
         
        
		// thread is not init
		if(pthread_create(&th[t], NULL, &rowSum, (void*)&tdat) != 0)
		{
			perror("error creating producer thread\n");
		}
	}// end for creating threads

	// join the threads
	for(int i = 1; i <= T; i++)
	{
		// threads were not joined
		if(pthread_join(th[i], NULL) != 0)
		{
			perror("error joining threads\n");
		}
	}// end for joining threads


	// destroy threads and semaphores
	pthread_mutex_destroy(&mutexBuffer);

	// end
	printf("\nEnd of program\n");
}

