/* sampleCodeModule.c */
#include <shell.h>

char * v = (char*)0xB8000 + 79 * 2;

int main() {
	initShell();
	return 0;
}
