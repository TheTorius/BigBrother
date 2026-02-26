#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "config.h"

void print_packet(Packet *pkt, const char* client_ip, alertCounter* alerts);
void send_response(SOCKET socket, alertType type, char* string);
void print_alerts_json(alertCounter *ac);
BOOL WINAPI ConsoleHandler(DWORD signal);

#endif
