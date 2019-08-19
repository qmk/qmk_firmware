
# David H. Brown's ergodox_ez `keymap.c`
The real goal of putting this on GitHub is not because I expect anyone else will want exactly the same layout I do. The key feature is described later in the section about `statusLed.c`. Briefly, I really missed having the usual NumLock status LED and figured out I'd share how I got it back while retaining the use of the keyboard LEDs to indicate the current layer. But I should probably describe the keymap first... 

## Base layer
My goal here was to maximize access to standard keys and to place them as close to their usual QWERTY positions as possible. I am writing in English at least 65% of the time and code maybe 35% (wish the code were higher; it's usually more fun, but not the only thing I need to do). 

### left-hand notes
Relative to the default layout, I restored **Esc** to the upper left and put **Tab** back below it. A fairly standard row of modifier keys begins the bottom row: **Ctrl**, **Fn**, **OS**, and **Alt** to match the notebook keyboards I use when I don't have one of my Ergodoxes available. The numbers extend up through **6** because I can't ever remember which pointer finger I'm supposed to use for that. An extra **Enter** just above the thumb cluster has proved a convenience (especially when my dominant right hand is on my trackpad), and the key above that summons the **Calculator**. "Space Cadet Shift" is enabled: just tapping the left shift produces a **(** while holding it really is Shift. 

The latest addition to this layout is putting a **{** where I'd previously just disabled the Caps Lock. Unfortunately, I couldn't figure out a way to get a Shift+{ to produce }, but most of the code editors I use automatically type the closing }, so it should be okay.
### right-hand notes
I very much wanted to retain an inverted-T of directional **arrows** at the lower right and to keep **Enter** where it is usually found. (Really, I tried the default layout for a while, but since I was often using a notebook, the switch was too much for my head.) The right thumb gets its own **Space** and left of that is (forward) **Delete**, mirroring the space and backspace on the left.

One compromise is that the semicolon (**;:**) key is displaced to retain the customary position of the single/double quote (**'"**) and brackets (**[{** and **]}**) are displaced to the thumb cluster. The numbers **6** through **0** begin the top row --- shifted left one position relative to the default layout to leave room for both **-_** and **=+** near their usual spot. Along with a "Space Cadet Shift" producing a **)**, holding **;** gets you **Alt** and holding **/** is **Ctrl**.

## How to use `statusLed.c`  

This file defines a `void statusLed(void)` function that uses both the current layer
and the USB LEDs (NumLock, CapsLock, etc) to set the `ergodox_right_led_*` indicators.

Each of the three right-hand keyboard LEDs will be associated with a layer (use its number or a constant you `#define` in `keymap.c`) and with one of the USB host "LEDs" that might appear on a keyboard to show some status of the keyboard HID.

* If the host LED is "on," the associated Ergodox-EZ LED will be illuminated dimly (just enough to see clearly in a lit room; not so bright as to bother you in the dark).
* If the associated layer is selected, the Ergodox-EZ LED will be at (approximately) half brightness.
* If both the associated host and the associated layer are enabled, the LED will be at full brightness (except green was too bright, so these are configurable).
* Otherwise, the LED is off.

In other words...
|  |USB Host LED is On|USB Host LED is Off|
|--:|:--:|:--:|
|**Layer Active**|`STATUS_LED_*_FULL`|`STATUS_LED_*_HALF`|
|**Layer Inactive**|`STATUS_LED_*_DIM` |`0`|
(If you want to define non-zero `STATUS_LED_*_OFF` values, they will go in the second line of the function body, currently `uint8_t red=0,green=0,blue=0;`.  I'd be curious to know the use case.)

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
In this file, change the `#define STATUS_LED_*_LAYER` entries to match the layer number you want to have indicated with each color. If you defined constants for your layer numbers, you can use them (assuming you included this file after).

Then, `#define STATUS_LED_*_USB` to which of the five USB Host "LEDs" you wish to associate with each actual LED. See [docs/custom_quantum_functions.md](https://github.com/qmk/qmk_firmware/blob/master/docs/custom_quantum_functions.md) for details. Allowable values are:

* `USB_LED_NUM_LOCK`
* `USB_LED_CAPS_LOCK`
* `USB_LED_SCROLL_LOCK`
* `USB_LED_COMPOSE`
* `USB_LED_KANA`
  
After flashing and trying it out, you may wish to come back and tweak the levels of the `STATUS_LED_*_*` #defines. On my keyboard, green is almost too bright and blue is fairly dim compared to the other two.

_[`qmk_firmware/keyboards/ergodox_ez/keymaps/davidhbrown/README.md`](https://github.com/davidhbrown/qmk_firmware/tree/davidhbrown/keyboards/ergodox_ez/keymaps/davidhbrown)_
_v1.1a; August 20, 2019_
