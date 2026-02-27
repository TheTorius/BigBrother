#include "functions.h"

BOOL CALLBACK CountAppsCallback(HWND hwnd, LPARAM lParam) {
	int* counter = (int*)lParam; 
	
	if (IsWindowVisible(hwnd)) {
		char title[256];
		GetWindowText(hwnd, title, 256);
		
		if (strlen(title) > 0) {
			(*counter)++;
		}
	}
	return TRUE; 
}

int get_app_count() {
	int count = 0;
	EnumWindows(CountAppsCallback, (LPARAM)&count); 
	return count;
}

BOOL WINAPI ConsoleHandler(DWORD signal) {
	if (signal == CTRL_CLOSE_EVENT || signal == CTRL_C_EVENT || signal == CTRL_BREAK_EVENT) {
		
		printf("\n[SYSTEM] Pokus o ukonceni detekovan! Odesilam zpravu na server...\n");
		
		send_alert_packet(GLOBAL_SERVER_IP, PORT, ALERT, "Student zavrel okno!");
		char str[16];
		gethostname(str,sizeof(str));
		send_alert_packet(GLOBAL_SERVER_IP,PORT+1,ALERT,str);
		
		Sleep(1000); 
		
		return TRUE; 
	}
	return FALSE;
}

int send_alert_packet(const char* server_ip, int port, alertType type, const char* details) {
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		printf("Chyba vytvoreni socketu: %d\n", WSAGetLastError());
		return 0;
	}
	
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = inet_addr(server_ip);
	
	if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		printf("Nelze se pripojit k serveru %s\n", server_ip);
		closesocket(sock);
		return 0;
	}
	
	Packet pkt;
	memset(&pkt, 0, sizeof(Packet)); 
	gethostname(pkt.ip, sizeof(pkt.ip));
	pkt.type = (int)type;
	pkt.timestamp = (int64_t)time(NULL);
	strncpy(pkt.message, details, 63);
	
	send(sock, (char*)&pkt, sizeof(Packet), 0);
	printf(">> Odeslan packet [TYPE: %d] na server.\n", type);
	
	if (type == HELLO || type == CONFIG || type == START) {
		int bytes;
		Packet response;
		bytes = recv(sock, (char*)&response, sizeof(Packet), 0);
		while(type == START && bytes <= 0){
			printf(".. cekam na potvrzeni od serveru ..\n");
			bytes = recv(sock, (char*)&response, sizeof(Packet), 0);
			Sleep(1000);
		}
		
		if (bytes > 0) {
			response.message[sizeof(response.message) - 1] = '\0';
			if(type != CONFIG) printf("<< Prijata odpoved: %s\n", response.message);
			else printf("<< Config obdrzen\n");
			
#ifdef DEBUG
			printf("%s",response.message);
#endif
			
			if(type == CONFIG) {
				char* token = strtok(response.message, ",\n");
				while(token != NULL) {
					// Alokujeme místo pro dosavadní položky + novou položku + ukončovací NULL
					char **temp = (char **)realloc(BLACKLIST, (nOfBlacklistItems + 2) * sizeof(char*));
					if(temp == NULL) {
						exit(EXIT_FAILURE);
					}
					BLACKLIST = temp;
					
					// Alokujeme místo pro text
					BLACKLIST[nOfBlacklistItems] = (char *)malloc(31 * sizeof(char));
					
					// Bezpečné kopírování s garancí konce
					strncpy(BLACKLIST[nOfBlacklistItems], token, 30);
					BLACKLIST[nOfBlacklistItems][30] = '\0';
					
					nOfBlacklistItems++; // Zvýšíme počet
					
					// ZAJIŠTĚNÍ KONCE POLE (Důležité pro is_forbidden!)
					BLACKLIST[nOfBlacklistItems] = NULL; 
					
					token = strtok(NULL, "\n,\0");
				}
			}
			
		} else {
			printf("!! Server neodpovedel nebo ukoncil spojeni.\n");
			return 0;
		}
		if(response.type == type) return 2;
		return 0;
	}
	if(type == WAITING) return 2;
	
	closesocket(sock);
	return 1;
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
			
			if (is_forbidden(window_title)) {
				printf("[ALERT] DETEKOVAN ZAKAZANY SW! Odesilam hlaseni na Server...\n");
				send_alert_packet(GLOBAL_SERVER_IP,PORT,ALERT,window_title);
			}
		}
	}
	
	int app_count = get_app_count();
	
	if (app_count > MAX_WIN_COUNT) {
		printf("[WARNING] Moc otevrenych oken (%d)! Hlasim...\n", app_count);
		
		char msg[64];
		snprintf(msg, 64, "Moc oken: %d", app_count);
		send_alert_packet(ip, 12345, WARNING, msg);
	}
}

void snapshot_code(const char *filepath) {
	FILE *file = fopen(filepath, "r");
	if (file) {
		//printf("Vytvarim snapshot souboru: %s\n", filepath);
		fclose(file);
	} else {
		//printf("Soubor se studentovym kodem nenalezen.\n");
	}
}

void install_to_startup(const char* app_name) {
	char exe_path[MAX_PATH];
	HKEY hKey;
	
	if (GetModuleFileName(NULL, exe_path, MAX_PATH) == 0) {
		printf("Chyba: Nelze zjistit cestu k programu.\n");
		return;
	}
	
	long result = RegOpenKeyEx(HKEY_CURRENT_USER, 
							   "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 
							   0, KEY_SET_VALUE, &hKey);
	
	if (result != ERROR_SUCCESS) {
		printf("Chyba: Nelze otevrit registry (error %ld).\n", result);
		return;
	}
	
	result = RegSetValueEx(hKey, app_name, 0, REG_SZ, (BYTE*)exe_path, strlen(exe_path) + 1);
	
	if (result == ERROR_SUCCESS) {
		printf("USPECH: Program pridan do 'Po spusteni'.\n");
	} else {
		printf("Chyba: Zapis do registru selhal.\n");
	}
	
	RegCloseKey(hKey);
}

void setupConsole() {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	GetConsoleMode(hOut, &dwMode);
	SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}
