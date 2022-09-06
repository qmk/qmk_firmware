# Keychron Q5

A customizable 96% keyboard.

* Keyboard Maintainer: [Keychron](https://github.com/keychron)
* Hardware Supported: Keychron Q5
* Hardware Availability: [Keychron](https://www.keychron.com)

Make example for this keyboard (after setting up your build environment):

- **rev_0150** is ansi version of Q5, you can compile rev_0150 default keymap by using:

```makefile
  make keychron/q5/rev_0150:default
```

- **rev_0151** is ansi version and with encoder of Q5, you can compile rev_0151 default keymap by using:

```makefile
  make keychron/q5/rev_0151:default
```

- **rev_0152** is iso version of Q5, you can compile default rev_0152 keymap by using:

```makefile
  make keychron/q5/rev_0152:default
```

- **rev_0153** is iso version and with encoder of Q5, you can compile rev_0153 default keymap by using:

```makefile
  make keychron/q5/rev_0153:default
```

Flashing example for this keyboard:

- Put the keyboard into DFU/IAP mode by unplugging the keyboard, then holding the reset key while plugging it back in.
- Run QMK Toolbox and flash the keyboard with the firmware you just built or just through command line by using:

```makefile
  make keychron/q5/rev_0150:default:flash
  make keychron/q5/rev_0151:default:flash
  make keychron/q5/rev_0152:default:flash
  make keychron/q5/rev_0153:default:flash
```

**Reset Key**: Hold down the key located at *K00*, commonly programmed as *Esc* while plugging in the keyboard.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
