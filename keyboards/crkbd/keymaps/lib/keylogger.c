#include "crkbd.h"

char keylog[40] = {};
char keylogs[21] = {};
int keylogs_idx = 0;

char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ';', '\'', ' ', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record)
{
  char name = ' ';
  if (keycode < 60)
  {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog, sizeof(keylog), "%dx%d, k%2d : %c",
           record->event.key.row,
           record->event.key.col,
           keycode,
           name);

  // update keylogs
  if (keylogs_idx == sizeof(keylogs) - 1)
  {
    keylogs_idx = 0;
    for (int i = 0; i < sizeof(keylogs) - 1; i++)
    {
      keylogs[i] = ' ';
    }
  }
  keylogs[keylogs_idx] = name;
  keylogs_idx++;
}

char *read_keylog(void) {
  return keylog;
}

char *read_keylogs(void) {
  return keylogs;
}
