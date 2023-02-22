# The kwer keymap and RGB MOD for cypher

![](https://i.imgur.com/b7snIju.jpg)

## Hardware
To make this mod, all you need a piece of WS2812b RGB strip (I used one with 144 LEDs per meter, so it's rather dense), some wiring (I used 0.6mm solid core wire) and steady hands for soldering to the MCU pin.

**Installed mod**
![](https://i.imgur.com/IKcFd0k.jpg)

As you can see, the wiring is relatively simple. VCC and GND can be easily accessed through the ISP header on the right side of the spacebar while the DATA line can be routed relatively easy through one of the stabilizer holes. While it isn't important where exactly you solder the VCC/GND wires to their respective lines on the strip, you have to keep the direction of the data line in mind. Most strip have arrows printed on them to show you in which direction the data is shifted through the LEDs and your should always solder your DATA line on the _from_ side, as seen in the above picture.

**Close-up for the VCC/GND connections**
![](https://i.imgur.com/K0OibwW.jpg)

Since there is no pinout availble for the pin we're gonna use to control the strip, the line has to be soldered to the MCU directly. While this is not a very complex process, you should have a fine tipped soldering irong and a steady hand. Make sure you do not bridge any of the neighboring pins when soldering the wire to the MCU pin. As shown in the picture below, you want to connect the DATA line to the third pin from the right on the top of the controller chip.

**Close-up for the DATA connection**
![](https://i.imgur.com/zkD3RjF.jpg)

## Software
To enable your RGB strip in QMK, you have to add change/add the following lines

**rules.&#8203;mk**
```
[...]
RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
[...]
```

**config.h**
```
[...]
#define RGB_DI_PIN F7
#define RGBLED_NUM 15        // Change this number to the amount of LEDs on the strip you soldered
[...]
```
To control the RGB color, animation, etc. you need to add the appropriate keycodes to your keymap. Either see [my keymap](./keymap.c) or the [official QMK documentation](https://docs.qmk.fm/#/feature_rgblight?id=keycodes) for references.
