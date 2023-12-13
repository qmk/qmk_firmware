# OS Detection

This feature makes a best guess at the host OS based on OS specific behavior during USB setup.  It may not always get the correct OS, and shouldn't be relied on as for critical functionality.

Using it you can have OS specific key mappings or combos which work differently on different devices.

It is available for keyboards which use ChibiOS, LUFA and V-USB.

## Usage

In your `rules.mk` add:

```make
OS_DETECTION_ENABLE = yes
```

Include `"os_detection.h"` in your `keymap.c`.
It declares `os_variant_t detected_host_os(void);` which you can call to get detected OS.

It returns one of the following values:

```c
enum {
    OS_UNSURE,
    OS_LINUX,
    OS_WINDOWS,
    OS_MACOS,
    OS_IOS,
} os_variant_t;
```

?> Note that it takes some time after firmware is booted to detect the OS.
This time is quite short, probably hundreds of milliseconds, but this data may be not ready in keyboard and layout setup functions which run very early during firmware startup.

## Debug

If OS is guessed incorrectly, you may want to collect data about USB setup packets to refine the detection logic.

To do so in your `config.h` add:

```c
#define OS_DETECTION_DEBUG_ENABLE
```

And in your `rules.mk` add:

```make
CONSOLE_ENABLE = yes
```

And also include `"os_detection.h"` in your `keymap.c`.

Then you can define custom keycodes to store data about USB setup packets in EEPROM (persistent memory) and to print it later on host where you can run `qmk console`:

```c
enum custom_keycodes {
    STORE_SETUPS = SAFE_RANGE,
    PRINT_SETUPS,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case STORE_SETUPS:
            if (record->event.pressed) {
                store_setups_in_eeprom();
            }
            return false;
        case PRINT_SETUPS:
            if (record->event.pressed) {
                print_stored_setups();
            }
            return false;
    }
}
```

Then please open an issue on Github with this information and tell what OS was not detected correctly and if you have any intermediate devices between keyboard and your computer.


## Credits

Original idea is coming from [FingerprintUSBHost](https://github.com/keyboardio/FingerprintUSBHost) project.
