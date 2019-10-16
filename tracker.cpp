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
#include<bits/stdc++.h>
using namespace std;

    map<string,string>user;
    map<string, string>::iterator itr;
    map<string,int>user1;
    map<string,int>::iterator itr1;

int ly=0;

void error(char* text);


void *multiple_server(void* new_fd)
{
     cout<<1234<<endl;

    int sockfd, newfd, portno,n;
    char buff[1000];
    // struct sockaddr_in serv_addr, cli_addr;
    // socklen_t clilen;

    // sockfd=socket(AF_INET,SOCK_STREAM,0);
    // if(sockfd < 0)
    // {
    //     error("ERROR");
    // }
    
    // bzero((char*)&serv_addr,sizeof(serv_addr));
    
    // portno=ly;

    // serv_addr.sin_family= AF_INET;
    // serv_addr.sin_addr.s_addr = INADDR_ANY;
    // serv_addr.sin_port = htons(portno);

    // if (bind(sockfd,(struct sockaddr*) &serv_addr,sizeof(serv_addr))<0)
    // {
    //     error("ERROR in bind");
    // }

    // listen(sockfd,5);
    
   // clilen = sizeof(cli_addr);
   // cout<<767<<endl;
  // cout<<new_fd<<endl;
   int *lk=(int*)new_fd;
   newfd=*lk;
    cout<<newfd<<endl;
    //newfd=(char*)new_fd
   // cout<<7673<<endl;



    FILE *fp;
    char l[100];
    recv(newfd,&l,sizeof(l),0);
    cout<<98765;
    int i = strncmp("cr",l,2);
    int j = strncmp("l",l,1);
    bzero(l,sizeof(l));
    if(i == 0)
    {
    char temp[255],t[123];
    recv(newfd,&temp,sizeof(temp),0);
    recv(newfd,&t,sizeof(t),0);
    user.insert(pair<string,string>(temp,t));
    cout<<endl;

     for (itr = user.begin(); itr != user.end(); ++itr) { 
        cout << endl << itr->first 
             << endl << itr->second << '\n'; 
    } 

    cout<<"user created"<<endl;
    }
    else
    {
       // cout<<011<<endl;
  //  int j = strncmp("c",l,1);
    if(j == 0)
    {
       // cout<<9<<endl;
    char temp1[255],t1[123];
    recv(newfd,&temp1,sizeof(temp1),0);
   // cout<<1234<<endl;
    recv(newfd,&t1,sizeof(t1),0);
    //cout<<123<<endl;

    itr = user.find(temp1);
  //  cout<<12300<<endl;

    if(itr == user.end())
    {
        cout<<"user not found"<<endl;
        send(newfd,"n",1,0);
    }
    else 
    {
        if(itr->second == t1)
        {
            cout<<"login successfull"<<endl;
            send(newfd,"done",4,0);
            //cout<<99<<endl;
            char l1[100];
            recv(newfd,&l1,sizeof(l1),0);
            //cout<<991<<endl;
            int i1 = strncmp("upload_file",l1,11);
            //cout<<992<<endl;
            int j1 = strncmp("download_file",l1,13);
            //cout<<993<<endl;
            if(i1 == 0)
            {
                //cout<<994<<endl;
                char temp2[255],t2[123];
                recv(newfd,&temp2,sizeof(temp2),0);
                recv(newfd,&t2,sizeof(t2),0);
                int x1;
                sscanf(t2, "%d", &x1);
                //cout<<x1<<endl;
                user1.insert(pair<string,int>(temp2,x1));
                cout<<endl;

                for (itr1 = user1.begin(); itr1 != user1.end(); ++itr1) { 
                cout << endl << itr1->first 
                    << endl << itr1->second << '\n'; 
    }
            }

             else
            {
                cout<<89<<endl;
                //  int j = strncmp("c",l,1);
                if(j1 == 0)
                {
                 cout<<9<<endl;
                char temp3[255],t3[123];
                bzero(temp3,sizeof(temp3));
                recv(newfd,&temp3,sizeof(temp3),0);
                 cout<<1234<<endl;
                // recv(newfd,&t3,sizeof(t3),0);
                // cout<<123<<endl;

                itr1 = user1.find(temp3);
                bzero(temp3,sizeof(temp3));

                if(itr1 == user1.end())
                {
                    cout<<"file not found"<<endl;
                    send(newfd,"n",1,0);
                }
                else
                {
                    cout<<"file present"<<endl;
                    send(newfd,"done123",7,0);
                    char jkl[100];
                    bzero(jkl,sizeof(jkl));
                    string s = to_string(itr1->second);
                    strcpy(jkl, s.c_str());
                    send(newfd,jkl,sizeof(jkl),0);
                    cout<<jkl<<endl;
                    bzero(jkl,sizeof(jkl));
                }




                }

            }





        }
        else 
        {
            cout<<"wrong password"<<endl;
            send(newfd,"n",1,0);
        }
    } 
    
    } 
    
    
    }
    
 


    
     close(newfd);
     close(sockfd);
     return 0;  
   




}



void error(char* text)
{
    perror(text);
    exit(1);
}

int main(int argc,char *argv[])
{
    if(argc < 2)
    {
        fprintf(stderr,"please enter port number\n");
        exit(1);
    }
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
    
    portno=atoi(argv[1]);
    ly=portno;

    serv_addr.sin_family= AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd,(struct sockaddr*) &serv_addr,sizeof(serv_addr))<0)
    {
        error("ERROR in bind");
    }

    listen(sockfd,5);
    
    clilen = sizeof(cli_addr);
   // newfd=accept(sockfd,(struct sockaddr*) &cli_addr,&clilen);


    while(1)
    {
      cout<<12<<endl;
    newfd=accept(sockfd,(struct sockaddr*) &cli_addr,&clilen);
    cout<<newfd<<endl;
    
        if(newfd<0)
       {
        error("ERROR on accept");
       }
       pthread_t newthread;
       pthread_create(&newthread,NULL, multiple_server ,(void*) &newfd);
     //  pthread_join(newthread,NULL);
    }



     
//     FILE *fp;
//     char l[100];
//     recv(newfd,&l,sizeof(l),0);
//     int i = strncmp("cr",l,2);
//     int j = strncmp("l",l,1);
//     bzero(l,sizeof(l));
//     if(i == 0)
//     {
//     char temp[255],t[123];
//     recv(newfd,&temp,sizeof(temp),0);
//     recv(newfd,&t,sizeof(t),0);
//     user.insert(pair<string,string>(temp,t));
//     cout<<endl;

//      for (itr = user.begin(); itr != user.end(); ++itr) { 
//         cout << endl << itr->first 
//              << endl << itr->second << '\n'; 
//     } 

//     cout<<"user created"<<endl;
//     }
//     else
//     {
//        // cout<<011<<endl;
//   //  int j = strncmp("c",l,1);
//     if(j == 0)
//     {
//        // cout<<9<<endl;
//     char temp1[255],t1[123];
//     recv(newfd,&temp1,sizeof(temp1),0);
//    // cout<<1234<<endl;
//     recv(newfd,&t1,sizeof(t1),0);
//     //cout<<123<<endl;

//     itr = user.find(temp1);
//   //  cout<<12300<<endl;

//     if(itr == user.end())
//     {
//         cout<<"user not found"<<endl;
//         send(newfd,"n",1,0);
//     }
//     else 
//     {
//         if(itr->second == t1)
//         {
//             cout<<"login successfull"<<endl;
//             send(newfd,"done",4,0);
//             //cout<<99<<endl;
//             char l1[100];
//             recv(newfd,&l1,sizeof(l1),0);
//             //cout<<991<<endl;
//             int i1 = strncmp("upload_file",l1,11);
//             //cout<<992<<endl;
//             int j1 = strncmp("download_file",l1,13);
//             //cout<<993<<endl;
//             if(i1 == 0)
//             {
//                 //cout<<994<<endl;
//                 char temp2[255],t2[123];
//                 recv(newfd,&temp2,sizeof(temp2),0);
//                 recv(newfd,&t2,sizeof(t2),0);
//                 int x1;
//                 sscanf(t2, "%d", &x1);
//                 //cout<<x1<<endl;
//                 user1.insert(pair<string,int>(temp2,x1));
//                 cout<<endl;

//                 for (itr1 = user1.begin(); itr1 != user1.end(); ++itr1) { 
//                 cout << endl << itr1->first 
//                     << endl << itr1->second << '\n'; 
//     }
//             }

//              else
//             {
//                 cout<<89<<endl;
//                 //  int j = strncmp("c",l,1);
//                 if(j1 == 0)
//                 {
//                  cout<<9<<endl;
//                 char temp3[255],t3[123];
//                 bzero(temp3,sizeof(temp3));
//                 recv(newfd,&temp3,sizeof(temp3),0);
//                  cout<<1234<<endl;
//                 // recv(newfd,&t3,sizeof(t3),0);
//                 // cout<<123<<endl;

//                 itr1 = user1.find(temp3);
//                 bzero(temp3,sizeof(temp3));

//                 if(itr1 == user1.end())
//                 {
//                     cout<<"file not found"<<endl;
//                     send(newfd,"n",1,0);
//                 }
//                 else
//                 {
//                     cout<<"file present"<<endl;
//                     send(newfd,"done123",7,0);
//                     char jkl[100];
//                     bzero(jkl,sizeof(jkl));
//                     string s = to_string(itr1->second);
//                     strcpy(jkl, s.c_str());
//                     send(newfd,jkl,sizeof(jkl),0);
//                     bzero(jkl,sizeof(jkl));
//                 }




//                 }

//             }





//         }
//         else 
//         {
//             cout<<"wrong password"<<endl;
//             send(newfd,"n",1,0);
//         }
//     } 
    
//     } 
    
    
//     }
    



    
     close(newfd);
     close(sockfd);
     return 0;  















//     FILE *fp;

//     fp = fopen("new.mp3","wb");
//     int file_size;
//     recv(newfd, &file_size,sizeof(file_size),0);
//       cout<<file_size;

//      while ((n = recv(newfd,buff,sizeof(buff),0))>0 && file_size > 0)
//     {
//         fwrite(buff,sizeof(char),n,fp);
//         memset(buff,'\0',sizeof(buff));
//         file_size =file_size - n;
//     }
// }


//     close(newfd);
//     close(sockfd);
//      return 0;
    
}


