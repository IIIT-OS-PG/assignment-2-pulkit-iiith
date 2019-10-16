#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<ctype.h>
#include<iostream>
#include<openssl/sha.h>

using namespace std;

void error(char * text)
{
    perror(text);
    exit(1);
}

int main(int argc, char* argv[])
{
    int socketfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buff[1000];
    if(argc < 3)
    {
        fprintf(stderr,"hostname or portno missing %s\n",argv[0]);
        exit(1);
    }
    
    portno=atoi(argv[2]);
    socketfd=socket(AF_INET,SOCK_STREAM,0);

    if(socketfd<0)
    {
        error("error in socket");
    }
    server = gethostbyname(argv[1]);

    if(server== NULL)
    {
        fprintf(stderr,"invalid host");
    }
     bzero((char *)&serv_addr,sizeof(serv_addr));

     serv_addr.sin_family = AF_INET;
     //serv_addr.sin_addr.s_addr=INADDR_ANY;
     bcopy((char *)server->h_addr_list[0],(char*)&serv_addr.sin_addr.s_addr,server->h_length);
     
      serv_addr.sin_port=htons(portno);

    if(connect(socketfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
    {
          error("ERROR in connect");
    }
    bzero(buff,sizeof(buff));


//file tranfer
    
    
    FILE *f;

    f = fopen("Post_MaloneWow.mp3","rb");
    fseek(f,0,SEEK_END);
    int size = ftell(f);
    rewind(f);

    unsigned char temp[512000];

    //int fd = fopen
 
 
 
 
   char c;

    f = fopen("Post_MaloneWow.mp3","r");
    if (f!=NULL)
    {
        while((c = getc(f)) != EOF)
        {
            strcat((char*)temp,&c);
        }
    }
    rewind(f);

    unsigned char temp1[INT16_MAX];



   SHA1(temp,strlen((char*)temp),temp1);
   cout<<temp1;


    send(socketfd,&size,sizeof(size),0);


    while((n = fread(buff,sizeof(char),sizeof(buff),f))>0 && size>0)
    {
        send(socketfd,buff,n,0);
        memset(buff,'\0',sizeof(buff));
        size= size-n;
    }

    fclose(f);
    close(socketfd);
    
  
  
  
  
  
  
  
  




















// code for chat:
 // while(1) 
    // {
    //     bzero(buff,sizeof(buff));
    //     fgets(buff,sizeof(buff),stdin);
    //     n = write(socketfd,buff,strlen(buff));
    //     if(n<0)
    //     {
    //         error("ERROR on write");
    //     }
    //     bzero(buff,sizeof(buff));
    //     n=read(socketfd,buff,sizeof(buff));
    //     if(n<0)
    //     {
    //         error("ERROR on read");
    //     }
    //     printf("SERVER: %s",buff);

    //     int i = strncmp("bye",buff,3);
    //     if(i == 0)
    //     {
    //         break;
    //     }
    // }
    // close(socketfd);
   
   
   
   
    return 0;

}