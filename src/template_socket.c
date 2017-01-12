/*
 * template_socket.c
 *
 *  Created on: Jan 12, 2017
 *      Author: Ashwini Shankar Patankar
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


static void *fn_receiver(void *ptr) {
	printf("Hello world from thread 1\n");
	return NULL;

}

static void fetchUserInput(int *user_input) {
	printf("enter any number: ");
	scanf("%d", user_input);

}

static void *fn_transmitter(void *ptr) {
	int user_input;
	fetchUserInput(&user_input);
	printf("You entered %d\n", user_input);
	return NULL;
}


int main(void) {

	pthread_t th_receiver, th_transmitter;
	int return_thread_receiver, return_thread_transmitter;

	return_thread_receiver  = pthread_create(&th_receiver, NULL, fn_receiver, NULL);
	return_thread_transmitter  = pthread_create(&th_transmitter, NULL, fn_transmitter, NULL);

	pthread_join(th_receiver, NULL);
	pthread_join(th_transmitter, NULL);
	return 0;
}

