// in keyboard.c
#include my_keyboard_name.h

// You could technically add more layers if 160 keys are not enough
// This is me trying to make a normal-ish layout in the middle of the keyboard, leaving the rest unassigned
// Going to need a wiiiide editor window for this to look readable
// Available keycodes are at https://github.com/qmk/qmk_firmware/blob/master/docs/keycodes.md
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(     NO,         NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO, 
    NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO,   NO, 

    NO,   NO,   NO,   NO,   NO,   ESC,        NO,         NO,         NO,   NO,   NO,   NO,   NO,         BKSP, NO,   NO,         NO,   NO,   NO,   NO, 
    NO,   NO,   NO,   NO,   NO,   TAB,  Q,    W,    E,    R,    T,    Y,    U,    I,    O,    P,    LBRC, RBRC, NO,   NO,   NO,   NO,   NO,   NO,   NO, 
    NO,   NO,   NO,   NO,   NO,   CAPS, A,    S,    D,    F,    G,    H,    J,    K,    L,    SCLN, QUOT, NO,   ENT,  NO,   NO,   NO,   NO,   NO,   NO,  
    NO,   NO,   NO,   NO,   NO,   LSFT, NO,   Z,    X,    C,    V,    B,    N,    M,    COMM, DOT,  SLSH, NO,   RSFT, NO,   NO,   NO,   NO,   NO,   NO,  
    NO,         NO,   NO,   NO,   LCTL, LWIN,             LALT,             SPC,        RALT, NO,   APP,  RCTL, NO,         NO,   NO,   NO
  );


