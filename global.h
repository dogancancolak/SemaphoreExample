//
// Created by root on 11/30/16.
//

#ifndef ASS2_GLOBAL_H
#define ASS2_GLOBAL_H

#include <sys/types.h>
#include <semaphore.h>


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

pthread_mutex_t brideLock;
pthread_mutex_t groomLock;
pthread_mutex_t values;
int brideNumber;                                     //            Creating all variables
int groomNumber;                                     //            all files can reach variables
int brideNumbersem;
int groomNumbersem;
int married;
int gettingMarried;
int totalbride;
int totalgroom;

typedef sem_t Semaphore;

Semaphore registsem;
Semaphore couple;
Semaphore bridesem;
Semaphore groomsem;
Semaphore incdecsemb;
Semaphore incdecsemg;

#endif //ASS2_GLOBAL_H
