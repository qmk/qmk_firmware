#include QMK_KEYBOARD_H

#include "polyatom.h"
#include "print.h"
#include "base/disp_array.h"
#include "base/shift_reg.h"
#include "fonts/gfx_used_fonts.h"

#include "quantum/quantum_keycodes.h"

#include "lang/lang_lut.h"

static enum lang_layer current_lang = 
    /*[[[cog
    import cog
    import os
    from openpyxl import load_workbook
    wb = load_workbook(filename = os.path.join(os.path.abspath(os.path.dirname(cog.inFile)), "..", "..", "..", "lang", "lang_lut.xlsx"))
    sheet = wb['key_lut']

    languages = []
    lang_index = 0
    lang_key = sheet["B1"].value
    while lang_key:
        languages.append(lang_key)
        if lang_index==0:
            cog.outl(f"{lang_key};")
        lang_index = lang_index + 1
        lang_key = sheet.cell(row = 1, column = 2 + lang_index*3).value
    ]]]*/
    LANG_EN;
    //[[[end]]]

enum kb_layers { _LAYER0 = 0,  _LAYER1 = 1, _LAYER2 = 2, //, _LAYER3 = 3, _LAYER4 = 4, _LAYER5 = 5, _LAYER6 = 6, _LAYER7 = 7,
                 NUM_LAYERS = 2 };

enum my_keycodes {
  KC_NXTL = SAFE_RANGE,
  KC_LANG,
  //KC_NEXT_LANG,
  KC_ENC_UP,
  KC_ENC_DOWN,
  RGB_TOGGLE,
  RGB_NEXT,
  RGB_PREV,
  KC_DARKER,
  KC_CONTRAST,
  KC_BRIGTHER,
  KC_SAVE_EE,
  KC_RST_DSP,
  /*[[[cog
    for lang in languages:
        cog.outl(f"KC_{lang},")
  ]]]*/
  KC_LANG_EN,
  KC_LANG_DE,
  KC_LANG_FR,
  KC_LANG_ES,
  KC_LANG_PT,
  KC_LANG_IT,
  KC_LANG_TR,
  KC_LANG_KO,
  KC_LANG_JA,
  KC_LANG_AR,
  //[[[end]]]
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
    [_LAYER0] = SPLIT_LAYOUT(
        KC_GRAVE,       KC_1,       KC_2,        KC_3,       KC_4,       KC_5,       KC_MINUS,    /*no key*/KC_NO,    
        KC_TAB,         KC_Q,       KC_W,        KC_E,       KC_R,       KC_T,       KC_LBRC,   KC_ENC_UP,          
        KC_CAPSLOCK,    KC_A,       KC_S,        KC_D,       KC_F,       KC_G,       KC_SCLN,   KC_ENC_DOWN,        
        KC_LSHIFT,      KC_Z,       KC_X,        KC_C,       KC_V,       KC_B,       KC_ESC,     KC_MS_BTN1,/*enc*/  
        KC_LCTL,        KC_LALT,    KC_LANG,     KC_APP,     KC_LWIN,    KC_SPACE,   KC_END,     KC_HOME,            
        
/*!key*/KC_NO,          KC_EQUAL,   KC_6,        KC_7,       KC_8,       KC_9,       KC_0,       KC_BSPC, 
        KC_ENC_UP,      KC_RBRC,    KC_Y,        KC_U,       KC_I,       KC_O,       KC_P,       KC_BSLS,    
        KC_ENC_DOWN,    KC_QUOTE,   KC_H,        KC_J,       KC_K,       KC_L,       KC_L,       KC_NUHS,     
 /*enc*/KC_MS_BTN1,     KC_UP,      KC_N,        KC_M,       KC_COMMA,   KC_DOT,     KC_SLASH,   KC_RSHIFT,
        KC_ENT,         KC_LEFT,    KC_DOWN,     KC_RIGHT,   KC_LNG1,    KC_RWIN,    KC_NXTL,    KC_RCTL
        ),

    [_LAYER1] = SPLIT_LAYOUT(
        KC_NO,          KC_NO,      KC_SAVE_EE,  KC_NO,      KC_NO,      KC_MPRV,    KC_NXTL,    /*no key*/KC_NO,    
        RGB_PREV,       KC_VOLU,    DB_TOGG,     KC_DARKER,  KC_NO,      KC_MPLY,    KC_NO,      KC_ENC_UP,          
        RGB_TOGGLE,     KC_MUTE,    EE_CLR,      KC_CONTRAST,KC_RST_DSP, KC_MSTP,    KC_NO,      KC_ENC_DOWN,        
        RGB_NEXT,       KC_VOLD,    QK_BOOT,     KC_BRIGTHER,KC_NO,      KC_MNXT,    KC_NO,      KC_MS_BTN1,/*enc*/  
        KC_NO,          KC_NO,      QK_MAKE,     QK_RBT,     KC_NO,      KC_NO,      KC_NO,      KC_NO,              

/*!key*/KC_NO,          KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
        KC_NO,          KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
        KC_NO,          KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
 /*enc*/KC_NO,          KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
        KC_NO,          KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO
        ),

    [_LAYER2] = SPLIT_LAYOUT(
        KC_LEAD,        KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      /*no key*/KC_NO,    
        KC_NO,          KC_LANG_PT, KC_LANG_ES, KC_LANG_AR, KC_NO,      KC_NO,      KC_NO,      KC_ENC_UP,          
        KC_NO,          KC_LANG_FR, KC_LANG_DE, KC_LANG_JA, KC_LANG_TR, KC_NO,      KC_NO,      KC_ENC_DOWN,        
        KC_NO,          KC_LANG_IT, KC_LANG_EN, KC_LANG_KO, KC_NO,      KC_NO,      KC_NO,      KC_MS_BTN1,/*enc*/  
        KC_NO,          KC_NO,      KC_LANG,    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,              

/*!key*/KC_NO,          KC_NO,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,
        KC_NO,          KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
        KC_NO,          KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
 /*enc*/KC_NO,          KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
        KC_NO,          KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO         
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

const uint16_t* keycode_to_disp_text(uint16_t keycode, led_t state) {
    switch (keycode) {
        case KC_LEAD:
            return u"Lead";
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
        case KC_NXTL:
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
            return PRIVATE_HOME;
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
        case KC_RIGHT_CTRL:
            return u"Ctrl";
        case KC_LEFT_ALT:
            return u"Alt";
        case KC_RIGHT_ALT:
            return u"AltGr";
        case KC_TAB:
            return u"Tab";
        case KC_LWIN:
        case KC_RWIN:
            return  DINGBAT_BLACK_DIA_X;
        case KC_LEFT:
            return u"  " ICON_LEFT;
        case KC_RIGHT:
            return u"  " ICON_RIGHT;
        case KC_UP:
            return u"  " ICON_UP;
        case KC_DOWN:
            return u"  " ICON_DOWN;
        case KC_CAPSLOCK:
            return state.caps_lock ? u"Cap" ICON_CAPSLOCK_ON : u"Cap" ICON_CAPSLOCK_OFF;
        case KC_LSHIFT:
        case KC_RSHIFT:
            return u" " ICON_SHIFT;
        case KC_NO:
            return u"";
        case KC_DARKER:
            return u" -";
        case KC_CONTRAST:
            return u"Bright";
        case KC_BRIGTHER:
            return u" +";
        case KC_LANG:
            return PRIVATE_WORLD;
        case QK_MAKE:
            return u"Make";
        case QK_REBOOT:
            return u"Reset";
        case KC_RST_DSP:
            return u"Reset\r\vDisp";
        case KC_SAVE_EE:
            return u"Save\r\v\tEE";
        //case KC_NEXT_LANG: return u"Next";
            /*{
                switch((current_lang + 1) % NUM_LANG) {
                    case LANG_DE: return u"Nxt D";
                    case LANG_KO: return u"Nxt K";
                    case LANG_JA: return u"Nxt J";
                    case LANG_AR: return u"Nxt A";
                    default: return u"Nxt E";
                }
            }*/

        /*[[[cog
            for lang in languages:
                short = lang.split("_")[1]
                cog.outl(f'case KC_{lang}: return current_lang=={lang} ? u"[{short}]" : u" {short}";')
        ]]]*/
        case KC_LANG_EN: return current_lang==LANG_EN ? u"[EN]" : u" EN";
        case KC_LANG_DE: return current_lang==LANG_DE ? u"[DE]" : u" DE";
        case KC_LANG_FR: return current_lang==LANG_FR ? u"[FR]" : u" FR";
        case KC_LANG_ES: return current_lang==LANG_ES ? u"[ES]" : u" ES";
        case KC_LANG_PT: return current_lang==LANG_PT ? u"[PT]" : u" PT";
        case KC_LANG_IT: return current_lang==LANG_IT ? u"[IT]" : u" IT";
        case KC_LANG_TR: return current_lang==LANG_TR ? u"[TR]" : u" TR";
        case KC_LANG_KO: return current_lang==LANG_KO ? u"[KO]" : u" KO";
        case KC_LANG_JA: return current_lang==LANG_JA ? u"[JA]" : u" JA";
        case KC_LANG_AR: return current_lang==LANG_AR ? u"[AR]" : u" AR";
        //[[[end]]]
        case KC_LNG1:
            return u"Han/Y";
        case KC_APP:
            return u" Ctx";
        default:
            {
                bool shift = ((get_mods() & MOD_MASK_SHIFT)!=0);
                const uint16_t* text = translate_keycode(current_lang, keycode, shift, state.caps_lock);
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
    uint8_t offset = is_master() ? MATRIX_ROWS_PER_SIDE : 0;

    // keypos_t key;
    for (uint8_t r = 0; r < MATRIX_ROWS_PER_SIDE; ++r) {
        for (uint8_t c = 0; c < MATRIX_COLS; ++c) {
            //key.col           = c;
            //key.row           = r;
            uint16_t keycode  = keymaps[new_layer][r+offset][c];
            uint8_t  disp_idx = LAYOUT_TO_INDEX(r, c);

            if (disp_idx != 255) {
                const uint16_t* text = keycode_to_disp_text(keycode, state);
                sr_shift_out_buffer_latch(key_display[disp_idx].bitmask, sizeof(key_display->bitmask));
                kdisp_set_buffer(0x00);
                kdisp_write_gfx_text(ALL_FONTS, sizeof(ALL_FONTS) / sizeof(GFXfont*), 28, 22, text);
                kdisp_send_buffer();
            }
        }
    }
}

void display_message(uint8_t row, uint8_t col, const uint16_t* message, const GFXfont* font) {

    const GFXfont* displayFont [] = {font};
    uint8_t index = 0;
    for (uint8_t c = 0; c < MATRIX_COLS; ++c) {

        uint8_t disp_idx = LAYOUT_TO_INDEX(row, c);

        if (disp_idx != 255) {
            
            sr_shift_out_buffer_latch(key_display[disp_idx].bitmask, sizeof(key_display->bitmask));
            kdisp_set_buffer(0x00);
            
            if(c>=col && message[index]!=0) {
                const uint16_t text[2] = {message[index], 0};
                kdisp_write_gfx_text(displayFont, 1, 49, 38, text);
                index++;
            }
            kdisp_send_buffer();
        }
    }
}

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
    uint8_t disp_idx = LAYOUT_TO_INDEX(record->event.key.row % MATRIX_ROWS_PER_SIDE, record->event.key.col );
    const uint8_t* bitmask = key_display[disp_idx].bitmask;
    sr_shift_out_buffer_latch(bitmask, sizeof(key_display->bitmask));
    
    if((is_master() && record->event.key.row >= MATRIX_ROWS_PER_SIDE) ||
       (!is_master() && record->event.key.row < MATRIX_ROWS_PER_SIDE) ) {
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
    }

    if(keycode==KC_CAPSLOCK) {
        force_layer_switch();
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
            case KC_NXTL:
                next_layer(NUM_LAYERS);
                break;
            case RGB_NEXT:
                rgb_matrix_step_noeeprom();
                break;
            case RGB_PREV:
                rgb_matrix_step_reverse_noeeprom();
                break;
            case KC_DARKER:
                dec_brightness();
                break;
            case KC_BRIGTHER:
                inc_brightness();
                break;
            case KC_SAVE_EE:
                rgb_matrix_mode(rgb_matrix_get_mode());
                if(rgb_matrix_is_enabled()) {
                    rgb_matrix_enable();
                } else {
                    rgb_matrix_disable();
                }
                break;
            case KC_RST_DSP:
                kdisp_init(NUM_SHIFT_REGISTERS, true);
                break;
            /*case KC_NEXT_LANG:
                current_lang = (current_lang + 1) % NUM_LANG;
                process_layer_switch_user(_LAYER0);
                break;*/
            /*[[[cog
            for lang in languages:
                cog.outl(f'case KC_{lang}: current_lang = {lang}; process_layer_switch_user(_LAYER0); break;')
            ]]]*/
            case KC_LANG_EN: current_lang = LANG_EN; process_layer_switch_user(_LAYER0); break;
            case KC_LANG_DE: current_lang = LANG_DE; process_layer_switch_user(_LAYER0); break;
            case KC_LANG_FR: current_lang = LANG_FR; process_layer_switch_user(_LAYER0); break;
            case KC_LANG_ES: current_lang = LANG_ES; process_layer_switch_user(_LAYER0); break;
            case KC_LANG_PT: current_lang = LANG_PT; process_layer_switch_user(_LAYER0); break;
            case KC_LANG_IT: current_lang = LANG_IT; process_layer_switch_user(_LAYER0); break;
            case KC_LANG_TR: current_lang = LANG_TR; process_layer_switch_user(_LAYER0); break;
            case KC_LANG_KO: current_lang = LANG_KO; process_layer_switch_user(_LAYER0); break;
            case KC_LANG_JA: current_lang = LANG_JA; process_layer_switch_user(_LAYER0); break;
            case KC_LANG_AR: current_lang = LANG_AR; process_layer_switch_user(_LAYER0); break;
            //[[[end]]]
            case KC_F1:case KC_F2:case KC_F3:case KC_F4:case KC_F5:case KC_F6:
            case KC_F7:case KC_F8:case KC_F9:case KC_F10:case KC_F11:case KC_F12:
                process_layer_switch_user(_LAYER0);
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
        case KC_LANG:
            if(biton32(layer_state)==_LAYER2) {
                current_lang = (current_lang + 1) % NUM_LANG;
                process_layer_switch_user(_LAYER0);
            } else {
                process_layer_switch_user(_LAYER2);
            }
            break;
        default:
            break;
        }
    }

    uprintf("Key 0x%04X, col/row: %u/%u, %s, time: %u, int: %d, cnt: %u disp#: %d 0x%02X%02X%02X%02X%02X\n",
        keycode, record->event.key.col, record->event.key.row, record->event.pressed ? "DN" : "UP",
        record->event.time, record->tap.interrupted ? 1 : 0, record->tap.count, disp_idx, bitmask[4], bitmask[3], bitmask[2], bitmask[1], bitmask[0]);

   update_performed();
};

// uint8_t select_display(uint8_t row, uint8_t col) {
//     if(is_master()) {
//         col -= MATRIX_COLS;
//     }

//     uint8_t  disp_idx = LAYOUT_TO_INDEX(row, col);
//     if (disp_idx != 255) {
//         sr_shift_out_buffer_latch(key_display[disp_idx].bitmask, sizeof(key_display->bitmask));
//     }
//     return disp_idx;
// }

void show_splash_screen(void) {
    clear_all_displays();
    /*display_message(1, 1, u"POLY", &FreeSansBold24pt7b);
    display_message(3, 0, u"KEYBOAR", &FreeSansBold24pt7b);
    display_message(4, 7, u"D", &FreeSansBold24pt7b);*/
    display_message(1, 1, u"POLY", &FreeSansBold24pt7b);
    display_message(2, 2, u"KB", &FreeSansBold24pt7b);
}

#ifdef OLED_ENABLE
void keyboard_pre_init_user(void) {
    setPinInputHigh(I2C1_SDA_PIN);
}
#endif
