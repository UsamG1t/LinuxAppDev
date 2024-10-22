#include <dlfcn.h>

typedef int (*rnd_type)(void);
int rand(void) {
	int ret;
		// найти ещё один символ с таким же именем
	ret = ((rnd_type)(dlsym(RTLD_NEXT, "rand")))();
	return ret % 2 ? ret : 42;
}
