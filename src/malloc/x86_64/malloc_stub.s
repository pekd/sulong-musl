.global malloc
.type malloc,@function

.global calloc
.type calloc,@function

.global realloc
.type realloc,@function

.global free
.type free,@function

malloc:
calloc:
realloc:
free:
	movq $0, %rax
	ret
