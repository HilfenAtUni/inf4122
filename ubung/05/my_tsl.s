	.text
	.p2align 4,,15
	.global my_tsl
	.type	my_tsl, @function

my_tsl:
	xor		%rax,%rax		/* using 64-bit general-purpose register, and use
								xor to set it to 0 */
	inc		%al				/* increase value in 8-bit general-purpose register
								al */
	lock	xchg %al,(%rdi)	/* exchange the value of register rdi and al and
								use prefix 'lock' to lock the register */
	retq					/* gleich wie "popq %rip" */
