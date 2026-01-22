#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

// --- DEKLARACE STRUKTUR (Musí být shodné s klientem!) ---

typedef enum alertType{
	ALERT = 0,
	WARNING = 1
}alertType;

#pragma pack(push, 1)
typedef struct Packet {
	char ip[16];        // Identifikátor/IP klienta
	int type;           // AlertType
	int64_t timestamp;  // Časová značka
	char message[64];   // Zpráva (např. název okna)
} Packet;
#pragma pack(pop)

#define PORT 12345

void print_packet(Packet *pkt, const char* client_ip) {
	time_t raw_time = (time_t)pkt->timestamp;
	struct tm * timeinfo = localtime(&raw_time);
	char buffer[80];
	
	// Formátování času na čitelný řetězec
	strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
	
	const char* type_str;
	switch(pkt->type) {
		case ALERT: type_str = "ALERT"; break;
		default: type_str = "UNKNOWN"; break;
	}
	
	printf("--------------------------------------------------\n");
	printf("[PRIJATO] Z IP: %s (Hlaseno jako ID: %s)\n", client_ip, pkt->ip);
	printf("Cas:   %s\n", buffer);
	printf("Typ:   %s\n", type_str);
	printf("Zprava: %s\n", pkt->message);
	printf("--------------------------------------------------\n");
}

int main() {
	SOCKET server_fd, new_socket;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	
#ifdef _WIN32
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Chyba: WSAStartup selhal.\n");
		return 1;
	}
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
	
	while (1) {
		struct sockaddr_in client_addr;
		socklen_t client_len = sizeof(client_addr);
		
		new_socket = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
		
		if (!SOCK_VALID(new_socket)) {
			perror("Chyba pri Accept");
			continue;
		}
		
		Packet pkt;
		int bytes_read = recv(new_socket, (char*)&pkt, sizeof(Packet), 0);
		
		if (bytes_read == sizeof(Packet)) {
			char *client_ip = inet_ntoa(client_addr.sin_addr);
			
			print_packet(&pkt, client_ip);
		} else {
			printf("[CHYBA] Prijat neuplny packet nebo spatna velikost dat.\n");
		}
		
		CLOSE_SOCKET(new_socket);
	}
	
	CLOSE_SOCKET(server_fd);
#ifdef _WIN32
	WSACleanup();
#endif
	
	return 0;
}
