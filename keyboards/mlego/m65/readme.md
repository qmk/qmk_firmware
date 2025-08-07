# M65

![M65](https://i.imgur.com/gXuecush.jpg)

A  (13x5) ortholinear keyboard that can be hand wired or using a pcb.

* Keyboard Maintainer: [Alin Elena](https://github.com/alinelena) ([@drFaustroll on GitLab](https://gitlab.com/drFaustroll))
* Hardware Supported: custom pcb [see](https://gitlab.com/m-lego/m65) STM/APM32F103C8T6, aka Black Pill (rev1),
  GD32F303CCT6 from we act aka Blue Pill Plus (rev2), STM32F401 from we act (rev3,rev4) STM32F411 can also be used just ask
* Hardware Availability: [custom how to](https://mlego.elena.space/m65)


Make example for this keyboard (after setting up your build environment):

For rev1

    make mlego/m65/rev1:default

Flashing example for this keyboard:

    make mlego/m65/rev1:default:flash

To enter flashing mode, press Lower+Raise+R.

For rev2

    make mlego/m65/rev2:default

Flashing example for this keyboard:

    make mlego/m65/rev2:default:flash

To enter flashing mode, on microcontroller keep pressed KEY and then NRST, release NRST and then after 1s release KEY.

For rev3

    make mlego/m65/rev3:default

Flashing example for this keyboard:

    make mlego/m65/rev3:default:flash

To enter flashing mode, on microcontroller keep pressed BOOT0 and then NRST, release NRST and then after 0.5s or so  release BOOT0.

For rev4

    make mlego/m65/rev4:default

Flashing example for this keyboard:

    make mlego/m65/rev4:default:flash

To enter flashing mode, press in the same time, LWR+RSE+r, alternatively on microcontroller keep pressed BOOT0 and then NRST, release NRST and then after 0.5s or so  release BOOT0.



See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Pins and leds rev1 STM/APM32F103C8T6

similar pinout for STM32F303

| Rows  | C0    | C1    | C2    | C3    | C4    | C5    | C6    | C7    | C8    | C9    | C10   | C11   | C12   | Pins  |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| R0    | Esc   | 1     | 2     | 3     | 4     | 5     | 6     | 7     | 8     | 9     | 0     | -     | Bksp  | B11   |
| R1    | Tab   | q     | w     | e     | r     | t     | y     | u     | i     | o     | p     | [     | ]     | B0    |
| R2    | #     | a     | s     | d     | f     | g     | h     | j     | k     | l     | ;     | '     | Enter | B1    |
| R3    | Shift | \     | z     | x     | c     | v     | b     | n     | m     | ,     | .     | Up    | /     | A2    |
| R4    | Ctrl  | Menu  | Lower | Alt   | Raise | Space | Space | Space | AltGr | Shift | Left  | Down  | Right | A3    |
|       | A10   | A15   | B3    | B4    | B5    | B9    | B8    | B7    | B6    | C15   | A0    | A7    | B10   |       |

### Encoders

  - Pad_A: A8
  - Pad_B: A9

### Leds

| Leds        | Pin |
| ----------- | --- |
| NUM_LOCK    | B12 |
| CAPS_LOCK   | C13 |
| SCROLL_LOCK | B13 |
| RBG_DI      | B15 |

## Pins and leds rev2 GD32F303CCT6


| Rows  | C0    | C1    | C2    | C3    | C4    | C5    | C6    | C7    | C8    | C9    | C10   | C11   | C12   | Pins  |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| R0    | Esc   | 1     | 2     | 3     | 4     | 5     | 6     | 7     | 8     | 9     | 0     | -     | Bksp  | B11   |
| R1    | Tab   | q     | w     | e     | r     | t     | y     | u     | i     | o     | p     | [     | ]     | B0    |
| R2    | #     | a     | s     | d     | f     | g     | h     | j     | k     | l     | ;     | '     | Enter | B1    |
| R3    | Shift | \     | z     | x     | c     | v     | b     | n     | m     | ,     | .     | Up    | /     | A2    |
| R4    | Ctrl  | Menu  | Lower | Alt   | Raise | Space | Space | Space | AltGr | Shift | Left  | Down  | Right | A3    |
|       | A10   | A15   | B3    | B4    | B5    | B9    | B8    | B7    | B6    | C15   | A0    | A7    | B10   |       |


### Encoders

  - Pad_A: A8
  - Pad_B: A9

### Leds

| Leds        | Pin |
| ----------- | --- |
| NUM_LOCK    | B12 |
| CAPS_LOCK   | B2  |
| SCROLL_LOCK | B13 |
| RBG_DI      | B15 |


## Pins and leds rev3 stm32f401

the pinout is the same for stm32f411

| Rows  | C0    | C1    | C2    | C3    | C4    | C5    | C6    | C7    | C8    | C9    | C10   | C11   | C12   | Pins  |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| R0    | Esc   | 1     | 2     | 3     | 4     | 5     | 6     | 7     | 8     | 9     | 0     | -     | Bksp  | B10   |
| R1    | Tab   | q     | w     | e     | r     | t     | y     | u     | i     | o     | p     | [     | ]     | A5    |
| R2    | #     | a     | s     | d     | f     | g     | h     | j     | k     | l     | ;     | '     | Enter | A6    |
| R3    | Shift | \     | z     | x     | c     | v     | b     | n     | m     | ,     | .     | Up    | /     | A7    |
| R4    | Ctrl  | Menu  | Lower | Alt   | Raise | Space | Space | Space | AltGr | Shift | Left  | Down  | Right | B0    |
|       | A10   | A15   | B3    | B4    | B5    | B9    | B8    | B7    | A1    | A2    | A3    | A4    | B1    |       |

### Encoders

  - Pad_A: A0
  - Pad_B: B6

### LEDS

| Leds        | Pin |
| ----------- | --- |
| NUM_LOCK    | B12 |
| CAPS_LOCK   | C13 |
| SCROLL_LOCK | B13 |
| RBG_DI      | B15 |

## Pins and leds rev4 stm32f401

the pinout is the same for stm32f411

| Rows  | C0    | C1    | C2    | C3    | C4    | C5    | C6    | C7    | C8    | C9    | C10   | C11   | C12   | Pins  |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| R0    | Esc   | 1     | 2     | 3     | 4     | 5     | 6     | 7     | 8     | 9     | 0     | -     | Bksp  | B10   |
| R1    | Tab   | q     | w     | e     | r     | t     | y     | u     | i     | o     | p     | [     | ]     | A5    |
| R2    | #     | a     | s     | d     | f     | g     | h     | j     | k     | l     | ;     | '     | Enter | A6    |
| R3    | Shift | \     | z     | x     | c     | v     | b     | n     | m     | ,     | .     | Up    | /     | A7    |
| R4    | Ctrl  | Menu  | Lower | Alt   | Raise | Space | Space | Space | AltGr | Shift | Left  | Down  | Right | B0    |
|       | B14   | A8    | A10   | A15   | B3    | B4    | B5    | B7    | A1    | A2    | A3    | A4    | B1    |       |

### Encoders

  - Pad_A: A0
  - Pad_B: B6

### Oled

  - SDA: B9
  - SCL: B8

### LEDS

| Leds        | Pin |
| ----------- | --- |
| NUM_LOCK    | B12 |
| CAPS_LOCK   | C13 |
| SCROLL_LOCK | B13 |
| RBG_DI      | B15 |

