#include QMK_KEYBOARD_H

#include "polykybd.h"
#include "split72/split72.h"
#include "base/disp_array.h"
#include "base/helpers.h"
#include "base/spi_helper.h"
#include "base/shift_reg.h"
#include "base/text_helper.h"
#include "base/fonts/NotoSans_Regular_Base_11pt.h"
#include "base/fonts/NotoSans_Medium_Base_8pt.h"
#include "base/fonts/gfx_used_fonts.h"

#include "quantum/quantum_keycodes.h"
#include "quantum/keymap_extras/keymap_german.h"

#include "raw_hid.h"
#include "oled_driver.h"
#include "version.h"
#include "print.h"

#include <transactions.h>

#include "lang/lang_lut.h"

#define FULL_BRIGHT 50
#define MIN_BRIGHT 1
#define DISP_OFF 0
#define BRIGHT_STEP 1

//6 sec
#define FADE_TRANSITION_TIME 6000
//1 min
#define FADE_OUT_TIME 60000
//20 min
#define TURN_OFF_TIME 1200000
//#define TURN_OFF_TIME   8000000

/*[[[cog
import cog
import os
from openpyxl import load_workbook
wb = load_workbook(filename = os.path.join(os.path.abspath(os.path.dirname(cog.inFile)), "lang", "lang_lut.xlsx"))
sheet = wb['key_lut']

languages = []
lang_index = 0
lang_key = sheet["B1"].value
while lang_key:
    languages.append(lang_key)
    if lang_index==0:
        cog.outl(f"static enum lang_layer g_lang_init = {lang_key};")
    lang_index = lang_index + 1
    lang_key = sheet.cell(row = 1, column = 2 + lang_index*3).value
]]]*/
static enum lang_layer g_lang_init = LANG_EN;
//[[[end]]]

enum kb_layers {
    _BL = 0x00,
    _L0 = _BL,
    _L1,
    _L2,
    _L3,
    _L4,
    _FL0,
    _FL1,
    _NL,
    _UL,
    _SL,
    _LL,
    _ADDLANG1 };

enum my_keycodes {
    KC_LANG = SAFE_RANGE,
    KC_DMIN,
    KC_DMAX,
    KC_DDIM,
    KC_DBRI,
    KC_DHLF,
    KC_D1Q,
    KC_D3Q,
    KC_BASE,
    KC_L0,
    KC_L1,
    KC_L2,
    KC_L3,
    KC_L4,
    KC_DEADKEY,
    /*[[[cog
      for lang in languages:
          cog.out(f"KC_{lang}, ")
    ]]]*/
    KC_LANG_EN, KC_LANG_DE, KC_LANG_FR, KC_LANG_ES, KC_LANG_PT, KC_LANG_IT, KC_LANG_TR, KC_LANG_KO, KC_LANG_JA, KC_LANG_AR, KC_LANG_GR,
    //[[[end]]]
};

struct display_info {
    uint8_t bitmask[NUM_SHIFT_REGISTERS];
};

#define BITMASK1(x) .bitmask = {~0, ~0, ~0, ~0, (uint8_t)(~(1<<x))}
#define BITMASK2(x) .bitmask = {~0, ~0, ~0, (uint8_t)(~(1<<x)), ~0}
#define BITMASK3(x) .bitmask = {~0, ~0, (uint8_t)(~(1<<x)), ~0, ~0}
#define BITMASK4(x) .bitmask = {~0, (uint8_t)(~(1<<x)), ~0, ~0, ~0}
#define BITMASK5(x) .bitmask = {(uint8_t)(~(1<<x)), ~0, ~0, ~0, ~0}

struct display_info key_display[] = {
        {BITMASK1(0)}, {BITMASK1(1)}, {BITMASK1(2)}, {BITMASK1(3)}, {BITMASK1(4)}, {BITMASK1(5)}, {BITMASK1(6)}, {BITMASK1(7)},
        {BITMASK2(0)}, {BITMASK2(1)}, {BITMASK2(2)}, {BITMASK2(3)}, {BITMASK2(4)}, {BITMASK2(5)}, {BITMASK2(6)}, {BITMASK2(7)},
        {BITMASK3(0)}, {BITMASK3(1)}, {BITMASK3(2)}, {BITMASK3(3)}, {BITMASK3(4)}, {BITMASK3(5)}, {BITMASK3(6)}, {BITMASK3(7)},
        {BITMASK4(0)}, {BITMASK4(1)}, {BITMASK4(2)}, {BITMASK4(3)}, {BITMASK4(4)}, {BITMASK4(5)}, {BITMASK4(6)}, {BITMASK4(7)},
        {BITMASK5(0)}, {BITMASK5(1)}, {BITMASK5(2)}, {BITMASK5(3)}, {BITMASK5(4)}, {BITMASK5(5)}, {BITMASK5(6)}, {BITMASK5(7)}
};

struct display_info disp_row_0 = { BITMASK1(0) };
struct display_info disp_row_3 = { BITMASK4(0) };


enum refresh_mode { START_FIRST_HALF, START_SECOND_HALF, DONE_ALL, ALL_AT_ONCE };
static enum refresh_mode g_refresh = DONE_ALL;

enum com_state { NOT_INITIALIZED, USB_HOST, BRIDGE };
static enum com_state com = NOT_INITIALIZED;

bool is_usb_host_side(void) {
    return com == USB_HOST;
}

enum side_state { UNDECIDED, LEFT_SIDE, RIGHT_SIDE };
static enum side_state side = UNDECIDED;

bool is_left_side(void) {
    return side == LEFT_SIDE;
}

bool is_right_side(void) {
    return side == RIGHT_SIDE;
}
typedef struct _poly_eeconf_t {
    uint8_t lang;
    uint8_t brightness;
    uint16_t unused;
} poly_eeconf_t;

typedef union _poly_eeconf{
    uint32_t raw;
    poly_eeconf_t conf;
} poly_eeconf;

enum flags { STATUS_DISP_ON = 1, RGB_MATRIX_ON = 2, DISP_IDLE = 4, DEAD_KEY_ON_WAKEUP = 8};
typedef struct _poly_sync_t {
    uint8_t lang;
    uint8_t contrast;
    uint8_t flags;
    layer_state_t default_ls;
} poly_sync_t;

/*
typedef struct _poly_error_chk{
    poly_sync_t a;
    uint16_t sum_a;
    poly_sync_t b;
    uint16_t sum_b;
} poly_error_chk;
*/

typedef struct _poly_state_t {
    led_t led_state;
    uint8_t mod_state;
    layer_state_t layer_state;
    poly_sync_t s;
} poly_state_t;

poly_state_t g_state;
poly_sync_t g_local;

static int32_t last_update = 0;

bool display_wakeup(keyrecord_t* record);
void update_displays(enum refresh_mode mode);
void set_displays(uint8_t contrast, bool idle);
void set_selected_displays(int8_t old_value, int8_t new_value);
void toggle_stagger(bool new_state);
//static int8_t old_contrast = 0;

uint16_t fletcher16( uint8_t *data, int count )
{
   uint16_t sum1 = 0;
   uint16_t sum2 = 0;
   int index;

   for ( index = 0; index < count; ++index )
   {
      sum1 = (sum1 + data[index]) % 255;
      sum2 = (sum2 + sum1) % 255;
   }

   return (sum2 << 8) | sum1;
}

void save_user_eeconf(void) {
    poly_eeconf ee;
    ee.conf.lang = g_local.lang;
    ee.conf.brightness = ~g_local.contrast;
    ee.conf.unused = 0;
    eeconfig_update_user(ee.raw);
}

poly_eeconf load_user_eeconf(void) {
    poly_eeconf ee;
    ee.raw = eeconfig_read_user();
    ee.conf.brightness = ~ee.conf.brightness;
    if(ee.conf.brightness>FULL_BRIGHT) {
        ee.conf.brightness = FULL_BRIGHT;
    }
    return ee;
}

void inc_brightness(void) {
    if (g_local.contrast < FULL_BRIGHT) {
        g_local.contrast += BRIGHT_STEP;
    }
    if (g_local.contrast > FULL_BRIGHT) {
        g_local.contrast = FULL_BRIGHT;
    }

    save_user_eeconf();
}

void dec_brightness(void) {
    if (g_local.contrast > (MIN_BRIGHT+BRIGHT_STEP)) {
        g_local.contrast -= BRIGHT_STEP;
    } else {
        g_local.contrast = MIN_BRIGHT;
    }

    save_user_eeconf();
}

void select_all_displays(void) {
    // make sure we are talking to all shift registers
    sr_shift_out_0_latch(NUM_SHIFT_REGISTERS);
}

void clear_all_displays(void) {
    select_all_displays();

    kdisp_set_buffer(0x00);
    kdisp_send_buffer();
}

void early_hardware_init_post(void) {
    spi_hw_setup();
}

void update_performed(void) {
    last_update = timer_read32();
}

layer_state_t persistent_default_layer_get(void) {
    return (layer_state_t)eeconfig_read_default_layer();
}

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

void request_disp_refresh(void) {
    g_refresh = ALL_AT_ONCE;
    //use the following for partial update (during housekeeping)
    // g_refresh = START_FIRST_HALF;
}

/*static bool wait_for_data = false;
void user_sync_poly_data_handler(uint8_t in_len, const void* in_data, uint8_t out_len, void* out_data) {
    if (in_len == sizeof(poly_error_chk) && in_data != NULL) {
        poly_error_chk* data = (poly_error_chk*)in_data;
        if(data->sum_a == fletcher16((uint8_t *)&data->a, sizeof(poly_sync_t))) {
            wait_for_data = true;
            memcpy(&g_local, &data->a, sizeof(poly_sync_t));
            wait_for_data = false;
        } else if(data->sum_b == fletcher16((uint8_t *)&data->b, sizeof(poly_sync_t))) {
            wait_for_data = true;
            memcpy(&g_local, &data->b, sizeof(poly_sync_t));
            wait_for_data = false;
        }
    }
}*/

void user_sync_poly_data_handler(uint8_t in_len, const void* in_data, uint8_t out_len, void* out_data) {
    if (in_len == sizeof(poly_sync_t) && in_data != NULL) {
        memcpy(&g_local, in_data, sizeof(poly_sync_t));
    }
}

void oled_on_off(bool on);

void sync_and_refresh_displays(void) {
    bool retry = false;
    if (is_usb_host_side()) {
        //master syncs data
        if ( memcmp(&g_local, &g_state.s, sizeof(poly_sync_t))!=0 ) {
            retry = true;
            /*
            poly_error_chk data;
            memcpy(&(data.a), (poly_sync_t*)&g_local, sizeof(poly_sync_t));
            memcpy(&(data.b), (poly_sync_t*)&g_local, sizeof(poly_sync_t));
            data.sum_a = data.sum_b = fletcher16((uint8_t *)&g_local, sizeof(poly_sync_t));
            */
            if (transaction_rpc_send(USER_SYNC_POLY_DATA, sizeof(poly_sync_t), &g_local)) {
                retry = false;
            }
        }
    }
    //while(wait_for_data) {}
    if(!retry) {
        const bool idle_changed = (g_local.flags&DISP_IDLE)!=(g_state.s.flags&DISP_IDLE);
        if(idle_changed) {
            if((g_local.flags&DISP_IDLE)==0) {
                oled_set_brightness(OLED_BRIGHTNESS);
            } else {
                oled_set_brightness(0);
            }
        }
        /*if((g_state.s.flags&STATUS_DISP_ON) != (g_local.flags&STATUS_DISP_ON)) {
            oled_on_off((g_local.flags&STATUS_DISP_ON)!=0);
        }*/

        const led_t led_state = host_keyboard_led_state();
        const uint8_t mod_state = get_mods();

        if (led_state.raw != g_state.led_state.raw ||
            mod_state != g_state.mod_state ||
            layer_state != g_state.layer_state ||
            g_state.s.lang != g_local.lang ||
            g_state.s.default_ls != g_local.default_ls) {

            g_state.led_state = led_state;
            g_state.mod_state = mod_state;
            g_state.layer_state = layer_state;

            request_disp_refresh();
        }

        //split the update cycle
        if (g_refresh == START_FIRST_HALF) {
            update_displays(START_FIRST_HALF);
            g_refresh = START_SECOND_HALF;
        }
        else if (g_refresh == START_SECOND_HALF || g_refresh == ALL_AT_ONCE) {
            update_displays(g_refresh);
            g_refresh = DONE_ALL;
        } else if (g_state.s.contrast != g_local.contrast || idle_changed) {
            set_displays(g_local.contrast, (g_local.flags&DISP_IDLE)!=0);
        }

        // if((g_local.flags&USE_STAGGER)!=(g_state.s.flags&USE_STAGGER)) {
        //     toggle_stagger((g_local.flags&USE_STAGGER)==0);
        // }
        g_state.s = g_local;
    }
}

void housekeeping_task_user(void) {
    sync_and_refresh_displays();

    //turn off displays
    uint32_t elapsed_time_since_update = timer_elapsed32(last_update);

    if (is_usb_host_side()) {
        g_local.flags |= STATUS_DISP_ON;

        if(elapsed_time_since_update > FADE_OUT_TIME && g_local.contrast >= MIN_BRIGHT && (g_local.flags & DISP_IDLE)==0) {
            poly_eeconf ee = load_user_eeconf();
            int32_t time_after = elapsed_time_since_update - FADE_OUT_TIME;
            int16_t brightness = ((FADE_TRANSITION_TIME - time_after) * ee.conf.brightness) / FADE_TRANSITION_TIME;

            //transition to pulsing mode
            if(brightness<=MIN_BRIGHT) {
                g_local.contrast = DISP_OFF;
                g_local.flags |= DISP_IDLE;
            } else if(brightness>FULL_BRIGHT) {
                g_local.contrast = FULL_BRIGHT;
            } else{
                g_local.contrast = brightness;
            }
        } else if(elapsed_time_since_update > TURN_OFF_TIME) {
            g_local.contrast = DISP_OFF;
            g_local.flags &= ~((uint8_t)STATUS_DISP_ON);
            g_local.flags &= ~((uint8_t)DISP_IDLE);
        } else if((g_local.flags & DISP_IDLE)!=0) {
            int32_t time_after = PK_MAX(elapsed_time_since_update - FADE_OUT_TIME - FADE_TRANSITION_TIME, 0)/300;
            g_local.contrast = time_after%50;
        } else {
            g_local.flags &= ~((uint8_t)DISP_IDLE);
        }
    }
}
enum unicode_names {
    UM_A,
    UM_AC,
    UM_O,
    UM_OC,
    UM_U,
    UM_UC,
    SZ,
    SZC
};

const uint32_t unicode_map[] PROGMEM = {
    [UM_A]  = UMLAUT_A_SMALL[0],
    [UM_AC] = UMLAUT_A[0],
    [UM_O]  = UMLAUT_O_SMALL[0],
    [UM_OC] = UMLAUT_O[0],
    [UM_U]  = UMLAUT_U_SMALL[0],
    [UM_UC] = UMLAUT_U[0],
    [SZ]  = ESZETT[0],
    [SZC] = 0x1E9E
};

uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    //Base Layers
/*
                                                              ┌────────────────┐
                                                              │     QWERTY     │
                                                              └────────────────┘
   ┌────────┬───────┬───────┬───────┬───────┬───────┬───────┐                    ┌───────┬───────┬───────┬───────┬───────┬───────┬────────┐
   │  Esc   │   1   │   2   │   3   │   4   │   5   │  Nubs │ ╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮ │   6   │   7   │   8   │   9   │   0   │   -   │ BckSp  │
   ├────────┼───────┼───────┼───────┼───────┼───────┼───────┤ │╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯│ ├───────┼───────┼───────┼───────┼───────┼───────┼────────┤
   │  TAB   │   q   │   w   │   e   │   r   │   t   │   `   ├─╯                ╰─┤  Hypr │   y   │   u   │   i   │   o   │   p   │   \    │
   ├────────┼───────┼───────┼───────┼───────┼───────┼───────┤                    ├───────┼───────┼───────┼───────┼───────┼───────┼────────┤
   │  FN    │   a   │   s   │   d   │   f   │   g   │   '   │  (MB1)             │  Intl │   h   │   j   │   k   │   l   │   =   │  Ret   │
   ├────────┼───────┼───────┼───────┼───────┼───────┼───────┼────────╮  ╭────────┼───────┼───────┼───────┼───────┼───────┼───────┼────────┤
   │ Shift  │   z   │   x   │   c   │   v   │   b   │  Nuhs │  Num!  │  │   [    │   ]   │   n   │   m   │   ,   │   ;   │  Up   │ Shift  │
   └┬───────┼───────┼───────┼───────┼──────┬┴───────┼───────┼────────┤  ├────────┼───────┼───────┴┬──────┼───────┼───────┼───────┼───────┬┘
    │ Ctrl  │  Os   │  Alt  │  Intl │      │  Space │  Del  │   Ret  │  │  Lang  │   /   │ Space  │      │   .   │  Left │  Down │ Right │
    └───────┴───────┴───────┴───────┘      └────────┴───────┴────────╯  └────────┴───────┴────────┘      └───────┴───────┴───────┴───────┘
*/
    [_L0] = LAYOUT_left_right_stacked(
        KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_NUBS,
        KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_GRAVE,
        MO(_FL0),   KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_QUOTE,   KC_MS_BTN1,
        KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_NUHS,    MO(_NL),
        KC_LCTL,    KC_LWIN,    KC_LALT,    KC_APP,                 KC_SPACE,   KC_DEL,     KC_ENTER,

                    KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINUS,   KC_BSPC,
                    KC_HYPR,    KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_BSLS,
        KC_NO,      MO(_ADDLANG1),KC_H,     KC_J,       KC_K,       KC_L,       KC_EQUAL,   KC_ENTER,
        KC_LBRC,    KC_RBRC,    KC_N,       KC_M,       KC_COMMA,   KC_SCLN,    KC_UP,      KC_RSFT,
        KC_LANG,    KC_SLASH,    KC_SPC,                KC_DOT,     KC_LEFT,    KC_DOWN,    KC_RIGHT
        ),

/*
                                                              ┌────────────────┐
                                                              │     QWERTY!    │
                                                              └────────────────┘
   ┌────────┬───────┬───────┬───────┬───────┬───────┬───────┐                    ┌───────┬───────┬───────┬───────┬───────┬───────┬────────┐
   │  Esc   │   1   │   2   │   3   │   4   │   5   │   6   │ ╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮ │   7   │   8   │   9   │   0   │   -   │   =   │  Hypr  │
   ├────────┼───────┼───────┼───────┼───────┼───────┼───────┤ │╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯│ ├───────┼───────┼───────┼───────┼───────┼───────┼────────┤
   │  TAB   │   q   │   w   │   e   │   r   │   t   │   `   ├─╯                ╰─┤   y   │   u   │   i   │   o   │   p   │   [   │  Nubs  │
   ├────────┼───────┼───────┼───────┼───────┼───────┼───────┤                    ├───────┼───────┼───────┼───────┼───────┼───────┼────────┤
   │  FN    │   a   │   s   │   d   │   f   │   g   │   '   │  (MB1)             │   h   │   j   │   k   │   l   │   ;   │   ]   │    \   │
   ├────────┼───────┼───────┼───────┼───────┼───────┼───────┼────────╮  ╭────────┼───────┼───────┼───────┼───────┼───────┼───────┼────────┤
   │ Shift  │ Nuhs  │   z   │   x   │   c   │   v   │   b   │  Num!  │  │  Lang  │  Ctx  │   n   │   m   │   ,   │   .   │   /   │ Shift  │
   └┬───────┼───────┼───────┼───────┼──────┬┴───────┼───────┼────────┤  ├────────┼───────┼───────┴┬──────┼───────┼───────┼───────┼───────┬┘
    │ Ctrl  │  Os   │  Alt  │  Intl │      │  Space │  Del  │   Ret  │  │  Ret   │ BckSp │ Space  │      │ Left  │   Up  │  Down │ Right │
    └───────┴───────┴───────┴───────┘      └────────┴───────┴────────╯  └────────┴───────┴────────┘      └───────┴───────┴───────┴───────┘
*/

    [_L1] = LAYOUT_left_right_stacked(
        KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,
        KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_GRAVE,
        MO(_FL1),   KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_QUOTE,   KC_MS_BTN1,
        KC_LSFT,    KC_NUHS,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       MO(_NL),
        KC_LCTL,    KC_LWIN,    KC_LALT,    MO(_ADDLANG1),          KC_SPACE,   KC_DEL,     KC_ENTER,

                    KC_7,       KC_8,       KC_9,       KC_0,       KC_MINUS,   KC_EQUAL,   KC_HYPR,
                    KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,    KC_NUBS,
        KC_NO,      KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_RBRC,    KC_BSLS,
        KC_LANG,    KC_APP,     KC_N,       KC_M,       KC_COMMA,   KC_DOT,     KC_SLASH,   KC_RSFT,
        KC_ENTER,   KC_BSPC,    KC_SPC,                 KC_LEFT,    KC_UP,      KC_DOWN,    KC_RIGHT
        ),
/*
                                                              ┌────────────────┐
                                                              │   Colemak DH   │
                                                              └────────────────┘
   ┌────────┬───────┬───────┬───────┬───────┬───────┬───────┐                    ┌───────┬───────┬───────┬───────┬───────┬───────┬────────┐
   │  Esc   │   1   │   2   │   3   │   4   │   5   │  Nub  │ ╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮ │   6   │   7   │   8   │   9   │   0   │   -   │   =    │
   ├────────┼───────┼───────┼───────┼───────┼───────┼───────┤ │╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯│ ├───────┼───────┼───────┼───────┼───────┼───────┼────────┤
   │  TAB   │   q   │   w   │   f   │   p   │   b   │   `   ├─╯                ╰─┤   j   │   l   │   u   │   y   │   ;   │   [   │  Intl  │
   ├────────┼───────┼───────┼───────┼───────┼───────┼───────┤                    ├───────┼───────┼───────┼───────┼───────┼───────┼────────┤
   │  FN    │   a   │   r   │   s   │   t   │   g   │   '   │  (MB1)             │   m   │   n   │   e   │   i   │   o   │   ]   │    \   │
   ├────────┼───────┼───────┼───────┼───────┼───────┼───────┼────────╮  ╭────────┼───────┼───────┼───────┼───────┼───────┼───────┼────────┤
   │ Shift  │   z   │   x   │   c   │   d   │   v   │  Nuhs |  Num!  │  │  Lang  │  Hypr │   k   │   h   │   ,   │   .   │   /   │ Shift  │
   └┬───────┼───────┼───────┼───────┼──────┬┴───────┼───────┼────────┤  ├────────┼───────┼───────┴┬──────┼───────┼───────┼───────┼───────┬┘
    │ Ctrl  │  Os   │  Alt  │  Ctx  │      │  Space │  Del  │   Ret  │  │  Ret   │ BckSp │ Space  │      │ Left  │   Up  │  Down │ Right │
    └───────┴───────┴───────┴───────┘      └────────┴───────┴────────╯  └────────┴───────┴────────┘      └───────┴───────┴───────┴───────┘
*/
    [_L2] = LAYOUT_left_right_stacked(
        KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_NUBS,
        KC_TAB,     KC_Q,       KC_W,       KC_F,       KC_P,       KC_B,       KC_GRAVE,
        MO(_FL1),   KC_A,       KC_R,       KC_S,       KC_T,       KC_G,       KC_QUOTE,   KC_MS_BTN1,
        KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_D,       KC_V,       KC_NUHS,    MO(_NL),
        KC_LCTL,    KC_LWIN,    KC_LALT,    KC_APP,                 KC_SPACE,   KC_DEL,     KC_ENTER,

                    KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINUS,   KC_EQUAL,
                    KC_J,       KC_L,       KC_U,       KC_Y,       KC_SCLN,    KC_LBRC,    MO(_ADDLANG1),
        KC_NO,      KC_M,       KC_N,       KC_E,       KC_I,       KC_O,       KC_RBRC,    KC_BSLS,
        KC_LANG,    KC_HYPR,    KC_K,       KC_H,       KC_COMMA,   KC_DOT,     KC_SLASH,   KC_RSFT,
        KC_ENTER,   KC_BSPC,    KC_SPC,                 KC_LEFT,    KC_UP,      KC_DOWN,    KC_RIGHT
        ),
        /*
                                                              ┌────────────────┐
                                                              │       Neo      │
                                                              └────────────────┘
   ┌────────┬───────┬───────┬───────┬───────┬───────┬───────┐                    ┌───────┬───────┬───────┬───────┬───────┬───────┬────────┐
   │  Esc   │   1   │   2   │   3   │   4   │   5   │   <   │ ╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮ │   6   │   7   │   8   │   9   │   0   │   -   │   `    │
   ├────────┼───────┼───────┼───────┼───────┼───────┼───────┤ │╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯│ ├───────┼───────┼───────┼───────┼───────┼───────┼────────┤
   │  TAB   │   x   │   v   │   l   │   c   │   w   │   ^   ├─╯                ╰─┤   k   │   h   │   g   │   f   │   q   │   ß   │   ´    │
   ├────────┼───────┼───────┼───────┼───────┼───────┼───────┤                    ├───────┼───────┼───────┼───────┼───────┼───────┼────────┤
   │  FN    │   u   │   i   │   a   │   e   │   o   │   '   │  (MB1)             │   s   │   n   │   r   │   t   │   d   │   y   │   \    │
   ├────────┼───────┼───────┼───────┼───────┼───────┼───────┼────────╮  ╭────────┼───────┼───────┼───────┼───────┼───────┼───────┼────────┤
   │ Shift  │   #   │   ü   │   ö   │   ä   │   p   │   z   │  Num!  │  │  Lang  │   +   │   b   │   m   │   ,   │   .   │   j   │ Shift  │
   └┬───────┼───────┼───────┼───────┼──────┬┴───────┼───────┼────────┤  ├────────┼───────┼───────┴┬──────┼───────┼───────┼───────┼───────┬┘
    │ Ctrl  │  Os   │  Alt  │  Ctx  │      │  Space │  Del  │   Ret  │  │  Ret   │ BckSp │ Space  │      │ Left  │   Up  │  Down │ Right │
    └───────┴───────┴───────┴───────┘      └────────┴───────┴────────╯  └────────┴───────┴────────┘      └───────┴───────┴───────┴───────┘
*/
    [_L3] = LAYOUT_left_right_stacked(
        KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       DE_LABK,
        KC_TAB,     KC_X,       KC_V,       KC_L,       KC_C,       KC_W,       DE_CIRC,
        MO(_FL0),   KC_U,       KC_I,       KC_A,       KC_E,       KC_O,       KC_QUOTE,   KC_MS_BTN1,
        KC_LSFT,    DE_HASH,    DE_UDIA,    DE_ODIA,    DE_ADIA,    KC_P,       DE_Z,       MO(_NL),
        KC_LCTL,    KC_LWIN,    KC_LALT,    KC_APP,                 KC_SPACE,   KC_DEL,     KC_ENTER,

                    KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       DE_MINS,    DE_GRV,
                    KC_K,       KC_H,       KC_G,       KC_F,       KC_Q,       DE_SS,      DE_ACUT,
        KC_NO,      KC_S,       KC_N,       KC_R,       KC_T,       KC_D,       DE_Y,       KC_BSLS,
        KC_LANG,    DE_PLUS,    KC_B,       KC_M,       KC_COMMA,   KC_DOT,     KC_J,       KC_RSFT,
        KC_ENTER,   KC_BSPC,    KC_SPC,                 KC_LEFT,    KC_UP,      KC_DOWN,    KC_RIGHT
        ),
        /*
                                                              ┌────────────────┐
                                                              │    Workman     │
                                                              └────────────────┘
   ┌────────┬───────┬───────┬───────┬───────┬───────┬───────┐                    ┌───────┬───────┬───────┬───────┬───────┬───────┬────────┐
   │  Esc   │   1   │   2   │   3   │   4   │   5   │   `   │ ╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮╭╮ │   6   │   7   │   8   │   9   │   0   │   -   │   =    │
   ├────────┼───────┼───────┼───────┼───────┼───────┼───────┤ │╰╯╰╯╰╯╰╯╰╯╰╯╰╯╰╯│ ├───────┼───────┼───────┼───────┼───────┼───────┼────────┤
   │  TAB   │   q   │   d   │   r   │   w   │   b   │  Hypr ├─╯                ╰─┤   j   │   f   │   u   │   p   │   ;   │   [   │   ]    │
   ├────────┼───────┼───────┼───────┼───────┼───────┼───────┤                    ├───────┼───────┼───────┼───────┼───────┼───────┼────────┤
   │  FN    │   a   │   s   │   h   │   t   │   g   │  Meh  │  (MB1)             │   y   │   n   │   e   │   o   │   i   │   '   │   \    │
   ├────────┼───────┼───────┼───────┼───────┼───────┼───────┼────────╮  ╭────────┼───────┼───────┼───────┼───────┼───────┼───────┼────────┤
   │ Shift  │   z   │   x   │   m   │   c   │   v   │  Intl │  Num!  │  │  Lang  │   k   │   b   │   l   │   ,   │   .   │   /   │ Shift  │
   └┬───────┼───────┼───────┼───────┼──────┬┴───────┼───────┼────────┤  ├────────┼───────┼───────┴┬──────┼───────┼───────┼───────┼───────┬┘
    │ Ctrl  │  Os   │  Alt  │  Ctx  │      │  Space │  Del  │   Ret  │  │  Ret   │ BckSp │ Space  │      │ Left  │   Up  │  Down │ Right │
    └───────┴───────┴───────┴───────┘      └────────┴───────┴────────╯  └────────┴───────┴────────┘      └───────┴───────┴───────┴───────┘
*/
    [_L4] = LAYOUT_left_right_stacked(
        KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_GRAVE,
        KC_TAB,     KC_Q,       KC_D,       KC_R,       KC_W,       KC_B,       KC_HYPR,
        MO(_FL1),   KC_A,       KC_S,       KC_H,       KC_T,       KC_G,       KC_MEH,     KC_MS_BTN1,
        KC_LSFT,    KC_Z,       KC_X,       KC_M,       KC_C,       KC_V,       MO(_ADDLANG1), MO(_NL),
        KC_LCTL,    KC_LWIN,    KC_LALT,    KC_APP,                 KC_SPACE,   KC_DEL,     KC_ENTER,

                    KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINUS,   KC_EQUAL,
                    KC_J,       KC_F,       KC_U,       KC_P,       KC_SCLN,    KC_LBRC,    KC_RBRC,
        KC_NO,      KC_Y,       KC_N,       KC_E,       KC_O,       KC_I,       KC_QUOTE,   KC_BSLS,
        KC_LANG,    KC_K,       KC_B,       KC_L,       KC_COMMA,   KC_DOT,     KC_SLASH,   KC_RSFT,
        KC_ENTER,   KC_BSPC,    KC_SPC,                 KC_LEFT,    KC_UP,      KC_DOWN,    KC_RIGHT
        ),
    //Function Layer (Fn)
    [_FL0] = LAYOUT_left_right_stacked(
        OSL(_UL),   KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,     TO(_UL),
        _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
        KC_CAPS,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    KC_BTN2,                _______,    _______,    _______,

                    KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,      KC_F11,    KC_F12,
                    KC_BTN3,    KC_BTN2,    _______,    _______,    _______,    _______,    TO(_SL),
        _______,    KC_BTN1,    _______,    _______,    _______,    _______,    _______,    _______,
        TO(_NL),    _______,    _______,    _______,    _______,    _______,    _______,    _______,
        KC_RALT,    KC_RWIN,    KC_RCTL,                KC_HOME,    KC_PGUP,    KC_PGDN,    KC_END
        ),
    [_FL1] = LAYOUT_left_right_stacked(
        OSL(_UL),   KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,             _______,    _______,    _______,

                    KC_F7,      KC_F8,      KC_F9,      KC_F10,      KC_F11,     KC_F12,    TO(_UL),
                    KC_BTN3,    KC_BTN2,    _______,    _______,    _______,    _______,    TO(_SL),
        _______,    KC_BTN1,    _______,    _______,    _______,    _______,    _______,    KC_CAPS,
        TO(_NL),    _______,    _______,    _______,    _______,    _______,    _______,    _______,
        KC_RALT,    KC_RWIN,    KC_RCTL,                KC_HOME,    KC_PGUP,    KC_PGDN,    KC_END
        ),
     //Num Layer
    [_NL] = LAYOUT_left_right_stacked(
        KC_NO,      KC_NUM,     KC_PSLS,    KC_PAST,    KC_PMNS,    KC_NO,      KC_NO,
        KC_BTN1,    KC_KP_7,    KC_KP_8,    KC_KP_9,    KC_PPLS,    KC_INS,     KC_NO,
        KC_NO,      KC_KP_4,    KC_KP_5,    KC_KP_6,    KC_PPLS,    KC_DEL,     KC_NO,     _______,
        KC_NO,      KC_KP_1,    KC_KP_2,    KC_KP_3,    KC_PENT,    KC_NO,      KC_NO,     _______,
        KC_BASE,    KC_KP_0,    KC_PDOT,    KC_PENT,                KC_MS_BTN2, KC_NO,     KC_NO,

                    KC_NO,      KC_NO,      KC_NUM,     KC_PSLS,    KC_PAST,    KC_PMNS,   KC_NO,
                    KC_NO,      KC_INS,     KC_KP_7,    KC_KP_8,    KC_KP_9,    KC_PPLS,   KC_NO,
        _______,    KC_NO,      KC_DEL,     KC_KP_4,    KC_KP_5,    KC_KP_6,    KC_PPLS,   KC_NO,
        _______,    _______,    KC_NO,      KC_KP_1,    KC_KP_2,    KC_KP_3,    KC_PENT,   KC_NO,
        _______,    KC_NO,      KC_NO,                  KC_KP_0,    KC_PDOT,    KC_PENT,   KC_BASE
        ),
    //Util Layer
    [_UL] = LAYOUT_left_right_stacked(
        KC_NO,      KC_F13,     KC_F14,     KC_F15,     KC_F16,     KC_F17,     KC_F18,
        KC_MYCM,    KC_CALC,    KC_PSCR,    KC_SCRL,    KC_BRK,     KC_NO,      KC_NO,
        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      _______,
        KC_LSFT,    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
        KC_BASE,    KC_NO,      KC_NO,      KC_NO,                  KC_NO,      KC_NO,      KC_NO,

                    KC_F19,     KC_F20,     KC_F21,     KC_F22,     KC_F23,     KC_F24,     KC_NO,
                    KC_NO,      KC_MPRV,    KC_MPLY,    KC_MSTP,    KC_MNXT,    KC_NO,      TO(_SL),
        _______,    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
        KC_NO,      KC_NO,      KC_MUTE,    KC_VOLD,    KC_VOLU,    KC_NO,      KC_NO,      KC_RSFT,
        KC_NO,      KC_NO,      KC_NO,                  KC_NO,      KC_NO,      KC_NO,      KC_BASE
        ),
    //Settings Layer
    [_SL] = LAYOUT_left_right_stacked(
        KC_DDIM,    KC_DMIN,    KC_D1Q,     KC_DHLF,    KC_D3Q,     KC_DMAX,    KC_DBRI,
        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
        KC_NO,      KC_L0,      KC_L1,      KC_L2,      KC_L3,      KC_L4,      KC_NO,      _______,
        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      QK_RBT,
        KC_BASE,    KC_NO,      KC_NO,      KC_NO,                  KC_NO,      QK_MAKE,    QK_BOOT,


                    RGB_RMOD,   RGB_M_SW,   RGB_M_R,    RGB_TOG,    RGB_M_P,    RGB_M_B,    RGB_MOD,
                    KC_NO,      RGB_SPD,    RGB_SPI,    KC_NO,      RGB_HUD,    RGB_HUI,    KC_NO,
        _______,    KC_NO,      RGB_VAD,    RGB_VAI,    KC_NO,      RGB_SAD,    RGB_SAI,    KC_NO,
        EE_CLR,     KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
        DB_TOGG,    KC_DEADKEY, KC_NO,                  KC_NO,      KC_NO,      KC_NO,      KC_BASE
        ),
    //Language Selection Layer
    [_LL] = LAYOUT_left_right_stacked(
                        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,
                        KC_NO,      KC_LANG_PT, KC_LANG_ES, KC_LANG_AR, KC_LANG_GR, KC_NO,      KC_NO,
        QK_UNICODE_MODE_WINCOMPOSE, KC_LANG_FR, KC_LANG_DE, KC_LANG_JA, KC_LANG_TR, KC_NO,      KC_NO,      KC_MS_BTN1,
        QK_UNICODE_MODE_EMACS,      KC_LANG_IT, KC_LANG_EN, KC_LANG_KO, KC_NO,      KC_NO,      KC_NO,      KC_NO,
        KC_BASE,                    KC_NO,      KC_NO,      KC_NO,                  KC_NO,      KC_NO,      KC_NO,

                    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,      QK_UNICODE_MODE_MACOS,
                    KC_NO,      KC_LANG_GR, KC_LANG_AR, KC_LANG_ES, KC_LANG_PT, KC_NO,      QK_UNICODE_MODE_LINUX,
        _______,    KC_NO,      KC_LANG_TR, KC_LANG_JA, KC_LANG_DE, KC_LANG_FR, KC_NO,      QK_UNICODE_MODE_WINDOWS,
        KC_NO,      KC_NO,      KC_NO,      KC_LANG_KO, KC_LANG_EN, KC_LANG_IT, KC_NO,      QK_UNICODE_MODE_BSD,
        KC_NO,      KC_NO,      KC_NO,                  KC_NO,      KC_NO,      KC_NO,      KC_BASE
        ),
    [_ADDLANG1] = LAYOUT_left_right_stacked(
        _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    XP(UM_A,UM_AC),   XP(SZ,SZC),    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,                _______,    _______,    _______,

                    _______,    _______,    _______,    _______,    _______,    _______,     _______,
                    _______,    XP(UM_U,UM_UC),    _______,    XP(UM_O,UM_OC),    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,                _______,    _______,    _______,    _______
        )
};


#define LX(x,y) ((x)/2),y
led_config_t g_led_config = { {// Key Matrix to LED Index
                              {6, 5, 4, 3, 2, 1, 0, NO_LED},
                              {13, 12, 11, 10, 9, 8, 7, NO_LED},
                              {20, 19, 18, 17, 16, 15, 14, NO_LED},
                              {27, 26, 25, 24, 23, 22, 21, NO_LED},
                              {35, 34, 33, 32, 31, 30, 29, 28},

                              {NO_LED, 42, 41, 40, 39, 38, 37, 36},
                              {NO_LED, 49, 48, 47, 46, 45, 44, 43},
                              {NO_LED, 56, 55, 54, 53, 52, 51, 50},
                              {NO_LED, 63, 62, 61, 60, 59, 58, 57},
                              {71, 70, 69, 68, 67, 66, 65, 64}
                             },
                             {
                                // LED Index to Physical Position
                                                {LX(144, 9)},   {LX(129, 9)},   {LX(104, 5)},   {LX(79, 1)},    {LX(55, 5)},    {LX(30, 9)},    {LX(0, 9)},
                                                {LX(144, 33)},  {LX(129, 33)},  {LX(104, 19)},  {LX(79, 25)},   {LX(55, 29)},   {LX(30, 33)},   {LX(0, 33)},
                                                {LX(144, 58)},  {LX(129, 58)},  {LX(104, 54)},  {LX(79, 50)},   {LX(55, 54)},   {LX(30, 58)},   {LX(0, 58)},
                                                {LX(144, 83)},  {LX(129, 83)},  {LX(104, 79)},  {LX(79, 75)},   {LX(55, 79)},   {LX(30, 83)},   {LX(0, 83)},
                {LX(170, 99)},  {LX(170, 127)}, {LX(144, 118)}, {LX(129, 113)},                 {LX(79, 99)},   {LX(55, 103)},  {LX(30, 107)},  {LX(6, 107)},

                                                {LX(446, 9)},   {LX(415, 9)},   {LX(390, 5)},   {LX(365, 1)},   {LX(341, 5)},   {LX(316, 9)},   {LX(286, 9)},
                                                {LX(446, 33)},  {LX(415, 33)},  {LX(390, 19)},  {LX(365, 25)},  {LX(341, 29)},  {LX(316, 33)},  {LX(286, 33)},
                                                {LX(446, 58)},  {LX(415, 58)},  {LX(390, 54)},  {LX(365, 50)},  {LX(341, 54)},  {LX(316, 58)},  {LX(286, 58)},
                                                {LX(446, 83)},  {LX(415, 83)},  {LX(390, 79)},  {LX(365, 75)},  {LX(341, 79)},  {LX(316, 83)},  {LX(286, 83)},
                                                {LX(440, 107)}, {LX(415, 107)}, {LX(390, 103)}, {LX(365, 99)},                  {LX(324, 113)}, {LX(290, 118)}, {LX(264, 127)},  {LX(264, 99)}
                             },
                             {
                                 // LED Index to Flag
                                 4, 4, 4, 4, 4, 4, 4,
                                 4, 4, 4, 4, 4, 4, 4,
                                 4, 4, 4, 4, 4, 4, 4,
                                 4, 4, 4, 4, 4, 4, 4,
                                 4, 4, 4, 4, 4, 4, 4, 4,

                                 4, 4, 4, 4, 4, 4, 4,
                                 4, 4, 4, 4, 4, 4, 4,
                                 4, 4, 4, 4, 4, 4, 4,
                                 4, 4, 4, 4, 4, 4, 4,
                                 4, 4, 4, 4, 4, 4, 4, 4
                             } };

const uint16_t* keycode_to_disp_text(uint16_t keycode, led_t state) {
    switch (keycode) {
    case KC_DEADKEY: return (g_local.flags&DEAD_KEY_ON_WAKEUP)==0 ? u"WakeX\r\v" ICON_SWITCH_OFF : u"WakeX\r\v" ICON_SWITCH_ON;
    case QK_UNICODE_MODE_MACOS: return u"Mac";
    case QK_UNICODE_MODE_LINUX: return u"Lnx";
    case QK_UNICODE_MODE_WINDOWS: return u"Win";
    case QK_UNICODE_MODE_BSD: return u"BSD";
    case QK_UNICODE_MODE_WINCOMPOSE: return u"WinC";
    case QK_UNICODE_MODE_EMACS: return u"Emcs";
    case QK_LEAD:
        return u"Lead";
    case KC_HYPR:
        return u" " PRIVATE_HYPER;
    case KC_MEH:
        return u" " PRIVATE_MEH;
    case KC_EXEC:
        return u"Exec";
    case KC_NUM_LOCK:
        return !state.num_lock ? u"Nm" ICON_NUMLOCK_OFF : u"Nm" ICON_NUMLOCK_ON;
    case KC_KP_SLASH:
        return u"/";
    case KC_KP_ASTERISK:
    case KC_KP_MINUS:
        return u"-";
    case KC_KP_7:
        return !state.num_lock ? ARROWS_LEFTSTOP : u"7";
    case KC_KP_8:
        return !state.num_lock ? u"   " ICON_UP : u"8";
    case KC_KP_9:
        return !state.num_lock ? ARROWS_UPSTOP : u"9";
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
        return !state.num_lock ? ARROWS_RIGHTSTOP : u"1";
    case KC_KP_2:
        return !state.num_lock ? u"   " ICON_DOWN : u"2";
    case KC_KP_3:
        return !state.num_lock ? ARROWS_DOWNSTOP : u"3";
    case KC_CALCULATOR:
        return u"   " PRIVATE_CALC;
    case KC_KP_0:
        return !state.num_lock ? u"Ins" : u"0";
    case KC_KP_DOT:
        return !state.num_lock ? u"Del" : u".";
    case KC_KP_ENTER:
        return u"Enter";
    case QK_BOOTLOADER:
        return u"Boot";
    case QK_DEBUG_TOGGLE:
        return debug_enable==0? u"Dbg\r\v" ICON_SWITCH_OFF : u"Dbg\r\v" ICON_SWITCH_ON;
    case RGB_RMOD:
        return u" " ICON_LEFT PRIVATE_LIGHT;
    case RGB_TOG:
        return u"  I/O";
    case RGB_MOD:
        return PRIVATE_LIGHT ICON_RIGHT;
    case RGB_HUI:
        return u"Hue+";
    case RGB_HUD:
        return u"Hue-";
    case RGB_SAI:
        return u"Sat+";
    case RGB_SAD:
        return u"Sat-";
    case RGB_VAI:
        return u"Bri+";
    case RGB_VAD:
        return u"Bri-";
    case RGB_SPI:
        return u"Spd+";
    case RGB_SPD:
        return u"Spd-";
    case RGB_MODE_PLAIN:
        return u"Plan";
    case RGB_MODE_BREATHE:
        return u"Brth";
    case RGB_MODE_SWIRL:
        return u"Swrl";
    case RGB_MODE_RAINBOW:
        return u"Rnbw";
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
    case KC_BTN1:
        return u"  " ICON_LMB;
    case KC_BTN2:
        return u"  " ICON_RMB;
    case KC_BTN3:
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
        return u"  " PRIVATE_MUTE;
    case KC_AUDIO_VOL_DOWN:
        return u"  " PRIVATE_VOL_DOWN;
    case KC_AUDIO_VOL_UP:
        return u"  " PRIVATE_VOL_UP;
    case KC_PRINT_SCREEN:
        return u"  " PRIVATE_IMAGE;
    case KC_SCROLL_LOCK:
        return u"ScLk";
    case KC_PAUSE:
        return u"Paus";
    case KC_INSERT:
        return u"Ins";
    case KC_HOME:
        return ARROWS_LEFTSTOP;
    case KC_END:
        return u"   " ARROWS_RIGHTSTOP;
    case KC_PAGE_UP:
        return u"  " ARROWS_UPSTOP;
    case KC_PAGE_DOWN:
        return u"  " ARROWS_DOWNSTOP;
    case KC_DELETE:
        return TECHNICAL_ERASERIGHT;
    case KC_MYCM:
        return u"  " PRIVATE_PC;
    case TO(_SL):
        return PRIVATE_SETTINGS u"\v" ICON_LAYER;
    case MO(_FL0):
    case MO(_FL1):
        return u"Fn\r\v\t" ICON_LAYER;
    case TO(_NL):
        return u"Nm\r\v\t" ICON_LAYER;
    case MO(_NL):
        return u"Nm!\r\v\t" ICON_LAYER;
    case KC_BASE:
        return u"Base\r\v\t" ICON_LAYER;
    case KC_L0:
        return g_local.default_ls==_L0 ? u"Qwty\r\v" ICON_SWITCH_ON : u"Qwty\r\v" ICON_SWITCH_OFF;
    case KC_L1:
        return g_local.default_ls==_L1 ? u"Qwty!\r\v" ICON_SWITCH_ON : u"Qwty!\r\v" ICON_SWITCH_OFF;
    case KC_L2:
        return g_local.default_ls==_L2 ? u"Clmk\r\v" ICON_SWITCH_ON : u"Clmk\r\v" ICON_SWITCH_OFF;
    case KC_L3:
        return g_local.default_ls==_L3 ? u"Neo\r\v" ICON_SWITCH_ON : u"Neo\r\v" ICON_SWITCH_OFF;
    case KC_L4:
        return g_local.default_ls==_L4 ? u"Wkm\r\v" ICON_SWITCH_ON : u"Wkm\r\v" ICON_SWITCH_OFF;
    case OSL(_UL):
        return u"Util*\r\v\t" ICON_LAYER;
    case TO(_UL):
        return u"Util\r\v\t" ICON_LAYER;
    case MO(_ADDLANG1):
        return u"Intl";
    case KC_F1: return u" F1";
    case KC_F2: return u" F2";
    case KC_F3: return u" F3";
    case KC_F4: return u" F4";
    case KC_F5: return u" F5";
    case KC_F6: return u" F6";
    case KC_F7: return u" F7";
    case KC_F8: return u" F8";
    case KC_F9: return u" F9";
    case KC_F10:return u" F10";
    case KC_F11:return u" F11";
    case KC_F12:return u" F12";
    case KC_F13:return u" F13";
    case KC_F14:return u" F14";
    case KC_F15:return u" F15";
    case KC_F16:return u" F16";
    case KC_F17:return u" F17";
    case KC_F18:return u" F18";
    case KC_F19:return u" F19";
    case KC_F20:return u" F20";
    case KC_F21:return u" F21";
    case KC_F22:return u" F22";
    case KC_F23:return u" F23";
    case KC_F24:return u" F24";
    case KC_LEFT_CTRL:
    case KC_RIGHT_CTRL:
        return TECHNICAL_COMMAND;
    case KC_LEFT_ALT:
    case KC_RIGHT_ALT:
        return TECHNICAL_OPTION;
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
    case KC_CAPS_LOCK:
        return state.caps_lock ? u"Cap" ICON_CAPSLOCK_ON : u"Cap" ICON_CAPSLOCK_OFF;
    case KC_LSFT:
    case KC_RSFT:
        return u" " ICON_SHIFT;
    case KC_NO:
        return u"";
    case KC_DDIM:
        return u"  " ICON_LEFT;
    case KC_DBRI:
        return u"  " ICON_RIGHT;
    case KC_D1Q:
        return u"  " PRIVATE_DISP_DARKER;
    case KC_D3Q:
        return u"  " PRIVATE_DISP_BRIGHTER;
    case KC_DHLF:
        return u"  " PRIVATE_DISP_HALF;
    case KC_DMIN:
        return u"  " PRIVATE_DISP_DARK;
    case KC_DMAX:
        return u"  " PRIVATE_DISP_BRIGHT;
    case KC_LANG:
        return PRIVATE_WORLD;
    case SH_TOGG:
        return u"SwpH";
    case QK_MAKE:
        return u"Make";
    case EE_CLR:
        return u"ClrEE";
    case QK_REBOOT:
        return u"Boot";
        /*[[[cog
            for lang in languages:
                short = lang.split("_")[1]
                cog.outl(f'case KC_{lang}: return g_local.lang == {lang} ? u"[{short}]" : u" {short}";')
        ]]]*/
        case KC_LANG_EN: return g_local.lang == LANG_EN ? u"[EN]" : u" EN";
        case KC_LANG_DE: return g_local.lang == LANG_DE ? u"[DE]" : u" DE";
        case KC_LANG_FR: return g_local.lang == LANG_FR ? u"[FR]" : u" FR";
        case KC_LANG_ES: return g_local.lang == LANG_ES ? u"[ES]" : u" ES";
        case KC_LANG_PT: return g_local.lang == LANG_PT ? u"[PT]" : u" PT";
        case KC_LANG_IT: return g_local.lang == LANG_IT ? u"[IT]" : u" IT";
        case KC_LANG_TR: return g_local.lang == LANG_TR ? u"[TR]" : u" TR";
        case KC_LANG_KO: return g_local.lang == LANG_KO ? u"[KO]" : u" KO";
        case KC_LANG_JA: return g_local.lang == LANG_JA ? u"[JA]" : u" JA";
        case KC_LANG_AR: return g_local.lang == LANG_AR ? u"[AR]" : u" AR";
        case KC_LANG_GR: return g_local.lang == LANG_GR ? u"[GR]" : u" GR";
        //[[[end]]]
    case KC_LNG1:
        return u"Han/Y";
    case KC_APP:
        return u" Ctx";
    case DE_GRV: //for Neo Layout
        return u"`";
    default:
    {
        bool shift = ((get_mods() & MOD_MASK_SHIFT) != 0);
        const uint16_t* text = translate_keycode(g_local.lang, keycode, shift, state.caps_lock);
        if (text != NULL) {
            return text;
        }
    }
    break;
    }
    return NULL;
}

const uint16_t* keycode_to_disp_overlay(uint16_t keycode, led_t state) {
    switch (keycode)
    {
        case KC_F2: return u"      " PRIVATE_NOTE;
        case KC_F5: return u"     " ARROWS_CIRCLE;
        case QK_DEBUG_TOGGLE: return debug_enable==0 ? u"\v" ICON_SWITCH_OFF : u"\v" ICON_SWITCH_ON;
        //case RGB_TOG: return rgb_matrix_is_enabled() ? u"\v" ICON_SWITCH_ON : u"\v" ICON_SWITCH_OFF;
        default: break;
    }

    if( (get_mods() & MOD_MASK_CTRL) != 0) {
        switch(keycode) {
            case KC_A: return u"    " BOX_WITH_CHECK_MARK;
            case KC_C: return u"   " CLIPBOARD_COPY;
            case KC_D: return u"    " PRIVATE_DELETE;
            case KC_F: return u"   " PRIVATE_FIND;
            case KC_X: return u"    " CLIPBOARD_CUT;
            case KC_V: return u"    " CLIPBOARD_PASTE;
            case KC_S: return u"    " PRIVATE_FLOPPY;
            case KC_O: return u"     " FILE_OPEN;
            case KC_P: return u"    " PRIVATE_PRINTER;
            case KC_Z: return u"    " ARROWS_UNDO;
            case KC_Y: return u"    " ARROWS_REDO;
            default: break;
        }
    } else if((get_mods() & MOD_MASK_GUI) != 0) {
        switch(keycode) {
            case KC_D:      return u"    " PRIVATE_PC;
            case KC_L:      return u"    " PRIVATE_LOCK;
            case KC_P:      return u"    " PRIVATE_SCREEN;
            case KC_UP:     return u"     " PRIVATE_MAXIMIZE;
            case KC_DOWN:   return u"     " PRIVATE_WINDOW;
            default: break;
        }
    }
    return NULL;
}


void update_displays(enum refresh_mode mode) {
    uint8_t layer = get_highest_layer(layer_state);
    /*if (layer > _LL) {
        layer = g_local.default_ls;
    }*/

    //set_displays(g_local.contrast, false);

    led_t state = host_keyboard_led_state();
    bool capital_case = ((get_mods() & MOD_MASK_SHIFT) != 0) || state.caps_lock;
    //the left side has an offset of 0, the right side an offset of MATRIX_ROWS_PER_SIDE
    uint8_t offset = is_left_side() ? 0 : MATRIX_ROWS_PER_SIDE;
    uint8_t start_row = 0;

    //select first display (and later on shift that 0 till the end)
    if (mode == START_SECOND_HALF) {
        sr_shift_out_buffer_latch(disp_row_3.bitmask, sizeof(struct display_info));
        start_row = 3;
    }
    else {
        sr_shift_out_buffer_latch(disp_row_0.bitmask, sizeof(struct display_info));
    }

    uint8_t max_rows = mode == START_FIRST_HALF ? 3 : MATRIX_ROWS_PER_SIDE;

    uint8_t skip = 0;
    for (uint8_t r = start_row; r < max_rows; ++r) {
        for (uint8_t c = 0; c < MATRIX_COLS; ++c) {
            uint8_t  disp_idx = LAYOUT_TO_INDEX(r, c);

            //since MATRIX_COLS==8 we don't need to shift multiple times at the end of the row
            //except there was a leading and missing physical key (KC_NO on base layer)
            uint16_t keycode = keymaps[_BL][r + offset][c];
            if (keycode == KC_NO) {
                skip++;
            }
            else {
                if (disp_idx != 255) {
                    keycode = keymaps[layer][r + offset][c];
                    kdisp_enable(true);//(g_local.flags&STATUS_DISP_ON) != 0);
                    kdisp_set_contrast(g_local.contrast-1);
                    if(keycode!=KC_TRNS) {
                        const uint16_t* text = keycode_to_disp_text(keycode, state);
                        kdisp_set_buffer(0x00);
                        if(text==NULL){
                            if((keycode&QK_UNICODEMAP_PAIR)!=0){
                                uint16_t chr = capital_case ? QK_UNICODEMAP_PAIR_GET_SHIFTED_INDEX(keycode) : QK_UNICODEMAP_PAIR_GET_UNSHIFTED_INDEX(keycode);
                                kdisp_write_gfx_char(ALL_FONTS, sizeof(ALL_FONTS) / sizeof(GFXfont*), 28, 23, unicode_map[chr]);
                            }
                        } else {
                            kdisp_write_gfx_text(ALL_FONTS, sizeof(ALL_FONTS) / sizeof(GFXfont*), 28, 23, text);
                        }
                        text = keycode_to_disp_overlay(keycode, state);
                        if(text!=NULL) {
                            kdisp_write_gfx_text(ALL_FONTS, sizeof(ALL_FONTS) / sizeof(GFXfont*), 28, 23, text);
                        }
                        kdisp_send_buffer();
                    }
                }
                sr_shift_once_latch();
            }

        }
        for (;skip > 0;skip--) {
            sr_shift_once_latch();
        }
    }
}

uint8_t to_brightness(uint8_t b) {
    switch(b) {
        case 23: case 24: case 25: case 26: case 27: return 7;
        case 22: case 28: return 6;
        case 21: case 29: return 5;
        case 20: case 30: return 4;
        case 19: case 31: return 3;
        case 18: case 32: return 2;
        case 1: case 7: return 1;
        case 2: case 6: return 3;
        case 3: case 4: case 5: return 5;
        default: return 0;
    }
}

void kdisp_idle(uint8_t contrast) {
    uint8_t offset = is_left_side() ? 0 : MATRIX_ROWS_PER_SIDE;
    uint8_t skip = 0;
    sr_shift_out_buffer_latch(disp_row_0.bitmask, sizeof(struct display_info));

    //uint8_t idx = 0;
    for (uint8_t r = 0; r < MATRIX_ROWS_PER_SIDE; ++r) {
        for (uint8_t c = 0; c < MATRIX_COLS; ++c) {
            uint8_t  disp_idx = LAYOUT_TO_INDEX(r, c);

            //since MATRIX_COLS==8 we don't need to shift multiple times at the end of the row
            //except there was a leading and missing physical key (KC_NO on base layer)
            uint16_t keycode = keymaps[_BL][r + offset][c];
            if (keycode == KC_NO) {
                skip++;
            } else {
                if (disp_idx != 255) {
                    uint8_t idle_brightness = to_brightness((contrast+(c%3+r)*keycode+offset+r)%50);
                    if(idle_brightness==0) {
                        kdisp_enable(false);
                    } else {
                        kdisp_enable(true);
                        kdisp_set_contrast(idle_brightness-1);
                    }
                }
                sr_shift_once_latch();
            }

        }
        for (;skip > 0;skip--) {
            sr_shift_once_latch();
        }
    }
}

void display_message(uint8_t row, uint8_t col, const uint16_t* message, const GFXfont* font) {

    const GFXfont* displayFont[] = { font };
    uint8_t index = 0;
    for (uint8_t c = 0; c < MATRIX_COLS; ++c) {

        uint8_t disp_idx = LAYOUT_TO_INDEX(row, c);

        if (disp_idx != 255) {

            sr_shift_out_buffer_latch(key_display[disp_idx].bitmask, sizeof(key_display->bitmask));
            kdisp_set_buffer(0x00);

            if (c >= col && message[index] != 0) {
                const uint16_t text[2] = { message[index], 0 };
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
            //uprintf("Enter Bootloader...");
            clear_all_displays();
            display_message(1, 1, u"BOOT-", &FreeSansBold24pt7b);
            display_message(3, 0, u"LOADER!", &FreeSansBold24pt7b);
            break;
        }
    }

    return display_wakeup(record);
}

/*
           0            1        2              3            4       5            6             7
    [_L0] = LAYOUT_left_right_stacked(
        KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_NUBS,
        KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_GRAVE,
        MO(_FL0),   KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_QUOTE,   KC_MS_BTN1,
        KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_NUHS,    MO(_NL),
        KC_LCTL,    KC_LWIN,    KC_LALT,    KC_APP,                 KC_SPACE,   KC_DEL,     KC_ENTER,

                    KC_7,       KC_8,       KC_9,       KC_0,       KC_MINUS,   KC_EQUAL,   KC_6,
                    KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,    KC_HYPR,
        KC_NO,      KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_RBRC,    MO(_ADDLANG
        KC_LANG,    KC_BSLS,    KC_N,       KC_M,       KC_COMMA,   KC_DOT,     KC_SLASH,   KC_RSFT,
        KC_ENTER,   KC_BSPC,    KC_SPC,                 KC_LEFT,    KC_UP,      KC_DOWN,    KC_RIGHT
        ),
         8            9          10          11           12          13         14           15
    [_L1] = LAYOUT_left_right_stacked(
        KC_ESC,     KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,
        KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_GRAVE,
        MO(_FL1),   KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_QUOTE,   KC_MS_BTN1,
        KC_LSFT,    KC_NUHS,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       MO(_NL),
        KC_LCTL,    KC_LWIN,    KC_LALT,    MO(_ADDLANG1),          KC_SPACE,   KC_DEL,     KC_ENTER,

                    KC_7,       KC_8,       KC_9,       KC_0,       KC_MINUS,   KC_EQUAL,   KC_HYPR,
                    KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,    KC_NUBS,
        KC_NO,      KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_RBRC,    KC_BSLS,
        KC_LANG,    KC_APP,     KC_N,       KC_M,       KC_COMMA,   KC_DOT,     KC_SLASH,   KC_RSFT,
        KC_ENTER,   KC_BSPC,    KC_SPC,                 KC_LEFT,    KC_UP,      KC_DOWN,    KC_RIGHT
        ),
*/
// void shiftl_row(const uint8_t row, const uint8_t from, const uint8_t to) {
//     uint16_t swap = keymaps[g_local.default_ls][row][from];

//     for(uint8_t current = from; current<to; current++) {
//         keymaps[g_local.default_ls][row][current] = keymaps[g_local.default_ls][row][current+1];
//     }
//     keymaps[g_local.default_ls][row][to] = swap;
// }

// void shiftr_row(const uint8_t row, const uint8_t from, const uint8_t to) {
//     uint16_t swap = keymaps[g_local.default_ls][row][to];

//     for(uint8_t current = to; current>from; current--) {
//         keymaps[g_local.default_ls][row][current] = keymaps[g_local.default_ls][row][current-1];
//     }
//     keymaps[g_local.default_ls][row][from] = swap;
// }

// void swap_keys(const uint8_t r1, const uint8_t c1, const uint8_t r2, const uint8_t c2) {
//     uint16_t swap = keymaps[g_local.default_ls][r1][c1];
//     keymaps[g_local.default_ls][r1][c1] = keymaps[g_local.default_ls][r2][c2];
//     keymaps[g_local.default_ls][r2][c2] = swap;
// }

// void shiftl_3keys(const uint8_t r1, const uint8_t c1, const uint8_t r2, const uint8_t c2, const uint8_t r3, const uint8_t c3) {
//     uint16_t swap = keymaps[g_local.default_ls][r1][c1];
//     keymaps[g_local.default_ls][r1][c1] = keymaps[g_local.default_ls][r2][c2];
//     keymaps[g_local.default_ls][r2][c2] = keymaps[g_local.default_ls][r3][c3];
//     keymaps[g_local.default_ls][r3][c3] = swap;
// }

// void shiftr_3keys(const uint8_t r1, const uint8_t c1, const uint8_t r2, const uint8_t c2, const uint8_t r3, const uint8_t c3) {
//     uint16_t swap = keymaps[g_local.default_ls][r3][c3];
//     keymaps[g_local.default_ls][r3][c3] = keymaps[g_local.default_ls][r2][c2];
//     keymaps[g_local.default_ls][r2][c2] = keymaps[g_local.default_ls][r1][c1];
//     keymaps[g_local.default_ls][r1][c1] = swap;
// }

// void toggle_stagger(bool new_state) {
//     bool current_state = (g_local.flags&USE_STAGGER) != 0;
//     if(current_state!=new_state) {
//         if(new_state) {
//             shiftr_row(3,1,6);

//             keymaps[g_local.default_ls][0][2] = MO(_FL1);

//             shiftl_row(6,1,7);
//             shiftl_row(7,1,7);
//             shiftl_row(5,1,7);

//             shiftl_3keys(7,7, 8,1, 4,3);
//             shiftl_3keys(7,5, 7,6, 0,6);
//         } else {
//             shiftl_row(3,1,6);

//             keymaps[g_local.default_ls][0][2] = MO(_FL0);

//             shiftr_3keys(7,7, 8,1, 4,3);
//             shiftr_3keys(7,5, 7,6, 0,6);

//             shiftr_row(6,1,7);
//             shiftr_row(7,1,7);
//             shiftr_row(5,1,7);
//         }
//     }
// }

void post_process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (keycode == KC_CAPS_LOCK) {
        request_disp_refresh();
    }

    if (!record->event.pressed) {
        switch (keycode) {
        case KC_DEADKEY:
            if((g_local.flags&DEAD_KEY_ON_WAKEUP)==0) {
                g_local.flags |= DEAD_KEY_ON_WAKEUP;
            } else {
                g_local.flags &= ~((uint8_t)DEAD_KEY_ON_WAKEUP);
            }
            request_disp_refresh();
            break;
        case KC_L0:
            g_local.default_ls = _L0;
            persistent_default_layer_set(g_local.default_ls);
            request_disp_refresh();
            break;
        case KC_L1:
            g_local.default_ls = _L1;
            persistent_default_layer_set(g_local.default_ls);
            request_disp_refresh();
            break;
        case KC_L2:
            g_local.default_ls = _L2;
            persistent_default_layer_set(g_local.default_ls);
            request_disp_refresh();
            break;
        case KC_L3:
            g_local.default_ls = _L3;
            persistent_default_layer_set(g_local.default_ls);
            request_disp_refresh();
            break;
        case KC_L4:
            g_local.default_ls = _L4;
            persistent_default_layer_set(g_local.default_ls);
            request_disp_refresh();
            break;
        case KC_BASE:
            layer_clear();
            layer_on(g_local.default_ls);
            break;
        case KC_RIGHT_SHIFT:
        case KC_LEFT_SHIFT:
            request_disp_refresh();
            break;
        case KC_D1Q:
            g_local.contrast = FULL_BRIGHT/4;
            save_user_eeconf();
            break;
        case KC_D3Q:
            g_local.contrast = (FULL_BRIGHT/4)*3;
            save_user_eeconf();
            break;
        case KC_DHLF:
            g_local.contrast = FULL_BRIGHT/2;
            save_user_eeconf();
            break;
        case KC_DMAX:
            g_local.contrast = FULL_BRIGHT;
            save_user_eeconf();
            break;
        case KC_DMIN:
            g_local.contrast = 2;
            save_user_eeconf();
            break;
        case KC_DDIM:
            dec_brightness();
            break;
        case KC_DBRI:
            inc_brightness();
            break;
            /*[[[cog
            for lang in languages:
                cog.outl(f'case KC_{lang}: g_local.lang = {lang}; layer_off(_LL); break;')
            ]]]*/
            case KC_LANG_EN: g_local.lang = LANG_EN; layer_off(_LL); break;
            case KC_LANG_DE: g_local.lang = LANG_DE; layer_off(_LL); break;
            case KC_LANG_FR: g_local.lang = LANG_FR; layer_off(_LL); break;
            case KC_LANG_ES: g_local.lang = LANG_ES; layer_off(_LL); break;
            case KC_LANG_PT: g_local.lang = LANG_PT; layer_off(_LL); break;
            case KC_LANG_IT: g_local.lang = LANG_IT; layer_off(_LL); break;
            case KC_LANG_TR: g_local.lang = LANG_TR; layer_off(_LL); break;
            case KC_LANG_KO: g_local.lang = LANG_KO; layer_off(_LL); break;
            case KC_LANG_JA: g_local.lang = LANG_JA; layer_off(_LL); break;
            case KC_LANG_AR: g_local.lang = LANG_AR; layer_off(_LL); break;
            case KC_LANG_GR: g_local.lang = LANG_GR; layer_off(_LL); break;
            //[[[end]]]
        case KC_F1:case KC_F2:case KC_F3:case KC_F4:case KC_F5:case KC_F6:
        case KC_F7:case KC_F8:case KC_F9:case KC_F10:case KC_F11:case KC_F12:
            layer_off(_LL);
            break;
        default:
            break;
        }
    }
    else {
        switch (keycode)
        {
        case KC_RIGHT_SHIFT:
        case KC_LEFT_SHIFT:
            request_disp_refresh();
            break;
        case KC_LANG:
            if (IS_LAYER_ON(_LL)) {
                g_local.lang = (g_local.lang + 1) % NUM_LANG;
                layer_off(_LL);
            }
            else {
                layer_on(_LL);
            }
            break;
        case RGB_TOG:
            if(!rgb_matrix_is_enabled()) {
                g_local.flags |= RGB_MATRIX_ON;
            }else{
                g_local.flags &= ~((uint8_t)RGB_MATRIX_ON);
            }
        case RGB_MOD:
        case RGB_RMOD:
            request_disp_refresh();
            break;
        case QK_DEBUG_TOGGLE:
            if (!debug_enable) {
                debug_enable = 1;
            } else if (!debug_keyboard) {
                debug_keyboard = 1;
            } else if (!debug_matrix) {
                debug_matrix = 1;
            } else {
                debug_enable   = 0;
                debug_keyboard = 0;
                debug_matrix   = 0;
            }
            dprintf("DEBUG: enable=%u, keyboard=%u, matrix=%u\n", debug_enable, debug_keyboard, debug_matrix);
            dprint(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE "\n");
            eeconfig_update_debug(debug_config.raw);
            break;
        default:
            break;
        }
    }

    //uprintf("Key 0x%04X, col/row: %u/%u, %s, time: %u, int: %d, cnt: %u disp#: %d 0x%02X%02X%02X%02X%02X\n",
     //   keycode, record->event.key.col, record->event.key.row, record->event.pressed ? "DN" : "UP",
     //   record->event.time, record->tap.interrupted ? 1 : 0, record->tap.count, disp_idx, bitmask[4], bitmask[3], bitmask[2], bitmask[1], bitmask[0]);

    update_performed();
};

void show_splash_screen(void) {
    clear_all_displays();
    display_message(1, 1, u"POLY", &FreeSansBold24pt7b);
    display_message(2, 1, u"KYBD", &FreeSansBold24pt7b);
}

void oled_on_off(bool on) {
    if (!on) {//} && is_oled_on()) {
        oled_off();
    } else { //} if (on && !is_oled_on()) {
        oled_on();
        uprintf("oled_on %s", is_usb_host_side() ? "Host" : "Bridge");
    }
}

void set_displays(uint8_t contrast, bool idle) {
    if(idle) {
        kdisp_idle(contrast);
    } else {
        select_all_displays();
        if(contrast==DISP_OFF) {
            kdisp_enable(false);
        } else {
            kdisp_enable(true);
            kdisp_set_contrast(contrast - 1);
        }
    }
}



//disable first keypress if the displays are turned off
bool display_wakeup(keyrecord_t* record) {
    bool accept_keypress = true;
    if ((g_local.contrast==DISP_OFF || (g_local.flags & DISP_IDLE)!=0) && record->event.pressed) {
        if(g_local.contrast==DISP_OFF && (g_local.flags&DEAD_KEY_ON_WAKEUP)!=0) {
            accept_keypress = timer_elapsed32(last_update) <= TURN_OFF_TIME;
        }
        poly_eeconf ee = load_user_eeconf();
        g_local.contrast = ee.conf.brightness;
        g_local.flags &= ~((uint8_t)DISP_IDLE);
        g_local.flags |= STATUS_DISP_ON;
        update_performed();
        request_disp_refresh();
    }

    return accept_keypress;
}
//void oled_render_logos(void);
void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable = true;
    debug_matrix = false;
    debug_keyboard = false;
    debug_mouse = false;

    //pointing_device_set_cpi(20000);
    //pointing_device_set_cpi(2000);
    //pimoroni_trackball_set_rgbw(0,0,255,100);
    g_local.default_ls = persistent_default_layer_get();
    layer_clear();
    layer_on(g_local.default_ls);

    //set these values, they will never change
    com = is_keyboard_master() ? USB_HOST : BRIDGE;
    side = is_keyboard_left() ? LEFT_SIDE : RIGHT_SIDE;

    //encoder pins
    setPinInputHigh(GP25);
    setPinInputHigh(GP29);

    //srand(halGetCounterValue());
    dprintf("PolyKybd ready.");

    wait_ms(500);
    transaction_register_rpc(USER_SYNC_POLY_DATA, user_sync_poly_data_handler);
/*
    int8_t retries = 5;
    while(!transaction_rpc_send(USER_SYNC_POLY_DATA, sizeof(g_local), &g_local) && retries>0) {
        retries--;
        wait_ms(1000);
        dprintf("Connecting...");
    }*/
}

void keyboard_pre_init_user(void) {
    memset(&g_state, 0, sizeof(g_state));
    kdisp_hw_setup();
    kdisp_init(NUM_SHIFT_REGISTERS);
    peripherals_reset();
    kdisp_setup(true);

    select_all_displays();
    kdisp_scroll_vlines(47);
    kdisp_scroll_modehv(true, 3, 1);
    kdisp_scroll(false);

    poly_eeconf ee = load_user_eeconf();

    g_local.lang = ee.conf.lang;
    g_local.default_ls = 0;
    g_local.contrast = ee.conf.brightness;
    g_local.flags = STATUS_DISP_ON;

    set_displays(g_local.contrast, false);
    show_splash_screen();

    setPinInputHigh(I2C1_SDA_PIN);
}

void eeconfig_init_user(void) {
    poly_eeconf ee;
    ee.conf.lang = g_lang_init;
    ee.conf.brightness = ~FULL_BRIGHT;
    ee.conf.unused = 0;
    eeconfig_update_user(ee.raw);
}


void num_to_u16_string(char* buffer, uint8_t buffer_len, uint8_t value) {
    if(value<10) {
        snprintf((char*) buffer, buffer_len, "%d", value);
        buffer[1] = 0;
        buffer[2] = 0;
        buffer[3] = 0;
    } else if(value>99) {
        snprintf((char*) buffer, buffer_len, "%d %d %d", value/100, (value/10)%10, value%10);
        buffer[1] = 0;
        buffer[3] = 0;
        buffer[5] = 0;
        buffer[6] = 0;
        buffer[7] = 0;
    } else {
        snprintf((char*) buffer, buffer_len, "%d %d", value/10, value%10);
        buffer[1] = 0;
        buffer[3] = 0;
        buffer[4] = 0;
        buffer[5] = 0;
    }
}

void hex_to_u16_string(char* buffer, uint8_t buffer_len, uint8_t value) {
    if(value<16) {
        snprintf((char*) buffer, buffer_len, "%X", value);
        buffer[1] = 0;
        buffer[2] = 0;
        buffer[3] = 0;
    } else {
        snprintf((char*) buffer, buffer_len, "%X %X", value/16, value%16);
        buffer[1] = 0;
        buffer[3] = 0;
        buffer[4] = 0;
        buffer[5] = 0;
    }
}

void oled_status_screen(void) {
    if( (g_local.flags&STATUS_DISP_ON) == 0) {
        oled_off();
        //rgb_matrix_disable_noeeprom();
        return;
    } else if( (g_local.flags&STATUS_DISP_ON) != 0) {
        oled_on();
    }
    uint16_t buffer[32];

    kdisp_set_buffer(0);

    const GFXfont* displayFont[] = { &NotoSans_Regular11pt7b };
    const GFXfont* smallFont[] = { &NotoSans_Medium8pt7b };
    kdisp_write_gfx_text(ALL_FONTS, sizeof(ALL_FONTS) / sizeof(GFXfont*), 0, 14, ICON_LAYER);
    hex_to_u16_string((char*) buffer, sizeof(buffer), get_highest_layer(layer_state));
    kdisp_write_gfx_text(displayFont, 1, 20, 14, buffer);
    if(side==UNDECIDED) {
        kdisp_write_gfx_text(displayFont, 1, 50, 14, u"Uknw");
    } else {
        kdisp_write_gfx_text(displayFont, 1, 38, 14, is_left_side() ? u"LEFT" : u"RIGHT");
    }

    kdisp_write_gfx_text(ALL_FONTS, sizeof(ALL_FONTS) / sizeof(GFXfont*), 108, 16, g_state.led_state.num_lock ? ICON_NUMLOCK_ON : ICON_NUMLOCK_OFF);
    kdisp_write_gfx_text(ALL_FONTS, sizeof(ALL_FONTS) / sizeof(GFXfont*), 108, 38, g_state.led_state.caps_lock ? ICON_CAPSLOCK_ON : ICON_CAPSLOCK_OFF);
    if(g_state.led_state.scroll_lock) {
        kdisp_write_gfx_text(ALL_FONTS, sizeof(ALL_FONTS) / sizeof(GFXfont*), 112, 54, ARROWS_DOWNSTOP);
    } else {
        kdisp_write_gfx_text(smallFont, 1, 112, 56, is_usb_host_side() ? u"H" : u"B");
    }



    if(is_right_side()) {
        kdisp_write_gfx_text(smallFont, 1, 0, 30, u"RGB");

        if(!rgb_matrix_is_enabled()) {
            kdisp_write_gfx_text(smallFont, 1, 34, 30, u"Off");
        } else {
            num_to_u16_string((char*) buffer, sizeof(buffer), rgb_matrix_get_mode());
            kdisp_write_gfx_text(smallFont, 1, 34, 30, buffer);
            kdisp_write_gfx_text(smallFont, 1, 58, 30, get_led_matrix_text(rgb_matrix_get_mode()));
            kdisp_write_gfx_text(smallFont, 1, 0, 44, u"HSV");
            hex_to_u16_string((char*) buffer, sizeof(buffer), rgb_matrix_get_hue());
            kdisp_write_gfx_text(smallFont, 1, 38, 44, buffer);
            hex_to_u16_string((char*) buffer, sizeof(buffer), rgb_matrix_get_sat());
            kdisp_write_gfx_text(smallFont, 1, 60, 44, buffer);
            hex_to_u16_string((char*) buffer, sizeof(buffer), rgb_matrix_get_val());
            kdisp_write_gfx_text(smallFont, 1, 82, 44, buffer);
            kdisp_write_gfx_text(smallFont, 1, 0, 58, u"Speed");
            num_to_u16_string((char*) buffer, sizeof(buffer), rgb_matrix_get_speed());
            kdisp_write_gfx_text(smallFont, 1, 58, 58, buffer);
        }
    } else {
        switch(g_local.default_ls) {
            case 0: kdisp_write_gfx_text(smallFont, 1, 0, 30, u"Qwerty"); break;
            case 1: kdisp_write_gfx_text(smallFont, 1, 0, 30, u"Qwerty Stag!"); break;
            case 2: kdisp_write_gfx_text(smallFont, 1, 0, 30, u"Colemak DH"); break;
            case 3: kdisp_write_gfx_text(smallFont, 1, 0, 30, u"Neo"); break;
            case 4: kdisp_write_gfx_text(smallFont, 1, 0, 30, u"Workman"); break;
            default: kdisp_write_gfx_text(smallFont, 1, 0, 30, u"Unknown"); break;
        }
        kdisp_write_gfx_text(smallFont, 1, 0, 44, u"Dsp*");
        num_to_u16_string((char*) buffer, sizeof(buffer), g_local.contrast);
        kdisp_write_gfx_text(smallFont, 1, 42, 44, buffer);
        uint8_t i=0;
        for(;i<(g_local.contrast/5);++i) {
            buffer[i] = 'l';
        }
        buffer[i] = 0;
        buffer[i+1] = 0;
        kdisp_write_gfx_text(smallFont, 1, 64, 44, buffer);

        kdisp_write_gfx_text(smallFont, 1, 0, 58, u"WPM");
        num_to_u16_string((char*) buffer, sizeof(buffer), get_current_wpm());
        kdisp_write_gfx_text(smallFont, 1, 44, 58, buffer);
    }

    oled_clear();
    oled_write_raw((char *)get_scratch_buffer(), get_scratch_buffer_size());
}

void oled_render_logos(void) {
    if(is_left_side()) {
        oled_draw_poly();
        oled_scroll_right();
    } else {
        oled_draw_kybd();
        oled_scroll_left();
    }
}
bool oled_task_user(void) {
    if((g_local.flags&DISP_IDLE) != 0) {
        oled_render_logos();
    } else {
        oled_scroll_off();
        oled_status_screen();
    }
    return false;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
      tap_code(KC_WH_U);
    } else {
      tap_code(KC_WH_D);
    }

    return false;
}

void invert_display(uint8_t r, uint8_t c, bool state) {
    uint16_t keycode = keymaps[_BL][r][0];
    if (keycode == KC_NO) {
        c--;
    }

    r = r % MATRIX_ROWS_PER_SIDE;
    uint8_t disp_idx = LAYOUT_TO_INDEX(r, c);
    const uint8_t* bitmask = key_display[disp_idx].bitmask;
    sr_shift_out_buffer_latch(bitmask, sizeof(key_display->bitmask));

    if (disp_idx != 255) {
        kdisp_invert(state);
    }
}

// invert displays directly when pressed (no need to do split sync)
extern matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t last_matrix[MATRIX_ROWS_PER_SIDE];
void matrix_scan_user(void) {
    uint8_t first   = is_left_side() ? 0 : MATRIX_ROWS_PER_SIDE;
    bool    changed = false;
    for (uint8_t r = first; r < first + MATRIX_ROWS_PER_SIDE; r++) {
        if (last_matrix[r - first] != matrix[r]) {
            changed = true;
            for (uint8_t c = 0; c < MATRIX_COLS; c++) {
                bool old     = ((last_matrix[r - first] >> c) & 1) == 1;
                bool current = ((matrix[r] >> c) & 1) == 1;
                if (!old && current) {
                    invert_display(r,c,true);
                } else if (old && !current) {
                    invert_display(r,c,false);
                }
            }
        }
    }
    if (changed) {
        memcpy(last_matrix, &matrix[first], sizeof(last_matrix));
    }
}

void matrix_slave_scan_user(void) {
    matrix_scan_user();
}

oled_rotation_t oled_init_user(oled_rotation_t rotation){
    oled_off();
    oled_clear();
    oled_render();
    oled_scroll_set_speed(0);
    oled_render_logos();
    oled_on();
    return rotation;
}

void suspend_power_down_kb(void) {
    dprint("Suspend power down\n");
    g_local.flags &= ~((uint8_t)STATUS_DISP_ON);
    g_local.flags &= ~((uint8_t)DISP_IDLE);
    g_local.contrast = DISP_OFF;

    if(rgb_matrix_is_enabled()) {
         g_local.flags |= RGB_MATRIX_ON;
    }else{
         g_local.flags &= ~((uint8_t)RGB_MATRIX_ON);
    }

    sync_and_refresh_displays();
    //sync_and_refresh_displays();
}

void suspend_wakeup_init_kb(void) {
    dprint("Suspend wakeup\n");
    g_local.flags |= STATUS_DISP_ON;
    g_local.flags &= ~((uint8_t)DISP_IDLE);
    g_local.contrast = FULL_BRIGHT;

    if((g_local.flags&RGB_MATRIX_ON)==0) {
        rgb_matrix_disable_noeeprom();
    } else {
        rgb_matrix_enable_noeeprom();
    }
    if(is_usb_host_side()) {
        sync_and_refresh_displays();
    }
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    uint8_t response[length];
    memset(response, 0, length);
    response[0] = 'K';

    if(data[0] == 'P') {
        raw_hid_send(response, length);
    }
}
