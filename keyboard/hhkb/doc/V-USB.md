V-USB controller for HHKB
=========================
Not supported actively any more.

## Build
Use `Makefile.vusb` for [V-USB] controller.
    $ make -f Makefile.vusb

##Hardware
###3. V-USB connection
                    +---+   +---------------+
    USB            GND  |   |   ATmega328p  |
    ~~~                 C3  |               |
    5V <-------+--------+---|Vcc,AVCC       |               HHKB pro    pro2
               R1           |               |               ~~~~~~~~    ~~~~
    D- <----+--+-----R2-----|INT1      PB2-4|------->ROW    (6-8)       (5-7)
    D+ <----|---+----R3-----|INT0      PC0-2|------->COL    (9-11)      (8-10)
            Z1  Z2          |            PC3|------->ENABLE (12)        (11)
    GND<----+---+-----------|GND         PB0|<-------KEY    (4)         (3)
                            |            PB1|------->PREV   (5)         (4)
                            |               |
                GND+-C2--+--|XTAL1       RXD|------->Debug Console
                         X1 |            TXD|<-------Debug Console
                GND+-C3--+--|XTAL2       RST|---SW--+GND
                            +---------------+
    R1:     1.5K Ohm
    R2,R3:  68 Ohm
    Z1,Z2:  Zener 3.6V
    C1,C2:  22pF
    C3:     0.1uF
    X1:     Crystal 12MHz
    SW:     Push Switch(for bootloader)

- NOTE: See [V-USB] documentation for more detail of hardware and the USB stack.
- NOTE: [USBaspLoader] is very useful for firmware update.


[V-USB]: http://www.obdev.at/products/vusb/index.html
[USBaspLoader]: http://www.obdev.at/products/vusb/usbasploader.html
