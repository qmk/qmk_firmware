# Introduction
This keyboard layout centers around Dvorak,  harnesing the power of the Kyria thumb
clusters and layers to reduce finger and wrist movement.

## IMPORTANT NOTE
This keymap will only work if you have all the kyria keys available! If you've used 2u keys on the thumb cluster, or have broken off a column, this layout will not work!

---

## Features
- **Dvorak:** So you don't have to leave the home row so much.
- **Qwerty:** So you don't have to remap common programs.
- **Custom FPS gaming layer:** Because the WASD stagger is so extreme on the Kyria.
- **A number layer:** To access numbers, symbols and volume controls.
- **Index Layer:** To help navigate thru base layers without wasting accessible keys.
- And a very *very* rare **fren** to tag along on your adventures.

## Guiding ideology
- Use lower thumb keys as much as possible.
- Minimise home row departure.
- Minimize or eliminate non home row pinkie finger use.
- Create macros for very common key shortcuts (ctrl + c/v/s, ctrl+shift+home etc.).
- Create macros for very common commands (git status, git pull, git push etc.).
- Use hints to indicate current layer (rgb lighting/OLED display).
- Allow graceful layer handling (emergency return to default layer/layer index layer).
---


# Current Layers
- Base1: dvorak
- Base2: qwerty
- Base3: Gaming layer (WASD is too staggered on Kyria)
- MO layer: Number, Symbol & volume control layer

## Future Layers

- F keys
- FE macros
- Git macros

---


# Issues
### Major
- [x] None

### Minor
- [ ] Backlight LEDs dont indicate layer
- [ ] Not fully using thumb clusters
- [ ] Function keys and indicators missing (NUM, CAPS, SCROLL)
- [ ] No Macro layers

---

# Helpful Links

- QMK Docs https://docs.qmk.fm/#/
- [Keymap diagram editor for the Kyria](http://www.keyboard-layout-editor.com/##@_name=Kyria%3B&@_y:0.25&x:3&a:7%3B&=&_x:9%3B&=%3B&@_y:-0.75&x:2%3B&=&_x:1%3B&=&_x:7%3B&=&_x:1%3B&=%3B&@_y:-0.875&x:5%3B&=&_x:5%3B&=%3B&@_y:-0.625%3B&=&=&_x:13%3B&=&=%3B&@_y:-0.75&x:3%3B&=&_x:9%3B&=%3B&@_y:-0.75&x:2%3B&=&_x:1%3B&=&_x:7%3B&=&_x:1%3B&=%3B&@_y:-0.875&x:5%3B&=&_x:5%3B&=%3B&@_y:-0.625%3B&=&=&_x:13%3B&=&=%3B&@_y:-0.75&x:3%3B&=&_x:9%3B&=%3B&@_y:-0.75&x:2%3B&=&_x:1%3B&=&_x:7%3B&=&_x:1%3B&=%3B&@_y:-0.875&x:5%3B&=&_x:5%3B&=%3B&@_y:-0.625%3B&=&=&_x:13%3B&=&=%3B&@_y:-0.5&x:2.5%3B&=&_x:10%3B&=%3B&@_rx:4&ry:8.175&y:-4.675000000000001&x:-0.5%3B&=%3B&@_rx:13&y:-4.675000000000001&x:-0.5%3B&=%3B&@_r:15&rx:4&y:-4.675000000000001&x:-0.5%3B&=%3B&@_r:30&y:-2&x:-0.5%3B&=%3B&@_x:-0.5%3B&=%3B&@_r:45&y:-2&x:-0.5%3B&=%3B&@_x:-0.5%3B&=%3B&@_r:-45&rx:13&y:-5.675000000000001&x:-0.5%3B&=%3B&@_x:-0.5%3B&=%3B&@_r:-30&y:-2&x:-0.5%3B&=%3B&@_x:-0.5%3B&=%3B&@_r:-15&y:-1&x:-0.5%3B&=)
- [Thomas' Guide for creating OLED images](https://docs.splitkb.com/hc/en-us/articles/360013811280)
- [Image converter](https://javl.github.io/image2cpp/)

---

## Useful notes
Various useful info for setting up your own keyboard layout.

### Install QMK Tool steps
[QMK Setup (Windows)](https://docs.qmk.fm/#/newbs_getting_started)
- Install QMK MSYS,
- Install Toolbox,
- Using QMK MSYS, follow the setup guide, then `cd` to where you've cloned the `qmk_firmware` folder,
- `qmk compile` to generate your .hex file (it should be located in the `qmk_firmware` folder),
- Using QMK Toolbox, flash the .hex file to your keyboard halves (drag your hex file into the toolbox window, press the reset button on the keyboard, the toolbox should detect this, then press flash. You need to reset each half separately).
- Congrats, all done!


---
### Layer template
```
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
```

