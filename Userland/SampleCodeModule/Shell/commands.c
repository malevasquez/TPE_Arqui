#include <commands.h>

extern void throwOpcode();

// Help command builtin
void openHelp() {
    printf("Comandos Disponibles\n");
    printf("DIVZERO - Excepcion: Division por cero\n");
    printf("OPCODE- Excepcion: Codigo de operacion invalido\n");
    printf("INFOREG - Imprime en pantalla el valor de todos los registros\n");
    printf("PRINTMEM - Realiza un volcado de memoria de 32 bytes a partir de una direccion recibida como argumento\n");
    printf("DATETIME - Despliega dia y hora del sistema\n");
    printf("4IN1 - Divide la pantalla en cuatro ventanas con diferentes funcionalidades en cada una\n");
    printf("EXIT - Salir de la shell");
    printf("\n");
    printf("\n");
    return;
}

void throwDivZero() {
    int a = 3;
    int b = 0;
    a /= b;
}
