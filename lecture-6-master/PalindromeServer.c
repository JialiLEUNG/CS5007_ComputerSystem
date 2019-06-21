/*
 * DateServer.c
 *
 *  @since 2018-08-07
 *  @author philip gust
 */
#include <stdbool.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

//#define PORT 9091
#define MAXBUF 128
#define MAXPALINBUF 128

/**
 * This program acts as a server that serves dates on request.
 *
 * @return EXIT_SUCCESS if successful
 */
int main(void) {

    // Creating internet socket stream file descriptor
    int listener_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    //
    if (listener_sock_fd == 0) { // if it failed (0)
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // my code here
    // take a port number as a program argument.
    printf("Enter a port number of the palindrome server: ");
    fflush(stdin);
    char buf[MAXBUF];
    if (fgets(buf, MAXBUF, stdin) == NULL) {
        perror("fgets");
        return EXIT_FAILURE;
    }

    unsigned short port = (unsigned short) atol(buf);

    // attach socket to port PORT
    struct sockaddr_in address; // ip address . in stands for internet.
    socklen_t addrlen = sizeof(address);
    // memset() is used to fill a block of memory with a particular value.
        // ptr ==> Starting address of memory to be filled
        // x   ==> Value to be filled
        // n   ==> Number of bytes to be filled starting from ptr to be filled
    // void *memset(void *ptr, int x, size_t n);
    // Note that ptr is a void pointer, so that we can pass any type of pointer to this function.
    memset(&address, 0, addrlen); // zero out.
    address.sin_family = AF_INET;  // address from internet
    address.sin_port = htons(port);   // port in network byte order
    address.sin_addr.s_addr = INADDR_ANY;  // bind to any address

    // bind host address to port
    // int bind(int sockfd, const struct sockaddr *addr, socklen_t_addrlen);
    // after creation of the socket, bind function binds the socket to the
    // address and port number specified in addre (custom data structur).
    if (bind(listener_sock_fd, (struct sockaddr *)&address, addrlen) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // listen.
    // set up queue for clients connections up to default
    // maximum pending socket connections (usually 128) -- SOMAXCONN
    if (listen(listener_sock_fd, SOMAXCONN) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (true) {
        // accept client connection
    	fprintf(stderr, "connection?\n");
        // listener_sock_fd is the listen socket.
		int socket_fd = accept(listener_sock_fd, (struct sockaddr *)&address, &addrlen);
		// create accept socket.
		if (socket_fd < 0) {
			perror("accept");
			continue;
		}
        fprintf(stderr, "got one! %d\n", ntohs(address.sin_port));

		// create a buffer for the user palindrome input.
        char palinBuff[MAXPALINBUF];
        memset(palinBuff, 0, MAXPALINBUF); // zero out.

        if (read(socket_fd, palinBuff, MAXPALINBUF/2) < 0){
            perror("read");
        } else {
            printf("Original Palindrome: %s\n", palinBuff);
        }

        // palindrome function
        size_t len = strlen(palinBuff);
        if (len > 1 && palinBuff[len-2] == '\r') palinBuff[len-2] = 0;
        if (len > 0 && palinBuff[len-1] == '\n') palinBuff[len-1] = 0;
        //
        len = strlen(palinBuff);

        for (int i = len - 1, j = len; i >=0 &&  j < MAXPALINBUF; i--, j++){
            palinBuff[j] = palinBuff[i];
        }

		// send time
		if (write(socket_fd , palinBuff , strlen(palinBuff)+1) < 0) {
			perror("send");
		}
		// close socket to complete write operation
		close(socket_fd);
    }

    // close server socket
    close(listener_sock_fd);
    return 0;
}

