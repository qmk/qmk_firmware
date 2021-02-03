#include QMK_KEYBOARD_H

#define _DVORAK 0
#define _QWERTY 1
#define _FN1 2
#define _MOUSE 3

enum custom_keycodes {
  DVORAK = SAFE_RANGE,
  QWERTY,
};

#define KC_ KC_TRNS

#define KC_DVOR DVORAK
#define KC_QWER QWERTY
#define KC_FN1 MO(_FN1)

// Tap-Hold keys (QWERTY)
#define KC_S_C MT(MOD_LCTL, KC_S)
#define KC_D_A MT(MOD_LALT, KC_D)
#define KC_F_G MT(MOD_LGUI, KC_F)
#define KC_J_G MT(MOD_RGUI, KC_J)
#define KC_K_A MT(MOD_RALT, KC_K)
#define KC_L_C MT(MOD_RCTL, KC_L)

// Tap-Hold keys (Dvorak)
#define KC_O_C MT(MOD_LCTL, KC_O)
#define KC_E_A MT(MOD_LALT, KC_E)
#define KC_U_G MT(MOD_LGUI, KC_U)
#define KC_H_G MT(MOD_RGUI, KC_H)
#define KC_T_A MT(MOD_RALT, KC_T)
#define KC_N_C MT(MOD_RCTL, KC_N)

#define KC_G_A LGUI(KC_A)
#define KC_G_C LGUI(KC_C)
#define KC_G_V LGUI(KC_V)
#define KC_G_X LGUI(KC_X)
#define KC_G_Z LGUI(KC_Z)
#define KC_G_BL LGUI(KC_BSLS)
#define KC_G_TB LGUI(KC_TAB)
#define KC_G_SP LGUI(KC_SPC)

#define KC_ENTM LT(_MOUSE, KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
     DVOR,ESC , 1  , 2  , 3  , 4  , 5  ,      6  , 7  , 8  , 9  , 0  ,MINS,PGUP,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     G_A ,TAB , Q  , W  , E  , R  , T  ,      Y  , U  , I  , O  , P  ,BSLS,PGDN,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     G_X ,CAPS, A  ,S_C ,D_A ,F_G , G  ,      H  ,J_G ,K_A ,L_C ,SCLN,QUOT, UP ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     G_C ,LSFT, Z  , X  , C  , V  , B  ,      N  , M  ,COMM,DOT ,SLSH,RSFT,DOWN,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     G_V ,FN1 ,G_TB,G_SP,BSPC,SPC ,SPC ,     ENTM,ENTM,G_Z ,GRV ,EQL ,LEFT,RGHT
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),

  [_DVORAK] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
     QWER,ESC , 1  , 2  , 3  , 4  , 5  ,      6  , 7  , 8  , 9  , 0  ,EQL ,PGUP,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     G_A ,TAB ,QUOT,COMM,DOT , P  , Y  ,      F  , G  , C  , R  , L  ,SLSH,PGDN,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     G_X ,CAPS, A  ,O_C ,E_A ,U_G , I  ,      D  ,H_G ,T_A ,N_C , S  ,MINS, UP ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     G_C ,LSFT,SCLN, Q  , J  , K  , X  ,      B  , M  , W  , V  , Z  ,RSFT,DOWN,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     G_V ,FN1 ,G_TB,G_SP,BSPC,SPC ,SPC ,     ENTM,ENTM,G_Z ,GRV ,BSLS,LEFT,RGHT
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),

  [_FN1] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
         ,    , F1 , F2 , F3 , F4 , F5 ,      F6 , F7 , F8 , F9 ,F10 ,F11 ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,EXLM, AT ,LCBR,RCBR,PIPE,         , P7 , P8 , P9 ,ASTR,F12 ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,HASH,DLR ,LPRN,RPRN,GRV ,         , P4 , P5 , P6 ,PLUS,MINS,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,PERC,CIRC,LBRC,RBRC,TILD,     AMPR, P1 , P2 , P3 ,SLSH,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,PDOT, P0 ,EQL ,    ,
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),

  [_MOUSE] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,MS_U,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,MS_L,MS_D,MS_R,    ,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,BTN1,BTN2,    ,         ,    ,    ,    ,    ,    ,
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  )
};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
#endif

void update_rgblight(uint16_t layer) {
  if (layer & (1UL << _DVORAK)) {
    rgblight_sethsv_green();
  } else if (layer & (1UL << _QWERTY)) {
    rgblight_sethsv_goldenrod();
  }
}

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
  #ifdef RGBLIGHT_ENABLE
  update_rgblight(default_layer);
  #endif // RGBLIGHT_ENABLE
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL << _QWERTY);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_dvorak);
        #endif
        persistent_default_layer_set(1UL << _DVORAK);
      }
      return false;
      break;
  }
  return true;
}


void matrix_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
  rgblight_enable();
  uint8_t default_layer = eeconfig_read_default_layer();
  update_rgblight(default_layer);
  #endif
}
