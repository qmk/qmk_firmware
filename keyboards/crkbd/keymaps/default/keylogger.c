#include "crkbd.h"

char KEYLOG[40] = {};
char KEYLOGS[21] = {};
int KEYLOGS_IDX = 0;
char TIMELOG[40] = {};

char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ';', '\'', ' ', ',', '.', '/', ' ', ' ', ' '};

void keylog_set(uint16_t keycode, keyrecord_t *record)
{
  char name = ' ';
  if (keycode < 60)
  {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(KEYLOG, sizeof(KEYLOG), "%dx%d, k%2d : %c",
           record->event.key.row,
           record->event.key.col,
           keycode,
           name);

  // update keylogs
  if (KEYLOGS_IDX == sizeof(KEYLOGS) - 1)
  {
    KEYLOGS_IDX = 0;
    for (int i = 0; i < sizeof(KEYLOGS) - 1; i++)
    {
      KEYLOGS[i] = ' ';
    }
  }
  KEYLOGS[KEYLOGS_IDX] = name;
  KEYLOGS_IDX++;
}

char *keylog_read(void) {
  return KEYLOG;
}

char *keylogs_read(void) {
  return KEYLOGS;
}
