GLOBAL _syscall
GLOBAL throwOpcode
GLOBAL SystemCall02

;------------------------------------------------------------
;                       USERLAND
;------------------------------------------------------------
section .text
;------------------------------------------------------------
; syscall recibe argumentos variables.
;------------------------------------------------------------
_syscall:
    int 80h
    ret
;------------------------------------------------------------

throwOpcode:
    ud2
    ret

SystemCall02:
    mov rax, 2
    jmp _syscall
