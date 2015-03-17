/*
	Bind socket to port 8888 on localhost
*/
#include<iostream>
#include<winsock2.h>
#include<conio.h>
#include<stdio.h>
#include<fstream>
#include<string.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library

using namespace std;

int main(int argc , char *argv[])
{
	WSADATA wsa;
	SOCKET s , new_socket;

	struct sockaddr_in server , client;

	int c,recv_size;
	char message_got[100];
	char message[]=">>c:\\guru\\g.txt";
	char *command,*messagetoclient;
	ifstream in;
	string file,tell ="Now running..";;

     messagetoclient = &tell[0];

	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}


	//Create a socket
	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d" , WSAGetLastError());
	}


	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );

	//Bind
	if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d" , WSAGetLastError());
	}


	//Listen to incoming connections

	listen(s , 1);

	//Accept and incoming connection

	c = sizeof(struct sockaddr_in);

	new_socket = accept(s , (struct sockaddr *)&client, &c);

	if (new_socket == INVALID_SOCKET)
	{
		printf("accept failed with error code : %d" , WSAGetLastError());
	}

 do{
        printf("\n~~~~~waiting for executing command~~~~~~~\n");
        if((recv_size = recv(new_socket , message_got , 100 , 0)) == SOCKET_ERROR)
            {
                puts("recv failed");
                return 1;
            }
                        //Add a NULL terminating character to make it a proper string before printing
        message_got[recv_size] = '\0';

cout<<message_got<<"\n";//////////////////////////////////////////////////////////

                send(new_socket , messagetoclient , strlen(messagetoclient) , 0);

        if(message_got[0]=='q'||message_got[0]=='Q')
            {
                closesocket(s);
                closesocket(new_socket);
                WSACleanup();
                return 0;
            }
        else
            {
                    string to,message_got_asstr,fun,g;
                    int i=0,dlen,data_line;
                    char *toptr, file_dataptr[2000];
                    ofstream out;

                        message_got_asstr=&message_got[0];
                        //cout<<"+++++++++++++++++++";
                        fun = message_got_asstr.substr(0,4);
                        //cout<<fun;
                if(fun == "take")

                {


                    dlen = message_got_asstr.rfind(":");
                    to = message_got_asstr.substr((dlen-1),message_got_asstr.length());
                    toptr = &to[0];
cout<<toptr<<endl;//getch();
                    out.open(toptr,ios::out|ios::binary);

                    cout<<"taking file\n";

                  // do{

                      while((data_line = recv(new_socket , file_dataptr ,2000 , 0))>0)
                      {
                         //file_dataptr[data_line]='\0';
                       //cout<<file_dataptr<<"\n";

     /*g = &file_dataptr[0];
                        if(g.find(EOF))//file_dataptr[data_line-1]=='\n'&&file_dataptr[data_line-2]=='q')
                        {
                            cout<<"+++++++++++++++";
                            out.write(file_dataptr,data_line-5);
                            out.close();

                           break;
                        }*/

                       out.write(file_dataptr,data_line);
                       //if(file_dataptr[data_line-1]==EOF)break;
                     }
                }
                else{
                command = strcat(message_got,message);
                //send(new_socket , messagetoclient , strlen(messagetoclient) , 0);
                printf("\n~~~~~~Now i am executing your given command~~~~~~~\n");

                system(command);

                in.open("c:\\guru\\g.txt");

                while(!in.eof())
                {
                     getline(in,file);
                     file.insert(file.length(),"\n");
                     messagetoclient = &file[0];

                     send(new_socket , messagetoclient , strlen(messagetoclient) , 0);
                }
                string quite="q\n";
                messagetoclient=&quite[0];
                send(new_socket , messagetoclient , strlen(messagetoclient) , 0);
                in.close();
                system("del c:\\guru\\g.txt");
                }

            }


 }while(1);

}
