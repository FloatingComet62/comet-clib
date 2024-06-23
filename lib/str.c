#include "../lib.h"

u32 cstr_len(const char* data) {
	u32 length = 0;
	while (data[length] != '\0') {
		length++;
	}
	return length;
}

str str_init(const char* data) {
	u32 length = cstr_len(data);
	u32 capacity = max(COMET_LIB_STR_INITIAL_CAPACITY, length);
	char* m_data = malloc(capacity * sizeof(char));
	if (m_data == NULL) {
		errr("Failed to alloacte memory");
	}
	u32 i = 0;
	for (; i < length; i++) {
		m_data[i] = data[i];
	}
	m_data[i] = '\0';

	return (str) { m_data, length, capacity };
}

str str_init_reserve(const u32 capacity) {
	char* m_data = malloc(capacity * sizeof(char));
	if (m_data == NULL) {
		errr("Failed to alloacte memory");
	}

	return (str) { m_data, 0, capacity };
}

void str_deinit(const str self) {
	free(self.data);
}

str str_concat(const str str1, const str str2) {
	u32 new_len = str1.length + str2.length;
	u32 new_capacity = str1.capacity + str2.capacity;
	char* new_data = malloc(new_capacity * sizeof(char));
	if (new_data == NULL) {
		errr("Failed to alloacte memory");
	}
	u32 i = 0;
	for (; i < new_len; i++) {
		if (i < str1.length) {
			new_data[i] = str1.data[i];
			continue;
		}
		new_data[i] = str2.data[i - str1.length];
	}
	new_data[i] = '\0';
	return (str) { new_data, new_len, new_capacity };
}

str str_concat_cstr(const str str1, const char* str2) {
	u32 str2_length = cstr_len(str2);
	u32 new_len = str1.length + str2_length;
	u32 new_capacity = str1.capacity + str2_length;
	char* new_data = malloc(new_capacity * sizeof(char));
	if (new_data == NULL) {
		errr("Failed to alloacte memory");
	}
	u32 i = 0;
	for (; i < new_len; i++) {
		if (i < str1.length) {
			new_data[i] = str1.data[i];
			continue;
		}
		new_data[i] = str2[i - str1.length];
	}
	new_data[i] = '\0';
	return (str) { new_data, new_len, new_capacity };
}

void strMUT_concat(str* str1, const str str2) {
	if (str1->length + str2.length > str1->capacity) {
		str1->capacity = max(str1->length + str2.length, 2 * str1->capacity);
		str1->data = realloc(str1->data, str1->capacity * sizeof(char));
		if (str1->data == NULL) {
			errr("Failed to alloacte memory");
		}
	}
	strMUT_concat_assume_capacity(str1, str2);
}

void strMUT_concat_cstr(str* str1, const char* str2) {
	u32 str2_length = cstr_len(str2);
	if (str1->length + str2_length > str1->capacity) {
		str1->capacity = max(str1->length + str2_length, 2 * str1->capacity);
		str1->data = realloc(str1->data, str1->capacity * sizeof(char));
		if (str1->data == NULL) {
			errr("Failed to alloacte memory");
		}
	}
	strMUT_concat_cstr_assume_capacity(str1, str2);
}

void strMUT_remove_at(str* self, const u32 index) {
	for (u32 i = index; i < self->length; i++) {
		self->data[i] = self->data[i + 1];
	}
}

void strMUT_concat_assume_capacity(str* str1, const str str2) {
	u32 i = str1->length;
	for(; i < str1->length + str2.length; i++) {
		str1->data[i] = str2.data[i];
	}
	str1->data[i] = '\0';
}

void strMUT_concat_cstr_assume_capacity(str* str1, const char* str2) {
	u32 str2_length = cstr_len(str2);
	u32 i = str1->length;
	for(; i < str1->length + str2_length; i++) {
		str1->data[i] = str2[i];
	}
	str1->data[i] = '\0';
}

optional str_at(const str self, const u32 index) {
	if (index >= self.length) {
		return optional_init_none();
	}
	return optional_init_some((void*)self.data[index]);
}

optional str_find(const str self, const char character) {
	for (u32 i = 0; i < self.length; i++) {
		if (self.data[i] != character) {
			continue;
		}
		return optional_init_some((void*)i);
	}
	return optional_init_none();
}

