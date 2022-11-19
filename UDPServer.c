/* USAGE: Write down your port and address, than use ctrl+c to interrupt code */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>

#define PORT 6549
#define MAXLINE 1024
#define ADDRESS "192.168.1.244"

void handler();

int s=0;

int main() {
	int sockfd;
	char buffer[MAXLINE];
	char *hello = "Hello from server";
	struct sockaddr_in servaddr, cliaddr;
    int tr=1, len, n;
	
    signal(SIGINT, handler);

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
    
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4 Domain
	servaddr.sin_addr.s_addr = inet_addr(ADDRESS);
	servaddr.sin_port = htons(PORT);

    setsockopt(sockfd,SOL_SOCKET, SO_REUSEADDR, &tr, sizeof(int));
	
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	len = sizeof(cliaddr); //len is value/resuslt

    while(s==0){
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, (socklen_t *)&len);
	    buffer[n] = '\0';
	    printf("Client %s: %s\n", inet_ntoa(cliaddr.sin_addr), buffer);
    }
	printf("\n\nExit..."); fflush(stdout);
    close(sockfd);
    

	return 0;
}

void handler(){
    s=1;
    printf("\nServer Interrupt"); fflush(stdout);
}
