#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include<bits/stdc++.h>
using namespace std;

void*send(void*);
struct sr
{
	int index[10]={0,0,0,0,0,0,0,0,0,0};
	FILE*fp;
	int port;
	char**argv1;
	int argc1;

};
pthread_mutex_t lock1; 
int main()
{
 if (pthread_mutex_init(&lock1, NULL) != 0) 
	    { 
	        printf("\n mutex init has failed\n"); 
	        return 1; 
	    } 
int num_args=3;
pthread_t tids[num_args];
struct sr args[num_args];
FILE*fp1=fopen("file.txt","rb");
// args[0].index.push_back(1);
// args[0].index.push_back(2);
// args[1].index.push_back(3);
// args[1].index.push_back(4);
// args[2].index.push_back(5);
// args[2].index.push_back(6);
//  args[0].index[0]=1;
//  args[0].index[1]=1;
 args[0].index[1]=2;
//  args[1].index[0]=4;
 args[1].index[1]=1;
// args[2].index[0]=4;
// args[2].index[1]=4;
 //args[2].index[2]=4;
//args[2].index[3]=5;

//args[2].index[7]=4;



for(int i=0;i<num_args;i++)
{
//cout<<"for1"<<endl;
args[i].fp=fp1;
args[i].port=i;
// args[i].argv1=argv;
// args[i].argc1=argc;

pthread_attr_t attr;
pthread_attr_init(&attr);
pthread_create(&tids[i],&attr,&send,&args[i]);


}

for(int i=0;i<num_args;i++)
{

pthread_join(tids[i],NULL);

}
fclose(fp1);
pthread_exit(NULL);
pthread_mutex_destroy(&lock1); 


}




void*send(void*arg)
{
	// cout<<"here"<<endl;
struct sr * sra=(struct sr*)arg;
//cout<<sra->index[0]<<endl;
int n;
int sock_id=socket(AF_INET,SOCK_STREAM,0);
int prt=1025+sra->port;
struct sockaddr_in server_add;
server_add.sin_family=AF_INET;
server_add.sin_port=htons(prt);
server_add.sin_addr.s_addr=inet_addr("127.0.0.1");

int j=connect(sock_id,(struct sockaddr*)&server_add,sizeof(server_add));
if(j==0)
{
	cout<<"connected"<<endl;
}
else
{
	cout<<"error"<<endl;
}

// FILE*file_pointer=sra->fp;
// FILE*fp1=fopen("/home/himanshu/Desktop/osassign/file_trasfer/help.txt","rb");
// fseek(file_pointer,0,SEEK_END);

// int size=ftell(file_pointer);

// cout<<size<<endl;

// rewind(file_pointer);

cout<<"sendingnow"<<endl;

send(sock_id,sra->index,sizeof(sra->index),0);

char buffer[512];
// cout<<endl;
// size_t n= fread(buffer, 8, 3, file_pointer);
// printf("%s\n", buffer);
// cout<<n<<endl;
int i=0;
cout<<sra->index[0]<<" "<<sra->index[1]<<endl;
while(sra->index[i]!=0)
{
pthread_mutex_lock(&lock1); 
int sk;
rewind(sra->fp);
sk=(sra->index[i]-1)*512;
fseek(sra->fp, sk , SEEK_SET);
n=fread(buffer,1,sizeof(buffer),sra->fp);
pthread_mutex_unlock(&lock1);
cout<<buffer<<endl;
send(sock_id,buffer,n,0);
memset(buffer,'\0',512);


i++;
}







// fclose(fp1);
close(sock_id);


pthread_exit(0);

}
