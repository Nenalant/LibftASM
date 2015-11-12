section .text
	global _ft_memcpy

_ft_memcpy:
	mov rax, rsi
	mov rcx, rdx 
	mov rdx, rdi
	rep movsb
	mov rax, rdx
	ret