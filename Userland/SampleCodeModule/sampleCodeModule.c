/* sampleCodeModule.c */
#include <shell.h>
#include <libc.h>
#include <userSyscalls.h>

int main()
{
	_setStack();
	initialize(0, NULL);
	// char *argv[] = {"Shell"};
	// newProcess(initialize, 1, argv, FOREGROUND, NULL);
	return 0;
}

// char * v = (char*)0xB8000 + 79 * 2;

// static int var1 = 0;
// static int var2 = 0;

// int main() {
// 	//All the following code may be removed
// 	*v = 'X';
// 	*(v+1) = 0x74;

// 	//Test if BSS is properly set up
// 	if (var1 == 0 && var2 == 0)
// 		return 0xDEADC0DE;

// 	return 0xDEADBEEF;
// }