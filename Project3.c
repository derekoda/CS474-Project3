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


#define _REENTRANT
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

int main(int argc, char *argv[]) {

    // i is a counter variable
    int i = 1;
    // T is the number of threads to use, default is 1
    int T = 1;
    // N is the size of the array, default is 100
    int N = 100;
    // V is the value every element in the array should be set to, default is 0
    int V = 0;
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
}

