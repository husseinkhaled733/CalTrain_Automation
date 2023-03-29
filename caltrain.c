//
// Created by exception on 25/03/23.
//
#include <pthread.h>
#include "caltrain.h"
#include <stdio.h>



void
station_init(struct station *station)
{
    pthread_cond_init(&(station->train_arrived), NULL);
    pthread_cond_init(&(station->passengers_seated), NULL);
    pthread_mutex_init(&(station->mutex), NULL);
    station->waiting_passengers = 0;
    station->enough_seats = 0;
    station->free_seats_on_train = 0;
    // FILL ME IN
}

void
station_load_train(struct station *station, int count)
{

    station->free_seats_on_train = count;
    pthread_mutex_lock(&(station->mutex));
    station->enough_seats = count;
    if (station->waiting_passengers != 0 && station->free_seats_on_train != 0) {
        pthread_cond_broadcast(&(station->train_arrived));
        pthread_cond_wait(&(station->passengers_seated), &(station->mutex));
    }
    pthread_mutex_unlock(&(station->mutex));
    // FILL ME IN
}

void
station_wait_for_train(struct station *station)
{
    pthread_mutex_lock(&(station->mutex));
    station->waiting_passengers++;
    do {
        pthread_cond_wait(&(station->train_arrived), &(station->mutex));
        station->enough_seats--;
    } while (station->enough_seats <0);
    pthread_mutex_unlock(&(station->mutex));
    // FILL ME IN
}

void
station_on_board(struct station *station)
{
    pthread_mutex_lock(&(station->mutex));
    if(station->waiting_passengers != 0 && station->free_seats_on_train != 0) {
        station->waiting_passengers--;
        station->free_seats_on_train--;
    }
    pthread_mutex_unlock(&(station->mutex));
    if(station->waiting_passengers == 0 || station->free_seats_on_train == 0) {
        pthread_cond_broadcast(&(station->passengers_seated));
    }
    // FILL ME IN
}