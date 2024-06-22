#include "lib.h"

int main() {
	str s = str_init("Hello World");
	info(s.data);
	str_deinit(s);
	return 0;
}
