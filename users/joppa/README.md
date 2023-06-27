# joppa

All my keyboard collected in one userspace. 



## The joppa layout

The layout is inspired by [Miryoku](https://github.com/manna-harbour/miryoku_qmk/tree/miryoku/users/manna-harbour_miryoku) keyboard layout, but there are quite differences. I admit that I have stolen much of his setup, because it is so vel suited to support a bunce of keyboards.

## Your keyboard

If you want to use this keymap yourself, here are the instructions to use it. It is easier with an example. Example with the "Lets'split" keyboard.



Check out what keymap layout your keyboard is using. Let's say that you want to use the "Lets'split" keyboard. Check in the `keymap.c` file, in the `default` layout  for your keyboard --> `.../qmk_firmware/keyboards/lets_split/keymaps/default/keymap.c` when looking in this file, we can see that the name of the layout is `LAYOUT_ortho_4x12`.



Look in the folder for community layouts(`.../qmk_firmware/layouts/community/`), to see if you can find your layout (`LAYOUT_ortho_4x12`). It's found in folder `.../qmk_firmware/layouts/community/ortho_4x12/`



If you have found a folder called `.../qmk_firmware/layouts/community/ortho_4x12/joppa` for your keyboard layout then you are ready to go. If not, then you have to copy the folder `.../qmk_firmware/layouts/community/ortho_4x12/manna-harbour_miryoku/` and rename it to `.../qmk_firmware/layouts/community/ortho_4x12/joppa/`.



Now you could be ready to flash your keyboard. Flashing is done with the instruction on Miryoku website. [Find your Keyboard on the page]([miryoku_qmk/users/manna-harbour_miryoku at miryoku · manna-harbour/miryoku_qmk · GitHub](https://github.com/manna-harbour/miryoku_qmk/tree/miryoku/users/manna-harbour_miryoku)). When your keyboard is found. you could replace `manna-harbour_miryoku` with `joppa` . Here is the [description to flash the Lets'split keyboard]([miryoku_qmk/users/manna-harbour_miryoku at miryoku · manna-harbour/miryoku_qmk · GitHub](https://github.com/manna-harbour/miryoku_qmk/tree/miryoku/users/manna-harbour_miryoku#ortho_4x12)):

```bash
make lets_split:manna-harbour_miryoku:\
    MIRYOKU_MAPPING=SPLIT \
    MIRYOKU_ALPHAS=QWERTY \
    MIRYOKU_NAV=VI \
    MIRYOKU_CLIPBOARD=WIN
```

Here under is the modified version of this command you could use. All the options could work except `MIRYOKU_ALPHAS` this could always be `QWERTY` . my layout has only support for `QWERTY` :

```bash
make lets_split:joppa:\
    MIRYOKU_MAPPING=SPLIT \
    MIRYOKU_ALPHAS=QWERTY \
    MIRYOKU_NAV=VI \
    MIRYOKU_CLIPBOARD=WIN
```



## My keyboards

### [ Lets'split](https://falba.tech/product/lets-split-standard-lift-bamboo-wood-case-with-oil-finish/)

Follow instructions over, in the [Your keyboard](#your-keyboard) section to flash. There are different layouts. I find the layout above most attractive.  My operating system is Windows



### [Dactyl manuform 3x5_3](https://www.dlford.io/keyboard-build-guide-per-key-rgb-leds/)

This is a hardwired keyboard witch is built on [instructions on these page](https://www.dlford.io/keyboard-build-guide-per-key-rgb-leds/). My keyboard is without LED lightening. The communication between the halves is serial, set up as [this](https://github.com/qmk/qmk_firmware/blob/master/keyboards/handwired/dactyl_manuform/readme.md#wiring).

#### Flashing trouble

Trouble when flashing the keyboard. All keys are dead if these criteria's is not met:

A litle tweak has to be done in this file

[.../qmk_firmware/keyboards/handwired/dactyl_manuform/3x5_3
/info.json]([qmk_firmware/keyboards/handwired/dactyl_manuform/3x5_3/info.json at master · qmk/qmk_firmware · GitHub](https://github.com/qmk/qmk_firmware/blob/master/keyboards/handwired/dactyl_manuform/3x5_3/info.json)). The property `diode_direction`. has to be set to `COL2ROW` instead of `ROW2COL`.

```json
    "diode_direction": "COL2ROW",
```

In the file [.../qmk_firmware/users/joppa/rules.mk](https://github.com/qmk/qmk_firmware/blob/master/users/joppa/rules.mk), these lines of config must be present:

```bash
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
RGB_MATRIX_ENABLE = no     # Enable WS2812 RGB matrix
RGBLIGHT_SUPPORTED = no
RGB_MATRIX_SUPPORTED = no
```



The instructions in section [Your keyboard](#your-keyboard) is folowe



[setup environment like this description](https://filterpaper.github.io/qmk/userspace.html?utm_source=pocket_mylist)

I have 2 different keyboards to maintain. `Lets'split` and a handmade `Dactyl manuform 3x5_3`

This is a attemt to collect all my keyboards in one userspace

- .../qmk_firmware/users/craftsmandigital

## Lets'split

This keyboard config is located here:

- https://github.com/craftsmandigital/manna-harbour_miryoku

## Dactyl manuform 3x5_3

This keyboard does not have a repo on gitub yet, but some related info is in this repo:

- https://github.com/craftsmandigital/3x5_3