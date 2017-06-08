/*
 ============================================================================
 Name        : socket_server.c
 Author      : ibsz
 Version     : v 1.0
 Copyright   : Your copyright notice
 Description : Socket communication try
 Origin		 : http://www.thegeekstuff.com/2011/12/c-socket-programming/?utm_source=feedburner
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/types.h>

int local_port = 5000;

int main(void) {

	/**
	 * listenfd is file descriptor for listening socket
	 * connfd is file descriptor for ???
	 */
	int listenfd = 0, connfd = 0;
	struct sockaddr_in serv_addr;

	char sendBuff[1025];
	time_t ticks;
	/**
	 * AF_INET means "IP protocol family."
	 * SOCK_STREAM means "Sequenced, reliable, connection-based byte streams."
	 * socket() creates a file descriptor for the socket new socket
	 */
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd == -1){
		printf("could not create file descriptor\n");
		return -1;
	}
	memset(&serv_addr, '0', sizeof(serv_addr));
	memset(sendBuff, '0', sizeof(sendBuff));

	/**
	 * INADDR_ANY means "Address to accept any incoming messages."
	 * serv_addr is host/port/connection type configuration
	 */
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(local_port);

	/**
	 * Give the socket FD the local address ADDR (which is LEN bytes long).
	 */
	bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	/**
	 * Prepare to accept connections on socket FD.
   	 * N connection requests will be queued before further requests are refused.
     * Returns 0 on success, -1 for errors.
	 */
	if(listen(listenfd, 10) == -1){
		printf("could not start listening on local socket\n");
		return -1;
	}

	printf("start");
	/**
	 * endless listening loop
	 */
	while(1)
	{
		/**
		 * Await a connection on listenfd and opens a new socket connection to communicate with
		 * result is the file descriptor to the new connection
		 */
		connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);


		/**
		 * if connection arrives, get current time stamp and send it back
		 */
		ticks = time(NULL);
		snprintf(sendBuff, sizeof(sendBuff), "time: %.24s\r\n", ctime(&ticks));
		write(connfd, sendBuff, strlen(sendBuff));
		close(connfd);
		sleep(1);
		printf(".");
	 }

	puts("press any key..."); /* prints press any key... */
	return EXIT_SUCCESS;
}
