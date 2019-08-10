# Jotanck

![Jotanck](https://i.imgur.com/bBfO4L2.jpg)

A compact 40% (12x4) ortholinear keyboard kit inspired in the Planck made by jotix.

Keyboard Maintainer: [jotix](https://github.com/jotix)  
Hardware Supported: Arduino Pro Micro  
Hardware Availability: [Mercado Libre](https://articulo.mercadolibre.com.ar/MLA-771696548-teclado-mecanico-handwired-black-switchs-pbt-keycaps-_JM)

### Arduino Pro Micro Pinout

| Rows        | 0  | 1  | 2  | 3  |
|-------------|----|----|----|----|
| Arduino pin | 6  | 7  | 10 | 16 |
| QMK pin     | D7 | E6 | B6 | B2 |

| Columns     | 0  | 1  | 2  | 3  | 4  | 5  | 6   | 7   | 8  | 9  | 10 | 11 |
|-------------|----|----|----|----|----|----|-----|-----|----|----|----|----|
| Arduino pin | A3 | A2 | A1 | A0 | 15 | 14 | TX0 | RXI | 2  | 3  | 4  | 5  |
| QMK pin     | F4 | F5 | F6 | F7 | B1 | B3 | D3  | D2  | D1 | D0 | D4 | C6 |

|             | LED1 | LED2 |
|-------------|------|------|
| Arduino pin | 9    | 8    |
| QMK pin     | B5   | B4   |

### Compiling the Firmware

Make example for this keyboard (after setting up your build environment):

    make handwired/jotanck:default

### The Defaukt Keymap

![Default Keymap](https://i.imgur.com/xh7Dmd7.png)

To reset the keyboard press Ctrl+Esc+BackSpace

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
