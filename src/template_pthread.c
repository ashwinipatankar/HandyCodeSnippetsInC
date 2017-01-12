/*
 * template_pthread.c
 *
 *  Created on: Jan 12, 2017
 *      Author: Ashwini Shankar Patankar
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static void *execute_thread1(void *ptr) {
	printf("Hello world from thread 1\n");
	return NULL;

}

static void *execute_thread2(void *ptr) {
	printf("Hello World from thread 2\n");
	return NULL;
}


int main(void) {

	pthread_t thread1, thread2;
	int return_value_thread1, return_value_thread2;

	return_value_thread1  = pthread_create(&thread1, NULL, execute_thread1, NULL);
	return_value_thread2  = pthread_create(&thread2, NULL, execute_thread2, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	return 0;
}
