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

// this code runs before the usb and keyboard is initialized
void matrix_setup(void) {
  isLeftHand = eeprom_read_byte(EECONFIG_HANDEDNESS);
}
