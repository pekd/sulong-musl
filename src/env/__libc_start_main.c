#include <elf.h>
#include <poll.h>
#include <fcntl.h>
#include <signal.h>
#include "syscall.h"
#include "atomic.h"
#include "libc.h"

void __init_tls(size_t *);

static void dummy(void) {}
weak_alias(dummy, _init);

__attribute__((__weak__, __visibility__("hidden")))
extern void (*const __init_array_start)(void), (*const __init_array_end)(void);

static void dummy1(void *p) {}
weak_alias(dummy1, __init_ssp);

#define AUX_CNT 38

void __init_libc(char **envp, char *pn)
{
	size_t i, *auxv, aux[AUX_CNT] = { 0 };
	__environ = envp;
	for (i=0; envp[i]; i++);
	libc.auxv = auxv = (void *)(envp+i+1);
	for (i=0; auxv[i]; i+=2) if (auxv[i]<AUX_CNT) aux[auxv[i]] = auxv[i+1];
	__hwcap = aux[AT_HWCAP];
	__sysinfo = aux[AT_SYSINFO];
	libc.page_size = aux[AT_PAGESZ];

	if (pn) {
		__progname = __progname_full = pn;
		for (i=0; pn[i]; i++) if (pn[i]=='/') __progname = pn+i+1;
	}

	__init_tls(aux);
	__init_ssp((void *)aux[AT_RANDOM]);
}

static void libc_start_init(void)
{
	_init();
#if 0
	uintptr_t a = (uintptr_t)&__init_array_start;
	for (; a<(uintptr_t)&__init_array_end; a+=sizeof(void(*)()))
		(*(void (**)())a)();
#endif
}

weak_alias(libc_start_init, __libc_start_init);

int __libc_start_main(int (*main)(int,char **,char **), int argc, char **argv, char **envp)
{
	//__init_libc(envp, argv[0]);
	__libc_start_init();

	/* Pass control to the application */
	exit(main(argc, argv, envp));
	return 0;
}
