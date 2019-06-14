#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

enum layer_number {
  _BASE = 0,
  _IONIAN,
  _DORIAN,
  _PHRYGIAN,
  _LYDIAN,
  _MIXOLYDIAN,
  _AEOLIAN,
  _LOCRIAN,
  _MENU
};

enum custom_keycodes {
  BASE = SAFE_RANGE,
  IONIAN,
  DORIAN,
  PHRYGIAN,
  LYDIAN,
  MIXOLYDIAN,
  AEOLIAN,
  LOCRIAN,
};

#define MENU MO(_MENU)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Basic controls like octave and transpose
  [_BASE] = LAYOUT_ortho_3x10(
    _______, _______, _______, _______, _______, _______, _______, _______, MI_OCTD,  MI_OCTU,
    _______, _______, _______, _______, _______, _______, _______, _______, MI_TRNSD, MI_TRNSU,
    _______, _______, _______, _______, _______, _______, _______, _______, MI_SUS,   MENU
  ),

  [_IONIAN] = LAYOUT_ortho_3x10(
    MI_C_1,  MI_F_1,  MI_B_1,  MI_E_2,  MI_A_2,  MI_D_3,  MI_G_3,  MI_C_4,  _______, _______,
    MI_D_1,  MI_G_1,  MI_C_2,  MI_F_2,  MI_B_2,  MI_E_3,  MI_A_3,  MI_D_4,  _______, _______,
    MI_E_1,  MI_A_1,  MI_D_2,  MI_G_2,  MI_C_3,  MI_F_3,  MI_B_3,  MI_E_4,  _______, _______
  ),

  [_DORIAN] = LAYOUT_ortho_3x10(
    MI_C_1,  MI_F_1,  MI_As_1, MI_Ds_2, MI_A_2,  MI_D_3,  MI_G_3,  MI_C_4,  _______, _______,
    MI_D_1,  MI_G_1,  MI_C_2,  MI_F_2,  MI_As_2, MI_Ds_3, MI_A_3,  MI_D_4,  _______, _______,
    MI_Ds_1, MI_A_1,  MI_D_2,  MI_G_2,  MI_C_3,  MI_F_3,  MI_As_3, MI_Ds_4, _______, _______
  ),

  [_PHRYGIAN] = LAYOUT_ortho_3x10(
    MI_C_1,  MI_F_1,  MI_As_1, MI_Ds_2, MI_Gs_2, MI_Cs_3, MI_G_3,  MI_C_4,  _______, _______,
    MI_Cs_1, MI_G_1,  MI_C_2,  MI_F_2,  MI_As_2, MI_Ds_3, MI_Gs_3, MI_Cs_4, _______, _______,
    MI_Ds_1, MI_Gs_1, MI_Cs_2, MI_G_2,  MI_C_3,  MI_F_3,  MI_As_3, MI_Ds_4, _______, _______
  ),

  [_LYDIAN] = LAYOUT_ortho_3x10(
    MI_C_1,  MI_Fs_1, MI_B_1,  MI_E_2,  MI_A_2,  MI_D_3,  MI_G_3,  MI_C_4,  _______, _______,
    MI_D_1,  MI_G_1,  MI_C_2,  MI_Fs_2, MI_B_2,  MI_E_3,  MI_A_3,  MI_D_4,  _______, _______,
    MI_E_1,  MI_A_1,  MI_D_2,  MI_G_2,  MI_C_3,  MI_Fs_3, MI_B_3,  MI_E_4,  _______, _______
  ),

  [_MIXOLYDIAN] = LAYOUT_ortho_3x10(
    MI_C_1,  MI_F_1,  MI_As_1, MI_E_2,  MI_A_2,  MI_D_3,  MI_G_3,  MI_C_4,  _______, _______,
    MI_D_1,  MI_G_1,  MI_C_2,  MI_F_2,  MI_As_2, MI_E_3,  MI_A_3,  MI_D_4,  _______, _______,
    MI_E_1,  MI_A_1,  MI_D_2,  MI_G_2,  MI_C_3,  MI_F_3,  MI_As_3, MI_E_4,  _______, _______
  ),

  [_AEOLIAN] = LAYOUT_ortho_3x10(
    MI_C_1,  MI_F_1,  MI_As_1, MI_Ds_2, MI_Gs_2, MI_D_3,  MI_G_3,  MI_C_4,  _______, _______,
    MI_D_1,  MI_G_1,  MI_C_2,  MI_F_2,  MI_As_2, MI_Ds_3, MI_Gs_3, MI_D_4,  _______, _______,
    MI_Ds_1, MI_Gs_1, MI_D_2,  MI_G_2,  MI_C_3,  MI_F_3,  MI_As_3, MI_Ds_4, _______, _______
  ),

  [_LOCRIAN] = LAYOUT_ortho_3x10(
    MI_C_1,  MI_F_1,  MI_As_1, MI_Ds_2, MI_Gs_2, MI_Cs_3, MI_Fs_3, MI_C_4,  _______, _______,
    MI_Cs_1, MI_Fs_1, MI_C_2,  MI_F_2,  MI_As_2, MI_Ds_3, MI_Gs_3, MI_Cs_4, _______, _______,
    MI_Ds_1, MI_Gs_1, MI_Cs_2, MI_Fs_2, MI_C_3,  MI_F_3,  MI_As_3, MI_Ds_4, _______, _______
  ),

  [_MENU] = LAYOUT_ortho_3x10(
    IONIAN,   LYDIAN,     LOCRIAN, _______, _______, _______, _______, _______, _______, _______,
    DORIAN,   MIXOLYDIAN, _______, _______, _______, _______, _______, _______, _______, _______,
    PHRYGIAN, AEOLIAN,    _______, _______, _______, _______, _______, _______, RESET,   _______
  )
};

void persistent_default_layer_set(uint16_t default_layer){
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case IONIAN:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_IONIAN);
      }
      return false;
      break;
    case DORIAN:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_DORIAN);
      }
      return false;
      break;
    case PHRYGIAN:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_PHRYGIAN);
      }
      return false;
      break;
    case LYDIAN:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_LYDIAN);
      }
      return false;
      break;
    case MIXOLYDIAN:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_MIXOLYDIAN);
      }
      return false;
      break;
    case AEOLIAN:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_AEOLIAN);
      }
      return false;
      break;
    case LOCRIAN:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_LOCRIAN);
      }
      return false;
      break;
  }
  return true;
}
