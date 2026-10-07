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

## Runtime toggle {#runtime-toggle}

Add `QK_OS_DETECTION_TOGGLE` (short alias `QK_OS_TOG`, value `0x7C7D`) to your keymap to turn OS detection off or on. It requires `OS_DETECTION_ENABLE`. The default handler commits the toggle on key release so an enabling restart cannot reprocess a still-held key at boot.

The setting is stored as a disabled flag in the existing EEPROM keymap configuration, without reserving another EEPROM region or changing the dynamic-keymap layout. Detection is enabled by default, and resetting EEPROM restores that default. The saved setting survives keyboard restarts and power loss.

Disabling takes effect on release without restarting the keyboard. It clears the current detection state and stops OS fingerprinting, automatic OS-detection resets, report callbacks, and debug trace collection in RAM. `detected_host_os()` returns `OS_UNSURE` while disabled. The currently selected layer is unchanged; manual layer switching remains available.

Enabling saves the setting and restarts the keyboard once so detection can collect a fresh USB fingerprint. This restart does not require `OS_DETECTION_KEYBOARD_RESET`. Toggling detection does not erase an existing diagnostic snapshot in EEPROM.

Unlike `QK_OS_SKIP`, which temporarily suppresses OS-detection callbacks and automatic resets while held, `QK_OS_TOG` persistently disables detection itself.

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

OS detection observes the `wLength` values of USB string-descriptor requests while the USB descriptors are being assembled, not HID report-descriptor requests.
The process is done in steps, generating a number of intermediate results until it stabilizes.
We therefore resort to debouncing the result until it has been stable for a given amount of milliseconds.
This amount can be configured, in case your board is not stable within the default debouncing time of 250ms.

Some KVMs keep the keyboard powered while switching hosts and need a real keyboard restart to force USB descriptor assembly. `OS_DETECTION_KEYBOARD_RESET` enables that restart after an eligible USB reinitialization; detection is not cleared and rerun in place.

## Configuration Options

* `#define OS_DETECTION_DEBOUNCE 250`
  * defined the debounce time for OS detection, in milliseconds
  * defaults to 250ms
* `#define OS_DETECTION_KEYBOARD_RESET`
  * Restarts the entire keyboard on USB reinitialization after a stable configured REPORT-protocol session, including sessions with an unknown OS or no string-descriptor requests.
  * BOOT protocol clears eligibility and cancels queued resets even if the fingerprint resembles a known OS. BIOS/UEFI may remain in REPORT protocol, so this policy alone cannot guarantee that BIOS boot loops are prevented.
  * Eligibility is remembered across USB initialization rather than rearmed by its default REPORT protocol. Switching from a stable configured REPORT session can therefore restart the keyboard even when the new host requests no strings.
* `#define OS_DETECTION_RESET_DEBOUNCE 250`
  * Requires this many milliseconds without USB state notifications or any USB descriptor request before an automatic reset executes; defaults to `OS_DETECTION_DEBOUNCE`.
  * The quiet period gives a late `SET_PROTOCOL(BOOT)` request time to cancel a queued restart.
* `#define OS_DETECTION_BOOT_LOOP_GUARD`
  * Opts into the persistent automatic-reboot limiter described below; requires `OS_DETECTION_KEYBOARD_RESET`.
* `#define OS_DETECTION_SKIP_RESET_KEY QK_OS_DETECTION_SKIP_RESET`
  * Sets the held keycode that suppresses OS-detection resets; `QK_OS_SKIP` is its short alias.
  * An ordinary keycode such as `KC_F12` may be used instead; it retains its normal key behavior.
  * Automatic re-enumeration resets and OS-detection callbacks are suppressed while the key is held. Suppressed resets are canceled, not delayed until release. Fingerprint collection continues so a pending OS decision can be reported after release without another enumeration.
  * The debounced matrix is checked directly, including a held `MO()` layer key before its event is processed. Holding the toggle key also suppresses automatic re-enumeration during a mode change. The persistent detection toggle is unchanged; manual reboot and bootloader keys are unaffected.
* `#define OS_DETECTION_SINGLE_REPORT`
  * Reports the first stable result once per keyboard boot.
  * Later fingerprint changes are ignored until the keyboard restarts; USB reinitialization alone does not rearm reporting. Automatic-reset eligibility is independent of whether the OS was identified.
  * this setting may help with delayed stability issues when switching devices on some KVMs (see [Troubleshooting](#troubleshooting))
  

## Automatic reboot guard

With `OS_DETECTION_BOOT_LOOP_GUARD`, automatic resets use a separate EEPROM record containing a validity marker, a consecutive rapid-reset count, and the firmware uptime of the last permitted automatic-reset request. The defaults can be overridden in `config.h`:

```c
#define OS_DETECTION_BOOT_LOOP_GUARD
#define OS_DETECTION_BOOT_LOOP_GUARD_FAST_MS 1000
#define OS_DETECTION_BOOT_LOOP_GUARD_MAX_REBOOTS 3
#define OS_DETECTION_BOOT_LOOP_GUARD_REARM_MS 5000
```

A permitted automatic-reset request at `timer_read32()` uptime strictly below `FAST_MS` increments the count. A permitted request at or beyond that uptime clears the consecutive count. Three rapid requests are allowed by default; the fourth is canceled. Once the count reaches `MAX_REBOOTS`, later uptime does not unblock resets: USB must remain continuously `CONFIGURED` for `REARM_MS` to clear the count. Leaving that state restarts the stable-link interval; LED, idle-rate, or protocol notifications while still configured do not. Canceling a blocked request also discards its reset history, so rearming cannot execute that stale request.

These measurements are firmware uptime within each boot, not wall-clock intervals between resets or power cycles. The persistent count survives reconnects and manual restarts. Manual reboot, bootloader entry, and the explicit restart when re-enabling detection are not limited by the guard. EEPROM writes occur only when committing a permitted automatic-reset request, or once when a stable configured link clears a positive count.

This limits only resets classified as rapid by that uptime threshold. A loop whose requests occur at or beyond `FAST_MS` breaks the consecutive count and is not bounded by this guard; tune the threshold based on the captured request uptime if necessary. BOOT cancellation and the guard do not provide a universal BIOS/UEFI compatibility guarantee.

The guard uses `OS_DETECTION_BOOT_LOOP_GUARD_EEPROM_SIZE` bytes (7). Its default `OS_DETECTION_BOOT_LOOP_GUARD_EEPROM_ADDR` follows the 104-byte diagnostic reservation when debugging is enabled, or starts at `EECONFIG_SIZE` otherwise. It must not overlap other settings. VIA and dynamic keymaps require an explicitly reserved guard address, in addition to any debug reservation; capacity and diagnostic-record overlap are checked at compile time. For example, a VIA build with both records can reserve:

```c
#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 111
#define OS_DETECTION_DEBUG_EEPROM_ADDR VIA_EEPROM_CUSTOM_CONFIG_ADDR
#define OS_DETECTION_BOOT_LOOP_GUARD_EEPROM_ADDR (VIA_EEPROM_CUSTOM_CONFIG_ADDR + 104)
```

Back up VIA mappings before changing this reservation and restore them afterward. Clearing or replacing a diagnostic snapshot does not clear the separate guard record. `os_detection_init()` is called after EEPROM initialization at keyboard startup to reset volatile detector state and load the guard.

## Troubleshooting

Some KVMs and USB switches may cause issues when the OS detection is turned on. 
Here is a list of common issues and how to fix them:

* **Problem**: _keyboard won't redetect the OS when switching between machines using a KVM_
    * **Explanation**: some KVMs keep the keyboard powered between hosts and only assemble fresh USB descriptors after the keyboard itself restarts.
    * **Solution**: enable `OS_DETECTION_KEYBOARD_RESET` to force re-enumeration after switching from a stable configured REPORT session, even with an unknown fingerprint. Reset waits for descriptor/state activity to settle, and a BOOT-protocol request cancels the restart. If firmware still loops in BIOS/UEFI using REPORT protocol, enable `OS_DETECTION_BOOT_LOOP_GUARD` to bound rapid automatic resets instead of disabling the KVM restart.
* **Problem**: _keyboard OS detection callback gets invoked even minuted after startup_
    * **Explanation**: some OSes, notably macOS on ARM-based Macs, may cause this behavior. 
    The actual cause is not known at this time.'
    * **Solution**: use `OS_DETECTION_SINGLE_REPORT` to suppress repeated callback invocations.


## Debug

If the OS is guessed incorrectly, collect the `wLength` values from USB string-descriptor requests to refine the detection logic. This trace does not record HID report-descriptor requests or every USB setup packet.

To do so in your `config.h` add:

```c
#define OS_DETECTION_DEBUG_ENABLE
```

And in your `rules.mk` add:

```make
CONSOLE_ENABLE = yes
```

And also include `"os_detection.h"` in your `keymap.c`.

Then you can define custom keycodes to store the USB string-descriptor request lengths in EEPROM (persistent memory) and print them later on a host where you can run `qmk console`:

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
        default:
            return true; // Process all other keycodes normally
    }
}
```

Add both `STORE_SETUPS` and `PRINT_SETUPS` to your keyboard's keymap. Connect the keyboard to the device where the OS was not recognised, and press the `STORE_SETUPS` key to capture and store the fingerprint. On your development computer, run one of the suggested [console debugging tools](/faq_debug#debugging-tools), connect the keyboard, and press the `PRINT_SETUPS` key. The console should display multiple lines of data from the most recent `STORE_SETUPS` run.

Open an issue on GitHub and paste the console output into the issue. Also tell us which OS (including the version, if possible) was not detected correctly and whether any intermediate devices, such as a USB hub, were used between the keyboard and the target device.

Only the first 50 USB string-descriptor request lengths are captured. Stored snapshots are validated before printing; a cleared or invalid snapshot reports that no valid stored data is available. A valid snapshot with no string-descriptor requests prints a zero-packet count and its reset reason.

### Capturing reboot loops

Enable `OS_DETECTION_DEBUG_AUTO_STORE` together with `OS_DETECTION_DEBUG_ENABLE` and `OS_DETECTION_KEYBOARD_RESET` to save a snapshot immediately before an eligible USB-reinitialization reset. It includes the string-descriptor request lengths and reset reason. Saving runs in the keyboard task, not in the USB callback; a suppressed reset does not trigger automatic capture.

Automatic capture preserves the first valid snapshot across subsequent resets and unplugging. It does not rewrite the snapshot during a reboot loop or overwrite it on a healthy host. Call `clear_stored_setups()` from a custom key to clear the snapshot and rearm automatic capture before reproducing a problem. Calling `store_setups_in_eeprom()` explicitly replaces the saved snapshot with the current boot's trace.

The validated snapshot format uses a magic marker, count, reset reason, and packed request lengths. Captures from the earlier unvalidated count-only format are not migrated; clear and recapture them.

When the reboot guard is enabled, `print_stored_setups()` prints its current count and the last automatic restart-request uptime before validating the snapshot, including when no valid snapshot exists. Suppressed or guard-blocked reset requests do not replace the snapshot.

The snapshot uses `OS_DETECTION_DEBUG_EEPROM_SIZE` bytes (104), starting at `EECONFIG_SIZE` by default. With VIA or dynamic keymaps, an explicitly reserved `OS_DETECTION_DEBUG_EEPROM_ADDR` is required to avoid overwriting keymaps. A VIA keymap can reserve its custom-config area in `config.h`:

```c
#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 104
#define OS_DETECTION_DEBUG_EEPROM_ADDR VIA_EEPROM_CUSTOM_CONFIG_ADDR
```

Do not share that area with other custom configuration. Changing this reservation changes the dynamic-keymap EEPROM layout; back up VIA mappings before flashing and restore them afterward. Snapshots survive power loss, but not explicit clearing, replacement, or EEPROM erasure. This is a bounded diagnostic capture, not a permanent full USB log.

## Credits

Original idea is coming from [FingerprintUSBHost](https://github.com/keyboardio/FingerprintUSBHost) project.
