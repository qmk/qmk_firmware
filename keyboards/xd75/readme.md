xd75 keyboard firmware
======================

The XD75Re is a 15x5 full-grid ortholinear keyboard manufactured by XIUDI. This port of the QMK firmware is my first shot at using QMK, so if you see any features done wrong (or just plain missing), feel free to fix them and put in a pull request!

## Quantum MK Firmware

For more info on this firmware (and how to make it your own), head over to [qmk.fm](http://qmk.fm).

## Building

Download or clone the whole firmware and navigate to the
keyboards/xd75 folder. Once your dev env is setup, you'll be able to
type `make` to generate your .hex - you can then use the Teensy Loader
to install the resulting .hex file, or have the `make` process install
it using DFU.

### Default

To build with the default keymap, simply run `make xd75:default` from the root directory (i.e. two levels above this file), and to install via DFU, `make xd75:default:dfu`, also from the root directory.

Note that DFU is likely to require root permissions, so installing the
firmware likely requires a command line like:

```
$ sudo make xd75:default:dfu
```

### LED control

There are 3 individual LEDs that can be turned on and off, plus the keycap LEDs (which are all wired into the same pin).  The functions are named according to how they're labeled on the PCB.

TODO: it would be nice to have PWM support on these LEDs for fade-in/fade-out effects.

```c
capslock_led_on();
gp100_led_on();
gp103_led_on();
keycaps_led_on();


// led_set_user example - you could also turn these on/off in response
// to events in process_record_user or matrix_scan_user
void led_set_user(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        capslock_led_on();
    } else {
        capslock_led_off();
    }

    if (some_custom_state) {
      gp100_led_on();
    }
    else {
      gp100_led_off();
    }
}
```

For the curious:

```
CAPSLOCK_LED    B2
GP103_LED       F4
KEYCAPS_LED     F5
GP100_LED       F7
```

### Other Keymaps

The "default" keymap included is basically the OLKB Atomic keymap with
a few buttons added for RGB underglow control. This should be usable
as a starting point, but most people will be best served creating
their own keymap and flashing it - more info on creating your own
keymap is available in [the official QMK
documentation](https://docs.qmk.fm).

Keymaps follow the format **__\<name\>.c__** and are stored in
subdirectories under `keyboards/xd75/keymaps`

To build the firmware binary hex file for a specific keymap, and
install it, using DFU, just do `make` with a keymap like this:

```
$ make xd75:[default|<name>]
```

