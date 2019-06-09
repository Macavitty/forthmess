section .data
	newline_char: db 0xA

section .text

;-------------- string_length --------------
; # rdi is a pointer to the 1st char of the null-terminated string
; # rax contains the length of the string
string_length:
	xor eax, eax
	.count:
	mov dl, [rdi + rax]
	test dl, dl ; check if char is a null-terminator
	je .done
	inc rax
	jmp .count
	.done:
		ret

;-------------- print_string --------------
; # rdi is a pointer to the 1st char of the null-terminated string
print_string:
	call string_length
	mov rdx, rax ; rdx ← the length of our string
	mov rsi, rdi ; rsi ← string adress
	mov rax, 1 ; 'write'
	mov rdi, 1 ; stdout
	syscall
	ret

;-------------- print_char --------------
; # rdi contains a char to be printed
print_char:
	mov rdx, 1 ; rdx ← char length
	push rdi
	mov rsi, rsp ; rsi ← char adress
	mov rax, 1 ; 'write'
	mov rdi, 1 ; stdout
	syscall
	pop rdi ; restore stack
	ret

;-------------- print_newline --------------
print_newline:
	mov rsi, newline_char ; rsi ← char adress
	mov rdx, 1 ; rdx ← char length
	mov rax, 1 ; 'write'
	mov rdi, 1 ; stdout
	syscall
	ret

;-------------- print_uint --------------
; # rdi - an unsigned 8-byte integer to be outputed
print_uint:
	mov r10, rsp ; save stack pointer
	dec rsp
	mov [rsp], byte 0 ; null-terminator
	mov r11, 0xA
	mov rax, rdi ; the quotient
	.get_num:
		dec rsp
		xor rdx, rdx
		div r11
		add rdx, 48 ; to ascii
		mov [rsp], dl
		test rax, rax
		jnz .get_num
	.output:
		mov rdi, rsp
		call print_string
	mov rsp, r10
	ret

;-------------- print_int --------------
; # rdi - an signed 8-byte integer to be outputed
print_int:
	test rdi, rdi
	js .parse_neg
	call print_uint
	ret
	.parse_neg:
		mov r10, rdi
		mov rdi, '-'
		call print_char
		mov rdi, r10
		neg rdi
		call print_uint
	ret

;-------------- read_char --------------
; # rax contains character from stdin
read_char:
	xor eax, eax ; 'read'
	xor edi, edi ; stdin
	mov rdx, 1 ; rdx ← char length
	dec rsp
	mov rsi, rsp
	syscall
	cmp rax, 1 ; 'read' puts in rax the number of bytes read
	jnz .ret_zero
	mov eax, [rsp]
	inc rsp
	ret
	.ret_zero:
		xor eax, eax ; read can return not only 0 (eof) but -1 (on error)
		inc rsp
		ret

;-------------- read_word --------------
; # rdi - a buffer address
; # rsi - size
; # rax - 0 if the word is too big, otherwise - a buffer address
; # rdx - the numcer of chars read
read_word:
	mov r8, rsi ; buffer size
	xor r9, r9
	; counter
	mov r10, rdi
	.skip_space:
	call read_char
	cmp al, 0x20
	jz .skip_space
	cmp al, 0x10
	jz .skip_space
	cmp al, 0x9
	jz .skip_space
	test rax, rax
	jz .end_normal
	.read:
		cmp r9, r8
		ja .too_long
		mov byte[r10 + r9], al
		inc r9
		call read_char
		; check if the end reached
		cmp al, 0x20
		jz .end_normal
		cmp al, 0x10
		jz .end_normal
		cmp al, 0x9
		jz .end_normal
		test rax, rax
		jz .end_normal
		jmp .read
	.end_normal:
	mov byte[r10 + r9], 0 ; null-terminator
	mov rax, r10
	mov rdx, r9
	ret
	.too_long:
	xor rax, rax
	xor rdx, rdx
	ret
	;-------------- parse_uint --------------
	; # rdi - pointer to a string
	; # rax - parsed number
	; # rdx - the number of characters in the number
	parse_uint:
	mov r8, 10
	xor rcx, rcx
	xor eax, eax
	; accumulator
	xor rdx, rdx
	xor rsi, rsi
	.loop:
	mov sil, [rdi + rcx] ; contains current character
	cmp sil, 48
	; compare with 0
	jb .finish
	cmp sil, 57
	; compare with 9
	ja .finish
	inc rcx
	sub sil, 48
	mul r8
	; shift digits
	add rax, rsi
	jmp .loop
	.finish:
	mov rdx, rcx
	ret

;-------------- parse_int --------------
; # rdi - pointer to a string
; # rax - parsed number
; # rdx - the number of characters in the number
parse_int:
	xor r9, r9
	cmp byte[rdi], '-'
	jz .parse_neg
	call parse_uint
	ret
	.parse_neg:
		inc rdi
		call parse_uint
		neg rax
		inc rdx
		ret

;-------------- string_equals --------------
; # rdi - pointer to the first string
; # rsi - pointer to the second string
; # rax contains 1, if strings are equal, 0 - otherwise
string_equals:
	xor r8, r8 ; pointer to the first string
	xor r9, r9 ; pointer to the second string
	xor eax, eax ; answer
	.compare:
		mov r8b, byte[rdi]
		mov r9b, byte[rsi]
		inc rdi
		inc rsi
		test r8, r8
		jz .term_found
		; the end of the first string
		test r9, r9
		jz .false
		cmp r8, r9
		jz .compare
		jmp .false
	.term_found:
		test r9, r9
		jz .true
		jmp .false
	.true:
		inc al
		ret
	.false:
		ret

;-------------- string_copy --------------
; # rdi - pointer to a string
; # rsi - pointer to a target buffer
; # rdx - buffer’s length
; # rax - pointer to the target buffer address if the string fits in it, otherwise - 0
string_copy:
	push rdx
	call string_length
	pop rdx
	inc rax
	cmp rax, rdx ; check if string fits buffer
	jg .invalid
	xor r11, r11 ; counter = 0
	.mov_by_char:
		test rax, rax
		je .valid
		mov cl, byte[rdi + r11]
		mov byte[rsi + r11], cl
		dec rax
		inc r11
		jmp .mov_by_char
	.valid:
		mov rax, rsi
		nop
	.invalid:
		xor eax, eax
		ret