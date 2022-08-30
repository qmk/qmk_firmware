# Pointing Device :id=pointing-device

Pointing Device is a generic name for a feature intended to be generic: moving the system pointer around.  There are certainly other options for it - like mousekeys - but this aims to be easily modifiable and hardware driven.  You can implement custom keys to control functionality, or you can gather information from other peripherals and insert it directly here - let QMK handle the processing for you.

To enable Pointing Device, add the following line in your rules.mk and specify one of the driver options below.

```make
POINTING_DEVICE_ENABLE = yes
```

## Sensor Drivers

There are a number of sensors that are supported by default. Note that only one sensor can be enabled by `POINTING_DEVICE_DRIVER` at a time.  If you need to enable more than one sensor, then you need to implement it manually, using the `custom` driver.

### ADNS 5050 Sensor

To use the ADNS 5050 sensor, add this to your `rules.mk`

```make
POINTING_DEVICE_DRIVER = adns5050
```

The ADNS 5050 sensor uses a serial type protocol for communication, and requires an additional light source. 

| Setting             | Description                                                        | Default                    |
| ------------------- | ------------------------------------------------------------------ | -------------------------- |
| `ADNS5050_SCLK_PIN` | (Required) The pin connected to the clock pin of the sensor.       | `POINTING_DEVICE_SCLK_PIN` |
| `ADNS5050_SDIO_PIN` | (Required) The pin connected to the data pin of the sensor.        | `POINTING_DEVICE_SDIO_PIN` |
| `ADNS5050_CS_PIN`   | (Required) The pin connected to the Chip Select pin of the sensor. | `POINTING_DEVICE_CS_PIN`   |



The CPI range is 125-1375, in increments of 125. Defaults to 500 CPI.

### ADNS 9800 Sensor

To use the ADNS 9800 sensor, add this to your `rules.mk`

```make
POINTING_DEVICE_DRIVER = adns9800
```

The ADNS 9800 is an SPI driven optical sensor, that uses laser output for surface tracking. 

| Setting                 | Description                                                            | Default                  |
| ----------------------- | ---------------------------------------------------------------------- | ------------------------ |
| `ADNS9800_CLOCK_SPEED`  | (Optional) Sets the clock speed that the sensor runs at.               | `2000000`                |
| `ADNS9800_SPI_LSBFIRST` | (Optional) Sets the Least/Most Significant Byte First setting for SPI. | `false`                  |
| `ADNS9800_SPI_MODE`     | (Optional) Sets the SPI Mode for the sensor.                           | `3`                      |
| `ADNS9800_SPI_DIVISOR`  | (Optional) Sets the SPI Divisor used for SPI communication.            | _varies_                 |
| `ADNS9800_CS_PIN`       | (Required) Sets the Chip Select pin connected to the sensor.           | `POINTING_DEVICE_CS_PIN` |


The CPI range is 800-8200, in increments of 200. Defaults to 1800 CPI. 

### Analog Joystick

To use an analog joystick to control the pointer, add this to your `rules.mk`

```make
POINTING_DEVICE_DRIVER = analog_joystick
```

The Analog Joystick is an analog (ADC) driven sensor.  There are a variety of joysticks that you can use for this.

| Setting                           | Description                                                                | Default       |
| --------------------------------- | -------------------------------------------------------------------------- | ------------- |
| `ANALOG_JOYSTICK_X_AXIS_PIN`      | (Required) The pin used for the vertical/X axis.                           | _not defined_ |
| `ANALOG_JOYSTICK_Y_AXIS_PIN`      | (Required) The pin used for the horizontal/Y axis.                         | _not defined_ |
| `ANALOG_JOYSTICK_AXIS_MIN`        | (Optional) Sets the lower range to be considered movement.                 | `0`           |
| `ANALOG_JOYSTICK_AXIS_MAX`        | (Optional) Sets the upper range to be considered movement.                 | `1023`        |
| `ANALOG_JOYSTICK_SPEED_REGULATOR` | (Optional) The divisor used to slow down movement. (lower makes it faster) | `20`          |
| `ANALOG_JOYSTICK_READ_INTERVAL`   | (Optional) The interval in milliseconds between reads.                     | `10`          |
| `ANALOG_JOYSTICK_SPEED_MAX`       | (Optional) The maximum value used for motion.                              | `2`           |
| `ANALOG_JOYSTICK_CLICK_PIN`       | (Optional) The pin wired up to the press switch of the analog stick.       | _not defined_ |

### Cirque Trackpad

To use the Cirque Trackpad sensor, add this to your `rules.mk`:

```make
POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c
```

or

```make
POINTING_DEVICE_DRIVER = cirque_pinnacle_spi
```


This supports the Cirque Pinnacle 1CA027 Touch Controller, which is used in the TM040040, TM035035 and the TM023023 trackpads. These are I2C or SPI compatible, and both configurations are supported.

#### Common settings

| Setting                          | Description                                                | Default                                     |
| -------------------------------- | ---------------------------------------------------------- | ------------------------------------------- |
| `CIRQUE_PINNACLE_DIAMETER_MM`    | (Optional) Diameter of the trackpad sensor in millimeters. | `40`                                        |
| `CIRQUE_PINNACLE_ATTENUATION`    | (Optional) Sets the attenuation of the sensor data.        | `EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_4X` |
| `CIRQUE_PINNACLE_CURVED_OVERLAY` | (Optional) Applies settings tuned for curved overlay.      | _not defined_                               |
| `CIRQUE_PINNACLE_POSITION_MODE`  | (Optional) Mode of operation.                              | _not defined_                               |

**`CIRQUE_PINNACLE_ATTENUATION`** is a measure of how much data is suppressed in regards to sensitivity. The higher the attenuation, the less sensitive the touchpad will be.

Default attenuation is set to 4X, although if you are using a thicker overlay (such as the curved overlay) you will want a lower attenuation such as 2X. The possible values are:
* `EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_4X`: Least sensitive
* `EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_3X`
* `EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_2X`
* `EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_1X`: Most sensitive

**`CIRQUE_PINNACLE_POSITION_MODE`** can be `CIRQUE_PINNACLE_ABSOLUTE_MODE` or `CIRQUE_PINNACLE_RELATIVE_MODE`. Modes differ in supported features/gestures.

* `CIRQUE_PINNACLE_ABSOLUTE_MODE`: Reports absolute x, y, z (touch pressure) coordinates and up to 5 hw buttons connected to the trackpad
* `CIRQUE_PINNACLE_RELATIVE_MODE`: Reports x/y deltas, scroll and up to 3 buttons (2 of them can be from taps, see gestures) connected to trackpad. Supports taps on secondary side of split. Saves about 2k of flash compared to absolute mode with all features.

| I2C Setting               | Description                                                                     | Default |
| ------------------------- | ------------------------------------------------------------------------------- | ------- |
| `CIRQUE_PINNACLE_ADDR`    | (Required) Sets the I2C Address for the Cirque Trackpad                         | `0x2A`  |
| `CIRQUE_PINNACLE_TIMEOUT` | (Optional) The timeout for i2c communication with the trackpad in milliseconds. | `20`    |

| SPI Setting                    | Description                                                            | Default                  |
| ------------------------------ | ---------------------------------------------------------------------- | ------------------------ |
| `CIRQUE_PINNACLE_CLOCK_SPEED`  | (Optional) Sets the clock speed that the sensor runs at.               | `1000000`                |
| `CIRQUE_PINNACLE_SPI_LSBFIRST` | (Optional) Sets the Least/Most Significant Byte First setting for SPI. | `false`                  |
| `CIRQUE_PINNACLE_SPI_MODE`     | (Optional) Sets the SPI Mode for the sensor.                           | `1`                      |
| `CIRQUE_PINNACLE_SPI_DIVISOR`  | (Optional) Sets the SPI Divisor used for SPI communication.            | _varies_                 |
| `CIRQUE_PINNACLE_SPI_CS_PIN`   | (Required) Sets the Chip Select pin connected to the sensor.           | `POINTING_DEVICE_CS_PIN` |

Default Scaling is 1024. Actual CPI depends on trackpad diameter.

Also see the `POINTING_DEVICE_TASK_THROTTLE_MS`, which defaults to 10ms when using Cirque Pinnacle, which matches the internal update rate of the position registers (in standard configuration). Advanced configuration for pen/stylus usage might require lower values.

#### Absolute mode settings

| Setting                          | Description                                                | Default            |
| -------------------------------- | ---------------------------------------------------------- | ------------------ |
| `CIRQUE_PINNACLE_X_LOWER`        | (Optional) The minimum reachable X value on the sensor.    | `127`              |
| `CIRQUE_PINNACLE_X_UPPER`        | (Optional) The maximum reachable X value on the sensor.    | `1919`             |
| `CIRQUE_PINNACLE_Y_LOWER`        | (Optional) The minimum reachable Y value on the sensor.    | `63`               |
| `CIRQUE_PINNACLE_Y_UPPER`        | (Optional) The maximum reachable Y value on the sensor.    | `1471`             |

#### Absolute mode gestures

| Gesture Setting                                | Description                                                                    | Default              |
| ---------------------------------------------- | ------------------------------------------------------------------------------ | -------------------- |
| `CIRQUE_PINNACLE_TAP_ENABLE`                   | (Optional) Enable tap to click. This currently only works on the master side.  | _not defined_        |
| `CIRQUE_PINNACLE_TAPPING_TERM`                 | (Optional) Length of time that a touch can be to be considered a tap.          | `TAPPING_TERM`/`200` |
| `CIRQUE_PINNACLE_TOUCH_DEBOUNCE`               | (Optional) Length of time that a touch can be to be considered a tap.          | `TAPPING_TERM`/`200` |

`POINTING_DEVICE_GESTURES_SCROLL_ENABLE` in this mode enables circular scroll. Touch originating in outer ring can trigger scroll by moving along the perimeter. Near side triggers vertical scroll and far side triggers horizontal scroll.

Additionally, `POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE` is supported in this mode.

#### Relative mode gestures

| Gesture Setting                        | Description                                                                                                                                                                               | Default       |
| -------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------- |
| `CIRQUE_PINNACLE_TAP_ENABLE`           | (Optional) Enable tap to "left click". Works on both sides of a split keyboard.                                                                                                           | _not defined_ |
| `CIRQUE_PINNACLE_SECONDARY_TAP_ENABLE` | (Optional) Tap in upper right corner (half of the finger needs to be outside of the trackpad) of the trackpad will result in "right click". `CIRQUE_PINNACLE_TAP_ENABLE` must be enabled. | _not defined_ |

Tapping term and debounce are not configurable in this mode since it's handled by trackpad internally.

`POINTING_DEVICE_GESTURES_SCROLL_ENABLE` in this mode enables side scroll. Touch originating on the right side can trigger vertical scroll (IntelliSense trackpad style).

### PAW 3204 Sensor

To use the paw 3204 sensor, add this to your `rules.mk`

```make
POINTING_DEVICE_DRIVER = paw3204
```

The paw 3204 sensor uses a serial type protocol for communication, and requires an additional light source. 

| Setting            | Description                                                    | Default                    |
| ------------------ |--------------------------------------------------------------- | -------------------------- |
| `PAW3204_SCLK_PIN` | (Required) The pin connected to the clock pin of the sensor.   | `POINTING_DEVICE_SCLK_PIN` |
| `PAW3204_SDIO_PIN` | (Required) The pin connected to the data pin of the sensor.    | `POINTING_DEVICE_SDIO_PIN` |

The CPI range is 400-1600, with supported values of (400, 500, 600, 800, 1000, 1200 and 1600).  Defaults to 1000 CPI.

### Pimoroni Trackball

To use the Pimoroni Trackball module, add this to your `rules.mk`:

```make
POINTING_DEVICE_DRIVER = pimoroni_trackball
```

The Pimoroni Trackball module is a I2C based breakout board with an RGB enable trackball. 

| Setting                              | Description                                                                        | Default |
| ------------------------------------ | ---------------------------------------------------------------------------------- | ------- |
| `PIMORONI_TRACKBALL_ADDRESS`         | (Required) Sets the I2C Address for the Pimoroni Trackball.                        | `0x0A`  |
| `PIMORONI_TRACKBALL_TIMEOUT`         | (Optional) The timeout for i2c communication with the trackball in milliseconds.   | `100`   |
| `PIMORONI_TRACKBALL_SCALE`           | (Optional) The multiplier used to generate reports from the sensor.                | `5`     |
| `PIMORONI_TRACKBALL_DEBOUNCE_CYCLES` | (Optional) The number of scan cycles used for debouncing on the ball press.        | `20`    |
| `PIMORONI_TRACKBALL_ERROR_COUNT`     | (Optional) Specifies the number of read/write errors until the sensor is disabled. | `10`    |

### PMW 3360 and PMW 3389 Sensor

This drivers supports both the PMW 3360 and PMW 3389 sensor as well as multiple sensors of the same type _per_ controller, so 2 can be attached at the same side for split keyboards (or unsplit keyboards).

To use the **PMW 3360** sensor, add this to your `rules.mk`

```make
POINTING_DEVICE_DRIVER = pmw3360
```

The CPI range is 100-12000, in increments of 100. Defaults to 1600 CPI.

To use the **PMW 3389** sensor, add this to your `rules.mk`

```make
POINTING_DEVICE_DRIVER = pmw3389
```

The CPI range is 50-16000, in increments of 50. Defaults to 2000 CPI.

Both PMW 3360 and PMW 3389 are SPI driven optical sensors, that use a built in IR LED for surface tracking.
If you have different CS wiring on each half you can use `PMW33XX_CS_PIN_RIGHT` or `PMW33XX_CS_PINS_RIGHT` in combination with `PMW33XX_CS_PIN` or `PMW33XX_CS_PINS` to configure both sides independently. If `_RIGHT` values aren't provided, they default to be the same as the left ones.

| Setting                      | Description                                                                                 | Default                  |
| ---------------------------- | ------------------------------------------------------------------------------------------- | ------------------------ |
| `PMW33XX_CS_PIN`             | (Required) Sets the Chip Select pin connected to the sensor.                                | `POINTING_DEVICE_CS_PIN` |
| `PMW33XX_CS_PINS`            | (Alternative) Sets the Chip Select pins connected to multiple sensors.                      | `{PMW33XX_CS_PIN}`       |
| `PMW33XX_CS_PIN_RIGHT`       | (Optional) Sets the Chip Select pin connected to the sensor on the right half.              | `PMW33XX_CS_PIN`         |
| `PMW33XX_CS_PINS_RIGHT`      | (Optional) Sets the Chip Select pins connected to multiple sensors on the right half.       | `{PMW33XX_CS_PIN_RIGHT}` |
| `PMW33XX_CPI`                | (Optional) Sets counts per inch sensitivity of the sensor.                                  | _varies_                 |
| `PMW33XX_CLOCK_SPEED`        | (Optional) Sets the clock speed that the sensor runs at.                                    | `2000000`                |
| `PMW33XX_SPI_DIVISOR`        | (Optional) Sets the SPI Divisor used for SPI communication.                                 | _varies_                 |
| `PMW33XX_LIFTOFF_DISTANCE`   | (Optional) Sets the lift off distance at run time                                           | `0x02`                   |
| `ROTATIONAL_TRANSFORM_ANGLE` | (Optional) Allows for the sensor data to be rotated +/- 127 degrees directly in the sensor. | `0`                      |

To use multiple sensors, instead of setting `PMW33XX_CS_PIN` you need to set `PMW33XX_CS_PINS` and also handle and merge the read from this sensor in user code.
Note that different (per sensor) values of CPI, speed liftoff, rotational angle or flipping of X/Y is not currently supported.

```c
// in config.h:
#define PMW33XX_CS_PINS { B5, B6 }
// in keyboard.c:
#ifdef POINTING_DEVICE_ENABLE
void pointing_device_init_kb(void) {
    pmw33xx_init(1);         // index 1 is the second device.
    pmw33xx_set_cpi(0, 800); // applies to first sensor
    pmw33xx_set_cpi(1, 800); // applies to second sensor
    pointing_device_init_user();
}

// Contains report from sensor #0 already, need to merge in from sensor #1
report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    pmw33xx_report_t report = pmw33xx_read_burst(1);
    if (!report.motion.b.is_lifted && report.motion.b.is_motion) {
// From quantum/pointing_device_drivers.c
#define constrain_hid(amt) ((amt) < -127 ? -127 : ((amt) > 127 ? 127 : (amt)))
        mouse_report.x = constrain_hid(mouse_report.x + report.delta_x);
        mouse_report.y = constrain_hid(mouse_report.y + report.delta_y);
    }
    return pointing_device_task_user(mouse_report);
}
#endif

```

### Custom Driver

If you have a sensor type that isn't supported above, a custom option is available by adding the following to your `rules.mk`

```make
POINTING_DEVICE_DRIVER = custom
```

Using the custom driver will require implementing the following functions:

```c
void           pointing_device_driver_init(void) {}
report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report) { return mouse_report; }
uint16_t       pointing_device_driver_get_cpi(void) { return 0; }
void           pointing_device_driver_set_cpi(uint16_t cpi) {}
```

!> Ideally, new sensor hardware should be added to `drivers/sensors/` and `quantum/pointing_device_drivers.c`, but there may be cases where it's very specific to the hardware.  So these functions are provided, just in case. 

## Common Configuration

| Setting                                        | Description                                                                                                                      | Default       |
| ---------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------- | ------------- |
| `MOUSE_EXTENDED_REPORT`                        | (Optional) Enables support for extended mouse reports. (-32767 to 32767, instead of just -127 to 127).                           | _not defined_ |
| `POINTING_DEVICE_ROTATION_90`                  | (Optional) Rotates the X and Y data by  90 degrees.                                                                              | _not defined_ |
| `POINTING_DEVICE_ROTATION_180`                 | (Optional) Rotates the X and Y data by 180 degrees.                                                                              | _not defined_ |
| `POINTING_DEVICE_ROTATION_270`                 | (Optional) Rotates the X and Y data by 270 degrees.                                                                              | _not defined_ |
| `POINTING_DEVICE_INVERT_X`                     | (Optional) Inverts the X axis report.                                                                                            | _not defined_ |
| `POINTING_DEVICE_INVERT_Y`                     | (Optional) Inverts the Y axis report.                                                                                            | _not defined_ |
| `POINTING_DEVICE_MOTION_PIN`                   | (Optional) If supported, will only read from sensor if pin is active.                                                            | _not defined_ |
| `POINTING_DEVICE_MOTION_PIN_ACTIVE_LOW`        | (Optional) If defined then the motion pin is active-low.                                                                         | _varies_      |
| `POINTING_DEVICE_TASK_THROTTLE_MS`             | (Optional) Limits the frequency that the sensor is polled for motion.                                                            | _not defined_ |
| `POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE` | (Optional) Enable inertial cursor. Cursor continues moving after a flick gesture and slows down by kinetic friction.             | _not defined_ |
| `POINTING_DEVICE_GESTURES_SCROLL_ENABLE`       | (Optional) Enable scroll gesture. The gesture that activates the scroll is device dependent.                                     | _not defined_ |
| `POINTING_DEVICE_CS_PIN`                       | (Optional) Provides a default CS pin, useful for supporting multiple sensor configs.                                             | _not defined_ |
| `POINTING_DEVICE_SDIO_PIN`                     | (Optional) Provides a default SDIO pin, useful for supporting multiple sensor configs.                                           | _not defined_ |
| `POINTING_DEVICE_SCLK_PIN`                     | (Optional) Provides a default SCLK pin, useful for supporting multiple sensor configs.                                           | _not defined_ |

!> When using `SPLIT_POINTING_ENABLE` the `POINTING_DEVICE_MOTION_PIN` functionality is not supported and `POINTING_DEVICE_TASK_THROTTLE_MS` will default to `1`. Increasing this value will increase transport performance at the cost of possible mouse responsiveness.

The `POINTING_DEVICE_CS_PIN`, `POINTING_DEVICE_SDIO_PIN`, and `POINTING_DEVICE_SCLK_PIN` provide a convenient way to define a single pin that can be used for an interchangeable sensor config.  This allows you to have a single config, without defining each device.  Each sensor allows for this to be overridden with their own defines. 

!> Any pointing device with a lift/contact status can integrate inertial cursor feature into its driver, controlled by `POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE`. e.g. PMW3360 can use Lift_Stat from Motion register. Note that `POINTING_DEVICE_MOTION_PIN` cannot be used with this feature; continuous polling of `get_report()` is needed to generate glide reports.

## Split Keyboard Configuration

The following configuration options are only available when using `SPLIT_POINTING_ENABLE` see [data sync options](feature_split_keyboard.md?id=data-sync-options). The rotation and invert `*_RIGHT` options are only used with `POINTING_DEVICE_COMBINED`. If using `POINTING_DEVICE_LEFT` or `POINTING_DEVICE_RIGHT` use the common configuration above to configure your pointing device.

| Setting                              | Description                                                                                           | Default       |
| ------------------------------------ | ----------------------------------------------------------------------------------------------------- | ------------- |
| `POINTING_DEVICE_LEFT`               | Pointing device on the left side (Required - pick one only)                                           | _not defined_ |
| `POINTING_DEVICE_RIGHT`              | Pointing device on the right side (Required - pick one only)                                          | _not defined_ |
| `POINTING_DEVICE_COMBINED`           | Pointing device on both sides (Required - pick one only)                                              | _not defined_ |
| `POINTING_DEVICE_ROTATION_90_RIGHT`  | (Optional) Rotates the X and Y data by  90 degrees.                                                   | _not defined_ |
| `POINTING_DEVICE_ROTATION_180_RIGHT` | (Optional) Rotates the X and Y data by 180 degrees.                                                   | _not defined_ |
| `POINTING_DEVICE_ROTATION_270_RIGHT` | (Optional) Rotates the X and Y data by 270 degrees.                                                   | _not defined_ |
| `POINTING_DEVICE_INVERT_X_RIGHT`     | (Optional) Inverts the X axis report.                                                                 | _not defined_ |
| `POINTING_DEVICE_INVERT_Y_RIGHT`     | (Optional) Inverts the Y axis report.                                                                 | _not defined_ |

!> If there is a `_RIGHT` configuration option or callback, the [common configuration](feature_pointing_device.md?id=common-configuration) option will work for the left. For correct left/right detection you should setup a [handedness option](feature_split_keyboard?id=setting-handedness), `EE_HANDS` is usually a good option for an existing board that doesn't do handedness by hardware.


## Callbacks and Functions 

| Function                                                   | Description                                                                                                   |
| ---------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------- |
| `pointing_device_init_kb(void)`                            | Callback to allow for keyboard level initialization. Useful for additional hardware sensors.                  |
| `pointing_device_init_user(void)`                          | Callback to allow for user level initialization. Useful for additional hardware sensors.                      |
| `pointing_device_task_kb(mouse_report)`                    | Callback that sends sensor data, so keyboard code can intercept and modify the data.  Returns a mouse report. |
| `pointing_device_task_user(mouse_report)`                  | Callback that sends sensor data, so user code can intercept and modify the data.  Returns a mouse report.     |
| `pointing_device_handle_buttons(buttons, pressed, button)` | Callback to handle hardware button presses. Returns a `uint8_t`.                                              |
| `pointing_device_get_cpi(void)`                            | Gets the current CPI/DPI setting from the sensor, if supported.                                               |
| `pointing_device_set_cpi(uint16_t)`                        | Sets the CPI/DPI, if supported.                                                                               |
| `pointing_device_get_report(void)`                         | Returns the current mouse report (as a `report_mouse_t` data structure).                                      |
| `pointing_device_set_report(mouse_report)`                 | Sets the mouse report to the assigned `report_mouse_t` data structured passed to the function.                |
| `pointing_device_send(void)`                               | Sends the current mouse report to the host system.  Function can be replaced.                                 |
| `has_mouse_report_changed(new_report, old_report)`         | Compares the old and new `report_mouse_t` data and returns true only if it has changed.                       |
| `pointing_device_adjust_by_defines(mouse_report)`          | Applies rotations and invert configurations to a raw mouse report.                                            |


## Split Keyboard Callbacks and Functions

The combined functions below are only available when using `SPLIT_POINTING_ENABLE` and `POINTING_DEVICE_COMBINED`. The 2 callbacks `pointing_device_task_combined_*` replace the single sided equivalents above. See the [combined pointing devices example](feature_pointing_device.md?id=combined-pointing-devices)

| Function                                                        | Description                                                                                                              |
| --------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------ |
| `pointing_device_set_shared_report(mouse_report)`               | Sets the shared mouse report to the assigned `report_mouse_t` data structured passed to the function.                    |
| `pointing_device_set_cpi_on_side(bool, uint16_t)`               | Sets the CPI/DPI of one side, if supported. Passing `true` will set the left and `false` the right                       |
| `pointing_device_combine_reports(left_report, right_report)`    | Returns a combined mouse_report of left_report and right_report (as a `report_mouse_t` data structure)                   |
| `pointing_device_task_combined_kb(left_report, right_report)`   | Callback, so keyboard code can intercept and modify the data. Returns a combined mouse report.                           |
| `pointing_device_task_combined_user(left_report, right_report)` | Callback, so user code can intercept and modify. Returns a combined mouse report using `pointing_device_combine_reports` |
| `pointing_device_adjust_by_defines_right(mouse_report)`         | Applies right side rotations and invert configurations to a raw mouse report.                                            |


# Manipulating Mouse Reports

The report_mouse_t (here "mouseReport") has the following properties:

* `mouseReport.x` - this is a signed int from -127 to 127 (not 128, this is defined in USB HID spec) representing movement (+ to the right, - to the left) on the x axis.
* `mouseReport.y` - this is a signed int from -127 to 127 (not 128, this is defined in USB HID spec) representing movement (+ upward, - downward) on the y axis.
* `mouseReport.v` - this is a signed int from -127 to 127 (not 128, this is defined in USB HID spec) representing vertical scrolling (+ upward, - downward).
* `mouseReport.h` - this is a signed int from -127 to 127 (not 128, this is defined in USB HID spec) representing horizontal scrolling (+ right, - left).
* `mouseReport.buttons` - this is a uint8_t in which all 8 bits are used.  These bits represent the mouse button state - bit 0 is mouse button 1, and bit 7 is mouse button 8.

To manually manipulate the mouse reports outside of the `pointing_device_task_*` functions, you can use:

* `pointing_device_get_report()` - Returns the current report_mouse_t that represents the information sent to the host computer
* `pointing_device_set_report(report_mouse_t mouse_report)` - Overrides and saves the report_mouse_t to be sent to the host computer
* `pointing_device_send()` - Sends the mouse report to the host and zeroes out the report. 

When the mouse report is sent, the x, y, v, and h values are set to 0 (this is done in `pointing_device_send()`, which can be overridden to avoid this behavior).  This way, button states persist, but movement will only occur once.  For further customization, both `pointing_device_init` and `pointing_device_task` can be overridden.

Additionally, by default, `pointing_device_send()` will only send a report when the report has actually changed.  This prevents it from continuously sending mouse reports, which will keep the host system awake.  This behavior can be changed by creating your own `pointing_device_send()` function.

Also, you use the `has_mouse_report_changed(new_report, old_report)` function to check to see if the report has changed.

## Examples

### Custom Mouse Keycode

In this example, a custom key is used to click the mouse and scroll 127 units vertically and horizontally, then undo all of that when released - because that's a totally useful function.

```c
case MS_SPECIAL:
    report_mouse_t currentReport = pointing_device_get_report();
    if (record->event.pressed) {
        currentReport.v = 127;
        currentReport.h = 127;
        currentReport.buttons |= MOUSE_BTN1;  // this is defined in report.h
    } else {
        currentReport.v = -127;
        currentReport.h = -127;
        currentReport.buttons &= ~MOUSE_BTN1;
    }
    pointing_device_set_report(currentReport);
    pointing_device_send();
    break;
```

Recall that the mouse report is set to zero (except the buttons) whenever it is sent, so the scrolling would only occur once in each case.

### Drag Scroll or Mouse Scroll

A very common implementation is to use the mouse movement to scroll instead of moving the cursor on the system.  This uses the `pointing_device_task_user` callback to intercept and modify the mouse report before it's sent to the host system. 

```c
enum custom_keycodes {
    DRAG_SCROLL = SAFE_RANGE,
};

bool set_scrolling = false;

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (set_scrolling) {
        mouse_report.h = mouse_report.x;
        mouse_report.v = mouse_report.y;
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == DRAG_SCROLL && record->event.pressed) {
        set_scrolling = !set_scrolling;
    }
    return true;
}
```

This allows you to toggle between scrolling and cursor movement by pressing the DRAG_SCROLL key.  

## Split Examples

The following examples make use the `SPLIT_POINTING_ENABLE` functionality and show how to manipulate the mouse report for a scrolling mode.

### Single Pointing Device

The following example will work with either `POINTING_DEVICE_LEFT` or `POINTING_DEVICE_RIGHT` and enables scrolling mode while on a particular layer.

```c

static bool scrolling_mode = false;

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _RAISE:  // If we're on the _RAISE layer enable scrolling mode
            scrolling_mode = true;
            pointing_device_set_cpi(2000);
            break;
        default:
            if (scrolling_mode) {  // check if we were scrolling before and set disable if so
                scrolling_mode = false;
                pointing_device_set_cpi(8000);
            }
            break;
    }
    return state;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (scrolling_mode) {
        mouse_report.h = mouse_report.x;
        mouse_report.v = mouse_report.y;
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}
```

### Combined Pointing Devices

The following example requires `POINTING_DEVICE_COMBINED` and sets the left side pointing device to scroll only.

```c
void keyboard_post_init_user(void) {
    pointing_device_set_cpi_on_side(true, 1000); //Set cpi on left side to a low value for slower scrolling.
    pointing_device_set_cpi_on_side(false, 8000); //Set cpi on right side to a reasonable value for mousing.
}

report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
    left_report.h = left_report.x;
    left_report.v = left_report.y;
    left_report.x = 0;
    left_report.y = 0;
    return pointing_device_combine_reports(left_report, right_report);
}
```

# Troubleshooting

If you are having issues with pointing device drivers debug messages can be enabled that will give you insights in the inner workings. To enable these add to your keyboards `config.h` file:

```c
#define POINTING_DEVICE_DEBUG
```
 
?> The messages will be printed out to the `CONSOLE` output. For additional information, refer to [Debugging/Troubleshooting QMK](faq_debug.md).


---
# Automatic Mouse Layer :id=pointing-device-auto-mouse

When using a pointing device combined with a keyboard the mouse buttons are often kept on a separate layer from the default keyboard layer, which requires pressing or holding a key to change layers before using the mouse. To make this easier and more efficient an additional pointing device feature may be enabled that will automatically activate a target layer as soon as the pointing device is active (_in motion, mouse button pressed etc._) and deactivate the target layer after a set time.   

Additionally if any key that is defined as a mouse key is pressed then the layer will be held as long as the key is pressed and the timer will be reset on key release. When a non-mouse key is pressed then the layer is deactivated early (_with some exceptions see below_).  Mod, mod tap, and one shot mod keys are ignored (_i.e. don't hold or activate layer but do not deactivate the layer either_) when sending a modifier keycode (_e.g. hold for mod tap_) allowing for mod keys to be used with the mouse without activating the target layer when typing.

All of the standard layer keys (tap toggling, toggle, toggle on, one_shot, layer tap, layer mod) that activate the current target layer are uniquely handled to ensure they behave as expected _(see layer key table below)_. The target layer that can be changed at any point during by calling the `set_auto_mouse_layer(<new_target_layer>);` function.

### Behaviour of Layer keys that activate the target layer
| Layer key as in `keymap.c` | Auto Mouse specific behaviour                                                                                         |
| -------------------------- | --------------------------------------------------------------------------------------------------------------------- |
| `MO(<target_layer>)`       | Treated as a mouse key holding the layer while pressed                                                                |
| `LT(<target_layer>)`       | When tapped will be treated as non mouse key and mouse key when held                                                  |
| `LM(<target_layer>)`       | Treated as a mouse key                                                                                                |
| `TG(<target_layer>)`       | Will set flag preventing target layer deactivation or removal until pressed again                                     |
| `TO(<target_layer>)`       | Same as `TG(<target_layer>)`                                                                                          |
| `TT(<target_layer>)`       | Treated as a mouse key when `tap.count < TAPPING_TOGGLE` and as `TG` when `tap.count == TAPPING_TOGGLE`               |
| `DF(<target_layer>)`       | Skips auto mouse key processing similar to mod keys                                                                   |
| `OSL(<target_layer>)`      | Skips, but if current one shot layer is the target layer then it will prevent target layer deactivation or removal    |


## How to enable:

```c
// in config.h:
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
// only required if not setting mouse layer elsewhere
#define AUTO_MOUSE_DEFAULT_LAYER <index of your mouse layer>

// in keymap.c:
void pointing_device_init_user(void) {
    set_auto_mouse_layer(<mouse_layer>); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
}
```

Because the auto mouse feature can be disabled/enabled during runtime and starts as disabled by default it must be enabled by calling `set_auto_mouse_enable(true);` somewhere in firmware before the feature will work.   
_Note: for setting the target layer during initialization either setting `AUTO_MOUSE_DEFAULT_LAYER` in `config.h` or calling `set_auto_mouse_layer(<mouse_layer>)` can be used._   


## How to Customize:

There are a few ways to control the auto mouse feature with both `config.h` options and functions for controlling it during runtime.

### `config.h` Options:
| Define                              | Description                                                           |         Range        |    Units    |                    Default |
| ----------------------------------- | --------------------------------------------------------------------- | :------------------: | :---------: | -------------------------: |
| `POINTING_DEVICE_AUTO_MOUSE_ENABLE` | (Required) Enables auto mouse layer feature                           |                      |   _None_    |              _Not defined_ |
| `AUTO_MOUSE_DEFAULT_LAYER`          | (Optional) Index of layer to use as default target layer              |    0 - `LAYER_MAX`   | _`uint8_t`_ |                        `1` |
| `AUTO_MOUSE_TIME`                   | (Optional) Time layer remains active after activation                 | _ideally_ (250-1000) |     _ms_    |                   `650 ms` |
| `AUTO_MOUSE_DELAY`                  | (Optional) Lockout time after non-mouse key is pressed                | _ideally_ (100-1000) |     _ms_    | `TAPPING_TERM` or `200 ms` |
| `AUTO_MOUSE_DEBOUNCE`               | (Optional) Time delay from last activation to next update             | _ideally_ (10 - 100) |     _ms_    |                    `25 ms` |

### Adding mouse keys

While all default mouse keys and layer keys(for current mouse layer) are treated as mouse keys, additional Keyrecords can be added to mouse keys by adding them to the is_mouse_record_* stack. 

#### Callbacks for setting up additional key codes as mouse keys:
| Callback                                                             | Description                                        |
| -------------------------------------------------------------------- | -------------------------------------------------- |
| `bool is_mouse_record_kb(uint16_t keycode, keyrecord_t* record)`     |  keyboard level callback for adding mouse keys     |
| `bool is_mouse_record_user(uint16_t keycode, keyrecord_t* record)`   |  user/keymap level callback for adding mouse keys  |

##### To use the callback function to add mouse keys:   

The following code will cause the enter key and all of the arrow keys to be treated as mouse keys (hold target layer while they are pressed and reset active layer timer).
```c

// in <keyboard>.c:
bool is_mouse_record_kb(uint16_t keycode, keyrecord_t* record) {
    switch(keycode) {
        case KC_ENT:
            return true;
        case KC_RIGHT ... KC_UP:
            return true;
        default:
            return false;
    }
    return  is_mouse_record_user(keycode, record);
}
```


## Advanced control

There are several functions that allow for more advanced interaction with the auto mouse feature allowing for greater control.

### Functions to control auto mouse enable and target layer:   
| Function                                                   | Description                                                                          | Aliases                   |     Return type |
| :--------------------------------------------------------- | ------------------------------------------------------------------------------------ | ------------------------- | --------------: |
| `set_auto_mouse_enable(bool enable)`                       | Enable or disable auto mouse (true:enable, false:disable)                            |                           |    `void`(None) |
| `get_auto_mouse_enable(void)`                              | Return auto mouse enable state (true:enabled, false:disabled)                        | `AUTO_MOUSE_ENABLED`      |          `bool` |
| `set_auto_mouse_layer(uint8_t LAYER)`                      | Change/set the target layer for auto mouse                                           |                           |    `void`(None) |
| `get_auto_mouse_layer(void)`                               | Return auto mouse target layer index                                                 | `AUTO_MOUSE_TARGET_LAYER` |       `uint8_t` |
| `remove_auto_mouse_layer(layer_state_t state, bool force)` | Return `state` with target layer removed if appropriate (ignore criteria if `force`) |                           | `layer_state_t` |
| `auto_mouse_layer_off(void)`                               | Disable target layer if appropriate will call (makes call to `layer_state_set`)      |                           |   `void`(None)  |
| `auto_mouse_toggle(void)`                                  | Toggle on/off target toggle state (disables layer deactivation when true)            |                           |    `void`(None) |
| `get_auto_mouse_toggle(void)`                              | Return value of toggling state variable                                              |                           |          `bool` |

_NOTES:_   
    - _Due to the nature of how some functions work, the `auto_mouse_trigger_reset`, and `auto_mouse_layer_off` functions should never be called in the `layer_state_set_*` stack as this can cause indefinite loops._   
    - _It is recommended that `remove_auto_mouse_layer` is used in the `layer_state_set_*` stack of functions and `auto_mouse_layer_off` is used everywhere else_   
    - _`remove_auto_mouse_layer(state, false)` or `auto_mouse_layer_off()` should be called before any instance of `set_auto_mouse_enabled(false)` or `set_auto_mouse_layer(layer)` to ensure that the target layer will be removed appropriately before disabling auto mouse or changing target to avoid a stuck layer_      
    
### Functions for handling custom key events:   
| Function                                                   | Description                                                                      |     Return type |
| :--------------------------------------------------------- | -------------------------------------------------------------------------------- | --------------: |
| `auto_mouse_keyevent(bool pressed)`                        | Auto mouse mouse key event (true: key down, false: key up)                       |    `void`(None) |
| `auto_mouse_trigger_reset(bool pressed)`                   | Reset auto mouse status on key down and start delay timer (non-mouse key event)  |    `void`(None) |
| `auto_mouse_toggle(void)`                                  | Toggle on/off target toggle state (disables layer deactivation when true)        |    `void`(None) |
| `get_auto_mouse_toggle(void)`                              | Return value of toggling state variable                                          |          `bool` |   
_NOTE: Generally it would be preferable to use the `is_mouse_record_*` functions to add any additional keys that should act as mouse keys rather than adding `auto_mouse_keyevent(record.event->pressed)` to `process_records_*`_

### Advanced control examples   

#### Disable auto mouse on certain layers  

The auto mouse feature can be disabled any time and this can be helpful if you want to disable the auto mouse feature under certain circumstances such as when particular layers are active. One issue however is the handling of the target layer, it needs to be removed appropriately **before** disabling auto mouse _(see notes under control functions above)_. The following function would disable the auto_mouse feature whenever the layers `_LAYER5` through `_LAYER7` are active as the top most layer _(ignoring target layer)_.   

```c
// in keymap.c:
layer_state_t layer_state_set_user(layer_state_t state) {
    // checks highest layer other than target layer
    switch(get_highest_layer(remove_auto_mouse_layer(state, true))) {
        case _LAYER5 ... _LAYER7:
            // remove_auto_mouse_target must be called to adjust state *before* setting enable
            state = remove_auto_mouse_layer(state, false);
            set_auto_mouse_enable(false);
            break;
        default:
            set_auto_mouse_enable(true);
            break;
    }
    // recommend that any code that makes adjustment based on auto mouse layer state would go here
    return state;
}
```

#### Set different target layer when a particular layer is active:

The below code will change the auto mouse layer target to `_MOUSE_LAYER_2` when `_DEFAULT_LAYER_2` is highest default layer state.   
*NOTE: that `auto_mouse_layer_off` is used here instead of `remove_auto_mouse_layer` as `default_layer_state_set_*` stack is separate from the `layer_state_set_*` stack* if something similar was to be done in `layer_state_set_user_state = remove_auto_mouse_layer(state, false)` should be used instead    
*ADDITIONAL NOTE: `AUTO_MOUSE_TARGET_LAYER` is checked if already set to avoid deactivating the target layer unless needed*   

```c
// in keymap.c
layer_state_t default_layer_state_set_user(layer_state_t state) {
    // switch on change in default layer need to check if target layer already set to avoid turning off layer needlessly
    switch(get_highest_layer(state)) {
        case _DEFAULT_LAYER_2:
            if ((AUTO_MOUSE_TARGET_LAYER) == _MOUSE_LAYER_2) break;
            auto_mouse_layer_off();
            set_auto_mouse_layer(_MOUSE_LAYER_2);
            break;
        
        default:
            if((AUTO_MOUSE_TARGET_LAYER) == _MOUSE_LAYER_1) break;
            auto_mouse_layer_off();
            set_auto_mouse_layer(_MOUSE_LAYER_1);
    }
    return state;
}
```

### Use custom keys to control auto mouse 

Custom key records could also be created that control the auto mouse feature.   
The code example below would create a custom key that would toggle the auto mouse feature on and off when pressed while also setting a bool that could be used to disable other code that may turn it on such as the layer code above.   

```c
// in config.h:
enum user_custom_keycodes {
    AM_Toggle = SAFE_RANGE
};

// in keymap.c:
// set up global bool to adjust other user code
bool auto_mouse_tg_off = !AUTO_MOUSE_ENABLED;

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        // toggle auto mouse enable key
        case AM_Toggle:
            if(record->event.pressed) { // key down
                auto_mouse_layer_off(); // disable target layer if needed
                set_auto_mouse_enabled((AUTO_MOUSE_ENABLED) ^ 1);
                auto_mouse_tg_off = !get_auto_mouse_enabled();
            } // do nothing on key up
            return false; // prevent further processing of keycode
    }
}
```

## Customize Target Layer Activation

Layer activation can be customized by overwriting the `auto_mouse_activation` function. This function is checked every time `pointing_device_task` is called when inactive and every `AUTO_MOUSE_DEBOUNCE` ms when active, and will evaluate pointing device level conditions that trigger target layer activation. When it returns true, the target layer will be activated barring the usual exceptions (_e.g. delay time has not expired_).   

By default it will return true if any of the `mouse_report` axes `x`,`y`,`h`,`v` are non zero, or if there is any mouse buttons active in `mouse_report`.
_Note: The Cirque pinnacle track pad already implements a custom activation function that will activate on touchdown as well as movement all of the default conditions, currently this only works for the master side of split keyboards._
 
| Function                                                   | Description                                                                      |     Return type |
| :--------------------------------------------------------- | -------------------------------------------------------------------------------- | --------------: |
| `auto_mouse_activation(report_mouse_t mouse_report)`       | Overwritable function that controls target layer activation (when true)          |          `bool` |

## Auto Mouse for Custom Pointing Device Task

When using a custom pointing device (overwriting `pointing_device_task`) the following code should be somewhere in the `pointing_device_task_*` stack:

```c
void pointing_device_task(void) {
    //...Custom pointing device task code
    
    // handle automatic mouse layer (needs report_mouse_t as input)
    pointing_device_task_auto_mouse(local_mouse_report);
    
    //...More custom pointing device task code
    
    pointing_device_send();
}
```

In general the following two functions must be implemented in appropriate locations for auto mouse to function:

| Function                                                       | Description                                                  |           Suggested location |
| -------------------------------------------------------------- | ------------------------------------------------------------ | ---------------------------: |
| `pointing_device_task_auto_mouse(report_mouse_t mouse_report)` | handles target layer activation and is_active status updates | `pointing_device_task` stack |
| `process_auto_mouse(uint16_t keycode, keyrecord_t* record)`    | Keycode processing for auto mouse                            |       `process_record` stack |

---

# Pointing Device Modes :id=pointing_device_modes

Inspired by the work of previous trackball users that added features such as drag scroll, caret scroll, and sniping modes to their keyboards, this framework allows for easy setup and inclusion of different pointing device modes that when active will change the behaviour of a pointing device by taking it's x/y outputs and changing them into something else such as h/v for drag scrolling, key presses such as arrow keys for caret scrolling, and even just adjusting the x/y values before output.  When a pointing device mode is active it accumulates x and y outputs from a pointing device and stores it into internal h & v values, halting mouse x and y output (_modes can re-enable and modify mouse output_), these internally stored h and v axes can be then compared against any relevant divisor/threshold triggering the appropriate output. The dividing factors can be used to control pointing device sensitivity in each mode as adjusting cpi may not always be desired/possible.   

The framework supports up to **15** custom modes natively through the `PM_MO(<pointing mode>)` and `PM_TG(<pointing mode>)` keycode macros which act as momentary and toggle keys for `<pointing mode>` respectively, similarly to the layer keys of the same type.  5 of the 15 modes are already used by built in modes, however these can easily be overwritten if needed.  There is an additional Null mode `PM_NONE` (_Default pointing device output_) that cannot be overwritten.  More modes beyond this (_mode id's > 16_) can be added but they will require the addition of custom keycodes to activate the modes as `PM_MO(<pm>)` and `PM_TG(<pm>)` macros only support up to mode id 15.  New custom modes can be added through either adding keycode maps to the `pointing_device_mode_maps` array or through the through user/kb callbacks functions (_see advanced use below_). 

## Basic Use
   
### How To Enable
On a keyboard that has a pointing device (_i.e._ `POINTING_DEVICE_ENABLED` _is defined_) pointing modes can be enabled by defining `POITNING_DEVICE_MODES_ENABLED` in `config.h`.  If only built in modes are being used then simply adding keycodes to the keymap to enable is all that is needed (_see advanced use for activating modes outside of key presses_).

```c
// in config.h:
#define POINTING_DEVICE_MODES_ENABLED
```

###  Activating Pointing Device Modes
The first 15 pointing device modes can easily be activated by keypress by adding the following macros to a keymap by using the following keycode macros:  

#### Keycode Macros (_for the first 15 modes and _`PM_NONE`_ only_)
| Keycode Macro  | Description                                                                                                           |
| -------------- | --------------------------------------------------------------------------------------------------------------------- |
| `PM_MO(<pm>)`  | Momentary key for pointing mode `<pm>` (i.e active while key pressed deactivate on release)                           |
| `PM_TG(<pm>)`  | Toggle key for pointing mode `<pm>` (toggle on release, remain until pressed and released again)                      |
 
***Note: For pointing device modes above mode id 15 a custom keycode would need to be added unless the mode is being activated through some other means (such as on specific layers see advanced use below)***

#### Toggled Pointing Device Modes vs Momentary Pointing Modes
Pointing device modes activated by toggle type functions/macros have their mode id saved until toggled off or a different mode is activated by toggle overwriting the last toggle mode.  When a Momentary type function or key is used while another mode is toggled the toggled mode will be reactivated once the momentary mode is released. Toggling a mode on will overwrite both the saved toggled mode id (_if different_) as well as the current mode id while using a momentary type key will only overwrite the current mode.

#### Built-in Pointing Device Modes
| Pointing Device Mode  | Alias     | Mode Id | Description                                                                                                                       |
| :-------------------- | --------- | :-----: | --------------------------------------------------------------------------------------------------------------------------------- |
| `PM_HISTORY`          | `PM_HST`  |    10   | x movement of pointing device to undo and redo macros  `x->(C(KC_Z)), C(KC_Y)`  `y->ignored`                                      |
| `PM_VOLUME`           | `PM_VOL`  |    11   | y movement of pointing device to media volume up/down (requires `EXTRAKEY_ENABLED`) `x->ignored` `y->(KC_VOLU, KC_VOLD)`          |
| `PM_CARET`            | `PM_CRT`  |    12   | Taps arrow keys based on pointing input  `x->(<-, ->)` `y->(^, v)`                                                                |
| `PM_PRECISION`        | `PM_PRE`  |    13   | Reduce x and y movement output of pointing device by the divisor (_similar to "sniping" modes_)                                   |
| `PM_DRAG`             | `PM_DRG`  |    14   | Change x and y movement of pointing device into h and v axis values  `x->h`  `y->v`                                               |
| `PM_NONE`             |  _None_   |    15   | Null pointing mode that will will pass through normal x and y output of pointing device (Cannot be overwritten)                   |
   
***Notes:***   
-***These modes can all be overwritten with the exception of `PM_NONE`.***   
-***The mode id count starts at 0 (e.g. mode id 15 is the 16th mode) and thus mode mode ids 0-9 are free to be used without overwriting a mode (see adding custom modes below), however mode ids 10-14 will overwrite the modes above (see advanced use below for adding custom modes past mode id 15).***

#### Use In A keymap:
```c
// in keymap.c

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_TEST] = LAYOUT(
      PM_MO(PM_DRG),  PM_TG(PM_PRE), PM_MO(PM_VOL)
      )
  };

```

### Settings
| Define                         | Description                                                                               |  Range  |      Units    |                  Default |
| ------------------------------ | ----------------------------------------------------------------------------------------- | :-----: | :-----------: | -----------------------: |
| `POINTING_DEVICE_MODES_ENABLE` | Enables pointing device pointing device modes feature                                     |  `NA`   |    `None`     |            _Not defined_ |
| `POINTING_DEVICE_INVERT_V`     | Inverts stored v axis accumulation (affects all modes)                                    |  `NA`   |    `None`     |            _Not defined_ |
| `POINTING_DEVICE_INVERT_H`     | Inverts stored h axis accumulation (affects all modes)                                    |  `NA`   |    `None`     |            _Not defined_ |
| `POINTING_MODE_DEFAULT`        | Default pointing device mode                                                              | `0-255` |    `None`     |                `PM_NONE` |
| `POINTING_TAP_DELAY`           | Delay between key presses in `pointing_tap_codes` in ms                                   | `0-255` |     `ms`      |                      `0` |
| `POINTING_MODE_MAP_COUNT`      | Number of modes defined in `pointing_device_mode_maps`                                    | `0-255` |    `None`     |                      `0` |
| `POINTING_DEFAULT_DIVISOR`     | Default divisor for all modes that do not have a defined divisor                          | `1-255` |   `Varies`    |                     `64` |
| `POINTING_HISTORY_DIVISOR`     | Accumulated stored h/v per key tap in `PM_HISTORY` mode                                   | `1-255` | `(h\|v)/tap`  |                     `64` |
| `POINTING_VOLUME_DIVISOR`      | Accumulated stored h/v per key tap in `PM_VOLUME` mode                                    | `1-255` | `(h\|v)/tap`  |                     `64` |
| `POINTING_CARET_DIVISOR`       | Accumulated stored h/v per key tap in `PM_CARET` mode                                     | `1-255` | `(h\|v)/tap`  |                     `32` |
| `POINTING_CARET_DIVISOR_V`     | Stored v per tap in `PM_CARET` (_overrides_ `POINTING_CARET_DIVISOR` _Recommended:_ `32`) | `1-255` |   `(v)/tap`   | `POINTING_CARET_DIVISOR` |
| `POINTING_CARET_DIVISOR_H`     | Stored h per tap in `PM_CARET` (_overrides_ `POINTING_CARET_DIVISOR` _Recommended:_ `16`) | `1-255` |   `(h)/tap`   | `POINTING_CARET_DIVISOR` |
| `POINTING_PRECISION_DIVISOR`   | Pointing device x/y movement per output x/y in `PM_PRECISION` mode                        | `1-255` | `(x\|y)/dot`  |                      `2` |
| `POINTING_DRAG_DIVISOR`        | Pointing device x/y movement per h/v axis tick in `PM_DRAG` mode                          | `1-255` | `(x\|y)/dot`  |                      `4` |
   
***Notes:***  
1. it is recommended that generally powers of 2 are used for divisors **(e.g. 1, 2, 4, 8, 16, 32, 64, 128*)** as they should optimize better (_less code space and faster to compute_), but **any positive integer of 255 or less** will work.   
2. Drag scroll speed will be effected by OS mouse settings (_there are usually separate settings for scroll "wheel" and "wheel tilt"_)   
    - The `POINTING_DRAG_DIVISOR` default value of 8 is based on having mouse settings in the OS set to one line per tick of "mouse wheel" or "wheel tilt" (_the minimum_)   
3. `POINTING_PRECISION_DIVISOR` default will half cursor speed when active (_divisor of 2_) but a divisor of 4 is fine to use as well but the cursor will be quite a bit slower, however divisors of 8 or greater will likely only work well for high cpi settings.
4. Speed and sensitivity of any pointing device mode will be impacted by the pointing device CPI setting so divisors may need to be adjusted to personal preference and CPI settings typically used.   
5. Recommended settings for `POINTING_CARET_DIVISOR_V` and `POINTING_CARET_DIVISOR_H` will give faster horizontal caret movement than vertical and will give even more stability to keeping movement horizontal.

### Basic Custom Modes
There are a couple of ways to add new pointing device modes, using the pointing device mode maps will be covered here under basic use where the other method of using the `process_pointing_mode_*` callbacks will be covered under advance use.

#### Pointing Device Mode Maps
The easiest way to add pointing device modes that are only using keycode taps (similar to `PM_CARET`, `PM_VOLUME`, and `PM_HISTORY`) are through creating Pointing device mode maps.

```c
// Pointing Device Mode Maps Format
const uint16_t pointing_device_mode_maps[][4] = {
    [<pm mode 0>] = POINTING_MODE_LAYOUT(
                <keycode up>,
        <keycode left>,       <keycode right>,
                <keycode down>
    ),
    //... all other pointing mode maps ...
    [<pm mode final>] = POINTING_MODE_LAYOUT(
                <keycode up>,
        <keycode left>,       <keycode right>,
                <keycode down>
    )
}

```

#### Example Mode Maps:
```c
// in config.h:
#define POINTING_DEVICE_MODES_ENABLE // always needed (assumed for future example code)
#define POINTING_MODE_MAP_COUNT 4    // number of modes in map

// in keymap.c
// enums always start at zero so just start 
enum keymap_pointing_device_modes {
    PM_BROW,      // BROWSER TAB Manipulation            [mode id 0]
    PM_RGB_MD_VA, // RGB Control for mode and Brightness [mode id 1]
    PM_RGB_HU_SA, // RGB Control for HUE and Saturation  [mode id 2]
    PM_RGB_SPEED  // RGB Control for Speed               [mode id 3]
};

const uint16_t pointing_device_mode_maps[][4] = {
    [PM_BROW] = POINTING_MODE_LAYOUT(
                C(S(KC_PGUP)),
        C(S(KC_TAB)),       C(KC_TAB),
                C(S(KC_PGDN))
    ),
    [PM_RGB_MD_VA] = POINTING_MODE_LAYOUT(
                RGB_VAI,
        RGB_RMOD,        RGB_MOD,
                RGB_VAD
    ),
    [PM_RGB_HU_SA] = POINTING_MODE_LAYOUT(
                RGB_SAI,
        RGB_HUD,        RGB_HUI,
                RGB_SAD
    ),
    [PM_RGB_SPEED] = POINTING_MODE_LAYOUT(
                KC_NO,
        RGB_SPD,        RGB_SPI,
                KC_NO
    )
};

```
***Note: `KC_NO` is used when no keycode is desired, use of `KC_TRNS` or `_______` is unsupported***   
***Additional Note: any mode map with a mode id greater than `POINTING_MODE_MAP_COUNT - 1` will be ignored***   

**Note on Adding more than 10 modes using pointing device mode maps:**   
If 11 or more modes are added to the map (`mode_id > 9`) then these modes will override the built in modes (in the order of `PM_HISTORY`, `PM_VOLUME`, `PM_CARET`, `PM_PRECISION`, `PM_DRAG`).  Mode maps will technically function for more than 15 modes (`mode_id > 14`) but the modes will need to be activated the modes above 16 will be needed (_see Advanced use_) and all built in modes will be forcibly overwritten with the exception of `PM_NONE`. This will cause the map with mode id 15 to not function.  Because of these limitations it is not recommended to use pointing device mode maps for more than 10 modes (_mode id 9_) unless the built in modes are not being used or are intended to be modified/overwritten .  This limitation can be gotten around by defining modes using the more advanced options of pointing device modes and custom keys (_see adding custom pointing mode keycodes and Advanced use_).

### Adding & Customizing Divisors   
All Newly added modes will use `POINTING_DEFAULT_DIVISOR` unless a divisor is defined for the modes in the `get_pointing_mode_divisor` callback functions.
For most keycode tapping modes a divisor of `64` works well, which is the default divisor for `POINTING_DEFAULT_DIVISOR`.  The `get_pointing_mode_divisor_*` callbacks have two variables available, `mode_id` which is the current pointing device mode id and `direction` which indicates the primary direction of the stored accumulated h/v values with the largest magnitude (_see table below_).  This makes it simple to have a unique divisor for each direction or axis for a particular mode.

| Direction code | Value |Description                                                                                         |
| :------------- | ----- | -------------------------------------------------------------------------------------------------- |
| `PD_DOWN`      |     0 | Stored v axis is negative and the largest value (also default if both h and v are the same value)  |
| `PD_UP`        |     1 | Stored v axis is positive and the largest value                                                    |
| `PD_LEFT`      |     2 | Stored h axis is negative and the largest value                                                    |
| `PD_RIGHT`     |     3 | Stored h axis is positive and the largest value                                                    |   
   
***NOTE: if checking `pointing_mode.direction` or `direction` is on the h or v axis using `direction < PD_LEFT` could be used to return true for the v axis and false for the h axis (see example below)***
   
#### Callbacks to set pointing device mode divisors
The following callbacks can be used to overwrite built in mode divisors or to set divisors for new modes. The `get_pointing_mode_divisor` stacks works by checking the functions until a non zero value is reached in order of `user`->`kb`->`built in`->`default_value`.  Returning a divisor of `0` will allow processing to continue on to the next function, However this means that if any of the callback returns a default value other than 0 then that will overwrite the divisors for all modes not defined in the callback functions (such as built in modes).  This allows for overriding built in divisors by users/keymaps and keyboards and overriding keyboard level divisors by users/keymaps so it is possible to give built in modes the same level of divisor customization as new custom modes.

| Callback                                                                      | Description                                                               |
| ----------------------------------------------------------------------------- | ------------------------------------------------------------------------- |
| `uint8_t get_pointing_mode_divisor_kb(uint8_t mode_id, uint8_t direction);`   | Keyboard level callback for setting divisor based on mode id an direction |
| `uint8_t get_pointing_mode_divisor_user(uint8_t mode_id, uint8_t direction);` | Keymap/user level callback for setting divisor                            |

 
#### Example code of divisor adjustment
```c
// added to keymap.c
// assuming poinding device enum and maps from example above
uint8_t get_pointing_mode_divisor_user(uint8_t mode_id, uint8_t direction) {
    switch(mode_id) {
        
        case PM_BROW:
            // half speed for vertical axis
            return direction < PD_LEFT ? 128 : 64;
        
        case PM_RGB_MD_VA:
            // half speed for horizontal axis
            return direction < PD_LEFT ? 64 : 128;
        
        case PM_RGB_HU_SA:
            // example of unique divisor for each mode (not actually recommended for this mode (64 would be a good divisor here))
            switch(direction) {
                case PD_DOWN:
                    return 32;
                case PD_UP:
                    return 64;
                case PD_LEFT:
                    return 16;
                case PD_RIGHT:
                    return 128;
            }  
            
        case PM_RGB_SPEED:
            return 64; // could skip adding this if default if POINTING_DEFAULT_DIVISOR is 64
    }
    
    return 0; // returning 0 to let processing of divisors continue
}
```
This code assigns some divisors for some of the modes added in a previous code example showing some of the things that are possible with defining divisors. It could also be possible to make divisors adjust based on global variables such as a dynamic divisor adjustment term (_note that if a divisor of zero is returned it will default to_ `POINTING_DIVISOR_DEFAULT`).


### Creating Custom pointing mode keycodes

There are built in functions to simplify the creation of custom keycodes and it is generally recommended to use these in combination with other functions rather than using mode changing functions as they do handle some edge cases to ensure consistent behaviour.

| Function                                                                                    | Description                                                                                     | Return type |
| :------------------------------------------------------------------------------------------ | :---------------------------------------------------------------------------------------------- | :---------: |
| `pointing_mode_key_momentary(uint8_t mode_id, keyrecord_t* record)`                         | Momentary change of pointing mode while key is held (_for use in custom keycodes_)              |   _None_    |
| `pointing_mode_key_toggle(uint8_t mode_id, keyrecord_t* record)`                            | Toggle pointing mode on/off on key release (_for use in custom keycodes_)                       |   _None_    |

These can be used to activate pointing device modes outside of the range of the built in keycodes as well as adding custom features to a mode that activate on key press such as registering a keycode and holding it until key release (_see code examples below_).

#### Example code for adding an open app navigation mode outside of basic mode range
```c
// in keymap.c

enum my_pointing_modes {
    // place Pointing device mode id outside of basic range as it will not use PM_MO or PM_TG macros
    PM_APP = PM_SAFE_RANGE  // Control alt tabbing through open applications [mode id: 16]
};

enum my_custom_keycodes {
    KC_MO_APP = SAFE_RANGE
};

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    
    switch(keycode) {
        case KC_MO_APP:
            // hold alt while mode and key are active
            if(record->event.pressed) {
                register_code(KC_LALT);
            } else {
                unregister_code(KC_LALT);
            }
            pointing_mode_key_momentary(PM_APP, record);
            return false; // stop key record processing
    }
    return true; // allow normal key record processing
}

// This callback and other functions are explained below in advanced use but is needed here for completeness
bool process_pointing_mode_user(pointing_mode_t pointing_mode, report_mouse_t* mouse_report) {
    switch(pointing_mode.id) {
        // Open App scrolling mode (requires alt key to be held while active)
        case PM_APP:
            pointing_tap_codes(S(KC_TAB), KC_NO, KC_NO, KC_TAB);
            return false; // stop pointing mode processing
    }
    return true; // allow normal pointing mode processing
}

```
The above code will create an Application pointing mode that should work on windows and linux allowing for navigation through currently open applications/windows having the alt key held will keep the application/window UI active as long as the `KC_MO_APP` key is held (_after the first pointing device input_).


## Advanced use   
There are a number of functions allowing access and control of different aspects of the pointing modes feature most of these are intended for more advanced control such as custom keycodes to activate pointing modes or pointing modes that are manipulating something other than key presses (pointing device data, internal keyboard variables, etc.).

### `pointing_mode_t` structure
The current active pointing mode is controlled by tracking an internal `pointing_mode_t` data structure. The `pointing_mode.direction`, and `pointing_mode.divisor` variables are updated immediately after `pointing_mode.h`, and `pointing_mode.v` at the start of the pointing device modes process before the callback functions are called.  Therefore if the `h`,`v`, or `mode_id` are modified and it is desired to have the direction and divisor reflect the changes they will need to be updated by calling `pointing_mode_update()`.  A few other variables are tracked outside of the pointing mode structure and there are specialized functions to access/modify them.

| Variable                  | Description                               | Data type  | Functions to access/modify                      |
| :------------------------ | :---------------------------------------- | :--------: | :---------------------------------------------- |
| `pointing_mode.id`        | Id number of current active mode          | `uint8_t`  | `get_pointing_mode_id`, `set_pointing_mode_id`  |
| `pointing_mode.divisor`   | Divisor of current mode id and direction  | `uint8_t`  | 
| `pointing_mode.direction` | Direction based on stored h and v values  | `uint8_t`  |
| `pointing_mode.h`         | Stored horizontal axis value              | `uint16_t` |
| `pointing_mode.v`         | Stored vertical axis value                | `uint16_t` |
   
### Other tracked variables (Not directly accessible use functions)
|   Variable   | Description                                                     | Data type  | Functions 
| :----------: | :-------------------------------------------------------------- | :--------: |
| `tg_mode_id` | Mode id of last active toggle mode                              | `uint8_t`  |
|  `is_left`   | if mode is on left pointing device (see split pointing below)   |   `bool`   |
  
***NOTE: `is_left` is only available when `SPLIT_POINTING_ENABLE` and `POINTING_DEVICE_COMBINED` are both defined***

#### Controlling pointing device modes
| Function                                   | Description                                                                                                                          | Return type |
| :----------------------------------------- | :----------------------------------------------------------------------------------------------------------------------------------- | :---------: |
| `set_pointing_mode_id(uint8_t mode_id)`    | Set current pointing device mode id to `mode_id`                                                                                     |   _None_    |
| `toggle_pointing_mode_id(uint8_t mode_id)` | Set both stored toggle, and current mode id to `mode_id` <br /> or `POINTING_MODE_DEFAULT` if the stored toggle mode id is `mode_id` |   _None_    |
| `get_pointing_mode_id(void)`               | Return current stored pointing device mode id                                                                                        |  `uint8_t`  |
| `get_toggled_pointing_mode_id(void)`       | Return current stored toggle pointing device mode id                                                                                 |  `uint8_t`  |
 
***Note: `toggle_pointing_mode_id(POINTING_MODE_DEFAULT)` can be used to clear the stored toggled mode but it will also reset the current active mode so that would need to be stored first and then reactivated if that is not the desired behaviour***
 
These can be used to manipulate the current pointing mode id and toggle mode id at any time such as during layer changes, keypresses, tap dance sequences, and anywhere else in code (see examples below).

#### Code example for changing modes on layer changes
```c
// in keymap.c
// assuming enum and Layout for layers are already defined
layer_state_t layer_state_set_user(layer_state_t state) {
    // reset toggle to base pointing mode
    toggle_pointing_mode_id(POINTING_MODE_DEFAULT);
    switch(get_highest_layer(state)) {
        case _NAVI:  // Navigation layer
            toggle_pointing_mode_id(PM_CARET);
            break;
        case _MEDIA: // Media control layer
            toggle_pointing_mode_id(PM_VOL);
            break;
    }
    return state;
}
```

[comment]: # (>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>TODO: ADD Code Example changing pointing modes based on tap_dance)

### Advanced custom modes
Creating pointing device modes outside of the keycode mapped modes requires using the mode processing callbacks.

#### Callbacks for adding custom modes
These callbacks work similar to keycode processing callbacks in that returning false will prevent further processing of the pointing device mode.  The processing order of pointing device modes is: `user`->`kb`->`maps`->`built in`.

| Callback                                                                                         | Description                                                 |
| ------------------------------------------------------------------------------------------------ | ----------------------------------------------------------- |
| `bool process_pointing_mode_kb(pointing_mode_t pointing_mode, report_mouse_t* mouse_report)`     | keyboard level callback for adding pointing device modes    |
| `bool process_pointing_mode_user(pointing_mode_t pointing_mode, report_mouse_t* mouse_report)`   | user/keymap level callback for adding pointing device modes |
   
There are several functions available to assist with the creation of custom modes.  These allow for setting the internal `pointing_mode` values with any changes that have been made, as well as updating divisor and direction after changes.

| Function                                                                                    | Description                                                                                     | Return type |
| :------------------------------------------------------------------------------------------ | :---------------------------------------------------------------------------------------------- | :---------: |
| `set_pointing_mode(pointing_mode_t pointing_mode)`                                          | Set stored pointing mode state to `pointing_mode`                                               |   _None_    |
| `pointing_mode_update(void)`                                                                | Update stored direction and divisor based on current mode id and h/v values                     |   _None_    |
| `pointing_tap_codes(uint16_t kc_left, uint16_t kc_down, uint16_t kc_up, uint16_t kc_right)` | Convert stored h/v axis value to key taps depending on direction, 1 key tap per current divisor |   _None_    |
     
#### Creating modes using callback functions:
```c
// in <keyboard>.h or <keyboard>.c

static bool APP_ALT; // flag to track alt key activation for APP scrolling

// add custom pointing device mode
enum my_kb_pointing_modes {
    // start at the end of basic range
    PM_BROW = PM_SAFE_RANGE,   // [mode id: 16]
    PM_CUR_ACCEL,              // [mode id: 17]
    PM_APP_2,                  // [mode id: 18]
    // good practice to allow users to expand further
    KB_PM_SAFE_RANGE
};

// add custom keycodes
enum my_kb_keycodes {
    KB_MO_BROW = SAFE_RANGE,
    KB_TG_ACCEL,
    KB_MO_APP,
    // again good practice to allow users to expand
    MY_KB_SAFE_RANGE
};
  
  
// in <keyboard>.c
// define keybaord level divisors
uint8_t get_pointing_mode_divisor_kb(uint8_t mode_id, uint8_t direction) {
    switch(mode_id) {
        case PM_BROW:
            return 64;
        case PM_CUR_ACCEL:
            return 8;
        case PM_APP_2:
            return 64;
    }
    
    return 0; // continue processing
}

#define CONSTRAIN_XY(amt) ((amt) < XY_REPORT_MIN ? XY_REPORT_MIN : ((amt) > XY_REPORT_MAX ? XY_REPORT_MAX : (amt)))

bool process_pointing_mode_kb(pointing_mode_t pointing_mode, report_mouse_t* mouse_report) {
    switch(pointing_mode.id){
        /** Manipulate browser tabs (win/linux) (switch to left tab, move tab left, move tab right, switch to right tab)
         *  Note that this mode could be put in a mode map but is here as an example of going past the bottom support 10 modes
         *  without overwriting any built in modes
         */
        case PM_BROW:
            pointing_tap_codes(C(S(KC_TAB)), C(S(KC_PGDN)), C(S(KC_PGUP)), C(KC_TAB));
            return false;  // stop pointing mode processing
        
        // Manipulating pointing_mode & mouse_report (cursor speed boost mode example)
        case PM_CUR_ACCEL:
            // reset mouse_report note tha mouse_report is a pointer in this function's context
            *mouse_report = pointing_device_get_report();
#ifdef POINTING_DEVICE_INVERT_H
            // add linear boost to cursor x speed
            mouse_report->x = CONSTRAIN_XY(mouse_report->x - pointing_mode.h / pointing_mode.divisor);
#else
            mouse_report->x = CONSTRAIN_XY(mouse_report->x + pointing_mode.h / pointing_mode.divisor);
#endif
            // collect residuals
            pointing_mode.h = 0;
            // add linear boost to cursor y speed
#ifdef POINTING_DEVICE_INVERT_V
            mouse_report->y = CONSTRAIN_XY(mouse_report->y - pointing_mode.v / pointing_mode.divisor);
#else
            mouse_report->y = CONSTRAIN_XY(mouse_report->y + pointing_mode.v / pointing_mode.divisor);
#endif
            // collect residuals
            pointing_mode.v = 0;
            // update pointing_mode with residual h & v
            set_pointing_mode(pointing_mode);
            // NOTE: mouse_report does not need to be set or sent here as it will be carried forward
            return false; // stop pointing mode processing
        
        // Alternative method for app scrolling that only toggles ALT key when there is movement and holds until key release
        case PM_APP_2:
            // activate alt key if greater/equal to divisor and set flag
            if((abs(pointing_mode.h)) >= pointing_mode.divisor && !APP_ALT) {
                register_code(KC_LALT);
                APP_ALT = true;
            }
            pointing_tap_codes(S(KC_TAB), KC_NO, KC_NO, KC_TAB);
            return false;
    }
    return true;
}

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    switch(keycode) {
        case KB_MO_BROW:
            pointing_mode_key_momentary(PM_BROW, record);
            return true; // continue key record processing
            
        case KB_TG_ACCEL:
            pointing_mode_key_toggle(PM_CUR_ACCEL, record);
            return true; // continue key record processing
            
        case KB_MO_APP:
            // toggle Alt key off on key release and reset flag
            if(!record->event.pressed && APP_ALT) {
                unregister_code(KC_LALT);
                APP_ALT = false;
            }
            pointing_mode_key_momentary(PM_APP_2, record);
            return true; // continue key record processing
    }
}

```

***Note: that in the above code example there needed to be some additional handling of `POINTING_DEVICE_INVERT_V` and `POINTING_DEVICE_INVERT_H` as when modifying cursor movement these may not work as expected otherwise if a user has ether of these options defined.***

## Further customization  
If not using standard QMK functions `pointing_device_task` or `process_record` code (_Not using the built in QMK functions_) then the following functions will be needed to use pointing device modes.
Also there is an ability to modify how pointing device output is converted to stored h & v axes by overwriting `the pointing_modes_axes_conv` function (_see notes and warnings below_).

| Function                                                                               | Description                                                                                     |   Return type    |
| :------------------------------------------------------------------------------------- | :---------------------------------------------------------------------------------------------- | :--------------: |
| `pointing_device_modes_task(report_mouse_t mouse_report)`                              | Intercepts and changes mouse_report for pointing modes                                          | `report_mouse_t` |
| `process_pointing_mode_records(uint16_t keyrecord, keyrecord_t* record)`               | Handle processing of pointing mode keyrecords returning true when processed or false otherwise  |      `bool`      |    
| `pointing_modes_axes_conv(pointing_mode_t pointing_mode, report_mouse_t mouse_report)` | Accumulate (_and clear_) pointing device x/y output to stored h/v (_see notes_)                 | `report_mouse_t` |
   
***Notes:***   
-***`pointing_modes_axes_conv` is only weakly defined and can be overwritten allowing for customization on what happens during accumulation such as adjusting additional variables, dynamic rate of accumulation etc.***   
-***Additional Note: `pointing_modes_axes_conv` does not need to be overwritten to avoid clearing pointing device x/y***   
-***!Warning!: changes made to `pointing_mode` within `pointing_modes_axes_conv` must be saved by calling `set_pointing_mode(pointing_mode)` before returning the updated `mouse_report`***
   
## Multiple pointing devices
If both `SPLIT_POINTING_ENABLE` and `POINTING_DEVICE_COMBINED` are defined then the pointing device modes will use the input from either left or right pointing devices which can set at compile time with `POINTING_MODES_LEFT` and switched at run time using `pointing_mode_switch_hands()`.  Currently pointing device modes does not support control of multiple pointing devices simultaneously, so only one device will be affected by the current active mode with the other giving default output.

#### Relevant Settings

| Define                             | Description                                                 |        Default |
| ---------------------------------- | ----------------------------------------------------------- | -------------: |
| `POINTING_MODES_LEFT`              | Set left side to default pointing device controlled side    |  _Not defined_ |
   
#### Functions when using two pointing devices  
These functions are only available when both `SPLIT_POINTING_ENABLE` and `POINTING_DEVICE_COMBINED` are defined and will cause a compiler error if they are not.  It is recommended that code that uses them is conditional on both of these settings being defined.

| Function                                    | Description                                                                                     | Return type |
| :------------------------------------------ | :---------------------------------------------------------------------------------------------- | :---------: |
| `is_pointing_mode_on_left(void)`            | Return `true` if pointing modes control left side pointing device (_see notes_)                 |    `bool`   |
| `pointing_mode_switch_hands(void)`          | Switch pointing device affected by pointing modes (left/right) (_see notes_)                    |    `void`   |
