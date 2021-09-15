
#include "unicode.h"

const uint32_t PROGMEM unicode_map[] = {
    [BUL1]     = 0x2022,   // •
    [BUL2]     = 0x25E6,   // ◦
    [LARR]     = 0x2190,   // ←
    [RARR]     = 0x2192,   // →
    [ENDASH]   = 0x2013,   // –
    [EMDASH]   = 0x2014,   // —
    [SPIDER]   = 0x1F577,  // 🕷
    [SAD]      = 0x2639,   // ☹
    [MEH]      = 0x1F611,  // 😑
    [HAPPY]    = 0x1F600,  // 😀
    [ANGRY]    = 0x1F620,  // 😠
    [THUMBUP]  = 0x1F44D,  // 👍
    [THUMBDN]  = 0x1F44E,  // 👎
    [LOL]      = 0x1F602,  // 😂
    [SURPRISE] = 0x1F62E,  // 😮
};

void eeconfig_init_user_unicode(void) {
    // Default to Linux style
    set_unicode_input_mode(UC_LNX);
}
