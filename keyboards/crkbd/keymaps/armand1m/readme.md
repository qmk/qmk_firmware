# armand1m crkbd layout

This is the personal layout for [@armand1m](https://go.d1m.dev/github)

This layout is heavily inspired in my personal Moonlander layout, optimized for my own personal usage.

As of the date of this writing, my environment runs OS X Big Sur with yabai and skhd to provide an window tiling management experience similar to what i3wm offers to Linux, which means that I often use the `alt` keys.

I am a huge fan of ModTaps, so this layout will contain some of those to allow for a better experience in such a small keyboard like the crkbd.

## Layout

You can find `json` files for http://www.keyboard-layout-editor.com/ in the keymap folder.

Here are some screenshots for convenience:

Base Layer:<br/>
<a href="https://ibb.co/fYZw3yj"><img src="https://i.ibb.co/0j1b06H/Screen-Shot-2021-03-15-at-4-58-43-PM.png" alt="Base Layer" border="0"></a>

Numbers Layer:<br/>
<a href="https://ibb.co/30Vg1tS"><img src="https://i.ibb.co/hKr3sp2/Screen-Shot-2021-03-15-at-5-18-07-PM.png" alt="Numbers Layer" border="0"></a>

Symbols Layer:<br/>
<a href="https://ibb.co/ryCg4pS"><img src="https://i.ibb.co/q1tzkgf/Screen-Shot-2021-03-15-at-5-18-33-PM.png" alt="Symbols Layer" border="0"></a>

## Choices

Every keymap is pretty unique and tailored to suit it's main creators needs. Here are some of my choices for the keys and their explanations:

 - Left thumb acts as Space when tapping but as Command when holding: this makes my life so much easier in OS X. Having command reachable all the time just feels right to me and Mod Taps help me a lot on this.

 - Right thumb acts as Enter when tapping but as Right Shift when holding: this is more of an experiment. I usually use shift on my pinkies. It is an interesting feature but I often forget about it.

 - Esc lives in the home row, before A. It also acts as a layer toggle to the numbers layer when held. Having the LT to the numbers layer here allows me to actually reach the number 1 pretty nicely and other numbers on the left hand pretty easily.

 - Keys on the home row are used to switch to layers, so "A" goes to layer 2 when held. I started making this in the Moonlander and migrated the practice, but still sometimes I use the MO 2 on the right thumb.

 - One Shot Keys are enabled for the shifts on the pinkies. If you press it twice: it will lock on shift until pressed again (pretty much like caps lock). These are handy when you're typing and just don't want to hold shift to have a capitalized word.

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
