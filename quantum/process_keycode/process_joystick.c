#include "process_joystick.h"

#include <quantum/joystick.h>
#include <quantum/quantum_keycodes.h>

#include <drivers/avr/analog.h>

#include <string.h>

bool process_joystick_buttons(uint16_t keycode, keyrecord_t *record);

bool process_joystick_analog(void);

bool process_joystick(uint16_t keycode, keyrecord_t *record){
  
  bool ok = process_joystick_buttons(keycode, record) 
    &&      process_joystick_analog();
  
  if (ok && (joystick_status.status & JS_UPDATED)>0){
    send_joystick_packet(&joystick_status);
    joystick_status.status &= ~JS_UPDATED;
  }
  
  return ok;
}

bool process_joystick_buttons(uint16_t keycode, keyrecord_t *record){
  
  if (keycode < JS_BUTTON0 || keycode > JS_BUTTON_MAX){
    return true;
  } else {
    if (record->event.pressed){
      joystick_status.buttons[(keycode-JS_BUTTON0)/8] |= 1<<(keycode%8);
    } else {
      joystick_status.buttons[(keycode-JS_BUTTON0)/8] &= ~(1<<(keycode%8));
    }
    
    joystick_status.status |= JS_UPDATED;
  }
  
  return true;
}

bool process_joystick_analog(){
  
#if JOYSTICK_AXES_COUNT > 0
  for (int axis_index=0 ; axis_index<JOYSTICK_AXES_COUNT ; ++axis_index){
    if (joystick_axes[axis_index].input_pin==JS_VIRTUAL_AXIS){
      continue;
    }
    
    int16_t axis_val = analogRead(joystick_axes[axis_index].input_pin);
    if (axis_val!=joystick_status.axes[axis_index]){
      joystick_status.axes[axis_index] = axis_val;
      joystick_status.status |= JS_UPDATED;
    }
  }
#endif
  return true;
}
