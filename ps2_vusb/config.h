#ifndef CONFIG_H
#define CONFIG_H


#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6512
#define MANUFACTURER    t.m.k.
#define PRODUCT         PS/2 keyboard converter
#define DESCRIPTION     convert PS/2 keyboard to USB

/* matrix size */
#define MATRIX_ROWS 32  // keycode bit: 3-0
#define MATRIX_COLS 8   // keycode bit: 6-4
/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* USB NKey Rollover */
#ifdef USB_NKRO_ENABLE
#endif

/* mouse keys */
#ifdef MOUSEKEY_ENABLE
#   define MOUSEKEY_DELAY_TIME 255
#endif

/* PS/2 lines */
#define PS2_CLOCK_PORT  PORTD
#define PS2_CLOCK_PIN   PIND
#define PS2_CLOCK_DDR   DDRD
#define PS2_CLOCK_BIT   3
#define PS2_DATA_PORT   PORTD
#define PS2_DATA_PIN    PIND
#define PS2_DATA_DDR    DDRD
#define PS2_DATA_BIT    7

/* External interrupt for PS/2 clock line (optional) */
#define PS2_INT_ENABLE()  do {  \
    EIMSK |= (1<<INT1);         \
    EICRA |= ((1<<ISC11) | (0<<ISC10)); \
    EIFR |= (1<<INTF1);         \
} while (0)
#define PS2_INT_DISABLE() do {  \
    EIMSK &= ~(1<<INT1);        \
} while (0)
#define PS2_INT_VECT    INT1_vect

/* Pin Change interrupt for PS/2 clock line (optional)
#define PS2_INT_ENABLE()  do {  \
    PCMSK2 |= (1<<PCINT22);     \
    PCICR |= (1<<PCIE2);        \
    PCIFR |= (1<<PCIF2);        \
} while (0)
#define PS2_INT_DISABLE() do {  \
    PCMSK2 &= ~(1<<PCINT22);    \
    PCICR &= ~(1<<PCIE);        \
} while (0)
#define PS2_INT_VECT    PCINT2_vect
*/

#endif
