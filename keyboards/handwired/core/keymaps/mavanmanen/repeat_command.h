#include <string.h>

bool RC_record_on = false;
char RC_recorded_number[4] = "\0";
char RC_command[50] = "\0";

void repeat_command(const char com[50]) {
  strcpy(RC_command, com);
  RC_record_on = true;
}

const bool repeat_command_check(uint16_t keycode) {
  if(!RC_record_on) return false;

  if(keycode == KC_ENTER) {
    RC_record_on = false;
    int num = atoi(RC_recorded_number);
    for(int x = 0; x < num; x++) {
      send_string(RC_command);
    }
    strcpy(RC_recorded_number, "\0");
    return true;
  }

  char number[] = "\0";
  if((number[0] = (keycode < 30 || keycode > 39) ? '\0' : keycode == KC_0 ? '0' : (char)keycode+19)) {
    strcat(RC_recorded_number, number);
    return true;
  }

  return false;
}
