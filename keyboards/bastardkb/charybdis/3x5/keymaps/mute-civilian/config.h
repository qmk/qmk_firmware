#pragma once

#define CHARYBDIS_MINIMUM_DEFAULT_DPI 1200
#define CHARYBDIS_MINIMUM_SNIPING_DPI 400
#define CHARYBDIS_DRAGSCROLL_REVERSE_Y

#ifdef ENCODER_ENABLE
/* Free pins { B7 D5 C7 } */
/* Encoder is NOT fully compatible with the SPI pins { B1 B2 B3 F1 } */
/* You will need to connect the RGB, GND and VCC pins to SPI pins as marked */
/* You will need to connect BTN to C7, R1 to D5, and R2 to B7 */
#define ENCODERS_PAD_A { D5 }
#define ENCODERS_PAD_B { B7 }
#define ENCODER_RESOLUTIONS { 4 }
#endif
