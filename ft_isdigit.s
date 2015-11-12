section .text
	global _ft_isdigit

_ft_isdigit:
	cmp rdi, '9'
		jle step2
	mov rax, 0
	ret

step2:
	cmp rdi, '0'
		jge do_ret1
	mov rax, 0
	ret

do_ret1:
	mov rax, 1
	ret