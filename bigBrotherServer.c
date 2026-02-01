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

int PORT = 12345;

void print_packet(Packet *pkt, const char* client_ip) {
	time_t raw_time = (time_t)pkt->timestamp;
	struct tm * timeinfo = localtime(&raw_time);
	char buffer[80];
	
	// Formátování času na čitelný řetězec
	strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	const char* type_str;
	switch(pkt->type) {
		case ALERT: type_str = "ALERT"; SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); break;
		case HELLO: type_str = "HELLO"; SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY); break;
		case CONFIG: type_str = "CONFIG"; SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY); break;
		case WARNING: type_str = "WARNING"; SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); break;
		case BYE: type_str = "BYE"; SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY); break;
		default: type_str = "UNKNOWN"; SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY); break;
	}
	
	printf("--------------------------------------------------\n");
	printf("[PRIJATO] Z IP: %s (Hlaseno jako ID: %s)\n", client_ip, pkt->ip);
	printf("Cas:   %s\n", buffer);
	printf("Typ:   %s\n", type_str);
	printf("Zprava: %s\n", pkt->message);
	printf("--------------------------------------------------");
}

void send_response(SOCKET socket, alertType type, char* string) {
	Packet response;
	memset(&response, 0, sizeof(Packet)); 
	gethostname(response.ip, sizeof(response.ip));
	response.type = type;
	response.timestamp = (int64_t)time(NULL);
	strncpy(response.message, string, 63);
	
	send(socket, (char*)&response, sizeof(Packet), 0);
}

int main() {
	SocketList list;
	list.start = NULL;
	list.last = NULL;
	list.numOfNodes = 0;
	
	SOCKET server_fd;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	
#ifdef _WIN32
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Chyba: WSAStartup selhal.\n");
		return 1;
	}
	SetConsoleOutputCP(65001);
#endif
	
	if (!SOCK_VALID(server_fd = socket(AF_INET, SOCK_STREAM, 0))) {
		perror("Chyba pri vytvareni socketu");
		return 1;
	}
	
	int opt = 1;
#ifdef _WIN32
	setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt));
#else
	setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
#endif
	
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY; // Naslouchat na všech síťových kartách
	address.sin_port = htons(PORT);
	
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		perror("Chyba pri Bind");
		return 1;
	}
	
	if (listen(server_fd, 3) < 0) {
		perror("Chyba Listen");
		return 1;
	}
	
	printf("=== BIG BROTHER SERVER ===\n");
	printf("Server bezi a nasloucha na portu %d...\n", PORT);
	printf("Cekam na packety od studentu...\n\n");
	
	u_long mode = 1; // 1 = neblokující, 0 = blokující
	ioctlsocket(server_fd, FIONBIO, &mode);
	
	while (1) {
		if (GetAsyncKeyState('P') & 0x8000) {
			printf("Posilam start\n");
			SocketNode* np = NULL;
			for(SocketNode* n = list.start; n != NULL; n = n->nextNode) {
				if(np != NULL) {
					CLOSE_SOCKET(*np->socket);
					free(np);
				}
				send_response(*n->socket,START,"START");
				np = n;
			}
			if(list.numOfNodes > 0) {
				CLOSE_SOCKET(*np->socket);
				free(np);
			}
			list.start = NULL;
			list.last = NULL;
			list.numOfNodes = 0;
			Sleep(200);
			system("cls");
		}
		
		struct sockaddr_in client_addr;
		socklen_t client_len = sizeof(client_addr);
		
		SOCKET* new_socket = malloc(sizeof(SOCKET));
		
		*new_socket = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
		
		if (!SOCK_VALID(*new_socket)) {
			int err = WSAGetLastError();
			free(new_socket); // Tady nikdo neni, uvolníme paměť a zkusíme to znova
			
			// Pokud je to jen "WSAEWOULDBLOCK", neni to chyba, jen nikdo neni pripojen
			if (err != WSAEWOULDBLOCK) {
				// Tady muzes neco vypsat, pokud chces videt skutecne chyby
			}
			
			Sleep(10); // Důležité: Šetříme CPU
			continue;
		} 
		
		u_long block_mode = 0; 
		ioctlsocket(*new_socket, FIONBIO, &block_mode);
		
		Packet pkt;
		int bytes_read = recv(*new_socket, (char*)&pkt, sizeof(Packet), 0);
		
		if (bytes_read == sizeof(Packet)) {
			char *client_ip = inet_ntoa(client_addr.sin_addr);
			
			switch (pkt.type) {
				case HELLO: {
					send_response(*new_socket,HELLO,"HELLO");
					break;
				}
				case CONFIG: {
					send_response(*new_socket,CONFIG,"CONFIG");
					break;
				}
				case START:
					list.numOfNodes++;
					printf("Clients: %d\n", list.numOfNodes);
					break;
				default:
					break;
			}
			
			print_packet(&pkt, client_ip);
			MessageBeep(MB_ICONASTERISK);
		} else {
			printf("[CHYBA] Prijat neuplny packet nebo spatna velikost dat.\n");
		}
		
		if(pkt.type != START) CLOSE_SOCKET(*new_socket);
		else {
			SocketNode* node = malloc(sizeof(SocketNode));
			node->socket = new_socket;
			node->nextNode = NULL;
			
			if(list.start == NULL) {
				list.start = node;
				list.last = node;
			} else {
				list.last->nextNode = node;
				list.last = node;
			}
		}
	}
	
	CLOSE_SOCKET(server_fd);
#ifdef _WIN32
	WSACleanup();
#endif
	
	return 0;
}
