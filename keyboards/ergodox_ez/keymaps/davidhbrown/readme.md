
# David H. Brown's ergodox_ez keymap
The real goal of putting this on GitHub is not because I expect anyone else will want exactly the same layout I do. The more interesting feature is described later in the section about `statusLed.c`. 

Briefly, I really missed having the usual NumLock status LED and figured out I'd share how I got it back while retaining the use of the keyboard LEDs to indicate the current layer. At least for up to three additional layers. You are welcome to take that and incorporate it into your own keymaps. 

But I should probably describe the keymap first... 

# Keymap
If you would like to download a hex file with this layout including the statusLed.c behavior, you can get that from https://davidhbrown.us/ergodox_ez/ergodox_ez_davidhbrown.hex  This works with both my ErgoDox EZ Original and my ErgoDox EZ Shine keyboards.

If you would like to fork the layout in the configurator, go to [https://configure.ergodox-ez.com/ergodox-ez/layouts/LvADM/latest/0](https://configure.ergodox-ez.com/ergodox-ez/layouts/LvADM/latest/0). What you download won't have the statusLed function; that's not part of the configurator. The configrator is what prepared the nice layout images you'll see below.
## Base layer
My goal here was to maximize access to standard keys and to place them as close to their usual QWERTY positions as possible. I am writing in English at least 65% of the time and code maybe 35% (wish the code were higher; it's usually more fun, but not the only thing I need to do). 
![Base layout image](https://davidhbrown.us/ergodox_ez/0-Base.png)
### left-hand notes
Relative to the default layout, I restored **Esc** to the upper left and put **Tab** back below it. A fairly standard row of modifier keys begins the bottom row: **Ctrl**, **Fn**, **OS**, and **Alt** to match the notebook keyboards I use when I don't have one of my Ergodoxes available. The numbers extend up through **6** because I can't ever remember which pointer finger I'm supposed to use for that. An extra **Enter** just above the thumb cluster has proved a convenience (especially when my dominant right hand is on my trackpad), and the key above that summons the **Calculator**. "Space Cadet Shift" is enabled: just tapping the left shift produces a **(** while holding it really is Shift. 

The latest addition to this layout is putting a **{** where I'd previously just disabled the Caps Lock. Unfortunately, I couldn't figure out a way to get a Shift+{ to produce }, but most of the code editors I use automatically type the closing }, so it should be okay.
### right-hand notes
I very much wanted to retain an inverted-T of directional **arrows** at the lower right and to keep **Enter** where it is usually found. (Really, I tried the default layout for a while, but since I was often using a notebook, the switch was too much for my head.) The right thumb gets its own **Space** and left of that is (forward) **Delete**, mirroring the space and backspace on the left.

One compromise is that the semicolon (**;:**) key is displaced to retain the customary position of the single/double quote (**'"**) and brackets (**[{** and **]}**) are displaced to the thumb cluster. The numbers **6** through **0** begin the top row --- shifted left one position relative to the default layout to leave room for both **-_** and **=+** near their usual spot. Along with a "Space Cadet Shift" producing a **)**, holding **;** gets you **Alt** and holding **/** is **Ctrl**.
## Function keys
Many notebook keyboards have a blue "Fn" key used to access the function keys F1...Fn from keys normally invoking to system-specific behaviors such as changing the screen brightness. As the Ergodox EZ lacks a row for function keys, I figured I'd adopt the same approach, overlaying the numbers (and -, =) with F1..F12.
![Function key layer layout](https://davidhbrown.us/ergodox_ez/1-Function.png)
## Embedded numeric keypad
Some notebooks will "embed" a numeric keypad within the right half of the keyboard. I positioned this one so that 7, 8, and 9 match the labeled keys from the base layer.
![Numeric keypad layer layout](https://davidhbrown.us/ergodox_ez/2-Numpad.png)
## Mouse and media layer
I set this up mostly to have better control of middle-click for working in FreeCAD before I got my Space Mouse.
![Mouse and media layer layout](https://davidhbrown.us/ergodox_ez/3-MouseMedia.png)
# How to use `statusLed.c`  in your own keymap

This file defines a `void statusLed(void)` function that uses both the current layer
and the USB LEDs (NumLock, CapsLock, etc) to set the `ergodox_right_led_*` indicators.

Each of the three right-hand keyboard LEDs can be associated with a layer (use its number or a constant you `#define` in `keymap.c`) and with one of the USB host "LEDs" that might appear on a keyboard to show some status of the keyboard HID.

* If the host LED is "on," the Ergodox-EZ LED will be illuminated dimly -- just enough to see clearly in a lit room; not so bright as to bother you in the dark. 
(The values for each LED are specified by `#define STATUS_LED_<color>_DIM ___`)
* If the associated layer is selected, the Ergodox-EZ LED will be at (approximately) half brightness. 
(`#define STATUS_LED_<color>_HALF ___`)
* If both the associated host and the associated layer are enabled, the LED will be at full brightness (my green was too bright, so these are configurable).
(`#define STATUS_LED_<color>_FULL ___`)
* Otherwise, the keyboard LED is off
...but if you want it not to be off, change the values in the second line of the function body, currently `uint8_t red=0,green=0,blue=0;`.

### Integration into `keymap.c`
To use this feature, `#include "statusLed.c"` at an appropriate point in your `keyboard.c`, typically
after the rest of the `#include` and `#define` directives.

Call `statusLed();` from within *both* the `led_set_user` and `layer_state_set_user` functions. The default
`keymap.c` does not define `led_set_user`, so that's new code. This function call could be placed anywhere
within those functions. From my `keymap.c`:  

```C
    void led_set_user(uint8_t usb_led) {
      statusLed();
    }

    uint32_t layer_state_set_user(uint32_t state) {
      statusLed();
      uint8_t layer = biton32(state);
      ...  
```
Search for and delete (or comment-out) any code calling the `ergodox_right_led_*` functions. (Unless, of course, you can figure out how to usefully integrate that behavior with this.) You may find some in the first part of the `layer_state_set_user` function (both in the default keymap and from the generator).

### Customization of `statusLed.c`
In this file, change the `#define STATUS_LED_<color>_LAYER` entries to match the layer number you want to have indicated with each keyboard LED \<color> --- `RED`, `GREEN`, or `BLUE`. If you defined constants for your layer numbers, you can use them (assuming you included this file after).

Then, `#define STATUS_LED_<color>_USB` to which of the five USB Host "LEDs" you wish to associate with each actual LED. See [docs/custom_quantum_functions.md](https://github.com/qmk/qmk_firmware/blob/master/docs/custom_quantum_functions.md) for details. Possible values are:

* `USB_LED_NUM_LOCK`
* `USB_LED_CAPS_LOCK`
* `USB_LED_SCROLL_LOCK`
* `USB_LED_COMPOSE`
* `USB_LED_KANA`
  
After flashing and trying it out, you may wish to come back and tweak the levels of the `STATUS_LED_<color>_<level>` #defines. On my keyboard, green is almost too bright and blue is fairly dim compared to the other two.

_[`qmk_firmware/keyboards/ergodox_ez/keymaps/davidhbrown/README.md`](https://github.com/davidhbrown/qmk_firmware/tree/davidhbrown/keyboards/ergodox_ez/keymaps/davidhbrown)_
_v1.1b; August 19, 2019_
