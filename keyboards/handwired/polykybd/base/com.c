#include "com.h"

bool test_flag(uint8_t flags, uint8_t f) {
    return (flags & f) != 0;
}

uint8_t flag_on(uint8_t flags, uint8_t f) {
    return flags | f;
}

uint8_t flag_off(uint8_t flags, uint8_t f) {
    return flags & ~f;
}

uint8_t set_flag(uint8_t flags, uint8_t f, bool set) {
    return set ? flag_on(flags, f) : flag_off(flags, f);
}

uint8_t toggle_flag(uint8_t flags, uint8_t f) {
    return set_flag(flags, f, (flags & f)==0);
}

bool has_flag_changed(uint8_t flags1, uint8_t flags2, uint8_t f) {
    return (flags1 & f) != (flags2 & f);
}

bool flag_turned_off(uint8_t flags1, uint8_t flags2, uint8_t f) {
    return ((flags1 & f) != 0) && ((flags2 & f) == 0);
}

bool flag_turned_on(uint8_t flags1, uint8_t flags2, uint8_t f) {
    return ((flags1 & f) == 0) && ((flags2 & f) != 0);
}
