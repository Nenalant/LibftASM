section .bss
	buffer resb 1024

section .text
	global _ft_cat
	extern _fcntl

_ft_cat:
	push rdi
	push rsi
	push rdx
	mov rsi, 1
	mov rax, 55
	syscall
	cmp rax, 0
	jne _ret
	lea rsi, [rel buffer]
	jmp _read

_read:
	mov rdx, 1024
	mov rax, 0x2000003
	syscall
	cmp rax, -1
		je _ret
	cmp rax, 0
		jg _write
	jmp _ret

_write:
	push rdi
	mov rdx, rax
	mov rdi, 1
	mov rax, 0x2000004
	syscall
	pop rdi
	cmp rax, -1
		jne _read
	jmp _ret

_ret:
	pop rdx
	pop rsi
	pop rdi
	ret
