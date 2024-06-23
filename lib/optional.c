#include "../lib.h"

optional optional_init_some(void* data) {
	return (optional) { data, true };
}

optional optional_init_none() {
	return (optional) { NULL, false };
}
