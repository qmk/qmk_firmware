# M60

![M60](https://i.imgur.com/Zm7LaHih.jpg)

A  (12x5) ortholinear keyboard that can be hand wired or using a pcb.

* Keyboard Maintainer: [Alin Elena](https://github.com/alinelena) ([@drFaustroll on GitLab](https://gitlab.com/drFaustroll))
* Hardware Supported: custom pcb [see](https://gitlab.com/drFaustroll/m60) STM32F401 from we act (rev1)
* Hardware Availability: [custom how to](https://gitlab.com/drFaustroll/m65)


Make example for this keyboard (after setting up your build environment):

    make mlego/m60/rev1:default

Flashing example for this keyboard:

    make mlego/m60/rev1:default

To enter flashing mode, press Lower+Raise also on microcontroller keep pressed BOOT0 and then NRST, release NRST and then after 0.5s or so  release BOOT0.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Layout and pins stm32f401

similar for stm32f411

| Rows  | C0    | C1    | C2    | C3    | C4    | C5    | C6    | C7    | C8    | C9    | C10   | C11   | Pins  |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| R0    | Esc   | 1     | 2     | 3     | 4     | 5     | 6     | 7     | 8     | 9     | 0     | BSpace|   A6  |
| R1    | Tab   | q     | w     | e     | r     | t     | y     | u     | i     | o     | p     | Del   |   A7  |
| R2    | #     | a     | s     | d     | f     | g     | h     | j     | k     | l     | ;     | '     |   B0  |
| R3    | Shift | z     | x     | c     | v     | b     | n     | m     | ,     | .     | /     | Enter |   B1  |
| R4    | Ctrl  | Menu  | Alt   | Fn    | Lower | Space | Space | Raise | Left  | Down  | Up    | Right |  B10  |
| Pins  | A10   | A15   | B3    | B4    | B5    | B7    | B6    | A1    | A2    | A3    | A4    |  A5   |       |

### Encoders:

  - Pad_A: A0
  - Pad_B: B8

### Leds

| Leds        | Pin |
| ----------- | --- |
| NUM_LOCK    | B12 |
| CAPS_LOCK   | C13 |
| SCROLL_LOCK | B13 |
| RBG_dI      | B15 |
