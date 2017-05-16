//
// Created by root on 11/28/16.
//

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "stdlib.h"
#include "semaphore.h"
#include "global.h"
#include "registar.h"
#include "bride.h"
#include "groom.h"


pthread_t bride_id[15]; //max bride count 15
pthread_t groom_id[15]; //max bride count 15
pthread_t reg_id[2];
pthread_t *exiter;      // Press Enter for exit
unsigned int randomizeCreate;  // For random bride or groom create


void Creator(){
    while(1){
        randomizeCreate = rand()%2; // Groom or Bride
        if(randomizeCreate == 0){      // Bride
            randomizeCreate = rand()&10;
            if(randomizeCreate>6 && brideNumber<15){   //Queue not full and random >6
                pthread_mutex_lock(&values);    //
                sem_wait(&incdecsemb);          // Locking variables
                sem_post(&bridesem);
                brideNumber++;
                totalbride++;
                sem_getvalue(&bridesem,&brideNumbersem);
                sem_post(&incdecsemb);          //
                pthread_mutex_unlock(&values);  // unlocking variables
                printf("------------------------\n");
                printf("                              Bride Added\n");
                printf(ANSI_COLOR_MAGENTA"Bride:%d\n"ANSI_COLOR_BLUE"Groom:%d\n"ANSI_COLOR_YELLOW"Getting Married:%d\nMarried:%d\n"ANSI_COLOR_CYAN"Total Bride:%d\nTotal Groom:%d\n"ANSI_COLOR_RESET" \n",brideNumber,groomNumber,gettingMarried,married, totalbride,totalgroom);
                pthread_create(&(bride_id[brideNumber-1]),NULL,&Bride,NULL);    // Create Bride
            }

        }
        else{   // Bride
            randomizeCreate = rand()&10;
            if(randomizeCreate>6 && groomNumber<15){ //Queue not full and random >6
                sem_wait(&incdecsemg);          //
                pthread_mutex_lock(&values);    // Lock variables
                sem_post(&groomsem);
                groomNumber++;
                totalgroom++;
                sem_getvalue(&groomsem,&groomNumbersem);        //
                sem_post(&incdecsemg);                          // unlock variables
                pthread_mutex_unlock(&values);

                printf("------------------------\n");
                printf("                              Groom Added\n");
                printf(ANSI_COLOR_MAGENTA"Bride:%d\n"ANSI_COLOR_BLUE"Groom:%d\n"ANSI_COLOR_YELLOW"Getting Married:%d\nMarried:%d\n"ANSI_COLOR_CYAN"Total Bride:%d\nTotal Groom:%d\n"ANSI_COLOR_RESET" \n",brideNumber,groomNumber,gettingMarried,married, totalbride,totalgroom);
                pthread_create(&(groom_id[groomNumber-1]),NULL,&Groom,NULL);    // Creating Groom
            }
        }
        randomizeCreate = rand()%4+2; // Wait random
        sleep(randomizeCreate);
    }
}

void out(){
    getchar(); // For exit
    exit(1);
}

int main(void){
    printf("\npress ENTER when you want to terminate\n");
    printf("\n");
    sleep(4);
    sem_init(&registsem,0,0);
    sem_init(&bridesem,0,4);
    sem_init(&groomsem,0,4);   // init semaphore
    sem_init(&couple,0,2);
    sem_init(&incdecsemb,0,1);
    sem_init(&incdecsemg,0,1);
    pthread_mutex_init(&brideLock,NULL);
    pthread_mutex_init(&groomLock,NULL);
    pthread_mutex_init(&values,NULL);
                                                                    //  I initialized 4 bride and 4 groom for showing max 2 registar can work at the sametime. You can take comment this part if you want.
    brideNumber = 1;
    groomNumber= 1;
    pthread_create(&(bride_id[brideNumber-1]),NULL,&Bride,NULL);
    pthread_create(&(groom_id[groomNumber-1]),NULL,&Groom,NULL);
    brideNumber = 2;
    groomNumber= 2;
    pthread_create(&(bride_id[brideNumber-1]),NULL,&Bride,NULL);
    pthread_create(&(groom_id[groomNumber-1]),NULL,&Groom,NULL);
    brideNumber = 3;
    groomNumber= 3;
    pthread_create(&(bride_id[brideNumber-1]),NULL,&Bride,NULL);
    pthread_create(&(groom_id[groomNumber-1]),NULL,&Groom,NULL);
    brideNumber = 4;
    groomNumber= 4;
    pthread_create(&(bride_id[brideNumber-1]),NULL,&Bride,NULL);
    pthread_create(&(groom_id[groomNumber-1]),NULL,&Groom,NULL);
    married = 0;
    gettingMarried= 0;
    totalbride=4;
    totalgroom=4;
                                                                 //////////////////////////////////

    pthread_create(&(reg_id[0]), NULL, &registar, NULL);
    pthread_create(&(reg_id[1]), NULL, &registar, NULL); // Creating registars
    pthread_create(&(exiter), NULL, &out, NULL); // 1 thread waiting for exit
    Creator(); // groom and bride creator function

    return 0;

}







