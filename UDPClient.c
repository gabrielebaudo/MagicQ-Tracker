/* Usage: write down port and address*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 6549
#define MAXLINE 1024
#define ADDRESS "192.168.1.176"

int s=0;
void handler();
// Driver code
int main() {
	int sockfd;
	char buffer[MAXLINE];
	char vett[200];
	struct sockaddr_in servaddr;

	float x = 2.5;
    float y = 5.7;
    float z = 8.9;
	signal(SIGINT, handler);

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	

	memset(&servaddr, 0, sizeof(servaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = inet_addr(ADDRESS);
	
     while(s==0){
		x++;
		sprintf(vett, "%.1f,%.1f,%.1f,1, Special", x, y, z);
        if(sendto(sockfd, (const char *)vett, strlen(vett), 0, (struct sockaddr *) &servaddr, sizeof(servaddr)) != strlen(vett)){
			printf("Sent different bytes number\n"); fflush(stdout);
		}
		usleep(30*1000); //Little delay (30 msecs) for declick
    }
	
	close(sockfd);
	return 0;
}

void handler(){
    s=1;
    printf("\nClient Interrupt"); fflush(stdout);
}
