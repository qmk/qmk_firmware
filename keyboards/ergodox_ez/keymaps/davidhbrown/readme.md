
![Base layout image](https://davidhbrown.us/ergodox_ez/0-Base.png)
# David H. Brown's ErgoDox EZ keymap
This keymap tries to be easy to learn and switch to-and-from by maximizing the number of standard keys that are at or reasonably near their standard QWERTY locations while providing a few extras for coding. Additional layers provide function keys, an embedded numeric keypad, and mouse/media controls. The CapsLock, NumLock, and ScrollLock USB Host status states are displayed with the indicator LEDs of the keyboard which do double-duty to also indicate activation of the three additional layers.

I pulled out the code to show both USB Host status LEDs and layer switches into a separate file; notes on how to add that to your own keymap are described later in the section about `statusLed.c`, below 

# Keymap extended description
I found this arrangement easier to learn and adjust to than the default layout, especially because I often switch to any of a number of laptop keyboards when I'm not at my desktop machine.

If you would like to download a hex file with this layout including the statusLed.c behavior, you can get that from https://davidhbrown.us/ergodox_ez/ergodox_ez_davidhbrown.hex  This works with both my ErgoDox EZ Original and my ErgoDox EZ Shine keyboards.

If you would like to fork the layout in the configurator, go to [https://configure.ergodox-ez.com/ergodox-ez/layouts/LvADM/latest/0](https://configure.ergodox-ez.com/ergodox-ez/layouts/LvADM/latest/0). What you download won't have the statusLed function; that's not part of the configurator. The configurator is what prepared the nice layout images.
## Base layer
My goal here was to maximize access to standard keys and to place them as close to their usual QWERTY positions as possible. I am writing in English at least 65% of the time and code maybe 35% (wish the code were higher; it's usually more fun, but not the only thing I need to do). 
![Base layout image](https://davidhbrown.us/ergodox_ez/0-Base.png)
### left-hand notes
Relative to the default layout, I restored **Esc** to the upper left and put **Tab** back below it. A fairly standard row of modifier keys begins the bottom row: **Ctrl**, **Fn** (more on that in the next layer), **OS**, and **Alt** to match the notebook keyboards I use when I don't have one of my Ergodoxes available. The numbers extend up through **6** because I can't ever remember which pointer finger I'm supposed to use for that. An extra **Enter** just above the thumb cluster has proved a convenience (especially when my dominant right hand is on my trackpad), and the key above that summons the **Calculator**. "Space Cadet Shift" is enabled: just tapping the left shift produces a **(** while holding it really is Shift. 

The latest addition to this layout is putting a **{** where I'd previously just disabled the Caps Lock. Unfortunately, I couldn't figure out a way to get a Shift+{ to produce }, but most of the code editors I use automatically type the closing }, so it should be okay.
### right-hand notes
I very much wanted to retain an inverted-T of directional **arrows** at the lower right and to keep **Enter** where it is usually found. (Really, I tried the default layout for a while, but since I was often using a notebook, the switch was too much for my head.) The right thumb gets its own **Space** and left of that is (forward) **Delete**, mirroring the space and backspace on the left.

One compromise is that the semicolon (**;:**) key is displaced to retain the customary position of the single/double quote (**'"**) and brackets (**[{** and **]}**) are displaced to the thumb cluster. The numbers **6** through **0** begin the top row --- shifted left one position relative to the default layout to leave room for both **-_** and **=+** near their usual spot. Along with a "Space Cadet Shift" producing a **)**, holding **;** gets you **Alt** and holding **/** is **Ctrl**.
## Function keys
Many notebook keyboards have a blue "Fn" key used to access the function keys F1...Fn from keys normally invoking to system-specific behaviors such as changing the screen brightness. As the Ergodox EZ lacks a row for function keys, I figured I'd adopt the same approach. To access this layer, hold down the second key on the bottom row of the left-hand keyboard.
![Function key layer layout](https://davidhbrown.us/ergodox_ez/1-Function.png)On the top row, function keys **F1-F9** match the numbers 1-9; 0 gets **F10**; - is **F11**, = is **F12**. The top left key, Ctrl-Shift-Esc will open the Task Manager on Windows. Fn+Q will send **Alt+F4** which will quit many Windows apps that don't respond to Ctrl+Q; similarly Fn+W sends **Ctrl+F4**, an old way to close a window.

Fn+left Shift toggles **CapsLock**. Fn+{ on the left gets the closing brace **}** as a compromise because I couldn't make it happen with shift. Fn+Delete becomes **Insert**. You can also toggle the numpad (2) and mouse (3) layers.

If you have the **Shine** keyboard, RGB on-off and brightness are on the left thumb cluster with animation and hue on the right.
## Embedded numeric keypad
Some notebooks will "embed" a numeric keypad within the right half of the keyboard. I positioned this one so that 7, 8, and 9 match the labeled keys from the base layer.
![Numeric keypad layer layout](https://davidhbrown.us/ergodox_ez/2-Numpad.png)You can toggle this layer with Fn+Calc or Fn+NumLock; those keys are still available where the 6s are in the base layer. The numbers work fine; the positions of 7, 8, and 9 match the base layer. Numpads often have a double-wide 0 at the bottom left, so I use two keys for 0 there, plus an extra at the top right because it matches the base layer. Honestly, I can't remember where I put the numpad-specific punctuation without labeling the keys. (Keycodes for the numeric keypad are different from those corresponding to the main keyboard.) For ease of data entry, I used the vertical key next to the embedded pad as an extra **Tab**. Never had anything better to do with that key, so it's on the base layer. The right-hand enter is remapped to the numpad-specific **Enter**, as is the **\** above it.
## Mouse and media layer
![Mouse and media layer layout](https://davidhbrown.us/ergodox_ez/3-MouseMedia.png)I usually access this layer by holding the bottom-right key on the left board (a tap is **`~**), and you can toggle this layer by adding the Fn key. Mouse **movement** is on WASD as well as the arrows. All four directions of mouse **wheel** are available in three clusters. I mostly use the **middle click** on this layer because that's an unreliable three-finger tap+drag on my trackpad, so it gets two keys. Starting to appreciate having the **volume** controls when in-game. 
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
