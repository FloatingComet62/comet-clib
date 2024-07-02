#include "../lib.h"

#if COMET_LIB_DEBUG

void log_debuginfo(const char* message, const char* file, const u32 line_number) {
	if (COMET_LIB_LOG_LEVEL > CLLL_INFO) {
		return;
	}
	printf("[\033[1;32mInfo\033[0m][%s:%d] %s\n", file, line_number, message);
}

void log_debugwarn(const char* message, const char* file, const u32 line_number) {
	if (COMET_LIB_LOG_LEVEL > CLLL_WARN) {
		return;
	}
	printf("[\033[1;33mWarn\033[0m][%s:%d] %s\n", file, line_number, message);
}

void log_debugerrr(const char* message, const char* file, const u32 line_number) {
	if (COMET_LIB_LOG_LEVEL > CLLL_ERROR) {
		return;
	}
	printf("[\033[1;31mError\033[0m][%s:%d] %s\n", file, line_number, message);
}

#else

void log_info(const char* message) {
	if (COMET_LIB_LOG_LEVEL > CLLL_INFO) {
		return;
	}
	printf("[\033[1;32mInfo\033[0m] %s\n", message);
}

void log_warn(const char* message) {
	if (COMET_LIB_LOG_LEVEL > CLLL_WARN) {
		return;
	}
	printf("[\033[1;33mWarn\033[0m] %s\n", message);
}

void log_errr(const char* message) {
	if (COMET_LIB_LOG_LEVEL > CLLL_ERROR) {
		return;
	}
	printf("[\033[1;31mError\033[0m] %s\n", message);
}

#endif
