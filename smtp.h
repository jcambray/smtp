#ifndef SERVER_H
#define SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;


#define CRLF	 "\r\n"

#define BUF_SIZE 1024

static void send_and_read(SOCKET sock, char* cmd, char* buffer);
static void app(const char* domain,int port,const char* user_name,const char* password,const char* subject,const char* content,const char** to,int to_len);
static int init_connection(const char *address, const int port);
static void end_connection(int sock);
static void read_server(SOCKET sock, char *buffer);
static void write_server(SOCKET sock, char *buffer);

#endif /* guard */
