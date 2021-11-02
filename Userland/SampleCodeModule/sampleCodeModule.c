/* sampleCodeModule.c */
#include <shell.h>

char * v = (char*)0xB8000 + 79 * 2;

int main() {
	//para correr la shell
	initShell();
	return 0;
}
