#include "lib.h"

#ifdef COMET_LIB_TEST
#include "test.h"
#else 

int main() {
	str s = str_init("Hello World");
	info(s.data);
	str_deinit(s);
	return 0;
}

#endif
