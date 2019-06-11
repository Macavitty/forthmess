global _start

%define pc r15
%define w r14
%define rstack r13

section .text
%include "src/lib.inc"		;do not remove src/
%include "src/macro.inc"
%include "src/word.inc"

section .bss
resq 1023
rstack_str: resq 1
usr_mem: resq 65536

section .data
last_word: dq _lw
dp: dq usr_mem
stack_str:  dq 0
 
section .text
_start: 
    mov rstack, rstack_str
    mov [stack_str], rsp
    mov pc, forth_init

next:                  
    mov w, pc
    add pc, 8
    mov w, [w]
    jmp [w]
