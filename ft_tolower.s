section .text
	global _ft_tolower

_ft_tolower:
	cmp rdi, 'A'
		jge step2
	mov rax, rdi
	ret

step2:
	cmp rdi, 'Z'
 		jle do_low
 	mov rax, rdi
 	ret

 do_low:
 	add rdi, 32
 	mov rax, rdi
 	ret