	.file	"helloworld.c"
	.section	.rodata
	.align 2
.LC0:
	.string	"Hello World!\n"
	.section	".text"
	.align 2
	.globl main
	.type	main, @function
main:
	stwu 1,-32(1)
	mflr 0
	stw 31,28(1)
	stw 0,36(1)
	mr 31,1
	lis 9,.LC0@ha
	la 3,.LC0@l(9)
	crxor 6,6,6
	bl printf
	li 0,0
	mr 3,0
	lwz 11,0(1)
	lwz 0,4(11)
	mtlr 0
	lwz 31,-4(11)
	mr 1,11
	blr
	.size	main, .-main
	.section	.note.GNU-stack,"",@progbits
	.ident	"GCC: (GNU) 3.3.4 (Debian)"
