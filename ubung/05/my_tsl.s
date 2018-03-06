	.text
	.p2align 4,,15
	.global my_tsl
	.type	my_tsl, @function

my_tsl:
	xor		%rax,%rax
	inc		%al
	lock	xchg %al,(%rdi)
	retq
