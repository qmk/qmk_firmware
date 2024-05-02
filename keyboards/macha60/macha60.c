#include "quantum.h"

bool led_update_kb(led_t led_state){
  bool res = led_update_user(led_state);
  if(res)
  {
    writePin(D5, !led_state.caps_lock);
  }

  return res;
}
