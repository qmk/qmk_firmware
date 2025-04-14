# Neodox

Inspired by Redox from Mattia Dal Ben

![neodox](https://i.imgur.com/sA6O45Jh.jpg)

**Neodox** project.

Keyboard Maintainer: [MatteoDM](https://github.com/MatteoDM)  

Hardware Supported:

- Raspberry Pi Pico microcontroller
- ws2812b
- GC9A01 Round display
- Hardware Availability: [Case files](https://www.thingiverse.com/thing:5625196)

Make example for this keyboard (after setting up your build environment):

    make handwired/neodox:default

Flashing example for this keyboard:

    make handwired/neodox:default:flash

Enter the bootloader when prompted by doing one of the following:

**Physical boot button**: Unplug your keyboard then press the BOOT button on the microcontroller PCB
**Keycode in layout**: Press the key mapped to `QK_BOOT` if you have a layout that has one.

Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

Keymap example : [neodimio keymap](https://gitlab.com/neodox/neodox/-/tree/new_keymap/keymaps/neodimio?ref_type=heads)  

Handwiring specification:

|RP2040 PIN|  FUNTIONALITY  |  COMMENTS                                                                   |
|----------|----------------|-----------------------------------------------------------------------------|
|GP0       |  USART TX      |  serial comunication between two boards( connected to rx of the other half) |
|GP1       |  USART RX      |  serial comunication between two boards(connected to tx of the other half)  |
|GP4       |  ROW 1         |                                                                             |
|GP5       |  ROW 2         |                                                                             |
|GP6       |  ROW 3         |                                                                             |
|GP7       |  ROW 4         |                                                                             |
|GP8       |  ROW 5         |                                                                             |
|GP9       |  COL 1         |                                                                             |
|GP10      |  COL 2         |                                                                             |
|GP11      |  COL 3         |                                                                             |
|GP12      |  COL 4         |                                                                             |
|GP13      |  COL 5         |                                                                             |
|GP14      |  COL 6         |                                                                             |
|GP15      |  COL 7         |                                                                             |
|GP16      |  RES LCD       |  lcd reset                                                                  |
|GP17      |  CS LCD        |  spi chip select                                                            |
|GP18      |  SCL LCD       |  spi clock                                                                  |
|GP19      |  SDA LCD       |  spi mosi                                                                   |
|GP21      |  DC LCD        |  data command lcd                                                           |
|GP23      |  WS2812        |  data pin for rgb leds( also called neopixel)                               |
|GP25      |  LED           |  noting to do ,usually every rp2040 controller board is wired to a led      |
|GP28      |  BLK LCD       |  backlight pwm for the lcd                                                  |

**Notes:**
GP5, GP15
this intersection is used to define handness( which of the half is, right leave it not connected on the left side, connect a diode as a continuosly pushed switch, this is possible because we have some hollow intersection that we didn t use physically in the matrix 7x5)
diode direction col to row(cathode)
