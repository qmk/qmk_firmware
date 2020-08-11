# Terrazzo

Terrazzo is a 40% pro micro keyboard kit with a fun, hot-swapable LED module. It is offered in both staggered and ortholinear variations, each with multiple layout options. A left hand macro column has 4 positions for switches or rotary encoders. 

Extended layout options and multiple encoder support will require use of an Elite-C controller. Key switch support is MX soldered only.

Images and layouts: https://imgur.com/a/eGyuVJs

The keyboard is QMK compatible with custom firmware to drive unique animations (and a WPM counter) on the LED module. Adding new animations is a fairly easy process if you are familiar with QMK, and I hope others want to contribute fun ideas!  This is still a work in progress, as is QMK Configurator and VIA support.

PCB Kits without a case will be offered. Plate files will be available at completion of the GB.

## Parts List
- 1 PCB (staggered or ortho)
- 1 LED module ([red](https://www.digikey.com/product-detail/en/adafruit-industries-llc/3134/1528-1699-ND/6058480), [green](https://www.digikey.com/product-detail/en/adafruit-industries-llc/3136/1528-1701-ND/6058482), [yellow](https://www.digikey.com/short/zbttp5), [blue](https://www.digikey.com/product-detail/en/adafruit-industries-llc/3137/1528-1702-ND/6058483), or [white](https://www.digikey.com/product-detail/en/adafruit-industries-llc/3138/1528-1703-ND/6058484))
- [1 Rotary encoder](https://www.digikey.com/short/zbttzn)
- 1 Knurled knob ([black](https://www.digikey.com/short/zbttz4) or [silver](https://www.digikey.com/short/zbttz4))
- [SMD diodes](https://www.digikey.com/short/zbttzr)
- [Reset switch](https://www.digikey.com/short/zbttz1)
- Mill-max female headers ([12](https://www.digikey.com/short/zbtt42) & [5](https://www.digikey.com/short/zbttmt) pins) and [through-hole diodes](https://www.digikey.com/short/zbttmj) to aid in socketing a pro micro
- Mill-max [male](https://www.digikey.com/short/zbttm5) & [female](https://www.digikey.com/short/zbttm4) headers for LED module


## Building Firmware

- `make terrazzo:default` Split spacebar staggered layout
- `make terrazzo:orhtho` 2 x 2u spacebar ortho layout
- `make terrazzo:ortho_mit` 2u spacebar ortho layout
- `make terrazzo:ortho_all` All 1u ortho layout

## Custom Keycodes

Terrazzo has several custom keycodes for LED control

| Key | Description |
|-----|-------------|
| `TZ_NXT` | Next Animation |
| `TZ_PRV` | Previous Animation |
| `TZ_OFF` | LED Off |

## Multiple Encoder Support

```c
void encoder_update_user(uint8_t index, bool clockwise) {
    terrazzo_scroll_pixel(clockwise);
    switch(index) {
      case 2:
        clockwise ? tap_code(KC_AUDIO_VOL_UP) : tap_code(KC_AUDIO_VOL_DOWN);
        break;
      case 1:
        clockwise ? tap_code(KC_UP) : tap_code(KC_DOWN);
        break;
      default:
        clockwise ? tap_code(KC_PGUP) : tap_code(KC_PGDN);
        break;
    }   
}
```