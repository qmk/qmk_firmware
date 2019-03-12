#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
//#ifdef SSD1306OLED
  //#include "ssd1306.h"
//#endif
#include "action_layer.h"
#include "wait.h"


extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;
// Layout for klackygears
// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _DVRK 0
#define _NUMB 1
#define _MDVK 2
#define _MNMB 3
#define _SYMB 4
#define _MDIA 5


enum custom_keycodes {
  DVRK = SAFE_RANGE,
  MDVK,
  NUMB,
  MNMB,
  SYMB,
  MDIA,
  RGBRST,
  DYNAMIC_MACRO_RANGE,
};

#include "dynamic_macro.h"

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

#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_KANJI KC_GRV

#define KC_SYMB SYMB
#define KC_NUMB NUMB
#define KC_MNMB MNMB
#define KC_MACD TO(_MDVK)
#define KC_MCNB TO(_MNMB)

#define KC_RST   RESET

#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LSMOD RGB_SMOD

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
#define KC_MDAZ LT(_MDIA,KC_Z)
#define KC_CTLA LCTL(KC_A)
#define KC_CTL2 MT(MOD_LCTL,KC_2)
#define KC_ALT3 MT(MOD_LALT,KC_3)
#define KC_CSTC C_S_T(KC_COLN)
#define KC_SWP  SH_TT
#define KC_MRC1 DYN_REC_START1
#define KC_MPL1 DYN_MACRO_PLAY1
#define KC_MSP DYN_REC_STOP

#define KC_KNRM  AG_NORM
#define KC_KSWP  AG_SWAP
#define KC_GUAP  LALT_T(KC_APP)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DVRK] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,  QUOT, COMQUES, DTEX,    P,     Y,                      F,     G,     C,     R,     L,   WNL,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     A,     O,     E,     U,     I,                      D,     H,     T,     N,     S,  RSFT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      MCTG2,  WNSC,  ALTQ,  CTLJ,     K,     X,                      B,     M,  CTLW,  ALTV,  MDAZ,  MCRTG,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   SWP,  SPSY,  BSNB,     TBNB,  ENSY,    SWP \
                              //`--------------------'  `--------------------'
  ),

  [_MDVK] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,  QUOT, COMQUES, DTEX,    P,     Y,                      F,     G,     C,     R,     L,   MCL,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,     A,     O,     E,     U,     I,                      D,     H,     T,     N,     S,  RSFT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      MCTG2,  CSCN,  ALTQ,  GUIJ,     K,     X,                      B,     M,  GUIW,  ALTV,  MDAZ,  MCRTG,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   SWP,  SPSY,  MBNB,     MTNB,  ENSY,    SWP \
                              //`--------------------'  `--------------------'
  ),

  [_NUMB] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      _____,  PGUP,  PGDN,  HOME,   END,  FNDR,                 MINPLS,     7,     8,     9, _____, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  LEFT,    UP,  DOWN, RIGHT,  PTSP,                 DIVMLT,     4,     5,     6,  CSTC, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  ACCW,  CTLA,  CCPY,  PSTI,  DDEL,                 DOTEQL,     1,  CTL2,  ALT3,  RWIN, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,    _____, _____,     0 \
                              //`--------------------'  `--------------------'
  ),


  [_MNMB] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      _____,  PGUP,  PGDN,  HOME,   END, XXXXX,                 MINPLS,     7,     8,     9, _____, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  LEFT,    UP,  DOWN, RIGHT, XXXXX,                 DIVMLT,     4,     5,     6,  CSTC, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____, XXXXX, XXXXX, MCCPY, MCPIN,   DEL,                 DOTEQL,     1,  CTL2,  ALT3,  RWIN, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____, _____,    _____, _____,     0 \
                              //`--------------------'  `--------------------'
  ),


  [_SYMB] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
      _____,  BSLS,    AT,  HASH,   DLR,  PERC,                   MACD,    F9,   F10,   F11,   F12, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  PLUS,  MINS,  ASTR,  SLSH,   EQL,                   MCNB,    F5,    F6,    F7,    F8, _____,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      _____,  LBRC,  RBRC,  LPRN,  RPRN,  AMPR,                    GRV,    F1,    F2,    F3,    F4, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____, _____,   DEL,    _____,  CAPS, _____ \
                              //`--------------------'  `--------------------'
  ),

  [_MDIA] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        RST,  XXXXX, XXXXX, XXXXX, XXXXX, ACL2,                  XXXXX,  LRST,  LSAD,  LSAI, XXXXX, _____,\
  //|------+-------+------+------+------+-----|                |------+------+------+------+------+------|
      _____,   MS_L,  MS_U,  MS_D,  MS_R, ACL1,                  XXXXX, LSMOD,  LHUD,  LHUI, XXXXX, _____,\
  //|------+-------+------+------+------+-----|                |------+------+------+------+------+------|
      _____,  LSMOD,  WH_U,  WH_D,  LVAD, ACL0,                  XXXXX,  MUTE,  VOLD,  VOLU, XXXXX, _____,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  _____,  BTN1,  BTN2,    _____, _____, XXXXX \
                              //`--------------------'  `--------------------'
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  
    if (!process_record_dynamic_macro(keycode, record)) {
        return false;
    }

  return true;
}
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



int RGB_current_mode;

// Setting MDIA layer RGB back to default
static inline void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
//#ifdef SSD1306OLED


// When add source files to SRC in rules.mk, you can use functions.
//const char *read_layer_state(void);
//const char *read_logo(void);
//void set_keylog(uint16_t keycode, keyrecord_t *record);
//const char *read_keylog(void);
//const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

#ifdef RGBLIGHT_ENABLE
  const char *read_rgb_info(void);
  #define RENDER_RGB_INFO(m) matrix_write_ln(m, (const char*)read_rgb_info())
#else
  #define RENDER_RGB_INFO(m)
#endif


//void matrix_scan_user(void) {
   //iota_gfx_task();
//}

//static inline void matrix_render_user(struct CharacterMatrix *matrix) {
  //if (is_master) {
    // If you want to change the display of OLED, you need to change here
   // matrix_write_ln(matrix, read_layer_state());
   // matrix_write_ln(matrix, read_keylog());
   // RENDER_RGB_INFO(matrix);
    // matrix_write_ln(matrix, read_keylogs());
    // matrix_write_ln(matrix, read_host_led_state());

    // matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    // matrix_write_ln(matrix, read_timelog());
  //} else {
   // matrix_write(matrix, read_logo());
 // }
//}

//static inline void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
 // if (memcmp(dest->display, source->display, sizeof(dest->display))) {
  //  memcpy(dest->display, source->display, sizeof(dest->display));
   // dest->dirty = true;
 // }
//}

//void iota_gfx_task_user(void) {
  //struct CharacterMatrix matrix;
  //matrix_clear(&matrix);
  //matrix_render_user(&matrix);
  //matrix_update(&display, &matrix);
//}

//#endif

