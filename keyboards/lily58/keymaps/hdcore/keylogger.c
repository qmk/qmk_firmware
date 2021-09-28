#include <stdio.h>
#include <string.h>
#include "action.h"
#include "lily58.h"

char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ';', '\'', ' ', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
  if (keycode < 60) {
    name = code_to_name[keycode];
    // if (keycode == 40) {
      // name = "Enter";
    // } else {
      // if (keycode == 41) {
        // name = "Esc";
      // } else {
        // if (keycode == 42) {
          // name = "Bksp";
        // } else {
          // if (keycode == 43) {
            // name = "Tab";
          // } else {
            // name = code_to_name[keycode];
          // }
        // }
      // }
    // }
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%c", name);
}

const char *read_keylog(void) {
  return keylog_str;
}
