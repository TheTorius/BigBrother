#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

const char *BLACKLIST[] = {
	"chrome",
	"firefox",
	"edge",
	"opera",
	"seznam",
	"chat",
	NULL // Konec pole
};

bool is_forbidden(char *window_title) {
	char lowerCase[256];
	for(int i = 0; i < 256; i++) {
		lowerCase[i] = tolower(window_title[i]);
	}
	for (int i = 0; BLACKLIST[i] != NULL; i++) {
		if (strstr(lowerCase, BLACKLIST[i]) != NULL) {
			return true; 
		}
	}
	return false;
}

void monitor_environment() {
	char window_title[256];
	HWND foreground_window;
	
	foreground_window = GetForegroundWindow();
	
	if (foreground_window) {
		GetWindowText(foreground_window, window_title, 256);
		
		if (strlen(window_title) > 0) {
			printf("Student se diva na: %s\n", window_title);
			
			if (is_forbidden(window_title)) {
				printf("[ALERT] DETEKOVAN ZAKAZANY SW! Odesilam hlaseni na RPi...\n");
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
	if(argc < 2) return 450;
	
	printf("Spoustim monitoring klienta (Big Brother - Safe Edition)...\n");
	
	int timer = 0;
	
	while (1) {
		monitor_environment();
		
		if (timer % 10 == 0) {
			snapshot_code(argv[1]);
			//snapshot_code("C:\\Users\\Student\\Documents\\Projekt\\main.c");
		}
		
		timer++;
		Sleep(1000); 
	}
	
	return 0;
}
