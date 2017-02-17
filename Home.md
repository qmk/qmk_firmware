# Getting started

Before you are able to compile, you'll need to install an environment for AVR development. You'll find the instructions for any OS below. If you find another/better way to set things up from scratch, please consider [making a pull request](https://github.com/qmk/qmk_firmware/pulls) with your changes!

* [Build Environment Setup](Build-Environment-Setup)
* [QMK Overview](QMK-Overview)

# Going beyond the keycodes

Aside from the [basic keycodes](https://github.com/qmk/qmk_firmware/wiki/Keycodes), your keymap can include shortcuts to common operations.

## Quick aliases to common actions

Your keymap can include shortcuts to common operations (called "function actions" in tmk). To learn more about them check out the [Key Functions](Key-Functions) page.

## Space Cadet Shift: The future, built in

Steve Losh [described](http://stevelosh.com/blog/2012/10/a-modern-space-cadet/) the Space Cadet Shift quite well. Essentially, you hit the left Shift on its own, and you get an opening parenthesis; hit the right Shift on its own, and you get the closing one. When hit with other keys, the Shift key keeps working as it always does. Yes, it's as cool as it sounds. Head on over to the [Space Cadet Shift](Space-Cadet-Shift) page to read about it.

## The Leader key: A new kind of modifier

Most modifiers have to be held or toggled. But what if you had a key that indicated the start of a sequence? You could press that key and then rapidly press 1-3 more keys to trigger a macro, or enter a special layer, or anything else you might want to do. To learn more about it check out the [Leader Key](Leader-Key) page.

## Tap Dance: A single key can do 3, 5, or 100 different things

Hit the semicolon key once, send a semicolon. Hit it twice, rapidly -- send a colon. Hit it three times, and your keyboard's LEDs do a wild dance. That's just one example of what Tap Dance can do. Read more about it on the [Tap Dance](Tap-Dance) page.

## Temporarily setting the default layer

`DF(layer)` - sets default layer to *layer*. The default layer is the one at the "bottom" of the layer stack - the ultimate fallback layer. This currently does not persist over power loss. When you plug the keyboard back in, layer 0 will always be the default. It is theoretically possible to work around that, but that's not what `DF` does.

## Macro shortcuts: Send a whole string when pressing just one key

How would you like a single keypress to send a whole word, sentence, paragraph, or even document? Head on over to the [Macros](Macros) page to read up on all aspects of Simple and Dynamic Macros.

## Additional keycode aliases for software-implemented layouts (Colemak, Dvorak, etc)

Everything is assuming you're in Qwerty (in software) by default, but there is built-in support for using a Colemak or Dvorak layout by including this at the top of your keymap:

    #include <keymap_colemak.h>

If you use Dvorak, use `keymap_dvorak.h` instead of `keymap_colemak.h` for this line. After including this line, you will get access to:

 * `CM_*` for all of the Colemak-equivalent characters
 * `DV_*` for all of the Dvorak-equivalent characters

These implementations assume you're using Colemak or Dvorak on your OS, not on your keyboard - this is referred to as a software-implemented layout. If your computer is in Qwerty and your keymap is in Colemak or Dvorak, this is referred to as a firmware-implemented layout, and you won't need these features.

To give an example, if you're using software-implemented Colemak, and want to get an `F`, you would use `CM_F` - `KC_F` under these same circumstances would result in `T`.

## Additional language support

In `quantum/keymap_extras/`, you'll see various language files - these work the same way as the alternative layout ones do. Most are defined by their two letter country/language code followed by an underscore and a 4-letter abbreviation of its name. `FR_UGRV` which will result in a `ù` when using a software-implemented AZERTY layout. It's currently difficult to send such characters in just the firmware (but it's being worked on - see Unicode support).

## Unicode support

There are three Unicode keymap definition method available in QMK:

### UNICODE_ENABLE

Supports Unicode input up to 0xFFFF. The keycode function is `UC(n)` in
keymap file, where *n* is a 4 digit hexadecimal.

### UNICODEMAP_ENABLE

Supports Unicode up to 0xFFFFFFFF. You need to maintain a separate mapping
table `const uint32_t PROGMEM unicode_map[] = {...}` in your keymap file.
The keycode function is `X(n)` where *n* is the array index of the mapping
table.

### UCIS_ENABLE

TBD

Unicode input in QMK works by inputing a sequence of characters to the OS,
sort of like macro. Unfortunately, each OS has different ideas on how Unicode is inputted.

This is the current list of Unicode input method in QMK:

* UC_OSX: MacOS Unicode Hex Input support. Works only up to 0xFFFF. Disabled by default. To enable: go to System Preferences -> Keyboard -> Input Sources, and enable Unicode Hex.
* UC_LNX: Unicode input method under Linux. Works up to 0xFFFFF. Should work almost anywhere on ibus enabled distros. Without ibus, this works under GTK apps, but rarely anywhere else.
* UC_WIN: (not recommended) Windows built-in Unicode input. To enable: create registry key under `HKEY_CURRENT_USER\Control Panel\Input Method\EnableHexNumpad` of type `REG_SZ` called `EnableHexNumpad`, set its value to 1, and reboot. This method is not recommended because of reliability and compatibility issue, use WinCompose method below instead.
* UC_WINC: Windows Unicode input using WinCompose. Requires [WinCompose](https://github.com/samhocevar/wincompose). Works reliably under many (all?) variations of Windows.

## Backlight Breathing

In order to enable backlight breathing, the following line must be added to your config.h file.

    #define BACKLIGHT_BREATHING

The following function calls are used to control the breathing effect.

* ```breathing_enable()``` - Enable the free-running breathing effect.
* ```breathing_disable()``` - Disable the free-running breathing effect immediately.
* ```breathing_self_disable()``` - Disable the free-running breathing effect after the current effect ends.
* ```breathing_toggle()``` - Toggle the free-running breathing effect.
* ```breathing_defaults()``` - Reset the speed and brightness settings of the breathing effect.

The following function calls are used to control the maximum brightness of the breathing effect.

* ```breathing_intensity_set(value)``` - Set the brightness of the breathing effect when it is at its max value.
* ```breathing_intensity_default()``` - Reset the brightness of the breathing effect to the default value based on the current backlight intensity.

The following function calls are used to control the cycling speed of the breathing effect.

* ```breathing_speed_set(value)``` - Set the speed of the breathing effect - how fast it cycles.
* ```breathing_speed_inc(value)``` - Increase the speed of the breathing effect by a fixed value.
* ```breathing_speed_dec(value)``` - Decrease the speed of the breathing effect by a fixed value.
* ```breathing_speed_default()``` - Reset the speed of the breathing effect to the default value.

The following example shows how to enable the backlight breathing effect when the FUNCTION layer macro button is pressed:

    case MACRO_FUNCTION:
        if (record->event.pressed)
        {
            breathing_speed_set(3);
            breathing_enable();
            layer_on(LAYER_FUNCTION);
        }
        else
        {
            breathing_speed_set(1);
            breathing_self_disable();
            layer_off(LAYER_FUNCTION);
        }
        break;

The following example shows how to pulse the backlight on-off-on when the RAISED layer macro button is pressed:

    case MACRO_RAISED:
      if (record->event.pressed)
      {
        layer_on(LAYER_RAISED);
        breathing_speed_set(2);
        breathing_pulse();
        update_tri_layer(LAYER_LOWER, LAYER_RAISED, LAYER_ADJUST);
      }
      else
      {
        layer_off(LAYER_RAISED);
        update_tri_layer(LAYER_LOWER, LAYER_RAISED, LAYER_ADJUST);
      }
      break;

## Other firmware shortcut keycodes

* `RESET` - puts the MCU in DFU mode for flashing new firmware (with `make dfu`)
* `DEBUG` - the firmware into debug mode - you'll need hid_listen to see things
* `BL_ON` - turns the backlight on
* `BL_OFF` - turns the backlight off
* `BL_<n>` - sets the backlight to level *n*
* `BL_INC` - increments the backlight level by one
* `BL_DEC` - decrements the backlight level by one
* `BL_TOGG` - toggles the backlight
* `BL_STEP` - steps through the backlight levels

Enable the backlight from the Makefile.

# Custom Quantum functions

All of these functions are available in the `*_kb()` or `*_user()` variety. `kb` ones should only be used in the `<keyboard>/<keyboard>.c` file, and `user` ones should only be used in the `keymap.c`. The keyboard ones call the user ones - it's necessary to keep these calls to allow the keymap functions to work correctly.

## `void matrix_init_*(void)`

This function gets called when the matrix is initiated, and can contain start-up code for your keyboard/keymap.

## `void matrix_scan_*(void)`

This function gets called at every matrix scan, which is basically as often as the MCU can handle. Be careful what you put here, as it will get run a lot.

## `bool process_record_*(uint16_t keycode, keyrecord_t *record)`

This function gets called on every keypress/release, and is where you can define custom functionality. The return value is whether or not QMK should continue processing the keycode - returning `false` stops the execution.

The `keycode` variable is whatever is defined in your keymap, eg `MO(1)`, `KC_L`, etc. and can be switch-cased to execute code whenever a particular code is pressed.

The `record` variable contains infomation about the actual press:

```
keyrecord_t record {
  keyevent_t event {
    keypos_t key {
      uint8_t col
      uint8_t row
    }
    bool     pressed
    uint16_t time
  }
}
```

The conditional `if (record->event.pressed)` can tell if the key is being pressed or released, and you can execute code based on that.

## `void led_set_*(uint8_t usb_led)`

This gets called whenever there is a state change on your host LEDs (eg caps lock, scroll lock, etc). The LEDs are defined as:

```
#define USB_LED_NUM_LOCK                0
#define USB_LED_CAPS_LOCK               1
#define USB_LED_SCROLL_LOCK             2
#define USB_LED_COMPOSE                 3
#define USB_LED_KANA                    4
```

and can be tested against the `usb_led` with a conditional like `if (usb_led & (1<<USB_LED_CAPS_LOCK))` - if this is true, you can turn your LED on, otherwise turn it off.

# Modding your keyboard

## Audio output from a speaker

Your keyboard can make sounds! If you've got a Planck, Preonic, or basically any keyboard that allows access to the C6 port, you can hook up a simple speaker and make it beep. You can use those beeps to indicate layer transitions, modifiers, special keys, or just to play some funky 8bit tunes.

The audio code lives in [quantum/audio/audio.h](/quantum/audio/audio.h) and in the other files in the audio directory. It's enabled by default on the Planck [stock keymap](/keyboards/planck/keymaps/default/keymap.c). Here are the important bits:

```
#include "audio.h"
```

Then, lower down the file:

```
float tone_startup[][2] = {
    ED_NOTE(_E7 ),
    E__NOTE(_CS7),
    E__NOTE(_E6 ),
    E__NOTE(_A6 ),
    M__NOTE(_CS7, 20)
};
```

This is how you write a song. Each of these lines is a note, so we have a little ditty composed of five notes here.

Then, we have this chunk:

```
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);

float music_scale[][2] = SONG(MUSIC_SCALE_SOUND);
float goodbye[][2] = SONG(GOODBYE_SOUND);
```

Wherein we bind predefined songs (from [quantum/audio/song_list.h](/quantum/audio/song_list.h)) into named variables. This is one optimization that helps save on memory: These songs only take up memory when you reference them in your keymap, because they're essentially all preprocessor directives.

So now you have something called `tone_plover` for example. How do you make it play the Plover tune, then? If you look further down the keymap, you'll see this:

```
PLAY_NOTE_ARRAY(tone_plover, false, 0); // Signature is: Song name, repeat, rest style
```

This is inside one of the macros. So when that macro executes, your keyboard plays that particular chime.

"Rest style" in the method signature above (the last parameter) specifies if there's a rest (a moment of silence) between the notes.


## Recording And Playing back Music
* ```Music On``` - Turn music mode on. The default mapping is ```Lower+Upper+C```
* ```LCTL``` - start a recording
* play some tones
* ```LALT``` - stop recording, stop playing
* ```LGUI``` - play recording
* ```LALT``` - stop playing
* ```Music Off``` - Turn music mode off. The default mapping is ```Lower+Upper+V```


## MIDI functionalty

This is still a WIP, but check out `quantum/keymap_midi.c` to see what's happening. Enable from the Makefile.

## Bluetooth functionality

This requires [some hardware changes](https://www.reddit.com/r/MechanicalKeyboards/comments/3psx0q/the_planck_keyboard_with_bluetooth_guide_and/?ref=search_posts), but can be enabled via the Makefile. The firmware will still output characters via USB, so be aware of this when charging via a computer. It would make sense to have a switch on the Bluefruit to turn it off at will.

## International Characters on Windows

[AutoHotkey](https://autohotkey.com) allows Windows users to create custom hotkeys among others.

The method does not require Unicode support in the keyboard itself but depends instead of AutoHotkey running in the background.

First you need to select a modifier combination that is not in use by any of your programs.
CtrlAltWin is not used very widely and should therefore be perfect for this.
There is a macro defined for a mod-tab combo `LCAG_T`.
Add this mod-tab combo to a key on your keyboard, e.g.: `LCAG_T(KC_TAB)`.
This makes the key behave like a tab key if pressed and released immediately but changes it to the modifier if used with another key.

In the default script of AutoHotkey you can define custom hotkeys.

    <^<!<#a::Send, ä
    <^<!<#<+a::Send, Ä

The hotkeys above are for the combination CtrlAltGui and CtrlAltGuiShift plus the letter a.
AutoHotkey inserts the Text right of `Send, ` when this combination is pressed.

## RGB Under Glow Mod

![Planck with RGB Underglow](https://raw.githubusercontent.com/qmk/qmk_firmware/master/keyboards/planck/keymaps/yang/planck-with-rgb-underglow.jpg)

Here is a quick demo on Youtube (with NPKC KC60) (https://www.youtube.com/watch?v=VKrpPAHlisY).

For this mod, you need an unused pin wiring to DI of WS2812 strip. After wiring the VCC, GND, and DI, you can enable the underglow in your Makefile.

    RGBLIGHT_ENABLE = yes

In order to use the underglow animation functions, you need to have `#define RGBLIGHT_ANIMATIONS` in your `config.h`.

Please add the following options into your config.h, and set them up according your hardware configuration. These settings are for the `F4` pin by default:

    #define RGB_DI_PIN F4     // The pin your RGB strip is wired to
    #define RGBLIGHT_ANIMATIONS    // Require for fancier stuff (not compatible with audio)
    #define RGBLED_NUM 14     // Number of LEDs
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17

You'll need to edit `RGB_DI_PIN` to the pin you have your `DI` on your RGB strip wired to.

The firmware supports 5 different light effects, and the color (hue, saturation, brightness) can be customized in most effects. To control the underglow, you need to modify your keymap file to assign those functions to some keys/key combinations. For details, please check this keymap. `keyboards/planck/keymaps/yang/keymap.c`

### WS2812 Wiring

![WS2812 Wiring](https://raw.githubusercontent.com/qmk/qmk_firmware/master/keyboards/planck/keymaps/yang/WS2812-wiring.jpg)

Please note the USB port can only supply a limited amount of power to the keyboard (500mA by standard, however, modern computer and most usb hubs can provide 700+mA.). According to the data of NeoPixel from Adafruit, 30 WS2812 LEDs require a 5V 1A power supply, LEDs used in this mod should not more than 20.

## PS/2 Mouse Support

Its possible to hook up a PS/2 mouse (for example touchpads or trackpoints) to your keyboard as a composite device.

There are three available modes for hooking up PS/2 devices: USART (best), interrupts (better) or busywait (not recommended).

### Busywait version

Note: This is not recommended, you may encounter jerky movement or unsent inputs. Please use interrupt or USART version if possible.

In rules.mk:

```
PS2_MOUSE_ENABLE = yes
PS2_USE_BUSYWAIT = yes
```

In your keyboard config.h:

```
#ifdef PS2_USE_BUSYWAIT
#   define PS2_CLOCK_PORT  PORTD
#   define PS2_CLOCK_PIN   PIND
#   define PS2_CLOCK_DDR   DDRD
#   define PS2_CLOCK_BIT   1
#   define PS2_DATA_PORT   PORTD
#   define PS2_DATA_PIN    PIND
#   define PS2_DATA_DDR    DDRD
#   define PS2_DATA_BIT    2
#endif
```

### Interrupt version

The following example uses D2 for clock and D5 for data. You can use any INT or PCINT pin for clock, and any pin for data.

In rules.mk:

```
PS2_MOUSE_ENABLE = yes
PS2_USE_INT = yes
```

In your keyboard config.h:

```
#ifdef PS2_USE_INT
#define PS2_CLOCK_PORT  PORTD
#define PS2_CLOCK_PIN   PIND
#define PS2_CLOCK_DDR   DDRD
#define PS2_CLOCK_BIT   2
#define PS2_DATA_PORT   PORTD
#define PS2_DATA_PIN    PIND
#define PS2_DATA_DDR    DDRD
#define PS2_DATA_BIT    5

#define PS2_INT_INIT()  do {    \
    EICRA |= ((1<<ISC21) |      \
              (0<<ISC20));      \
} while (0)
#define PS2_INT_ON()  do {      \
    EIMSK |= (1<<INT2);         \
} while (0)
#define PS2_INT_OFF() do {      \
    EIMSK &= ~(1<<INT2);        \
} while (0)
#define PS2_INT_VECT   INT2_vect
#endif
```

### USART version

To use USART on the ATMega32u4, you have to use PD5 for clock and PD2 for data. If one of those are unavailable, you need to use interrupt version.

In rules.mk:

```
PS2_MOUSE_ENABLE = yes
PS2_USE_USART = yes
```

In your keyboard config.h:

```
#ifdef PS2_USE_USART
#define PS2_CLOCK_PORT  PORTD
#define PS2_CLOCK_PIN   PIND
#define PS2_CLOCK_DDR   DDRD
#define PS2_CLOCK_BIT   5
#define PS2_DATA_PORT   PORTD
#define PS2_DATA_PIN    PIND
#define PS2_DATA_DDR    DDRD
#define PS2_DATA_BIT    2

/* synchronous, odd parity, 1-bit stop, 8-bit data, sample at falling edge */
/* set DDR of CLOCK as input to be slave */
#define PS2_USART_INIT() do {   \
    PS2_CLOCK_DDR &= ~(1<<PS2_CLOCK_BIT);   \
    PS2_DATA_DDR &= ~(1<<PS2_DATA_BIT);     \
    UCSR1C = ((1 << UMSEL10) |  \
              (3 << UPM10)   |  \
              (0 << USBS1)   |  \
              (3 << UCSZ10)  |  \
              (0 << UCPOL1));   \
    UCSR1A = 0;                 \
    UBRR1H = 0;                 \
    UBRR1L = 0;                 \
} while (0)
#define PS2_USART_RX_INT_ON() do {  \
    UCSR1B = ((1 << RXCIE1) |       \
              (1 << RXEN1));        \
} while (0)
#define PS2_USART_RX_POLL_ON() do { \
    UCSR1B = (1 << RXEN1);          \
} while (0)
#define PS2_USART_OFF() do {    \
    UCSR1C = 0;                 \
    UCSR1B &= ~((1 << RXEN1) |  \
                (1 << TXEN1));  \
} while (0)
#define PS2_USART_RX_READY      (UCSR1A & (1<<RXC1))
#define PS2_USART_RX_DATA       UDR1
#define PS2_USART_ERROR         (UCSR1A & ((1<<FE1) | (1<<DOR1) | (1<<UPE1)))
#define PS2_USART_RX_VECT       USART1_RX_vect
#endif
#endif
#endif
```

### Additional Settings

#### PS/2 mouse features

These enable settings supported by the PS/2 mouse protocol: http://www.computer-engineering.org/ps2mouse/

```
/* Use remote mode instead of the default stream mode (see link) */
#define PS2_MOUSE_USE_REMOTE_MODE  

/* Enable the scrollwheel or scroll gesture on your mouse or touchpad */
#define PS2_MOUSE_ENABLE_SCROLLING

/* Some mice will need a scroll mask to be configured. The default is 0xFF. */
#define PS2_MOUSE_SCROLL_MASK 0x0F

/* Applies a transformation to the movement before sending to the host (see link) */
#define PS2_MOUSE_USE_2_1_SCALING

/* The time to wait after initializing the ps2 host */
#define PS2_MOUSE_INIT_DELAY 1000 /* Default */
```

You can also call the following functions from ps2_mouse.h

```
void ps2_mouse_disable_data_reporting(void);

void ps2_mouse_enable_data_reporting(void);

void ps2_mouse_set_remote_mode(void);

void ps2_mouse_set_stream_mode(void);

void ps2_mouse_set_scaling_2_1(void);

void ps2_mouse_set_scaling_1_1(void);

void ps2_mouse_set_resolution(ps2_mouse_resolution_t resolution);

void ps2_mouse_set_sample_rate(ps2_mouse_sample_rate_t sample_rate);
```

#### Fine control

Use the following defines to change the sensitivity and speed of the mouse.
Note: you can also use `ps2_mouse_set_resolution` for the same effect (not supported on most touchpads).

```
#define PS2_MOUSE_X_MULTIPLIER 3
#define PS2_MOUSE_Y_MULTIPLIER 3
#define PS2_MOUSE_V_MULTIPLIER 1
```

#### Scroll button

If you're using a trackpoint, you will likely want to be able to use it for scrolling.
Its possible to enable a "scroll button/s" that when pressed will cause the mouse to scroll instead of moving.
To enable the feature, you must set a scroll button mask as follows:

```
#define PS2_MOUSE_SCROLL_BTN_MASK (1<<PS2_MOUSE_BUTTON_MIDDLE) /* Default */
```

To disable the scroll button feature:

```
#define PS2_MOUSE_SCROLL_BTN_MASK 0
```

The available buttons are:

```
#define PS2_MOUSE_BTN_LEFT      0
#define PS2_MOUSE_BTN_RIGHT     1
#define PS2_MOUSE_BTN_MIDDLE    2
```

You can also combine buttons in the mask by `|`ing them together.

Once you've configured your scroll button mask, you must configure the scroll button send interval.
This is the interval before which if the scroll buttons were released they would be sent to the host.
After this interval, they will cause the mouse to scroll and will not be sent.

```
#define PS2_MOUSE_SCROLL_BTN_SEND 300 /* Default */
```

To disable sending the scroll buttons:
```
#define PS2_MOUSE_SCROLL_BTN_SEND 0
```

Fine control over the scrolling is supported with the following defines:

```
#define PS2_MOUSE_SCROLL_DIVISOR_H 2
#define PS2_MOUSE_SCROLL_DIVISOR_V 2
```

#### Debug settings

To debug the mouse, add `debug_mouse = true` or enable via bootmagic.

```
/* To debug the mouse reports */
#define PS2_MOUSE_DEBUG_HID
#define PS2_MOUSE_DEBUG_RAW
```

## Safety Considerations

You probably don't want to "brick" your keyboard, making it impossible
to rewrite firmware onto it.  Here are some of the parameters to show
what things are (and likely aren't) too risky.

- If your keyboard map does not include RESET, then, to get into DFU
  mode, you will need to press the reset button on the PCB, which
  requires unscrewing the bottom.
- Messing with tmk_core / common files might make the keyboard
  inoperable
- Too large a .hex file is trouble; `make dfu` will erase the block,
  test the size (oops, wrong order!), which errors out, failing to
  flash the keyboard, leaving it in DFU mode.
  - To this end, note that the maximum .hex file size on Planck is
    7000h (28672 decimal)

```
Linking: .build/planck_rev4_cbbrowne.elf                                                            [OK]
Creating load file for Flash: .build/planck_rev4_cbbrowne.hex                                       [OK]

Size after:
   text    data     bss     dec     hex filename
      0   22396       0   22396    577c planck_rev4_cbbrowne.hex
```

  - The above file is of size 22396/577ch, which is less than
    28672/7000h
  - As long as you have a suitable alternative .hex file around, you
    can retry, loading that one
  - Some of the options you might specify in your keyboard's Makefile
    consume extra memory; watch out for BOOTMAGIC_ENABLE,
    MOUSEKEY_ENABLE, EXTRAKEY_ENABLE, CONSOLE_ENABLE, API_SYSEX_ENABLE
- DFU tools do /not/ allow you to write into the bootloader (unless
  you throw in extra fruitsalad of options), so there is little risk
  there.
- EEPROM has around a 100000 write cycle.  You shouldn't rewrite the
  firmware repeatedly and continually; that'll burn the EEPROM
  eventually.

# Porting your keyboard to QMK

If your keyboard is running an Atmega chip (atmega32u4 and others), it's pretty easy to get things setup for compiling your own firmware to flash onto your board. There is a `/util/new_project.sh <keyboard>` script to help get you started - you can simply pass your keyboard's name into the script, and all of the necessary files will be created. The components of each are described below.

## `/keyboards/<keyboard>/config.h`

The `USB Device descriptor parameter` block contains parameters are used to uniquely identify your keyboard, but they don't really matter to the machine.

Your `MATRIX_ROWS` and `MATRIX_COLS` are the numbers of rows and cols in your keyboard matrix - this may be different than the number of actual rows and columns on your keyboard. There are some tricks you can pull to increase the number of keys in a given matrix, but most keyboards are pretty straight-forward.

The `MATRIX_ROW_PINS` and `MATRIX_COL_PINS` are the pins your MCU uses on each row/column. Your schematic (if you have one) will have this information on it, and the values will vary depending on your setup. This is one of the most important things to double-check in getting your keyboard setup correctly.

For the `DIODE_DIRECTION`, most hand-wiring guides will instruct you to wire the diodes in the `COL2ROW` position, but it's possible that they are in the other - people coming from EasyAVR often use `ROW2COL`. Nothing will function if this is incorrect.

`BACKLIGHT_PIN` is the pin that your PWM-controlled backlight (if one exists) is hooked-up to. Currently only B5, B6, and B7 are supported.

`BACKLIGHT_BREATHING` is a fancier backlight feature that adds breathing/pulsing/fading effects to the backlight. It uses the same timer as the normal backlight. These breathing effects must be called by code in your keymap.

`BACKLIGHT_LEVELS` is how many levels exist for your backlight - max is 15, and they are computed automatically from this number.

## `/keyboards/<keyboard>/Makefile`

The values at the top likely won't need to be changed, since most boards use the `atmega32u4` chip. The `BOOTLOADER_SIZE` will need to be adjusted based on your MCU type. It's defaulted to the Teensy, since that's the most common controller. Below is quoted from the `Makefile`.

```
# Boot Section Size in *bytes*
#   Teensy halfKay   512
#   Teensy++ halfKay 1024
#   Atmel DFU loader 4096
#   LUFA bootloader  4096
#   USBaspLoader     2048
OPT_DEFS += -DBOOTLOADER_SIZE=512
```

At the bottom of the file, you'll find lots of features to turn on and off - all of these options should be set with `?=` to allow for the keymap overrides. `?=` only assigns if the variable was previously undefined. For the full documenation of these features, see the [Makefile options](#makefile-options).

## `/keyboards/<keyboard>/readme.md`

This is where you'll describe your keyboard - please write as much as you can about it! Talking about default functionality/features is useful here. Feel free to link to external pages/sites if necessary. Images can be included here as well. This file will be rendered into a webpage at qmk.fm/keyboards/<keyboard>/.

## `/keyboards/<keyboard>/<keyboard>.c`

This is where all of the custom logic for your keyboard goes - you may not need to put anything in this file, since a lot of things are configured automatically. All of the `*_kb()` functions are defined here. If you modify them, remember to keep the calls to `*_user()`, or things in the keymaps might not work. You can read more about the functions [here](#custom-quantum-functions-for-keyboards-and-keymaps)

## `/keyboards/<keyboard>/<keyboard>.h`

Here is where you can (optionally) define your `KEYMAP` function to remap your matrix into a more readable format. With ortholinear boards, this isn't always necessary, but it can help to accomodate the dead spots on your matrix, where there are keys that take up more than one space (2u, staggering, 6.25u, etc). The example shows the difference between the physical keys, and the matrix design:

```
#define KEYMAP( \
    k00, k01, k02, \
      k10,  k11   \
) \
{ \
    { k00, k01,   k02 }, \
    { k10, KC_NO, k11 }, \
}
```

Each of the `kxx` variables needs to be unique, and usually follows the format `k<row><col>`. You can place `KC_NO` where your dead keys are in your matrix.

# Unit Testing

If you are new to unit testing, then you can find many good resources on internet. However most of it is scattered around in small pieces here and there, and there's also many different opinions, so I won't give any recommendations.

Instead I recommend these two books, explaining two different styles of Unit Testing in detail.

* "Test Driven Development: By Example: Kent Beck"
* "Growing Object-Oriented Software, Guided By Tests: Steve Freeman, Nat Pryce"

If you prefer videos there are Uncle Bob's [Clean Coders Videos](https://cleancoders.com/), which unfortunately cost quite a bit, especially if you want to watch many of them. But James Shore has a free [Let's Play](http://www.jamesshore.com/Blog/Lets-Play) video series.

## Google Test and Google Mock
It's possible to Unit Test your code using [Google Test](https://github.com/google/googletest). The Google Test framework also includes another component for writing testing mocks and stubs, called "Google Mock". For information how to write the actual tests, please refer to the documentation on that site.

## Use of C++

Note that Google Test and therefore any test has to be written in C++, even if the rest of the QMK codebases is written in C. This should hopefully not be a problem even if you don't know any C++, since there's quite clear documentation and examples of the required C++ features, and you can write the rest of the test code almost as you would write normal C. Note that some compiler errors which you might get can look quite scary, but just read carefully what it says, and you should be ok.

One thing to remember, is that you have to append `extern "C"` around all of your C file includes.

## Adding tests for new or existing features

If you want to unit test some feature, then take a look at the existing serial_link tests, in the `quantum/serial_link/tests folder`, and follow the steps below to create a similar structure.

1. If it doesn't already exist, add a test subfolder to the folder containing the feature.
2. Create a `testlist.mk` and a `rules.mk` file in that folder.
3. Include those files from the root folder `testlist.mk`and `build_test.mk` respectively.
4. Add a new name for your testgroup to the `testlist.mk` file. Each group defined there will be a separate executable. And that's how you can support mocking out different parts. Note that it's worth adding some common prefix, just like it's done for the serial_link tests. The reason for that is that the make command allows substring filtering, so this way you can easily run a subset of the tests.
5. Define the source files and required options in the `rules.mk` file.
   * `_SRC` for source files
   * `_DEFS` for additional defines
   * `_INC` for additional include folders
6. Write the tests in a new cpp file inside the test folder you created. That file has to be one of the files included from the `rules.mk` file.

Note how there's several different tests, each mocking out a separate part. Also note that each of them only compiles the very minimum that's needed for the tests. It's recommend that you try to do the same. For a relevant video check out [Matt Hargett "Advanced Unit Testing in C & C++](https://www.youtube.com/watch?v=Wmy6g-aVgZI)

## Running the tests

To run all the tests in the codebase, type `make test`. You can also run test matching a substring by typing `make test-matchingsubstring` Note that the tests are always compiled with the native compiler of your platform, so they are also run like any other program on your computer.

## Debugging the tests

If there are problems with the tests, you can find the executable in the `./build/test` folder. You should be able to run those with GDB or a similar debugger.

## Full Integration tests

It's not yet possible to do a full integration test, where you would compile the whole firmware and define a keymap that you are going to test. However there are plans for doing that, because writing tests that way would probably be easier, at least for people that are not used to unit testing.

In that model you would emulate the input, and expect a certain output from the emulated keyboard.

# Tracing variables 

Sometimes you might wonder why a variable gets changed and where, and this can be quite tricky to track down without having a debugger. It's of course possible to manually add print statements to track it, but you can also enable the variable trace feature. This works for both for variables that are changed by the code, and when the variable is changed by some memory corruption.

To take the feature into use add `VARIABLE_TRACE=x` to the end of you make command. `x` represents the number of variables you want to trace, which is usually 1. 

Then at a suitable place in the code, call `ADD_TRACED_VARIABLE`, to begin the tracing. For example to trace all the layer changes, you can do this
```c
void matrix_init_user(void) {
  ADD_TRACED_VARIABLE("layer", &layer_state, sizeof(layer_state));
}
```

This will add a traced variable named "layer" (the name is just for your information), which tracks the memory location of `layer_state`. It tracks 4 bytes (the size of `layer_state`), so any modification to the variable will be reported. By default you can not specify a size bigger than 4, but you can change it by adding `MAX_VARIABLE_TRACE_SIZE=x` to the end of the make command line.

In order to actually detect changes to the variables you should call `VERIFY_TRACED_VARIABLES` around the code that you think that modifies the variable. If a variable is modified it will tell you between which two `VERIFY_TRACED_VARIABLES` calls the modification happened. You can then add more calls to track it down further. I don't recommend spamming the codebase with calls. It's better to start with a few, and then keep adding them in a binary search fashion. You can also delete the ones you don't need, as each call need to store the file name and line number in the ROM, so you can run out of memory if you add too many calls.

Also remember to delete all the tracing code once you have found the bug, as you wouldn't want to create a pull request with tracing code.