#include "final80v2.h"
#include "render_anime3.c"  // render_anime.c render_anime2.c render_anime3.c 分别为三种种大小不同OLED的待机动画，选择加载
#include <stdio.h>
// [Init Variables] ----------------------------------------------------------//
bool            is_alt_tab_active   = false;  // ALT_TAB 宏是否激活
uint16_t        alt_tab_timer       = 0;      // ALT_TAB 计时器
static uint32_t oled_timer          = 0;      // OLED 计时器
bool            master_oled_cleared = false;  // OLED CLEAR 标记
#define OLED_SHOW_STATE_TIMEOUT 20000         // 无操作10秒后激活OLED动画

// [Keymaps] -----------------------------------------------------------------//
enum layer_names { _BASE, _UPPER, _FN };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, KC_MUTE,  //
                     KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,                    //
                     KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,                   //
                     LT(2, KC_CAPS), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,                  //
                     KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_RIGHT,           //
                     KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(2), KC_RCTL, KC_LEFT, KC_DOWN),                                   //

    [_UPPER] = LAYOUT(KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, KC_MUTE,  //
                      KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,                    //
                      KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,                   //
                      KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,                         //
                      KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_RIGHT,           //
                      KC_LCTL, KC_NO, KC_LALT, KC_SPC, KC_RALT, MO(2), KC_RCTL, KC_LEFT, KC_DOWN),                                     //

    [_FN] = LAYOUT(RESET, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_TRNS,            //
                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_ASTERISK, KC_KP_SLASH, KC_TRNS, KC_CALCULATOR,  //
                   KC_TRNS, KC_HOME, KC_UP, KC_END, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_7, KC_8, KC_9, KC_KP_MINUS, KC_TRNS, KC_MY_COMPUTER,                    //
                   KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_4, KC_5, KC_6, KC_KP_PLUS, RGB_MOD,                                 //
                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_1, KC_2, KC_3, KC_ASTG, KC_PGUP, KC_TRNS,                            //
                   KC_TRNS, TG(1), KC_TRNS, RGB_TOG, KC_0, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGDOWN),                                                                  //
};

// {键盘预处理任务} -----------------------------------------------//
void keyboard_post_init_user(void) {
    autoshift_disable();

#ifdef CONSOLE_ENABLE
    // debug调试选项开关：
    debug_enable = true;
    // debug_matrix = true;
    debug_keyboard = true;
    // debug_mouse = true;
#endif
}

// {矩阵扫描任务} -----------------------------------------------//
void matrix_scan_user(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;  // 1000ms后重置ALT_TAB宏状态，unregister LALT.
        }
    }
}

// {编码器功能} -----------------------------------------------//
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (biton32(layer_state)) {  // 层检查
        // 1 = _UPPER:
        case 1:
            clockwise ? tap_code(KC_MS_LEFT) : tap_code(KC_MS_RIGHT);
            break;

        // 2 = _FN:
        case 2:
            clockwise ? rgb_matrix_decrease_val() : rgb_matrix_increase_val();
            break;

        // 0 or default = _BASE:
        default:
            if (get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT))) {  // Modifier检查，此处检查LSHIFT是否按下
                if (clockwise) {
                    register_code(KC_VOLD);
                    wait_ms(10);
                    unregister_code(KC_VOLD);
                } else {
                    register_code(KC_VOLU);
                    wait_ms(10);
                    unregister_code(KC_VOLU);
                }
            } else if (get_mods() & MOD_BIT(KC_LCTRL)) {
                clockwise ? tap_code(KC_KP_MINUS) : tap_code(KC_KP_PLUS);
            } else {
                // 编码器默认执行ALT_TAB宏：
                if (clockwise) {
                    if (!is_alt_tab_active) {
                        is_alt_tab_active = true;
                        register_code(KC_LALT);
                    }
                    alt_tab_timer = timer_read();
                    tap_code16(S(KC_TAB));
                } else {
                    if (!is_alt_tab_active) {
                        is_alt_tab_active = true;
                        register_code(KC_LALT);
                    }
                    alt_tab_timer = timer_read();
                    tap_code16(KC_TAB);
                }
            }
            break;
    }

    return false;
}

// [OLED 设置] ---------------------------------------------//
// !!以下OLED显示代码基于 ./myskeeb/oled.c 修改

#ifdef OLED_DRIVER_ENABLE
// 绘图常量
static const char PROGMEM oled_header[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0};

static const char PROGMEM oled_layer_keylog_separator[] = {0xc8, 0xff, 0};

static const char PROGMEM oled_layer_line_end[] = {0xd4, 0};

static const char PROGMEM oled_layer_keylog_bottom[] = {0xc1, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc3, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc2, 0};

static const char PROGMEM oled_line_start[] = {0xc0, 0};

static const char PROGMEM oled_mods_bottom[] = {0xc1, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc2, 0};

static const char PROGMEM oled_footer[] = {0xc4, 0xc5, 0xc5, 0xc9, 0xca, 0xca, 0xca, 0xca, 0xca, 0xca, 0xca, 0xca, 0xca, 0xca, 0xca, 0xca, 0xca, 0xcb, 0xc5, 0xc5, 0xc6, 0};

// Modifier 状态显示
void render_mod_status(uint8_t modifiers) {
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("-"), false);
    oled_write_P(PSTR("SHF"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("-"), false);
    oled_write_P(PSTR("CTR"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("-"), false);
    oled_write_P(PSTR("WIN"), (modifiers & MOD_MASK_GUI));
    oled_write_P(PSTR("-"), false);
    oled_write_P(PSTR("ALT"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("-"), false);
    oled_write_P(PSTR(" "), false);
}

// Layer 状态显示
void render_layer_state(void) {
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR(" MAIN   "), false);
            break;
        case 1:
            oled_write_P(PSTR(" GAME   "), false);
            break;
        case 2:
            oled_write_P(PSTR("FUNCTION"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined"), false);
    }
}

// 键盘其他状态
char wpm_str[6];

void render_keyboard_status(void) {
    oled_write_P(PSTR(" "), false);

    // CAPSLOCK状态:
    oled_write_P(host_keyboard_led_state().caps_lock ? PSTR("-CAPS") : PSTR("-----"), false);

    oled_write_P(PSTR(" "), false);

    // 显示WPM（每分钟按键次数/APM）:
    sprintf(wpm_str, "-%03d-", get_current_wpm());
    oled_write_ln_P(wpm_str, false);

    oled_write_P(PSTR(" "), false);

    // RGB 是否开启以及模式:
    rgb_matrix_is_enabled() ? oled_write_P(PSTR("RGB"), false) : oled_write_P(PSTR("---"), false);
    static char rgbStatusLine1[39] = {0};
    snprintf(rgbStatusLine1, sizeof(rgbStatusLine1), "%02d", rgb_matrix_get_mode());
    rgb_matrix_is_enabled() ? oled_write_P(rgbStatusLine1, false) : oled_write_P(PSTR("--"), false);

    oled_write_P(PSTR(" "), false);
}
// 按键记录显示：
#    define KEYLOGGER_LENGTH 8
static char keylog_str[KEYLOGGER_LENGTH + 1] = {0};

static const char PROGMEM code_to_name[0xFF] = {
    //   0    1    2    3    4    5    6    7    8    9    A    B    c    D    E    F
    182, ' ',  ' ', ' ', 'a',  'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',  // 0x
    'm', 'n',  'o', 'p', 'q',  'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2',  // 1x
    '3', '4',  '5', '6', '7',  '8', '9', '0', 20,  19,  17,  29,  22,  '-', '=', '[',  // 2x
    ']', '\\', '#', ';', '\'', '`', ',', '.', '/', 188, 149, 150, 151, 152, 153, 154,  // 3x
    155, 156,  157, 158, 159,  181, 191, 190, ' ', ' ', 185, 183, 16,  186, 184, 26,   // 4x
    27,  25,   24,  189, '/',  '*', '-', '+', ' ', '1', '2', '3', '4', '5', '6', '7',  // 5x
    '8', '9',  '0', '.', ' ',  187, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 6x
    ' ', ' ',  ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 7x
    ' ', ' ',  ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 8x
    ' ', ' ',  ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 9x
    ' ', ' ',  ' ', ' ', ' ',  ' ', ' ', ' ', 214, 215, 216, 217, 218, 219, 220, 221,  // Ax
    ' ', ' ',  213, ' ', ' ',  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Bx
    ' ', ' ',  ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Cx
    ' ', ' ',  ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Dx
    'C', 'S',  'A', 'W', ' ',  'S', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ex
    ' ', ' ',  ' ', ' ', ' ',  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '        // Fx
};

void add_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) || (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
        keycode = keycode & 0xFF;
    } else if (keycode > 0xFF) {
        keycode = 0;
    }

    for (uint8_t i = (KEYLOGGER_LENGTH - 1); i > 0; --i) {
        keylog_str[i] = keylog_str[i - 1];
    }

    if (keycode < (sizeof(code_to_name) / sizeof(char))) {
        keylog_str[0] = pgm_read_byte(&code_to_name[keycode]);
    }
}

void render_keylogger_status(void) { oled_write(keylog_str, false); }

// {OLED 主进程} ------------------------------------------------------//
void oled_task_user(void) {
    if (timer_elapsed32(oled_timer) > OLED_SHOW_STATE_TIMEOUT && timer_elapsed32(oled_timer) < OLED_TIMEOUT) {
        // 无操作10秒后，OLED_TIMEOUT(60秒默认)前播放动画
        if (!master_oled_cleared) {
            // Clear OLED一次确保动画正确渲染
            oled_clear();
            master_oled_cleared = true;
        }
        render_anime();
        return;
    } else if (timer_elapsed32(oled_timer) > OLED_TIMEOUT) {
        // 无操作60秒后关闭OLED
        oled_off();
        return;
    } else {
        // 重置Clear OLED标记
        if (master_oled_cleared) {
            oled_on();
            oled_clear();
            master_oled_cleared = false;
        }

        // 各种状态信息显示：
        oled_write_P(oled_header, false);
        render_layer_state();
        oled_write_P(oled_layer_keylog_separator, false);
        render_keylogger_status();
        oled_set_cursor(20, 2);
        oled_write_P(oled_layer_line_end, false);
        oled_write_P(oled_layer_keylog_bottom, false);
        oled_write_P(oled_line_start, false);
        render_keyboard_status();
        oled_write_P(oled_layer_line_end, false);
        oled_write_P(oled_mods_bottom, false);
        oled_write_P(oled_line_start, false);
        render_mod_status(get_mods() | get_oneshot_mods());
        oled_write_P(oled_layer_line_end, false);
        oled_write_P(oled_footer, false);
    }
}
#endif

// {按键记录进程} ------------------------------------------------------//
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
        add_keylog(keycode);
        oled_timer = timer_read32();
#endif
    }
    return true;
}
