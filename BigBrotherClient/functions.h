#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "config.h"

BOOL CALLBACK CountAppsCallback(HWND hwnd, LPARAM lParam);
int get_app_count();
BOOL WINAPI ConsoleHandler(DWORD signal);
void send_alert_packet(const char* server_ip, int port, alertType type, const char* details);
bool is_forbidden(char *window_title);
void monitor_environment(char* ip);
void snapshot_code(const char *filepath);
void install_to_startup(const char* app_name);
void setupConsole();

#endif
