GLOBAL _cli
GLOBAL _sti
GLOBAL _hlt
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq80Handler
GLOBAL _exception00Handler
GLOBAL _exception06Handler
GLOBAL saveInitialConditions

EXTERN irqDispatcher
EXTERN exceptionDispatcher

SECTION .text
;----------------------------------------
; popState: popea todos los registros
; pushState: pushea todos los registros
;----------------------------------------
%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro


;----------------------------------------
; irqHandlerMaster: llama a irqDispatcher con el numero de IRQ para que maneje la interrupcion
; exceptionHandler: analogo irqHandlerMaster
;----------------------------------------
%macro irqHandlerMaster 1
    pushState
    mov rdi, %1 ; pasaje de parámetro
    mov rsi, rsp; pasaje del "vector" de registros
    call irqDispatcher

    ; signal pic EOI (End of Interrupt)
    mov al, 20h
    out 20h, al

    popState
    iretq
%endmacro

%macro exceptionHandler 1
    pushState

	mov rdi, %1 ; pasaje de parametro
	mov rsi, rsp ; pasaje del "vector" de registros
	call exceptionDispatcher

    mov rax, [initialConditions] ; rsp
	mov [rsp + 18*8], rax
	mov rax, [initialConditions + 8] ; rip
	mov [rsp + 15*8], rax

	popState
	iretq
%endmacro

_cli:
	cli
	ret

_sti:
	sti
	ret

_hlt:
	hlt
	ret

picMasterMask:
    push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    mov rsp, rbp
    pop rbp
    retn

picSlaveMask:
    push rbp
    mov rbp, rsp
    mov ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    mov rsp, rbp
    pop rbp
    retn

;timer tick
_irq00Handler:
    irqHandlerMaster 0

;keyboard
_irq01Handler:
    irqHandlerMaster 1

;int 80h - syscalls
_irq80Handler:
    irqHandlerMaster 80

;zero Division Exception
_exception00Handler:
    exceptionHandler 0

;invalid OpCode Exception
_exception06Handler:
    exceptionHandler 6

;---------------------------------------------------------
; Save Initial Registers (to restore in case of exception)
;---------------------------------------------------------
saveInitialConditions:
    mov rax, rsp
    mov [initialConditions], rax
    mov rax, rdi
    mov [initialConditions + 8], rax
    ret
;---------------------------------------------------------


SECTION .bss
    initialConditions resb 16   ; rsp: primeros 8 bits - rip: segundos 8 bits
