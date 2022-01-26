# Sofle Keyboard

![SofleKeyboard version 2.1 RGB Keyhive](https://i.imgur.com/WH9OoWuh.jpg)

Sofle is 6×4+5 keys column-staggered split keyboard. Based on Lily58, Corne and Helix keyboards.

For detailed instructions on using VIA and flashing, please refer to the sections further down the page!

For details about the keyboard design, refer to Josef's blog: [Sofle Keyboard - a split keyboard based on Lily58 and Crkbd](https://josef-adamcik.cz/electronics/let-me-introduce-you-sofle-keyboard-split-keyboard-based-on-lily58.html)

Build guide: [Keyhive Sofle RGB build guide](https://github.com/keyhive/build_guides/blob/master/docs/keyboards/sofle-rgb.md)

* Keyboard Maintainer: [Solartempest]
* Hardware Supported: SofleKeyboard V2.1 RGB PCB, ProMicro / Elite-C
* Hardware Availability: [Keyhive](https://keyhive.xyz/shop/sofle)

# Custom Features:

### OLED Features:
-   Includes Snakey keyboard pet! Slithers according to WPM, bites, and sticks its tongue out at you!
-	OLED displays current layer, lock key status, WPM, custom logo, and custom name.
-	OLED shuts off on idle and when computer is sleeping.
-	Includes working Luna keyboard pet.
-	Includes working Bongocat (disable RGB for sufficient space).
-   Includes stock OLED code as well.

### RGB Features:
-   Adds custom layer lighting with custom gradients for each layer.
-   RGB underglow support and remapped to physical locations (nicer gradients and effects).
-   Adds white caps lock, scroll lock, and num lock key indicators using the top row/underglow LEDs.

### Rotary Encoder and VIA Features:
-   Fully emappable left encoder controls volume up/down/mute. Right encoder PGUP/PGDOWN.
-   Allows for  live remapping of per-layer rotary encoder functions in VIA.
-   VIA support included by default.
-   This fixes the Keyhive left bottom row offset issue in VIA. You will need to import sofle.json in VIA.
-   Custom macro key in VIA for Super Alt Tab, which is fully compatible with rotary encoders.
-   Custom macro key in VIA for moving windows to other monitors in Windows, which is fully compatible with rotary encoders.

### Tap and Other Features:
-   Push left-shift + backspace to delete whole words. Right-shift + backspace to delete whole words in the opposite direction.
-   Double tap layers to stay on a layer instead of momentary push.
-   Adds key combo functionality.
-   Symmetric modifiers (CMD/Super, Alt/Opt, Ctrl, Shift).

## Using with VIA

-   After flashing, in VIA make sure to Import Keymap, which is "sofle VIA keymap.json". This will alow VIA to recognize the updated layout and custom functions. VIA will not auto-recognize the keyboard with this firmware because of the necessary customization.
-   Go to Save+Load to Load Saved Layout. You can import my own layout "sofle VIA layout.json" or just use the Keymap tab to assign your own keys. Having another keyboard connected can be handy for doing this step.
-   It is a good idea to Save Current Layout after you decide on your mapping.


Make example for this keyboard (after setting up your build environment):

    make sofle/keyhive:default

Flashing example for this keyboard:

    make sofle/keyhive:default:flash

Press reset button on he keyboard when asked.

Disconnect the first half, connect the second one and repeat the process.


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
