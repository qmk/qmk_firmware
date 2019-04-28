PS/2 to USB keyboard converter
==============================
This firmware converts PS/2 keyboard protocol to USB.(It supports Scan Code Set 2.)


Connect Wires
-------------
1. Connect **Vcc** and **GND**.
2. Connect **Clock** and **Data** line. 
    - **Interrupt**:   **Clock** is on `PD1` and **Data** on `PD0`.(Recommended. Soarer's converter compatible)
    - **Busywait**:    **Clock** is on `PD1` and **Data** on `PD0`.
    - **USART**:       **Clock** is on `PD5` and **Data** on `PD2`.
3. You need pull-up resistors. 1K-10K Ohm would be fine.

To change pin configuration edit **config.h** and **Makefile**.


Build Firmware
--------------
For **TMK converter Rev.2**:

    $ make -f Makefile.rev2 clean
    $ make -f Makefile.rev2 KEYMAP=plain

To program firmware push the button on converter and run:

    $ make -f Makefile.rev2 KEYMAP=plain dfu


- For **TMK converter Rev.1** use `make -f Makefile.rev1` instead.
- To select keymap use `jis`, `spacefn` or your own in place of `plain`.


Keymap
------
Several version of keymap are available in advance but you are recommended to define your favorite layout yourself. To define your own keymap create file named `keymap_<name>.c` and see keymap document(you can find in README.md of top directory) and existent keymap files.


PS/2 signal handling implementations
------------------------------------
Following three methods can be used to implement PS/2 signal handling.

### Simple and stupid busy-wait(ps2_busywait.c)
    This is expected to implemented with portable C code for reference.
### Interrupt driven(ps2_interrupt.c)
    Uses pin interrupt to detect falling edge of clock line.
### USART hardware module(ps2_usart.c)
    Uses AVR USART engine to receive PS/2 signal.

To select method edit Makefile.


V-USB Support
-------------
With V-USB you can use this converter on ATmega(168/328) but it doesn't support NKRO at this time.

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
