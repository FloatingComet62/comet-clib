#ifndef COMET_LIB
#define COMET_LIB

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ----------------------------------------------
// Configuration

#define COMET_LIB_DEBUG 1
#define COMET_LIB_LOG_LEVEL CLLL_INFO
#define COMET_LIB_VEC_INITIAL_CAPACITY 4
#define COMET_LIB_VEC_MAX_INCREMENT 32
#define COMET_LIB_STR_INITIAL_CAPACITY 4

// ----------------------------------------------
// improved the naming by a factor of 10^64

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
// typedef __uint128_t u128;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
// typedef __int128_t i128;

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

// ----------------------------------------------
// Optional

typedef struct {
	void* data;
	bool has_data;
} optional;

optional optional_init_some(void* data);
optional optional_init_none();

// ----------------------------------------------
// String
typedef struct {
	char* data;
	u32 length;
	u32 capacity;
} str;

str      str_init(const char* data);
str      str_init_reserve(const u32 capacity);
void     str_deinit(const str self);
str      str_concat(const str str1, const str str2);
str      str_concat_cstr(const str str1, const char* str2);
void     strMUT_concat(str* str1, const str str2);
void     strMUT_concat_cstr(str* str1, const char* str2);
void     strMUT_remove_at(str* self, const u32 index);
void     strMUT_concat_assume_capacity(str* str1, const str str2);
void     strMUT_concat_cstr_assume_capacity(str* str1, const char* str2);
optional str_at(const str self, const u32 index);
optional str_find(const str self, const char character);

// ----------------------------------------------
// Vec
typedef struct {
	void* head;
	u32 stride;
	u32 length;
	u32 capacity;
} vec;

vec      vec_init(const u32 stride);
vec      vec_init_reserve(const u32 stride, const u32 capacity);
void     vec_deinit(const vec self);
optional vec_at(const vec self, const u32 index);
void     vecMUT_reserve(vec* self, const u32 capacity);
void     vecMUT_push(vec* self, const void* data);
void     vecMUT_push_value(vec* self, const void* data);
void     vecMUT_push_assume_capacity(vec* self, const void* data);
void     vecMUT_push_value_assume_capacity(vec* self, const void* data);
optional vecMUT_pop(vec* self);
void     vecMUT_remove_at(vec* self, const u32 index);

// ----------------------------------------------
// Logging

typedef enum {
	CLLL_INFO,
	CLLL_WARN,
	CLLL_ERROR,
	CLLL_COUNT
} COMET_LIB_LOG_LEVELS;

#if COMET_LIB_DEBUG

void log_debuginfo(const char* message, const char* file, const u32 line_number);
void log_debugwarn(const char* message, const char* file, const u32 line_number);
void log_debugerrr(const char* message, const char* file, const u32 line_number);

#define info(message) log_debuginfo(message, __FILE__, __LINE__)
#define warn(message) log_debugwarn(message, __FILE__, __LINE__)
#define errr(message) log_debugerrr(message, __FILE__, __LINE__)

#else

void log_info(const char* message);
void log_warn(const char* message);
void log_errr(const char* message);

#define info(message) log_info(message)
#define warn(message) log_warn(message)
#define errr(message) log_errr(message)

#endif

#endif
