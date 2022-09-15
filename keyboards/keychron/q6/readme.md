# Keychron Q6

A customizable 100% keyboard.

* Keyboard Maintainer: [Keychron](https://github.com/keychron)
* Hardware Supported: Keychron Q6
* Hardware Availability: [Keychron](https://www.keychron.com)

Make example for this keyboard (after setting up your build environment):

- **rev_0160** is for Q6 ansi version, you can compile rev_0160 default keymap by using:

```
  make keychron/q6/rev_0160:default
```

- **rev_0161** is for Q6 ansi version with knob(encoder), you can compile rev_0161 default keymap by using:

```
  make keychron/q6/rev_0161:default
```

- **rev_0162** is for Q6 iso version, you can compile default rev_0162 keymap by using:

```
  make keychron/q6/rev_0162:default
```

- **rev_0163** is for Q6 iso version with knob(encoder), you can compile rev_0163 default keymap by using:

```
  make keychron/q6/rev_0163:default
```

Flashing example for this keyboard:

- Put the keyboard into DFU/IAP mode by unplugging the keyboard, then holding the reset key while plugging it back in.
- Run QMK Toolbox and flash the keyboard with the firmware you just built or just through command line by using:

```
  make keychron/q6/rev_0160:default:flash
  make keychron/q6/rev_0161:default:flash
  make keychron/q6/rev_0162:default:flash
  make keychron/q6/rev_0163:default:flash
```

**Reset Key**: Hold down the key located at *K00*, commonly programmed as *Esc* while plugging in the keyboard.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
