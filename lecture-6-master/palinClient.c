/*
 * DateClient.c
 *
 *  Created on: Aug 7, 2018
 *      Author: philip gust
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 9091
#define MAXBUF 128

int main(int argc, char const *argv[]) {
    printf("Enter IP Address of a date server on port %d: ", PORT);
    fflush(stdin);
    char buf[MAXBUF];
    if (fgets(buf, MAXBUF, stdin) == NULL) {
        perror("fgets");
        return EXIT_FAILURE;
    }

    // trim newline: “\r\n” or “\n”
    size_t len = strlen(buf);
    if (len > 1 && buf[len-2] == '\r') buf[len-2] = 0;
    if (len > 0 && buf[len-1] == '\n') buf[len-1] = 0;

    int sock_fd = 0;
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return EXIT_FAILURE;
    }

    struct sockaddr_in address;
    const socklen_t addrlen = sizeof(address);
    memset(&address, 0, addrlen);
    address.sin_family = AF_INET;  // address from internet
    address.sin_port = htons(PORT);   // port in network byte order

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, buf, &address.sin_addr) <= 0) {
        perror("inet_pton");
        return -1;
    }

    if (connect(sock_fd, (struct sockaddr *)&address, addrlen) < 0) {
        perror("connect");
        return -1;
    }
    if (read(sock_fd, buf, MAXBUF) < 0) {
        perror("read");
    } else {
        printf("Time: %s\n", buf);
    }

    close(sock_fd);
    return 0;
}
