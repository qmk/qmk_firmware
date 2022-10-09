# Understanding QMK's Code

This document attempts to explain how the QMK firmware works from a very high level. It assumes you understand basic programming concepts but does not (except where needed to demonstrate) assume familiarity with C. It assumes that you have a basic understanding of the following documents:

* [Introduction](getting_started_introduction.md)
* [How Keyboards Work](how_keyboards_work.md)
* [FAQ](faq_general.md)

## Startup

You can think of QMK as no different from any other computer program. It is started and performs its tasks, but this program never finishes. Like other C programs, the entry point is the `main()` function. For QMK, the `main()` function is found in [`quantum/main.c`](https://github.com/qmk/qmk_firmware/blob/0.15.13/quantum/main.c#L55).

If you browse through the `main()` function you'll find that it starts by initializing any hardware that has been configured (including USB to the host). The most common platform for QMK is `lufa`, which runs on AVR processors such as the atmega32u4. When compiled for that platform, it will invoke for example `platform_setup()` in [`platforms/avr/platform.c`](https://github.com/qmk/qmk_firmware/blob/0.15.13/platforms/avr/platform.c#L19) and `protocol_setup()` in [`tmk_core/protocol/lufa/lufa.c`](https://github.com/qmk/qmk_firmware/blob/0.15.13/tmk_core/protocol/lufa/lufa.c#L1066). It will use other implementations when compiled for other platforms like `chibios` and `vusb`. At first glance, it can look like a lot of functionality but most of the time the code will be disabled by `#define`s.

The `main()` function will then start the core part of the program with a [`while (true)`](https://github.com/qmk/qmk_firmware/blob/0.15.13/quantum/main.c#L63). This is [The Main Loop](#the-main-loop).

## The Main Loop

This section of code is called "The Main Loop" because it's responsible for looping over the same set of instructions forever, without ever reaching the end. This is where QMK dispatches out to the functions responsible for making the keyboard do everything it is supposed to do.

The main loop will call [`protocol_task()`](https://github.com/qmk/qmk_firmware/blob/0.15.13/quantum/main.c#L38), which in turn will call `keyboard_task()` in [`quantum/keyboard.c`](https://github.com/qmk/qmk_firmware/blob/0.15.13/quantum/keyboard.c#L377). This is where all the keyboard specific functionality is dispatched, and it is responsible for detecting changes in the matrix and turning status LEDs on and off.

Within `keyboard_task()` you'll find code to handle:

* [Matrix Scanning](#matrix-scanning)
* Mouse Handling
* Keyboard status LEDs (Caps Lock, Num Lock, Scroll Lock)

#### Matrix Scanning

Matrix scanning is the core function of a keyboard firmware. It is the process of detecting which keys are currently pressed, and your keyboard runs this function many times a second. It's no exaggeration to say that 99% of your firmware's CPU time is spent on matrix scanning.

While there are different strategies for doing the actual matrix detection, they are out of scope for this document. It is sufficient to treat matrix scanning as a black box, you ask for the matrix's current state and get back a datastructure that looks like this:


```
{
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
}
```

That datastructure is a direct representation of the matrix for a 4 row by 5 column numpad. When a key is pressed that key's position within the matrix will be returned as `1` instead of `0`.

Matrix Scanning runs many times per second. The exact rate varies but typically it runs at least 10 times per second to avoid perceptible lag.

##### Matrix to Physical Layout Map

Once we know the state of every switch on our keyboard we have to map that to a keycode. In QMK this is done by making use of C macros to allow us to separate the definition of the physical layout from the definition of keycodes.

At the keyboard level we define a C macro (typically named `LAYOUT()`) which maps our keyboard's matrix to physical keys. Sometimes the matrix does not have a switch in every location, and we can use this macro to pre-populate those with KC_NO, making the keymap definition easier to work with. Here's an example `LAYOUT()` macro for a numpad:

```c
#define LAYOUT( \
    k00, k01, k02, k03, \
    k10, k11, k12, k13, \
    k20, k21, k22, \
    k30, k31, k32, k33, \
    k40,      k42 \
) { \
    { k00, k01,   k02, k03   }, \
    { k10, k11,   k12, k13   }, \
    { k20, k21,   k22, KC_NO }, \
    { k30, k31,   k32, k33   }, \
    { k40, KC_NO, k42, KC_NO } \
}
```

Notice how the second block of our `LAYOUT()` macro matches the Matrix Scanning array above? This macro is what will map the matrix scanning array to keycodes. However, if you look at a 17 key numpad you'll notice that it has 3 places where the matrix could have a switch but doesn't, due to larger keys. We have populated those spaces with `KC_NO` so that our keymap definition doesn't have to.

You can also use this macro to handle unusual matrix layouts, for example the [Alice](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/keyboards/sneakbox/aliceclone/aliceclone.h#L24). Explaining that is outside the scope of this document.

##### Keycode Assignment

At the keymap level we make use of our `LAYOUT()` macro above to map keycodes to physical locations to matrix locations. It looks like this:

```c
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,   KC_P5,   KC_P6,
        KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_P0,            KC_PDOT
    )
}
```

Notice how all of these arguments match up with the first half of the `LAYOUT()` macro from the last section? This is how we take a keycode and map it to our Matrix Scan from earlier.

##### State Change Detection

The matrix scanning described above tells us the state of the matrix at a given moment, but your computer only wants to know about changes, it doesn't care about the current state. QMK stores the results from the last matrix scan and compares the results from this matrix to determine when a key has been pressed or released.

Let's look at an example. We'll hop into the middle of a keyboard scanning loop to find that our previous scan looks like this:

```
{
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
}
```

And when our current scan completes it will look like this:

```
{
    {1,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
}
```

Comparing against our keymap we can see that the pressed key is `KC_NUM`. From here we dispatch to the `process_record` set of functions.

<!-- FIXME: Magic happens between here and process_record -->

##### Process Record

The `process_record()` function itself is deceptively simple, but hidden within is a gateway to overriding functionality at various levels of QMK. The chain of events is listed below, using cluecard whenever we need to look at the keyboard/keymap level functions. Depending on options set in `rules.mk` or elsewhere, only a subset of the functions below will be included in final firmware.

* [`void action_exec(keyevent_t event)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/action.c#L78-L140)
    * [`void pre_process_record_quantum(keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/quantum.c#L204)
      * [`bool process_combo(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/process_keycode/process_combo.c#L521)
  * [`void process_record(keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/action.c#L254)
    * [`bool process_record_quantum(keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/quantum.c#L224)
      * [Map this record to a keycode](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/quantum.c#L225)
      * [`void velocikey_accelerate(void)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/velocikey.c#L27)
      * [`void update_wpm(uint16_t keycode)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/wpm.c#L109)
      * [`void preprocess_tap_dance(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/process_keycode/process_tap_dance.c#L118)
      * [`bool process_key_lock(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/process_keycode/process_key_lock.c#L64)
      * [`bool process_dynamic_macro(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/process_keycode/process_dynamic_macro.c#L160)
      * [`bool process_clicky(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/process_keycode/process_clicky.c#L84)
      * [`bool process_haptic(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/process_keycode/process_haptic.c#L87)
      * [`bool process_record_via(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/via.c#L160)
      * [`bool process_record_kb(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/keyboards/planck/ez/ez.c#L271)
        * [`bool process_record_user(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/keyboards/planck/keymaps/default/keymap.c#L183)
      * [`bool process_secure(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/process_keycode/process_secure.c#L23)
      * [`bool process_sequencer(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/process_keycode/process_sequencer.c#L19)
      * [`bool process_midi(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/process_keycode/process_midi.c#L75)
      * [`bool process_audio(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/process_keycode/process_audio.c#L18)
      * [`bool process_backlight(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/process_keycode/process_backlight.c#L25)
      * [`bool process_steno(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/process_keycode/process_steno.c#L159)
      * [`bool process_music(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/process_keycode/process_music.c#L103)
      * [`bool process_key_override(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/5a1b857dea45a17698f6baa7dd1b7a7ea907fb0a/quantum/process_keycode/process_key_override.c#L397)
      * [`bool process_tap_dance(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/process_keycode/process_tap_dance.c#L135)
      * [`bool process_caps_word(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/process_keycode/process_caps_word.c#L17)
      * [`bool process_unicode_common(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/process_keycode/process_unicode_common.c#L290)
        calls one of:
          * [`bool process_unicode(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/process_keycode/process_unicode.c#L21)
          * [`bool process_unicodemap(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/process_keycode/process_unicodemap.c#L42)
          * [`bool process_ucis(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/process_keycode/process_ucis.c#L70)
      * [`bool process_leader(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/process_keycode/process_leader.c#L48)
      * [`bool process_printer(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/process_keycode/process_printer.c#L77)
      * [`bool process_auto_shift(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/process_keycode/process_auto_shift.c#L353)
      * [`bool process_dynamic_tapping_term(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/process_keycode/process_dynamic_tapping_term.c#L35)
      * [`bool process_space_cadet(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/process_keycode/process_space_cadet.c#L123)
      * [`bool process_magic(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/process_keycode/process_magic.c#L40)
      * [`bool process_grave_esc(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/process_keycode/process_grave_esc.c#L23)
      * [`bool process_rgb(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/process_keycode/process_rgb.c#L53)
      * [`bool process_joystick(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/process_keycode/process_joystick.c#L9)
      * [`bool process_programmable_button(uint16_t keycode, keyrecord_t *record)`](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/process_keycode/process_programmable_button.c#L21)
      * [Identify and process Quantum-specific keycodes](https://github.com/qmk/qmk_firmware/blob/325da02e57fe7374e77b82cb00360ba45167e25c/quantum/quantum.c#L343)

At any step during this chain of events a function (such as `process_record_kb()`) can `return false` to halt all further processing.

After this is called, `post_process_record()` is called, which can be used to handle additional cleanup that needs to be run after the keycode is normally handled.

* [`void post_process_record(keyrecord_t *record)`]()
  * [`void post_process_record_quantum(keyrecord_t *record)`]()
    * [Map this record to a keycode]()
    * [`void post_process_clicky(uint16_t keycode, keyrecord_t *record)`]()
    * [`void post_process_record_kb(uint16_t keycode, keyrecord_t *record)`]()
      * [`void post_process_record_user(uint16_t keycode, keyrecord_t *record)`]()

<!--
#### Mouse Handling

FIXME: This needs to be written

#### Serial Link(s)

FIXME: This needs to be written

#### Keyboard state LEDs (Caps Lock, Num Lock, Scroll Lock)

FIXME: This needs to be written

-->
