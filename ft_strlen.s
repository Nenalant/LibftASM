section .text
	global _ft_strlen

_ft_strlen:
	sub rcx, rcx
	not rcx
	sub al, al
	cld
	repne scasb
	not	rcx
	dec	rcx
	mov rax, rcx
	ret