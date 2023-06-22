#include QMK_KEYBOARD_H

enum layer_number {
  _IONIAN = 0,
  _DORIAN,
  _PHRYGIAN,
  _LYDIAN,
  _MIXOLYDIAN,
  _AEOLIAN,
  _LOCRIAN,
  _MENU
};

enum custom_keycodes {
  IONIAN = SAFE_RANGE,
  DORIAN,
  PHRYGIAN,
  LYDIAN,
  MIXOLYDIAN,
  AEOLIAN,
  LOCRIAN,
};

#define MENU MO(_MENU)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_IONIAN] = LAYOUT_ortho_3x10(
    MI_C1,  MI_F1,  MI_B1,  MI_E2,  MI_A2,  MI_D3,  MI_G3,  MI_C4,  MI_OCTD, MI_OCTU,
    MI_D1,  MI_G1,  MI_C2,  MI_F2,  MI_B2,  MI_E3,  MI_A3,  MI_D4,  MI_TRSD, MI_TRSU,
    MI_E1,  MI_A1,  MI_D2,  MI_G2,  MI_C3,  MI_F3,  MI_B3,  MI_E4,  MI_SUST, MENU
  ),

  [_DORIAN] = LAYOUT_ortho_3x10(
    MI_C1,  MI_F1,  MI_As1, MI_Ds2, MI_A2,  MI_D3,  MI_G3,  MI_C4,  _______, _______,
    MI_D1,  MI_G1,  MI_C2,  MI_F2,  MI_As2, MI_Ds3, MI_A3,  MI_D4,  _______, _______,
    MI_Ds1, MI_A1,  MI_D2,  MI_G2,  MI_C3,  MI_F3,  MI_As3, MI_Ds4, _______, _______
  ),

  [_PHRYGIAN] = LAYOUT_ortho_3x10(
    MI_C1,  MI_F1,  MI_As1, MI_Ds2, MI_Gs2, MI_Cs3, MI_G3,  MI_C4,  _______, _______,
    MI_Cs1, MI_G1,  MI_C2,  MI_F2,  MI_As2, MI_Ds3, MI_Gs3, MI_Cs4, _______, _______,
    MI_Ds1, MI_Gs1, MI_Cs2, MI_G2,  MI_C3,  MI_F3,  MI_As3, MI_Ds4, _______, _______
  ),

  [_LYDIAN] = LAYOUT_ortho_3x10(
    MI_C1,  MI_Fs1, MI_B1,  MI_E2,  MI_A2,  MI_D3,  MI_G3,  MI_C4,  _______, _______,
    MI_D1,  MI_G1,  MI_C2,  MI_Fs2, MI_B2,  MI_E3,  MI_A3,  MI_D4,  _______, _______,
    MI_E1,  MI_A1,  MI_D2,  MI_G2,  MI_C3,  MI_Fs3, MI_B3,  MI_E4,  _______, _______
  ),

  [_MIXOLYDIAN] = LAYOUT_ortho_3x10(
    MI_C1,  MI_F1,  MI_As1, MI_E2,  MI_A2,  MI_D3,  MI_G3,  MI_C4,  _______, _______,
    MI_D1,  MI_G1,  MI_C2,  MI_F2,  MI_As2, MI_E3,  MI_A3,  MI_D4,  _______, _______,
    MI_E1,  MI_A1,  MI_D2,  MI_G2,  MI_C3,  MI_F3,  MI_As3, MI_E4,  _______, _______
  ),

  [_AEOLIAN] = LAYOUT_ortho_3x10(
    MI_C1,  MI_F1,  MI_As1, MI_Ds2, MI_Gs2, MI_D3,  MI_G3,  MI_C4,  _______, _______,
    MI_D1,  MI_G1,  MI_C2,  MI_F2,  MI_As2, MI_Ds3, MI_Gs3, MI_D4,  _______, _______,
    MI_Ds1, MI_Gs1, MI_D2,  MI_G2,  MI_C3,  MI_F3,  MI_As3, MI_Ds4, _______, _______
  ),

  [_LOCRIAN] = LAYOUT_ortho_3x10(
    MI_C1,  MI_F1,  MI_As1, MI_Ds2, MI_Gs2, MI_Cs3, MI_Fs3, MI_C4,  _______, _______,
    MI_Cs1, MI_Fs1, MI_C2,  MI_F2,  MI_As2, MI_Ds3, MI_Gs3, MI_Cs4, _______, _______,
    MI_Ds1, MI_Gs1, MI_Cs2, MI_Fs2, MI_C3,  MI_F3,  MI_As3, MI_Ds4, _______, _______
  ),

  [_MENU] = LAYOUT_ortho_3x10(
    IONIAN,   LYDIAN,     LOCRIAN, _______, _______, _______, _______, _______, _______, _______,
    DORIAN,   MIXOLYDIAN, _______, _______, _______, _______, _______, _______, _______, _______,
    PHRYGIAN, AEOLIAN,    _______, _______, _______, _______, _______, _______, QK_BOOT, _______
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case IONIAN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_IONIAN);
      }
      break;
    case DORIAN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DORIAN);
      }
      break;
    case PHRYGIAN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_PHRYGIAN);
      }
      break;
    case LYDIAN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_LYDIAN);
      }
      break;
    case MIXOLYDIAN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_MIXOLYDIAN);
      }
      break;
    case AEOLIAN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_AEOLIAN);
      }
      break;
    case LOCRIAN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_LOCRIAN);
      }
      break;
  }
  return true;
}
