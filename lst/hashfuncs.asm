	.file	"hashfuncs.cpp"
	.intel_syntax noprefix
	.text
	.p2align 4
	.globl	_Z10hash_constPKhm
	.type	_Z10hash_constPKhm, @function
_Z10hash_constPKhm:
.LFB82:
	.cfi_startproc
	endbr64
	mov	eax, 19
	ret
	.cfi_endproc
.LFE82:
	.size	_Z10hash_constPKhm, .-_Z10hash_constPKhm
	.p2align 4
	.globl	_Z23hash_first_letter_asciiPKhm
	.type	_Z23hash_first_letter_asciiPKhm, @function
_Z23hash_first_letter_asciiPKhm:
.LFB83:
	.cfi_startproc
	endbr64
	movzx	eax, BYTE PTR [rdi]
	ret
	.cfi_endproc
.LFE83:
	.size	_Z23hash_first_letter_asciiPKhm, .-_Z23hash_first_letter_asciiPKhm
	.p2align 4
	.globl	_Z13hash_word_lenPKhm
	.type	_Z13hash_word_lenPKhm, @function
_Z13hash_word_lenPKhm:
.LFB84:
	.cfi_startproc
	endbr64
	mov	rax, rsi
	ret
	.cfi_endproc
.LFE84:
	.size	_Z13hash_word_lenPKhm, .-_Z13hash_word_lenPKhm
	.p2align 4
	.globl	_Z13hash_checksumPKhm
	.type	_Z13hash_checksumPKhm, @function
_Z13hash_checksumPKhm:
.LFB85:
	.cfi_startproc
	endbr64
	mov	rdx, rdi
	lea	rcx, -1[rsi]
	test	rsi, rsi
	je	.L11
	cmp	rcx, 14
	jbe	.L12
	pxor	xmm6, xmm6
	pxor	xmm5, xmm5
	pxor	xmm4, xmm4
	mov	rax, rdi
	mov	rdi, rsi
	pxor	xmm3, xmm3
	and	rdi, -16
	add	rdi, rdx
	.p2align 4,,10
	.p2align 3
.L8:
	movdqu	xmm1, XMMWORD PTR [rax]
	add	rax, 16
	movdqa	xmm0, xmm1
	punpckhbw	xmm1, xmm5
	punpcklbw	xmm0, xmm5
	movdqa	xmm2, xmm1
	punpckhwd	xmm1, xmm4
	movdqa	xmm7, xmm0
	punpckhwd	xmm0, xmm4
	punpcklwd	xmm2, xmm4
	movdqa	xmm8, xmm0
	punpcklwd	xmm7, xmm4
	punpckhdq	xmm0, xmm3
	punpckldq	xmm8, xmm3
	paddq	xmm0, xmm8
	movdqa	xmm8, xmm7
	punpckhdq	xmm7, xmm3
	punpckldq	xmm8, xmm3
	paddq	xmm7, xmm8
	paddq	xmm0, xmm7
	movdqa	xmm7, xmm2
	punpckhdq	xmm2, xmm3
	punpckldq	xmm7, xmm3
	paddq	xmm2, xmm7
	movdqa	xmm7, xmm1
	punpckhdq	xmm1, xmm3
	punpckldq	xmm7, xmm3
	paddq	xmm1, xmm6
	paddq	xmm2, xmm7
	paddq	xmm0, xmm2
	movdqa	xmm6, xmm0
	paddq	xmm6, xmm1
	cmp	rax, rdi
	jne	.L8
	movdqa	xmm0, xmm6
	mov	rdi, rsi
	psrldq	xmm0, 8
	and	rdi, -16
	paddq	xmm6, xmm0
	add	rdx, rdi
	sub	rcx, rdi
	movq	rax, xmm6
	cmp	rsi, rdi
	je	.L56
.L7:
	movzx	esi, BYTE PTR [rdx]
	add	rax, rsi
	test	rcx, rcx
	je	.L5
	movzx	esi, BYTE PTR 1[rdx]
	add	rax, rsi
	cmp	rcx, 1
	je	.L5
	movzx	esi, BYTE PTR 2[rdx]
	add	rax, rsi
	cmp	rcx, 2
	je	.L5
	movzx	esi, BYTE PTR 3[rdx]
	add	rax, rsi
	cmp	rcx, 3
	je	.L5
	movzx	esi, BYTE PTR 4[rdx]
	add	rax, rsi
	cmp	rcx, 4
	je	.L5
	movzx	esi, BYTE PTR 5[rdx]
	add	rax, rsi
	cmp	rcx, 5
	je	.L5
	movzx	esi, BYTE PTR 6[rdx]
	add	rax, rsi
	cmp	rcx, 6
	je	.L5
	movzx	esi, BYTE PTR 7[rdx]
	add	rax, rsi
	cmp	rcx, 7
	je	.L5
	movzx	esi, BYTE PTR 8[rdx]
	add	rax, rsi
	cmp	rcx, 8
	je	.L5
	movzx	esi, BYTE PTR 9[rdx]
	add	rax, rsi
	cmp	rcx, 9
	je	.L5
	movzx	esi, BYTE PTR 10[rdx]
	add	rax, rsi
	cmp	rcx, 10
	je	.L5
	movzx	esi, BYTE PTR 11[rdx]
	add	rax, rsi
	cmp	rcx, 11
	je	.L5
	movzx	esi, BYTE PTR 12[rdx]
	add	rax, rsi
	cmp	rcx, 12
	je	.L5
	movzx	esi, BYTE PTR 13[rdx]
	add	rax, rsi
	cmp	rcx, 13
	je	.L5
	movzx	edx, BYTE PTR 14[rdx]
	add	rax, rdx
	ret
	.p2align 4,,10
	.p2align 3
.L11:
	xor	eax, eax
.L5:
	ret
.L12:
	xor	eax, eax
	jmp	.L7
.L56:
	ret
	.cfi_endproc
.LFE85:
	.size	_Z13hash_checksumPKhm, .-_Z13hash_checksumPKhm
	.p2align 4
	.globl	_Z12hash_rol_xorPKhm
	.type	_Z12hash_rol_xorPKhm, @function
_Z12hash_rol_xorPKhm:
.LFB87:
	.cfi_startproc
	endbr64
	test	rsi, rsi
	je	.L60
	add	rsi, rdi
	xor	eax, eax
	.p2align 4,,10
	.p2align 3
.L59:
#APP
# 39 "src/hashfuncs.cpp" 1
	rol rax, 1
# 0 "" 2
#NO_APP
	movzx	edx, BYTE PTR [rdi]
	add	rdi, 1
	xor	rax, rdx
	cmp	rsi, rdi
	jne	.L59
	ret
	.p2align 4,,10
	.p2align 3
.L60:
	xor	eax, eax
	ret
	.cfi_endproc
.LFE87:
	.size	_Z12hash_rol_xorPKhm, .-_Z12hash_rol_xorPKhm
	.p2align 4
	.globl	_Z12hash_ror_xorPKhm
	.type	_Z12hash_ror_xorPKhm, @function
_Z12hash_ror_xorPKhm:
.LFB89:
	.cfi_startproc
	endbr64
	test	rsi, rsi
	je	.L65
	add	rsi, rdi
	xor	eax, eax
	.p2align 4,,10
	.p2align 3
.L64:
#APP
# 61 "src/hashfuncs.cpp" 1
	ror rax, 1
# 0 "" 2
#NO_APP
	movzx	edx, BYTE PTR [rdi]
	add	rdi, 1
	xor	rax, rdx
	cmp	rsi, rdi
	jne	.L64
	ret
	.p2align 4,,10
	.p2align 3
.L65:
	xor	eax, eax
	ret
	.cfi_endproc
.LFE89:
	.size	_Z12hash_ror_xorPKhm, .-_Z12hash_ror_xorPKhm
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
