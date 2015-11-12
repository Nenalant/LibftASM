section .text
	global _ft_islower

_ft_islower:
	cmp rdi, 'a'
		jge step2
	mov rax, 0
	ret

step2:
	cmp rdi, 'z'
 		jle ret_1
 	mov rax, 0
 	ret

ret_1:
 	mov rax, 1
 	ret