PS/2 to USB keyboard converter
==============================
This firmware converts PS/2 keyboard protocol to USB and supports only Scan Code Set 2.


PS/2 signal handling implementations
------------------------------------
Following three methods are used to implement PS/2 signal handling.

### Simple and stupid busy-wait(ps2_busywait.c)
    This is expected to implemented with portable C code for reference.
### Interrupt driven(ps2_interrupt.c)
    Uses pin interrupt to detect falling edge of clock line.
### USART hardware module(ps2_usart.c)
    Uses AVR USART engine to recevie PS/2 signal.

To select method edit Makefile.


Connect Wires
-------------
In case of Teensy2.0(ATMega32U4):

1. Connect Vcc and GND.
2. Connect Clock and Data line. 
    - Busywait:    Clock is on PD5 and Data on PD2.
    - Interrupt:   Clock is on PD1 and Data on PD2.
    - USART:       Clock is on PD5 and Data on PD2.
3. Optionally you need pull-up register. 1K-10K Ohm is OK.

To change pin configuration edit config.h.


Build Frimware
--------------
Just run `make`:

    $ make

To select keymap:

    $ make KEYMAP=[plain|jis|spacefn|...]


Keymap
------
Several version of keymap are available in advance but you are recommended to define your favorite layout yourself. To define your own keymap create file named `keymap_<name>.c` and see keymap document(you can find in top README.md) and existent keymap files.


V-USB Support
-------------
You can also use this converter on ATmega(168/328) with V-USB instead of Teensy.
The converter on V-USB lacks some features for now: USB NKRO and System/Media control.

Circuit:

                    +---+   +---------------+
    USB            GND  |   |   ATmega168   |
    ===                 C3  |               |
    5V <-------+--------+---|Vcc,AVCC       |        PS/2
               R1           |               |        ====
    D- <----+--+-----R2-----|INT1        RXD|------->DATA
    D+ <----|---+----R3-----|INT0        XCK|------->CLOCK
            Z1  Z2          |               |      ->5V
    GND<----+---+--+--+-----|GND            |      ->GND
                   |  |     |               |
                   |  C2-+--|XTAL1          |
                   |     X1 |               |
                   +--C3-+--|XTAL2          |
                            +---------------+
    R1:     1.5K Ohm
    R2,R3:  68 Ohm
    Z1,Z2:  Zenner 3.6V
    C1,C2:  22pF
    C3:     0.1uF
    X1:     Crystal 20MHz(16MHz/12MHz)
