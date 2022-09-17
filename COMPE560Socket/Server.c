#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

struct message
{
char a ;
int b;
float c;
};

int main()
{
        struct message Before;
        struct message After;
        int socket_desc  , c , read_size;
        struct sockaddr_in server , client;
        char client_message[2000];
int client_sock[2];

        //Create socket
        socket_desc = socket(AF_INET , SOCK_STREAM , 0);
        if (socket_desc == -1)
        {
                printf("Could not create socket");
        }
        puts("Socket created");

        //Prepare the sockaddr_in structure
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons( 5023 );//specify port 5023 for connection

        //Bind
        if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
        {
                //print the error message
                perror("bind failed. Error");

                return 1;
        }
        puts("bind done");

        //Listen
        listen(socket_desc , 3);

        //Accept and incoming connection
        puts("Waiting for incoming connections...");
        c = sizeof(struct sockaddr_in);

        //accept connection from an incoming clients
       for(int i = 0; i<2; i++)
        {
         client_sock[i] = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
        printf("\nClient %d has connected\n", i);
        }
        if (client_sock[0] < 0)
        {
                perror("accept failed");
                return 1;
        }


        //Receive a message from client 0
         recv(client_sock[0] , &Before , sizeof(Before) , 0);
       //print message that was recieved from client 0
        printf("Recieved Char: %c Recieved int: %d Recieved Float: %f",Before.a,Before.b,Before.c);
        if(Before.a=='z'||Before.a=='Z')//change character with rollover support
        {
        After.a=Before.a - 25;//
        }
        else
        {
        After.a = Before.a +1;//add 1 if char is not rolled over
        }
        After.b =Before.b*2;//double integer
        After.c= Before.c + 1;//add 1 to float
        printf("\nSent Char: %c Sent int: %d Sent Float: %f\n",After.a,After.b,After.c);
        while( send(client_sock[1] , &After , sizeof(After) , 0)<0){}//send modified struct to client 1


        return 0;
}
