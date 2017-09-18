#include <elf.h>
#include <poll.h>
#include <fcntl.h>
#include <signal.h>
#include "syscall.h"
#include "atomic.h"
#include "libc.h"

int main();
_Noreturn int __libc_start_main(int (*)(), int, char **, char **);

void _start(long *p, int extra)
{
	int argc = p[0];
	char **argv = (void *)(p+1);
	char **envp = argv+argc+1;
	__libc_start_main(main, argc, argv, envp);
}
