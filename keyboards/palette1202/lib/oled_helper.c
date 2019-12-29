#ifdef OLED_DRIVER_ENABLE
#include QMK_KEYBOARD_H
#include <stdio.h>
#include <string.h>

// returns character cord of the logo by line number
char *read_logo(int row) {
  static char logoLines[][18] = {
    { 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0},
    { 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 0xa0, 0xa1, 0},
    { 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0},
    { 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf, 0xc0, 0xc1, 0xc2, 0xc3, 0}
  };
  return logoLines[row];
}

void render_row(int row, const char* status) {
  // reset cursor position
  oled_set_cursor(0, row);
  // read logo charcode
  char * logoLine = read_logo(row);
  // copy logo into buffer
  char writeLine[22];
  strcpy(writeLine, logoLine);
  // combine status string with logo
  strcat(writeLine, status);
  // write the line to OLED
  oled_write(writeLine, false);
}
#endif


char keylog_str[5] = {'0x00'};
/*
  R(0x18): Return
  E(0x19): Esc
  B(0x20): BackSpace
  T(0x18): Tab
   (0x19): Space
*/
const char charMatrix[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2',
    '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', ' ', '-', '=', '[',
    ']', '\\','#', ';', '\'','`', ',', '.', '/', ' ', ' ', ' '};
void registerKeylog(uint16_t keycode, keyrecord_t *record) {
  if (keycode < 60) {
    keylog_str[4] = charMatrix[keycode];
  } else if (keycode == 0xE0 || keycode == 0xE3) {
    // CTRL / CMD
    keylog_str[3] = 0x01;
  } else if (keycode == 0xE1) {
    // SHIFT
    // pressedChar = 0x02;
  } else if (keycode == 0xE2) {
    // ALT
    // pressedChar = 0x03;
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%c", pressedChar);

  // update keylogs
  if (keylogs_str_idx == sizeof(keylogs_str) - 1) {
  }
}

const char *read_keylog(void) {
  return keylog_str;
}
