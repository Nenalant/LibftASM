section .text
	global _ft_isupper

_ft_isupper:
	cmp rdi, 'A'
		jge step2
	mov rax, 0
	ret

step2:
	cmp rdi, 'Z'
 		jle ret_1
 	mov rax, 0
 	ret

 ret_1:
 	mov rax, 1
 	ret