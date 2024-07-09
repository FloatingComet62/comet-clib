#include "../test.h"

void test_func(bool (*fun_ptr)(), const char* function_name) {
	printf("Testing \033[1;33m%s\033[0m ...", function_name);
	if (fun_ptr()) {
		printf(" \033[1;32mpassed\033[0m\n");
	} else {
		printf(" ... \033[1;31mfailed\033[0m\n");
	}
}

int main() {
	test_func(&test_str_init, "str_init");
	test_func(&test_str_init_reserve, "str_init_reserve");
	test_func(&test_str_concat, "str_concat");
	test_func(&test_str_concat_cstr, "str_concat_cstr");
	test_func(&test_str_at, "str_at");
	test_func(&test_str_find, "str_find");
	return 0;
}
