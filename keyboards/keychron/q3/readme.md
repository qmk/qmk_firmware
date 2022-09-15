# Keychron Q3

A customizable 80% keyboard.

* Keyboard Maintainer: [Keychron](https://github.com/keychron)
* Hardware Supported: Keychron Q3
* Hardware Availability: [Keychron](https://www.keychron.com)

Make example for this keyboard (after setting up your build environment):

- **rev_0120** is for Q3 ansi version, you can compile rev_0120 default keymap by using:

```
  make keychron/q3/rev_0120:default
```

- **rev_0121** is for Q3 ansi version with knob(encoder), you can compile rev_0121 default keymap by using:

```
  make keychron/q3/rev_0121:default
```

- **rev_0122** is for Q3 iso version, you can compile default rev_0122 keymap by using:

```
  make keychron/q3/rev_0122:default
```

- **rev_0123** is for Q3 iso version with knob(encoder), you can compile rev_0123 default keymap by using:

```
  make keychron/q3/rev_0123:default
```

- **rev_0124** is for Q3 jis version, you can compile rev_0124 default keymap by using:

```
  make keychron/q3/rev_0124:default
```

- **rev_0125** is for Q3 jis version with knob(encoder), you can compile rev_0125 default keymap by using:

```
make keychron/q3/rev_0125:default
```

Flashing example for this keyboard:

- Put the keyboard into DFU/IAP mode by unplugging the keyboard, then holding the reset key while plugging it back in.
- Run QMK Toolbox and flash the keyboard with the firmware you just built or just through command line by using:

```
  make keychron/q3/rev_0120:default:flash
  make keychron/q3/rev_0121:default:flash
  make keychron/q3/rev_0122:default:flash
  make keychron/q3/rev_0123:default:flash
  make keychron/q3/rev_0124:default:flash
  make keychron/q3/rev_0125:default:flash
```

**Reset Key**: Hold down the key located at *K00*, commonly programmed as *Esc* while plugging in the keyboard.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
