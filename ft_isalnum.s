section .text
	global _ft_isalnum

_ft_isalnum:
	cmp rdi, '0'
		jl do_ret0
	cmp rdi, 'z'
		jle step2
	mov rax, 0
	ret

step2:
	cmp rdi, '9'
		jle do_ret1
	cmp rdi, 'A'
		jge step3
	mov rax, 0
	ret

step3:
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