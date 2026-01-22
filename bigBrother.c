#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>

const char *BLACKLIST[] = {
	"chrome",
	"firefox",
	"edge",
	"opera",
	"seznam",
	"chat",
	NULL 
};

typedef enum alertType{
	ALERT = 0,
	WARNING = 1
}alertType;

typedef struct Packet{
	char ip[16];
	alertType type;
	time_t timestamp;
	char message[64];
}Packet;

void send_alert_packet(const char* server_ip, int port, alertType type, const char* details) {
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		printf("Chyba vytvoreni socketu: %d\n", WSAGetLastError());
		return;
	}
	
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = inet_addr(server_ip);
	
	// Připojení k serveru (RPi)
	if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		printf("Nelze se pripojit k serveru %s\n", server_ip);
		closesocket(sock);
		return;
	}
	
	Packet pkt;
	memset(&pkt, 0, sizeof(Packet)); // Vynulování paměti
	
	strcpy(pkt.ip, "CLIENT_ID_1"); 
	pkt.type = (int)type;
	pkt.timestamp = (int64_t)time(NULL);
	
	strncpy(pkt.message, details, 63);
	
	send(sock, (char*)&pkt, sizeof(Packet), 0);
	printf(">> Odeslan packet [TYPE: %d] na server.\n", type);
	
	closesocket(sock);
}

bool is_forbidden(char *window_title) {
	char lowerCase[256];
	for(int i = 0; i < 256; i++) {
		lowerCase[i] = tolower(window_title[i]);
		lowerCase[i+1] = '\0';
	}
	for (int i = 0; BLACKLIST[i] != NULL; i++) {
		if (strstr(lowerCase, BLACKLIST[i]) != NULL) {
			return true; 
		}
	}
	return false;
}

void monitor_environment(char* ip) {
	char window_title[256];
	HWND foreground_window;
	
	foreground_window = GetForegroundWindow();
	
	if (foreground_window) {
		GetWindowText(foreground_window, window_title, 256);
		
		if (strlen(window_title) > 0) {
			printf("Student se diva na: %s\n", window_title);
			
			if (is_forbidden(window_title)) {
				printf("[ALERT] DETEKOVAN ZAKAZANY SW! Odesilam hlaseni na RPi...\n");
				send_alert_packet(ip,8080,ALERT,window_title);
			}
		}
	}
}

void snapshot_code(const char *filepath) {
	FILE *file = fopen(filepath, "r");
	if (file) {
		printf("Vytvarim snapshot souboru: %s\n", filepath);
		fclose(file);
	} else {
		printf("Soubor se studentovym kodem nenalezen.\n");
	}
}

int main(int argc, char* argv[]) {
	if(argc < 3) return 450;
	
	printf("Spoustim monitoring klienta (Big Brother - Safe Edition)...\n");
	printf("Sledovany soubor: %s\n", argv[1]);
	printf("Server IP: %s\n", argv[2]);
	
	int timer = 0;
	
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Selhala inicializace Winsock.\n");
		return 1;
	}
	
	while (1) {
		monitor_environment(argv[2]);
		
		if (timer % 10 == 0) {
			snapshot_code(argv[1]);
		}
		
		timer++;
		Sleep(1000); 
	}
	
	WSACleanup();
	
	return 0;
}
