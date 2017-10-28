Phantom keyboard firmware
=========================

A community-developed keyboard PCB designed to fit inside the case of a Filco Majestouch.

See the [Deskthority wiki](https://deskthority.net/wiki/Phantom) for more information.

## Bootloader

The Phantom uses a [Teensy 2.0](https://www.pjrc.com/store/teensy.html) as a controller.

The Teensy has a special bootloader that can be accessed by pressing the button on the Teensy PCB. It is also possible to use Boot Magic and Command to access the bootloader.

To write the firmware to the Teensy use [Teensy loader](https://www.pjrc.com/teensy/loader.html).

## Quantum MK Firmware

For the full Quantum feature list, see the [documentation](https://docs.qmk.fm).

## RGB underlight

It is possible to connect a WS2812B LED strip to the Teensy for RGB underlight support.

For this to work the DIN connection on the WS2812B strip should be soldered to PE2 on the Teensy (see reference image https://i.imgur.com/aDfNoHT.jpg).

See [rgbmod](keymaps/rgbmod) for a keymap that utilizes the RGB underlight feature.

## Building

The Phantom allows for a huge amount of different layouts.

Depending on which layout and keymap you would like to use, you will have to compile the firmware slightly differently. All of the commands should be run in the [keyboards/phantom](/keyboards/phantom) folder.

### Custom keymaps

To define your own keymap, copy one of the [existing keymap](keymaps) folders and give it the name of your keymap. Then check the [keymap documentation](https://docs.qmk.fm/Keymap.html) for details on how to modify the keymap.

To make it easy to define keymaps for the most common layouts a few macros are provided.

| Layout          | Macro                     |
| --------------- | ------------------------- |
| Winkey ANSI     | `KEYMAP()`                |
| Winkeyless ANSI | `KEYMAP_WINKEYLESS()`     |
| Winkey ISO      | `KEYMAP_ISO()`            |
| Winkeyless ISO  | `KEYMAP_ISO_WINKEYLESS()` |
| 7BIT            | `KEYMAP_7BIT()`           |

To build the firmware with a custom keymap, run `make <keymap name>`
