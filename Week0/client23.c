#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

void chat(int sockfd){
    printf("Connected to server!\n");
    char buffer[256];
    int n=0,k=0;
    bzero(buffer,256);
    n = read(sockfd,buffer,256);
    if(n!=0)
        printf("From server:%s\n",buffer);
    while(true){
         k++;
        printf("%d\n",k);
        bzero(buffer,256);
        printf("Enter the message: "); 
        n = 0; 
        while ((buffer[n++] = getchar()) != '\n');
            // printf("%s\n",buffer);
        n = write(sockfd,buffer,strlen(buffer));
        if (n < 0) 
             error("ERROR writing to socket");
         if ((strncmp(buffer, "exit", 4)) == 0) { 
            printf("Client Exit...\n"); 
            break; 
        } 
        bzero(buffer,256);
        n = read(sockfd,buffer,256);
        if (n < 0) 
             error("ERROR reading from socket");
        printf("From server:%s\n",buffer);
        if ((strncmp(buffer, "exit", 4)) == 0) { 
            printf("Client Exit...\n"); 
            break; 
        } 
    }
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;


    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    chat(sockfd);
    close(sockfd);
    return 0;
}
