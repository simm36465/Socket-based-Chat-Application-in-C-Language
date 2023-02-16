#include <stdio.h>
#include <winsock2.h>

int main()
{
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
        fprintf(stderr, "La fonction WSAStartup a echoue.\n");
    else
    {
       /* déclaration de la socket serveur */
        	SOCKET c_socket;
       /* création de la socket serveur a l'aide de la fonction 'socket'*/
        	c_socket = socket(AF_INET, SOCK_STREAM,0);
       /* déclaration et initialisation de la structure SOCKADDR_IN */
            SOCKADDR_IN client;
			client.sin_addr.s_addr = inet_addr("127.0.0.1");
			client.sin_family = AF_INET;
			client.sin_port = htons(9999); 
       /* se connecter au serveur 'connect'*/
            connect(c_socket,(SOCKADDR*)&client,sizeof(client));
            printf("Connected to server \n");
		      while(1){
		      	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		      	// Reset the text color to white
    			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		      	// Send data to client
		        char response[255];
		        memset(response, 0, sizeof(response));

		        printf("Client: ");
		        fgets(response, sizeof(response), stdin);
        		response[strcspn(response, "\n")] = '\0';
        		fflush(stdin);
		        send(c_socket, response, strlen(response), 0);
		    
		    	// Receive data from client
		        char receive[255];
		        int bytes_received;
		        bytes_received = recv(c_socket, receive, 255, 0);
		            // Change the text color to green
				    
				    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
		        printf("Server: %s\n", receive);
		        
		        if (bytes_received <= 0) {
		            // Connection is lost, break the loop
		            break;
		        }
		        
		
		    }
//         char buffer[100];
//         int n;                        
//         
//
//         /* appel de la function recv */
//         	recv(c_socket,buffer,strlen(buffer),0);
//            buffer[n] = '\0';
//            printf("%s", buffer);
//
//         /* appel de la function send */         
//    		send(c_socket,buffer,strlen(buffer),0);
                                                
         /* fermeture de la socket client */
         closesocket(c_socket);	
                       
        WSACleanup();
    }
    return 0;
}

