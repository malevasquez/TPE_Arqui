#include <keyboardDriver.h>
#include <naiveConsole.h>
#include <stdint.h>
//deberiamos poner esto en un .h? para que quede mas prolijo
#define MAX_BUFFER 10
#define LEFT_SHIFT 42
#define RIGHT_SHIFT 54
#define RELEASED 128
#define CAPS_LOCK 58
#define ENTER 10
#define SPACE 32
#define KEY_COUNT 58 //CHEQUADO?

#define DEL 127
#define TAB 09
#define ESC 27



static char keyMap[][2] = {{0, 0}, {0, 0}, {'1', '!'}, {'2', '@'}, {'3', '#'}, {'4', '$'}, {'5', '%'}, {'6', '^'}, {'7', '&'},
{'8', '*'}, {'9', '('}, {'0', ')'}, {'-', '_'}, {'=', '+'}, {'\b', '\b'}, {'\t', '\t'}, {'q', 'Q'}, {'w', 'W'}, {'e', 'E'}, {'r', 'R'},
{'t', 'T'}, {'y', 'Y'}, {'u', 'U'}, {'i', 'I'}, {'o', 'O'}, {'p', 'P'}, {'[', '{'}, {']', '}'}, {'\n', '\n'}, {0, 0}, {'a', 'A'},
{'s', 'S'}, {'d', 'D'}, {'f', 'F'}, {'g', 'G'}, {'h', 'H'}, {'j', 'J'}, {'k', 'K'}, {'l', 'L'}, {';', ':'}, {'\'', '\"'}, {'`', '~'},
{0, 0}, {'\\', '|'}, {'z', 'Z'}, {'x', 'X'}, {'c', 'C'}, {'v', 'V'}, {'b', 'B'}, {'n', 'N'}, {'m', 'M'}, {',', '<'}, {'.', '>'},
{'/', '?'}, {0, 0}, {0, 0}, {0, 0}, {' ', ' '}, {0, 0}};

static char keyBuffer[MAX_BUFFER] = {0};
static unsigned int bufferSize = 0;
static unsigned int bsize = 0;

//flags: si una de las teclas se presiona, el flag se setea en 1
static uint64_t shift = 0;
static uint64_t capsLock = 0;

//detecta que tecla esta presionada
int keyboardHandler() {
    int scanCode;
    while (readKeyboard()) {
        scanCode = getScancode();
        switch(scanCode):
            //shift presionado -> prendo flag
            case LEFT_SHIFT:
            case RIGHT_SHIFT:
                shift = 1;
                break;
            //shift liberado -> apago el flag
            case LEFT_SHIFT + RELEASED:
            case RIGHT_SHIFT +  RELEASED:
                shift = 0;
                break;
            //mayuscula
            case CAPS_LOCK:
                capsLock = !capsLock;
                break;
            //CONSULTAR: considero ctrl, alt, etc? hasta donde
            //si no es una tecla especial
            default:
                if (scanCode >= 0 && scanCode < KEY_COUNT && pressCodes[scanCode][0] != 0) {
                    addToBuffer(keyToAscii(scanCode));
                    return 1;
                }
                break;
            }
    }
    return 0;
}

void addToBuffer(char c) {
    if (bufferSize <= MAX_BUFFER) {
        keyBuffer[bsize++] = c;
    }
}

char keyToAscii(int scancode) {
    /*
    si esta activado la mayuscula, toma el segundo valor del caracter en el keyMap
    en caso contrario, toma el primero/izquierdo
    keymap tiene forma {a, A}
    */
    int capsActivated = (capsLock || shift)? 1 : 0;
    return keyMap[scancode][capsActivated];
}
