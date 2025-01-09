# Schievel's RP2040 Tractyl Manuform (5x6) with a right side trackball

![Imgur](https://i.imgur.com/Xvua5XKh.jpeg)

* Split Hand Pin, using GP28 on left side
* Full Duplex Serial/USART using GP1 and GP2. Do not swap pins on other side, connect GP1 left to GP1 right.
* PWM WS2812 RGB using GP21
* PMW3360 sensor on SPID0, with GP17 as CS pin
* Encoder using GP26 and GP27
* SSD1306 OLED display (128x64) using GP3 and GP4 on I2CD1
* Reset LED on GP25 (blue LED an many boards)
* Double tap onboard reset switch (many boards have that) to enter bootloader
* Connect GP22 to ground 2 times in RESET_PIN_DOUBLE_TAP_RESET_TIMEOUT milliseconds (default 1000ms) to enter bootloader

Ciruit diagram:
```

                                RP2040 left
                                +-------------------+
 +------------------------------+GP0    +-----+ VBUS+-------------------------+
 |   +--------------------------+GP1    | USB | VSYS|         +---------------+---+
 |   |  +-----------+           |GND    +-----+  GND+---------|    +-LED5V    |   |
 |   |  |OLED    SDA+-----------+GP2          3V3_EN|              |          |   |
 |   |  |Display SCL+-----------+GP3         3V3_OUT+--------+-----+------+   |   |
 |   |  |        GND+-----+ ROW0|GP4        ADC_VREF|        |            |   |   |
 |   |  |        3V3+--+  | ROW1|GP5            GP28+--------+            |   |   |
 |   |  +-----------+  |  +-----+GND             GND|Encoder Root         |   |   |
 |   |                 |    ROW2|GP6            GP27|Encoder A            |   |   |
 |   |                 |    ROW3|GP7            GP26|Encoder B            |   |   |
 |   |                 |    ROW4|GP8             RUN|                     |   |   |
 |   |                 |    ROW5|GP9            GP22|Reset switch-+       |   |   |
 |   |                 |        |GND             GND+-------------+       |   |   |
 |   |                 |    COL0|GP10           GP21|LEDIN                |   |   |
 |   |                 |    COL1|GP11           GP20|                     |   |   |
 |   |                 |    COL2|GP12           GP19|                     |   |   |
 |   |                 |    COL3|GP13           GP18|                     |   |   |
 |   |                 |        |GND             GND|LEDGND               |   |   |
 |   |                 |    COL4|GP14           GP17|                     |   |   |
 |   |                 |    COL5|GP15           GP16|                     |   |   |
 |   |                 |        +-------------------+                     |   |   |
 |   |                 |                                                  |   |   |
 |   |                 |                                                  |   |   |
 |   |                 +--------------------------------------------------+   |   |
 |   |                                                                        |   |
 |   |                                                                        |   |
 |   |                                                                        |   |
 |   |                                                                        |   |
 |   |                                                                        |   |
 |   |                                                  +---------------------+   |
 |   |                                                  |                         |
 |   |                          RP2040 right            |  +----------------------+
 |   |                          +-------------------+   |  |
 +---+--------------------------+GP0    +-----+ VBUS|   |  |
     +--------------------------+GP1    | USB | VSYS|---+  |
 +-----------+                  |GND    +-----+  GND|------+           +-LED5V
 |OLED    SDA+------------------+GP2          3V3_EN|                  |
 |Display SCL+------------------+GP3         3V3_OUT+---------------+--+-----------------+
 |        GND+---------+    ROW0|GP4        ADC_VREF|               |                    |
 |        3V3+---+     |    ROW1|GP5            GP28|--+            |                    |
 +-----------+   |     +--------+GND             GND|--+            |                    |
                 |          ROW2|GP6            GP27|Encoder A      |                    |
                 |          ROW3|GP7            GP26|Encoder B      |                    |
                 |          ROW4|GP8             RUN|               |                    |
                 |          ROW5|GP9            GP22|Reset switch-+ |       PMW3360      |
                 |      Enc Root|GND             GND|-------------+ |      +---------+   |
                 |          COL0|GP10           GP21|LEDIN          +------+ VCC     |   |
                 |          COL1|GP11           GP20|          +-----------+ MIS     |   |
                 |          COL2|GP12           GP19+----------+-----------+ MOS     |   |
                 |          COL3|GP13           GP18+----------+-----------+ SCL     |   |
                 |        LEDGND|GND             GND|--+   +---+-----------+ SS      |   |
                 |          COL4|GP14           GP17+--+---+   |       +---+ GND     |   |
                 |          COL5|GP15           GP16+--+-------+       |   |         |   |
                 |              +-------------------+  |               |   +---------+   |
                 |                                     +---------------+                 |
                 |                                                                       |
                 |                                                                       |
                 +- ---------------------------------------------------------------------+





```

PCB (not strictly necessary):
![Imgur](https://i.imgur.com/KGgvo96.jpeg)

## Keyboard Info

* Keyboard Maintainer: [Schievel](https://github.com/Schievel1)
* Hardware Supported: Design files [[1]](https://gitlab.com/keyboards1/dm_r_track/-/tree/master/boolean)[[2]](https://github.com/Schievel1/baby_got_track), [Rasberry Pi Pico or similar clone](https://www.raspberrypi.com/products/raspberry-pi-pico/), PMW3360 Optical Sensor [[1]](https://www.tindie.com/products/jkicklighter/pmw3360-motion-sensor/)[[2]](https://www.ebay.de/itm/275829001607) [PCB (optional)](https://www.ebay.de/itm/276107110019)

Make example for this keyboard (after setting up your build environment):

    make handwired/tractyl_manuform/5x6_right/rp2040:default

Flashing example for this keyboard:

    make handwired/tractyl_manuform/5x6_right/rp2040:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

* **Bootmagic reset**: Hold down the top right key on the right side, or the top left key on the left side while plugging in.
* **Physical reset button**: Doubletab the "RST" button on the RP2040
* **Keycode in layout**: Press the key mapped to `QK_BOOT`.
* **External physical reset button**: Doubletab PIN GP22 to GND
