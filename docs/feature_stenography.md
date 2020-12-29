# Stenography in QMK :id=stenography-in-qmk

[Stenography](https://en.wikipedia.org/wiki/Stenotype) is a method of writing most often used by court reports, closed-captioning, and real-time transcription for the deaf. In stenography words are chorded syllable by syllable with a mixture of spelling, phonetic, and shortcut (briefs) strokes. Professional stenographers can reach 200-300 WPM without any of the strain usually found in standard typing and with far fewer errors (>99.9% accuracy).

The [Open Steno Project](http://www.openstenoproject.org/) has built an open-source program called Plover that provides real-time translation of steno strokes into words and commands. It has an established dictionary and supports

## Plover with QWERTY Keyboard :id=plover-with-qwerty-keyboard

Plover can work with any standard QWERTY keyboard, although it is more efficient if the keyboard supports NKRO (n-key rollover) to allow Plover to see all the pressed keys at once. An example keymap for Plover can be found in `planck/keymaps/default`. Switching to the `PLOVER` layer adjusts the position of the keyboard to support the number bar.

To use Plover with QMK just enable NKRO and optionally adjust your layout if you have anything other than a standard layout. You may also want to purchase some steno-friendly keycaps to make it easier to hit multiple keys.

## Plover with Steno Protocol :id=plover-with-steno-protocol

Plover also understands the language of several steno machines. QMK can speak a couple of these languages, TX Bolt and GeminiPR. An example layout can be found in `planck/keymaps/steno`.

When QMK speaks to Plover over a steno protocol Plover will not use the keyboard as input. This means that you can switch back and forth between a standard keyboard and your steno keyboard, or even switch layers from Plover to standard and back without needing to activate/deactivate Plover.

In this mode Plover expects to speak with a steno machine over a serial port so QMK will present itself to the operating system as a virtual serial port in addition to a keyboard. By default QMK will speak the TX Bolt protocol but can be switched to GeminiPR; the last protocol used is stored in non-volatile memory so QMK will use the same protocol on restart.

> Note: Due to hardware limitations you may not be able to run both a virtual serial port and mouse emulation at the same time.

### TX Bolt :id=tx-bolt

TX Bolt communicates the status of 24 keys over a very simple protocol in variable-sized (1-5 byte) packets.

### GeminiPR :id=geminipr

GeminiPR encodes 42 keys into a 6-byte packet. While TX Bolt contains everything that is necessary for standard stenography, GeminiPR opens up many more options, including supporting non-English theories.

## Configuring QMK for Steno :id=configuring-qmk-for-steno

Firstly, enable steno in your keymap's Makefile. You may also need disable mousekeys, extra keys, or another USB endpoint to prevent conflicts. The builtin USB stack for some processors only supports a certain number of USB endpoints and the virtual serial port needed for steno fills 3 of them.

```makefile
STENO_ENABLE = yes
MOUSEKEY_ENABLE = no
```

In your keymap create a new layer for Plover. You will need to include `keymap_steno.h`. See `planck/keymaps/steno/keymap.c` for an example. Remember to create a key to switch to the layer as well as a key for exiting the layer. If you would like to switch modes on the fly you can use the keycodes `QK_STENO_BOLT` and `QK_STENO_GEMINI`. If you only want to use one of the protocols you may set it up in your initialization function:

```c
void matrix_init_user() {
  steno_set_mode(STENO_MODE_GEMINI); // or STENO_MODE_BOLT
}
```

Once you have your keyboard flashed launch Plover. Click the 'Configure...' button. In the 'Machine' tab select the Stenotype Machine that corresponds to your desired protocol. Click the 'Configure...' button on this tab and enter the serial port or click 'Scan'. Baud rate is fine at 9600 (although you should be able to set as high as 115200 with no issues). Use the default settings for everything else (Data Bits: 8, Stop Bits: 1, Parity: N, no flow control).

On the display tab click 'Open stroke display'. With Plover disabled you should be able to hit keys on your keyboard and see them show up in the stroke display window. Use this to make sure you have set up your keymap correctly. You are now ready to steno!

## Learning Stenography :id=learning-stenography

* [Learn Plover!](https://sites.google.com/site/learnplover/)
* [QWERTY Steno](http://qwertysteno.com/Home/)
* [Steno Jig](https://joshuagrams.github.io/steno-jig/)
* More resources at the Plover [Learning Stenography](https://github.com/openstenoproject/plover/wiki/Learning-Stenography) wiki

## Interfacing with the code :id=interfacing-with-the-code

The steno code has three interceptable hooks. If you define these functions, they will be called at certain points in processing; if they return true, processing continues, otherwise it's assumed you handled things.

```c
bool send_steno_chord_user(steno_mode_t mode, uint8_t chord[6]);
```

This function is called when a chord is about to be sent. Mode will be one of `STENO_MODE_BOLT` or `STENO_MODE_GEMINI`. This represents the actual chord that would be sent via whichever protocol. You can modify the chord provided to alter what gets sent. Remember to return true if you want the regular sending process to happen.

```c
bool process_steno_user(uint16_t keycode, keyrecord_t *record) { return true; }
```

This function is called when a keypress has come in, before it is processed. The keycode should be one of `QK_STENO_BOLT`, `QK_STENO_GEMINI`, or one of the `STN_*` key values.

```c
bool postprocess_steno_user(uint16_t keycode, keyrecord_t *record, steno_mode_t mode, uint8_t chord[6], int8_t pressed);
```

This function is called after a key has been processed, but before any decision about whether or not to send a chord. If `IS_PRESSED(record->event)` is false, and `pressed` is 0 or 1, the chord will be sent shortly, but has not yet been sent. This is where to put hooks for things like, say, live displays of steno chords or keys.


## Keycode Reference :id=keycode-reference

As defined in `keymap_steno.h`.

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
|`STN_PR`|`STN_PR`| `-P`|
|`STN_RR`|`STN_RR`| `-R`|
|`STN_BR`|`STN_BR`| `-B`|
|`STN_LR`|`STN_LR`| `-L`|
|`STN_GR`|`STN_GR`| `-G`|
|`STN_TR`|`STN_TR`| `-T`|
|`STN_SR`|`STN_SR`| `-S`|
|`STN_DR`|`STN_DR`| `-D`|
|`STN_ZR`|`STN_ZR`| `-Z`|
|`STN_FN`|| (GeminiPR only)|
|`STN_RES1`||(GeminiPR only)|
|`STN_RES2`||(GeminiPR only)|
|`STN_PWR`||(GeminiPR only)|
