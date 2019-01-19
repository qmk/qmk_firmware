## PS/2 Mouse Support

Its possible to hook up a PS/2 mouse (for example touchpads or trackpoints) to your keyboard as a composite device.

To hook up a Trackpoint, you need to obtain a Trackpoint module (i.e. harvest from a Thinkpad keyboard), identify the function of each pin of the module, and make the necessary circuitry between controller and Trackpoint module. For more information, please refer to [Trackpoint Hardware](https://deskthority.net/wiki/TrackPoint_Hardware) page on Deskthority Wiki.

There are three available modes for hooking up PS/2 devices: USART (best), interrupts (better) or busywait (not recommended).

### The Cirtuitry between Trackpoint and Controller

To get the things working, a 4.7K drag is needed between the two lines DATA and CLK and the line 5+. 

```

          DATA ----------+--------- PIN
                         |
                        4.7K
                         |
MODULE    5+  --------+--+--------- PWR   CONTROLLER
                      |
                     4.7K
                      |    
          CLK   ------+------------ PIN
```


### Busywait Version

Note: This is not recommended, you may encounter jerky movement or unsent inputs. Please use interrupt or USART version if possible.

In rules.mk:

```
PS2_MOUSE_ENABLE = yes
PS2_USE_BUSYWAIT = yes
```

In your keyboard config.h:

```
#ifdef PS2_USE_BUSYWAIT
#   define PS2_CLOCK_PORT  PORTD
#   define PS2_CLOCK_PIN   PIND
#   define PS2_CLOCK_DDR   DDRD
#   define PS2_CLOCK_BIT   1
#   define PS2_DATA_PORT   PORTD
#   define PS2_DATA_PIN    PIND
#   define PS2_DATA_DDR    DDRD
#   define PS2_DATA_BIT    2
#endif
```

### Interrupt Version

The following example uses D2 for clock and D5 for data. You can use any INT or PCINT pin for clock, and any pin for data.

In rules.mk:

```
PS2_MOUSE_ENABLE = yes
PS2_USE_INT = yes
```

In your keyboard config.h:

```
#ifdef PS2_USE_INT
#define PS2_CLOCK_PORT  PORTD
#define PS2_CLOCK_PIN   PIND
#define PS2_CLOCK_DDR   DDRD
#define PS2_CLOCK_BIT   2
#define PS2_DATA_PORT   PORTD
#define PS2_DATA_PIN    PIND
#define PS2_DATA_DDR    DDRD
#define PS2_DATA_BIT    5

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
```

### USART Version

To use USART on the ATMega32u4, you have to use PD5 for clock and PD2 for data. If one of those are unavailable, you need to use interrupt version.

In rules.mk:

```
PS2_MOUSE_ENABLE = yes
PS2_USE_USART = yes
```

In your keyboard config.h:

```
#ifdef PS2_USE_USART
#define PS2_CLOCK_PORT  PORTD
#define PS2_CLOCK_PIN   PIND
#define PS2_CLOCK_DDR   DDRD
#define PS2_CLOCK_BIT   5
#define PS2_DATA_PORT   PORTD
#define PS2_DATA_PIN    PIND
#define PS2_DATA_DDR    DDRD
#define PS2_DATA_BIT    2

/* synchronous, odd parity, 1-bit stop, 8-bit data, sample at falling edge */
/* set DDR of CLOCK as input to be slave */
#define PS2_USART_INIT() do {   \
    PS2_CLOCK_DDR &= ~(1<<PS2_CLOCK_BIT);   \
    PS2_DATA_DDR &= ~(1<<PS2_DATA_BIT);     \
    UCSR1C = ((1 << UMSEL10) |  \
              (3 << UPM10)   |  \
              (0 << USBS1)   |  \
              (3 << UCSZ10)  |  \
              (0 << UCPOL1));   \
    UCSR1A = 0;                 \
    UBRR1H = 0;                 \
    UBRR1L = 0;                 \
} while (0)
#define PS2_USART_RX_INT_ON() do {  \
    UCSR1B = ((1 << RXCIE1) |       \
              (1 << RXEN1));        \
} while (0)
#define PS2_USART_RX_POLL_ON() do { \
    UCSR1B = (1 << RXEN1);          \
} while (0)
#define PS2_USART_OFF() do {    \
    UCSR1C = 0;                 \
    UCSR1B &= ~((1 << RXEN1) |  \
                (1 << TXEN1));  \
} while (0)
#define PS2_USART_RX_READY      (UCSR1A & (1<<RXC1))
#define PS2_USART_RX_DATA       UDR1
#define PS2_USART_ERROR         (UCSR1A & ((1<<FE1) | (1<<DOR1) | (1<<UPE1)))
#define PS2_USART_RX_VECT       USART1_RX_vect
#endif
```

### Additional Settings

#### PS/2 Mouse Features

These enable settings supported by the PS/2 mouse protocol: http://www.computer-engineering.org/ps2mouse/

```
/* Use remote mode instead of the default stream mode (see link) */
#define PS2_MOUSE_USE_REMOTE_MODE

/* Enable the scrollwheel or scroll gesture on your mouse or touchpad */
#define PS2_MOUSE_ENABLE_SCROLLING

/* Some mice will need a scroll mask to be configured. The default is 0xFF. */
#define PS2_MOUSE_SCROLL_MASK 0x0F

/* Applies a transformation to the movement before sending to the host (see link) */
#define PS2_MOUSE_USE_2_1_SCALING

/* The time to wait after initializing the ps2 host */
#define PS2_MOUSE_INIT_DELAY 1000 /* Default */
```

You can also call the following functions from ps2_mouse.h

```
void ps2_mouse_disable_data_reporting(void);

void ps2_mouse_enable_data_reporting(void);

void ps2_mouse_set_remote_mode(void);

void ps2_mouse_set_stream_mode(void);

void ps2_mouse_set_scaling_2_1(void);

void ps2_mouse_set_scaling_1_1(void);

void ps2_mouse_set_resolution(ps2_mouse_resolution_t resolution);

void ps2_mouse_set_sample_rate(ps2_mouse_sample_rate_t sample_rate);
```

#### Fine Control

Use the following defines to change the sensitivity and speed of the mouse.
Note: you can also use `ps2_mouse_set_resolution` for the same effect (not supported on most touchpads).

```
#define PS2_MOUSE_X_MULTIPLIER 3
#define PS2_MOUSE_Y_MULTIPLIER 3
#define PS2_MOUSE_V_MULTIPLIER 1
```

#### Scroll Button

If you're using a trackpoint, you will likely want to be able to use it for scrolling.
Its possible to enable a "scroll button/s" that when pressed will cause the mouse to scroll instead of moving.
To enable the feature, you must set a scroll button mask as follows:

```
#define PS2_MOUSE_SCROLL_BTN_MASK (1<<PS2_MOUSE_BUTTON_MIDDLE) /* Default */
```

To disable the scroll button feature:

```
#define PS2_MOUSE_SCROLL_BTN_MASK 0
```

The available buttons are:

```
#define PS2_MOUSE_BTN_LEFT      0
#define PS2_MOUSE_BTN_RIGHT     1
#define PS2_MOUSE_BTN_MIDDLE    2
```

You can also combine buttons in the mask by `|`ing them together.

Once you've configured your scroll button mask, you must configure the scroll button send interval.
This is the interval before which if the scroll buttons were released they would be sent to the host.
After this interval, they will cause the mouse to scroll and will not be sent.

```
#define PS2_MOUSE_SCROLL_BTN_SEND 300 /* Default */
```

To disable sending the scroll buttons:
```
#define PS2_MOUSE_SCROLL_BTN_SEND 0
```

Fine control over the scrolling is supported with the following defines:

```
#define PS2_MOUSE_SCROLL_DIVISOR_H 2
#define PS2_MOUSE_SCROLL_DIVISOR_V 2
```

#### Invert Mouse and Scroll Axes

To invert the X and Y axes you can put:

```
#define PS2_MOUSE_INVERT_X
#define PS2_MOUSE_INVERT_Y
```

into config.h.

To reverse the scroll axes you can put:

```
#define PS2_MOUSE_INVERT_H
#define PS2_MOUSE_INVERT_V
```

into config.h.

#### Debug Settings

To debug the mouse, add `debug_mouse = true` or enable via bootmagic.

```
/* To debug the mouse reports */
#define PS2_MOUSE_DEBUG_HID
#define PS2_MOUSE_DEBUG_RAW
```
