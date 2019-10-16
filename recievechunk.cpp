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
void*receive(void*);
struct sr
{
	vector<int>index;
	FILE*fp;
	int port;

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
	// empty file creation..............................................................

	int fsize,null_buff_size;
	fsize=3864;
	if(fsize<=512)
	{
	null_buff_size=fsize;
	}
	else
	{
	null_buff_size=512;
	}
	char buffer_null[null_buff_size];
	memset(buffer_null,'\0',null_buff_size);
	char buffer[512];
	FILE *fop=fopen("neww.txt.","wb+"); 
	if(fop<0)
	{
	perror("unable to open file");
	pthread_exit(NULL);


	}

	int n=fsize;
	while(n>0)
	{
	int minus;
	if(n<512)
	{
	null_buff_size=n;
	minus=fwrite(buffer_null,sizeof(char),null_buff_size,fop);
	memset(buffer_null,'\0',null_buff_size);
	}
	else
	{
	minus=fwrite(buffer_null,sizeof(char),null_buff_size,fop);
	memset(buffer_null,'\0',null_buff_size);
	}
	n=n-minus;
	}
	fseek(fop,0,SEEK_END);
	int file_size=ftell(fop);
	rewind(fop);
	cout<<"file_size"<<file_size<<endl;
	// upto here.......................................................................................

	for(int i=0;i<num_args;i++)
	{

	// args[i].fp=fp1;
	args[i].port=i;
	args[i].fp=fop;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&tids[i],&attr,&receive,&args[i]);


	}

	for(int i=0;i<num_args;i++)
	{

	pthread_join(tids[i],NULL);
	}
	
	
	fclose(fop);
	pthread_exit(NULL);
	pthread_mutex_destroy(&lock1); 

}


void*receive(void*arg)
{

	struct sr * sra=(struct sr*)arg;
	// cout<<"here"<<endl;
	int server_fd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in addr;
	addr.sin_family=AF_INET;
	int prt=1025+sra->port;
	addr.sin_port=htons(prt);
	addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	int len=sizeof(addr);
	bind(server_fd,(struct sockaddr*)&addr,sizeof(addr));
	listen(server_fd,0);
	cout<<"waiting"<<endl;
	int sockfd = accept( server_fd , (struct sockaddr *)&addr, (socklen_t*)&len);
	char buffer[512];

	// FILE*fp2=fopen("/home/himanshu/Desktop/osassign/file_trasfer/xyz.txt","wb+");
	// from here null file logic



	//upto here.


	// fclose(fp2);
	// rewind(fp1); 


	FILE*fp1=sra->fp;
	// fseek(fp1, 0 , SEEK_SET);

	int index[10];
	cout<<"beforefirstreceive"<<endl;
	recv(sockfd,index,sizeof(index),0);
	cout<<index[0]<<" "<<index[1]<<endl;


	// char first='A';
	// fwrite(&first,sizeof(char),sizeof(first),fp1);

	int i=0;
	int n;
	while(index[i]!=0)
	{

	n = recv( sockfd , buffer ,sizeof(buffer),0);
	// cout<<buffer<<endl;
	
    
    pthread_mutex_lock(&lock1); 
    int sk;
	sk=(index[i]-1)*512;
    rewind(fp1);
	fseek(fp1, sk , SEEK_SET);
	fwrite (buffer , sizeof (char), n, fp1);
	pthread_mutex_unlock(&lock1);

	memset ( buffer , '\0', 512);
	


	i++;
	}


	close(sockfd);
	close(server_fd);

	// fclose(fp1);








	pthread_exit(0);
}
