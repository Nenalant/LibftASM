section	.text
	global _ft_isascii

_ft_isascii:
	cmp rdi, 0
		jge step2
	mov rax, 0
	ret

step2:
	cmp rdi, 127
		jle	do_ret1
	mov rax, 0
	ret

do_ret1:
	mov rax, 1
	ret