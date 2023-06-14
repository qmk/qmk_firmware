/*
Copyright 2020 rupa <rupa@lrrr.us> @rupa

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "unicode.h"

combined_mode_t combined_mode = CM_NULL;
bool _seeded = false;

#if defined(UNICODEMAP_ENABLE)
const uint32_t unicode_map[] PROGMEM = {
    [CCIR] = 0x20DD,  // COMBINING CIRCLE  ⃝
    [CENT] = 0x00A2,  // ¢
    [CHEK] = 0x2713,  // ✓
    [CKEY] = 0x20E3,  // COMBINING KEYCAP  ⃣
    [CUI]  = 0x26A0,  // ⚠
    [ECKS] = 0x2716,  // ✖
    [EFF]  = 0x017F,  // ſ
    [HAS]  = 0x262D,  // ☭
    [HUN]  = 0x1F4AF, // 💯
    [IBNG] = 0x203D,  // ‽
    [IRNY] = 0x2E2E,  // ⸮
    [LALL] = 0x2200,  // ∀
    [LELM] = 0x2208,  // ∈
    [LEXI] = 0x2203,  // ∃
    [LPRO] = 0x22A2,  // ⊢
    [M4]   = 0x2669,  // ♩
    [M8]   = 0x266A,  // ♪
    [M8B]  = 0x266B,  // ♫
    [M16]  = 0x266C,  // ♬
    [NEG]  = 0x20E0,  // COMBINING NO  ⃠
    [NOPE] = 0x1F6AB, // 🚫
    [NUM]  = 0x2116,  // №
    [OM]   = 0x0950,  // ॐ
    [SMB]  = 0x263A,  // ☻
    [SMW]  = 0x263B,  // ☺
    [STB]  = 0x2605,  // ★
    [STOP] = 0x26D4,  // ⛔
    [STW]  = 0x2606,  // ☆
};
#endif

const char *d6_map[] = {
    "⚀", "⚁", "⚂", "⚃", "⚄", "⚅"
};
const char *dance_map[] = {
    "〜(￣▽￣〜)",
    "(〜￣▽￣)〜"
};
const char *dance_more_map[] = {
    "ƪ(˘⌣˘)┐",
    "┌(˘⌣˘)ʃ"
};
const char *flip_map[] = {
    "(╯°□°）╯︵ ┻━━┻",
    "（ノ－＿－）ノ･･ ┻━━┻",
    "(ﾉꐦ⊙曲ఠ)ﾉ彡┻━┻"
};
const char *flip_back_map[] = {
    "┬──┬◡ﾉ(° -°ﾉ)",
    "┬──┬ノ( ゜-゜ノ)",
    "┬──┬ノ(ಠ_ಠノ)"
};
const char *joy_map[] = {
    "ᕕ( ᐛ )ᕗ ",
    "٩(ˊᗜˋ*)و",
    "٩( ᐛ )و"
};
const char *joy_harder_map[] = {
    "＼\\ ٩( ᐛ )و /／",
    "✧*｡٩(ˊᗜˋ*)و✧*｡"
};

const char *choice(const char *choices[], int size) {
    if (_seeded == false) {
        srand(timer_read32());
        dprintf("_seeded the roll\n");
        _seeded = true;
    }
    return choices[rand() % size];
}

const char *d6(void) {
    return choice(d6_map, 6);
}
const char *dance(bool more) {
    if (more) {
        return choice(dance_more_map, 2);
    }
    return choice(dance_map, 2);
}
const char *flip(bool flip_back) {
    if (flip_back) {
        return choice(flip_back_map, 3);
    }
    return choice(flip_map, 3);
}
const char *joy(bool harder) {
    if (harder) {
        return choice(joy_harder_map, 2);
    }
    return choice(joy_map, 3);
}

bool u_x(const char *text) {
    send_unicode_string(text);
    return false;
};
bool u_xp(bool is_shifted, const char *shifted, const char *plain) {
    send_unicode_string(is_shifted ? shifted : plain);
    return false;
};

void zalgo(void) {
    int number = (rand() % (8 + 1 - 2)) + 2;
    unsigned int index;
    for (index=0; index<number; index++) {
        uint16_t hex = (rand() % (0x036F + 1 - 0x0300)) + 0x0300;
        register_hex(hex);
    }
}

bool combined_text(uint16_t keycode) {
    if (keycode < KC_A || (keycode > KC_0 && keycode < KC_MINUS) || keycode > KC_SLASH) {
        return false;
    }
    tap_code(keycode);
    unicode_input_start();
    switch (combined_mode) {
        case CM_CIRCLE:
          register_hex(0x20DD);
          break;
        case CM_NO:
          register_hex(0x20E0);
          break;
        case CM_KEYCAP:
          register_hex(0x20E3);
          break;
        case CM_ZALGO:
          zalgo();
          break;
        default:
          break;
    }
    unicode_input_finish();
    return true;
}

void cycle_combined_mode(void) {
    if (combined_mode++ >= CM_MAX - 1) {
        combined_mode = CM_NULL;
    }
}

combined_mode_t set_combined_mode(combined_mode_t mode) {
    combined_mode = combined_mode == mode ? CM_NULL : mode;
    return combined_mode;
}
