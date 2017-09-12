#include "pthread_impl.h"

// FIXME: implement real tls
struct pthread *__tls_pthread_self__;

int __set_thread_area(void *p)
{
	__tls_pthread_self__ = (struct pthread *)p;
	return 1;
#if 0
#ifdef SYS_set_thread_area
	return __syscall(SYS_set_thread_area, p);
#else
	return -ENOSYS;
#endif
#endif
}
