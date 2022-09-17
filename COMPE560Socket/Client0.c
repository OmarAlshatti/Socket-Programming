#include <stdio.h>      //printf
#include <string.h>     //strlen
#include <sys/socket.h> //socket
#include <arpa/inet.h>  //inet_addr
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
        char d; int e;float f;
        printf("Enter Chararcter: ");
scanf("%c",&d);
printf("\nEnter Integer: ");
scanf("%d",&e);
printf("\nEnter Floating Number: ");
scanf("%f",&f);
        struct message m ={.a = d,.b =e,.c=f};
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
      //specify port and IP address
        server.sin_addr.s_addr = inet_addr("130.191.166.3");
        server.sin_family = AF_INET;
        server.sin_port = htons( 5023 );

        //Connect to remote server
        if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
        {
                perror("connect failed. Error");
                return 1;
        }

        puts("Connected\n");







                          //Send some data
                if( send(sock , &m , sizeof(message) , 0) < 0)
                {

                        return 1;
                }


                recv(sock , &m1 , sizeof(m1) , 0);
}
