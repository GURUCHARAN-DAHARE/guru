/*
	Create a TCP socket
*/

#include<iostream>
#include<stdio.h>
#include<winsock2.h>
#include<conio.h>
#include<fstream>
#pragma comment(lib,"ws2_32.lib") //Winsock Library
using namespace std;

int main(int argc , char *argv[])
{
	WSADATA wsa;
	SOCKET s;
	int reciev_size;
	struct sockaddr_in server;
    char *message,messagefromserver[50];//[1000];
	string write_message, op ="y";


	cout<<"\nInitialising Winsock...";
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		cout<<"Failed. Error Code : "<<WSAGetLastError();
		return 1;
	}

	cout<<"Initialised.\n";

	//Create a socket
	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		cout<<"Could not create socket : "<<WSAGetLastError();
	}

string ip;
char *ipptr;
	cout<<"Socket created.\n";
    cout<<"Type ip address:\t";
    getline(cin,ip);
    ipptr = &ip[0];
	server.sin_addr.s_addr = inet_addr(ipptr);
	server.sin_family = AF_INET;
	server.sin_port = htons( 8888 );

	//Connect to remote server
	if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		cout<<"connect error";
		return 1;
	}

	cout<<"Connected";
	//Receive a reply from the server
 do{

  if(op=="y"||op=="Y")
            {
               cout<<"\ncommand : ";
                getline(cin,write_message);

            }
            message = &write_message[0];
     if(send(s , message , strlen(message) , 0)<0)
     {
         cout<<"send failed";
         return 1;
     }
cout<<"sent";
     reciev_size = recv(s , messagefromserver , 50 , 0);
     messagefromserver[reciev_size]='\0';

     cout<<"\n"<<messagefromserver<<endl;

    string from;
     char *fromptr,*ptr, file_dataptr[2000];
     ifstream in;
     int h;
     if(write_message.substr(0,4)=="take")
     {

         cout<<"__________________________________________________________________________"<<endl;

         h = write_message.rfind(" ");

         from = write_message.substr(5,h-5);
         fromptr = &from[0];
         cout<<fromptr<<"\n";
         in.open(fromptr,ios::in|ios::binary);

         while(!in.eof())
            {
                in.read(file_dataptr,2000);
                ptr = &file_dataptr[0];
                send(s , ptr , strlen(ptr), 0 );

                cout<<ptr;

            }

          in.close();
     }

     else
        {

           cout<<"__________________________________________________________________________"<<endl;

          do
            {

               reciev_size = recv(s , messagefromserver , 50 , 0);
               messagefromserver[reciev_size]='\0';
               cout<<messagefromserver;
               if(messagefromserver[reciev_size-2]=='q'&&messagefromserver[reciev_size-1]=='\n')
                     break;

             }while(reciev_size>0);
         }
     cout<<"\n__________________________________________________________________________"<<endl;

     cout<<"Will you have more execution(Y/N):\t";
     getline(cin,op);

     cout<<"\n__________________________________________________________________________"<<endl;

   }while(op=="y"||op=="Y");
	getch();

	return 0;
}
