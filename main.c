#include "lib/lib.h"

int main(int argc, char** argv) {
  tString* str = tString_create_str("Hello World");
  tStringMUT_concat_cstr(&str, " concat me");
  log_infoF(str);
  info("Exiting");
  return 0;
}
