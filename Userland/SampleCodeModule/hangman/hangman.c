#include <stdio.h>
#include <stdlib.h>
#include "hangman.h"

//Cantidad de errores permitidos
#define CHANCES 8

//Longitud maxima que puede tener una palabra
#define WORDLEN 20

int main(void) {
    char dictionary[][WORDLEN] = {"bulbasaur", "charmander", "cubone", "cyndaquil", "eevee", "gastly", "geodude", "growlithe", "jigglypuff", "meowth", "pidgey", "pikachu", "poliwhirl", "ponyta", "cefalopodo", "psyduck", "rattata", "snorlax", "squirtle", "wobbuffet"};
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

    printf("\nGotta catch 'em all! Welcome to pokemon-hangman, the game where you have to guess the pokemon's name in order to win!\n");
    printf("You have maximum 6 mistakes allowed :o Remember that all alphabet are in lower case\n");
    printf("\nA wild pokemon has appeared! Good luck :)\n");

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
        printf("\n\nOh no! The wild %s fled! Better try next time :(\n", word);
    else
        printf("\n\nGotcha! %s was caught! Congrats!\n\n", word);

    return 0;
}
