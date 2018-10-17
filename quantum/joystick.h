#ifndef JOYSTICK_H
#define JOYSTICK_H

#ifndef JOYSTICK_BUTTON_COUNT
#define JOYSTICK_BUTTON_COUNT 8
#endif

#ifndef JOYSTICK_AXES_COUNT
#define JOYSTICK_AXES_COUNT 4
#endif

#include <stdint.h>

//configure on input_pin of the joystick_axes array entry to JS_VIRTUAL_AXIS 
// to prevent it from being read from the ADC. This allows outputing forged axis value.
//
#define JS_VIRTUAL_AXIS 0xFF

typedef struct {
  uint8_t output_pin;
  uint8_t input_pin;
  
  //the AVR ADC offers 10 bit precision, with significant bits on the higher part
  uint16_t min_digit;
  uint16_t max_digit;
} joystick_config_t;

extern joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT];

enum joystick_status{
  JS_INITIALIZED = 1,
  JS_UPDATED = 2
};

typedef struct {
  
  uint8_t buttons[JOYSTICK_BUTTON_COUNT/8+1];
  
  int8_t  axes[JOYSTICK_AXES_COUNT];
  uint8_t status:2;
} joystick_t;

extern joystick_t joystick_status;

//to be implemented in the hid protocol library
void send_joystick_packet(joystick_t* joystick);

#endif //JOYSTICK_H