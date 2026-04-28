#ifdef PS2_DRIVER_INTERRUPT
#define PS2_CLOCK_PIN   D2
#define PS2_DATA_PIN    D5

#define PS2_INT_INIT()  do {    \
    EICRA |= ((1<<ISC21) |      \
              (0<<ISC20));      \
} while (0)
#define PS2_INT_ON()  do {      \
    EIMSK |= (1<<INT2);         \
} while (0)
#define PS2_INT_OFF() do {      \
    EIMSK &= ~(1<<INT2);        \
} while (0)
#define PS2_INT_VECT   INT2_vect
#endif

#define PS2_MOUSE_INVERT_X
#define PS2_MOUSE_INVERT_Y
#define PS2_MOUSE_INVERT_H
#define PS2_MOUSE_INVERT_V
#define PS2_MOUSE_SCROLL_DIVISOR_H 2                                          
#define PS2_MOUSE_SCROLL_DIVISOR_V 2
