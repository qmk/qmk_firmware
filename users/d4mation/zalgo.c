#include "zalgo.h"

void zalgo_text( uint16_t keycode ) {

  tap_code( keycode );

  int number = ( rand() % ( 8 + 1 - 2 ) ) + 2;
  unsigned int index;

  unicode_input_start();

  for ( index = 0; index < number; index++ ) {

    uint16_t hex = ( rand() % ( 0x036F + 1 - 0x0300 ) ) + 0x0300;
    register_hex( hex );

  }

  unicode_input_finish();

}