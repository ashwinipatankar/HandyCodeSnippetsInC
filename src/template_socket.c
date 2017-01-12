/*
 * template_socket.c
 *
 *  Created on: Jan 12, 2017
 *      Author: Ashwini Shankar Patankar
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


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

#define PORTNUMBER 5000
void initTCPSocket(int *socket_id, struct sockaddr_in *socket_address) {

	if ((*socket_id = socket(AF_INET, SOCK_STREAM, 0)) == -1 ) {
		perror("Socket");
		exit(1);
	}

	socket_address->sin_family = AF_INET;
	socket_address->sin_port = htons(PORTNUMBER);
	socket_address->sin_addr.s_addr = INADDR_ANY;
	bzero(&(socket_address->sin_zero), 8);
}

int main(void) {


	pthread_t th_receiver, th_transmitter;
	int return_thread_receiver, return_thread_transmitter;
	int sk_transmitter, sk_receiver;

//	initTCPSocket(&sk_tra¿nsmitter);
	int sock, connected, bytes_received, true=1;
	char send_data[1024], recv_data[1024];

	struct sockaddr_in server_addr, client_addr;
	int sin_size;

	initTCPSocket(&sock , &server_addr);
#if 0
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket");
		exit(1);
	}
#endif

//	server_addr.sin_family = AF_INET;
//	server_addr.sin_port = htons(5000);
//	server_addr.sin_addr.s_addr = INADDR_ANY;
//	bzero(&(server_addr.sin_zero), 8);

	if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))==-1) {
		perror("Unable to bind");
		exit(1);
	}

	if (listen(sock, 5)==-1) {
		perror("Listen");
		exit(1);
	}

	printf("TCP server waiting for client on port 5000");
	fflush(stdout);

	while (1) {
		sin_size = sizeof(struct sockaddr_in);
		connected  = accept(sock, (struct sockaddr *)&client_addr, &sin_size);

		printf("\nI got a connection from (%s, %d)", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

		while (1) {
			printf("\nSEND (q or Q to quit): ");
			gets(send_data);

			if (strcmp(send_data, "q")==0 || strcmp(send_data, "Q")==0) {
				send(connected, send_data, strlen(send_data), 0);
				close(connected);
				break;
			}
			else {
				send(connected, send_data, strlen(send_data), 0);
			}

			bytes_received = recv(connected, recv_data, 1024, 0);

			recv_data[bytes_received]='\0';

			if (strcmp(recv_data, "q") == 0 || strcmp(recv_data, "Q")==0) {
				close (connected);
				break;
			}
			else {
				printf("\nRECEIVED DATA = %s", recv_data);
				fflush(stdout);
			}
		}

		close (sock);
	}
	return_thread_receiver  = pthread_create(&th_receiver, NULL, fn_receiver, NULL);
	return_thread_transmitter  = pthread_create(&th_transmitter, NULL, fn_transmitter, NULL);

	pthread_join(th_receiver, NULL);
	pthread_join(th_transmitter, NULL);
	return 0;
}

