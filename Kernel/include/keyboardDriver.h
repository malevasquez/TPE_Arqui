/**
 * Handler que se llama desde syscall para la lectura de teclado.
 * Retorna 1 si lo pudo leer correctamente, 0 si no.
 */
int keyboardHandler();
/**
 * Detecta si hay un codigo de teclado en el buffer.
 */
extern int keyboardActivated();

extern unsigned char getScancode();
