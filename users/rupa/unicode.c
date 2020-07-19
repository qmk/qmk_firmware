#include "unicode.h"

#if defined(UNICODEMAP_ENABLE)
const uint32_t PROGMEM unicode_map[] = {
    [CHEK] = 0x2713, // ✓
    /*
    [DI1]  = 0x2680, // ⚀
    [DI2]  = 0x2681, // ⚁
    [DI3]  = 0x2682, // ⚂
    [DI4]  = 0x2683, // ⚃
    [DI5]  = 0x2684, // ⚄
    [DI6]  = 0x2685, // ⚅
    */
    [HAS]  = 0x262D, // ☭
    [IBNG] = 0x203D, // ‽
    [IRNY] = 0x2E2E, // ⸮
    [M4]   = 0x2669, // ♩
    [M8]   = 0x266A, // ♪
    [M8B]  = 0x266B, // ♫
    [M16]  = 0x266C, // ♬
    [STB]  = 0x2605, // ★
    [STW]  = 0x2606, // ☆
};
#endif
