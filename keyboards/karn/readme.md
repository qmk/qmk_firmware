# Karn 2

Split, ortholinear, non-staggered, diodeless, 38 key keyboard, with a unique set of 1.5u thumb arc keys and 1.5u pinky reach keys. 

* Keyboard Maintainer: [Robert Mills](https://github.com/robcmills)
* Hardware Supported: Blackpill STM32F401

Based on the excellent [cantor](https://github.com/diepala/cantor), and inspired by the popular [corne](https://github.com/foostan/crkbd), [ferris](https://github.com/pierrechevalier83/ferris) and [sweep](https://github.com/davidphilipbarr/Sweep) keyboards.

![https://github.com/robcmills/karn-keyboard](https://github.com/robcmills/karn-keyboard)

![karn-2-left](https://github.com/robcmills/karn-keyboard/blob/main/images/karn-2-left.jpg)

![karn-2-full](https://github.com/robcmills/karn-keyboard/blob/main/images/karn-2-full.jpg)

![karn-2-pcb](https://github.com/robcmills/karn-keyboard/blob/main/images/karn-2-pcb.png)

The default keymap is designed for OSX.

```
 /* 
  *       ┌─────┬─────┬─────┬─────┬─────┐             ┌─────┬─────┬─────┬─────┬─────┐
  *       │  Q  │  W  │  F  │  P  │  G  │    BASE     │  J  │  L  │  U  │  Y  │  ;  │
  *       │     │     │     │     │     │    LAYER    │     │     │     │     │     │
  * ┌─────┼─────┼─────┼─────┼─────┼─────┤   ┌─────┐   ├─────┼─────┼─────┼─────┼─────┼─────┐
  * │ TAB │  A  │  R  │  S  │  T  │  D  │   │ TAP │   │  H  │  N  │  E  │  I  │  O  │ ENT │
  * │ HYP │     │     │     │     │     │   │ HOLD│   │     │     │     │     │     │ HYP │
  * └─────┼─────┼─────┼─────┼─────┼─────┤   └─────┘   ├─────┼─────┼─────┼─────┼─────┼─────┘
  *       │  Z  │  X  │  C  │  V  │  B  │             │  K  │  M  │  ,  │  .  │  /  │
  *       │ SFT │ CTL │ ALT │ CMD │     │             │     │ CMD │ ALT │ CTL │ SFT │
  *       └─────┴─────┴─────┼─────┼─────┼─────┐ ┌─────┼─────┼─────┼─────┴─────┴─────┘
  *                         │     │ ESC │     │ │ BAK │ SPC │     │
  *                         │ SYM │ SFT │ NUM │ │     │     │ NAV │
  *                         └─────┴─────┴─────┘ └─────┴─────┴─────┘
  *       ┌─────┬─────┬─────┬─────┬─────┐             ┌─────┬─────┬─────┬─────┬─────┐
  *       │  \  │  `  │  '  │  "  │  {  │     SYM     │  }  │  -  │  =  │  [  │  ]  │
  *       │     │     │     │     │     │    LAYER    │     │     │     │     │     │
  * ┌─────┼─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┼─────┐
  * │     │  !  │  @  │  #  │  $  │  %  │             │  ^  │  &  │  *  │  (  │  )  │     │
  * │     │     │     │     │     │     │             │     │     │     │     │     │     │
  * └─────┼─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┼─────┘
  *       │     │     │     │     │     │             │     │     │     │     │     │
  *       │     │     │     │     │     │             │     │     │     │     │     │
  *       └─────┴─────┴─────┼─────┼─────┼─────┐ ┌─────┼─────┼─────┼─────┴─────┴─────┘
  *                         │     │     │     │ │ DEL │     │     │
  *                         │     │     │     │ │     │     │     │
  *                         └─────┴─────┴─────┘ └─────┴─────┴─────┘
  *       ┌─────┬─────┬─────┬─────┬─────┐             ┌─────┬─────┬─────┬─────┬─────┐
  *       │     │     │     │     │ VOL │     NAV     │     │     │     │     │     │
  *       │     │     │     │     │ UP  │    LAYER    │     │     │     │     │     │
  * ┌─────┼─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┼─────┐
  * │     │ CTL │ CTL │ CMD │ CMD │ VOL │             │  ←  │  ↓  │  ↑  │  →  │CAPS │     │
  * │     │ + ↓ │ + ↑ │ + ` │ +TAB│ DOWN│             │     │     │     │     │LOCK │     │
  * └─────┼─────┼─────┼─────┼─────┼─────┤             ├─────┼─────┼─────┼─────┼─────┼─────┘
  *       │     │     │     │     │ MUTE│             │     │     │     │     │     │
  *       │     │     │     │     │     │             │     │     │     │     │     │
  *       └─────┴─────┴─────┼─────┼─────┼─────┐ ┌─────┼─────┼─────┼─────┴─────┴─────┘
  *                         │     │     │     │ │     │     │     │
  *                         │     │     │     │ │     │     │     │
  *                         └─────┴─────┴─────┘ └─────┴─────┴─────┘
  *       ┌─────┬─────┬─────┬─────┬─────┐             ┌─────┬─────┬─────┬─────┬─────┐
  *       │ F1  │ F2  │ F3  │ F4  │ F5  │     NUM     │ F6  │ F7  │ F8  │ F9  │ F10 │
  *       │ F11 │ F12 │     │     │     │    LAYER    │     │     │     │     │     │
  * ┌─────┼─────┼─────┼─────┼─────┼─────┤   ┌─────┐   ├─────┼─────┼─────┼─────┼─────┼─────┐
  * │     │  1  │  2  │  3  │  4  │  5  │   │ TAP │   │  6  │  7  │  8  │  9  │  0  │     │
  * │     │     │     │     │     │     │   │TAPx2│   │     │     │     │     │     │     │
  * └─────┼─────┼─────┼─────┼─────┼─────┤   └─────┘   ├─────┼─────┼─────┼─────┼─────┼─────┘
  *       │     │     │     │     │     │             │     │     │     │     │     │
  *       │     │     │     │     │     │             │     │     │     │     │     │
  *       └─────┴─────┴─────┼─────┼─────┼─────┐ ┌─────┼─────┼─────┼─────┴─────┴─────┘
  *                         │     │     │     │ │     │     │     │
  *                         │     │     │     │ │     │     │     │
  *                         └─────┴─────┴─────┘ └─────┴─────┴─────┘
  */
```

### Make

Make example for this keyboard (after setting up your build environment):

    make karn:default

Flashing example for this keyboard:

    make karn:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

### Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard. For the right side, hold the top right key and plug the keyboard.
* **Physical reset button**: 
  * Press and hold the BOOT0 button.
  * Press and release the NRST button.
  * Release the BOOT0 button.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

