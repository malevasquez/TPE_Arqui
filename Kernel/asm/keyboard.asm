GLOBAL readKeyboard
GLOBAL getScancode

section .text
; -----------------------------------
; keyboardActivated: detecta si hay un codigo de teclado en el buffer
;                    retorna 1 de haber, 0 si no.
; -----------------------------------
keyboardActivated:
    mov rax, 0
    in al, 64h
    and al, 01h
    ret

; -----------------------------------
; getScancode: retorna el codigo de teclado ("scancode") del buffer.
; -----------------------------------
getScancode:
    mov rax, 0
    in al, 60h
    ret
