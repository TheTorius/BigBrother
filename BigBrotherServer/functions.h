#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "config.h"

void print_packet(Packet *pkt, const char* client_ip);
void send_response(SOCKET socket, alertType type, char* string);

#endif
