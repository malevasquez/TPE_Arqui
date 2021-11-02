#ifndef STDC_H
#define STDC_H

void consoleSize(int maxX, int minX, int maxY, int minY);
int atoi(char * str);
int intToString(unsigned long long num, char * buffer);
int strlen(char *str);
int strcmp(char * str1, char * str2);
int intToBase(unsigned long long num, int base, char*buffer);
int iabs(int num);
char * strcpy(char * dest, char * src);
int atohex(char * str);
char toUpper(char letter);
char toLower(char letter);
int readKeyboard(char * buffer, int size);
void setConsoleUpdateFunction(void (*f)(char *, int));
char getChar();
void printf(char *, ...);
void putChar(char ch);
void scanf(char *);
int getError();
#endif
