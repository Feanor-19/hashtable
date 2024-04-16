	.file	"testing.cpp"
	.intel_syntax noprefix
	.text
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"TestingStatus Distribution_ctor(Distribution*, size_t)"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"src/testing.cpp"
.LC2:
	.string	"distr"
	.text
	.p2align 4
	.type	_Z17Distribution_ctorP12Distributionm.part.0, @function
_Z17Distribution_ctorP12Distributionm.part.0:
.LFB1182:
	.cfi_startproc
	push	rax
	.cfi_def_cfa_offset 16
	pop	rax
	.cfi_def_cfa_offset 8
	lea	rcx, .LC0[rip]
	mov	edx, 108
	lea	rsi, .LC1[rip]
	lea	rdi, .LC2[rip]
	sub	rsp, 8
	.cfi_def_cfa_offset 16
	call	__assert_fail@PLT
	.cfi_endproc
.LFE1182:
	.size	_Z17Distribution_ctorP12Distributionm.part.0, .-_Z17Distribution_ctorP12Distributionm.part.0
	.section	.rodata.str1.8
	.align 8
.LC3:
	.string	"TestingStatus run_hash_func_test(hash_func_t, WordsList, Distribution*, size_t)"
	.section	.rodata.str1.1
.LC4:
	.string	"hash_func"
.LC5:
	.string	"out_distr"
	.text
	.p2align 4
	.globl	_Z18run_hash_func_testPFmPKhmE9WordsListP12Distributionm
	.type	_Z18run_hash_func_testPFmPKhmE9WordsListP12Distributionm, @function
_Z18run_hash_func_testPFmPKhmE9WordsListP12Distributionm:
.LFB1028:
	.cfi_startproc
	endbr64
	push	r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	push	r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	push	r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	push	rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	push	rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	sub	rsp, 32
	.cfi_def_cfa_offset 80
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR 24[rsp], rax
	xor	eax, eax
	mov	r12, QWORD PTR 88[rsp]
	test	rdi, rdi
	je	.L19
	mov	r14, rsi
	test	rsi, rsi
	je	.L20
	mov	rbp, rsp
	mov	rsi, rdx
	mov	rdx, rdi
	mov	QWORD PTR [rsp], 0
	mov	rdi, rbp
	mov	r13d, 2
	mov	QWORD PTR 8[rsp], 0
	mov	QWORD PTR 16[rsp], 0
	call	_Z14hashtable_ctorP9HashtablemPFmPKhmE@PLT
	test	eax, eax
	jne	.L4
	mov	r13, QWORD PTR 80[rsp]
	xor	ebx, ebx
	test	r12, r12
	je	.L12
	.p2align 4,,10
	.p2align 3
.L11:
	mov	rsi, QWORD PTR 0[r13+rbx*8]
	mov	rdi, rbp
	add	rbx, 1
	call	_Z16hashtable_insertP9HashtablePKc@PLT
	cmp	r12, rbx
	jne	.L11
.L12:
	mov	rsi, QWORD PTR [r14]
	mov	rdi, rbp
	call	_Z26hashtable_get_distributionP9HashtablePm@PLT
	mov	r13d, eax
	test	eax, eax
	jne	.L21
	mov	rdi, rbp
	call	_Z14hashtable_dtorP9Hashtable@PLT
.L4:
	mov	rax, QWORD PTR 24[rsp]
	sub	rax, QWORD PTR fs:40
	jne	.L22
	add	rsp, 32
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	mov	eax, r13d
	pop	rbx
	.cfi_def_cfa_offset 40
	pop	rbp
	.cfi_def_cfa_offset 32
	pop	r12
	.cfi_def_cfa_offset 24
	pop	r13
	.cfi_def_cfa_offset 16
	pop	r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L21:
	.cfi_restore_state
	mov	rdi, rbp
	mov	r13d, 2
	call	_Z14hashtable_dtorP9Hashtable@PLT
	jmp	.L4
.L22:
	call	__stack_chk_fail@PLT
.L20:
	lea	rcx, .LC3[rip]
	mov	edx, 82
	lea	rsi, .LC1[rip]
	lea	rdi, .LC5[rip]
	call	__assert_fail@PLT
.L19:
	lea	rcx, .LC3[rip]
	mov	edx, 81
	lea	rsi, .LC1[rip]
	lea	rdi, .LC4[rip]
	call	__assert_fail@PLT
	.cfi_endproc
.LFE1028:
	.size	_Z18run_hash_func_testPFmPKhmE9WordsListP12Distributionm, .-_Z18run_hash_func_testPFmPKhmE9WordsListP12Distributionm
	.section	.rodata.str1.8
	.align 8
.LC6:
	.string	"TestingStatus run_all_hash_func_tests(WordsList, const char*, size_t)"
	.section	.rodata.str1.1
.LC7:
	.string	"out_dir"
.LC8:
	.string	"Testing %s...\n"
	.section	.rodata.str1.8
	.align 8
.LC9:
	.string	"TestingStatus write_distr_into_file(Distribution, const char*, const char*)"
	.section	.rodata.str1.1
.LC10:
	.string	"func_name"
.LC11:
	.string	"w"
.LC12:
	.string	"%lu\n"
.LC13:
	.string	"Done!"
	.text
	.p2align 4
	.globl	_Z23run_all_hash_func_tests9WordsListPKcm
	.type	_Z23run_all_hash_func_tests9WordsListPKcm, @function
_Z23run_all_hash_func_tests9WordsListPKcm:
.LFB1027:
	.cfi_startproc
	endbr64
	push	r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	push	r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	push	r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	push	r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	push	rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	push	rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	sub	rsp, 168
	.cfi_def_cfa_offset 224
	mov	QWORD PTR 8[rsp], rdi
	mov	QWORD PTR 16[rsp], rsi
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR 152[rsp], rax
	xor	eax, eax
	test	rdi, rdi
	je	.L43
	mov	esi, 511
	call	mkdir@PLT
	mov	rbx, QWORD PTR 16[rsp]
	mov	esi, 8
	mov	rdi, rbx
	call	calloc@PLT
	mov	QWORD PTR 32[rsp], rax
	test	rax, rax
	je	.L33
	lea	rax, 32[rsp]
	mov	QWORD PTR 40[rsp], rbx
	lea	r13, _ZL15HASH_FUNCS_LIST[rip]
	mov	QWORD PTR 24[rsp], rax
	lea	rax, 48[rsp]
	lea	r12, .LC12[rip]
	mov	QWORD PTR [rsp], rax
.L31:
	mov	r14, QWORD PTR 8[r13]
	lea	rsi, .LC8[rip]
	mov	edi, 1
	xor	eax, eax
	mov	rdx, r14
	call	__printf_chk@PLT
	push	QWORD PTR 248[rsp]
	.cfi_def_cfa_offset 232
	mov	rdi, QWORD PTR 0[r13]
	push	QWORD PTR 248[rsp]
	.cfi_def_cfa_offset 240
	push	QWORD PTR 248[rsp]
	.cfi_def_cfa_offset 248
	push	QWORD PTR 248[rsp]
	.cfi_def_cfa_offset 256
	mov	rdx, QWORD PTR 48[rsp]
	mov	rsi, QWORD PTR 56[rsp]
	call	_Z18run_hash_func_testPFmPKhmE9WordsListP12Distributionm
	mov	rbp, QWORD PTR 64[rsp]
	mov	rbx, QWORD PTR 72[rsp]
	add	rsp, 32
	.cfi_def_cfa_offset 224
	test	r14, r14
	je	.L44
	mov	r15, QWORD PTR 8[rsp]
	mov	rdi, QWORD PTR [rsp]
	mov	edx, 100
	mov	rsi, r15
	call	strncpy@PLT
	mov	rdi, r15
	call	strlen@PLT
	cmp	BYTE PTR 47[rsp+rax], 47
	je	.L27
	mov	BYTE PTR 48[rsp+rax], 47
	add	rax, 1
.L27:
	mov	r15, QWORD PTR [rsp]
	mov	edx, 100
	mov	rsi, r14
	sub	rdx, rax
	lea	rdi, [r15+rax]
	call	strncpy@PLT
	mov	rdi, r15
	lea	rsi, .LC11[rip]
	call	fopen@PLT
	mov	r15, rax
	test	rax, rax
	je	.L28
	test	rbx, rbx
	je	.L29
	xor	r14d, r14d
	.p2align 4,,10
	.p2align 3
.L30:
	mov	rcx, QWORD PTR 0[rbp+r14*8]
	mov	rdx, r12
	mov	esi, 1
	mov	rdi, r15
	xor	eax, eax
	add	r14, 1
	call	__fprintf_chk@PLT
	cmp	rbx, r14
	jne	.L30
.L29:
	mov	rdi, r15
	call	fclose@PLT
.L28:
	lea	rdi, .LC13[rip]
	add	r13, 16
	call	puts@PLT
	lea	rax, _ZL15HASH_FUNCS_LIST[rip+112]
	cmp	r13, rax
	jne	.L31
	mov	rdi, rbp
	call	free@PLT
	xor	eax, eax
.L23:
	mov	rdx, QWORD PTR 152[rsp]
	sub	rdx, QWORD PTR fs:40
	jne	.L45
	add	rsp, 168
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	pop	rbx
	.cfi_def_cfa_offset 48
	pop	rbp
	.cfi_def_cfa_offset 40
	pop	r12
	.cfi_def_cfa_offset 32
	pop	r13
	.cfi_def_cfa_offset 24
	pop	r14
	.cfi_def_cfa_offset 16
	pop	r15
	.cfi_def_cfa_offset 8
	ret
.L43:
	.cfi_restore_state
	lea	rcx, .LC6[rip]
	mov	edx, 56
	lea	rsi, .LC1[rip]
	lea	rdi, .LC7[rip]
	call	__assert_fail@PLT
.L45:
	call	__stack_chk_fail@PLT
.L44:
	lea	rcx, .LC9[rip]
	mov	edx, 35
	lea	rsi, .LC1[rip]
	lea	rdi, .LC10[rip]
	call	__assert_fail@PLT
.L33:
	mov	eax, 1
	jmp	.L23
	.cfi_endproc
.LFE1027:
	.size	_Z23run_all_hash_func_tests9WordsListPKcm, .-_Z23run_all_hash_func_tests9WordsListPKcm
	.p2align 4
	.globl	_Z17Distribution_ctorP12Distributionm
	.type	_Z17Distribution_ctorP12Distributionm, @function
_Z17Distribution_ctorP12Distributionm:
.LFB1029:
	.cfi_startproc
	endbr64
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	push	rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	sub	rsp, 8
	.cfi_def_cfa_offset 32
	test	rdi, rdi
	je	.L51
	mov	rbx, rdi
	mov	rdi, QWORD PTR [rdi]
	mov	rbp, rsi
	call	free@PLT
	mov	esi, 8
	mov	rdi, rbp
	call	calloc@PLT
	mov	QWORD PTR [rbx], rax
	test	rax, rax
	je	.L49
	mov	QWORD PTR 8[rbx], rbp
	xor	eax, eax
.L46:
	add	rsp, 8
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	pop	rbx
	.cfi_def_cfa_offset 16
	pop	rbp
	.cfi_def_cfa_offset 8
	ret
.L51:
	.cfi_restore_state
	call	_Z17Distribution_ctorP12Distributionm.part.0
.L49:
	mov	eax, 1
	jmp	.L46
	.cfi_endproc
.LFE1029:
	.size	_Z17Distribution_ctorP12Distributionm, .-_Z17Distribution_ctorP12Distributionm
	.section	.rodata.str1.8
	.align 8
.LC14:
	.string	"void Distribution_dtor(Distribution*)"
	.text
	.p2align 4
	.globl	_Z17Distribution_dtorP12Distribution
	.type	_Z17Distribution_dtorP12Distribution, @function
_Z17Distribution_dtorP12Distribution:
.LFB1030:
	.cfi_startproc
	endbr64
	push	rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	test	rdi, rdi
	je	.L55
	mov	rbx, rdi
	mov	rdi, QWORD PTR [rdi]
	call	free@PLT
	mov	QWORD PTR 8[rbx], 0
	pop	rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L55:
	.cfi_restore_state
	lea	rcx, .LC14[rip]
	mov	edx, 122
	lea	rsi, .LC1[rip]
	lea	rdi, .LC2[rip]
	call	__assert_fail@PLT
	.cfi_endproc
.LFE1030:
	.size	_Z17Distribution_dtorP12Distribution, .-_Z17Distribution_dtorP12Distribution
	.p2align 4
	.globl	_Z20run_search_perf_test9WordsListS_m
	.type	_Z20run_search_perf_test9WordsListS_m, @function
_Z20run_search_perf_test9WordsListS_m:
.LFB1031:
	.cfi_startproc
	endbr64
	push	r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	mov	rsi, rdi
	push	r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	mov	r14d, 2
	push	r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	push	r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	push	rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	push	rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	sub	rsp, 40
	.cfi_def_cfa_offset 96
	mov	rdx, QWORD PTR _Z12hash_murmur3PKhm@GOTPCREL[rip]
	mov	r15, rsp
	mov	rbp, QWORD PTR 104[rsp]
	mov	r12, QWORD PTR 136[rsp]
	mov	rax, QWORD PTR fs:40
	mov	QWORD PTR 24[rsp], rax
	xor	eax, eax
	mov	rdi, r15
	mov	QWORD PTR [rsp], 0
	mov	QWORD PTR 8[rsp], 0
	mov	QWORD PTR 16[rsp], 0
	call	_Z14hashtable_ctorP9HashtablemPFmPKhmE@PLT
	test	eax, eax
	jne	.L56
	mov	r13, QWORD PTR 96[rsp]
	mov	r14d, eax
	xor	ebx, ebx
	test	rbp, rbp
	je	.L62
.L61:
	mov	rsi, QWORD PTR 0[r13+rbx*8]
	mov	rdi, r15
	add	rbx, 1
	call	_Z16hashtable_insertP9HashtablePKc@PLT
	cmp	rbx, rbp
	jne	.L61
.L62:
	mov	r13d, 100
	test	r12, r12
	je	.L60
	.p2align 4,,10
	.p2align 3
.L59:
	mov	rbp, QWORD PTR 128[rsp]
	xor	ebx, ebx
	.p2align 4,,10
	.p2align 3
.L63:
	mov	rsi, QWORD PTR 0[rbp+rbx*8]
	mov	rdi, r15
	add	rbx, 1
	call	_Z14hashtable_findP9HashtablePKc@PLT
	cmp	r12, rbx
	jne	.L63
	sub	r13, 1
	jne	.L59
.L60:
	mov	rdi, r15
	call	_Z14hashtable_dtorP9Hashtable@PLT
.L56:
	mov	rax, QWORD PTR 24[rsp]
	sub	rax, QWORD PTR fs:40
	jne	.L75
	add	rsp, 40
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	mov	eax, r14d
	pop	rbx
	.cfi_def_cfa_offset 48
	pop	rbp
	.cfi_def_cfa_offset 40
	pop	r12
	.cfi_def_cfa_offset 32
	pop	r13
	.cfi_def_cfa_offset 24
	pop	r14
	.cfi_def_cfa_offset 16
	pop	r15
	.cfi_def_cfa_offset 8
	ret
.L75:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE1031:
	.size	_Z20run_search_perf_test9WordsListS_m, .-_Z20run_search_perf_test9WordsListS_m
	.section	.rodata.str1.1
.LC15:
	.string	"hash_const"
.LC16:
	.string	"hash_first_letter_ascii"
.LC17:
	.string	"hash_word_len"
.LC18:
	.string	"hash_checksum"
.LC19:
	.string	"hash_rol_xor"
.LC20:
	.string	"hash_ror_xor"
.LC21:
	.string	"hash_murmur3"
	.section	.data.rel.ro,"aw"
	.align 32
	.type	_ZL15HASH_FUNCS_LIST, @object
	.size	_ZL15HASH_FUNCS_LIST, 112
_ZL15HASH_FUNCS_LIST:
	.quad	_Z10hash_constPKhm
	.quad	.LC15
	.quad	_Z23hash_first_letter_asciiPKhm
	.quad	.LC16
	.quad	_Z13hash_word_lenPKhm
	.quad	.LC17
	.quad	_Z13hash_checksumPKhm
	.quad	.LC18
	.quad	_Z12hash_rol_xorPKhm
	.quad	.LC19
	.quad	_Z12hash_ror_xorPKhm
	.quad	.LC20
	.quad	_Z12hash_murmur3PKhm
	.quad	.LC21
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
