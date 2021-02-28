#include <stdint.h>

#include "progmem.h"

#define SEND_STRING(string) send_string_P(PSTR(string))
#define SEND_STRING_DELAY(string, interval) send_string_with_delay_P(PSTR(string), interval)

// Look-Up Tables (LUTs) to convert ASCII character to keycode sequence.
extern const uint8_t ascii_to_keycode_lut[128];
extern const uint8_t ascii_to_shift_lut[16];
extern const uint8_t ascii_to_altgr_lut[16];
extern const uint8_t ascii_to_dead_lut[16];

// clang-format off
#define KCLUT_ENTRY(a, b, c, d, e, f, g, h) \
    ( ((a) ? 1 : 0) << 0 \
    | ((b) ? 1 : 0) << 1 \
    | ((c) ? 1 : 0) << 2 \
    | ((d) ? 1 : 0) << 3 \
    | ((e) ? 1 : 0) << 4 \
    | ((f) ? 1 : 0) << 5 \
    | ((g) ? 1 : 0) << 6 \
    | ((h) ? 1 : 0) << 7 )
// clang-format on

void send_string(const char *str);
void send_string_with_delay(const char *str, uint8_t interval);
void send_string_P(const char *str);
void send_string_with_delay_P(const char *str, uint8_t interval);
void send_char(char ascii_code);
