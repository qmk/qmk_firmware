# Terrazzo

![Terrazzo](https://i.imgur.com/W91ixck.jpg)

Terrazzo is a 40% pro micro keyboard kit with a fun, hot-swapable LED module. It is offered in both staggered and ortholinear variations, each with multiple layout options. A left hand macro column has 4 positions for switches or rotary encoders. 

Extended layout options and multiple encoder support will require use of an Elite-C controller. Key switch support is MX soldered only.

* Keyboard Maintainer: MsMustard, [Anne Demey](https://github.com/ademey) 
* Hardware Supported: Terrazzo v1 & v2 PCB in staggered and ortholinear

Make example for this keyboard (after setting up your build environment):

- `make terrazzo:default` Split spacebar staggered layout
- `make terrazzo:ortho` 2 x 2u spacebar ortho layout
- `make terrazzo:ortho_mit` 2u spacebar ortho layout
- `make terrazzo:ortho_all` All 1u ortho layout

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Parts List
- 1 PCB (staggered or ortho)
- 1 LED module ([red](https://www.digikey.com/product-detail/en/adafruit-industries-llc/3134/1528-1699-ND/6058480), [green](https://www.digikey.com/product-detail/en/adafruit-industries-llc/3136/1528-1701-ND/6058482), [yellow](https://www.digikey.com/short/zbttp5), [blue](https://www.digikey.com/product-detail/en/adafruit-industries-llc/3137/1528-1702-ND/6058483), or [white](https://www.digikey.com/product-detail/en/adafruit-industries-llc/3138/1528-1703-ND/6058484))
- [1 Rotary encoder](https://www.digikey.com/short/zbttzn)
- 1 Knurled knob ([black](https://www.digikey.com/short/zbttz4) or [silver](https://www.digikey.com/short/zbttz4))
- [SMD diodes](https://www.digikey.com/short/zbttzr)
- [Reset switch](https://www.digikey.com/short/zbttz1)
- Mill-max female headers ([12](https://www.digikey.com/short/zbtt42) & [5](https://www.digikey.com/short/zbttmt) pins) and [through-hole diodes](https://www.digikey.com/short/zbttmj) to aid in socketing a pro micro
- Mill-max [male](https://www.digikey.com/short/zbttm5) & [female](https://www.digikey.com/short/zbttm4) headers for LED module

## Custom Keycodes

Terrazzo has several custom keycodes for LED control.

| Key | Description |
|-----|-------------|
| `TZ_NXT` | Next Animation |
| `TZ_PRV` | Previous Animation |
| `TZ_OFF` | LED Off |

## LED Animations

LED animations for Terrazzo are reactive to keyboard input. Each key press or encoder turn increments an internal counter, looping through the number of individual LEDs. 

This counter (`terrazzo_led_index`) is used as a seed for the animation functions, along with a boolean indicating the direction. Turning the encoder counter-clockwise, or pressing backspace will decrement the counter, allowing for animations to reverse or display alternative frames.

The current animations are:

- DINO: It's like your internet went out
- DOT: Just a single led at a time, for debugging
- HEART: Love you too
- OUTRUN: Driving into the sunset
- PAC_DUDE: Vintage arcade fun
- STRIPES: Just a nice gradient
- WPM_CHART: 2 digit readout with lights indicating speed, each pixel = 2 wpm

Not all animations are enabled by default. You can enable or disable animations in the `config.h` file to limit firmware size.

```
// #define DISABLE_TERRAZZO_EFFECT_STRIPES
// #define DISABLE_TERRAZZO_EFFECT_DINO
// #define DISABLE_TERRAZZO_EFFECT_OUTRUN
#define DISABLE_TERRAZZO_EFFECT_PAC_DUDE
#define DISABLE_TERRAZZO_EFFECT_HEART
// #define DISABLE_TERRAZZO_EFFECT_WPM_CHART
#define DISABLE_TERRAZZO_EFFECT_DOT
```

## Microcontroller Support

Terrazzo is designed for use with a Pro Micro (or compatible, like Bit-C), or an Elite-C. The extra pinouts of an Elite-C are required for the ortho MIT and ALL layouts and multiple encoders. By default the firmware is set up for an Elite-C. For a Pro Micro some changes to `config.h` are needed.

Change number of rows from 9 to 8.
```
#define MATRIX_ROWS 8
```

Change pinouts, Pro Micro does not have the "F0" pin.
```
#define MATRIX_ROW_PINS { D2, D7, E6, B4, B5, B6, B2, B3 }
```

Set encoder to just top or bottom position.
```
#define ENCODERS_PAD_A { C6 }
#define ENCODERS_PAD_B { D4 }
```

## Encoder Setup

Terrazzo has 4 positions for encoders in the left-hand column. Up to 3 may be used at a time, but this requires the extra pins of an Elite-C. Please refer to `config.h` for examples of pin configurations.

The default keymaps are setup for one encoder. Encoders can change behavior based on the current layer. Here, on the "NAV" layer, the encoder changes volume instead of scrolling.

```c
bool encoder_update_user(uint8_t index, bool clockwise) {
    terrazzo_scroll_pixel(clockwise);
    switch(get_highest_layer(layer_state)) {
      case _NAV:
        // Change volume when on nav layer
        clockwise ? tap_code(KC_AUDIO_VOL_UP) : tap_code(KC_AUDIO_VOL_DOWN);
        break;
      default:
        // Default encoder behavior of Page Up and Down
        clockwise ? tap_code(KC_PGDN) : tap_code(KC_PGUP);
        break;
    }   
    return true;
}
```

If using multiple encoders, the `index` param can be used to distingish which is providing input.

```c
bool encoder_update_user(uint8_t index, bool clockwise) {
    terrazzo_scroll_pixel(clockwise);
    switch(index) {
      case 0:
        clockwise ? tap_code(KC_PGDN) : tap_code(KC_PGUP);
        break;
      case 1:
        clockwise ? tap_code(KC_AUDIO_VOL_UP) : tap_code(KC_AUDIO_VOL_DOWN);
        break;        
    }
    return true;
}
```
