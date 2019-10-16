#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<iostream>
#include<openssl/sha.h>
#include<pthread.h>
#include<netdb.h>
#include<ctype.h>
#include<iostream>
using namespace std;


void *serverthread(void* port);


void error(char * text)
{
    perror(text);
    exit(1);
}






void *sendfile(void* newfd1)
{
   // char *argv[2];
    int sockfd, portno,n;
    char buff[1000];
    int newfd = *((int*)newfd1);
    struct sockaddr_in serv_addr, cli_addr;
   // socklen_t clilen;
     // cout<<11;
    // sockfd=socket(AF_INET,SOCK_STREAM,0);
    // if(sockfd < 0)
    // {
    //     error("ERROR");
    // }
     char temp[255];
 recv(newfd,&temp,sizeof(temp),0);
   
    FILE *fp;
    fp = fopen(temp,"r");
   
   
    if(fp==NULL)
    {
    cout<<"file not present";
    exit(1);
    }

    fp = fopen(temp,"rb");
    fseek(fp,0,SEEK_END);
    int size = ftell(fp);
    rewind(fp);

    send(newfd,&size,sizeof(size),0);


    while((n = fread(buff,sizeof(char),sizeof(buff),fp))>0 && size>0)
    {
        send(newfd,buff,n,0);
        memset(buff,'\0',sizeof(buff));
        size= size-n;
    }

    close(newfd);
    close(sockfd);
    return 0;
}


void *serverthread(void* port)
{


    int sockfd, newfd, portno,n;
    char buff[1000];
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd < 0)
    {
        error("ERROR");
    }
    
    bzero((char*)&serv_addr,sizeof(serv_addr));
    
    portno=atoi((char*)port);

    //cout<<portno;

    serv_addr.sin_family= AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd,(struct sockaddr*) &serv_addr,sizeof(serv_addr))<0)
    {
        error("ERROR in bind");
    }

    listen(sockfd,5);
    
    clilen = sizeof(cli_addr);


    while(1)
    {
      cout<<12<<endl;
    newfd=accept(sockfd,(struct sockaddr*) &cli_addr,&clilen);
    
        if(newfd<0)
       {
        error("ERROR on accept");
       }
       pthread_t newthread;
       pthread_create(&newthread,NULL, sendfile ,(void*) &newfd);
       pthread_join(newthread,NULL);

    }
}





void download_file(int port,char filename[])
{


cout<<8778<<endl;
    int socketfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buff[1000];
    // if(argc < 4)
    // {
    //     fprintf(stderr,"hostname or portno missing %s\n",argv[0]);
    //     exit(1);
    // }
    
    portno=port;
    socketfd=socket(AF_INET,SOCK_STREAM,0);

    if(socketfd<0)
    {
        error("error in socket");
    }
    server = gethostbyname("127.0.0.1");

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
    char tempz[100];
    strcpy(tempz,filename);
    cout<<tempz<<endl;
    cout<<12345<<endl;



    send(socketfd,tempz,sizeof(tempz),0);
    cout<<9876<<endl;


    f = fopen("new.mp3","wb");
    int file_size;
    recv(socketfd, &file_size,sizeof(file_size),0);
      cout<<file_size<<endl;

     while ((n = recv(socketfd,buff,sizeof(buff),0))>0 && file_size > 0)
    {
        cout<<n<<endl;
        fwrite(buff,sizeof(char),n,f);
        fflush(f);
        memset(buff,'\0',sizeof(buff));
        file_size =file_size - n;
    }
 












}

int main(int argc, char* argv[])
{


    pthread_t newthread1;
    pthread_create(&newthread1,NULL, serverthread ,(void*) argv[3]);
   // pthread_join(newthread1,NULL);
//    cout<<66666;



    int socketfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buff[1000];
    if(argc < 4)
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
    int x,y;
    while(1)
    {
    cout<<"please enter choice"<<endl;
    cout<<"1. new user"<<endl;
    cout<<"2. old user"<<endl;
    cin>>x;
    if(x==1)
    {
        send(socketfd,"create",6,0);
        //string s1,s2;
        char b[100],aa[100];
        cout<<"enter username"<<endl;
        cin>>b;
       // cout<<1234<<endl;
        send(socketfd,b,sizeof(b),0);
        cout<<123<<endl;
        bzero(b,sizeof(b));
        cout<<"enter password"<<endl;
        cin>>aa;
        send(socketfd,aa,sizeof(aa),0);
        bzero(aa,sizeof(aa));
    }
    else if(x==2)
    {
        send(socketfd,"login",5,0);
        char b1[100],aa1[100];
        cout<<"please login"<<endl;
        cout<<"enter username"<<endl;
        cin>>b1;
        send(socketfd,b1,sizeof(b1),0);
        bzero(b1,sizeof(b1));
        cout<<"enter password"<<endl;
        cin>>aa1;
        send(socketfd,aa1,sizeof(aa1),0);
        bzero(aa1,sizeof(aa1));


        
        recv(socketfd,b1,sizeof(b1),0);
        int j = strncmp("done",b1,4);
        bzero(b1,sizeof(b1));
        if(j == 0)
        {
            cout<<"success"<<endl;
            cout<<"please enter choice"<<endl;
            cout<<"3. upload file"<<endl;
            cout<<"4. download file"<<endl;
            cin>>y;
        if(y==3)
        {
        send(socketfd,"upload_file",11,0);
        //string s1,s2;
        char b2[100],aa2[100];
        cout<<"enter filename"<<endl;
        cin>>b2;
        //cout<<1234<<endl;
        send(socketfd,b2,sizeof(b2),0);
        //cout<<123<<endl;
        bzero(b2,sizeof(b2));
        cout<<"enter port"<<endl;
        cin>>aa2;
        send(socketfd,aa2,sizeof(aa2),0);
        } 
        else if(y==4)
        {
            send(socketfd,"download_file",13,0);
            char b3[100],aa3[100];
            cout<<"enter filename"<<endl;
            cin>>b3;
            send(socketfd,b3,sizeof(b3),0);
            //bzero(b3,sizeof(b3));
             
             
             
            recv(socketfd,aa3,sizeof(aa3),0);  
            int j1 = strncmp("done123",aa3,7);
            char zx[100];
            bzero(zx,sizeof(zx));
            if(j1==0)
            {
                cout<<"file present"<<endl;
                int var=0;
                recv(socketfd,zx,sizeof(zx),0);
                cout<<zx<<endl;
                sscanf(zx, "%d", &var);
                cout<<"port_is"<<" "<<var<<endl;
                cout<<var<<endl;
                download_file(var,b3);

            }
            else
            {
                cout<<"Oops...!!!";
            }

        }  













        }
    }
    else break;
    
    
    }





















//     bzero(buff,sizeof(buff));
//     //file tranfer
    
    
//     FILE *f;
//     char temp[255]= "new.txt";



//     send(socketfd,temp,sizeof(temp),0);


//     f = fopen("file.txt","wb");
//     int file_size;
//     recv(socketfd, &file_size,sizeof(file_size),0);
//       cout<<file_size<<endl;

//      while ((n = recv(socketfd,buff,sizeof(buff),0))>0 && file_size > 0)
//     {
//         cout<<n<<endl;
//         fwrite(buff,sizeof(char),n,f);
//         fflush(f);
//         memset(buff,'\0',sizeof(buff));
//         file_size =file_size - n;
//     }

//     pthread_join(newthread1,NULL);

//     fclose(f);
    close(socketfd);
     return 0;
 }
