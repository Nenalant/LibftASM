section .bss
	onec resb 1

section .text
	global _ft_putchar

_ft_putchar:
	lea rsi, [rel onec]
	mov [rsi], dil
	mov rdi, 1
	mov rdx, 1
	mov rax, 0x2000004
	syscall
	ret