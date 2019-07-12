#include QMK_KEYBOARD_H

enum layers {
  _QWERTY,
  _HYPER,
};

#define KC_ KC_TRNS

#define KC_ESCC MT(MOD_LCTL, KC_ESC)
#define KC_RST  RESET
#define KC_BSPH LT(_HYPER, KC_BSPC)
#define KC_ENTS MT(MOD_LSFT, KC_ENT)
// Brightness
#define KC_BRUP KC_PAUS
#define KC_BRDN KC_SLCK

// Used to create a keymap using only KC_ prefixed keys
#ifndef LAYOUT_kc
#define LAYOUT_kc( \
	k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
	k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
	k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, \
	k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b \
	) \
	LAYOUT_ortho_5x12( \
		KC_##k00, KC_##k01, KC_##k02, KC_##k03, KC_##k04, KC_##k05, KC_##k06, KC_##k07, KC_##k08, KC_##k09, KC_##k0a, KC_##k0b, \
		KC_##k10, KC_##k11, KC_##k12, KC_##k13, KC_##k14, KC_##k15, KC_##k16, KC_##k17, KC_##k18, KC_##k19, KC_##k1a, KC_##k1b, \
		KC_##k20, KC_##k21, KC_##k22, KC_##k23, KC_##k24, KC_##k25, KC_##k26, KC_##k27, KC_##k28, KC_##k29, KC_##k2a, KC_##k2b, \
		KC_##k30, KC_##k31, KC_##k32, KC_##k33, KC_##k34, KC_##k35, KC_##k36, KC_##k37, KC_##k38, KC_##k39, KC_##k3a, KC_##k3b, \
		KC_##k40, KC_##k41, KC_##k42, KC_##k43, KC_##k44, KC_##k45, KC_##k46, KC_##k47, KC_##k48, KC_##k49, KC_##k4a, KC_##k4b \
	)
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc( \
  // ,-----------------------------------------------------------------------------------.
       GRV  ,   1  ,   2  ,   3  ,   4  ,   5  ,   6  ,   7  ,   8  ,   9  ,   0  , MINS ,
  // |------+------+------+------+------+------+------+------+------+------+------+------|
       TAB  ,   Q  ,   W  ,   E  ,   R  ,   T  ,   Y  ,   U  ,   I  ,   O  ,   P  , EQL  ,
  // |------+------+------+------+------+------+------+------+------+------+------+------|
       ESCC ,   A  ,   S  ,   D  ,   F  ,   G  ,   H  ,   J  ,   K  ,   L  , SCLN , QUOT ,
  // |------+------+------+------+------+------+------+------+------+------+------+------|
       LSFT ,   Z  ,   X  ,   C  ,   V  ,   B  ,   N  ,   M  , COMM ,  DOT , SLSH , ENTS ,
  // |------+------+------+------+------+------+------+------+------+------+------+------|
            , LCTL , LALT , LGUI , SPC  , SPC  , BSPC , BSPH , LEFT , DOWN ,  UP  , RGHT
  // `---------------------------------------------------+-------------------------------'
  ), //                                                  |
  //                                                     |
  [_HYPER] = LAYOUT_kc( /*                               V  */ \
  // ,-----------------------------------------------------------------------------------.
        RST ,  F1  ,  F2  ,  F3  ,  F4  ,  F5  ,  F6  ,  F7  ,  F8  , LBRC , RBRC ,      ,
  // |------+------+------+------+------+------+------+------+------+------+------+------|
            ,      ,      , PGUP ,      ,      ,      ,      ,  UP  , LCBR , RCBR , BSLS ,
  // |------+------+------+------+------+------+------+------+------+------+------+------|
            ,      , HOME , PGDN , END  ,      , MINS , LEFT , DOWN , RGHT ,      , PIPE ,
  // |------+------+------+------+------+------+------+------+------+------+------+------|
            ,      ,      ,      ,      ,      ,      ,      ,      , BRDN , BRUP ,      ,
  // |------+------+------+------+------+------+------+------+------+------+------+------|
            ,      ,      ,      ,      ,      ,      ,      , MUTE , VOLD , VOLU , MPLY
  // `-----------------------------------------------------------------------------------'
  ),
};
