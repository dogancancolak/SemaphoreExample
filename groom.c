//
// Created by root on 11/28/16.
//

#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "global.h"
#include "groom.h"


void Groom(){
    sleep(1);
    sem_wait(&bridesem);// decrements herself
    sem_wait(&groomsem);// if there is at least one groom decrements groom
    sem_wait(&couple);// if there is at least 1 registar
    sem_post(&registsem);// signals registar
    pthread_mutex_lock(&groomLock); // Just dies
}