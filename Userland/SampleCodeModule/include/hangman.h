#ifndef hangman_h
#define hangman_h

#include <stdio.h>
#include <stdarg.h>

//Lee un int de la entrada standar
int getint(const char message[], ... );

char readLetter(void);

void printWord(const char word[], const short found[]);

int completeWord(const char word[], const short found[]);

#endif /* hangman_h */
