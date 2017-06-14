
## Audio output from a speaker

Your keyboard can make sounds! If you've got a Planck, Preonic, or basically any keyboard that allows access to the C6 port, you can hook up a simple speaker and make it beep. You can use those beeps to indicate layer transitions, modifiers, special keys, or just to play some funky 8bit tunes.

The audio code lives in [quantum/audio/audio.h](https://github.com/qmk/qmk_firmware/blob/master/quantum/audio/audio.h) and in the other files in the audio directory. It's enabled by default on the Planck [stock keymap](https://github.com/qmk/qmk_firmware/blob/master/keyboards/planck/keymaps/default/keymap.c). Here are the important bits:

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

Wherein we bind predefined songs (from [quantum/audio/song_list.h](https://github.com/qmk/qmk_firmware/blob/master/quantum/audio/song_list.h)) into named variables. This is one optimization that helps save on memory: These songs only take up memory when you reference them in your keymap, because they're essentially all preprocessor directives.

So now you have something called `tone_plover` for example. How do you make it play the Plover tune, then? If you look further down the keymap, you'll see this:

```
PLAY_NOTE_ARRAY(tone_plover, false, 0); // Signature is: Song name, repeat, rest style
```

This is inside one of the macros. So when that macro executes, your keyboard plays that particular chime.

"Rest style" in the method signature above (the last parameter) specifies if there's a rest (a moment of silence) between the notes.

## Music mode

The music mode maps your columns to a chromatic scale, and your rows to octaves. This works best with ortholinear keyboards, but can be made to work with others. All keycodes less than `0xFF` get blocked, so you won't type while playing notes - if you have special keys/mods, those will still work. A work-around for this is to jump to a different layer with KC_NOs before (or after) enabling music mode.  

Recording is experimental due to some memory issues - if you experience some weird behavior, unplugging/replugging your keyboard will fix things.

Keycodes available:

* `MU_ON` - Turn music mode on
* `MU_OFF` - Turn music mode off
* `MU_TOG` - Toggle music mode

In music mode, the following keycodes work differently, and don't pass through:

* `LCTL` - start a recording
* `LALT` - stop recording/stop playing
* `LGUI` - play recording
* `KC_UP` - speed-up playback
* `KC_DOWN` - slow-down playback

## MIDI functionalty

This is still a WIP, but check out `quantum/keymap_midi.c` to see what's happening. Enable from the Makefile.

## Bluetooth functionality

This requires [some hardware changes](https://www.reddit.com/r/MechanicalKeyboards/comments/3psx0q/the_planck_keyboard_with_bluetooth_guide_and/?ref=search_posts), but can be enabled via the Makefile. The firmware will still output characters via USB, so be aware of this when charging via a computer. It would make sense to have a switch on the Bluefruit to turn it off at will.

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

To hook up a Trackpoint, you need to obtain a Trackpoint module (i.e. harvest from a Thinkpad keyboard), identify the function of each pin of the module, and make the necessary circuitry between controller and Trackpoint module. For more information, please refer to [Trackpoint Hardware](https://deskthority.net/wiki/TrackPoint_Hardware) page on Deskthority Wiki.

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

