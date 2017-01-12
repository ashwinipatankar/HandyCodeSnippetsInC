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
#include <netinet/in.h>
#include <netdb.h>



#define NUMBEROFCONNECTIONS 5
#define PORTNUMBER 5000

static void *fn_receiver(void *ptr) {
	int sock, bytes_recieved;
	char send_data[1024], recv_data[1024];
	struct hostent *host;
	struct sockaddr_in server_addr;

	host = gethostbyname("127.0.0.1");

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket");
		exit(1);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(5000);
	server_addr.sin_addr = *((struct in_addr *) host->h_addr);
	bzero(&(server_addr.sin_zero), 8);

	if (connect(sock, (struct sockaddr *) &server_addr, sizeof(struct sockaddr))
			== -1) {
		perror("Connect");
		exit(1);
	}

	while (1) {

		bytes_recieved = recv(sock, recv_data, 1024, 0);
		recv_data[bytes_recieved] = '\0';

		if (strcmp(recv_data, "q") == 0 || strcmp(recv_data, "Q") == 0) {
			close(sock);
			break;
		}

		else
			printf("\nRecieved data = %s ", recv_data);

		printf("\nSEND (q or Q to quit) : ");
		gets(send_data);

		if (strcmp(send_data, "q") != 0 && strcmp(send_data, "Q") != 0)
			send(sock, send_data, strlen(send_data), 0);

		else {
			send(sock, send_data, strlen(send_data), 0);
			close(sock);
			break;
		}

	}
	return NULL;
}


void __initSocketId(int *socket_id) {
	if ((*socket_id = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket");
		exit(1);
	}
}

void __initSocketConfiguration(struct sockaddr_in *socket_address) {

	socket_address->sin_family = AF_INET;
	socket_address->sin_port = htons(PORTNUMBER);
	socket_address->sin_addr.s_addr = INADDR_ANY;
	bzero(&(socket_address->sin_zero), 8);
}



void initTCPSocket(int *socket_id, struct sockaddr_in *socket_address) {

	__initSocketId(socket_id);

	__initSocketConfiguration(socket_address);


	if (bind(*socket_id, (struct sockaddr *)socket_address, sizeof(struct sockaddr))==-1) {
		perror("Unable to bind");
		exit(1);
	}

	if (listen(*socket_id, NUMBEROFCONNECTIONS)==-1) {
		perror("Listen");
		exit(1);
	}

	printf("TCP server waiting for client on port 5000");
	fflush(stdout);


}

static void *fn_transmitter(void *ptr) {
	int sk_transmitter, sk_receiver;

	int sock, connected, bytes_received, true=1;
	char send_data[1024], recv_data[1024];

	struct sockaddr_in server_addr, client_addr;
	int sin_size;

	initTCPSocket(&sock , &server_addr);

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

		}

		close (sock);
	}
	return NULL;
}


int main(void) {


	pthread_t th_receiver, th_transmitter;
	int return_thread_receiver, return_thread_transmitter;

	return_thread_transmitter  = pthread_create(&th_transmitter, NULL, fn_transmitter, NULL);
	sleep(1);
	return_thread_receiver  = pthread_create(&th_receiver, NULL, fn_receiver, NULL);


	pthread_join(th_receiver, NULL);
	pthread_join(th_transmitter, NULL);
	return 0;
}

