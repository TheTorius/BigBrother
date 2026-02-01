#include "functions.h"

char GLOBAL_SERVER_IP[16] = "127.0.0.1";
int MAX_WIN_COUNT = 50;
int PORT = 12345;

char *BLACKLIST[] = {
	"chrome",
	"firefox",
	"edge",
	"opera",
	"seznam",
	"chat",
	"winscp",
	"cmd",
	"console",
	"far",
	"outlook",
	"teams",
	"kazov",
	NULL 
};

int main(int argc, char* argv[]) {
	PORT = 0;
	GLOBAL_SERVER_IP[0] = '\0';
	MAX_WIN_COUNT = 0;
	
	for(int i = 1; i < argc; i++) {
		if(!strcmp(argv[i],"-port")) {
			PORT = atoi(argv[++i]);
		} else if(!strcmp(argv[i],"-ip")) {
			strncpy(GLOBAL_SERVER_IP, argv[++i], 15);
			GLOBAL_SERVER_IP[15] = '\0';
		} else if(!strcmp(argv[i],"-winCNT")) {
			MAX_WIN_COUNT = atoi(argv[++i]);
		}
	}
	
	if(PORT == 0 || GLOBAL_SERVER_IP[0] == '\0' || MAX_WIN_COUNT == 0) exit(EXIT_FAILURE);
	
	install_to_startup("BigBrotherClient");
	
	if (!SetConsoleCtrlHandler(ConsoleHandler, TRUE)) {
		printf("\nCHYBA: Nepodarilo se nastavit odchytavani zavreni okna!\n");
		exit(EXIT_FAILURE);
	}
	
	char title[256];
	sprintf(title,"Big Brother v%.1f - %d", VERSION, MAX_WIN_COUNT);
	
	char str[16];
	gethostname(str,sizeof(str));
	send_alert_packet(GLOBAL_SERVER_IP,PORT+1,ALERT,str);
	
	printf("Spoustim monitoring klienta (Big Brother)...\n");
	printf("Sledovany soubor: %s\n", "nullptr");
	printf("Server IP: %s:%d\n", GLOBAL_SERVER_IP, PORT);
	printf("Verze BigBrothera: %.1f\n", VERSION);
	
	int timer = 0;
	
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Selhala inicializace Winsock.\n");
		return 1;
	}
	
	SetConsoleTitle(title);
	
	system("pause");
	
	while (1) {
		monitor_environment(GLOBAL_SERVER_IP);
		
		if (timer % 10 == 0) {
			//snapshot_code();
		}
		
		timer++;
		Sleep(1000); 
	}
	
	WSACleanup();
	
	return 0;
}
