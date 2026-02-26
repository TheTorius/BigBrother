#include "functions.h"
#include "cJSON.h"

void print_packet(Packet *pkt, const char* client_ip, alertCounter* alerts ) {
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
		case WARNING: type_str = "WARNING"; SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);  break;
		case BYE: type_str = "BYE"; SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);  break;
		default: type_str = "UNKNOWN"; SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY); break;
	}
	
	alerts[pkt->type].count++;	
	
	if(alerts[pkt->type].list->first == NULL) {
		alerts[pkt->type].list->first = malloc(sizeof(PCNameNode)); 	
		alerts[pkt->type].list->last = alerts[pkt->type].list->first;
		alerts[pkt->type].list->first->next = NULL;
		strcpy(alerts[pkt->type].list->last->name,pkt->ip);
	} else {
		alerts[pkt->type].list->last->next = malloc(sizeof(PCNameNode));
		alerts[pkt->type].list->last = alerts[pkt->type].list->last->next;
		alerts[pkt->type].list->last->next = NULL;
		strcpy(alerts[pkt->type].list->last->name,pkt->ip);
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

void print_alerts_json(alertCounter *ac) {
// 1. Vytvoříme hlavní kořenový objekt a pole, ve kterém budou všechny typy
	cJSON *root = cJSON_CreateObject();
	cJSON *all_types_array = cJSON_AddArrayToObject(root, "alerts_report");
	
	// Iterujeme skrz všech 6 typů (0 až 5)
	for (int i = 0; i < 6; i++) {
		// Pro každý typ vytvoříme samostatný objekt
		cJSON *type_obj = cJSON_CreateObject();
		
		switch (ac[i].type) {
			case HELLO: cJSON_AddStringToObject(type_obj, "type_label","HELLO"); break;
			case CONFIG: cJSON_AddStringToObject(type_obj, "type_label","CONFIG"); break;
			case ALERT: cJSON_AddStringToObject(type_obj, "type_label","ALERT"); break;
			case WARNING: cJSON_AddStringToObject(type_obj, "type_label","WARNING"); break;
			case BYE: cJSON_AddStringToObject(type_obj, "type_label","BYE"); break;
			case START: cJSON_AddStringToObject(type_obj, "type_label","START"); break;
		}
		
		cJSON_AddNumberToObject(type_obj, "type_id", i);
		cJSON_AddNumberToObject(type_obj, "total_count", ac[i].count);
		
		// Vytvoříme pole pro klienty u tohoto konkrétního typu
		cJSON *clients_array = cJSON_AddArrayToObject(type_obj, "clients");
		
		// Projdeme spojový seznam pro daný typ (pokud existuje)
		if (ac[i].list != NULL) {
			PCNameNode *current = ac[i].list->first;
			while (current != NULL) {
				cJSON_AddItemToArray(clients_array, cJSON_CreateString(current->name));
				current = current->next;
			}
		}
		
		// Objekt typu vložíme do hlavního pole
		cJSON_AddItemToArray(all_types_array, type_obj);
	}
	
	// 2. Převod na string a zápis do souboru
	char *json_string = cJSON_Print(root); // Použij cJSON_PrintUnformatted(root) pro úsporu místa
	
	FILE *f = fopen("log.json", "w"); // Doporučuji "w", aby byl JSON vždy validní jako celek
	if (f != NULL) {
		fputs(json_string, f);
		fclose(f);
	}
	
	// 3. Úklid - cJSON_Delete maže všechno, co je v rootu "pod ním"
	cJSON_Delete(root);
	free(json_string);
}

BOOL WINAPI ConsoleHandler(DWORD signal) {
	if (signal == CTRL_CLOSE_EVENT || signal == CTRL_C_EVENT || signal == CTRL_BREAK_EVENT) {
		WaitForSingleObject(hSaveMutex,INFINITE);
		
		printf("\nUkoncuje se!\n");
		
		ReleaseMutex(hSaveMutex);
		CloseHandle(hSaveMutex);
		
		exit(0);
		return TRUE;
	}
	return FALSE;
}
