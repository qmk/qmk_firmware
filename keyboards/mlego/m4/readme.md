# M4

![M4](https://i.imgur.com/1rrREGY.jpg)

A  (2x2) ortholinear keyboard that can be hand wired or using a pcb.

* Keyboard Maintainer: [Alin Elena](https://github.com/alinelena) ([@drFaustroll on GitLab](https://gitlab.com/drFaustroll))
* Hardware Supported: custom pcb [see](https://mlego.elena.space/m4/ seeeduino xiao rp2040, rev2)
* Hardware Availability: [custom how to](https://mlego.elena.space)


Make example for this keyboard (after setting up your build environment):

    make mlego/m4/rev2:default

Flashing example for this keyboard:

    make mlego/m4/rev2:default

To enter flashing mode, press Lower+Raise+2  also on microcontroller keep pressed BOOT with mcu unpowered and then power, release BOOT after 1-2s. device will appear as a mass storage device and copy the uf2

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


## Pins for rev2

| Rows  | C0    | C1    |  Pins  |
| :---: | :---: | :---: |  :---: |
| R0    |   1   |   2   | D0-GP26|
| R1    | Lwr   | Rse   | D3-GP29|
| Pins  |SR1-QA |SR2-QA |        |

SRx - shift register x

### Encoders:

  - Pad_A: D1 - GP27
  - Pad_B: D2 - GP28

### Oled

  - SDA: D4-GP6
  - SCL: D5-GP7

### 74HC595

  - data:  D10 - GP3
  - latch: D7  - GP1
  = clock: D8  - GP2

### Leds

| Leds        |   Pin |
| ----------- |   --- |
| NUM_LOCK    |  GP17 |
| CAPS_LOCK   |  GP25 |
| SCROLL_LOCK |  GP16 |
| RBG_DI      |  GP12 |

rgb power on GP11
