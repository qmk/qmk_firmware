# RGB Lighting

<!-- FIXME: Describe how to use RGB Lighting here. -->

## RGB Under Glow Mod

![Planck with RGB Underglow](https://raw.githubusercontent.com/qmk/qmk_firmware/master/keyboards/planck/keymaps/yang/planck-with-rgb-underglow.jpg)

Here is a quick demo on Youtube (with NPKC KC60) (https://www.youtube.com/watch?v=VKrpPAHlisY).

For this mod, you need an unused pin wiring to DI of WS2812 strip. After wiring the VCC, GND, and DI, you can enable the underglow in your Makefile.

    RGBLIGHT_ENABLE = yes

In order to use the underglow animation functions, you need to have `#define RGBLIGHT_ANIMATIONS` in your `config.h`.

Please add the following options into your config.h, and set them up according your hardware configuration. These settings are for the `F4` pin by default:

    #define RGB_DI_PIN F4     // The pin your RGB strip is wired to
    #define RGBLIGHT_ANIMATIONS    // Require for fancier stuff (not compatible with audio)
    #define RGBLED_NUM 14     // Number of LEDs
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17

You'll need to edit `RGB_DI_PIN` to the pin you have your `DI` on your RGB strip wired to.

The firmware supports 5 different light effects, and the color (hue, saturation, brightness) can be customized in most effects. To control the underglow, you need to modify your keymap file to assign those functions to some keys/key combinations. For details, please check this keymap. `keyboards/planck/keymaps/yang/keymap.c`

### WS2812 Wiring

![WS2812 Wiring](https://raw.githubusercontent.com/qmk/qmk_firmware/master/keyboards/planck/keymaps/yang/WS2812-wiring.jpg)

Please note the USB port can only supply a limited amount of power to the keyboard (500mA by standard, however, modern computer and most usb hubs can provide 700+mA.). According to the data of NeoPixel from Adafruit, 30 WS2812 LEDs require a 5V 1A power supply, LEDs used in this mod should not more than 20.

## RGB Lighting Keycodes

This controls the RGB Lighting functionality. Most keyboards use WS2812 (and compatible) LEDs for underlight or case lighting.

|Name|Description|
|----|-----------|
|`RGB_TOG`|toggle on/off|
|`RGB_MOD`|cycle through modes|
|`RGB_HUI`|hue increase|
|`RGB_HUD`|hue decrease|
|`RGB_SAI`|saturation increase|
|`RGB_SAD`|saturation decrease|
|`RGB_VAI`|value increase|
|`RGB_VAD`|value decrease|
