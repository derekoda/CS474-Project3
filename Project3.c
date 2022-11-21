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

// bestRC will find the best multiple to generate our matrix
// ex if T = 6, R>=C, R = N/C, so R = 3, C = 2
int bestRC(int n)
{
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


int main(int argc, char *argv[]) {

    int R;
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
    // used to make sure R >= C
    if(C > R)
    {
        int temp = C;
        C = R;
        R = temp;
    }
    printf("%d\n", C);
    printf("%d\n", R);
    // 2d array for computations
    float matrix[N][N];

    // 1d array for row sums
    float row_sums[R];

    // 1d array for thread timings
    float thread_time[T];

    // initialize matrix
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            matrix[i][j] = V;
        }// end for
    }// end for
    
    printf("%f\n", V);
}

