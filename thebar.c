/*
 * TheBar.c
 *
 *  Created on: Dec 26, 2015
 *      Author: dchiu
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include "globals.h"
#include "customer.h"
#include "bartender.h"

void printBanner();
void init();
void cleanup();

/**
 * Main function
 */
int main(int argc, char **argv)
{
	num_threads = atoi(argv[1]);
	num_served = 0;
	printBanner();
	init(); // initialize semaphores

	//Create bartender thread
	pthread_t bartender_t;
	pthread_create(&bartender_t, NULL, bartender, NULL);

	//Create customer threads
	pthread_t threads[num_threads];
	thread_args args[num_threads];
	for(int i=0; i<num_threads; i++){
		args[i].tid = i;
		pthread_create(&threads[i], NULL, customer, &args[i]);
	}

	sem_wait(all_served); //make sure all customer threads have been served before joining
	for(int i=0; i<num_threads; i++) {
		pthread_join(threads[i], NULL);
	}

	cleanup(); // cleanup and destroy semaphores
	return 0;
}

/**
 * Prints the activity banner.
 * Do not touch.
 */
void printBanner()
{
	printf("Customer:\t\t\t\t\t\t\t\t\t\t| Employee:\n");
	printf("Traveling\tArrived\t\tOrdering\tBrowsing\tAt Register\tLeaving");
	printf("\t| Waiting\tMixing Drinks\tAt Register\tPayment Recv\n");
	printf("----------------------------------------------------------------------------------------+");
	printf("-----------------------------------------------------------\n");
}

/**
 * Create and initialize semaphores
 */
void init()
{
	sem_unlink("/bar_open");
	sem_unlink("/order_placed");
	sem_unlink("/order_ready");
	sem_unlink("/payment_received");
	sem_unlink("all_served");

	bar_open = sem_open("/bar_open", O_CREAT, 0600, 1);
	order_placed = sem_open("/order_placed", O_CREAT, 0600, 0);
	order_ready = sem_open("/order_ready", O_CREAT, 0600, 0);
	payment_received = sem_open("/payment_received", O_CREAT, 0600, 0);
	all_served = sem_open("/all_served", O_CREAT, 0600, 0);
}

/**
 * Cleanup and destroy semaphores
 */
void cleanup()
{
	sem_close(bar_open);
	sem_close(order_placed);
	sem_close(order_ready);
	sem_close(payment_received);
	sem_close(all_served);

	sem_unlink("/bar_open");
	sem_unlink("/order_placed");
	sem_unlink("/order_ready");
	sem_unlink("/payment_received");
	sem_unlink("/all_served");
}
