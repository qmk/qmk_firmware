// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------------------------------------------------.
   * | `    |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Shift |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Brite| Ctrl | Alt  | Cmd  |Lower |    Space    |Raise | Enter| Cmd  |  Alt |Ctrl  |
   * `-----------------------------------------------------------------------------------'
   */
  [0] = LAYOUT_ortho_4x12(
      MI_C4, MI_Cs4, MI_D4, MI_Ds4, MI_E4, MI_F4, MI_Fs4, MI_G4, MI_Gs4, MI_A4, MI_As4, MI_B4,
      MI_C3, MI_Cs3, MI_D3, MI_Ds3, MI_E3, MI_F3, MI_Fs3, MI_G3, MI_Gs3, MI_A3, MI_As3, MI_B3,
      MI_C2, MI_Cs2, MI_D2, MI_Ds2, MI_E2, MI_F2, MI_Fs2, MI_G2, MI_Gs2, MI_A2, MI_As2, MI_B2,
      MI_C1, MI_Cs1, MI_D1, MI_Ds1, MI_E1, MI_F1, MI_Fs1, MI_G1, MI_Gs1, MI_A1, MI_As1, MI_B1
  )

};




