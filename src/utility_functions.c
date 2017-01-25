/*
 * utility_functioin.c
 *
 *  Created on: Jan 21, 2017
 *      Author: Ashwini Shankar Patankar
 */

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

