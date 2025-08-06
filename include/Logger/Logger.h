#pragma once

#define DEBUG_COLOR 2
#define ERROR_COLOR 3

void LOG_DEBUG(const char* message);
void LOG_ERROR(const char* message);
//Change later to resolve OS, act on separate thread, save console reference. 
