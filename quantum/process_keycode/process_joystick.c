#include "process_joystick.h"

#include <quantum/joystick.h>
#include <quantum/quantum_keycodes.h>

#ifdef __AVR__
# include <drivers/avr/analog.h>
#endif

#include <string.h>

bool process_joystick_buttons(uint16_t keycode, keyrecord_t *record);

bool process_joystick(uint16_t keycode, keyrecord_t *record){
  
  if (process_joystick_buttons(keycode, record) 
    && (joystick_status.status & JS_UPDATED)>0){
    send_joystick_packet(&joystick_status);
    joystick_status.status &= ~JS_UPDATED;
  }
  
  return true;
}

__attribute__ ((weak))
void joystick_task(void){
  if (process_joystick_analog() && (joystick_status.status & JS_UPDATED)){
    send_joystick_packet(&joystick_status);
    joystick_status.status &= ~JS_UPDATED;
  }
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

__attribute__ ((weak))
bool process_joystick_analog(){
#if JOYSTICK_AXES_COUNT > 0
  for (int axis_index=0 ; axis_index<JOYSTICK_AXES_COUNT ; ++axis_index){
    if (joystick_axes[axis_index].output_pin==JS_VIRTUAL_AXIS || joystick_axes[axis_index].input_pin==JS_VIRTUAL_AXIS){
      continue;
    }
    
    setPinOutput(joystick_axes[axis_index].output_pin);
    writePinHigh(joystick_axes[axis_index].output_pin);
    
    //disable pull-up resistance
    setPinInput(joystick_axes[axis_index].input_pin);
    writePinLow(joystick_axes[axis_index].input_pin);
    
#ifdef __AVR__
    int16_t axis_val = analogReadPin(joystick_axes[axis_index].input_pin);
#else
    int16_t axis_val = 0;
#endif
    if (axis_val!=joystick_status.axes[axis_index]){
      joystick_status.axes[axis_index] = axis_val;
      joystick_status.status |= JS_UPDATED;
    }
    
    writePinLow(joystick_axes[axis_index].output_pin);
  }
#endif
  return true;
}
