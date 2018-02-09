#include <string.h>
#include "quantum.h"

bool CWP_record_on = false;
char CWP_recorded_input[50] = "\0";
void (*CWP_callback)(char arg[]);
uint16_t CWP_space_keycodes[10];
bool CWP_numbers_only = false;

void callback_with_param(void (*callback)(char arg[]), bool numbers_only, uint16_t space_keycodes[]) {
  CWP_record_on = true;
  CWP_callback = callback;
  CWP_numbers_only = numbers_only;
  memcpy(CWP_space_keycodes, space_keycodes, sizeof(CWP_space_keycodes));
}

bool is_space(uint16_t keycode) {
  for(int i = 0; i < 10; i++) {
    if(CWP_space_keycodes[i] == keycode) return true;
  }
  return false;
}

const bool callback_with_param_check(uint16_t keycode) {
  if(!CWP_record_on) return false;

  if(keycode == KC_ENTER) {
    CWP_record_on = false;
    CWP_callback(CWP_recorded_input);
    strcpy(CWP_recorded_input, "\0");
    return true;
  }

  char input[] = "\0";
  if(keycode >= 4 && keycode <= 29 && !CWP_numbers_only) {
    input[0] = (char)keycode+93;
  }
  else if(keycode >= 30 && keycode <= 39 ) {
    input[0]  = keycode == KC_0 ? '0' : (char)keycode+19;
  }
  else if(is_space(keycode) && !CWP_numbers_only) {
    input[0]  = ' ';
  }

  if(input[0]) {
    strcat(CWP_recorded_input, input);
    return true;
  }

  return false;
}
