# OS Detection

This feature makes a best guess at the host OS based on OS specific behavior during USB setup.  It may not always get the correct OS, and shouldn't be relied on as for critical functionality.

Using it you can have OS specific key mappings or combos which work differently on different devices.

It is available for keyboards which use ChibiOS, LUFA and V-USB.

## Usage

In your `rules.mk` add:

```make
OS_DETECTION_ENABLE = yes
```

It will automatically include the required headers file.
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

::: tip
Note that it takes some time after firmware is booted to detect the OS.
:::
This time is quite short, probably hundreds of milliseconds, but this data may be not ready in keyboard and layout setup functions which run very early during firmware startup.

## Callbacks {#callbacks}

If you want to perform custom actions when the OS is detected, then you can use the `process_detected_host_os_kb` function on the keyboard level source file, or `process_detected_host_os_user` function in the user `keymap.c`.

```c
bool process_detected_host_os_kb(os_variant_t detected_os) {
    if (!process_detected_host_os_user(detected_os)) {
        return false;
    }
    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            rgb_matrix_set_color_all(RGB_WHITE);
            break;
        case OS_WINDOWS:
            rgb_matrix_set_color_all(RGB_BLUE);
            break;
        case OS_LINUX:
            rgb_matrix_set_color_all(RGB_ORANGE);
            break;
        case OS_UNSURE:
            rgb_matrix_set_color_all(RGB_RED);
            break;
    }
    
    return true;
}
```

## OS detection stability

The OS detection is currently handled while the USB device descriptor is being assembled. 
The process is done in steps, generating a number of intermediate results until it stabilizes.
We therefore resort to debouncing the result until it has been stable for a given amount of milliseconds.
This amount can be configured, in case your board is not stable within the default debouncing time of 200ms.

## Configuration Options

* `#define OS_DETECTION_DEBOUNCE 250`
  * defined the debounce time for OS detection, in milliseconds
  * defaults to 250ms
* `#define OS_DETECTION_KEYBOARD_RESET`
  * enables the keyboard reset upon a USB device reinitilization
  * this setting may help with detection issues when switching between devices on some KVMs (see [Troubleshooting](#troubleshooting))
* `#define OS_DETECTION_SINGLE_REPORT`
  * allows the report callbacks to be called only once, when the OS detection result is considered stable
  * subsequent changes in the detection results, if any, are ignored
  * this setting may help with delayed stability issues when switching devices on some KVMs (see [Troubleshooting](#troubleshooting))
  
## Troubleshooting

Some KVMs and USB switches may cause issues when the OS detection is turned on. 
Here is a list of common issues and how to fix them:

* **Problem**: _keyboard won't redetect the OS when switching between machines using a KVM_
    * **Explanation**: some KVMs keep the USB controller powered on during the switch and OS
    detection happens when the USB device description is being assembled.
    * **Solution**: use `OS_DETECTION_KEYBOARD_RESET` to force the keyboard to reset upon switching.
* **Problem**: _keyboard OS detection callback gets invoked even minuted after startup_
    * **Explanation**: some OSes, notably macOS on ARM-based Macs, may cause this behavior. 
    The actual cause is not known at this time.'
    * **Solution**: use `OS_DETECTION_SINGLE_REPORT` to suppress repeated callback invocations.


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
