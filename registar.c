//
// Created by root on 11/28/16.
//

#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "stdio.h"
#include "global.h"
#include "registar.h"



void makeCeramony(){
    unsigned int random = (rand()%8)+1;
    printf("------------------------\n");
    printf(ANSI_COLOR_RED"                              Ceramony in Progress\n"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA"Bride:%d\n"ANSI_COLOR_BLUE"Groom:%d\n"ANSI_COLOR_YELLOW"Getting Married:%d\nMarried:%d\n"ANSI_COLOR_CYAN"Total Bride:%d\nTotal Groom:%d\n"ANSI_COLOR_RESET" \n",brideNumber,groomNumber,gettingMarried,married, totalbride,totalgroom);
    sleep(random); // Ceramony waiting
    gettingMarried--;
    married = married+1;
    printf("------------------------\n");
    printf(ANSI_COLOR_GREEN"                              Ceramony Completed\n"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MAGENTA"Bride:%d\n"ANSI_COLOR_BLUE"Groom:%d\n"ANSI_COLOR_YELLOW"Getting Married:%d\nMarried:%d\n"ANSI_COLOR_CYAN"Total Bride:%d\nTotal Groom:%d\n"ANSI_COLOR_RESET" \n",brideNumber,groomNumber,gettingMarried,married, totalbride,totalgroom);
    pthread_mutex_unlock(&brideLock); // bride will die
    pthread_mutex_unlock(&groomLock); // groom will die
}

void registar(){

    while(1) {
        sem_wait(&registsem); // waiting for grooms/brides signal
        gettingMarried++;

        pthread_mutex_lock(&values);    //locking values
        sem_wait(&incdecsemb);
        brideNumber--;
        sem_getvalue(&bridesem,&brideNumbersem);    //  decrement bride
        sem_post(&incdecsemb);

        sem_wait(&incdecsemg);
        groomNumber--;
        sem_getvalue(&groomsem,&groomNumbersem);    //  decrement groom
        sem_post(&incdecsemg);
        pthread_mutex_unlock(&values);      // unlocking values

        makeCeramony();

        sem_post(&couple);  // register can take another couple

    }

}
