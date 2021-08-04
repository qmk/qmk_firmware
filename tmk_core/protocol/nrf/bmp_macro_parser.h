
#pragma once

#include <stdint.h>

int32_t bmp_macro_file_stringify(const uint8_t* macro, uint8_t* serialized_text,
                                 uint32_t len);
int32_t bmp_macro_file_parse(uint8_t*       macro,
                                   const uint8_t* serialized_text,
                                   uint32_t       len);
