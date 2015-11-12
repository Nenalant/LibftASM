section .text
	global _ft_isprint

_ft_isprint:
	cmp rdi, ' '
		jge step2
	mov rax, 0
	ret

step2:
	cmp rdi, '~'
		jle do_ret1
	mov rax, 0
	ret

do_ret1:
	mov rax, 1
	ret