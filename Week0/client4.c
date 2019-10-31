#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include<time.h>
#include<errno.h>
#include <arpa/inet.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

char name[25];

void send_name(int sockfd){
    printf("Enter your name\n");
    scanf("%s",name);
    int len=0;
    for(len=0;name[len]!='\0';++len){}
    name[len++]=':';
    name[len++]=' ';
    name[len++]='\0';
    int n = write(sockfd,name,strlen(name));
     if (n < 0) 
        error("ERROR writing to socket");

}

void chat(int sockfd){
    printf("Connected to server!\n");
    send_name(sockfd);
    char buffer[256];
    int n=0;
    fd_set readfds;
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 10000;
    FD_ZERO(&readfds);
    FD_SET(sockfd,&readfds);
    while(true){
        FD_ZERO(&readfds);
        FD_SET(sockfd,&readfds); 
        int activity=select(sockfd+1,&readfds,NULL,NULL,&timeout);
        // printf("After select\n");
        if(activity==-1){
            perror("select"); /* an error accured */
        }
        if(activity!=0){
            bzero(buffer,256);
            read( sockfd, buffer, 256 );
            printf("%s\n",buffer);
            if ((strncmp(buffer, "exit", 4)) == 0) { 
                printf("Client Exit...\n"); 
                break; 
            }
        }
        else{
            bzero(buffer,256);
            printf("No incoming message!\n");
            printf("1.Enter message\n2.Again Check for incoming messages\n");
            int opt;
            scanf("%d%*c",&opt);
            if(opt==1){
                // fflush(stdin);
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
                read( sockfd, buffer, 256 );
                printf("From server:%s\n",buffer);
                if ((strncmp(buffer, "exit", 4)) == 0) { 
                printf("Client Exit...\n"); 
                break;
                }
            }
        } 
    }
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;


    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    }
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    chat(sockfd);
    close(sockfd);
    return 0;
}
