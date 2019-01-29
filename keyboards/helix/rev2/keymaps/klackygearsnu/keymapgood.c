#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _DVORAK = 0,
    _SYMB,
    _NUMB,
    _ADJUST
};

enum custom_keycodes {

  DVORAK = SAFE_RANGE,
  SYMB,
  NUMB,
  ADJUST,
  BACKLIT,
  EISU,
  KANA,
  RGBRST,
  DYNAMIC_MACRO_RANGE,
};

 #include "dynamic_macro.h"

enum macro_keycodes {
  KC_SAMPLEMACRO,
};


enum {
  TD_MCROTOG,
  TD_MCROTG2,
  TD_BTK,
  TD_TDE,
  TD_LPRN,
  TD_RPRN,
  TD_MIN,
  TD_USC,
  TD_CMWN,
  TD_ATSH,
  TD_PSTI,
  TD_PTSP,
  TD_FNDR,
  TD_CCPY,
  TD_DDEL,
  TD_ACCW,
  TD_CAPESC,
  TD_DTEX,
  TD_COMQUES,
  TD_MINPLS,
  TD_DIVMLT,
  TD_DOTEQL,
  TD_LSHSYM,
  TD_RSHSYM,
  TD_SCNSP,
  TD_MCCCPY,
  TD_MCPSTIN,
};


#define KC________ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_KANJI KC_GRV
#define KC_DVORAK DVORAK
#define KC_SYMB SYMB
#define KC_NUMB NUMB
#define KC_ADJUST ADJUST
#define KC_BACKLIT BACKLIT
#define KC_EISU EISU
#define KC_KATNA KANA
#define KC_RESET RESET
#define KC_AU_ON AU_ON
#define KC_AU_OFF AU_OFF
#define KC_AG_NORM AG_NORM
#define KC_KSWP  AG_SWAP



#define KC_SYMB SYMB
#define KC_NUMB NUMB
#define KC_MNMB MNMB
#define KC_MACD TO(_MDVK)
#define KC_MCNB TO(_MNMB)

#define KC_RST   RESET

#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LMOD  RGB_MOD
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LSPI  RGB_SPI
#define KC_LSPD  RGB_SPD
#define KC_LRMOD RGB_RMOD

#define KC_SPSY LT(_SYMB,KC_SPC)
#define KC_BSNB LT(_NUMB,KC_BSPC)
#define KC_TBNB LT(_NUMB,KC_TAB)
#define KC_ENSY LT(_SYMB,KC_ENT)
#define KC_MBNB LT(_MNMB,KC_BSPC)
#define KC_MTNB LT(_MNMB,KC_TAB)

#define KC_MCRTG TD(TD_MCROTOG)
#define KC_MCTG2 TD(TD_MCROTG2)
#define KC_CMWN TD(TD_CMWN)
#define KC_ATSH TD(TD_ATSH)
#define KC_PSTI TD(TD_PSTI)
#define KC_PTSP TD(TD_PTSP)
#define KC_FNDR TD(TD_FNDR)
#define KC_CCPY TD(TD_CCPY)
#define KC_DDEL TD(TD_DDEL)
#define KC_ACCW TD(TD_ACCW)
#define KC_CAPES TD(TD_CAPES)
#define KC_DTEX TD(TD_DTEX)
#define KC_COMQUES TD(TD_COMQUES)
#define KC_MINPLS TD(TD_MINPLS)
#define KC_DIVMLT TD(TD_DIVMLT)
#define KC_DOTEQL TD(TD_DOTEQL)
#define KC_LSHSYM TD(TD_LSHSYM)
#define KC_RSHSYM TD(TD_RSHSYM)
#define KC_SCNSP TD(TD_SCNSP)
#define KC_MCCPY TD(TD_MCCCPY)
#define KC_MCPIN TD(TD_MCPSTIN)

#define KC_WNL  LGUI(KC_L)
#define KC_MCL  LCTL(LALT(KC_Q))
#define KC_WNSC MT(MOD_LGUI,KC_SCLN)
#define KC_CSCN MT(MOD_LCTL,KC_SCLN)
#define KC_ALTQ MT(MOD_LALT,KC_Q)
#define KC_CTLJ MT(MOD_LCTL,KC_J)
#define KC_GUIJ MT(MOD_LGUI,KC_J)
#define KC_SHFK MT(MOD_LSFT,KC_K)
#define KC_SHFM MT(MOD_LSFT,KC_M)
#define KC_CTLW MT(MOD_LCTL,KC_W)
#define KC_GUIW MT(MOD_LGUI,KC_W)
#define KC_ALTV MT(MOD_LALT,KC_V)
#define KC_MDAZ LT(_ADJUST,KC_Z)
#define KC_CTLA LCTL(KC_A)
#define KC_CTL2 MT(MOD_LCTL,KC_2)
#define KC_ALT3 MT(MOD_LALT,KC_3)
#define KC_CSTC C_S_T(KC_COLN)

#define KC_MRC1 DYN_REC_START1
#define KC_MPL1 DYN_MACRO_PLAY1
#define KC_MSP DYN_REC_STOP

#define KC_KNRM  AG_NORM
#define KC_GUAP  LALT_T(KC_APP)

///Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)



#if HELIX_ROWS == 5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {



  [_DVORAK] = LAYOUT_kc( \
      LRMOD,   _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
      ESC,     QUOT,    COMQUES, DTEX,    P,       Y,                         F,       G,       C,       R,       L,       _______, \
      LSFT,    A,       O,       E,       U,       I,                         D,       H,       T,       N,       S,       RSFT, \
      LSFT,    CSCN,    ALTQ,    GUIJ,    K,       X,       MCTG2,  MCRTG,    B,       M,       GUIW,    ALTV,    MDAZ,    RSFT, \
      ADJUST,  ENT,     LALT,    ENT,     SPSY,    SPSY,    BSNB,   TBNB,     ENSY,    ENSY,    LEFT,    DOWN,    UP,      RGHT \
      ),



  [_SYMB] = LAYOUT_kc( \
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
      _______, BSLS,    AT,      HASH,    DLR,     PERC,                      _______, F9,      F10,     F11,     F12,     _______, \
      _______, PLUS,    MINS,    ASTR,    SLSH,    EQL,                       _______, F5,      F6,      F7,      F8,      _______, \
      _______, LBRC,    RBRC,    LPRN,    RPRN,    AMPR,    _______, _______, GRV,     F1,      F2,      F3,      F4,      _______, \
      _______, _______, _______, _______, SPC,     DEL,     _______, _______, CAPS,    _______, _______, _______, _______, _______ \
      ),


  [_NUMB] = LAYOUT_kc( \
      GRV,     1,       2,       3,       4,       5,                         6,       7,       8,       9,       0,       _______, \
      _______, PGUP,    PGDN,    HOME,    END,     FNDR,                      MINPLS,  7,       8,       9,       COLN,    _______, \
      _______, LEFT,    UP,      DOWN,    RIGHT,   _______,                   DIVMLT,  4,       5,       6,       CSTC,    _______, \
      _______, _______, CTLA,    MCCPY,   MCPIN,   DEL,     _______, _______, DOTEQL,  1,       2,       ALT3,    RWIN,    _______, \
      _______, _______, _______, _______, SPC,     BSPC,    _______, _______, _______, 0,       0,       _______, _______, _______ \
      ),


  [_ADJUST] =  LAYOUT_kc( \
      _______, _______, _______, _______, _______, _______,                   LRST,    _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______,                   _______, LHUI,    LSAI,    LVAI,    LSPI,    _______, \
      _______, _______, _______, _______, _______, _______,                   LRMOD,   LHUD,    LSAD,    LVAD,    LSPD,    _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, MPLY,    MUTE,    VOLD,    VOLU,    _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
      )
};

#else
#error "undefined keymaps"
#endif


#ifdef AUDIO_ENABLE

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif




void macroTogKey(qk_tap_dance_state_t *state, void *user_data) {
  keyrecord_t kr;

  if (state->count == 1)
  {
    kr.event.pressed = false;
    process_record_dynamic_macro( DYN_MACRO_PLAY1, &kr );
  }
  else if (state->count == 2)
  {
    kr.event.pressed = true;
    process_record_dynamic_macro( DYN_REC_STOP, &kr );
  }
  else if (state->count == 3)
  {
    kr.event.pressed = false;
    process_record_dynamic_macro( DYN_REC_START1, &kr );
  }
}

void macroTogKey2(qk_tap_dance_state_t *state, void *user_data) {
  keyrecord_t kr;

  if (state->count == 1)
  {
    kr.event.pressed = false;
    process_record_dynamic_macro( DYN_MACRO_PLAY2, &kr );
  }
  else if (state->count == 2)
  {
    kr.event.pressed = true;
    process_record_dynamic_macro( DYN_REC_STOP, &kr );
  }
  else if (state->count == 3)
  {
    kr.event.pressed = false;
    process_record_dynamic_macro( DYN_REC_START2, &kr );
  }
}



void pstinsrt(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LALT);
    register_code(KC_I);
    unregister_code(KC_I);
    register_code(KC_E);
    unregister_code(KC_E);
    unregister_code(KC_LALT);
  }
  else
  {
    register_code(KC_LCTL);
    register_code(KC_V);
    unregister_code(KC_V);
    unregister_code(KC_LCTL);
  }
  reset_tap_dance(state);
}

void ccopy(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LCTL);
    register_code(KC_X);
    unregister_code(KC_X);
    unregister_code(KC_LCTL);
  }
  else
  {
    register_code(KC_LCTL);
    register_code(KC_C);
    unregister_code(KC_C);
    unregister_code(KC_LCTL);
  }
  reset_tap_dance(state);
}

void pstspecial(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LALT);
    register_code(KC_E);
    unregister_code(KC_E);
    register_code(KC_S);
    unregister_code(KC_S);
    unregister_code(KC_LALT);
    register_code(KC_V);
    unregister_code(KC_V);
  }
  else
  {
    register_code(KC_LALT);
    register_code(KC_E);
    unregister_code(KC_E);
    register_code(KC_S);
    unregister_code(KC_S);
    unregister_code(KC_LALT);
    register_code(KC_T);
    unregister_code(KC_T);
  }
  reset_tap_dance(state);
}

void deldel(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LALT);
    register_code(KC_E);
    unregister_code(KC_E);
    register_code(KC_D);
    unregister_code(KC_D);
    unregister_code(KC_LALT);
  }
  else
  {
    register_code(KC_DEL);
    unregister_code(KC_DEL);
  }
  reset_tap_dance(state);
}

void findreplace(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LCTL);
    register_code(KC_H);
    unregister_code(KC_H);
    unregister_code(KC_LCTL);
  }
  else
  {
    register_code(KC_LCTL);
    register_code(KC_F);
    unregister_code(KC_F);
    unregister_code(KC_LCTL);
  }
  reset_tap_dance(state);
}

void cyclawin(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LCTL);
    register_code(KC_LSFT);
    register_code(KC_F6);
    unregister_code(KC_F6);
    unregister_code(KC_LSFT);
    unregister_code(KC_LCTL);
  }
  else
  {
    register_code(KC_LCTL);
    register_code(KC_F6);
    unregister_code(KC_F6);
    unregister_code(KC_LCTL);
  }
  reset_tap_dance(state);
}


void SCRNSNP(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LALT);
    register_code(KC_PSCR);
    unregister_code(KC_PSCR);
    unregister_code(KC_LALT);
  }
  else
  {
    SEND_STRING(SS_TAP(X_LGUI));
    SEND_STRING("SN");
    register_code(KC_LCTL);
    register_code(KC_N);
    unregister_code(KC_N);
    unregister_code(KC_LCTL);
  }
  reset_tap_dance(state);
}


void mcccpy(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LGUI);
    register_code(KC_X);
    unregister_code(KC_X);
    unregister_code(KC_LGUI);
  }
  else
  {
    register_code(KC_LGUI);
    register_code(KC_C);
    unregister_code(KC_C);
    unregister_code(KC_LGUI);
  }
  reset_tap_dance(state);
}

void mcpstin(qk_tap_dance_state_t *state, void *user_data)
{
  if (state->count > 1)
  {
    register_code(KC_LGUI);
    register_code(KC_I);
    unregister_code(KC_I);
    unregister_code(KC_LGUI);
  }
  else
  {
    register_code(KC_LGUI);
    register_code(KC_V);
    unregister_code(KC_V);
    unregister_code(KC_LGUI);
  }
  reset_tap_dance(state);
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
// Other declarations would go here, separated by commas, if you have them
  [TD_MCROTOG]  = ACTION_TAP_DANCE_FN(macroTogKey),
  [TD_MCROTG2] = ACTION_TAP_DANCE_FN(macroTogKey2),
  [TD_PSTI] = ACTION_TAP_DANCE_FN(pstinsrt),
  [TD_PTSP] = ACTION_TAP_DANCE_FN(pstspecial),
  [TD_FNDR] = ACTION_TAP_DANCE_FN(findreplace),
  [TD_CCPY] = ACTION_TAP_DANCE_FN(ccopy),
  [TD_DDEL] = ACTION_TAP_DANCE_FN(deldel),
  [TD_ACCW] = ACTION_TAP_DANCE_FN(cyclawin),
  [TD_CAPESC] = ACTION_TAP_DANCE_DOUBLE(KC_ESC,KC_CAPS),
  [TD_DTEX] = ACTION_TAP_DANCE_DOUBLE(KC_DOT,KC_EXLM),
  [TD_COMQUES] = ACTION_TAP_DANCE_DOUBLE(KC_COMM,KC_QUES),
  [TD_MINPLS] = ACTION_TAP_DANCE_DOUBLE(KC_PMNS,KC_PPLS),
  [TD_DIVMLT] = ACTION_TAP_DANCE_DOUBLE(KC_PSLS,KC_PAST),
  [TD_DOTEQL] = ACTION_TAP_DANCE_DOUBLE(KC_DOT,KC_EQL),
  [TD_SCNSP]  = ACTION_TAP_DANCE_FN(SCRNSNP),
  [TD_MCCCPY] = ACTION_TAP_DANCE_FN(mcccpy),
  [TD_MCPSTIN] = ACTION_TAP_DANCE_FN(mcpstin)
};


// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      //rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

 if (!process_record_dynamic_macro(keycode, record)) {
        return false;
    }

  switch (keycode) {

      return false;
      break;

    case DVORAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_dvorak);
        #endif
        persistent_default_layer_set(1UL<<_DVORAK);
      }
      return false;
      break;
    case SYMB:
      if (record->event.pressed) {
          //not sure how to have keyboard check mode and set it to a variable, so my work around
          //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(RGBLIGHT_MODE_SNAKE + 1);
          #endif
        }
        layer_on(_SYMB);
        update_tri_layer_RGB(_SYMB, _NUMB, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
        #endif
        TOG_STATUS = false;
        layer_off(_SYMB);
        update_tri_layer_RGB(_SYMB, _NUMB, _ADJUST);
      }
      return false;
      break;
    case NUMB:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(RGBLIGHT_MODE_SNAKE);
          #endif
        }
        layer_on(_NUMB);
        update_tri_layer_RGB(_SYMB, _NUMB, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        #endif
        layer_off(_NUMB);
        TOG_STATUS = false;
        update_tri_layer_RGB(_SYMB, _NUMB, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case EISU:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG2);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG2);
      }
      return false;
      break;
    case KANA:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG1);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG1);
      }
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}


#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
}

void shutdown_user()
{
    _delay_ms(150);
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


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// hook point for 'led_test' keymap
//   'default' keymap's led_test_init() is empty function, do nothing
//   'led_test' keymap's led_test_init() force rgblight_mode_noeeprom(RGBLIGHT_MODE_RGB_TEST);
__attribute__ ((weak))
void led_test_init(void) {}


void matrix_scan_user(void) {
  //  rgblight_setrgb_at(0,255,0,0);
  //  rgblight_setrgb_at(0,255,0,1);
  //  rgblight_setrgb_at(0,255,0,2);
  //  rgblight_setrgb_at(0,255,0,3);
  //  rgblight_setrgb_at(0,255,0,4);
  //  rgblight_setrgb_at(0,255,0,5);
  //    rgblight_setrgb_at(0,0,255,6);
  //    rgblight_setrgb_at(10,0,255,17);
  //    rgblight_setrgb_at(10,0,230,18);
  //    rgblight_setrgb_at(20,0,220,31);

     led_test_init();
     iota_gfx_task();  // this is what updates the display continuously

}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_SYMB (1<<_SYMB)
#define L_NUMB (1<<_NUMB)
#define L_ADJUST (1<<_ADJUST)
#define L_ADJUST_TRI (L_ADJUST|L_NUMB|L_SYMB)

static void render_logo(struct CharacterMatrix *matrix) {

  static char logo[]={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write(matrix, logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}



void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
  static char logo[][2][3]={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
  if(keymap_config.swap_lalt_lgui==false){
    matrix_write(matrix, logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[0][1]);
  }else{
    matrix_write(matrix, logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[1][1]);
  }

  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[40];
  snprintf(buf,sizeof(buf), "Undef-%ld", layer_state);
  matrix_write_P(matrix, PSTR("\nLayer: "));
    switch (layer_state) {
        case L_BASE:
           matrix_write_P(matrix, PSTR("Dvorak"));
           break;
        case L_NUMB:
           matrix_write_P(matrix, PSTR("Numeric"));
           break;
        case L_SYMB:
           matrix_write_P(matrix, PSTR("Punctuation"));
           break;
        case L_ADJUST:
        case L_ADJUST_TRI:
           matrix_write_P(matrix, PSTR("Adjust"));
           break;
        default:
           matrix_write(matrix, buf);
    }

  // Host Keyboard LED Status
  char led[40];
    snprintf(led, sizeof(led), "\n%s  %s  %s",
            (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
            (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
            (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  matrix_write(matrix, led);
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif
