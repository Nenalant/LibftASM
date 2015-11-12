section .text
	global _ft_strcat
	extern _ft_strlen
	extern _ft_strcpy

_ft_strcat:
	push rdi
	push rsi
	push rdi
	call _ft_strlen
	pop rdi
	add rdi, rax
	pop rsi
	call _ft_strcpy
	pop rax
	ret
