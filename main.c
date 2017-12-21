#include <stdio.h>
#include "gc.h"
#include <math.h>
#include "root.h"
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
        
        h_init(1000, false, 0.5f);
        printf("stack size: %i\n\n", stack_size());
	return 0;
}
