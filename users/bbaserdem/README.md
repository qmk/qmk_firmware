# BBASERDEM userspace code for qmk

My userspace code for my various keyboards; available here.

# Todo

- [X] Add OLED support
- [ ] Centralize color definitions for RGB
- [ ] Document all features more extensibly
- [ ] Generate json files to be used with Keyboard-Layout-Editor to produce images.

# Keyboards

A list of my code accross the QMK repo accessible here.
(I will sell my built-but-not-using ones.)

## Builds

These are my keyboard builds and info, it allows me to plan out my builds. 

### Planck WORK

* Board: planck/rev6
* Switches: Zilent
* Case: Planck Hi-Pro Bottom Case: Glossy White
* Plate: Stainless steel with shiny finish (LaserBoost) 
* Keycaps: Pudding PBT Doubleshot Keycap Set
* Artisan: B.O.B StoneuCarved Lotus Artisan Keycap
* Artisan: Teamwolf 304 Stainless Steel Transparent Metal Keycaps

I use this at the workplace to not bother coworkers; focus on silence.

### Planck HOME

* Board: planck/rev6
* Switches: Crystal BOX Navy
* Case: Planck Hi-Pro Bottom Case (MOD version): Matte Black
* Plate: Copper with shiny finish (LaserBoost) 
* Keycaps: Buger TH01 XDA Dye-Subbed PBT
* Artisan: Sparkle Loft Reactor Artisan Keycap

I use this at home.
Has all the extra pinouts exposed to play arounh with.

### Planck SERVER

* Board: jj40
* Switches: BOX Navy
* Case: Clear Acrylic Top and Bottow, with Frosted Acrylic Diffuser (Smashing Acrylics)
* Keycaps: Datamancer Tall Deco Typewriter Keycaps

I'm using this while I'm in between boards; but very usable.
Long term plan is to use this for the server.
The case was initially designed for planck rev4;
I'm replaced the PCB since my rev4 one was derelict
due to repeated desolderings.

### Planck CARRY

* Board: planck/light
* Switches: Choc Low Jade
* Case: Stock Planck light case
* Keycaps: Blanck MKB

I carry this around; and is one of my favourite boards.
Found a better keycap profile for these as well.

### XD75RE

* Board: xd75
* Switches: Zealios 67g + Silencios
* Case: Npkc 60% Wooden Case (Rosewood)
* Keycaps: Massdrop x MITO XDA Godspeed
* Artisan: Hammer Fidget Spinner Artisan Keycap
* Artisan: Waffle Key Studio Rosette (Sunset)

My first work board; that is not seing any use due to being big.

### Gherkin PAD

* Board: 40percentclub/gherkin
* Case: Acrylic Case (Smashing Acrylics)
* Controller: Proton C
* Switches: Novelkeys Creams
* Keycaps: Random

The point of this is to act like a game/macro pad.
Other than that; i just use this for bragging points.
I have been planning on using my Proton C to turn into a MIDI controller.

### Let's Split Eh?

* Board: lets_split_eh/eh
* Case: Acrylic Case (Smashing Acrylics)
* Switches: Novelkeys BOX Royals 
* Keycaps: G20 Semiotics

I built this; but then I realized that I really don't enjoy ortholinear split.

### Infinity Ergodox

* Board: ergodox_infinity
* Case: Datamancer Wooden case
* Switches: Kailh Speed Gold
* Keycaps: None

I don't like Infinity Ergodox.
Should sell this soon cause really not seeing myself ever using this.
Lucky me got the case for free due to (then) Massdrop shipping errors.

### Corne

* Board: [Proton-C Compatible crkbd PCB](https://github.com/ItsWaffIe/waffle_corne)
* Case: IMK Corne Case v2 Polycarbonate
* Switches: Healios V2
* Keycaps: POM Jelly

I'm planning on adding a trackpad for this, as detailed
[here](https://github.com/manna-harbour/crkbd/blob/master/trackpoint/readme.org).

### Corne Lite

* Board: crkbd/rev1
* Case: Custom
* Switches: Choc Low Burnt Orange
* Keycaps: [Scooped Choc Keycaps](https://mkultra.click/collections/keycaps/products/scooped-choc-keycaps?variant=31223543365730)

### Kyria

* Board: kyria/rev1
* Case: Matte Black Acrylic High-Profile case
* Switches: Gateron Ink Silent Black
* Keycaps: Oblotzky SA Oblivion

Want to add a joystick to this board for mouse control.

### Big Switch

* Board: bigseries/1key
* Case: WoodKeys (KNOWN SCAMMER: DO NOT RECOMMEND)
* Switches: Big Series Pale Blue
* Keycaps: Idea23

Got this before being scammed out of 200$ by Cole Markham: owner of WoodKeys;
The usb port got torn off; and could not fix it.
Expensive paperweight?

# Firmware building

## Archlinux

On archlinux, the package *arm-none-eabi-gcc* is too new.
To fix; add to the environment `CFLAGS="-Wno-error=deprecated"` to compilation commands.
Also; try to run `avr-gcc` version `8.4.0` for smaller firmware.

## Bootloader

If I want to flash a new bootloader for a machine; here are steps;

1. Flash the util/pro_micro_ISP_B6_10.hex to a spare promicro using;
`avrdude -p atmega32u4 -P "$(ls /dev/ttyACM*)" -c avr109 -D -U flash:w:pro_micro_ISP_B6_10.hex`
2. Wire the pins; (first is the ISP pro micro; second is the target)
```
Pro Micro 10 (B6)  <-> Keyboard RESET
Pro Micro 15 (B1)  <-> Keyboard B1 (SCLK)
Pro Micro 16 (B2)  <-> Keyboard B2 (MOSI)
Pro Micro 14 (B3)  <-> Keyboard B3 (MISO)
Pro Micro VCC      <-> Keyboard VCC
Pro Micro GND      <-> Keyboard GND
```
I do have this on hand I believe; from massdrop's planck light firmware updater.
3. Connect the flashed pro micro to my computer and run
`avrdude -c avrisp -P "$(ls /dev/ttyACM*)" -p atmega32u4 -U flash:w:bootloader_atmega32u4_1.0.0.hex:i -U lfuse:w:0x5E:m -U hfuse:w:0xD9:m -U efuse:w:0xC3:m`

The avrisp here refers to the firmware on the ISP flasher pro micro.
The `atmega32u4` refers to the CPU used in the respective breakout boards.
The `avrdude` command interacts with catalina bootloader.
The shell call after the `-P` flag auto finds the port that the pro micro connects to.
The last few arguments are some jumpers apparently.

# Features

My userspace has a lot of shared code between different keyboards.
These files are prefixed with `sbp-` to remove any naming clash.

* [bb-audio](bb-audio.c): Code dealing with audio playback using onboard sound.
Also contains stuff regarding using the devices as MIDI controllers. (WIP)
* [bb-backlight](bb-backlight.c): Controls global key single-channel LED stuff.
* [bb-keylight](bb-keylight.c): Controls per-key RGB LED matrix stuff.
* [bb-underglow](bb-underglow.c): Controls RGB underglow effects.
* [bb-process](bb-macro.c): My custom keycodes; macros, tap dances, etc.
* [bb-rotary](bb-rotary.c): Rotary encoder sutff

# Layout

![Corne layout](https://i.imgur.com/6VvQZ2I.png)

My personal layout is mostly inspired by the
[Miryoku layout](../manna-harbour_miryoku/miryoku.org).
There are some changes to make it friendlier to international keyboards.
My board is compatible with software implementation of Dvorak and Turkish F.

## Base

Base layer uses tap-hold functionality to have access to modifiers.
The modifiers are mirrored on each half of the layout;
as to make those modifiers accessible to the keys that overlap them.
Besides the Alt key; each side has the proper L/R version of the modifier.
Since Right Alt key functions as AltGr key;
both the L and R versions are available on each side.

# Shoutout

* To [drashna](../drashna/readme.md), for documenting how to use userspace features;
all my code is pretty much inspired from them.
* To [Manna Harbour](../manna-harbour_miryoku/README.org) for their
amazing keymap that inspired me to recreate mine and allowed me to move to
smaller split keyboards.
* To people who taught me C and have me enjoy working with it;
Dr. Mehmet Enis Oğuz and Dr. Veysi Erkcan Özcan.
