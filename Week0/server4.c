#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/time.h>
#include <arpa/inet.h> 
#include<errno.h>

#define PORT 8888
#define TRUE 1
#define FALSE 0
#define MAX_CLIENT 30
#define SIZE 1024


struct name{
	char name[25];
};
struct name arr[100];
int main(int argc,char *argv[]){
	if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
	int opt=TRUE;
	int master_socket,addrlen,new_socket,client_socket[MAX_CLIENT],
	activity,valread;
	int max_sd;
	struct sockaddr_in address;
	char buffer[SIZE];
	fd_set readfds;
	char message[]="Hello, you  are connected to server!\n Currently people connected are:\n";
	for(int i=0;i<MAX_CLIENT;++i){
		client_socket[i]=0;
	}
	master_socket=socket(AF_INET,SOCK_STREAM,0);
	if(master_socket<0){
		perror("socket failed");   
        exit(EXIT_FAILURE);   
	}
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=INADDR_ANY;
	address.sin_port=htons(atoi(argv[1]));
	if(bind(master_socket,(struct sockaddr *)&address,sizeof(address))<0){
		perror("socket failed");   
        exit(EXIT_FAILURE);  
	}
	printf("Listning to on port %d\n",htons(atoi(argv[1])));
	listen(master_socket,5);
	addrlen=sizeof(address);
	printf("Waitng for connection\n");
	while(TRUE){
		FD_ZERO(&readfds);
		FD_SET(master_socket,&readfds);
		for(int i=0;i<MAX_CLIENT;++i){
			int sd=client_socket[i];
			if(sd>0){
				FD_SET(sd,&readfds);
			}
			if(sd>max_sd)
				sd=max_sd;
		}
		activity=select(max_sd+1,&readfds,NULL,NULL,NULL);
		if ((activity < 0) && (errno!=EINTR))   
        {   
            printf("select error");   
        }
        if(FD_ISSET(master_socket,&readfds)){
        	strcpy(message,"Hello, you  are connected to server!\n Currently people connected are:\n");
        	new_socket=accept(master_socket,(struct sockaddr *)&address,(socklen_t *)&addrlen);
        	// printf("after\n");
        	if(new_socket<0){
        		perror("accept");
        		exit(EXIT_FAILURE);
        	}
        	printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));   
           
            //send new connection greeting message 
            char name[25];
            bzero(name,25);
            read(new_socket,name,25);
            for (int i = 0;i < MAX_CLIENT;i++)   
            {   
                //if position is empty  
                if( client_socket[i] != 0 )   
                {   
                	strcat(message,arr[i].name);
                	strcat(message,"\n"); 
                }   
            } 
            if( send(new_socket, message, strlen(message), 0) != strlen(message) )   
            {   
                perror("send");   
            }   
                 
            printf("Welcome message sent successfully\n");
            for (int i = 0;i < MAX_CLIENT;i++)   
            {   
                //if position is empty  
                if( client_socket[i] == 0 )   
                {   
                    client_socket[i] = new_socket;
                    struct name t;
                    strcpy(t.name,name);
                    arr[i]=t;
                    printf("Adding to list of sockets as %d\n" , i);   
                         
                    break;   
                }   
            } 
        }

        for (int i = 0; i < MAX_CLIENT; i++)   
        {   
            int sd = client_socket[i];   
            bzero(buffer,SIZE);
            if (FD_ISSET( sd , &readfds))   
            {   
                //Check if it was for closing , and also read the  
                //incoming message 
                valread = read( sd , buffer, 1024);
                if (valread== 0)   
                {   
                    //Somebody disconnected , get his details and print  
                    getpeername(sd , (struct sockaddr*)&address,(socklen_t*)&addrlen);   
                    printf("Host disconnected , ip %s , port %d \n" ,  
                          inet_ntoa(address.sin_addr) , ntohs(address.sin_port));   
                         
                    //Close the socket and mark as 0 in list for reuse  
                    close(sd);   
                    client_socket[i] = 0;   
                }   
                     
                //Echo back the message that came in  
                else 
                {   
                    //set the string terminating NULL byte on the end  
                    //of the data read  
                    // printf("IN ELSE\n");
                    buffer[valread] = '\0';   
                    send(sd , buffer , strlen(buffer) , 0 ); 
                    for(int j=0;j<MAX_CLIENT;++j){
                    	if(client_socket[j]!=0&&client_socket[j]!=master_socket&&client_socket[j]!=sd){
                    		// printf("%d\n",i);
                    		char temp[SIZE];
                    		strcpy(temp,arr[i].name);
                    		strcat(temp,buffer);
                    		write(client_socket[j], temp, strlen(temp) );
                    		// read(client_socket[j],buffer,strlen(buffer));
                    	}
                    }
     //                FD_ZERO(&readfds);
					// for(int i=0;i<MAX_CLIENT;++i){
					// 	int sd=client_socket[i];
					// 	if(sd>0){
					// 		FD_SET(sd,&readfds);
					// 	}
					// 	if(sd>max_sd)
					// 		sd=max_sd;
					// }
					// activity=select(max_sd+1,&readfds,NULL,NULL,NULL);
					// if ((activity < 0) && (errno!=EINTR))   
			  //       {   
			  //           printf("select error");   
			  //       }    
                }   
            }   
        }      
	}
}