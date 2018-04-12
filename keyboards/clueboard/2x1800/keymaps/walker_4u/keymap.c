/* Copyright 2017 Zach White <skullydazed@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "2x1800.h"
#include "audio.h"
#include "song_list.h"

float tone_my_startup[][2] = SONG(ODE_TO_JOY);
float tone_my_goodbye[][2] = SONG(ROCK_A_BYE_BABY);

float tone_audio_on[][2]   = SONG(CLOSE_ENCOUNTERS_5_NOTE);
float tone_music_on[][2]   = SONG(DOE_A_DEER);
float tone_caps_on[][2]    = SONG(CAPS_LOCK_ON_SOUND);
float tone_caps_off[][2]   = SONG(CAPS_LOCK_OFF_SOUND);
float tone_numlk_on[][2]   = SONG(NUM_LOCK_ON_SOUND);
float tone_numlk_off[][2]  = SONG(NUM_LOCK_OFF_SOUND);
float tone_scroll_on[][2]  = SONG(SCROLL_LOCK_ON_SOUND);
float tone_scroll_off[][2] = SONG(SCROLL_LOCK_OFF_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);

enum keyboard_layers {
  LAYER_QWERTY = 0,
  LAYER_UPPER,
  LAYER_LOWER,
  LAYER_ADJUST,
};
enum keyboard_macros {
  MACRO_QWERTY = 0,
  MACRO_UPPER,
  MACRO_LOWER,
  MACRO_FUNCTION,
  MACRO_MOUSE,
  MACRO_TIMBRE_1,
  MACRO_TIMBRE_2,
  MACRO_TIMBRE_3,
  MACRO_TIMBRE_4,
  MACRO_TEMPO_U,
  MACRO_TEMPO_D,
  MACRO_TONE_DEFAULT,
  MACRO_MUSIC_TOGGLE,
  MACRO_AUDIO_TOGGLE,
  MACRO_INC_VOICE,
  MACRO_DEC_VOICE,
  MACRO_BACKLIGHT,
  MACRO_BREATH_TOGGLE,
  MACRO_BREATH_SPEED_INC,
  MACRO_BREATH_SPEED_DEC,
  MACRO_BREATH_DEFAULT,
  MACRO_MOUSE_MOVE_UL,
  MACRO_MOUSE_MOVE_UR,
  MACRO_MOUSE_MOVE_DL,
  MACRO_MOUSE_MOVE_DR,
  MACRO_HELP_1,
  MACRO_HELP_2,
  MACRO_HELP_3,
  MACRO_HELP_4,
  MACRO_HELP_5,
  MACRO_HELP_6,
  MACRO_HELP_7,
  MACRO_HELP_8,
  MACRO_HELP_9,
};

#define M_UPPER             M(MACRO_UPPER)
#define M_LOWER             M(MACRO_LOWER)
#define M_FUNCT             M(MACRO_FUNCTION)
#define M_MOUSE             M(MACRO_MOUSE)
#define TIMBR_1             M(MACRO_TIMBRE_1)
#define TIMBR_2             M(MACRO_TIMBRE_2)
#define TIMBR_3             M(MACRO_TIMBRE_3)
#define TIMBR_4             M(MACRO_TIMBRE_4)
#define TMPO_UP             M(MACRO_TEMPO_U)
#define TMPO_DN             M(MACRO_TEMPO_D)
#define TMPO_DF             M(MACRO_TONE_DEFAULT)
#define M_BACKL             M(MACRO_BACKLIGHT)
#define M_BRTOG             M(MACRO_BREATH_TOGGLE)
#define M_BSPDU             M(MACRO_BREATH_SPEED_INC)
#define M_BSPDD             M(MACRO_BREATH_SPEED_DEC)
#define M_BDFLT             M(MACRO_BREATH_DEFAULT)
#define M_MS_UL             M(MACRO_MOUSE_MOVE_UL)
#define M_MS_UR             M(MACRO_MOUSE_MOVE_UR)
#define M_MS_DL             M(MACRO_MOUSE_MOVE_DL)
#define M_MS_DR             M(MACRO_MOUSE_MOVE_DR)
#define M_HELP1             M(MACRO_HELP_1)
#define M_HELP2             M(MACRO_HELP_2)
#define M_HELP3             M(MACRO_HELP_3)
#define M_HELP4             M(MACRO_HELP_4)
#define M_HELP5             M(MACRO_HELP_5)
#define M_HELP6             M(MACRO_HELP_6)
#define M_HELP7             M(MACRO_HELP_7)
#define M_HELP8             M(MACRO_HELP_8)
#define M_HELP9             M(MACRO_HELP_9)


#define VC_UP               M(MACRO_INC_VOICE)
#define VC_DOWN             M(MACRO_DEC_VOICE)


#define SC_UNDO             LCTL(KC_Z)
#define SC_REDO             LCTL(KC_Y)
#define SC_CUT              LCTL(KC_X)
#define SC_COPY             LCTL(KC_C)
#define SC_PSTE             LCTL(KC_V)
#define SC_SELA             LCTL(KC_A)
#define SC_SAVE             LCTL(KC_S)
#define SC_OPEN             LCTL(KC_O)
#define SC_ACLS             LALT(KC_F4)
#define SC_CCLS             LCTL(KC_F4)

#define TG_NKRO             MAGIC_TOGGLE_NKRO
#define OS_SHFT             KC_FN0

#define _______             KC_TRNS
#define XXXXXXX             KC_NO
#define ________________    _______, _______
#define XXXXXXXXXXXXXXXX    XXXXXXX, XXXXXXX


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[LAYER_QWERTY] = LAYOUT_4U_SPACE(
      KC_HOME, KC_END,  KC_PGUP, KC_PGDN,       KC_ESC,    KC_F1,   KC_F2,   KC_F3,   KC_F4,     KC_F5,   KC_F6,   KC_F7,   KC_F8,     KC_F9,   KC_F10,   KC_F11,  KC_F12,        KC_PSCR, KC_SLCK, KC_PAUS, KC_INS,  \
                                                                                                                                                                                                                      \
      KC_PMNS, KC_NLCK, KC_PSLS, KC_PAST,      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,   KC_BSPC,     KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, \
      KC_PPLS, KC_P7,   KC_P8,   KC_P9,        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, KC_RBRC, KC_BSLS,       KC_P7, KC_P8, KC_P9, KC_PSLS,       \
               KC_P4,   KC_P5,   KC_P6,        KC_CAPS,     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,    KC_QUOT, KC_ENT,         KC_P4, KC_P5, KC_P6,                \
      KC_PENT, KC_P1,   KC_P2,   KC_P3,     KC_UP,  KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M, KC_SLSH, KC_COMM, KC_DOT,   KC_RSFT,      KC_UP,      KC_P1, KC_P2, KC_P3, KC_PENT,       \
               KC_P0,   KC_PDOT,  KC_LEFT, KC_DOWN, KC_RGHT,  KC_LCTL, KC_LGUI, KC_LALT,                 KC_SPC,         AU_TOG, KC_RGUI, KC_APP, KC_RCTL,  KC_LEFT, KC_DOWN, KC_RGHT,  KC_P0, KC_PDOT               \
),


[LAYER_UPPER] = LAYOUT_4U_SPACE(
      KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,       KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,     KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,     KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  \
                                                                                                                                                                                                                      \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,   KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       \
               KC_TRNS,   KC_TRNS,   KC_TRNS,        KC_TRNS,     KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS,                \
      KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,     KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,      KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       \
               KC_TRNS,   KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,                 KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS              \
),

[LAYER_LOWER] = LAYOUT_4U_SPACE(
      KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,       KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,     KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,     KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  \
                                                                                                                                                                                                                      \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,   KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       \
               KC_TRNS,   KC_TRNS,   KC_TRNS,        KC_TRNS,     KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS,                \
      KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,     KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,      KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       \
               KC_TRNS,   KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,                 KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS              \
),

[LAYER_ADJUST] = LAYOUT_4U_SPACE(
      KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,       KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,     KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,     KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  \
                                                                                                                                                                                                                      \
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,   KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
      KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       \
               KC_TRNS,   KC_TRNS,   KC_TRNS,        KC_TRNS,     KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS,                \
      KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,     KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,      KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,       \
               KC_TRNS,   KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,                 KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS              \
)

};

void led_set_user(uint8_t usb_led)
{
    static uint8_t old_usb_led = 0;

    _delay_ms(10); // gets rid of tick

    if ((usb_led & (1<<USB_LED_CAPS_LOCK)) && !(old_usb_led & (1<<USB_LED_CAPS_LOCK)))
    {
            // If CAPS LK LED is turning on...
            PLAY_SONG(tone_caps_on);
    }
    else if (!(usb_led & (1<<USB_LED_CAPS_LOCK)) && (old_usb_led & (1<<USB_LED_CAPS_LOCK)))
    {
            // If CAPS LK LED is turning off...
            PLAY_SONG(tone_caps_off);
    }
    else if ((usb_led & (1<<USB_LED_NUM_LOCK)) && !(old_usb_led & (1<<USB_LED_NUM_LOCK)))
    {
            // If NUM LK LED is turning on...
            PLAY_SONG(tone_numlk_on);
    }
    else if (!(usb_led & (1<<USB_LED_NUM_LOCK)) && (old_usb_led & (1<<USB_LED_NUM_LOCK)))
    {
            // If NUM LED is turning off...
            PLAY_SONG(tone_numlk_off);
    }
    else if ((usb_led & (1<<USB_LED_SCROLL_LOCK)) && !(old_usb_led & (1<<USB_LED_SCROLL_LOCK)))
    {
            // If SCROLL LK LED is turning on...
            PLAY_SONG(tone_scroll_on);
    }
    else if (!(usb_led & (1<<USB_LED_SCROLL_LOCK)) && (old_usb_led & (1<<USB_LED_SCROLL_LOCK)))
    {
            // If SCROLL LED is turning off...
            PLAY_SONG(tone_scroll_off);
    }
    old_usb_led = usb_led;
}

void startup_user()
{
    _delay_ms(10); // gets rid of tick
    PLAY_SONG(tone_my_startup);
}

void shutdown_user()
{
    PLAY_SONG(tone_my_goodbye);
    _delay_ms(2000);
    stop_all_notes();
}

void audio_on_user(void)
{
        PLAY_SONG(tone_audio_on);
}

void music_on_user(void)
{
        PLAY_SONG(tone_music_on);
}

void music_scale_user(void)
{
        PLAY_SONG(music_scale);
}


