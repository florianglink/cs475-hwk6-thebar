/*
 * globals.h
 *
 *  Created on: Dec 26, 2015
 *      Author: dchiu
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

int num_threads;	// number of customer threads
int now_serving;	// customer's ID who is being served
int num_served;     // keep track of how many customers have been served so threads can be
                    // reaped right after last costumer leaves the bar

//TODO - declare some semaphores
sem_t* bar_open;
sem_t* order_placed;
sem_t* order_ready;
sem_t* payment_received;
sem_t* all_served;

//Struct to hold thread customer thread number
typedef struct
{
    int tid;
} thread_args;

#endif /* GLOBALS_H_ */
