#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "split_util.h"
#include "matrix.h"
#include "keyboard.h"
#include "config.h"
#include "timer.h"
#include "debug.h"

volatile bool isLeftHand = true;
volatile bool contacted_by_master = false;

bool is_rev2(void) // Input with pullup, if rev2, pin is pulled down with 220R resistor.
{
  setPinInputHigh(B5);
  bool rev2 = !readPin(B5);
  setPinInput(B5);
  return rev2;
}

// this code runs before the usb and keyboard is initialized
void matrix_setup(void) {
  isLeftHand = eeprom_read_byte(EECONFIG_HANDEDNESS);
}
