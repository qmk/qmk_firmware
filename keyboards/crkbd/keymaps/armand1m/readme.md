# armand1m crkbd layout

This is the personal layout for [@armand1m](https://github.com/armand1m)

This layout is heavily inspired in my personal Moonlander layout, optimized for my own personal usage.

As of the date of this writing, my environment runs OS X Big Sur with yabai and skhd to provide an window tiling management experience similar to what i3wm offers to Linux, which means that I often use the `alt` keys.

I am a huge fan of ModTaps, so this layout will contain some of those to allow for a better experience in such a small keyboard like the crkbd.

## Usage

In case you have `qmk` installed:

```sh
qmk compile -kb crkbd -km armand1m
```

The compiled .hex file should be available in `qmk_firmware/.build`

You can also trigger a build and flash automatically by running the following command:

```sh
qmk flash -kb crkbd -km armand1m
```

If you built your crkbd with an Elite-C microcontroller, you probably want to use a DFU bootloader:

```sh
qmk flash -kb crkbd -km armand1m -bl dfu
```

## Credits

 - Armando Magalhaes [(github)](https://go.d1m.dev/github)
