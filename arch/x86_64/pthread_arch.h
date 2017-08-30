extern struct pthread __tls_pthread_self__;

static inline struct pthread *__pthread_self()
{
	struct pthread *self;
	// FIXME: use segment register instead of static global "tls"
	/*__asm__ __volatile__ ("mov %%fs:0,%0" : "=r" (self) );*/
	self = &__tls_pthread_self__;
	return self;
}

#define TP_ADJ(p) (p)

#define MC_PC gregs[REG_RIP]
