#include "../i2c-slave.h"
#include "../serial.h"
#include "uno-matrix.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void setup(void) {
  // give some time for noise to clear
  _delay_us(1000);

  // turn off arduino uno's led on pin 13
  DDRB |= (1 << 5);
  PORTB &= ~(1 << 5);

  matrix_init();
  /* i2c_slave_init(0x32); */
  serial_slave_init();

  /* serial_slave_buffer[0] = 0xa1; */
  /* serial_slave_buffer[1] = 0x52; */
  /* serial_slave_buffer[2] = 0xa2; */
  /* serial_slave_buffer[3] = 0x67; */

  // need interrupts for i2c slave code to work
  sei();
}

void loop(void) {
  matrix_scan();
  for(int i=0; i<MATRIX_ROWS; ++i) {
    slaveBuffer[i] = matrix_get_row(i);
    serial_slave_buffer[i] = slaveBuffer[i];
  }
}

int main(int argc, char *argv[]) {
  setup();
  while (1)
    loop();
}
