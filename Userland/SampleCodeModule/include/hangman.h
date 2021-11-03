#ifndef hangman_h
#define hangman_h

#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>

//Macro para vaciar el buffer
#define BORRA_BUFFER while (getchar() != '\n')

int getint(const char message[], ... ) {
    int n, leave = 0;
    va_list ap;
        
    do {
        va_start(ap, message);
        vprintf(message, ap);
        va_end(ap);

        if ( scanf("%d",&n) != 1)
        {
            printf("\nDato incorrecto\n");
            BORRA_BUFFER;
        }
        else
            leave = 1;
    } while (! leave);
    BORRA_BUFFER;
    return n;
}

char readLetter(void)
{
    char letter;
    printf("Please enter a letter: ");
    letter = getchar();
    if(letter != '\n')
        BORRA_BUFFER;
    return letter;
}

int checkLetter(const char word[], char letter, short found[])
{
    int i, ok = 0;

    for (i = 0; word[i]; i++)
        if (word[i] == letter)
        {
            ok = 1;
            found[i] = 1;
        }
    return ok;
}

void printWord(const char word[], const short found[])
{
    int i;

    for (i = 0; word[i]; i++)
    {
        if (found[i])
            putchar(word[i]);
        else
            putchar('_');
        putchar(' ');
    }
    putchar('\n');
}
int completeWord(const char word[], const short found[])
{
    int i, complete = 1;

    for (i = 0; word[i] && complete; i++)
        if (found[i] == 0)
            complete = 0;

    return complete;
}

#endif 
