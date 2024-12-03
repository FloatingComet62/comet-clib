#include "../lib.h"

#if COMET_LIB_DEBUG

void log_debuginfo(const char* message, const char* source_file,
                   const u32 line_number) {
  if (COMET_LIB_LOG_LEVEL > CLLL_INFO) {
    return;
  }
  printf("[\033[1;32mInfo\033[0m][%s:%d] %s\n", source_file, line_number,
         message);
#if COMET_LIB_FORCE_LOG || COMET_LIB_DEBUG
  FILE* file = fopen(COMET_LIB_LOG, "a");
  fprintf(file, "[Info][%s:%d] %s\n", source_file, line_number, message);
  fclose(file);
#endif
}

void log_debugwarn(const char* message, const char* source_file,
                   const u32 line_number) {
  if (COMET_LIB_LOG_LEVEL > CLLL_WARN) {
    return;
  }
  printf("[\033[1;33mWarn\033[0m][%s:%d] %s\n", source_file, line_number,
         message);
#if COMET_LIB_FORCE_LOG || COMET_LIB_DEBUG
  FILE* file = fopen(COMET_LIB_LOG, "a");
  fprintf(file, "[Warn][%s:%d] %s\n", source_file, line_number, message);
  fclose(file);
#endif
}

void log_debugerrr(const char* message, const char* source_file,
                   const u32 line_number) {
  if (COMET_LIB_LOG_LEVEL > CLLL_ERROR) {
    return;
  }
  printf("[\033[1;31mError\033[0m][%s:%d] %s\n", source_file, line_number,
         message);
#if COMET_LIB_FORCE_LOG || COMET_LIB_DEBUG
  FILE* file = fopen(COMET_LIB_LOG, "a");
  fprintf(file, "[Error][%s:%d] %s\n", source_file, line_number, message);
  fclose(file);
#endif
}

#else

void log_info(const char* message) {
  if (COMET_LIB_LOG_LEVEL > CLLL_INFO) {
    return;
  }
  printf("[\033[1;32mInfo\033[0m] %s\n", message);
#if COMET_LIB_FORCE_LOG || COMET_LIB_DEBUG
  FILE* file = fopen(COMET_LIB_LOG, "a");
  fprintf(file, "[Info] %s\n", message);
  fclose(file);
#endif
}

void log_warn(const char* message) {
  if (COMET_LIB_LOG_LEVEL > CLLL_WARN) {
    return;
  }
  printf("[\033[1;33mWarn\033[0m] %s\n", message);
#if COMET_LIB_FORCE_LOG || COMET_LIB_DEBUG
  FILE* file = fopen(COMET_LIB_LOG, "a");
  fprintf(file, "[Warn] %s\n", message);
  fclose(file);
#endif
}

void log_errr(const char* message) {
  if (COMET_LIB_LOG_LEVEL > CLLL_ERROR) {
    return;
  }
  printf("[\033[1;31mError\033[0m] %s\n", message);
#if COMET_LIB_FORCE_LOG || COMET_LIB_DEBUG
  FILE* file = fopen(COMET_LIB_LOG, "a");
  fprintf(file, "[Error] %s\n", message);
  fclose(file);
#endif
}

#endif
