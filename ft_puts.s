section .data

null: db "(null)", 10

section .text
	global _ft_puts
	extern _ft_strlen

_ft_puts:
	mov rsi, rdi
	test rdi, rdi
		je _null
	call _ft_strlen
	mov rdx, rax
	mov rdi, 1
	mov rax, 0x2000004
	syscall
	cmp rax, -1
		je _err
	jmp _jpl
	ret

_jpl:
	mov rdi, 1
	lea rsi, [rel null + 6]
	mov rdx, 1
	mov rax, 0x2000004
	syscall
	cmp rax, -1
		je _err
	mov rax, 10
	ret

_err:
	ret

_null:
	mov rdi, 1
	lea rsi, [rel null]
	mov rdx, 7
	mov rax, 0x2000004
	syscall
	cmp rax, -1
		je _err
	mov rax, 10
	ret