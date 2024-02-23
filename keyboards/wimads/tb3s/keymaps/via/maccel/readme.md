# Mouse acceleration

This feature was born from the frustration of not having a tweakable acceleration curve that could work between OSes and hosts and be specific to one device, catalysed by multiple users expressing interest.

## Installation

### Installation (keymap)

Choose this route if you do not maintain a userspace.

Place the `maccel` directory in your keymap directory. For example, if you were using the `via` keymap on a BastardKB Dilemma Max, you'd place it to be `keyboards/bastardkb/dilemma/4x6_4/keymaps/via/maccel/`.

Add to `rules.mk` (Create it if it does not exist):
```make
# MACCEL
SRC += ./maccel/maccel.c
ifeq ($(strip $(VIA_ENABLE)), yes)
	ifeq ($(strip $(MACCEL_VIA_ENABLE)), yes)
		SRC += ./maccel/maccel_via.c
	endif
endif
OPT_DEFS += -DMACCEL_ENABLE
```

Add to your `keymap.c`, near the top:
```c
#ifdef MACCEL_ENABLE
    #include "maccel/maccel.h"
#endif
```

Continue with "Installation (common)", below.

### Installation (userspace)

Choose this route if you maintain a userspace.

Place the `maccel` directory within `features/` in your userspace. For example, if your username was burkfers, you'd place it to be `users/burkfers/features/maccel/`.

Add to `rules.mk` in the top level of your userspace (Create it if not present):

```make
MACCEL_ENABLE = yes

include $(USER_PATH)/features/maccel/rules.mk
```

You may instead place `MACCEL_ENABLE = yes` in your keymap's `rules.mk` if you wish to only enable maccel for some boards.

Add to your userspace source file, near the top:
```c
#ifdef MACCEL_ENABLE
    #include "features/maccel/maccel.h"
#endif
```

Continue with "Installation (common)", below.

### Installation (common)

Add to `pointing_device_task_user` in `keymap.c` or your userspace source file (paste the whole function if it did not exist):
```c
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // ...
#ifdef MACCEL_ENABLE
    return pointing_device_task_maccel(mouse_report);
#endif
}
```

See the section on runtime adjusting by keycodes and on via support for installation steps for these optional features.

## Configuration

This accel curve works in opposite direction from what you may be used to from other acceleration tools, due to technical limitations in QMK. It scales pointer sensitivity upwards rather than downwards, which means you will have to lower your device DPI setting from what you'd normally do.

Several characteristics of the acceleration curve can be tweaked by adding relevant defines to `config.h`:
```c
#define MACCEL_TAKEOFF 2.0 // lower/higher value = curve takes off more smoothly/abrubtly
#define MACCEL_GROWTH 0.25 // lower/higher value = curve reaches its upper limit slower/faster 
#define MACCEL_OFFSET 2.2  // lower/higher value = acceleration kicks in earlier/later
#define MACCEL_LIMIT 6.0   // upper limit of accel curve (maximum acceleration factor)
```
[![](assets/accel_curve.png)](https://www.desmos.com/calculator/g6zxh5rt44)

The graph above shows the acceleration curve. You can interpret this graph as follows: the horizontal axis is input velocity (ie. how fast you are physically moving your mouse/trackball/trackpad); the vertical axis is the acceleration factor, which is the factor with which the input speed will be multiplied, resulting in your new output speed on screen. You can also understand this as a DPI scaling factor: at the start of the curve the factor is 1, and your mouse sensitivity will be equal to your default DPI setting. At the end of the curve, the factor approaches a limit which can be set by the LIMIT variable. The limit is 6 in this example and will result in a maximum mouse sensitivity of 6 times your default DPI.

If you click on the image of the curve, you will be linked to desmos, where you can play around with the variables to understand how each of them affect the shape of the curve. But in short:

The TAKEOFF variable controls how smoothly or abrubtly the acceleration curve takes off. A higher value will make it take off more abrubtly, a lower value smoothens out the start of the curve.

The GROWTH variable sets the growth rate of the acceleration curve. A lower value will result in a flatter curve which takes longer to reach its LIMIT. A higher value will result in a steeper curve, which will reach its LIMIT faster.

The OFFSET variable moves the entire curve towards left/right. Offsetting the curve to the right means acceleration will kick in later, which is useful for low speed precision - in effect what you would otherwise have used SNIPING mode for. The maccel feature basically eliminates the need for a sniping mode.

The LIMIT variable sets the upper limit for the acceleration curve. This is the maximum acceleration factor the curve will reach.

A good starting point for tweaking your settings, is to set your default DPI to what you'd normally have set your sniping DPI. Then set the LIMIT variable to a factor that results in a bit higher than your usual default DPI. For example, if my usual settings are a default DPI of 1000 and a sniping DPI of 200, I would now set my default DPI to 200, and set my LIMIT variable to 6, which will result in an equivalent DPI scaling of 200*6=1200 at the upper limit of the acceleration curve. From there you can start playing around with the variables until you arrive at something to your liking.

To aid in dialing in your settings just right, a debug mode exists to print mathy details to the console. Refer to the QMK documentation on how to *enable the console and debugging*, then enable mouse acceleration debugging in `config.h`:
```c
#define MACCEL_DEBUG
/*
 * Requires enabling float support for printf!
 */
#undef PRINTF_SUPPORT_DECIMAL_SPECIFIERS
#define PRINTF_SUPPORT_DECIMAL_SPECIFIERS 1
```

The debug console will print your current DPI setting and variable settings, as well as the acceleration factor, the input and output velocity, and the input and output distance.

## Runtime adjusting of curve parameters by keycodes (optional)

### Additional required installation steps

To use keycodes to adjust the parameters without recompiling, two more build steps are required.
First, add four keycodes to your keycode enum. You may choose different names, as long as you use the same names in the following step. If you are not yet using custom keycodes, add the following snippet to `keymap.c`:
```c
enum my_keycodes {
    MA_TAKEOFF = QK_USER,   // mouse acceleration curve takeoff (initial acceleration) step key
    MA_GROWTH_RATE,         // mouse acceleration curve growth rate step key
    MA_OFFSET,              // mouse acceleration curve offset step key
    MA_LIMIT,               // mouse acceleration curve limit step key
};
```
Next, add another shim, this time to `process_record_user`. If you have not previously implemented this function, simply place the following snippet in your `keymap.c`:
```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_maccel(keycode, record, MA_TAKEOFF, MA_GROWTH_RATE, MA_OFFSET, MA_LIMIT)) {
        return false;
    }
    return true;
}
```
Take care to use the same names that you used in the previous step.

See the configuration section on how to enable this feature once you have set it up.

Once the additional keycodes and shim are added, this feature can be enabled in `config.h`:
```
#define MACCEL_USE_KEYCODES
```

Lastly, place the new keycodes on your keymap.

---
### Acceleration keycode usage

The four keycodes can be used to adjust the curve parameters. This is *not* persisted unless you also enabled the via option - Adjusted values are printed to the console to aid in finding the right settings for `config.h`.
The step keys will adjust the parameters by the following amounts, which can optionally be adjusted:

| Parameter    | Default step value | Define name               |
| ---          | ---                | ---                       |
| Takeoff      | `+0.01`            | `MACCEL_TAKEOFF_STEP`     |
| Growth rate  | `+0.01`            | `MACCEL_GROWTH_RATE_STEP` |
| Offset       | `+0.1`             | `MACCEL_OFFSET_STEP`      |
| Limit        | `+0.1`             | `MACCEL_LIMIT_STEP`       |

The modifier keys can be used to alter the step effect:

| Modifier    | Effect                                    |
| ---         | ---                                       |
| Shift       | Reverse step (subtract instead of adding) |
| Control     | `step value * 10` (Step 10 times faster)  |

Modifiers can be combined.

With every adjustment, an informational message is printed to the console.

## VIA support

![](assets/via.png)

Mouse acceleration can now be configured though via. If your keyboard is not already supported by via, you must first [create a via definition](https://www.caniusevia.com/docs/specification).

Add to `rules.mk`, *before* the include added previously:
```make
VIA_MACCEL_ENABLE = yes
``````

Add a shim to `keyboard_post_init_user`:
```c
void keyboard_post_init_user(void) {
    keyboard_post_init_maccel();
}
```

Add the entire function to your keymap if not already present, or insert the call to `keyboard_post_init_maccel` in your existing implementation.

You must also configure the size of the EEPROM user block by placing the following define in `config.h`:
```c
#define EECONFIG_USER_DATA_SIZE 20
```

Please be aware of the following caveats:
- The maccel via support takes over your eeprom user block. If you are already storing values in eeprom in your userspace, you must manually merge the features.
- The maccel via support implements `via_custom_value_command_kb`. This is not compatible with keyboards that already add custom features to via. If your keyboard has custom via configuration, you must manually shim the keyboard-level callback.

Create a custom via definition: Find your keyboard's via definition in the [via keyboards repository](https://github.com/the-via/keyboards/tree/master/v3) if you did not create your own.

Extend its `menus` configuration by placing the [menu definition](assets/via.json) on the `menu` node. Completed examples are provided for the BastardKB [Charybdis Nano](assets/cnano.json), [Dilemma v2](assets/dilemma_v2.json) and [Dilemma Max](assets/dilemma_max.json).

Finally, after flashing the firmware to your board, load the custom via definition in the design tab in [via](https://usevia.app)

# Setup checklist

- Place files in `users/YOUR_USERNAME/features/maccel/`
- Include `maccel/rules.mk` in your `rules.mk`
- Shim `pointing_device_task_user`
- Add configuration defines for parameters and optionally debugging
- Optional: Config keycodes:
  - Enable keycode support by define
  - Create four keycodes in the keycode enum
  - Shim `process_record_user`
- Optional: VIA support:
  - Enable in `rules.mk`
  - Shim `keyboard_post_init_user`
  - Set user eeprom data block size
  - Create custom via json and sideload it in the web app

## Limitations

With an unfavorable combination of `POINTING_DEVICE_THROTTLE_MS` and higher DPI, you may run into issues of peaking the maximum movement. Enable extended mouse reports by adding the following define in `config.h` to make this much less likely:
```c
#define MOUSE_EXTENDED_REPORT
```

The maccel feature has so far only been properly tested with PMW3360 sensor. However, it should work fine with all other QMK compatible sensors and devices as well, but the behaviour may not be 100% consistent across different DPI settings. Hence it might be a bit harder to dial in your variable preferences for those devices. This is due to a device-specific parameter in the calculations, that hasn't yet been determined for other devices than the PMW3360 sensor.

## Release history
- 2024 February 23 - New four-parameter acceleration curve and improved documentation
- 2024 February 07 - Experimental new DPI correction to achieve consistent acceleration behavior across different user DPI settings.
- 2024 February 06 - First release candidate. Feedback welcome!

## Credits
Thanks to everyone who helped!
Including, but not limited to:
- Wimads (@wimads) and burkfers (@burkfers) wrote most of the code
- Quentin (@balanstik) for insightful commentary on the math, and testing
- ouglop (@ouglop) for insightful commentary on the math
- Drashna Jael're (@drashna) for coding tips and their invaluable bag of magic C tricks
- ankostis (@ankostis) for catalysing discussion about improving the acceleration curve
