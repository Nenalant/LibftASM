section .text
	global _ft_toupper

_ft_toupper:
	cmp rdi, 'a'
		jge step2
	mov rax, rdi
	ret

step2:
	cmp rdi, 'z'
 		jle do_upp
 	mov rax, rdi
 	ret

 do_upp:
 	sub rdi, 32
 	mov rax, rdi
 	ret