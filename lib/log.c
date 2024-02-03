#include "lib.h"

void log_info(tString* message) { log_info_str(tString_chars(message)); }
void log_warn(tString* message) { log_warn_str(tString_chars(message)); }
void log_err(tString* message) { log_err_str(tString_chars(message)); }
void log_infoF(tString* message) {
  log_info(message);
  tString_free(message);
}
void log_warnF(tString* message) {
  log_warn(message);
  tString_free(message);
}
void log_errF(tString* message) {
  log_err(message);
  tString_free(message);
}
void log_info_str(char* message) {
  if (COMET_LIB_CURRENT_LOG_LEVEL <= CLLL_INFO) {
    printf("[\033[1;32mInfo\033[0m] %s\n", message);
  }
}
void log_debuginfo_str(char* message, char* file_name, u8 line_number) {
  if (COMET_LIB_CURRENT_LOG_LEVEL <= CLLL_INFO) {
    printf("[\033[1;32mInfo\033[0m][%s:%d] %s\n", file_name, line_number,
           message);
  }
}
void log_warn_str(char* message) {
  if (COMET_LIB_CURRENT_LOG_LEVEL <= CLLL_WARN) {
    printf("[\033[1;33mWarn\033[0m] %s\n", message);
  }
}
void log_debugwarn_str(char* message, char* file_name, u8 line_number) {
  if (COMET_LIB_CURRENT_LOG_LEVEL <= CLLL_WARN) {
    printf("[\033[1;33mWarn\033[0m][%s:%d] %s\n", file_name, line_number,
           message);
  }
}
void log_err_str(char* message) {
  if (COMET_LIB_CURRENT_LOG_LEVEL <= CLLL_ERROR) {
    printf("[\033[1;31mError\033[0m] %s\n", message);
    exit(1);
  }
}
void log_debugerr_str(char* message, char* file_name, u8 line_number) {
  if (COMET_LIB_CURRENT_LOG_LEVEL <= CLLL_ERROR) {
    printf("[\033[1;31mError\033[0m][%s:%d] %s\n", file_name, line_number,
           message);
    exit(1);
  }
}