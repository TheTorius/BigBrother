#ifndef CONFIG_H
#define CONFIG_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>

#define VERSION 1.1
#pragma comment(lib, "ws2_32.lib")

extern char GLOBAL_SERVER_IP[16];
extern int MAX_WIN_COUNT;
extern int PORT;

extern char *BLACKLIST[];

typedef enum alertType{
	HELLO = 0,
	CONFIG = 1,
	ALERT = 2,
	WARNING = 3,
	BYE = 4
}alertType;

#pragma pack(push, 1)
typedef struct Packet {
	char ip[16];        
	int type;           
	int64_t timestamp;  
	char message[64];  
} Packet;
#pragma pack(pop)

#endif
