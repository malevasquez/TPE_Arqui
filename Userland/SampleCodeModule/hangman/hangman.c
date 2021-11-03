#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "hangman.h"
#include "pokemon.h"

//Macro para vaciar el buffer
#define DELETE_BUFFER while (getchar() != '\n')

//Cantidad de errores permitidos
#define CHANCES 8

//Longitud maxima que puede tener una palabra
#define WORDLEN 20

char readLetter(void);
int checkLetter(const char word[], char letter, short found[]);
void printWord(const char word[], const short found[]);
int completeWord(const char word[], const short found[]);

int main(void) {
    char dictionary[][WORDLEN] = {"bulbasaur", "butterfree", "charmander", "marowak", "slowpoke", "eevee", "gastly", "geodude", "growlithe", "jigglypuff", "meowth", "pidgey", "pikachu", "poliwag", "ponyta", "psyduck", "rattata", "ditto", "squirtle", "horsea"};
    char letter, *word;
    int mistakes = 0, qWords;
    short found[WORDLEN] = {0};

    qWords = sizeof(dictionary) / WORDLEN;
    
    int n;
    
    do {
        n = getint("Enter a number from 1 to 20: ");
    } while(n > 20 || n < 0);
    
    /* Elegir una palabra*/
    word = dictionary[n - 1];
    
    printLogo();

    printf("\nGotta catch 'em all! Welcome to pokemon-hangman, the game where you have to guess the pokemon's name in order to win!\n");
    printf("You have maximum 6 mistakes allowed :o Remember that all alphabet are in lower case\n");
    printf("\nA wild pokemon has appeared! (◍ㅇᆽㅇ◍) Good luck :)\n");

    do {
        printWord(word, found);
        letter = readLetter();
        if (!checkLetter(word, letter, found))
        {
            mistakes++;
            if (CHANCES - mistakes > 0)
                printf("Attack missed!\tRemaining attempts: %d\n", CHANCES - mistakes);
        }
        putchar('\n');
    } while (mistakes < CHANCES && !completeWord(word, found));

    if (mistakes == CHANCES)
        printf("\n\nOh no! The wild %s fled! (╯°□°)╯︵◓ Better try next time :(\n", word);
    else{
        printf("\n\nGotcha! %s was caught! (∩ᄑ_ᄑ)⊃*･｡*･ Congrats!\n\n", word);
        iChooseYou(n-1);
    }
    return 0;
}

int getint(const char message[], ... ) {
    int n, leave = 0;
    va_list ap;
        
    do {
        va_start(ap, message);
        vprintf(message, ap);
        va_end(ap);

        if ( scanf("%d",&n) != 1)
        {
            printf("\nIncorrect data\n");
            DELETE_BUFFER;
        }
        else
            leave = 1;
    } while (! leave);
    DELETE_BUFFER;
    return n;
}

char readLetter(void) {
    char letter;
    do {
        printf("Please enter a letter: ");
        letter = getchar();
        if(letter != '\n')
            DELETE_BUFFER;
    } while(letter < 'a' || letter > 'z');
    return letter;
}

int checkLetter(const char word[], char letter, short found[]) {
    int i, ok = 0;
    
    for (i = 0; word[i]; i++)
        if (word[i] == letter)
        {
            ok = 1;
            found[i] = 1;
        }
    return ok;
}

void printWord(const char word[], const short found[]) {
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

int completeWord(const char word[], const short found[]) {
    int i, complete = 1;

    for (i = 0; word[i] && complete; i++)
        if (found[i] == 0)
            complete = 0;

    return complete;
}
