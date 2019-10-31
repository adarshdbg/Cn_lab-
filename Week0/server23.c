/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include<ctime>
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void chat(int newsockfd){
    int n=0,k=0;
    char buffer[256];
    while(true){
        k++;
        printf("%d\n",k);
        bzero(buffer,256);
        n=0;
         n = read(newsockfd,buffer,256);
         if (n < 0) error("ERROR reading from socket");
         // current date/time based on current system
       time_t now = time(0);
       // convert now to string form
       char *dt= ctime(&now);
         printf("From client:%s",buffer);
        // if msg contains "Exit" then server exit and chat ended. 
        if (strncmp("exit", buffer, 4) == 0) { 
            printf("Server Exit...\n"); 
            break; 
        } 
        else if (strncmp("time", buffer, 4) == 0) { 
            // printf("%s\n",dt);
            strcpy(buffer, dt);
        } 
        else {
            bzero(buffer, 256); 
            n = 0; 
            printf("Enter the message: "); 
            while ((buffer[n++] = getchar()) != '\n');
        }
        // copy server message in the buffer 
        n=write(newsockfd, buffer, sizeof(buffer)); 
         if (n < 0) error("ERROR writing to socket");
     }
}



int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
    chat(newsockfd);
     close(newsockfd);
     close(sockfd);
     return 0; 
}