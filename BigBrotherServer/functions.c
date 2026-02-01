#include "functions.h"

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
