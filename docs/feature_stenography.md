# Stenography in QMK :id=stenography-in-qmk

[Stenography](https://en.wikipedia.org/wiki/Stenotype) is a method of writing most often used by court reports, closed-captioning, and real-time transcription for the deaf. In stenography words are chorded syllable by syllable with a mixture of spelling, phonetic, and shortcut (briefs) strokes. Professional stenographers can reach 200-300 WPM without any of the strain usually found in standard typing and with far fewer errors (>99.9% accuracy).

The [Open Steno Project](https://www.openstenoproject.org/) has built an open-source program called Plover that provides real-time translation of steno strokes into words and commands. It has an established dictionary and supports

## Plover with QWERTY Keyboard :id=plover-with-qwerty-keyboard

Plover can work with any standard QWERTY keyboard, although it is more efficient if the keyboard supports NKRO (n-key rollover) to allow Plover to see all the pressed keys at once. An example keymap for Plover can be found in `planck/keymaps/default`. Switching to the `PLOVER` layer adjusts the position of the keyboard to support the number bar.

To enable NKRO, add `NKRO_ENABLE = yes` in your `rules.mk` and make sure to press `NK_ON` to turn it on because `NKRO_ENABLE = yes` merely adds the possibility of switching to NKRO mode but it doesn't automatically switch to it. If you want to automatically switch, add `#define FORCE_NKRO` in your `config.h`.

You may also need to adjust your layout, either in QMK or in Plover, if you have anything other than a standard layout. You may also want to purchase some steno-friendly keycaps to make it easier to hit multiple keys.

## Plover with Steno Protocol :id=plover-with-steno-protocol

Plover also understands the language of several steno machines. QMK can speak a couple of these languages: TX Bolt and GeminiPR. An example layout can be found in `planck/keymaps/steno`.

When QMK speaks to Plover over a steno protocol, Plover will not use the keyboard as input. This means that you can switch back and forth between a standard keyboard and your steno keyboard, or even switch layers from Plover to standard and back without needing to activate/deactivate Plover.

In this mode, Plover expects to speak with a steno machine over a serial port so QMK will present itself to the operating system as a virtual serial port in addition to a keyboard.

> Note: Due to hardware limitations, you may not be able to run both a virtual serial port and mouse emulation at the same time.

### TX Bolt :id=tx-bolt

TX Bolt communicates the status of 24 keys over a very simple protocol in variable-sized (1-4 bytes) packets.

To enable it, add the following line to your `rules.mk`:
```mk
STENO_ENABLE_BOLT = yes
```

### GeminiPR :id=geminipr

GeminiPR encodes 42 keys into a 6-byte packet. While TX Bolt contains everything that is necessary for standard stenography, GeminiPR opens up many more options, including differentiating between top `S-` and bottom `S-`, and supporting non-English theories.

To enable it, add the following line to your `rules.mk`:
```mk
STENO_ENABLE_GEMINI = yes
```

### Switching protocols on the fly :id=switching-protocols-on-the-fly

If you wish to switch the serial protocol used to transfer the steno chords without having to recompile your keyboard firmware every time, you can press the `QK_STENO_BOLT` and `QK_STENO_GEMINI` keycodes in order to switch protocols on the fly.

To enable these special keycodes, add the following line to your `rules.mk`:
```mk
STENO_ENABLE_ALL = yes
```

?> To maintain backwards compatibility with older firmwares, the deprecated `STENO_ENABLE = yes` acts like `STENO_ENABLE_ALL = yes`.

The default protocol is TX Bolt but the last protocol used is stored in non-volatile memory so QMK will remember your choice between reboots of your keyboard &mdash; assuming that your keyboard features (emulated) EEPROM.

Naturally, this option takes the most amount of firmware space as it needs to compile the code for all the available stenography protocols. In most cases, compiling a single stenography protocol, by enabling the related `rules.mk` option, is sufficient.

Note that it is possible to compile the code for multiple protocols at once with something like:
```mk
STENO_ENABLE_ALL = no
STENO_ENABLE_BOLT = yes
STENO_ENABLE_GEMINI = yes
```
However, that only leads to unnecessary bloat; your keyboard will only use Gemini PR because it isn't be possible to switch between protocols with `QK_STENO_BOLT` or `QK_STENO_GEMINI` unless `STENO_ENABLE_ALL` is turned on.

## Configuring QMK for Steno :id=configuring-qmk-for-steno

Firstly, pick one of the `STENO_ENABLE_*` options to add to your `rules.mk`. You may also need disable mouse keys, extra keys, or another USB endpoint to prevent conflicts. The builtin USB stack for some processors only supports a certain number of USB endpoints and the virtual serial port needed for steno fills 3 of them.

!> If you had *explicitly* set `VIRSTER_ENABLE = no`, none of the serial stenography protocols (GeminiPR, TX Bolt) will work properly. You are expected to either set it to `yes`, remove the line from your `rules.mk` or send the steno chords yourself in an alternative way using the [provided interceptable hooks](#interfacing-with-the-code).

In your keymap, create a new layer for Plover, that you can fill in with the [steno keycodes](#keycode-reference) (you will need to include `keymap_steno.h`, see `planck/keymaps/steno/keymap.c` for an example). Remember to create a key to switch to the layer as well as a key for exiting the layer. 

Once you have your keyboard flashed, launch Plover. Click the 'Configure...' button. In the 'Machine' tab, select the Stenotype Machine that corresponds to your desired protocol. Click the 'Configure...' button on this tab and enter the serial port or click 'Scan'. Baud rate is fine at 9600 (although you should be able to set as high as 115200 with no issues). Use the default settings for everything else (Data Bits: 8, Stop Bits: 1, Parity: N, no flow control).

To test your keymap, you can chord keys on your keyboard and either look at the output of the 'paper tape' (Tools > Paper Tape) or that of the 'layout display' (Tools > Layout Display). If your strokes correctly show up, you are now ready to steno!

## Learning Stenography :id=learning-stenography

* [Learn Plover!](https://sites.google.com/site/learnplover/)
* [Steno Jig](https://joshuagrams.github.io/steno-jig/)
* More resources at the Plover [Learning Stenography](https://github.com/openstenoproject/plover/wiki/Learning-Stenography) wiki

## Interfacing with the code :id=interfacing-with-the-code

The steno code has three interceptable hooks. If you define these functions, they will be called at certain points in processing; if they return true, processing continues, otherwise it's assumed you handled things.

```c
bool send_steno_chord_user(steno_mode_t mode, uint8_t chord[MAX_STROKE_SIZE]);
```

This function is called when a chord is about to be sent. Mode will be one of `STENO_MODE_BOLT` or `STENO_MODE_GEMINI`. This represents the actual chord that would be sent via whichever protocol. You can modify the chord provided to alter what gets sent. Remember to return true if you want the regular sending process to happen.

```c
bool process_steno_user(uint16_t keycode, keyrecord_t *record) { return true; }
```

This function is called when a keypress has come in, before it is processed. The keycode should be one of `QK_STENO_BOLT`, `QK_STENO_GEMINI`, or one of the `STN_*` key values.

```c
bool postprocess_steno_user(uint16_t keycode, keyrecord_t *record, steno_mode_t mode, uint8_t chord[MAX_STROKE_SIZE], int8_t n_pressed_keys);
```

This function is called after a key has been processed, but before any decision about whether or not to send a chord. If `IS_PRESSED(record->event)` is false, and `n_pressed_keys` is 0 or 1, the chord will be sent shortly, but has not yet been sent. This is where to put hooks for things like, say, live displays of steno chords or keys.


## Keycode Reference :id=keycode-reference

You must include `keymap_steno.h` to your `keymap.c` with `#include "keymap_steno.h"` before you can use these keycodes

> Note: TX Bolt does not support the full set of keys. The TX Bolt implementation in QMK will map the GeminiPR keys to the nearest TX Bolt key so that one key map will work for both.

|GeminiPR|TX Bolt|Steno Key|
|--------|-------|-----------|
|`STN_N1`|`STN_NUM`|Number bar #1|
|`STN_N2`|`STN_NUM`|Number bar #2|
|`STN_N3`|`STN_NUM`|Number bar #3|
|`STN_N4`|`STN_NUM`|Number bar #4|
|`STN_N5`|`STN_NUM`|Number bar #5|
|`STN_N6`|`STN_NUM`|Number bar #6|
|`STN_N7`|`STN_NUM`|Number bar #7|
|`STN_N8`|`STN_NUM`|Number bar #8|
|`STN_N9`|`STN_NUM`|Number bar #9|
|`STN_NA`|`STN_NUM`|Number bar #A|
|`STN_NB`|`STN_NUM`|Number bar #B|
|`STN_NC`|`STN_NUM`|Number bar #C|
|`STN_S1`|`STN_SL`| `S-` upper|
|`STN_S2`|`STN_SL`| `S-` lower|
|`STN_TL`|`STN_TL`| `T-`|
|`STN_KL`|`STN_KL`| `K-`|
|`STN_PL`|`STN_PL`| `P-`|
|`STN_WL`|`STN_WL`| `W-`|
|`STN_HL`|`STN_HL`| `H-`|
|`STN_RL`|`STN_RL`| `R-`|
|`STN_A`|`STN_A`| `A` vowel|
|`STN_O`|`STN_O`| `O` vowel|
|`STN_ST1`|`STN_STR`| `*` upper-left |
|`STN_ST2`|`STN_STR`| `*` lower-left|
|`STN_ST3`|`STN_STR`| `*` upper-right|
|`STN_ST4`|`STN_STR`| `*` lower-right|
|`STN_E`|`STN_E`| `E` vowel|
|`STN_U`|`STN_U`| `U` vowel|
|`STN_FR`|`STN_FR`| `-F`|
|`STN_RR`|`STN_RR`| `-R`|
|`STN_PR`|`STN_PR`| `-P`|
|`STN_BR`|`STN_BR`| `-B`|
|`STN_LR`|`STN_LR`| `-L`|
|`STN_GR`|`STN_GR`| `-G`|
|`STN_TR`|`STN_TR`| `-T`|
|`STN_SR`|`STN_SR`| `-S`|
|`STN_DR`|`STN_DR`| `-D`|
|`STN_ZR`|`STN_ZR`| `-Z`|
|`STN_FN`|| (Function)|
|`STN_RES1`||(Reset 1)|
|`STN_RES2`||(Reset 2)|
|`STN_PWR`||(Power)|

If you do not want to hit two keys with one finger combined keycodes can be used. These are also defined in `keymap_steno.h`, and causes both keys to be reported as pressed or released. To use these keycodes define `STENO_COMBINEDMAP` in your `config.h` file.

|Combined key   | Key1   | Key 2    |
|---------------|--------|----------|
|STN_S3         | STN_S1 | STN_S2   |
|STN_TKL        | STN_TL | STN_KL   |
|STN_PWL        | STN_PL | STN_WL   |
|STN_HRL        | STN_HL | STN_RL   |
|STN_FRR        | STN_FR | STN_RR   |
|STN_PBR        | STN_PR | STN_BR   |
|STN_LGR        | STN_LR | STN_GR   |
|STN_TSR        | STN_TR | STN_SR   |
|STN_DZR        | STN_DR | STN_ZR   |
|STN_AO         | STN_A  | STN_O    |
|STN_EU         | STN_E  | STN_U    |
