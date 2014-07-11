#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "smtp.h"

static void app(const char* domain,int port,const char* user_name,const char* password,const char* subject,const char* content,const char** to,int to_len)
{
    SOCKET sock = init_connection(domain, port);
    char buffer[BUF_SIZE];
    char command[BUF_SIZE];

    read_server(sock, buffer);
    puts(buffer);

    //ehlo
    sprintf(command, "%s %s%s", "HELO", domain, CRLF);
    write_server(sock, command);
    read_server(sock, buffer);
    puts(buffer);

 /* send MAIL FROM */
    sprintf(command, "%s<%s>%s", "MAIL FROM:", user_name, CRLF);
    write_server(sock, command);

    /* read response */
    read_server(sock, buffer);
    puts(buffer);

        sprintf(command, "%s<%s>%s", "RCPT TO:", "aminecmi@gmail.com", CRLF);
        write_server(sock, command);
        /* read response */
    read_server(sock, buffer);
    puts(buffer);


 /* send DATA */
    sprintf(command, "%s%s", "DATA", CRLF);
    write_server(sock, command);

    /* read response */
    read_server(sock, buffer);
    puts(buffer);

     /* send body of the message */
    sprintf(command, "%s%s", "Subject: Test smtp\n\nBonjour,\nTest pour le programme C.", CRLF);
    write_server(sock, command);


    /* send the mark of the end of the message */
    sprintf(command, "%s%s%s", ".", CRLF, CRLF);
    write_server(sock, command);

    /* read response */
    read_server(sock, buffer);
    puts(buffer);

    /* send QUIT */
    sprintf(command, "%s%s", "QUIT", CRLF);
    write_server(sock, command);

    /* read response */
    read_server(sock, buffer);
    puts(buffer);

   end_connection(sock);
}

static int init_connection(const char *address, const int port)
{
   SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
   SOCKADDR_IN sin = { 0 };
   struct hostent *hostinfo;

   if(sock == INVALID_SOCKET)
   {
      perror("socket()");
      exit(errno);
   }

   hostinfo = gethostbyname(address);
   if (hostinfo == NULL)
   {
      fprintf (stderr, "Unknown host %s.\n", address);
      exit(EXIT_FAILURE);
   }

   sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
   sin.sin_port = htons(port);
   sin.sin_family = AF_INET;

   if(connect(sock,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
   {
      perror("connect()");
      exit(errno);
   }

   return sock;
}

static void end_connection(int sock)
{
   closesocket(sock);
}

static void read_server(SOCKET sock, char *buffer)
{
    char *p;
    int n = 0;

    if((n = recv(sock, buffer, BUF_SIZE - 1, 0)) < 0)
    {
        perror("recv()");
        exit(errno);
    }

    if(n == 0)
    {
       printf("Connection lost\n");
       exit(EXIT_FAILURE);
    }

    buffer[n] = 0;

    p = strstr(buffer, CRLF);

    if(p != NULL)
    {
        *p = 0;
    }
}

static void write_server(SOCKET sock, char *buffer)
{
    if(send(sock, buffer, strlen(buffer), 0) < 0)
    {
        perror("send()");
        exit(errno);
    }
}

int main(int argc, char **argv)
{
    /* Connection au client, et récupérer les données du client*/
    // données en dur ici
     app (
        "aspmx.l.google.com",
        25,
        "toto@toto.toto",
        "tatatatatata",
        "sujet",
        "contenu",
        "tata@tata.tata",
        1
    );
   return EXIT_SUCCESS;
}
