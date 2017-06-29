# Understanding QMK's Code

<!-- toc -->

This document attempts to explain how the QMK firmware works from a very high level. It assumes you understand basic programming concepts but does not (except where needed to demonstrate) assume familiarity with C. It assumes that you have a basic understanding of the following documents:

* [QMK Overview](qmk_overview.md)
* [How Keyboards Work](basic_how_keyboards_work.md)
* [FAQ](faq.md)

## Startup

You can think of QMK as no different from any other computer program. It is started, performs its tasks, and then ends. The entry point for the program is the `main()` function, just like it is on any other C program. However, for a newcomer to QMK it can be confusing because the `main()` function appears in multiple places, and it can be hard to tell which one to look at.

The reason for this is the different platforms that QMK supports. The most common platform is `lufa`, which runs on AVR processors such at the atmega32u4. We also support `chibios`, `pjrc`, `vusb`, and `bluefruit`, and may support more in the future.

Let's focus on AVR processors for the moment, which use the `lufa` platform. You can find the `main()` function in [tmk_core/protocol/lufa/lufa.c](https://github.com/qmk/qmk_firmware/blob/master/tmk_core/protocol/lufa/lufa.c#L1129). If you browse through that function you'll find that it initializes any hardware that has been configured (including USB to the host) and then it starts the core part of the program with a [`while(1)`](https://github.com/qmk/qmk_firmware/blob/master/tmk_core/protocol/lufa/lufa.c#L1182). This is [The Main Loop](#the_main_loop).

## The Main Loop

This section of code is called "The Main Loop" because it's responsible for looping over the same set of instructions forever. This is where QMK dispatches out to the functions responsible for making the keyboard do everything it is supposed to. At first glance it can look like a lot of functionality but most of the time the code will be disabled by `#define`'s.

### USB Suspend

```
    #if !defined(NO_USB_STARTUP_CHECK)
    while (USB_DeviceState == DEVICE_STATE_Suspended) {
        print("[s]");
        suspend_power_down();
        if (USB_Device_RemoteWakeupEnabled && suspend_wakeup_condition()) {
                USB_Device_SendRemoteWakeup();
        }
    }
    #endif
```

This section of code handles the USB suspend state. This state is entered when the computer the keyboard is plugged into is suspended. In this state we don't do anything but wait for the computer we're plugged into to wake up.

### `keyboard_task()`

```
    keyboard_task();
```

This is where all the keyboard specific functionality is dispatched. The source code for `keyboard_task()` can be found in [tmk_core/common/keyboard.c](https://github.com/qmk/qmk_firmware/blob/master/tmk_core/common/keyboard.c#L154), and it is responsible for detecting changes in the matrix and turning LED's on and off.

Within `keyboard_task()` you'll find code to handle:

* Matrix Scanning
* Mouse Handling
* Serial Link(s)
* Visualizer
* Keyboard state LED's (Caps Lock, Num Lock, Scroll Lock)

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

Matrix Scanning runs many times per second. The exact rate varies but typically it runs at least 10 times per second to avoid perceptable lag.

##### Matrix to Physical Layout Map

Once we know the state of every switch on our keyboard we have to map that to a keycode. In QMK this is done by making use of C macros to allow us to separate the definition of the physical layout from the definition of keycodes.

At the keyboard level we define a C macro (typically named `KEYMAP()`) which maps our keyboard's matrix to physical keys. Sometimes the matrix does not have a switch in every location, and we can use this macro to pre-populate those with KC_NO, making the keymap definition easier to work with. Here's an example `KEYMAP()` macro for a numpad:

```c
#define KEYMAP( \
    k00, k01, k02, k03, \
    k10, k11, k12, k13, \
    k20, k21, k22, \
    k30, k31, k32, k33, \
    k40,      k42 \
) { \
    { k00, k01, k02, k03, }, \
    { k10, k11, k12, k13, }, \
    { k20, k21, k22, KC_NO, }, \
    { k30, k31, k32, k33, }, \
    { k40, KC_NO, k42, KC_NO } \
}
```

Notice how the second block of our `KEYMAP()` macro matches the Matrix Scanning array above? This macro is what will map the matrix scanning array to keycodes. However, if you look at a 17 key numpad you'll notice that it has 3 places where the matrix could have a switch but doesn't, due to larger keys. We have populated those spaces with `KC_NO` so that our keymap definition doesn't have to.

You can also use this macro to handle unusual matrix layouts, for example the [Clueboard rev 2](https://github.com/qmk/qmk_firmware/blob/master/keyboards/clueboard/rev2/rev2.h). Explaining that is outside the scope of this document.

##### Keycode Assignment

At the keymap level we make use of our `KEYMAP()` macro above to map keycodes to physical locations to matrix locations. It looks like this:

```
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = KEYMAP(
  KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, \
  KC_P7,   KC_P8,   KC_P9,   KC_PPLS, \
  KC_P4,   KC_P5,   KC_P6, \
  KC_P1,   KC_P2,   KC_P3,   KC_PENT, \
  KC_P0,            KC_PDOT)
}
```

Notice how all of these arguments match up with the first half of the `KEYMAP()` macro from the last section? This is basically where we take a keycode and map it to our Matrix Scan from earlier. 

##### State Change Detection

The matrix scanning described above tells us the state of the matrix at a given moment, but your computer only wants to know about changes, it doesn't care about the current state. QMK stores the results from the last matrix scan and compares the results from this matrix to determine when a key has been pressed or released. 

Let's look at an example. We'll hop into the middle of a keyboard scanning look to find that our previous scan looks like this:

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

Comparing against our keymap we can see that the pressed key is KC_NLCK. From here we dispatch to the `process_record` set of functions.

(FIXME: Feels like this section could be fleshed out more.)

(FIXME: Magic happens between here and process_record)

##### Process Record

The `process_record()` function itself is deceptively simple, but hidden within is a gateway to overriding functionality at various levels of QMK. The chain of events looks something like this:

* `void process_record(keyrecord_t *record)`
  * `bool process_record_quantum(keyrecord_t *record)`
    * Map this record to a keycode
    * `bool process_record_kb(uint16_t keycode, keyrecord_t *record)`
      * `bool process_record_user(uint16_t keycode, keyrecord_t *record)`
    * `bool process_midi(uint16_t keycode, keyrecord_t *record)`
    * `bool process_audio(uint16_t keycode, keyrecord_t *record)`
    * `bool process_music(uint16_t keycode, keyrecord_t *record)`
    * `bool process_tap_dance(uint16_t keycode, keyrecord_t *record)`
    * `bool process_leader(uint16_t keycode, keyrecord_t *record)`
    * `bool process_chording(uint16_t keycode, keyrecord_t *record)`
    * `bool process_combo(uint16_t keycode, keyrecord_t *record)`
    * `bool process_unicode(uint16_t keycode, keyrecord_t *record)`
    * `bool process_ucis(uint16_t keycode, keyrecord_t *record)`
    * `bool process_printer(uint16_t keycode, keyrecord_t *record)`
    * `bool process_unicode_map(uint16_t keycode, keyrecord_t *record)`
    * Identify and process quantum specific keycodes
  * Identify and process standard keycodes
  
At any step during this chain of events a function (such as `process_record_kb()`) can `return false` and processing of that keypress will end immediately.

#### Mouse Handling

FIXME: This needs to be written

#### Serial Link(s)

FIXME: This needs to be written

#### Visualizer

FIXME: This needs to be written

#### Keyboard state LED's (Caps Lock, Num Lock, Scroll Lock)

FIXME: This needs to be written
