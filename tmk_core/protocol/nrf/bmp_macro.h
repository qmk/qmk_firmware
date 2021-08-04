
#pragma once

#include <stdint.h>

#define BMP_MACRO_COUNT (16)
#define BMP_MACRO_FILE_LEN (1024)

void     bmp_macro_task(void);
uint8_t* bmp_macro_get_file_buffer(void);
void     bmp_macro_load_file(void);
void     bmp_macro_save_file(void);
void     bmp_macro_send(uint8_t id);
void     bmp_macro_get_buffer(uint16_t offset, uint16_t size, uint8_t* buffer);
void     bmp_macro_set_buffer(uint16_t offset, uint16_t size, uint8_t* buffer);
void     bmp_macro_reset(void);
