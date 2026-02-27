#include "functions.h"

int PORT = 12345;
HANDLE hSaveMutex;
bool started;

int main() {
	SocketList list;
	list.start = NULL;
	list.last = NULL;
	list.numOfNodes = 0;
	started = false;
	
	alertCounter alerts[NOfAlertTypes];
	for(int i = 0; i < NOfAlertTypes; i++) {
		alerts[i].type = i;
		alerts[i].count = 0;
		alerts[i].list = malloc(sizeof(PCNameList));
		alerts[i].list->first = NULL;
		alerts[i].list->last = NULL;
	}
	
	hSaveMutex = CreateMutex(NULL, FALSE, NULL);
	
	SOCKET server_fd;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	
#ifdef _WIN32
	if (!SetConsoleCtrlHandler(ConsoleHandler, TRUE)) {
		printf("\nCHYBA: Nepodarilo se nastavit odchytavani zavreni okna!\n");
		exit(EXIT_FAILURE);
	}
	
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
			started = true;
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
				case WAITING: {
					send_response(*new_socket,WAITING,"WAITING");
					break;
				}
				case START: {
					list.numOfNodes++;
					printf("Clients: %d\n", list.numOfNodes);
					break;
				}
			default:
				break;
			}
			
			if(started) {
				print_packet(&pkt, client_ip, alerts);
				WaitForSingleObject(hSaveMutex, INFINITE);
				print_alerts_json(alerts);
				ReleaseMutex(hSaveMutex);
				MessageBeep(MB_ICONASTERISK);	
			}
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
