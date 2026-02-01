#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <stdint.h>

// --- MULTIPLATFORMNÍ HLAVIČKY A MAKRA ---

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define CLOSE_SOCKET(s) closesocket(s)
#define SOCK_VALID(s) ((s) != INVALID_SOCKET)
typedef int socklen_t; 

#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define CLOSE_SOCKET(s) close(s)
#define SOCKET int
#define INVALID_SOCKET -1
#define SOCK_VALID(s) ((s) >= 0)
#endif

typedef struct SocketNode {
	SOCKET* socket;
	struct SocketNode* nextNode;
}SocketNode;

typedef struct SocketList {
	SocketNode* start;
	SocketNode* last;
	int numOfNodes;
}SocketList;

// --- DEKLARACE STRUKTUR (Musí být shodné s klientem!) ---
typedef enum alertType{
	HELLO = 0,
	CONFIG = 1,
	ALERT = 2,
	WARNING = 3,
	BYE = 4,
	START = 5
}alertType;

#pragma pack(push, 1)
typedef struct Packet {
	char ip[16];        // Identifikátor/IP klienta
	int type;           // AlertType
	int64_t timestamp;  // Časová značka
	char message[64];   // Zpráva (např. název okna)
} Packet;
#pragma pack(pop)

extern int PORT;

#endif
