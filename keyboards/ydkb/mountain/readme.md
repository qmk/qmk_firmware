# ydkb/mountain

![ydkb/mountain](https://i.imgur.com/wUxh5Cfh.jpg)

An ergo keyboard designed by Wei and sold by [KBDfans](https://kbdfans.com)

-   Keyboard Maintainer: [Wraul](https://github.com/Wraul)
-   Hardware Supported: The YDKB compatible PCB provided as part of the initial
    batch sold by KBDfans.
    initial batch. It is most likely also compatible with the hot-swappable PCB,
    but this is unverified.
-   Hardware Availability: [KBDfans](https://kbdfans.com/products/ic-kbdfans-mountain-ergo-keyboard-kit)

Make example for this keyboard (after setting up your build environment):

    make ydkb/mountain:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

The keyboard comes with a custom Mass Storage Device bootloader and a TMK based firmware from [ydkb.io](https://ydkb.io/).
Some more information about the bootloader can be found in the [YDKB
documentation](https://ydkb.io/help/#/en/bootloader/msd-bootloader).

Enter the bootloader in 3 ways:

-   **Bootmagic reset**: Hold down the escape key and plug in the keyboard
-   **Physical reset button**: The PCB does not have a physical reset button,
    but it is possible to short the GND and RESET manually. The pins are mapped
    to two of the unsoldered pads on the controller PCB
-   **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

### Flashing on Linux

Flashing a firmware can be done on Linux by entering the bootloader and using
`dd` as described below.

The storage device can differ between systems, so make sure to specify the correct device.
To list available devices `lsblk` can be used.

```
dd if=./ydkb_mountain_{LAYOUT}.bin of=/dev/sd{X} seek=4 && sync
```

When flashing using this method I have at multiple times encountered some form
of corruption. Once this happens, further flash attempts will silently fail.

I was able to fix the corruption by switching to Windows and doing the flash using
the file explorer. Make sure to first remove the existing `.bin` file before
adding the new firmware file to the mounted drive.

## Matrix

The matrix of this keyboard is a bit unusual. Not only is the PCB split into two
halves, it uses multiple 74HC595 bit shift registers to scan each key
individually.

The 74HC595 bit shift registers appears to be some kind of off-brand version
that uses open-drain outputs instead of the expected push-pull output.

The chips are marked with the following

```
SM74HC595A
BRAFUJDB13
```

### Pins

The following two pins are used to control the 74HC595 bit shift registers.

| ATmega Pin | 74HC595 Pin |
| ---------- | ----------- |
| `B1`       | `SRCLK`     |
| `B3`       | `SER`       |

The following two pins are used to read the state of the matrix.

| ATmega Pin | Function   |
| ---------- | ---------- |
| `B2`       | Right half |
| `B3`       | Left half  |

As shown above the pin `B3` is used both to control the 74HC595 and to read the
state of the matrix. Thus it has to be switch between output and input modes
between the two phases.

### 74HC595 Bit Shift Registers

The PCB uses two banks of 74HC595 bit shift registers. The two banks are set up
in parallel.

#### Bank U1

Bank U1 is responsible for the left half of the board.
This bank consists of 4 74HC595 chips for a total of 32 bits.

The chips are linked in the following order

`U10 -> U11 -> U12 -> U13`

##### U10

| Chip Bit | Bank Bit | Key |
| -------- | -------- | --- |
| 0        | 0        | Esc |
| 1        | 1        | 1   |
| 2        | 2        | 2   |
| 3        | 3        | 3   |
| 4        | 4        | 4   |
| 5        | 5        | 5   |
| 6        | 6        | 6   |
| 7        | 7        | Tab |

##### U11

| Chip Bit | Bank Bit | Key  |
| -------- | -------- | ---- |
| 0        | 8        | Q    |
| 1        | 9        | W    |
| 2        | 10       | E    |
| 3        | 11       | R    |
| 4        | 12       | T    |
| 5        | 13       | G    |
| 6        | 14       | F    |
| 7        | 15       | Caps |

##### U12

| Chip Bit | Bank Bit | Key   |
| -------- | -------- | ----- |
| 0        | 16       | A     |
| 1        | 17       | S     |
| 2        | 18       | D     |
| 3        | 19       | B     |
| 4        | 20       | V     |
| 5        | 21       | C     |
| 6        | 22       | X     |
| 7        | 23       | Shift |

##### U13

| Chip Bit | Bank Bit | Key  |
| -------- | -------- | ---- |
| 0        | 24       |      |
| 1        | 25       | Z    |
| 2        | 26       |      |
| 3        | 27       | LFn2 |
| 4        | 28       | LFn1 |
| 5        | 29       | Alt  |
| 6        | 30       |      |
| 7        | 31       | Ctrl |

#### Bank U2

Bank U2 is responsible for the right half of the board.
This bank consists of 5 74HC595 chips for a total of 40 bits.

The chips are linked in the following order

`U24 -> U23 -> U22 -> U21 -> U20`

##### U24

| Chip Bit | Bank Bit | Key   |
| -------- | -------- | ----- |
| 0        | 0        | RCtrl |
| 1        | 1        |       |
| 2        | 2        | Space |
| 3        | 3        | RAlt  |
| 4        | 4        | RWin  |
| 5        | 5        |       |
| 6        | 6        | Menu  |
| 7        | 7        |       |

##### U23

| Chip Bit | Bank Bit | Key    |
| -------- | -------- | ------ |
| 0        | 8        | Fn     |
| 1        | 9        | b      |
| 2        | 10       | N      |
| 3        | 11       | M      |
| 4        | 12       | ,<     |
| 5        | 13       | .>     |
| 6        | 14       | /?     |
| 7        | 15       | RShift |

##### U22

| Chip Bit | Bank Bit | Key   |
| -------- | -------- | ----- |
| 0        | 16       | Enter |
| 1        | 17       | H     |
| 2        | 18       | J     |
| 3        | 19       | K     |
| 4        | 20       | L     |
| 5        | 21       | ;:    |
| 6        | 22       | '"    |
| 7        | 23       |       |

##### U21

| Chip Bit | Bank Bit | Key |
| -------- | -------- | --- |
| 0        | 24       | \   |
| 1        | 25       | Y   |
| 2        | 26       | U   |
| 3        | 27       | I   |
| 4        | 28       | O   |
| 5        | 29       | P   |
| 6        | 30       | [{  |
| 7        | 31       | ]}  |

##### U20

| Chip Bit | Bank Bit | Key |
| -------- | -------- | --- |
| 0        | 32       | BS  |
| 1        | 33       | 7   |
| 2        | 34       | 8   |
| 3        | 35       | 9   |
| 4        | 36       | 0   |
| 5        | 37       | -   |
| 6        | 38       | +   |
| 7        | 39       | BS2 |
