# M60 split

![M60](https://i.imgur.com/3QfVLFRh.jpg)

A  (12x5) ortholinear split keyboard that can be hand wired or using a pcb.

* Keyboard Maintainer: [Alin Elena](https://github.com/alinelena) ([@drFaustroll on GitLab](https://gitlab.com/drFaustroll))
* Hardware Supported: custom pcb [see](https://gitlab.com/m-lego/m60_split) STM32F401 from we act (rev1)
* Hardware Availability: [custom how to](https://gitlab.com/m-lego/m60_split)


Make example for this keyboard (after setting up your uild environment):

    make mlego/m60_split/rev1:default

Flashing example for this keyboard:

    make mlego/m60_split/rev1:default

To enter flashing mode, press Lower+Raise+1 or Lower+Raise+0 also on microcontroller keep pressed BOOT0 and then NRST, release NRST and then after 0.5s or so  release BOOT0.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## pins and leds rev1 and rev2

### left

| Rows  | C0    | C1    | C2    | C3    | C4    | C5    | Pins  |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| R0    |  `    | 1     | 2     | 3     | 4     | 5     |   B0  |
| R1    | Tab   | q     | w     | e     | r     | t     |   A6  |
| R2    | Esc   | a     | s     | d     | f     | g     |   A7  |
| R3    | Shift | z     | x     | c     | v     | b     |   B1  |
| R4    | Ctrl  | Menu  | Alt   | Fn    | Lower | Space |   A5  |
| Pins  | B14   | A10   | A15   | B3    | B4    | B5    |       |

### right

| Rows  | C6    | C7    | C8    | C9    | C10   | C11   | Pins  |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| R0    | 6     | 7     | 8     | 9     | 0     | BSpace|   B1  |
| R1    | y     | u     | i     | o     | p     | Del   |   A4  |
| R2    | h     | j     | k     | l     | ;     | '     |   A5  |
| R3    | n     | m     | ,     | .     | /     | Enter |   A6  |
| R4    | Space | Raise | Left  | Down  | Up    | Right |   A7  |
| Pins  | B5    | A7    | A1    | A2    | A3    |  B0   |       |

### Encoders:

  - Pad_A: A0
  - Pad_B: B8

### Leds

| Leds        | Pin |
| ----------- | --- |
| NUM_LOCK    | B12 |
| CAPS_LOCK   | C13 |
| SCROLL_LOCK | B13 |
| RBG_DI      | B15 |

### split pins

|                     | Pin  |
| ------------------- | ---- |
| SPLIT_HAND_PIN      |  B9  |
| SERIAL_USART_TX_PIN |  B6  |
