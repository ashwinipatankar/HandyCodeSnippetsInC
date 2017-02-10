/*
 * utility_functioin.c
 *
 *  Created on: Jan 21, 2017
 *      Author: Ashwini Shankar Patankar
 */

#include <stdio.h>
#include "utility_function.h"

int CharacterToInteger(char input) {
	int out = 0;

	char key[22] = "0123456789abcdefABCDEF";
	int value[22] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 10,
			11, 12, 13, 14, 15 };
	int index = 0;
	for (index = 0; index < 22; index++) {
		if (input == key[index]) {
			out = value[index];
			break;
		}
	}
	return out;
}

/*
 * Source http://stackoverflow.com/questions/1024389/print-an-int-in-binary-representation-using-c
 * TODO Handle unsigned/signed cases
 */
char *Integer2Binary(int input_number, char *buffer, int buffer_size) {



	buffer += (buffer_size -1);

	for (int i = 31; i >= 0; i--) {
		*buffer-- = (input_number & 1) + '0';
		input_number >>=1;
	}

	return buffer;
}

