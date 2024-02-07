#ifndef COMET_LIB
#define COMET_LIB

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // WHY THE FUCK IS memcpy() IN STRING.H?????

// -----Configuration--------------------------
#ifndef DEBUG
#define DEBUG 1
#endif

#ifndef COMET_LIB_CURRENT_LOG_LEVEL
#define COMET_LIB_CURRENT_LOG_LEVEL CLLL_INFO
#endif
// --------------------------------------------

// improved the naming by a factor of 10^64
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef __uint128_t u128;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef __int128_t i128;

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

// -----Optionals------------------------------

typedef void tOptional;

tOptional* tOptional_create(void* data, u8 size_of_data);
tOptional* tOptional_create_clone(void* data, u8 size_of_data);
tOptional* tOptional_create_none();
void tOptional_free(tOptional* this);

bool tOptional_is_some(tOptional* this);
bool tOptional_is_none(tOptional* this);
void* tOptional_unwrap(tOptional* this);
void* tOptional_unwrap_clone(tOptional* this);
void* tOptional_unwrapF(tOptional* this);  // returns a clone of the data
void* tOptional_unwrap_cloneF(tOptional* this);

// -----Iterators------------------------------

typedef void tIterator;

tIterator* tIterator_create(u16 stride);
void tIterator_free(tIterator* this);

void tIteratorMUT_feed(tIterator** this_mut, void* data);
void* tIteratorMUT_get(
    tIterator** this_mut); /* congrats! it's your responsibility */

// -----Vectors--------------------------------

typedef void tVec;

tVec* tVec_create(u8 stride);
void tVec_free(tVec* this);

u16 tVec_length(tVec* this);

void tVec_reserve(tVec* this, u8 stride, u16 length);
void tVecMUT_resize(tVec** this_mut, u16 length);
void* tVec_at(tVec* this, u16 index);
void tVecMUT_push(tVec** this_mut, void* data);
void* tVecMUT_pop(tVec** this_mut);
tIterator* tVec_iterate(tVec* this);

// -----String---------------------------------

typedef void tString;

tString* tString_create();
tString* tString_create_str(char* c_str);
void tString_free(tString* this);

u16 tString_length(tString* this);
char* tString_chars(tString* this);

void tStringMUT_concat_cstr(tString** this_mut, char* c_str);
void tStringMUT_concat(tString** this_mut, tString* str);
void tStringMUT_concatF(tString** this_mut, tString* str);
tOptional* tString_find_char(tString* this, char char_to_find);
tVec* tString_find_chars(tString* this, char char_to_find);

// -----Logging--------------------------------

typedef enum {
  CLLL_INFO,
  CLLL_WARN,
  CLLL_ERROR,
  CLLL_COUNT
} COMET_LIB_LOG_LEVEL;

void log_info(tString* message);
void log_warn(tString* message);
void log_err(tString* message);
void log_infoF(tString* message);
void log_warnF(tString* message);
void log_errF(tString* message);

// use these when informing failed memory allocation, because tString also
// needs memory to exist
void log_info_str(char* message);
void log_warn_str(char* message);
void log_err_str(char* message);

#if DEBUG
void log_debuginfo_str(char* message, char* file_name, u8 line_number);
void log_debugwarn_str(char* message, char* file_name, u8 line_number);
void log_debugerr_str(char* message, char* file_name, u8 line_number);

#define info(message) log_debuginfo_str(message, __FILE__, __LINE__)
#define warn(message) log_debugwarn_str(message, __FILE__, __LINE__)
#define err(message) log_debugerr_str(message, __FILE__, __LINE__)
#else
#define info(message) log_info_str(message)
#define warn(message) log_warn_str(message)
#define err(message) log_err_str(message)
#endif

// --------------------------------------------

#endif