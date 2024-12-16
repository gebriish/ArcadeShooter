#pragma once
#include <iostream>

#ifdef DEBUG
	#define LOG_INFO(...) printf("[INFO] >  " __VA_ARGS__)
	#define LOG_WARN(...) printf("[WARN] >  " __VA_ARGS__)
	#define LOG_SVER(...) printf("[SVER] >  " __VA_ARGS__)
#else
	#define LOG_INFO(...) ((void)0)
	#define LOG_WARN(...) ((void)0)
	#define LOG_SVER(...) ((void)0)
#endif

#define ERROR_EXIT(...) printf(__VA_ARGS__); exit(1)
