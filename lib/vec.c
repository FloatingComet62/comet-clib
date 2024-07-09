#include "../lib.h"

u32 increase_capacity(const u32 old_capacity) {
	return old_capacity * 2;
}

vec vec_init(const u32 stride) {
	void* data = malloc(COMET_LIB_VEC_INITIAL_CAPACITY * stride);
	if (data == NULL) {
		errr("Failed to allocate memory");
	}
	return (vec) { data, stride, 0, COMET_LIB_VEC_INITIAL_CAPACITY };
}

vec vec_init_reserve(const u32 stride, const u32 capacity) {
	void* data = malloc(capacity * stride);
	if (data == NULL) {
		errr("Failed to allocate memory");
	}
	return (vec) { data, stride, 0, capacity };
}

void vec_deinit(const vec self) {
	free(self.head);
}

optional vec_at(const vec self, const u32 index) {
	if (index >= self.length) {
		return optional_init_none();
	}
	return optional_init_some(self.head + index * self.stride);
}

void vecMUT_reserve(vec* self, const u32 capacity) {
	self->head = realloc(self->head, capacity * self->stride);
	if (self->head == NULL) {
		errr("Failed to allocate memory");
	}
	self->capacity = capacity;
}

void vecMUT_push(vec* self, const void* data) {
	if (self->length + 1 > self->capacity) {
		vecMUT_reserve(self, increase_capacity(self->capacity));
	}
	vecMUT_push_assume_capacity(self, data);
}

void vecMUT_push_value(vec* self, const void* data) {
	if (self->length + 1 > self->capacity) {
		vecMUT_reserve(self, increase_capacity(self->capacity));
	}
	vecMUT_push_value_assume_capacity(self, data);
}

void vecMUT_push_assume_capacity(vec* self, const void* data) {
	memcpy(self->head + self->length * self->stride, data, self->stride);
	self->length++;
}

void vecMUT_push_value_assume_capacity(vec* self, const void* data) {
	memcpy(self->head + self->length * self->stride, &data, self->stride);
	self->length++;
}

optional vecMUT_pop(vec* self) {
	if (self->length == 0) {
		return optional_init_none();
	}
	void* item = malloc(self->stride);
	memcpy(item, self->head + self->length * self->stride, self->stride);
	self->length--;
	return optional_init_some(item);
}

void vecMUT_remove_at(vec* self, const u32 index) {
	memcpy(
		self->head + index * self->stride,
		self->head + (index + 1) * self->stride,
		(self->length - index) * self->stride
	);
	self->length--;
}

