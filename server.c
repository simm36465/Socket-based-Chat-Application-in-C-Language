#include <stdio.h>
#include <winsock2.h>
#include <string.h>
int main()
{
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0){
        fprintf(stderr, "La fonction WSAStartup a echoue.\n");
        WSACleanup();
        return 1;
    } else
    {
       /* déclaration de la socket serveur */
        SOCKET sock;

       /* création de la socket serveur a l’aide de la fonction ‘socket’*/
        sock = socket(AF_INET, SOCK_STREAM, 0);

       /* déclaration et initialisation de la structure SOCKADDR_IN */

        SOCKADDR_IN sin;
        sin.sin_family = AF_INET;
        sin.sin_addr.s_addr = inet_addr("127.0.0.1");
        sin.sin_port = htons(9999);

       /* association des information a la socket (binding) */
        bind(sock, (SOCKADDR*)&sin, sizeof(sin));

       /* mettre la socket dans l’état d’écoute */
        listen(sock,0);

        printf("Serveur demarrer...\n");
        printf("==>IP address: %s\n", inet_ntoa(sin.sin_addr));
        printf("==>Port number: %d\n", ntohs(sin.sin_port));

        SOCKET s_client;/* socket du client */
        SOCKADDR_IN client;/*contexte d’adressage du client */
        int csize = sizeof(client);
        /* appel de la fonction accept */
        s_client = accept(sock, (SOCKADDR*)&client, &csize) ;

        printf("Client connected --> IP address: %s\n", inet_ntoa(client.sin_addr));
        printf("------------------------------------------------------\n");

      while(1){
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            // Change the text color to green
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

        char receive[255];
        int bytes_received;
        // Receive data from client
        bytes_received = recv(s_client, receive, 255, 0);
        printf("Client: %s\n", receive);
        // Reset the text color to white
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        if (bytes_received <= 0) {
            // Connection is lost, break the loop
            break;
        }


        // Send data to client
        char response[255];
        memset(response, 0, sizeof(response));
        printf("Server: ");
        fgets(response, sizeof(response), stdin);
        response[strcspn(response, "\n")] = '\0';
        fflush(stdin);
        send(s_client, response, strlen(response), 0);


    }



        /* fermeture de la socket client */
            closesocket(s_client);

         /* fermeture de la socket serveur */
            closesocket(sock);

        WSACleanup();
    }
    return 0;
}
