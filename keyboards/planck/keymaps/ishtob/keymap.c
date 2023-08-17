// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include "ishtob.h"

extern keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 ,-----------------------------------------------------------------------------------.
 * |Tab/FN|   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | LCtl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |Ctl/Et|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |  ,   |   .  |   /  |  -   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  | Caps | Alt  | GUI  |Lower |    Space    |Raise |NumLay| RAlt | Men  | Del  |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12_wrapper(
  LT_FN(KC_TAB), _________________QWERTY_L1_________________, _________________QWERTY_R1_________________, KC_BSPC,
  KC_LCTL,       _________________QWERTY_L2_________________, _________________QWERTY_R2_________________, CTL_ENT,
  KC_LSFT,       _________________QWERTY_L3_________________, _________________QWERTY_R3_________________, LT_RAI(KC_MINS),
  KC_ESC,        KC_CAPS, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE, KC_RALT, TG_NUMLAY, KC_APP,  KC_DEL
),
 
/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |Ctl/Et|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |  -   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_ortho_4x12_wrapper(
  LT_FN(KC_TAB), _________________COLEMAK_L1________________, _________________COLEMAK_R1________________, KC_BSPC,
  KC_LCTL,       _________________COLEMAK_L2________________, _________________COLEMAK_R2________________, KC_ENT,
  KC_LSFT,       _________________COLEMAK_L3________________, _________________COLEMAK_R3________________, LT_RAI(KC_MINS),
  KC_ESC,        KC_CAPS, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE, KC_RALT, TG_NUMLAY, KC_APP,  KC_DEL
),
 
/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |Ctl/Et|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT_ortho_4x12_wrapper(
  LT_FN(KC_TAB), _________________DVORAK_L1_________________, _________________DVORAK_R1_________________, KC_BSPC,
  KC_LCTL,       _________________DVORAK_L2_________________, _________________DVORAK_R2_________________, KC_ENT,
  KC_LSFT,       _________________DVORAK_L3_________________, _________________DVORAK_R3_________________, LT_RAI(KC_MINS),
  KC_ESC,        KC_CAPS, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE, KC_RALT, TG_NUMLAY, KC_APP,  KC_DEL
),
 
/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   ~  |  \   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | |   [  |   ]  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12_wrapper(
  ________________NUMBER_LEFT________________, ________________NUMBER_RIGHT_______________,    KC_GRV,  KC_BSLS,
  _______, __________________LONG_FUNC_LEFT___________________,   KC_UNDS, KC_EQL,  KC_LBRC, KC_RBRC, KC_PIPE,
  _______, __________________LONG_FUNC_RIGHT__________________,S(KC_NUHS),S(KC_NUBS),KC_LCBR, KC_RCBR, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),
 
/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   *  |  \   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   A  |  Up  |   D  |      | Vol+ |   4  |   5  |   6  |   +  |   :  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  Lt  |  Dn  |  Rt  | Mute | Vol- |   1  |   2  |   3  |  Up  |   /  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |   0  |      | Left | Down | Right| NumLk|
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12_wrapper(
  ________________NUMBER_LEFT________________, ________________NUMBER_RIGHT_______________,    KC_PLUS,  KC_BSLS,
  _______, KC_A,    KC_UP,   KC_D,    KC_PSCR,  KC_VOLU, KC_4,    KC_5,    KC_6,    KC_PAST, KC_COLN, KC_QUOT,
  _______, KC_LEFT, KC_DOWN, KC_RIGHT,KC_MUTE, KC_VOLD, KC_1,    KC_2,    KC_3,    KC_UP, KC_SLSH,   _______,
  _______, _______, _______, _______, _______, KC_SPC,  KC_0,   _______,  KC_LEFT, KC_DOWN, KC_RIGHT,   KC_NUM
),
 
/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
 
[_PLOVER] = LAYOUT_ortho_4x12_wrapper(
  KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   ,
  XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
  XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  EXT_PLV, XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX
),
 
/* FN layer on Esc key
 * ,-----------------------------------------------------------------------------------.
 * |      |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |   +  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   =  |   [  |   ]  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | |   {  |   }  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_FNLAYER] = LAYOUT_ortho_4x12_wrapper(
  _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS,
  _______, __________________LONG_FUNC_LEFT___________________,   KC_UNDS, KC_EQL,  KC_LBRC, KC_RBRC, KC_QUOT,
  _______, __________________LONG_FUNC_RIGHT__________________,S(KC_NUHS),S(KC_NUBS),KC_LCBR, KC_RCBR, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),
 
/* Num Layer
 * ,-----------------------------------------------------------------------------------.
 * |      |   Q  |  Up  |   4  |      |      |   7  |   8  |   9  |   -  |   +  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  Lt  |  Dn  |  Rt  |      |      |   4  |   5  |   6  |   *  |   :  |  ENT |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   Z  |   X  |   C  |   V  |      |   1  |   2  |   3  |   .  |   /  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |   0  |   .  | Exit | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMLAY] = LAYOUT_ortho_4x12_wrapper(
  _______, KC_Q,    KC_UP,   KC_H,     XXXXXXX, XXXXXXX,  KC_P7,   KC_P8,  KC_P9,   KC_MINS,   KC_PLUS,  KC_BSPC,
  _______, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, XXXXXXX,  KC_P4,  KC_P5,  KC_P6,   KC_PAST, KC_COLN,  KC_ENT,
  _______, KC_Z,    KC_X,    KC_C,     KC_V,    XXXXXXX,  KC_P1,  KC_P2,  KC_P3,   KC_PDOT, KC_PSLS,  _______,
  _______, _______, _______, _______, _______, _______,   KC_P0,  KC_PDOT, _______, _______, KC_NUM,  KC_MPLY
),
 
/* Mouse Layer (semi-col)
 * ,-----------------------------------------------------------------------------------.
 * | ACCL0| ACCL1| ACCL2|Email |Email2| Home | Wh_Up| WHL_L| M_Up | WHL_R|PASS| Meta |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |RT Q6H| End  | Wh_Dn| M_Lft| M_Dn | M_Rt |      | DayRn|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      | BTN2 | BTN3 | BTN4 | BTN5 |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |     BTN1    |      |      |      | Citx |      |
 * `-----------------------------------------------------------------------------------'
 */
 
[_MOUSECURSOR] = LAYOUT_ortho_4x12_wrapper(
  KC_ACL0, KC_ACL1, KC_ACL2, M_EMAIL,M_EMAIL2, KC_HOME, KC_PGUP, KC_WH_L, KC_MS_U, KC_WH_R, P_MPASS, P_META,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, O_RTQ6H, KC_END , KC_PGDN, KC_MS_L, KC_MS_D, KC_MS_R, _______, O_DAYRN,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, KC_BTN2, KC_BTN3, KC_BTN4, KC_BTN5, _______, _______,
  _______, _______, _______, _______, _______, KC_BTN1, KC_BTN1, _______, _______, _______, P_CITRIX, O_AUTODC
),
 
/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * | Reset|RGB TG|RGB ST|RGBH -|RGBH +|RGBS -|RGBS +|RGBV -|RGBV +|      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|      |      |      |      | BL + |BL ST |BL TG |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_ortho_4x12_wrapper(
  DFU, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, KC_DEL,
  _______, MAGIC_TOGGLE_NKRO, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK, DVORAK,  PLOVER,  _______,
  _______, AU_PREV, AU_NEXT, MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, BL_DOWN,BL_UP,  BL_STEP, BL_TOGG,
  _______, _______, _______, _______, _______, _______, _______, _______, CK_RST, CK_DOWN, CK_UP, CK_TOGG
)
 

};

#ifdef AUDIO_ENABLE

float tone_startup[][2]    = SONG(STARTUP_SOUND);
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);

float tone_goodbye[][2] = SONG(GOODBYE_SOUND);
#endif


void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

//  Helper Functions
void tap(uint16_t keycode){ register_code(keycode); unregister_code(keycode); };


bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_colemak);
        #endif
        persistant_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_dvorak);
        #endif
        persistant_default_layer_set(1UL<<_DVORAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      } else {
        unregister_code(KC_RSFT);
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(tone_plover);
        #endif
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_plover_gb);
        #endif
        layer_off(_PLOVER);
      }
      return false;
      break;
  }
  return true;
}

void matrix_init_keymap(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
}

#ifdef AUDIO_ENABLE

void startup_user(void)
{
    #ifdef RGB_MATRIX_ENABLE
    rgblight_mode(RGB_MATRIX_CYCLE_ALL);
    #endif //RGB_matrix
    wait_ms(20); // gets rid of tick
    PLAY_SONG(tone_startup);
}

void shutdown_user(void)
{
    PLAY_SONG(tone_goodbye);
    wait_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif

