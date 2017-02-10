/*
 * template_utilityfunctions.c
 *
 *  Created on: Jan 25, 2017
 *      Author: Ashwini Shankar Patankar
 */

#include <stdio.h>
#include "utility_function.h"

#define BUFFER_SIZE 33
int main() {
	char buffer[BUFFER_SIZE];
	buffer[BUFFER_SIZE - 1] = '\0';


	Integer2Binary(5, buffer, BUFFER_SIZE - 1);

	printf("the bit string for 5 is %s\n", buffer);

	Integer2Binary(12, buffer, BUFFER_SIZE - 1);
	printf("the bit string for 12 is %s\n", buffer);

	Integer2Binary(123, buffer, BUFFER_SIZE - 1);
	printf("the bit string for 123 is %s\n", buffer);

	Integer2Binary(1234, buffer, BUFFER_SIZE - 1);
	printf("the bit string for 1234 is %s\n",buffer);

	Integer2Binary(12345, buffer, BUFFER_SIZE - 1);
	printf("the bit string for 12345 is %s\n",buffer);

	Integer2Binary(123456, buffer, BUFFER_SIZE - 1);
	printf("the bit string for 123456 is %s\n",buffer);

	Integer2Binary(1234567, buffer, BUFFER_SIZE - 1);
	printf("the bit string for 1234567 is %s\n",buffer);

	return 0;
}

