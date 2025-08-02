#include "Logger/Logger.h"

bool debug = false;

void LOG_DEBUG(const char* message) {
	if (!debug) {
		return;
	}

	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, DEBUG_COLOR);
	std::cout << "DEBUG::" << message << std::endl;
}

void LOG_ERROR(const char* message) {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, ERROR_COLOR);
	std::cout << "ERROR::" << message << std::endl;
}