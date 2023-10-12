# m65

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

For rev5

    qmk compile -kb mlego/m65/rev5 -km default

Flashing example for this keyboard:

    qmk flash -kb mlego/m65/rev5 -km default

To enter flashing mode, press in the same time, LWR+RSE+r, alternatively when you plug the keyboard on microcontroller keep pressed BOOT then release. Mount the usb disk that appears


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
| LWR    | B12 |
| CAPS_LOCK   | C13 |
| RSE | B13 |
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
| LWR    | B12 |
| CAPS_LOCK   | B2  |
| RSE | B13 |
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
| LWR    | B12 |
| CAPS_LOCK   | C13 |
| RSE | B13 |
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
| LWR    | B12 |
| CAPS_LOCK   | C13 |
| RSE | B13 |
| RBG_DI      | B15 |


## Pins and leds rev5 rp2040 pico

the pinout is the same for stm32f411

| Rows  | C0    | C1    | C2    | C3    | C4    | C5    | C6    | C7    | C8    | C9    | C10   | C11   | C12   | Pins  |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| R0    | Esc   | 1     | 2     | 3     | 4     | 5     | 6     | 7     | 8     | 9     | 0     | -     | Bksp  | GP22  |
| R1    | Tab   | q     | w     | e     | r     | t     | y     | u     | i     | o     | p     | [     | ]     | GP16  |
| R2    | #     | a     | s     | d     | f     | g     | h     | j     | k     | l     | ;     | '     | Enter | GP18  |
| R3    | Shift | \     | z     | x     | c     | v     | b     | n     | m     | ,     | .     | Up    | /     | GP19  |
| R4    | Ctrl  | Menu  | Lower | Alt   | Raise | Space | Space | Space | AltGr | Shift | Left  | Down  | Right | GP20  |
|       | B14   | A8    | A10   | A15   | B3    | B4    | B5    | B7    | A1    | A2    | A3    | A4    | B1    |       |
|       | GP1   | GP6   | GP7   | GP8   | GP9   | GP15  | GP14  | GP13  | GP12  | GP11  | GP10  | GP17  | GP21  |

### Encoders

  - Pad_A: GP4
  - Pad_B: GP5

### Oled

  - SDA: GP2
  - SCL: GP3

### LEDS

| Leds        | Pin |
| ----------- | --- |
| LWR         | GP28 |
| CAPS_LOCK   | GP25 |
| RSE         | GP27 |
| RBG_DI      | GP0 |


