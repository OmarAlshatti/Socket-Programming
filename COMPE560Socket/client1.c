#include <stdio.h>      
#include <string.h>     
#include <sys/socket.h>
#include <arpa/inet.h>  
#include <unistd.h>
struct message
{
char a ;
int b;
float c;
};
struct message1
{
char a ;
int b;
float c;
};



int main()
{
        struct message1 m1;

        char t[100];
        int sock;
        struct sockaddr_in server;
        char message[1000] , server_reply[2000];

        //Create socket
        sock = socket(AF_INET , SOCK_STREAM , 0);
        if (sock == -1)
        {
                printf("Could not create socket");
        }
        puts("\nSocket created");

        server.sin_addr.s_addr = inet_addr("130.191.166.3");
        server.sin_family = AF_INET;
        server.sin_port = htons( 5023);

        //Connect to remote server
        if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
        {
                perror("connect failed. Error");
                return 1;
        }
  puts("Connected\n");







                         
            

		//recieve struct and store in local struct
                while(recv(sock , &m1 , sizeof(m1) , 0)<0){}

                 printf("Recieved Char: %c Recieved int: %d Recieved Float: 	  %f\n",m1.a,m1.b,m1.c);// PRINT OUTPUT


        close(sock); //close sock and terminate procceses on server



}

