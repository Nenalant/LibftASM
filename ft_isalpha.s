section .text
	global _ft_isalpha

_ft_isalpha:
	cmp rdi, 'A'
		jl do_ret0
	cmp rdi, 'z'
		jle step2
	mov rax, 0
	ret

step2:
	cmp rdi, 'Z'
		jle do_ret1
	cmp rdi, 'a'
		jge do_ret1
	mov rax, 0
	ret

do_ret0:
	mov rax, 0
	ret

do_ret1:
	mov rax, 1
	ret