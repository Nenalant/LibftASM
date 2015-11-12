section .text
	global _ft_bzero

_ft_bzero:	
	xor rax, rax

check:
	cmp rdi, 0
	je end
	cmp rsi, 0
	je end
	stosb
	dec rsi
	jmp check

end:
	ret