#pragma message("users keymap.c")
#include QMK_KEYBOARD_H
#include "bottilabo.h"

#define _STR(X) #X
#define INCLUDEFILE(STR) _STR(STR)
#include "plug.c"

void matrix_init_user(void) {
    matrix_init_local();
    harmonize_init();
    plug_matrix_init_user();
}
void matrix_scan_user(void) {
   matrix_scan_local();
   HARMONIZE_MATRIX_SCAN_USER;
   plug_matrix_scan_user();
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if( ! process_record_local(keycode,record) )
      return false;

  if( ! plug_process_record_user(keycode,record) )
      return false;

  HARMONIZE_PROC_RECORD_USER;
  return true;
}
