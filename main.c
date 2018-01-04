#include <stdio.h>
#include "gc.h"
#include <math.h>
int main(int argc, char** argv)
{
	#ifdef _WIN32
	puts("windows");
	#endif
	
	#ifdef __linux__
	puts("linux");
	#endif
	
	#ifdef __unix__
	puts("unix");
	#endif

	return 0;
}