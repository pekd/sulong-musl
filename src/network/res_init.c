#include <stdlib.h>
#include <resolv.h>
#include "libc.h"

static int __res_init()
{
	return 0;
}

weak_alias(__res_init, res_init);
