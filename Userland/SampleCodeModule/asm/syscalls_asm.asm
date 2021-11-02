GLOBAL readKeyboardSys
GLOBAL isKeyboardEmptySys
GLOBAL clearDisplaySys

section .text


readKeyboardSys:
  push rbp
  mov rbp, rsp

  mov rax, 0    ;ID read
  int 80h

  mov rsp, rbp
  pop rbp
  ret

isKeyboardEmptySys:
  push rbp
  mov rbp, rsp

  mov rax, 11    ;ID bufferEmpty
  int 80h

  mov rsp, rbp
  pop rbp
  ret

clearDisplaySys:
  push rbp
  mov rbp, rsp

  mov rax, 2    ;ID clear Display
  int 80h

  mov rsp, rbp
  pop rbp
  ret
