#include QMK_KEYBOARD_H

#include "polyatom.h"
#include "print.h"
#include "base/disp_array.h"
#include "base/shift_reg.h"
#include "fonts/gfx_used_fonts.h"

#include "quantum/quantum_keycodes.h"

enum lang_layer { LANG_EN = 0, LANG_KO = 1, LANG_JP = 2, NUM_LANG = 3};
static enum lang_layer current_lang = LANG_EN;

enum kb_layers { _LAYER0 = 0,  _LAYER1 = 1, // _LAYER2 = 2, _LAYER3 = 3, _LAYER4 = 4, _LAYER5 = 5, _LAYER6 = 6, _LAYER7 = 7,
                 NUM_LAYERS = 2 };

enum my_keycodes {
  KC_NEXT_LAYER = SAFE_RANGE,
  KC_NEXT_LANG,
  KC_ENC_UP,
  KC_ENC_DOWN,
  RGB_TOGGLE,
  RGB_NEXT,
  RGB_PREV,
  KC_DISP_CMINUS,
  KC_DISP_CONTRAST,
  KC_DISP_CPLUS
};




static bool encUpHigh, encDownHigh;

uint8_t encoder_read_state_kb(uint8_t index) {

    return index==0 ? ((uint8_t)encUpHigh) | ((uint8_t) encDownHigh<<1) : 0;
}

void encoder_init_state_kb(uint8_t index) {
    encUpHigh = true;
    encDownHigh = true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (!clockwise) {
        //prev_layer(NUM_LAYERS);
        register_code(KC_MS_WH_UP);
        unregister_code(KC_MS_WH_UP);
        //encDownHigh = true;
        //uprintf("UP");
    } else {
        //next_layer(NUM_LAYERS);
        register_code(KC_MS_WH_DOWN);
        unregister_code(KC_MS_WH_DOWN);
        //encUpHigh = true;
        //uprintf("DOWN");
    }

    //update_performed();
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LAYER0] = LAYOUT( KC_ESC,    KC_1,        KC_2,         KC_3,       KC_4,       KC_5,           KC_NEXT_LAYER, /*no key*/KC_NO,
                        KC_GRAVE,  KC_Q,        KC_W,         KC_E,       KC_R,       KC_T,           KC_EQUAL,     KC_ENC_UP,
                        KC_TAB,    KC_A,        KC_S,         KC_D,       KC_F,       KC_G,           KC_MINUS,     KC_ENC_DOWN,
                        KC_LSHIFT, KC_Z,        KC_X,         KC_C,       KC_V,       KC_B,           KC_CAPSLOCK,  KC_MS_BTN1,
                        KC_LCTL,   KC_LALT,     KC_NEXT_LANG, KC_APP,   KC_LWIN,    KC_SPACE,      KC_END,   KC_HOME
                        ),
    [_LAYER1] = LAYOUT( KC_NO,     KC_NO,           KC_NO,              KC_NO,              KC_NO,      KC_MEDIA_PREV_TRACK,    KC_NEXT_LAYER,        /*no key*/KC_NO,
                        RGB_PREV,  KC_AUDIO_VOL_UP, QK_DEBUG_TOGGLE,    KC_DISP_CMINUS,     KC_NO,      KC_MEDIA_PLAY_PAUSE,    KC_NO,                KC_ENC_UP,
                        RGB_TOGGLE,KC_AUDIO_MUTE,   QK_CLEAR_EEPROM,    KC_DISP_CONTRAST,   KC_NO,      KC_MEDIA_STOP,          KC_NO,                KC_ENC_DOWN,
                        RGB_NEXT,  KC_AUDIO_VOL_DOWN,QK_BOOTLOADER,     KC_DISP_CPLUS,     KC_NO,      KC_MEDIA_NEXT_TRACK,    KC_NO,                KC_MS_BTN1,
                        KC_LCTL,   KC_LALT,         KC_NO,            KC_APP,           KC_LWIN,    KC_SPACE,               KC_END,               KC_HOME
                        )
};

led_config_t g_led_config = {{// Key Matrix to LED Index
                              {0, 1, 2, 3, 4, 5, 6, NO_LED},
                              {7, 8, 9, 10, 11, 12, 13, NO_LED},
                              {14, 15, 16, 17, 18, 19, 20, NO_LED},
                              {21, 22, 23, 24, 25, 26, 27, NO_LED},
                              {28, 29, 30, 31, 32, 33, 34, 35}
                             },
                             {
                                 // LED Index to Physical Position
                                 {6, 9},   {36, 9},   {61, 5},  {85, 1},   {110, 5},  {135, 9},  {160, 9},
                                 {6, 33},  {36, 33},  {61, 29}, {85, 25},  {110, 19}, {135, 33}, {160, 33},
                                 {6, 58},  {36, 58},  {61, 54}, {85, 50},  {110, 54}, {135, 58}, {160, 58},
                                 {6, 83},  {36, 83},  {61, 79}, {85, 75},  {110, 79}, {135, 83}, {160, 83},
                                 {12, 107},{36, 107}, {61, 103},{85, 99},  {126, 113},{157, 118},{185, 127}, {196, 99}
                             },
                             {
                                 // LED Index to Flag
                                 4, 4, 4, 4, 4, 4, 4,
                                 4, 4, 4, 4, 4, 4, 4,
                                 4, 4, 4, 4, 4, 4, 4,
                                 4, 4, 4, 4, 4, 4, 4,
                                 4, 4, 4, 4, 4, 4, 4, 4
                             }};

void process_layer_switch_user(uint16_t new_layer);


void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}


struct diplay_info {
    uint8_t bitmask[NUM_SHIFT_REGISTERS];
};

#define BITMASK1(x) .bitmask = {~0, ~0, ~0, ~0, (uint8_t)(~(1<<x))}
#define BITMASK2(x) .bitmask = {~0, ~0, ~0, (uint8_t)(~(1<<x)), ~0}
#define BITMASK3(x) .bitmask = {~0, ~0, (uint8_t)(~(1<<x)), ~0, ~0}
#define BITMASK4(x) .bitmask = {~0, (uint8_t)(~(1<<x)), ~0, ~0, ~0}
#define BITMASK5(x) .bitmask = {(uint8_t)(~(1<<x)), ~0, ~0, ~0, ~0}

struct diplay_info key_display[] = {
        {BITMASK1(0)}, {BITMASK1(1)}, {BITMASK1(2)}, {BITMASK1(3)}, {BITMASK1(4)}, {BITMASK1(5)}, {BITMASK1(6)}, {BITMASK1(7)},
        {BITMASK2(0)}, {BITMASK2(1)}, {BITMASK2(2)}, {BITMASK2(3)}, {BITMASK2(4)}, {BITMASK2(5)}, {BITMASK2(6)}, {BITMASK2(7)},
        {BITMASK3(0)}, {BITMASK3(1)}, {BITMASK3(2)}, {BITMASK3(3)}, {BITMASK3(4)}, {BITMASK3(5)}, {BITMASK3(6)}, {BITMASK3(7)},
        {BITMASK4(0)}, {BITMASK4(1)}, {BITMASK4(2)}, {BITMASK4(3)}, {BITMASK4(4)}, {BITMASK4(5)}, {BITMASK4(6)}, {BITMASK4(7)},
        {BITMASK5(0)}, {BITMASK5(1)}, {BITMASK5(2)}, {BITMASK5(3)}, {BITMASK5(4)}, {BITMASK5(5)}, {BITMASK5(6)}, {BITMASK5(7)}
    };

enum {ALPHA = 26, NUM = 10, ADDITIONAL = 17};

const uint16_t* lang_plane [ALPHA + NUM + ADDITIONAL][NUM_LANG * 3] = {
    //           [  E N G L I S H - U S  ]          [          K O R E A N              ]      [          J A P A N E S E             ]
    //            glyph     shift   caps            glyph           shift           caps         glyph           shift           caps
    /* KC_A */   {u"a",     u"A",   NULL,           HANGEUL_MIEUM,  NULL,               NULL,   HIRAGANA_LETTER_TI, NULL,                   NULL},
    /* KC_B */   {u"b",     u"B",   NULL,           HANGEUL_YU,     NULL,               NULL,   HIRAGANA_LETTER_KO, NULL,                   NULL},
    /* KC_C */   {u"c",     u"C",   NULL,           HANGEUL_CHIEUCH,NULL,               NULL,   HIRAGANA_LETTER_SO, NULL,                   NULL},
    /* KC_D */   {u"d",     u"D",   NULL,           HANGEUL_IEUNG,  NULL,               NULL,   HIRAGANA_LETTER_SI, NULL,                   NULL},
    /* KC_E */   {u"e",     u"E",   NULL,           HANGEUL_TIKEUT, HANGEUL_SSANGTIKEUT,NULL,   HIRAGANA_LETTER_I,  HIRAGANA_LETTER_SMALL_I,NULL},
    /* KC_F */   {u"f",     u"F",   NULL,           HANGEUL_RIEUL,  NULL,               NULL,   HIRAGANA_LETTER_HA, NULL,                   NULL},
    /* KC_G */   {u"g",     u"G",   NULL,           HANGEUL_HIEUH,  NULL,               NULL,   HIRAGANA_LETTER_KI, NULL,                   NULL},
    /* KC_H */   {u"h",     u"H",   NULL,           HANGEUL_O,      NULL,               NULL,   HIRAGANA_LETTER_KU, NULL,                   NULL},
    /* KC_I */   {u"i",     u"I",   NULL,           HANGEUL_YA,     NULL,               NULL,   HIRAGANA_LETTER_RI, NULL,                   NULL},
    /* KC_J */   {u"j",     u"J",   NULL,           HANGEUL_EO,     NULL,               NULL,   HIRAGANA_LETTER_MA, NULL,                   NULL},
    /* KC_K */   {u"k",     u"K",   NULL,           HANGEUL_A,      NULL,               NULL,   HIRAGANA_LETTER_NO, NULL,                   NULL},
    /* KC_L */   {u"l",     u"L",   NULL,           HANGEUL_I,      NULL,               NULL,   HIRAGANA_LETTER_RI, NULL,                   NULL},
    /* KC_M */   {u"m",     u"M",   NULL,           HANGEUL_EU,     NULL,               NULL,   HIRAGANA_LETTER_MO, NULL,                   NULL},
    /* KC_N */   {u"n",     u"N",   NULL,           HANGEUL_U,      NULL,               NULL,   HIRAGANA_LETTER_MI, NULL,                   NULL},
    /* KC_O */   {u"o",     u"O",   NULL,           HANGEUL_AE,     HANGEUL_YAE,        NULL,   HIRAGANA_LETTER_RA, NULL,                   NULL},
    /* KC_P */   {u"p",     u"P",   NULL,           HANGEUL_E,      HANGEUL_YE,         NULL,   HIRAGANA_LETTER_SE, NULL,                   NULL},
    /* KC_Q */   {u"q",     u"Q",   NULL,           HANGEUL_PIEUP,  HANGEUL_SSANGPIEUP, NULL,   HIRAGANA_LETTER_TA, NULL,                   NULL},
    /* KC_R */   {u"r",     u"R",   NULL,           HANGEUL_KIYEOK, HANGEUL_SSANGKIYEOK,NULL,   HIRAGANA_LETTER_SU, NULL,                   NULL},
    /* KC_S */   {u"s",     u"S",   NULL,           HANGEUL_NIEUN,  NULL,               NULL,   HIRAGANA_LETTER_TO, NULL,                   NULL},
    /* KC_T */   {u"t",     u"T",   NULL,           HANGEUL_SIOS,   HANGEUL_SSANGSIOS,  NULL,   HIRAGANA_LETTER_KA, NULL,                   NULL},
    /* KC_U */   {u"u",     u"U",   NULL,           HANGEUL_YEO,    NULL,               NULL,   HIRAGANA_LETTER_NA, NULL,                   NULL},
    /* KC_V */   {u"v",     u"V",   NULL,           HANGEUL_PHIEUPH,NULL,               NULL,   HIRAGANA_LETTER_HI, NULL,                   NULL},
    /* KC_W */   {u"w",     u"W",   NULL,           HANGEUL_CIEUC,  HANGEUL_SSANGCIEUC, NULL,   HIRAGANA_LETTER_TE, NULL,                   NULL},
    /* KC_X */   {u"x",     u"X",   NULL,           HANGEUL_THIEUTH,NULL,               NULL,   HIRAGANA_LETTER_SA, NULL,                   NULL},
    /* KC_Y */   {u"y",     u"Y",   NULL,           HANGEUL_YO,     NULL,               NULL,   HIRAGANA_LETTER_N,  NULL,                   NULL},
    /* KC_Z */   {u"z",     u"Z",   NULL,           HANGEUL_KHIEUKH,NULL,               NULL,   HIRAGANA_LETTER_TU, HIRAGANA_LETTER_SMALL_TU,NULL},

    /* KC_1 */   {u"1",     u"!",   u"1",           NULL,           NULL,               NULL,   HIRAGANA_LETTER_NU, NULL,                   NULL},
    /* KC_2 */   {u"2",     u"@",   u"2",           NULL,           NULL,               NULL,   HIRAGANA_LETTER_HU, NULL,                   NULL},
    /* KC_3 */   {u"3",     u"#",   u"3",           NULL,           NULL,               NULL,   HIRAGANA_LETTER_A,  HIRAGANA_LETTER_SMALL_A,NULL},
    /* KC_4 */   {u"4",     u"$",   u"4",           NULL,           NULL,               NULL,   HIRAGANA_LETTER_U,  HIRAGANA_LETTER_SMALL_U,NULL},
    /* KC_5 */   {u"5",     u"%",   u"5",           NULL,           NULL,               NULL,   HIRAGANA_LETTER_E,  HIRAGANA_LETTER_SMALL_E,NULL},
    /* KC_6 */   {u"6",     u"^",   u"6",           NULL,           NULL,               NULL,   HIRAGANA_LETTER_O,  HIRAGANA_LETTER_SMALL_O,NULL},
    /* KC_7 */   {u"7",     u"&",   u"7",           NULL,           NULL,               NULL,   HIRAGANA_LETTER_YA, HIRAGANA_LETTER_SMALL_YA,NULL},
    /* KC_8 */   {u"8",     u"*",   u"8",           NULL,           NULL,               NULL,   HIRAGANA_LETTER_YU, HIRAGANA_LETTER_SMALL_YU,NULL},
    /* KC_9 */   {u"9",     u"(",   u"9",           NULL,           NULL,               NULL,   HIRAGANA_LETTER_YO, HIRAGANA_LETTER_SMALL_YO,NULL},
    /* KC_0 */   {u"0",     u")",   u"0",           NULL,           NULL,               NULL,   HIRAGANA_LETTER_WA, HIRAGANA_LETTER_WO,     NULL},

/*KC_ENTER     */{u"Ent",   NULL,   NULL,           NULL,           NULL,               NULL,   NULL,               NULL,                   NULL},  
/*KC_ESCAPE    */{u"ESC",   NULL,   NULL,           NULL,           NULL,               NULL,   NULL,               NULL,                   NULL}, 
/*KC_BACKSPACE */{ICON_BACKSPACE,NULL,NULL,         NULL,           NULL,               NULL,   NULL,               NULL,                   NULL}, 
/*KC_TAB       */{u"Tab",   NULL,   NULL,           NULL,           NULL,               NULL,   NULL,               NULL,                   NULL}, 
/*KC_SPACE     */{ICON_SPACE,NULL,  NULL,           NULL,           NULL,               NULL,   NULL,               NULL,                   NULL},  
/*KC_MINUS     */{u"-",     u"_",   u"-",           NULL,           NULL,               NULL,   HIRAGANA_LETTER_HO, KH_PROLONGED_SOUND_MARK,NULL}, 
/*KC_EQUAL     */{u"=",     u"+",   u"=",           NULL,           NULL,               NULL,   HIRAGANA_LETTER_HE, NULL,                   NULL},  
/*KC_LBRC      */{u"[",     u"{",   u"[",           NULL,           NULL,               NULL,   KH_VOICED_SOUND_MARK,LFET_CORNER_BRACKET,   NULL}, 
/*KC_RBRC      */{u"]",     u"}",   u"]",           NULL,           NULL,               NULL,   KH_SEMI_VOICED_SOUND_MARK,RIGHT_CORNER_BRACKET,NULL}, 
/*KC_BACKSLASH */{u"\\",    u"|",   u"\\",          NULL,           NULL,               NULL,   HIRAGANA_LETTER_MU, NULL,                   NULL},
/*KC_NONUS_HASH*/{u"#",     u"~",   u"#",           NULL,           NULL,               NULL,   NULL,               NULL,                   NULL}, 
/*KC_SEMICOLON */{u";",     u":",   u";",           NULL,           NULL,               NULL,   HIRAGANA_LETTER_RE, NULL,                   NULL},
/*KC_QUOTE     */{u"'",     u"\"",  u"'",           NULL,           NULL,               NULL,   HIRAGANA_LETTER_KE, NULL,                   NULL}, 
/*KC_GRAVE     */{u"`",     u"~",   u"`",           NULL,           NULL,               NULL,   HIRAGANA_LETTER_RO, NULL,                   NULL},
/*KC_COMMA     */{u",",     u"<",   u",",           NULL,           NULL,               NULL,   HIRAGANA_LETTER_NE, CJK_IDEOGRAPHIC_COMMA,  NULL},
/*KC_DOT       */{u".",     u">",   u".",           NULL,           NULL,               NULL,   HIRAGANA_LETTER_RU, CJK_IDEOGRAPHIC_FULL_STOP,NULL},
/*KC_SLASH     */{u"/",     u"?",   u"/",           NULL,           NULL,               NULL,   HIRAGANA_LETTER_ME, KATAKANA_MIDDLE_DOT,    NULL}
};

#define CJK_IDEOGRAPHIC_COMMA                       u"\x3001"
#define CJK_IDEOGRAPHIC_FULL_STOP                   u"\x3002"
#define LFET_CORNER_BRACKET                         u"\x300C"
#define RIGHT_CORNER_BRACKET                        u"\x300D"
#define KATAKANA_MIDDLE_DOT                         u"\x30FB"
#define KH_PROLONGED_SOUND_MARK                     u"\x30FC"


const uint16_t* translate_keycode(uint16_t keycode, bool shift, bool caps_lock) {
    if(keycode < KC_A || keycode > KC_SLASH) return NULL;

    uint16_t index = keycode - KC_A;
    
    uint8_t used_lang = current_lang;

    const uint16_t* lower_case = lang_plane[index][used_lang*3];
    if(lower_case==NULL) {
        lower_case = lang_plane[index][0]; //english as backup
        used_lang = 0;
    }

    if(caps_lock) {
        const uint16_t* caps_case = lang_plane[index][used_lang*3 + 2];
        if(caps_case!=NULL) {
            if(!shift) {
                return caps_case;
            }
        } else {
           shift = !shift;
        }
    }

    if(shift) {
        const uint16_t* upper_case = lang_plane[index][used_lang*3 + 1];
        if(upper_case!=NULL) {
            return upper_case;
        }
    }
    return lower_case;
}

const uint16_t* keycode_to_disp_text(uint16_t keycode, led_t state) {
    switch (keycode) {
        case KC_NUM_LOCK:
            return !state.num_lock ? u"Num" ICON_NUMLOCK_OFF : u"Num" ICON_NUMLOCK_ON;
        case KC_KP_SLASH:
            return u"/";
        case KC_KP_ASTERISK:
            return u"*";
        case KC_KP_MINUS:
            return u"-";
        case KC_KP_7:
            return !state.num_lock ? u"Home" : u"7";
        case KC_KP_8:
            return !state.num_lock ? u"   " ICON_UP : u"8";
        case KC_KP_9:
            return !state.num_lock ? u"PgUp" : u"9";
        case KC_KP_PLUS:
            return u"+";
        case KC_KP_4:
            return !state.num_lock ? u"  " ICON_LEFT : u"4";
        case KC_KP_5:
            return !state.num_lock ? u"" : u"5";
        case KC_KP_6:
            return !state.num_lock ? u"  " ICON_RIGHT : u"6";
        case KC_KP_EQUAL:
            return u"=";
        case KC_KP_1:
            return !state.num_lock ? u"End" : u"1";
        case KC_KP_2:
            return !state.num_lock ? u"   " ICON_DOWN : u"2";
        case KC_KP_3:
            return !state.num_lock ? u"PgDn" : u"3";
        case KC_CALCULATOR:
            return u"Calc";
        case KC_KP_0:
            return !state.num_lock ? u"Ins" : u"0";
        case KC_KP_DOT:
            return !state.num_lock ? u"Del" : u".";
        case KC_KP_ENTER:
            return u"Enter";
        case QK_BOOTLOADER:
            return u"BLdr";
        case QK_DEBUG_TOGGLE:
            return u"Dbg";
        case QK_CLEAR_EEPROM:
            return u"ClrEE";
        case RGB_PREV:
            return u"R  " ICON_LEFT;
        case RGB_TOGGLE:
            return rgb_matrix_is_enabled() ? u"G " ICON_SWITCH_ON : u"G " ICON_SWITCH_OFF;
        case RGB_NEXT:
            return u"B  " ICON_RIGHT;
        case KC_MEDIA_NEXT_TRACK:
            return ICON_RIGHT ICON_RIGHT;
        case KC_MEDIA_PLAY_PAUSE:
            return u"  " ICON_RIGHT;
        case KC_MEDIA_STOP:
            return u"Stop";
        case KC_MEDIA_PREV_TRACK:
            return ICON_LEFT ICON_LEFT;
        case KC_MS_ACCEL0:
            return u">>";
        case KC_MS_ACCEL1:
            return u">>>";
        case KC_MS_ACCEL2:
            return u">>>>";
        case KC_MS_BTN1:
            return u"  " ICON_LMB;
        case KC_MS_BTN2:
            return u"  " ICON_RMB;
        case KC_MS_BTN3:
            return u"  " ICON_MMB;
        case KC_MS_UP:
            return u"  " ICON_UP;
        case KC_MS_DOWN:
            return u"  " ICON_DOWN;
        case KC_MS_LEFT:
            return u"  " ICON_LEFT;
        case KC_MS_RIGHT:
            return u"  " ICON_RIGHT;
        case KC_AUDIO_MUTE:
            return u"Mute";
        case KC_AUDIO_VOL_DOWN:
            return u"  " ICON_VOL_DOWN;
        case KC_AUDIO_VOL_UP:
            return u"  " ICON_VOL_UP;
        case KC_NEXT_LAYER:
            return u"Nxt" ICON_LAYER;
        case KC_PRINT_SCREEN:
            return u"PScn";
        case KC_SCROLL_LOCK:
            return u"ScLk";
        case KC_PAUSE:
            return u"Pause";
        case KC_INSERT:
            return u"Ins";
        case KC_HOME:
            return u"Home";
        case KC_PAGE_UP:
            return u"PgUp";
        case KC_PAGE_DOWN:
            return u"PgDn";
        case KC_DELETE:
            return u"Del";
        case KC_END:
            return u"End";
        case KC_F1:
            return u" F1";
        case KC_F2:
            return u" F2";
        case KC_F3:
            return u" F3";
        case KC_F4:
            return u" F4";
        case KC_F5:
            return u" F5";
        case KC_F6:
            return u" F6";
        case KC_F7:
            return u" F7";
        case KC_F8:
            return u" F8";
        case KC_F9:
            return u" F9";
        case KC_F10:
            return u" F10";
        case KC_F11:
            return u" F11";
        case KC_F12:
            return u" F12";
        case KC_LEFT_CTRL:
            return u"LCtrl";
        case KC_LEFT_ALT:
            return u"LAlt";
        case KC_TAB:
            return u"Tab";
        case KC_LWIN:
            return u"LWin";
        case KC_LEFT:
            return u"  " ICON_LEFT;
        case KC_RIGHT:
            return u"  " ICON_RIGHT;
        case KC_UP:
            return u"  " ICON_UP;
        case KC_DOWN:
            return u"  " ICON_DOWN;
        case KC_CAPSLOCK:
            return state.caps_lock ? u"CL " ICON_CAPSLOCK_ON : u"CL " ICON_CAPSLOCK_OFF;
        case KC_LSHIFT:
            return state.caps_lock ? u"L " ICON_SHIFT u"  " ICON_CAPSLOCK_ON : u"L " ICON_SHIFT u"  " ICON_CAPSLOCK_OFF;
        case KC_RSHIFT:
            return state.caps_lock ? u"R " ICON_SHIFT u"  " ICON_CAPSLOCK_ON : u"R " ICON_SHIFT u"  " ICON_CAPSLOCK_OFF;
        case KC_NO:
            return u"";
        case KC_DISP_CMINUS:
            return u" -";
        case KC_DISP_CONTRAST:
            return u"Bright";
        case KC_DISP_CPLUS:
            return u" +";
        case KC_NEXT_LANG:
            {
                switch((current_lang + 1) % NUM_LANG) {
                    case LANG_KO: return u"KOR";
                    case LANG_JP: return u"JPN";
                    default: return u"ENG";
                }
            }
        case KC_APP:
            return u"Ctx";
        default:
            {
                bool shift = ((get_mods() & MOD_MASK_SHIFT)!=0);
                const uint16_t* text = translate_keycode(keycode, shift, state.caps_lock);
                if(text!=NULL) {
                    return text;
                }
            }
            break;
    }
    return u"[?]";
}

void process_layer_switch_user(uint16_t new_layer) {
    layer_move(new_layer);
    led_t state = host_keyboard_led_state();

    // keypos_t key;
    for (uint8_t r = 0; r < MATRIX_ROWS; ++r) {
        for (uint8_t c = 0; c < MATRIX_COLS; ++c) {
            //key.col           = c;
            //key.row           = r;
            uint16_t keycode  = keymaps[new_layer][r][c];
            uint8_t  disp_idx = LAYOUT_TO_INDEX(r, c);

            if (disp_idx != 255) {
                const uint16_t* text = keycode_to_disp_text(keycode, state);
                sr_shift_out_buffer_latch(key_display[disp_idx].bitmask, sizeof(key_display->bitmask));
                kdisp_set_buffer(0x00);
                kdisp_write_gfx_text(ALL_FONTS, sizeof(ALL_FONTS) / sizeof(GFXfont*), 26, 22, text);
                kdisp_send_buffer();
            }
        }
    }
}

/*
void clear_all_displays(void) {
    select_all_displays();
    kdisp_set_buffer(0x00);
    kdisp_send_buffer();
}

void display_message(uint8_t row, uint8_t col, const uint16_t* message, const GFXfont* font) {

    const GFXfont* displayFont [] = {font};
    uint8_t index = 0;
    for (uint8_t c = col; c < MATRIX_COLS; ++c) {
        uint8_t  disp_idx = LAYOUT_TO_INDEX(row, c);

        if (disp_idx != 255) {
            const uint16_t text[2] = {message[index], 0};
            sr_shift_out_buffer_latch(key_display[disp_idx].bitmask, sizeof(key_display->bitmask));
            kdisp_set_buffer(0x00);
            kdisp_write_gfx_text(displayFont, 1, 49, 38, text);
            kdisp_send_buffer();
        }
        index++;
        if(message[index]==0) {
            return;
        }
    }

}
*/

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (record->event.pressed) {
        switch (keycode) {
            case QK_BOOTLOADER:
                uprintf("Enter Bootloader...");
                clear_all_displays();
                display_message(1, 1, u"BOOT-", &FreeSansBold24pt7b);
                display_message(3, 0, u"LOADER!", &FreeSansBold24pt7b);
                break;
            case KC_ENC_DOWN:
                encDownHigh = !encDownHigh;
                break;
            case KC_ENC_UP:
                encUpHigh = !encUpHigh;
                break;
        }
    }

    return display_wakeup(record);
}

void post_process_record_user(uint16_t keycode, keyrecord_t* record) {
    uint8_t disp_idx = LAYOUT_TO_INDEX(record->event.key.row, record->event.key.col);
    const uint8_t* bitmask = key_display[disp_idx].bitmask;
    sr_shift_out_buffer_latch(bitmask, sizeof(key_display->bitmask));
    if (record->event.pressed) {
        set_last_key(keycode);
        if (disp_idx != 255) {
            kdisp_invert(true);
        }
    } else {
        if (disp_idx != 255) {
            kdisp_invert(false);
        }
    }

    if(!record->event.pressed) {
        switch(keycode) {
            case RGB_TOGGLE:
                rgb_matrix_toggle_noeeprom();
                force_layer_switch();
                break;
            case KC_RIGHT_SHIFT:
            case KC_LEFT_SHIFT:
                force_layer_switch();
                break;
            case KC_NEXT_LAYER:
                next_layer(NUM_LAYERS);
                break;
            case RGB_NEXT:
                rgb_matrix_step_noeeprom();
                break;
            case RGB_PREV:
                rgb_matrix_step_reverse_noeeprom();
                break;
            case KC_DISP_CMINUS:
                dec_brightness();
                break;
            case KC_DISP_CPLUS:
                inc_brightness();
                break;
            case KC_NEXT_LANG:
                current_lang = (current_lang + 1) % NUM_LANG;
                force_layer_switch();
                break;
            /*case KC_ENC_DOWN:
                encDownHigh = true;
                break;
            case KC_ENC_UP:
                encUpHigh = true;
                break;*/
            default:
                break;
        }
    } else {
        switch (keycode)
        {
        case KC_RIGHT_SHIFT:
        case KC_LEFT_SHIFT:
            force_layer_switch();
            break;
        default:
            break;
        }
    }

    uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %d, time: %u, interrupt: %d, count: %u display: %d SR bitmask: 0x%02X%02X%02X%02X%02X\n",
        keycode, record->event.key.col, record->event.key.row, record->event.pressed ? 1 : 0,
        record->event.time, record->tap.interrupted ? 1 : 0, record->tap.count, disp_idx, bitmask[4], bitmask[3], bitmask[2], bitmask[1], bitmask[0]);

   update_performed();
};

bool led_update_user(led_t led_state) {
    force_layer_switch();
    return true;
}

uint8_t selsect_display(uint8_t row, uint8_t col) {
    uint8_t  disp_idx = LAYOUT_TO_INDEX(row, col);
    if (disp_idx != 255) {
        sr_shift_out_buffer_latch(key_display[disp_idx].bitmask, sizeof(key_display->bitmask));
    }
    return disp_idx;
}

void show_splash_screen(void) {
    clear_all_displays();
    /*display_message(1, 1, u"POLY", &FreeSansBold24pt7b);
    display_message(3, 0, u"KEYBOAR", &FreeSansBold24pt7b);
    display_message(4, 7, u"D", &FreeSansBold24pt7b);*/
    display_message(1, 1, u"POLY", &FreeSansBold24pt7b);
    display_message(2, 2, u"KB", &FreeSansBold24pt7b);
}


