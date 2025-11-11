# Digitizer {#digitizer}

Digitizers allow the mouse cursor to be placed at absolute coordinates, unlike the [Pointing Device](pointing_device) feature which applies relative displacements. Common digitizer devices include trackpads, touchscreens and drawing tablets.

This feature implements a stylus device with a tip switch and barrel switch (generally equivalent to the primary and secondary mouse buttons respectively). Tip pressure is not currently implemented and a touchpad device with upto 5 finger reports.

## Usage {#usage}

Add the following to your `rules.mk`:

```make
DIGITIZER_ENABLE = yes
```

## Stylus Positioning {#positioning}

Digitizers report values in logical ranges from `0..DIGITIZER_RESOLUTION_X` and `0..DIGITIZER_RESOLUTION_Y`. The HID descriptor also reports the physical dimensions `DIGITIZER_WIDTH_MM` x `DIGITIZER_HEIGHT_MM` of the sensor to the host so that it can determine what distance has been moved.

If the device uses the stylus report to set the position to `0,0`, the cursor will jump to the lop left hand corner of the screen. The co-ordinate `DIGITIZER_RESOLUTION_X,DIGITIZER_RESOLUTION_Y` will take it to the bottom right of the screen.

::: tip
Since there is no display attached, the OS will likely map these coordinates to the virtual desktop. This may be important to know if you have multiple monitors.
:::

## Finger reports

The host will interpret finger reports as gestures. Typically:

- A single finger moving will be interpreted as a relative mouse move
- A short tap will be interpreted as a left click
- A short two finger tap will be interpreted as a right click
- A tap and hold will be interpreted as a drag and drop
- Two fingers moving will be interpreted as scrolling
- Two fingers moving apart or together will be interperted as a zoom
- Two fingers turning, will be interpreted as rotation
- Thee finger swipes will expose the running applications or swap desktops

## Mouse fallback

If a host does not support USB trackpads (such as Mac-OS, or some KVMs) the Microsoft PTP specification requires us to fallback to reporting as a mouse. In this mode gesture detection is performed on the device.

## Common Configuration

| Setting                                        | Description                                                                                                                      | Default       |
| ---------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------- | ------------- |
| `DIGITIZER_WIDTH_MM`                           | (Optional) Set the physical width of the digitizer device in mm.                                                                 | `100`         |
| `DIGITIZER_HEIGHT_MM`                          | (Optional) Set the physical height of the digitizer device in mm.                                                                | `100`         |
| `DIGITIZER_RESOLUTION_X`                       | (Optional) Set the logical maximum X value.                                                                                      | `1920`        |
| `DIGITIZER_RESOLUTION_Y`                       | (Optional) Set the logical maximum Y value.                                                                                      | `1080`        |
| `DIGITIZER_HAS_STYLUS`                         | (Optional) Configures whether or not stylus reporting is enabled.                                                                | `true`        |
| `DIGITIZER_FINGER_COUNT`                       | (Optional) Configures the maximum number of finger contacts we should report. Microsoft PTP devices should have between 3 and 5. | `0`           |
| `DIGITIZER_CONTACT_COUNT`                      | (Optional) Configures the number of contacts reported by the sensor. This will include stylus, fingers and other types.          | `0`           |
| `DIGITIZER_TASK_THROTTLE_MS`                   | (Optional) Limits the frequency that the sensor is polled for motion.                                                            | _not defined_ |
| `DIGITIZER_TOUCH_PAD`                          | (Optional) Causes the HID report to indicate the device is a Touch Pad.                                                          | _not defined_ |
| `DIGITIZER_MOTION_PIN`                         | (Optional) If supported, will only read from sensor if pin is active.                                                            | _not defined_ |
| `DIGITIZER_MOTION_PIN_ACTIVE_LOW`              | (Optional) If defined then the motion pin is active-low.                                                                         | _varies_      |
| `DIGITIZER_REPORT_TAPS_AS_CLICKS`              | (Optional) If defined then tap gestures from mouse fallback will also be reported in the digitizer report.                       | `False`       |

The option `DIGITIZER_REPORT_TAPS_AS_CLICKS` is provided as most hosts do not provide per device configuration for trackpads. If you would like tap to click enabled on your QMK trackpad, but not on your laptops integrated trackpad, you can enable this.

By default when reporting to the host, only the first `DIGITIZER_FINGER_COUNT` contacts will be considered, but additional contacts may be used by firmware to trigger custom behaviours (such as custom gestures).

## Mouse Fallback Configuration

The mouse fallback gesture detection code can be tweaked with the following parameters. To use mouse fallback the `POINTING_DEVICE_DRIVER` should be set to `digitizer`.

| Setting                                        | Description                                                                                                                      | Default             |
| ---------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------- | ------------------- |
| `DIGITIZER_MOUSE_TAP_DETECTION_TIMEOUT`        | (Optional) The timeout in ms before a tap gesture is detected.                                                                   | `200`               |
| `DIGITIZER_MOUSE_TAP_DURATION`                 | (Optional) The length of time each simulated button press is held for.                                                           | `1`                 |
| `DIGITIZER_MOUSE_TAP_DISTANCE`                 | (Optional) The maximum distance a contact can move in an axis and still be detected as a tap.                                    | `25`                |
| `DIGITIZER_SCROLL_DIVISOR`                     | (Optional) A scaling factor that is applied to reduce the speed of scroll reporting.                                             | `10`                |
| `DIGITIZER_MOUSE_SWIPE_TIMEOUT`                | (Optional) The timeout in ms before a swipe gesture is detected.                                                                 | `500`               |
| `DIGITIZER_MOUSE_SWIPE_DISTANCE`               | (Optional) Minimum move distance required for a swipe to be detected.                                                            | `300`               |
| `DIGITIZER_MOUSE_SWIPE_THRESHOLD`              | (Optional) Movements in the alternate axis must be less than this threshold for a swipe to be detected.                          | `100`               |
| `DIGITIZER_SWIPE_LEFT_KC`                      | (Optional) The keycode to generate when a swipe left gesture is detected                                                         | `QK_MOUSE_BUTTON_3` |
| `DIGITIZER_SWIPE_RIGHT_KC`                     | (Optional) The keycode to generate when a swipe right gesture is detected                                                        | `QK_MOUSE_BUTTON_4` |
| `DIGITIZER_SWIPE_UP_KC`                        | (Optional) The keycode to generate when a swipe up gesture is detected                                                           | `KC_LEFT_GUI`       |
| `DIGITIZER_SWIPE_DOWN_KC`                      | (Optional) The keycode to generate when a swipe down gesture is detected                                                         | `KC_ESC`            |

## Split Keyboard Configuration

The following configuration options are only available when using `SPLIT_DIGITIZER_ENABLE` see [data sync options](split_keyboard#data-sync-options). If using `DIGITIZER_LEFT` or `DIGITIZER_RIGHT` use the common configuration above to configure your pointing device.

It is strongly recommended to put your digitizer device on the master half, as the volume of traffic going over the split link can be significant.

| Setting                              | Description                                                                                           | Default       |
| ------------------------------------ | ----------------------------------------------------------------------------------------------------- | ------------- |
| `DIGITIZER_LEFT`                     | Digitizer device on the left side (Required - pick one only)                                          | _not defined_ |
| `DIGITIZER_RIGHT`                    | Digitizer device on the right side (Required - pick one only)                                         | _not defined_ |

## Callbacks and Functions 

| Function                                                   | Description                                                                                                                                                                                                |
| ---------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `digitizer_init_kb(void)`                                  | Callback to allow for keyboard level initialization. Useful for additional hardware sensors.                                                                                                               |
| `digitizer_init_user(void)`                                | Callback to allow for user level initialization Useful for additional hardware sensors.                                                                                                                    |
| `digitizer_task_kb(digitizer_t *const digitizer_state)`    | Callback that provides the keyboard an opportunity to change the digitizer state whenever we get new digitizer data. Returns true if the state was changed.                                                |
| `digitizer_task_user(digitizer_t *const digitizer_state)`  | Callback that provides the user an opportunity to change the digitizer state whenever we get new digitizer data. Returns true if the state was changed.                                                    |
| `digitizer_set_scale(uint8_t scale)`                       | Scale finger poitions by a percentage. This provides a mechanism for the device to reduce the pointer speed but it may cause issues with swipe gestures if you can no longer generate a long enough swipe. |
| `digitizer_get_scale()`                                    | Gets the configured scaling percentage.                                                                                                                                                                    |

## Example

There is a onekey keymap which demonstrates the digitizer api. It uses the stylus report to draw squares in the middle of the screen.
