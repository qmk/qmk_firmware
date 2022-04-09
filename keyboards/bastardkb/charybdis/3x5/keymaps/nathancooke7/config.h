#pragma once

#define CHARYBDIS_MINIMUM_DEFAULT_DPI 1200
#define CHARYBDIS_MINIMUM_SNIPING_DPI 400
#define CHARYBDIS_DRAGSCROLL_REVERSE_Y

#ifdef ENCODER_ENABLE
/* Free pins { B7 D5 C7 } */
/* Encoder is NOT fully compatible with the SPI pins { B1 B2 B3 F1 } */
/* You will need to connect the GND and VCC pins to SPI pins as marked */
/* You will need to connect the TK and TK pins to { B7 D5 and C7 } */
#define ENCODERS_PAD_A { B1 }
#define ENCODERS_PAD_B { B2 }
#define ENCODER_RESOLUTIONS { 4 }
#endif
