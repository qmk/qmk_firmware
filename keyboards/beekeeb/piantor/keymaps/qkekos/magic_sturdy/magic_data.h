#pragma once

#define MAX_CONTEXT_LENGTH 2

// --------------------------------------------------

// Magic dictionary (1 entries):
//   i -> ion

#define MAGIC_MIN_LENGTH 1 // "i"
#define MAGIC_MAX_LENGTH 1 // "i"
#define MAGIC_DICTIONARY_SIZE 6

static const uint8_t magic_data[MAGIC_DICTIONARY_SIZE] PROGMEM = {
    0x0C, 0x00, 0x80, 0x6F, 0x6E, 0x00
};

// --------------------------------------------------

// Repeat dictionary (1 entries):
//   y -> you

#define REPEAT_MIN_LENGTH 1 // "y"
#define REPEAT_MAX_LENGTH 1 // "y"
#define REPEAT_DICTIONARY_SIZE 6

static const uint8_t repeat_data[REPEAT_DICTIONARY_SIZE] PROGMEM = {
    0x1C, 0x00, 0x80, 0x6F, 0x75, 0x00
};
