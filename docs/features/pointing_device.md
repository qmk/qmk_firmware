# Pointing Device {#pointing-device}

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

| Setting (`config.h`) | Description                                                        | Default                    |
| -------------------- | ------------------------------------------------------------------ | -------------------------- |
| `ADNS5050_SCLK_PIN`  | (Required) The pin connected to the clock pin of the sensor.       | `POINTING_DEVICE_SCLK_PIN` |
| `ADNS5050_SDIO_PIN`  | (Required) The pin connected to the data pin of the sensor.        | `POINTING_DEVICE_SDIO_PIN` |
| `ADNS5050_CS_PIN`    | (Required) The pin connected to the Chip Select pin of the sensor. | `POINTING_DEVICE_CS_PIN`   |



The CPI range is 125-1375, in increments of 125. Defaults to 500 CPI.

### ADNS 9800 Sensor

To use the ADNS 9800 sensor, add this to your `rules.mk`

```make
POINTING_DEVICE_DRIVER = adns9800
```

The ADNS 9800 is an SPI driven optical sensor, that uses laser output for surface tracking.

| Setting (`config.h`)    | Description                                                            | Default                  |
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

| Setting (`config.h`)              | Description                                                                | Default       |
| --------------------------------- | -------------------------------------------------------------------------- | ------------- |
| `ANALOG_JOYSTICK_X_AXIS_PIN`      | (Required) The pin used for the vertical/X axis.                           | _not defined_ |
| `ANALOG_JOYSTICK_Y_AXIS_PIN`      | (Required) The pin used for the horizontal/Y axis.                         | _not defined_ |
| `ANALOG_JOYSTICK_AXIS_MIN`        | (Optional) Sets the lower range to be considered movement.                 | `0`           |
| `ANALOG_JOYSTICK_AXIS_MAX`        | (Optional) Sets the upper range to be considered movement.                 | `1023`        |
| `ANALOG_JOYSTICK_AUTO_AXIS`       | (Optional) Sets ranges to be considered movement automatically.            | _not defined_ |
| `ANALOG_JOYSTICK_SPEED_REGULATOR` | (Optional) The divisor used to slow down movement. (lower makes it faster) | `20`          |
| `ANALOG_JOYSTICK_READ_INTERVAL`   | (Optional) The interval in milliseconds between reads.                     | `10`          |
| `ANALOG_JOYSTICK_SPEED_MAX`       | (Optional) The maximum value used for motion.                              | `2`           |
| `ANALOG_JOYSTICK_CLICK_PIN`       | (Optional) The pin wired up to the press switch of the analog stick.       | _not defined_ |
| `ANALOG_JOYSTICK_WEIGHTS`         | (Optional) Use custom weights for lever positions.                         | _not defined_ |
| `ANALOG_JOYSTICK_CUTOFF`          | (Optional) Cut off movement when joystick returns to start position.       | _not defined_ |

If `ANALOG_JOYSTICK_AUTO_AXIS` is used, then `ANALOG_JOYSTICK_AXIS_MIN` and `ANALOG_JOYSTICK_AXIS_MAX` are ignored.

By default analog joystick implementation uses `x^2` weighting for lever positions. `ANALOG_JOYSTICK_WEIGHTS` allows to experiment with different configurations that might feel better.

E.g. This is weights for `((x-0.4)^3+0.064)/0.282`:

```c
#define ANALOG_JOYSTICK_WEIGHTS {0,2,4,5,7,8,9,10,12,13,14,15,15,16,17,18,18,19,19,20,20,21,21,21,22,22,22,22,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,24,24,24,24,24,24,25,25,25,26,26,26,27,28,28,29,29,30,31,32,33,34,35,36,37,38,40,41,43,44,46,48,49,51,53,56,58,60,62,65,68,70,73,76,79,82,85,89,92,96,100}
```

You can use following JS code to generate weights for different formulas:

```js
JSON.stringify(Array.from(Array(101).keys()).map(x => Math.ceil((((x/100-0.4)**3+0.064)/0.282*100))))
```

### Azoteq IQS5XX Trackpad

To use a Azoteq IQS5XX trackpad, add this to your `rules.mk`:

```make
POINTING_DEVICE_DRIVER = azoteq_iqs5xx
```

This supports the  IQS525, IQS550 and IQS572 controllers, with the latter two being used in the TPS43 and TPS65 trackpads.

#### Device settings

Specific device profiles are provided which set the required values for dimensions and resolution.

| Setting                          | Description                                                |
| -------------------------------- | ---------------------------------------------------------- |
| `AZOTEQ_IQS5XX_TPS43`            | (Pick One) Sets resolution/mm to TPS43 specifications.     |
| `AZOTEQ_IQS5XX_TPS65`            | (Pick One) Sets resolution/mm to TPS65 specifications.     |

::: tip
If using one of the above defines you can skip to gesture settings.
:::

| Setting                          | Description                                                | Default       |
| -------------------------------- | ---------------------------------------------------------- | ------------- |
| `AZOTEQ_IQS5XX_WIDTH_MM`         | (Required) Width of the trackpad sensor in millimeters.    | _not defined_ |
| `AZOTEQ_IQS5XX_HEIGHT_MM`        | (Required) Height of the trackpad sensor in millimeters.   | _not defined_ |
| `AZOTEQ_IQS5XX_RESOLUTION_X`     | (Optional) Specify X resolution for CPI calculation.       | _not defined_ |
| `AZOTEQ_IQS5XX_RESOLUTION_Y`     | (Optional) Specify Y resolution for CPI calculation.       | _not defined_ |

**`AZOTEQ_IQS5XX_RESOLUTION_X/Y`** fall back resolutions are provided within the driver based on controller model.

| I2C Setting               | Description                                                                     | Default |
| ------------------------- | ------------------------------------------------------------------------------- | ------- |
| `AZOTEQ_IQS5XX_ADDRESS`   | (Optional) Sets the I2C Address for the Azoteq trackpad                         | `0xE8`  |
| `AZOTEQ_IQS5XX_TIMEOUT_MS`| (Optional) The timeout for i2c communication with in milliseconds.              | `10`    |

#### Gesture settings

| Setting                                   | Description                                                                          | Default     |
| ----------------------------------------- | ------------------------------------------------------------------------------------ | ----------- |
| `AZOTEQ_IQS5XX_TAP_ENABLE`                | (Optional) Enable single finger tap. (Left click)                                    | `true`      |
| `AZOTEQ_IQS5XX_TWO_FINGER_TAP_ENABLE`     | (Optional) Enable two finger tap. (Right click)                                      | `true`      |
| `AZOTEQ_IQS5XX_PRESS_AND_HOLD_ENABLE`     | (Optional) Emulates holding left click to select text.                               | `false`     |
| `AZOTEQ_IQS5XX_SWIPE_X_ENABLE`            | (Optional) Enable swipe gestures X+ (Mouse Button 5) / X- (Mouse Button 4)           | `false`     |
| `AZOTEQ_IQS5XX_SWIPE_Y_ENABLE`            | (Optional) Enable swipe gestures Y+ (Mouse Button 3) / Y- (Mouse Button 6)           | `false`     |
| `AZOTEQ_IQS5XX_ZOOM_ENABLE`               | (Optional) Enable zoom gestures Zoom Out (Mouse Button 7) / Zoom In (Mouse Button 8) | `false`     |
| `AZOTEQ_IQS5XX_SCROLL_ENABLE`             | (Optional) Enable scrolling using two fingers.                                       | `true`      |
| `AZOTEQ_IQS5XX_TAP_TIME`                  | (Optional) Maximum time in ms for tap to be registered.                              | `150`       |
| `AZOTEQ_IQS5XX_TAP_DISTANCE`              | (Optional) Maximum deviation in pixels before single tap is no longer valid.         | `25`        |
| `AZOTEQ_IQS5XX_HOLD_TIME`                 | (Optional) Minimum time in ms for press and hold.                                    | `300`       |
| `AZOTEQ_IQS5XX_SWIPE_INITIAL_TIME`        | (Optional) Maximum time to travel initial distance before swipe is registered.       | `150`       |
| `AZOTEQ_IQS5XX_SWIPE_INITIAL_DISTANCE`    | (Optional) Minimum travel in pixels before swipe is registered.                      | `300`       |
| `AZOTEQ_IQS5XX_SWIPE_CONSECUTIVE_TIME`    | (Optional) Maximum time to travel consecutive distance before swipe is registered.   | `0`         |
| `AZOTEQ_IQS5XX_SWIPE_CONSECUTIVE_DISTANCE`| (Optional) Minimum travel in pixels before a consecutive swipe is registered.        | `2000`      |
| `AZOTEQ_IQS5XX_SCROLL_INITIAL_DISTANCE`   | (Optional) Minimum travel in pixels before scroll is registered.                     | `50`        |
| `AZOTEQ_IQS5XX_ZOOM_INITIAL_DISTANCE`     | (Optional) Minimum travel in pixels before zoom is registered.                       | `50`        |
| `AZOTEQ_IQS5XX_ZOOM_CONSECUTIVE_DISTANCE` | (Optional) Maximum time to travel zoom distance before zoom is registered.           | `25`        |

#### Rotation settings

| Setting                      | Description                                                | Default       |
| ---------------------------- | ---------------------------------------------------------- | ------------- |
| `AZOTEQ_IQS5XX_ROTATION_90`  | (Optional) Configures hardware for 90 degree rotation.     | _not defined_ |
| `AZOTEQ_IQS5XX_ROTATION_180` | (Optional) Configures hardware for 180 degree rotation.    | _not defined_ |
| `AZOTEQ_IQS5XX_ROTATION_270` | (Optional) Configures hardware for 270 degree rotation.    | _not defined_ |

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

| Setting                              | Description                                                | Default                                     |
| ------------------------------------ | ---------------------------------------------------------- | ------------------------------------------- |
| `CIRQUE_PINNACLE_DIAMETER_MM`        | (Optional) Diameter of the trackpad sensor in millimeters. | `40`                                        |
| `CIRQUE_PINNACLE_ATTENUATION`        | (Optional) Sets the attenuation of the sensor data.        | `EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_4X` |
| `CIRQUE_PINNACLE_CURVED_OVERLAY`     | (Optional) Applies settings tuned for curved overlay.      | _not defined_                               |
| `CIRQUE_PINNACLE_POSITION_MODE`      | (Optional) Mode of operation.                              | _not defined_                               |
| `CIRQUE_PINNACLE_SKIP_SENSOR_CHECK`  | (Optional) Skips sensor presence check                     | _not defined_                               |

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

| Setting                                 | Description                                                             | Default     |
|-----------------------------------------|-------------------------------------------------------------------------|-------------|
| `CIRQUE_PINNACLE_X_LOWER`               | (Optional) The minimum reachable X value on the sensor.                 | `127`       |
| `CIRQUE_PINNACLE_X_UPPER`               | (Optional) The maximum reachable X value on the sensor.                 | `1919`      |
| `CIRQUE_PINNACLE_Y_LOWER`               | (Optional) The minimum reachable Y value on the sensor.                 | `63`        |
| `CIRQUE_PINNACLE_Y_UPPER`               | (Optional) The maximum reachable Y value on the sensor.                 | `1471`      |
| `CIRQUE_PINNACLE_REACHABLE_CALIBRATION` | (Optional) Enable console messages to aide in calibrating above values. | not defined |

#### Absolute mode gestures

| Gesture Setting                                | Description                                                                    | Default              |
| ---------------------------------------------- | ------------------------------------------------------------------------------ | -------------------- |
| `CIRQUE_PINNACLE_TAP_ENABLE`                   | (Optional) Enable tap to click. This currently only works on the master side.  | _not defined_        |
| `CIRQUE_PINNACLE_TAPPING_TERM`                 | (Optional) Length of time that a touch can be to be considered a tap.          | `TAPPING_TERM`/`200` |
| `CIRQUE_PINNACLE_TOUCH_DEBOUNCE`               | (Optional) Length of time that a touch can be to be considered a tap.          | `TAPPING_TERM`/`200` |

`POINTING_DEVICE_GESTURES_SCROLL_ENABLE` in this mode enables circular scroll. Touch originating in outer ring can trigger scroll by moving along the perimeter. Near side triggers vertical scroll and far side triggers horizontal scroll.

Additionally, `POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE` is supported in this mode.

#### Relative mode gestures

| Gesture Setting (`config.h`)           | Description                                                                                                                                                                               | Default       |
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

| Setting (`config.h`) | Description                                                    | Default                    |
| -------------------- |--------------------------------------------------------------- | -------------------------- |
| `PAW3204_SCLK_PIN`   | (Required) The pin connected to the clock pin of the sensor.   | `POINTING_DEVICE_SCLK_PIN` |
| `PAW3204_SDIO_PIN`   | (Required) The pin connected to the data pin of the sensor.    | `POINTING_DEVICE_SDIO_PIN` |

The CPI range is 400-1600, with supported values of (400, 500, 600, 800, 1000, 1200 and 1600).  Defaults to 1000 CPI.

### Pimoroni Trackball

To use the Pimoroni Trackball module, add this to your `rules.mk`:

```make
POINTING_DEVICE_DRIVER = pimoroni_trackball
```

The Pimoroni Trackball module is a I2C based breakout board with an RGB enable trackball. 

| Setting (`config.h`)                 | Description                                                                        | Default |
| ------------------------------------ | ---------------------------------------------------------------------------------- | ------- |
| `PIMORONI_TRACKBALL_ADDRESS`         | (Required) Sets the I2C Address for the Pimoroni Trackball.                        | `0x0A`  |
| `PIMORONI_TRACKBALL_TIMEOUT`         | (Optional) The timeout for i2c communication with the trackball in milliseconds.   | `100`   |
| `PIMORONI_TRACKBALL_SCALE`           | (Optional) The multiplier used to generate reports from the sensor.                | `5`     |
| `PIMORONI_TRACKBALL_DEBOUNCE_CYCLES` | (Optional) The number of scan cycles used for debouncing on the ball press.        | `20`    |
| `PIMORONI_TRACKBALL_ERROR_COUNT`     | (Optional) Specifies the number of read/write errors until the sensor is disabled. | `10`    |

### PMW3320 Sensor

To use the PMW3320 sensor, add this to your `rules.mk`

```make
POINTING_DEVICE_DRIVER = pmw3320
```

The PMW3320 sensor uses a serial type protocol for communication, and requires an additional light source (it could work without one, but expect it to be out of service early).

| Setting             | Description                                                         | Default                    |
| ------------------- | ------------------------------------------------------------------- | -------------------------- |
| `PMW3320_SCLK_PIN` | (Required) The pin connected to the clock pin of the sensor.        | `POINTING_DEVICE_SCLK_PIN` |
| `PMW3320_SDIO_PIN` | (Required) The pin connected to the data pin of the sensor.         | `POINTING_DEVICE_SDIO_PIN` |
| `PMW3320_CS_PIN`   | (Required) The pin connected to the cable select pin of the sensor. | `POINTING_DEVICE_CS_PIN`   |

The CPI range is 500-3500, in increments of 250. Defaults to 1000 CPI.

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

| Setting (`config.h`)         | Description                                                                                 | Default                  |
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

::: warning
Ideally, new sensor hardware should be added to `drivers/sensors/` and `quantum/pointing_device_drivers.c`, but there may be cases where it's very specific to the hardware.  So these functions are provided, just in case. 
:::

## Common Configuration

| Setting                                        | Description                                                                                                                      | Default       |
| ---------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------- | ------------- |
| `MOUSE_EXTENDED_REPORT`                        | (Optional) Enables support for extended mouse reports. (-32767 to 32767, instead of just -127 to 127).                           | _not defined_ |
| `WHEEL_EXTENDED_REPORT`                        | (Optional) Enables support for extended wheel reports. (-32767 to 32767, instead of just -127 to 127).                           | _not defined_ |
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

::: warning
When using `SPLIT_POINTING_ENABLE` the `POINTING_DEVICE_MOTION_PIN` functionality is not supported and `POINTING_DEVICE_TASK_THROTTLE_MS` will default to `1`. Increasing this value will increase transport performance at the cost of possible mouse responsiveness.
:::

The `POINTING_DEVICE_CS_PIN`, `POINTING_DEVICE_SDIO_PIN`, and `POINTING_DEVICE_SCLK_PIN` provide a convenient way to define a single pin that can be used for an interchangeable sensor config.  This allows you to have a single config, without defining each device.  Each sensor allows for this to be overridden with their own defines. 

::: warning
Any pointing device with a lift/contact status can integrate inertial cursor feature into its driver, controlled by `POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE`. e.g. PMW3360 can use Lift_Stat from Motion register. Note that `POINTING_DEVICE_MOTION_PIN` cannot be used with this feature; continuous polling of `get_report()` is needed to generate glide reports.
:::

## High Resolution Scrolling

| Setting                                  | Description                                                                                                               | Default       |
| ---------------------------------------- | ------------------------------------------------------------------------------------------------------------------------- | ------------- |
| `POINTING_DEVICE_HIRES_SCROLL_ENABLE`    | (Optional) Enables high resolution scrolling.                                                                             | _not defined_ |
| `POINTING_DEVICE_HIRES_SCROLL_MULTIPLIER`| (Optional) Resolution mutiplier value used by high resolution scrolling. Must be between 1 and 127, inclusive.            | `120`         |
| `POINTING_DEVICE_HIRES_SCROLL_EXPONENT`  | (Optional) Resolution exponent value used by high resolution scrolling. Must be between 0 and 127, inclusive.             | `0`           |

The `POINTING_DEVICE_HIRES_SCROLL_ENABLE` setting enables smooth and continuous scrolling when using trackballs or high-end encoders as mouse wheels (as opposed to the typical stepped behavior of most mouse wheels).
This works by adding a resolution multiplier to the HID descriptor for mouse wheel reports, causing the host computer to interpret each wheel tick sent by the keyboard as a fraction of a normal wheel tick.
The resolution multiplier is set to `1 / (POINTING_DEVICE_HIRES_SCROLL_MULTIPLIER * (10 ^ POINTING_DEVICE_HIRES_SCROLL_EXPONENT))`, which is `1 / 120` by default.
If even smoother scrolling than provided by this default value is desired, first try using `#define POINTING_DEVICE_HIRES_SCROLL_EXPONENT 1` which will result in a multiplier of `1 / 1200`.

The function `pointing_device_get_hires_scroll_resolution()` can be called to get the pre-computed resolution multiplier value as a `uint16_t`.

::: warning
High resolution scrolling usually results in larger and/or more frequent mouse reports. This can result in overflow errors and overloading of the host computer's input buffer. 
To deal with these issues, define `WHEEL_EXTENDED_REPORT` and throttle the rate at which mouse reports are sent.
:::

::: warning
Many programs, especially those that implement their own smoothing for scrolling, don't work well when they receive simultaneous vertical and horizontal wheel inputs (e.g. from high resolution drag-scroll using a trackball).
These programs typically implement their smoothing in a way that assumes the user will only scroll in one axis at a time, resulting in slow or jittery motion when trying to scroll at an angle.
This can be addressed by snapping scrolling to one axis at a time.
:::

## Split Keyboard Configuration

The following configuration options are only available when using `SPLIT_POINTING_ENABLE` see [data sync options](split_keyboard#data-sync-options). The rotation and invert `*_RIGHT` options are only used with `POINTING_DEVICE_COMBINED`. If using `POINTING_DEVICE_LEFT` or `POINTING_DEVICE_RIGHT` use the common configuration above to configure your pointing device.

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

::: warning
If there is a `_RIGHT` configuration option or callback, the [common configuration](pointing_device#common-configuration) option will work for the left. For correct left/right detection you should setup a [handedness option](split_keyboard#setting-handedness), `EE_HANDS` is usually a good option for an existing board that doesn't do handedness by hardware.
:::


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

The combined functions below are only available when using `SPLIT_POINTING_ENABLE` and `POINTING_DEVICE_COMBINED`. The 2 callbacks `pointing_device_task_combined_*` replace the single sided equivalents above. See the [combined pointing devices example](pointing_device#combined-pointing-devices)

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

::: tip
The [pointing device modes](#pointing-device-modes) feature implements this along with other popular pointing device features automatically.
:::

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

### Advanced Drag Scroll

Sometimes, like with the Cirque trackpad, you will run into issues where the scrolling may be too fast.

Here is a slightly more advanced example of drag scrolling. You will be able to change the scroll speed based on the values in set in `SCROLL_DIVISOR_H` and `SCROLL_DIVISOR_V`. This bit of code is also set up so that instead of toggling the scrolling state with set_scrolling = !set_scrolling, the set_scrolling variable is set directly to record->event.pressed. This way, the drag scrolling will only be active while the DRAG_SCROLL button is held down.

```c
enum custom_keycodes {
    DRAG_SCROLL = SAFE_RANGE,
};

bool set_scrolling = false;

// Modify these values to adjust the scrolling speed
#define SCROLL_DIVISOR_H 8.0
#define SCROLL_DIVISOR_V 8.0

// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

// Function to handle mouse reports and perform drag scrolling
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // Check if drag scrolling is active
    if (set_scrolling) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_accumulated_h += (float)mouse_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)mouse_report.y / SCROLL_DIVISOR_V;

        // Assign integer parts of accumulated scroll values to the mouse report
        mouse_report.h = (int8_t)scroll_accumulated_h;
        mouse_report.v = (int8_t)scroll_accumulated_v;

        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        // Clear the X and Y values of the mouse report
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}

// Function to handle key events and enable/disable drag scrolling
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DRAG_SCROLL:
            // Toggle set_scrolling when DRAG_SCROLL key is pressed or released
            set_scrolling = record->event.pressed;
            break;
        default:
            break;
    }
    return true;
}

// Function to handle layer changes and disable drag scrolling when not in AUTO_MOUSE_DEFAULT_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    // Disable set_scrolling if the current layer is not the AUTO_MOUSE_DEFAULT_LAYER
    if (get_highest_layer(state) != AUTO_MOUSE_DEFAULT_LAYER) {
        set_scrolling = false;
    }
    return state;
}

```


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
 
::: tip
The messages will be printed out to the `CONSOLE` output. For additional information, refer to [Debugging/Troubleshooting QMK](../faq_debug).
:::


---
# Automatic Mouse Layer {#pointing-device-auto-mouse}

When using a pointing device combined with a keyboard the mouse buttons are often kept on a separate layer from the default keyboard layer, which requires pressing or holding a key to change layers before using the mouse. To make this easier and more efficient an additional pointing device feature may be enabled that will automatically activate a target layer as soon as the pointing device is active _(in motion, mouse button pressed etc.)_ and deactivate the target layer after a set time.   

Additionally if any key that is defined as a mouse key is pressed then the layer will be held as long as the key is pressed and the timer will be reset on key release. When a non-mouse key is pressed then the layer is deactivated early _(with some exceptions see below)_.  Mod, mod tap, and one shot mod keys are ignored _(i.e. don't hold or activate layer but do not deactivate the layer either)_ when sending a modifier keycode _(e.g. hold for mod tap)_ allowing for mod keys to be used with the mouse without activating the target layer when typing.

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
| `AUTO_MOUSE_THRESHOLD`              | (Optional) Amount of mouse movement required to switch layers         | 0 -                  |   _units_   |                 `10 units` |

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
| `set_auto_mouse_timeout(uint16_t timeout)`                 | Change/set the timeout for turing off the layer                                      |                           |    `void`(None) |
| `get_auto_mouse_timeout(void)`                             | Return the current timeout for turing off the layer                                  |                           |      `uint16_t` |
| `set_auto_mouse_debounce(uint16_t timeout)`                | Change/set the debounce for preventing layer activation                              |                           |    `void`(None) |
| `get_auto_mouse_debounce(void)`                            | Return the current debounce for preventing layer activation                          |                           |       `uint8_t` |
| `is_auto_mouse_active(void)`                               | Returns the active state of the auto mouse layer (eg if the layer has been triggered)|                           |          `bool` |
| `get_auto_mouse_key_tracker(void)`                         | Gets the current count for the auto mouse key tracker.                               |                           |        `int8_t` |
| `set_auto_mouse_key_tracker(int8_t key_tracker)`           | Sets/Overrides the current count for the auto mouse key tracker.                     |                           |    `void`(None) |

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

#### Disable auto mouse on certain layers:  

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

### Use custom keys to control auto mouse: 

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

Layer activation can be customized by overwriting the `auto_mouse_activation` function. This function is checked every time `pointing_device_task` is called when inactive and every `AUTO_MOUSE_DEBOUNCE` ms when active, and will evaluate pointing device level conditions that trigger target layer activation. When it returns true, the target layer will be activated barring the usual exceptions _(e.g. delay time has not expired)_.   

By default it will return true if any of the `mouse_report` axes `x`,`y`,`h`,`v` are non zero, or if there is any mouse buttons active in `mouse_report`.
_Note: The Cirque pinnacle track pad already implements a custom activation function that will activate on touchdown as well as movement all of the default conditions, currently this only works for the master side of split keyboards._
 
| Function                                                   | Description                                                                      |     Return type |
| :--------------------------------------------------------- | -------------------------------------------------------------------------------- | --------------: |
| `auto_mouse_activation(report_mouse_t mouse_report)`       | Overwritable function that controls target layer activation (when true)          |          `bool` |

## Auto Mouse for Custom Pointing Device Task

When using a custom pointing device (overwriting `pointing_device_task`) the following code should be somewhere in the `pointing_device_task_*` stack:

```c
bool pointing_device_task(void) {
    //...Custom pointing device task code
    
    // handle automatic mouse layer (needs report_mouse_t as input)
    pointing_device_task_auto_mouse(local_mouse_report);
    
    //...More custom pointing device task code
    
    return pointing_device_send();
}
```

In general the following two functions must be implemented in appropriate locations for auto mouse to function:

| Function                                                       | Description                                                  |           Suggested location |
| -------------------------------------------------------------- | ------------------------------------------------------------ | ---------------------------: |
| `pointing_device_task_auto_mouse(report_mouse_t mouse_report)` | handles target layer activation and is_active status updates | `pointing_device_task` stack |
| `process_auto_mouse(uint16_t keycode, keyrecord_t* record)`    | Keycode processing for auto mouse                            |       `process_record` stack |

---

# Pointing Device Modes {#pointing-device-modes}

Inspired by the work of previous trackball users that added features such as drag scroll, caret scroll, and sniping modes to their keyboards, this framework allows for easy setup and inclusion of different pointing device modes that when active will change the behaviour of a pointing device by taking it's x/y outputs and changing them into something else such as h/v for drag scrolling, key presses such as arrow keys for caret scrolling, and even just adjusting the x/y values before output.  When a pointing device mode is active it accumulates x and y outputs from a pointing device and stores it into internal x & y values, halting normal mouse x and y output (_modes can re-enable and/or modify mouse output_), these internally stored x and y values are then divided by a defined divisor and current device precision value resulting the modified output (_key taps, h/v, modified mouse x/y etc._). The dividing factors can be used to control sensitivity in each mode and precision can be used to control sensitivity on each device as adjusting cpi may not always be desired/possible.

The framework has keycode support for up to **31** *(32 total modes including `PM_NONE`, 30 not including built in modes)* custom modes natively through the `PM_MO(<pointing mode>)` and `PM_TG(<pointing mode>)` keycode macros which act as momentary and toggle keys for `<pointing mode>` respectively, similarly to the layer keys of the same type (up to 256).  2 of the 15 modes are already used by built in modes, however these can easily be overwritten if needed.  There is an additional Null mode `PM_NONE` (_Default pointing device output_) that cannot be overwritten.  More modes beyond this (_mode id's > 31_) can be added but they will require the addition of custom keycodes to activate the modes as the `PM_MO(<pm>)` and `PM_TG(<pm>)` macros only support up to mode id 31.  New custom modes can be added through either adding keycode maps to the `pointing_device_mode_maps` array or through the through user/kb callbacks functions (_see advanced use below_). 

## How To Enable

On a keyboard that has a pointing device (_i.e._ `POINTING_DEVICE_ENABLE` _is defined_) pointing modes can be enabled by defining `POINTING_DEVICE_MODES_ENABLE` in `config.h`, defining new modes, and adding mode change keycodes to the keymap.

```c
// in config.h:
#define POINTING_DEVICE_MODES_ENABLE
```

##  Activating Pointing Device Modes

The first 15 pointing device modes can easily be activated by keypress through adding the following keycode macros to a keymap:

#### Built-in keycodes and Keycode Macros (_for _`PM_NONE`_ and the first 16 modes only_)

| Keycode Macro  | Description                                                                                                                                                                                                     |
| -------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `PM_MO(<pm>)`  | Momentary key for pointing mode `<pm>` (i.e active while key pressed deactivate on release)                                                                                                                     |
| `PM_TG(<pm>)`  | Toggle key for pointing mode `<pm>` (toggle on release, remain until pressed and released again)                                                                                                                |
| `PM_CYCPRE`    | Increase precision on active device by `POINTING_MODES_PRECISION_STEP` will set to `POINTING_MODES_PRECISION_MIN` if `POINTING_MODES_PRECISION_MAX` is exceeded, (_behaviour reverses if shift is held_)        |
| `PM_CYCDEV`    | Cycle through devices controlled by pointing modes in order of increasing device_id (_Requires more than one device to be controlled by pointing modes see Pointing Modes for Multiple Pointing Devices below_) |

::: warning

For pointing device modes above mode id 31 a custom keycode would need to be added unless the mode is being activated through some other means (such as on specific layers see [advanced use](#pointing-modes-advanced-use) below)

:::


### Toggled Pointing Device Modes vs Momentary Pointing Modes

Pointing device modes activated by toggle type functions/macros have their mode id saved until toggled off or a different mode is activated by toggle overwriting the last toggle mode.  When a Momentary type function or key is used while another mode is toggled the toggled mode will be reactivated once the momentary mode is released. Toggling a mode on will overwrite both the saved toggled mode id (_if different than current_) as well as the current mode id while using a momentary type key will only overwrite the current mode.

### Built-in Pointing Device Modes

| Pointing Device Mode      | Alias     | Mode Id | Description                                                                                                                                                 |
| :------------------------ | --------- | :-----: | --------------------------------------------------------------------------------------------------------------------------- |
| `PM_NONE`                 |  _None_   |     0   | Null pointing mode that will will pass through normal x and y output of pointing device (Cannot be overwritten)             |
| `PM_DRAG`                 | `PM_DRG`  |     1   | Change x and y movement of pointing device into h and v axis values  `x->h`  `y->v`                                         |
| `PM_SAFE_RANGE`           |  _None_   |     2   | Start of free mode id range supported by the `PM_MO()` and `PM_TG()` key macros (_default start of mode maps_)              |
| `PM_ADVANCED_RANGE_START` |  _None_   |    32   | Start of mode id range that will require the addition of custom keycode to activate them (_new keycodes, on layers etc._)   |

::: tip

- These modes can all be overwritten (including `PM_NONE` which would impact default cursor movement so care should be taken when doing this and should be generally avoided).
- Mode ids 3-31 are free to be used for custom modes and will be supported by the built in keycode macros `PM_MO(<pm>)` and `PM_TG(<pm>)` (see adding custom modes below)

:::

### Use In A keymap

```c
// in keymap.c

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_TEST] = LAYOUT(
      PM_MO(PM_DRG),  PM_TG(PM_DRG)
      )
  };

```

## Settings

| Define                           | Description                                                                                             |           Range          |     Units    |                  Default |
| -------------------------------- | ------------------------------------------------------------------------------------------------------- | :----------------------: | :----------: | -----------------------: |
| `POINTING_DEVICE_MODES_ENABLE`   | (Required) Enables pointing device pointing device modes feature                                        |            `NA`          |    `None`    |            _Not defined_ |
| `POINTING_MODES_MAP_ENABLE`      | (optional) Enables pointing device map feature for adding custom modes                                  |            `NA`          |    `None`    |            _Not defined_ |
| `POINTING_MODES_8WAY_MAP_ENABLE` | (optional) Changes expected number of keycodes per map to 8                                             |            `NA`          |    `None`    |            _Not defined_ |
| `POINTING_MODES_THRESHOLD`       | (optional) Minimum threshold of input in order to determine a direction for mode maps                   | `1->MOUSE_REPORT_XY_MAX` | `(x\|y)/dot` |                      `0` |
| `POINTING_MODES_DEFAULT_MODE`    | (optional) Default pointing device mode                                                                 |          `0->255`        |    `None`    |                `PM_NONE` |
| `POINTING_MODES_TAP_DELAY`       | (optional) Delay between key presses in `pointing_tap_codes` in ms                                      |          `0->255`        |     `ms`     |         `TAP_CODE_DELAY` |
| `POINTING_MODES_MAP_START`       | (optional) Starting mode id of `pointing_device_mode_maps` for adding modes without maps                |          `0->255`        |    `None`    |          `PM_SAFE_RANGE` |
| `POINTING_MODES_DEFAULT_DIVISOR` | (optional) Default divisor for all modes that do not have a defined divisor                             | `1->MOUSE_REPORT_XY_MAX` |   `Varies`   |                     `32` |
| `POINTING_MODES_DRAG_DIVISOR`    | (optional) Pointing device x/y movement per h/v axis tick in `PM_DRAG` mode                             | `1->MOUSE_REPORT_XY_MAX` | `(x\|y)/dot` |                      `4` |
| `POINTING_MODES_PRECISION_MIN`   | (optional) Minimum precision setting (_will always at least have this value NOT RECOMMENDED TO CHANGE_) | `1->MOUSE_REPORT_XY_MAX` | `(x\|y)/dot` |                      `1` |
| `POINTING_MODES_PRECISION_MAX`   | (optional) Maximum precision setting (_will never go above this value_)                                 | `1->MOUSE_REPORT_XY_MAX` | `(x\|y)/dot` |                      `4` |
| `POINTING_MODES_PRECISION_STEP`  | (optional) Step size of precision adjustments used in `PM_CYCPRE` keycode                               | `1->MOUSE_REPORT_XY_MAX` | `(x\|y)/dot` |                      `2` |
| `POINTING_MODES_HOLD_DECAY_RATE` | (optional) amount residuals are reduced per cycle for `PMO_HOLD` modes (effects held time)              | `0->MOUSE_REPORT_XY_MAX` | `(x\|y)/dot` |                      `2` |

::: warning

- `POINTING_MODES_HOLD_DECAY_RATE` can be set to zero however this will mean last direction key or keys will be held until the direction is changed or mode_id changes
- `MOUSE_REPORT_XY_MAX` will depend on if `MOUSE_EXTENDED_REPORT` is defined; `127` if it is not defined and `32,767` if it is

:::

Speed and sensitivity of any mode will be impacted by the pointing device CPI setting so divisors may need to be adjusted to personal preference and CPI settings typically used (it is possible to have divisors change based on cpi setting if desired).

::: tip

Drag scroll speed will additionally be effected by OS mouse scroll settings, there are usually separate settings for scroll "wheel" and "wheel tilt" which is Vertical and Horizontal scroll respectively (_e.g. lines per scroll in windows_). The `POINTING_MODES_DRAG_DIVISOR` default value of 4 is based on having mouse settings in the OS set to three lines per tick of "mouse wheel" or "wheel tilt" (_Windows Default_).

:::

::: warning

`POINTING_MODES_TAP_DELAY` defaults to `TAP_CODE_DELAY` so if `TAP_CODE_DELAY` is set high it can cause some noticeable latency on maps using tap mode.

:::

## Functions

There are many functions available to control and modify pointing modes details about these functions and data types unique to pointing modes can be found in the relevant sections below. All the functions below will get operate on the current active device (relevant if there is more than one pointing device that is controlled by )

| Function                                        | Description                                                                                                                | Data Type                    | Input Types                  |
| ----------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------- | :--------------------------: | :--------------------------: |
| `pointing_modes_set_mode(mode_id)`              | Set active device's pointing mode to `mode_id`                                                                             | _None_                       | `uint8_t`                    |
| `pointing_modes_get_mode()`                     | Get active device's current mode id                                                                                        | `uint8_t`                    | _None_                       |
| `pointing_modes_toggle_mode(mode_id)`           | Set active device's toggle mode to `mode_id` or `POINTING_MODES_DEFAULT_MODE` if `toggle_id == mode_id`                    | _None_                       | `uint8_t`                    |
| `pointing_modes_get_toggled_mode()`             | Get active device's toggle mode id                                                                                         | _None_                       | `uint8_t`                    |
| `pointing_modes_set_precision(precision)`       | Set active device's precision value to `precision`                                                                         | _None_                       | `mouse_xy_report_t`          |
| `pointing_modes_get_precision()`                | Get active device's precision value                                                                                        | `mouse_xy_report_t`          | _None_                       |
| `pointing_modes_set_residuals(residuals)`       | Set active device's residuals(_accumulated x, y_) to `residuals`                                                           | _None_                       | `pointing_modes_residuals_t` |
| `pointing_modes_get_residuals()`                | Get active device's residuals                                                                                              | `pointing_modes_residuals_t` | _None_                       |
| `pointing_modes_reset()`                        | reset active device to default values and clear residuals                                                                  | _None_                       | _None_                       |
| `pointing_modes_get_divisor()`                  | Get current precision adjusted divisor                                                                                     | `mouse_xy_report_t`          | _None_                       |
| `pointing_modes_get_direction()`                | Get current direction                                                                                                      | `uint8_t`                    | _None_                       |
| `pointing_modes_get_type()`                     | Get current mode type and options                                                                                          | `uint8_t`                    | _None_                       |
| `pointing_modes_update()`                       | Recalculate direction, precision adjusted final divisor, and mode_type                                                     | _None_                       | _None_                       |
| `pointing_modes_apply_divisor(axis)`            | Returns result of applying `divisor` to `residuals` based on `axis` (_[see advanced modes](#Pointing-Modes-Advanced-use)_) | `mouse_xy_report_t`          | `uint8_t`                    |
| `pointing_modes_get_active_device()`            | Returns device id of current active device (_see controlling multiple devices_)                                            | `uint8_t`                    | _None_                       |
| `pointing_modes_set_active_device(device_id)`   | Set active device to `device_id` (_see controlling multiple devices_)                                                      | _None_                       | `uint8_t`                    |

::: tip

`pointing_modes_get_divisor`, `pointing_modes_get_direction`, `pointing_modes_get_mode_type` will not recalculate any of the values to reflect changes in `mode_id` or `residuals` made in the same block of code, `pointing_modes_update` must be used to force this.

:::

## Precision

Precision is an additional value that is stored for each pointing mode device that will be multiplied against the divisor prior to applying it against pointing device output and residuals, this includes `PM_None` which has a default divisor of `1`. Precision is meant to be a separately controlled value to temporarily reduce sensitivity of both standard mouse output and pointing modes.  This can be easily controlled by default using the `PM_CYCPRE` keycode which will cycle through precision values by `POINTING_MODES_PRECISION_STEP` looping back over to the starting value e.g. `1 -> 2 -> 4 -> 1 -> 2` or if shift is held this is reversed `1 -> 4 -> 2 -> 1 -> 4`.

This is useful if changing sensitivity on the pointing device directly is not possible, unreliable, or could cause additional wear of non-volitile memory on the pointing device.

::: tip

- That the maximum value that a divisor can have is 255 even after precision adjustment so it will be clamped to this value if overflow occurs
- The default Maximum precision is `4` so `PM_CYCPRE` will cycle through `1`, `2`, and `4`

:::

## Basic Pointing Modes

There are a couple of ways to add new pointing device modes, using the pointing device mode maps will be covered here under basic use where the other method of using the `pointing_modes_task_*` callbacks to add or modify modes will be covered under advance use.

### Pointing Device Mode Maps

To add pointing device modes that are only using keycode output is accomplished through creating pointing device mode maps, pointing device mode maps support all QMK keycodes similar to encoder maps.

```c
// Pointing Device Mode Maps Format
const uint16_t PROGMEM pointing_modes_maps[][POINTING_MODE_NUM_DIRECTIONS] = {
    [0] = {
                        <first map keycode up>,
        <first map keycode left>,            <first map keycode right>,
                        <first map  keycode down>
    },
    //... all other pointing mode maps ...
    [<number of pointing mode maps - 1>] = {
                        <last map keycode up>,
        <last map keycode left>,             <last mapkeycode right>,
                        <last map keycode down>
    }
}

```

#### Example Mode Maps

```c
// in config.h:
// (Required)
#define POINTING_DEVICE_POINTING_MODES_ENABLE
#define POINTING_MODES_MAP_ENABLE
// (optional)
#define EXTRAKEY_ENABLE
// pointing mode map start is left at default value in this example

// in keymap.c
// required enum to set mode id's
// Note the use of POINTING_MODE_MAP_START here is essential
enum keymap_pointing_mode_ids {
    PM_BROW = POINTING_MODES_MAP_START, // BROWSER TAB Manipulation (POINTING_MODE_MAP_START is required)[mode id  2]
    PM_APP,                             // Open App browsing                                             [mode id  3]
    PM_CARET,                           // Arrow keys/cursor movement                                    [mode id  4]
    PM_VOLUME,                          // Adjust audio volume (requires EXTRAKEY_ENABLE)                [mode id  5]
    PM_HISTORY,                         // Undo/Redo scrolling                                           [mode id  6]
    PM_RGB_MB,                          // Change RGB Mode brightness                                    [mode id  7]
    PM_RGB_HS,                          // Change RGB Hue and Saturation                                 [mode id  8]
    PM_RGB_MSP,                         // Change RGB Mode and Speed                                     [mode id  9]
    PM_GAME                             // WASD game movement mode                                       [mode id 10]
};

// (optional) enum to make tracking mod maps easier(index numbers can be used directly)
// Must be in the same order as the above mode ids
enum keymap_pointing_modes_map_index {
    _PM_BROW,     // first mode map   [index 0]
    _PM_APP,      // second mode map  [index 1]
    _PM_CARET,    // Third mode map   [index 2]
    _PM_VOLUME,   // fourth mode map  [index 3]
    _PM_HISTORY,  // fifth mode map   [index 4]
    _PM_RGB_MB,   // sixth mode map   [index 5]
    _PM_RGB_HS,   // seventh mode map [index 6]
    _PM_RGB_MSP,  // eighth mode map  [index 7]
    _PM_GAME      // ninth mode map   [index 8]
};

// Note POINTING_MODES_NUM_DIRECTIONS is required
const uint16_t PROGMEM pointing_modes_maps[][POINTING_MODES_NUM_DIRECTIONS] = {
    [_PM_BROW] = {
                     KC_NO,
        C(S(KC_TAB)),       C(KC_TAB),
                     KC_NO
    },
    [_PM_APP] = {
                     KC_NO,
        A(S(KC_TAB)),           A(KC_TAB),
                     KC_NO
    },
    [_PM_CARET] = {
                    KC_UP,
        KC_LEFT,                KC_RIGHT,
                    KC_DOWN
    },
    [_PM_VOLUME] = {
                    KC_VOLU,
        KC_NO,                  KC_NO,
                    KC_VOLD
    },
    [_PM_HISTORY] = {
                    KC_NO,
        C(KC_Z),                C(KC_Y),
                    KC_NO
    },
    [_PM_RGB_MB] = {
                    RGB_VAI,
        RGB_RMOD,               RGB_MOD,
                    RGB_VAD
    },
    [_PM_RGB_HS] = {
                    RGB_HUI,
        RGB_SAD,                RGB_SAI,
                    RGB_HUD
    },
    [_PM_RGB_MSP] = {
                    RGB_SPI,
        RGB_RMOD,               RGB_MOD,
                    RGB_SPD
    },
    [_PM_GAME] = {
                    KC_W,
        KC_A,               KC_D,
                    KC_S
    }
};

```
::: warning

use `KC_NO` when no keycode is desired, use of `KC_TRNS` or `_______` is unsupported as these maps do not act like layers _(only one can be active per pointing device at a time)_.

:::

The mode map array starts at index 0 and **must** be in the **same order** as the mode_ids of the maps (i.e `<mode map array index> + POINTING_MODES_MAP_START = <mode map mode_id>`), so use of `POINTING_MODES_MAP_START` is essential. However you can have more modes than you have maps as not all modes will be based on key presses (_such as advanced mode using `pointing_modes_task_*` functions_).

### 8-Way Mode maps

If `POINTING_MODES_8WAY_MAP_ENABLE` is defined then mode maps expect 8 keycodes per map but will allow having unique keycodes for diagonal directions as long as the mode type is set to `PMT_8WAY` (`PMT_4WAY` will still be the default). All maps **must** have 8 keycodes even if it is intended to use only the cardinal directions (`PMT_4WAY` or `PMT_DPAD`), it is recommended to fill unused directions with `KC_NO` as this helps with clarity.

```c
// Pointing Device Mode Maps 8-Way Format:
const uint16_t PROGMEM pointing_modes_maps[][POINTING_MODE_NUM_DIRECTIONS] = {
    [0] = {
        <first map keycode up left>,   <first map keycode up>,    <first map keycode up right>,
        <first map keycode left>,                                 <first map keycode right>,
        <first map keycode down left>, <first map  keycode down>, <first map keycode down right>
    },
    //... all other pointing mode maps ...
    [<number of pointing mode maps - 1>] = {
        <last map keycode up left>,   <last map keycode up>,    <last map keycode up right>,
        <last map keycode left>,                                <last map keycode right>,
        <last map keycode down left>, <last map  keycode down>, <last map keycode down right>
    }
}
```

### Divisors

All newly added modes will use `POINTING_MODE_DEFAULT_DIVISOR` as its divisor unless one is defined for each mode in the `pointing_modes_get_divisor_*` callback functions that have a user and keyboard version.  The callback functions for setting divisors have both the` mode_id` and the `direction` _(see table)_ available to them to allow for easier setting of divisors without needing to call functions to get these values.
The default divisor of `32` will work well for most maps, however this would not be ideal for any mode that requires more sensitivity such as a WASD or Caret (arrow key) mode.

::: warning

Divisors should be set to a value between `1` and `MOUSE_REPORT_XY_MAX` (_`127` by default and `32767` if `MOUSE_EXTENDED_REPORT` is defined_)

:::

#### Callbacks to set pointing device mode divisors

The following callbacks can be used to overwrite built in mode divisors or to set divisors for new modes. The `get_pointing_mode_divisor` stacks works by checking the functions until a non zero value is reached in order of `user`->`kb`->`built in`->`default_value`.  Returning a divisor of `0` will allow processing to continue on to the next stage, However this means that if any of the get divisor callback functions return a default value other than 0 then that will overwrite all subsequent divisors(such as built in modes and divisors from the keyboard).  These functions allows for overriding and modifying built in divisors by users/keymaps and keyboards and overriding keyboard level divisors by users/keymaps so it is possible to give built in modes the same level of divisor customisation as new custom modes.

| Callback                                                                                | Description                                                                                                       |
| --------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------- |
| `mouse_xy_report_t pointing_modes_get_divisor_kb(uint8_t mode_id, uint8_t direction)`   | Keyboard level callback for setting divisor based on `mode_id` and `direction`                                    |
| `mouse_xy_report_t pointing_modes_get_divisor_user(uint8_t mode_id, uint8_t direction)` | Keymap/user level callback for setting divisor  based on `mode_id` and `direction`                                |


#### Directions table

Directions could be used to set the divisor based on the direction (`direction` is updated before the `divisor` are updated). Directions are represented as labels on specific values of a 8-bit unsigned integer(_but only 4 bits are used_).  The following table outlines the direction labels and the values that they represent.


| Direction code | Value | Value Hex | Value Binary | Description                                                                                           |
| :------------- | :---: | :-------: | :----------: | ----------------------------------------------------------------------------------------------------- |
| `PMD_None`     |     0 |   0x00    |     0000     | Both y and x are 0 or below `POINTING_MODES_THRESHOLD` if it is defined                               |
| `PMD_DOWN`     |     1 |   0x01    |     0001     | Stored y axis is positive and 2*\|y\| >= \|x\|                                                        |
| `PMD_UP`       |     2 |   0x02    |     0010     | Stored y axis is negative and 2*\|y\| >= \|x\|                                                        |
| `PMD_LEFT`     |     4 |   0x04    |     0100     | Stored x axis is negative and 2*\|x\| >= \|y\|                                                        |
| `PMD_RIGHT`    |     8 |   0x08    |     1000     | Stored x axis is positive and 2*\|x\| >= \|y\|                                                        |
| `PMD_DNLT`     |     5 |   0x05    |     0101     | Both `PMD_DOWN` and `PMD_LEFT` conditions are met and mode type is `PMT_DPAD` or `PMT_8WAY`           |
| `PMD_UPLT`     |     6 |   0x05    |     0110     | Both `PMD_UP` and `PMD_LEFT` conditions are met and mode type is `PMT_DPAD` or `PMT_8WAY`             |
| `PMD_DNRT`     |     9 |   0x09    |     1001     | Both `PMD_DOWN` and `PMD_RIGHT` conditions are met and mode type is `PMT_DPAD` or `PMT_8WAY`          |
| `PMD_UPRT`     |    10 |   0x0A    |     1010     | Both `PMD_UP` and `PMD_RIGHT` conditions are met and mode type is `PMT_DPAD` or `PMT_8WAY`            |
| `PMD_VERT`     |     3 |   0x03    |     0011     | For filtering direction to only vertical component (up or down) using `direction & PMD_VERT`          |
| `PMD_HORI`     |    12 |   0x0C    |     1100     | For filtering direction to only horizontal component (left or right) using `direction & PMD_HORI`     |

::: tip

Diagonal directions are only relevant for the `PMT_8WAY` and `PMT_DPAD` mode types (_[see Mode Types and Mode options](#mode-types-and-mode-options)_)

:::

#### Example code of assigning divisors for new modes

```c
// added to keymap.c
// assuming poinding device enum and maps from example above
mouse_xy_report_t pointing_modes_get_divisor_user(uint8_t mode_id, uint8_t direction) {
    switch(mode_id) {

        case PM_HALF_V:
            // half speed for vertical axis
            return direction & PMD_VERT ? 2 : 1;

        case PM_HALF_H:
            // half speed for horizontal axis
            return direction & PMD_HORI ? 2 : 1;

        case PM_ALL_DIFF:
            // example of unique divisor for each direction in 4WAY mode (not recommended just an example of what can be done)
            switch(direction) {
                case PMD_DOWN:
                    return 32;
                case PMD_UP:
                    return 64;
                case PMD_LEFT:
                    return 16;
                case PMD_RIGHT:
                    return 128;
            }

        case PM_SLOW:
            return 64;
        case PM_GAME:
            return 16;
    }

    return 0; // returning 0 to let processing of divisors continue
}
```

### Mode Types and Mode Options {#mode-types-and-mode-options}

Pointing modes can be further modified by changing the mode type as well as mode options.  Some options will obviously only impact maps as they change how keypresses are handled, but options or types that impact directions affect all modes even modes that are not using a mode map such as `PM_NONE`, `PM_DRG`, and any custom modes that do not have a map associated with them.  A mode can have **only one Mode Type** but can have **multiple Mode Options**. These are set for a given mode based on the callback functions for setting both the mode type and options using the bitwise or (`|`) operator to combine them (_e.g. `PMT_DPAD | PMO_XINV | PMO_HOLD`_).

#### Callback Functions for Setting Mode Type
| Callback                                                  | Description                                                                                                       |
| --------------------------------------------------------- | ----------------------------------------------------------------------------------------------------------------- |
| `uint8_t pointing_modes_get_type_kb(uint8_t mode_id)`     | Keyboard level callback for setting mode type and mode options based on `mode_id`                                 |
| `uint8_t pointing_modes_get_type_user(uint8_t mode_id)`   | Keymap/user level callback for setting mode type and mode options based on `mode_id`                              |

#### Mode Type and options Tables

Mode Types and options are represented by labels over values of a 8-bit unsigned integer with the bottom 4 bits storing the type and the top 4 bits storing the options.

| Mode Type    | Value Hex | Value Binary | Description                                                                                                                                 |
| :----------- | :-------: | :----------: | :------------------------------------------------------------------------------------------------------------------------------------------ |
| `PMT_4WAY`   |    0x00   |   00000000   | (Default) Restricts `direction` to cardinal directions (`PMD_DOWN`, `PMD_UP`, `PMD_LEFT`, or `PMD_RIGHT`) with one keycode per direction    |
| `PMT_HORI`   |    0x01   |   00000001   | Disables pointing device y axis output                                                                                                      |
| `PMT_VERT`   |    0x02   |   00000010   | Disables pointing device x axis output                                                                                                      |
| `PMT_8WAY`   |    0x03   |   00000011   | Allows for `direction` to have both cardinal and diagonal values and will output a single keycode per direction.                            |
| `PMT_DPAD`   |    0x04   |   00000100   | Allows for horizontal and vertical keys to be output simultaneously on diagonal directions (`PMD_DNLT`, `PMD_UPLT`, `PMD_DNRT`, `PMD_UPRT`) |
| `PMT_MODES`  |    0x0F   |   00001111   | Bit mask to allow extraction of mode types from output of `pointing_mode_get_type()` using bitwise operations e.g. `mode_type & PMT_MODES`  |

:::tip

The `PMT_4WAY` mode will additionally favour staying on the current axis i.e. if last input was horizontal will be less sensitive to vertical inputs until a large enough vertical input is given (_this effect increases with larger divisors/precision_)***

:::

| Mode Type    | Value Hex | Value Binary | Description                                                                                                                                 |
| :----------- | :-------: | :----------: | :------------------------------------------------------------------------------------------------------------------------------------------ |
| `PMO_TAP`    |    0x00   |   00000000   | (Default) Will tap direction keycode a number of times equal to the multiple of the divisor in that direction                               |
| `PMO_HOLD`   |    0x10   |   00010000   | Will press and hold pressed key for a length of time depending on size of the input (_can be interrupted/extended by further inputs_)       |
| `PMO_XINV`   |    0x20   |   00100000   | Inverts the Horizontal (**x** axis of the pointing device for a given mode                                                                  |
| `PMO_YINV`   |    0x40   |   01000000   | Inverts the Vertical (**y**) axis of the pointing device for a given mode                                                                   |
| `PMO_OPTS`   |    0xF0   |   11110000   | Bit mask to allow extraction of mode options from output of `pointing_mode_get_type()` using bitwise operations e.g. `mode_type & PMT_OPTS` |


#### Example of Setting Mode types and options

```c
// in keymap.c
uint8_t pointing_modes_get_type_user(uint8_t mode_id) {
    switch(mode_id) {
        // Default cursor output
        case PM_NONE:
            return PMO_YINV;
        // Drag scroll
        case PM_DRG:
            return PMO_YINV;
        // Browser Tabs
        case PM_BROW:
            return PMT_HORI | PMO_HOLD;
        // Arrow key output
        case PM_CARET:
            return PMO_TAP;
        // Volume output
        case PM_VOL:
            return PMT_VERT | PMO_YINV | PMO_HOLD;
        // History scrolling (UNDO/REDO)
        case PM_HIST:
            return PMT_HORI | PMO_TAP;
        // Windows APP scrolling
        case PM_APP:
            return PMT_HORI;
        // WASD output
        case PM_GAME:
            return PMT_DPAD | PMO_HOLD;
    }
    return PMT_4WAY; // regular default Passing anything else will overwrite all built in modes
}

```

### Creating Custom pointing modes keycodes

There are built in functions to simplify the creation of custom keycodes and it is generally recommended to use these as they handle some edge cases to ensure consistent behaviour.

| Function                                                    | Description                                                               | Return type |
| :---------------------------------------------------------- | :------------------------------------------------------------------------ | :---------: |
| `pointing_modes_key_momentary(mode_id, pressed)`            | Momentary change of active device mode id to `mode_id` while key is held  |   _None_    |
| `pointing_modes_key_toggle(mode_id, pressed)`               | Toggle active device pointing mode `mode_id` on key release               |   _None_    |
| `pointing_modes_key_set_device(mode_id, pressed)`           | Set active device to `device_id` on key release                           |   _None_    |
| `pointing_modes_key_set_precision(precision, pressed)`      | Set active device precision to `precision` on key release                 |   _None_    |

::: warning

All of these functions must be used in `process_record_*` functions and `record->event.pressed` should be passed for `pressed`.

:::

These can be used to activate pointing device modes outside of the range of the built in keycodes as well as adding custom features to a mode that activate on key press such as registering a keycode and holding it until key release (_see code examples below_).

#### Example code for adding an open app navigation mode outside of basic mode range

```c
// in keymap.c

enum my_pointing_modes {
    // place Pointing device mode id outside of basic range as it will not use PM_MO or PM_TG macros
    PM_TEST = PM_SAFE_RANGE  // Control alt tabbing through open applications [mode id: 16]
};

enum my_custom_keycodes {
    KC_MO_TEST = SAFE_RANGE,
    KC_TG_TEST
};

bool process_record_user(uint16_t keycode, keyrecord_t* record) {

    switch(keycode) {
        case KC_MO_TEST:
            pointing_mode_key_momentary(PM_TEST, bool pressed);
            return false; // stop key record processing
        case KC_TG_TEST:
            pointing_mode_key_toggle(PM_TEST, bool pressed);
            return false; // stop key record processing
    }
    return true; // allow normal key record processing
}
```

The above code will create an Application switching pointing mode that should work on windows and linux allowing for navigation through currently open applications having the alt key held will keep the application/window UI active as long as the `KC_MO_APP` key is held (there is a slightly more advanced version of this in a below example that delays registering the alt key until enough scroll has accumulated).


## Pointing Modes Advanced use {#pointing-modes-advanced-use}

There are a number of functions allowing access and control of different aspects of the pointing modes feature most of these are intended for more advanced control such as custom keycodes to activate pointing modes or pointing modes that are manipulating something other than key presses (pointing device data, internal keyboard variables, etc.).

#### Axes table for `pointing_modes_apply_divisor` function

| Divisor method code | Value | Description                                                                                                                     |
| :------------------ | :---: | ------------------------------------------------------------------------------------------------------------------------------- |
| `PM_X_AXIS`         |     0 | Return quotient of `residuals.x` and `divisor` and update `residuals.x`                                                         |
| `PM_Y_AXIS`         |     1 | Return quotient of `residuals.y` and `divisor` and update `residuals.y`                                                         |
| `PM_H_AXIS`         |     2 | Return quotient of `residuals.x` and `divisor` and clamp to `mouse_hv_report_t` range and update `residuals.x`                  |
| `PM_V_AXIS`         |     3 | Return quotient of `residuals.y` and `divisor` and clamp to `mouse_hv_report_t` range and update `residuals.y`                  |
| `PM_X_KEY`          |     4 | return `-1`, `0`, or `1` if `residuals.x` is positive, zero or negative and larger than divisor and update `residuals.x`        |
| `PM_Y_KEY`          |     5 | return `-1`, `0`, or `1` if `residuals.y` is positive, zero or negative and larger than divisor and update `residuals.y`        |
| `PM_XY_KEY`         |     6 | return sum of magnitude(_absolute value_) of `PM_X_KEY` and `PM_Y_KEY` functions, updating both `residual.x` and `residual.y`   |

This function allows simple application of a divisor to a given axis returning the relevant result and updating the residuals.

### `pointing_modes_residuals_t` structure

The current pointing mode on the active device is controlled by tracking several internal variables and the `pointing_mode_residual_t` data structure these residuals contain accumulated pointing device output (_this accumulation ensures smooth movement for any divisor_).  A few other variables are tracked outside of the pointing mode structure and there are specialised functions to access/modify them. all of these variables are cleared on mode changes/resets (_mode id will be set to tg_mode_id_).  These variables will also be available when using the `pointing_modes_task_*` functions.

| Variable              | Description                               | Data type           | Functions to access/modify outside of mode processing                  |
| :-------------------- | :---------------------------------------- | :-----------------: | :--------------------------------------------------------------------- |
| `residuals.x`         | Stored horizontal axis value              | `mouse_xy_report_t` | `pointing_modes_get_residuals`, `pointing_modes_set_residuals`         |
| `residuals.y`         | Stored vertical axis value                | `mouse_xy_report_t` | `pointing_modes_get_residuals`, `pointing_modes_set_residuals`         |

### Other Internally tracked Variables requiring functions to access and Modify

| Variable        | Description                                                                   | Data type | Access/Control Functions                                                                                                  |
| :-------------- | :---------------------------------------------------------------------------- | :-----------------: | :------------------------------------------------------------------------------------------------------------------------ |
| `mode_id`       | Mode id of active device                                                      |       `uint8_t`     | `pointing_modes_get_mode`, `pointing_modes_set_mode`                                                                      |
| `toggle_id`     | Toggle id of last active toggle mode on active device                         |       `uint8_t`     | `pointing_modes_toggle_mode`, `pointing_modes_get_toggled_mode`                                                           |
| `active_device` | Active device index [see here](#Pointing-Modes-for-Multiple-Pointing-Devices) |       `uint8_t`     | `pointing_modes_get_active_device`, `pointing_modes_set_active_device`, keycode:`PM_CYCDEV`                               |
| `divisor`       | Divisor of current mode id and direction                                      | `mouse_xy_report_t` | `pointing_modes_get_divisor`, `pointing_modes_get_divisor_user`, `pointing_modes_get_divisor_kb`, `pointing_modes_update` |
| `precision`     | Active device sensitivity setting                                             | `mouse_xy_report_t` | `pointing_modes_get_precision`, `pointing_modes_set_precision`, keycode:`PM_CYCPRE`                                       |
| `direction`     | Direction based on stored x and y values                                      |       `uint8_t`     | `pointing_modes_get_direction`, `pointing_modes_update`                                                                   |
| `mode_type`     | Mode type and options based on mode id                                        |       `uint8_t`     | `pointing_modes_get_type`, `pointing_modes_get_type_user`, `pointing_modes_get_type_kb`, `pointing_modes_update`          |

#### Code example for changing modes on layer changes (will keep current toggle mode id)

```c
// in keymap.c
// assuming enum and Layout for layers are already defined
layer_state_t layer_state_set_user(layer_state_t state) {
    // reset mode id to toggle_id on layer change
    pointing_modes_reset();
    switch(get_highest_layer(state)) {
        case _RAISE:
            pointing_modes_set_mode(PM_NONE);
            break;
        case _LOWER:
            pointing_modes_set_mode(PM_DRAG);
            break;
    }
    return state;
}
```

The above example will maintain the current toggle mode id and set layer pointing modes as temporary modes on top of it so that when changing to a different layer the current toggle mode will be re asserted.

::: tip

The above approach will also cause the pointing mode of the active device to be reset on every layer change.

:::

#### Example that treats toggle modes as a "default" mode that changes depending on layer

```c
// in keymap.c
// assuming enum and Layout for layers are already defined
layer_state_t layer_state_set_user(layer_state_t state) {
    switch(get_highest_layer(state)) {
        case _RAISE:
            pointing_modes_toggle_mode(PM_NONE);
            break;
        case _LOWER:
            pointing_modes_toggle_mode(PM_DRAG);
            break;
        default:
            // disable toggled pointing mode if
            switch(pointing_modes_get_toggled_mode()) {
                case PM_DRAG:
                    pointing_mode_toggle_mode(POINTING_MODE_DEFAULT);
            }
    }
    return state;
}
```
This approach will overwrite any toggled modes upon a layer switch but will allow for momentary mode switching while on other layers returning to the current toggled mode for that layer once a momentary mode is released. This approach works best when keys primarily are used for momentary modes and layers trigger changes to toggled modes.


### Additional ways to create custom modes

Creating pointing device modes outside of pointing mode maps requires using the mode processing callbacks, Which give easy access to both the `mouse_report` and `residuals`.

::: tip

At this point in the process `mouse_report` x, and y have already been transferred to the `residuals` and must be added back if cursor movement is desired

:::

#### Callbacks for adding custom modes

These callbacks work similar to keycode processing callbacks in that returning false will prevent further processing of the pointing device mode.  The processing order of pointing device modes is: `user`->`kb`->`built in`->`maps`.

| Callback                                                                                            | Description                                                 |
| :-------------------------------------------------------------------------------------------------- | ----------------------------------------------------------- |
| `bool pointing_modes_task_kb(report_mouse_t* mouse_report, pointing_modes_residuals_t residuals)`   | keyboard level callback for adding pointing device modes    |
| `bool pointing_modes_task_user(report_mouse_t* mouse_report, pointing_modes_residuals_t residuals)` | user/keymap level callback for adding pointing device modes |


#### Creating modes using callback functions

```c
// in <keyboard>.h or <keyboard>.c
// add custom pointing device mode
enum my_kb_pointing_modes {
    // start at the end of basic range
    PM_CUR_NOPRE = PM_ADVANCED_RANGE_START,  // [mode id: 34]
    PM_CUR_ACCEL,                             // [mode id: 35]
    // good practice to allow users to expand further
    KB_PM_SAFE_RANGE
};

// add custom keycodes
enum my_kb_keycodes {
    // start of keyboard custom keycode range
    KB_MO_CUR_NOPRE = QK_KB,
    KB_TG_CUR_ACCEL
};

#define CONSTRAIN_XY(val) (((val) > (XY_REPORT_MAX)) ? (XY_REPORT_MAX) : ((val) < (XY_REPORT_MIN)) ? (XY_REPORT_MIN) : (val))


// in <keyboard>.c

// define keybaord level divisors
mouse_xy_report_t pointing_modes_get_divisor_kb(uint8_t mode_id, uint8_t direction) {
    switch(mode_id) {
        case PM_CUR_NOPRE:
            return 1;
        case PM_CUR_ACCEL:
            return 10;
    }
    return 0; // continue processing
}

bool pointing_modes_task_kb(report_mouse_t* mouse_report, pointing_modes_residuals_t* residuals) {
    // setting up on needed variable for APP scrolling mode
    static bool alt_registered;
    switch(pointing_modes_get_mode()){
        // cursor movement unaffected by precision
        case PM_CUR_NOPRE:
            mouse_report->x += residuals->x;
            mouse_report->y += residuals->y;
            return false;  // stop pointing mode processing

        // Manipulating pointing_mode & mouse_report (cursor speed boost mode example)
        case PM_CUR_ACCEL:
            // reset mouse_report note that mouse_report is a pointer in this function's context
            *mouse_report = pointing_device_get_report();
            // set up temp variable and context
            {
                // add linear acceleration to x
                uint8_t mode_type = pointing_modes_get_type();
                if (mode_type & PMO_XINV) {                                             // note checking for inversion options may not be needed this just makes the function more general
                    mouse_report->x = CONSTRAIN_XY(mouse_report->x - pointing_modes_apply_divisor(PM_X_AXIS));
                } else {
                    mouse_report->x = CONSTRAIN_XY(mouse_report->x + pointing_modes_apply_divisor(PM_X_AXIS));
                }
                // add linear acceleration to y
                if (mode_type & PMO_YINV) {                                             // note checking for inversion options may not be needed this just makes the function more general
                    mouse_report->x = CONSTRAIN_XY(mouse_report->y - pointing_modes_apply_divisor(PM_Y_AXIS));
                } else {
                    mouse_report->x = CONSTRAIN_XY(mouse_report->y + pointing_modes_apply_divisor(PM_Y_AXIS));
                }
            }
            return false; // stop pointing mode processing
    }
    return true;
}

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    switch(keycode) {
        case KB_MO_CUR_NOPRE:
            pointing_mode_key_momentary(PM_CUR_NOPRE, record);
            return true; // continue key record processing

        case KB_TG_CUR_ACCEL:
            pointing_mode_key_toggle(PM_CUR_ACCEL, record);
            return true; // continue key record processing
    }
    return true;
}

```

### Example combining mode maps with the `pointing_modes_task_*` functions for smoother app scrolling
```c
// in keymap.c
// add custom pointing device mode
enum my_kb_pointing_modes {
    // set up map id for smoother app scrolling
    PM_APP = POINTING_MODES_MAP_START        // [mode id: 02 (Default can be chenged)]
};

// add map index label
enum my_kb_pointing_mode_maps {
    _PM_APP // [index: 0]
};

mouse_xy_report_t pointing_modes_get_divisor_user(uint8_t mode_id, uint8_t direction) {
    switch(mode_id) {
        case PM_APP:
            return 64;
    }
    return 0; // continue processing
}

uint8_t pointing_modes_get_type_user(uint8_t mode_id) {
    switch(mode_id) {
        case PM_APP:
            return PMT_HORI;
    }
    return PMT_4WAY; // continue processing
}

bool pointing_modes_task_kb(report_mouse_t* mouse_report, pointing_modes_residuals_t* residuals) {
    // setting up on needed variable for APP scrolling mode
    static bool alt_registered;
    switch(pointing_modes_get_mode()){
        case PM_APP:
            // add alt key if not already registed
            if (!alt_registered && (abs(residuals->x) >= pointing_modes_get_divisor())) {
                add_mods(MOD_BIT(KC_LALT));
                alt_registered = true;
            }
            return true; // continue processing
        default:
            // remove alt key as soon as the mode changes
            if(alt_registered) {
                unregister_mods(MOD_BIT(KC_LALT));
                alt_registered = false;
            }
    }
}

// with the alt key added during pointing_modes_task_* this will keep the app switching menu open as long as the modes are on
const uint16_t PROGMEM pointing_modes_maps[][POINTING_MODES_NUM_DIRECTIONS] = {
    [_PM_APP] = {
                KC_NO,
        S(KC_TAB),   KC_TAB,
                KC_NO
    }
};
```

## Pointing Modes for Multiple Pointing Devices

Pointing modes supports multiple pointing devices allowing for either control of one pointing device at a time or simultaneous control of multiple pointing devices. This supports left and right devices natively when both `SPLIT_POINTING_ENABLE` and `POINTING_DEVICE_COMBINED` as either single or simultaneous control (depending if `POINTING_MODE_SINGLE_CONTROL` is defined), However while controlling 3 or more pointing devices is possible this will need to be handled by using a custom `pointing_device_task` function.

#### Multiple device Settings

| Define                                | Description all (optional)                                                                                     | Data type |  Range  |       Default |
| ------------------------------------- | -------------------------------------------------------------------------------------------------------------- | :-------: | :-----: | ------------: |
| `POINTING_MODES_NUM_DEVICES`          | (optional) Number of devices available for control (intended for when using more than 2 pointing devices)      | `uint8_t` | `1-255` |    `1` or `2` |
| `POINTING_MODES_SINGLE_CONTROL`       | (optional) Force control of only one device at a time (but the active device can be switched)                  |   _None_  |  _None_ | _Not defined_ |
| `POINTING_MODES_DEFAULT_DEVICE_ID`    | (optional) Default device id controlled (`PM_RIGHT_DEVICE`, `PM_LEFT_DEVICE` depending on `MASTER_RIGHT`)      | `uint8_t` | `1-255` |           `0` |

::: warning

`POINTING_MODE_NUM_DEVICES` defaults to 2 if both `SPLIT_POINTING_ENABLE` and `POINTING_DEVICE_COMBINED` are defined.

:::

#### Default device id defines

| Device code       | Value | Description                                             |
| :---------------- | ----- | ------------------------------------------------------- |
| `PM_RIGHT_DEVICE` |  `0`  | Device index of right side pointing device              |
| `PM_LEFT_DEVICE`  |  `1`  | Device index of left side pointing device               |

::: tip

Although up to `255` device id's are technically supported (ignoring hardware limitations) only two are given labels by default as that covers most common configurations.

:::

#### Multiple Device keycodes

| Keycode                | Alias       | Description                                                                                                                                          |
| :--------------------- | ----------- | ---------------------------------------------------------------------------------------------------------------------------------------------------- |
| `QK_PM_CYCLE_DEVICES`  | `PM_CYCDEV` | Cycles the active device through available devices on each key release (e.g. toggling between `PM_RIGHT_DEVICE` and `PM_LEFT_DEVICE` with 2 devices) |

#### Multiple device functions

These functions control and query the current active device id.

| Function                                           | Description                                                        | Return type |
| :------------------------------------------------- | ------------------------------------------------------------------ | :---------: |
| `pointing_modes_get_active_device(void)`           | Return active device index                                         |  `uint8_t`  |
| `pointing_modes_set_active_device(uint8_t device)` | Set active device index                                            |    `void`   |

### Simultaneous device control

When `POINTING_MODES_SINGLE_CONTROL` is not defined and `POINTING_MODES_NUM_DEVICES > 1` simultaneous control of multiple devices is enabled, which is the default behaviour when `SPLIT_POINTING_ENABLE` and `POINTING_DEVICE_COMBINED` are both defined.  This will cause separate tracking of pointing modes data (`mode_id`, `toggle_id`, `residuals`, held keys, and `precision`) for each device allowing all to have different active modes simultaneously.  All functions under this scheme require changing the active device to the desired device before calling any pointing modes function and the functions will only target that device (_this also affects built-in keycodes e.g. PM_CYCPRE_).  Once set the active device will remain so until changed or the keyboard is powered down so keypresses or functions elsewhere in code will impact the current active device only.  Changing the active device is made easier through use of the above keycodes (`PMR_CYCDEV`) so the active device can be set with a keypress and then subsequent `PM_MO` or `PM_TG` keypress will affect the newly active device.

The default behaviour when using `SPLIT_POINTING_ENABLE` and `POINTING_DEVICE_COMBINED` are both defined will assign `left_mouse_report` to the `PM_LEFT_DEVICE` index and `right_mouse_report` to the `PM_RIGHT_DEVICE` and will process both devices pointing modes every /time `pointing_device_task` is called. Simply setting the active device and changing the mode id should enable using modes on either device.

The code below is an example of how a hypothetical three device scenario using PMW33XX devices as the driver supports multiple devices per mcu.


#### Example of setting up 3 PMW33XX based devices for pointing modes (and just general mouse reports)
```c
// in keyboard config.h
#define POINTING_DEVICE_MODES_ENABLE
#define POINTING_MODES_NUM_DEVICES 3

//if adding custom maps
#define POINTING_MODES_MAP_ENABLE

#define PMW33XX_CS_PINS { <pd_pin_1>, <pd_pin_2>, <pd_pin_3> }

// in <keyboard>.h
enum my_pointing_device_ids{
    PD_LEFT  == 0, // index 0
    PD_CENTRE,     // index 1
    PD_RIGHT       // index 2
};

// in <keyboard>.c
#ifdef POINTING_DEVICE_ENABLE
// constrain to mouse movement
#    define constrain_hid_xy(amt) ((amt) < XY_REPORT_MIN ? XY_REPORT_MIN : ((amt) > XY_REPORT_MAX ? XY_REPORT_MAX : (amt)))
void pointing_device_init_kb(void) {
    // initialize non-default devices i.e. device id > 0
    pmw33xx_init(PD_CENTRE);
    pmw33xx_init(PD_RIGHT);
    pmw33xx_set_cpi_all_sensors(800); // set all sensors to 800 cpi
    // set default pointing modes for devices
    pointing_mode_set_active_device(PD_LEFT);
    pointing_mode_set_mode(PM_DRAG);

    pointing_mode_set_active_device(PD_CENTRE);
    pointing_mode_set_mode(PM_CARET);
    // PD_RIGHT is left as POINTING_MODE_DEFAULT which is PM_NONE if undefined
    // reset default device ID
    pointing_mode_set_active_device(POINTING_MODE_DEFAULT_DEVICE_ID);

    pointing_device_init_user();
}

// Contains report from sensor #0 already, need to apply modes and merge in from other sensors
report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    // start at highest device id
    uint8_t device = PD_RIGHT;
    // store active device id
    uint8_t stored_device = pointing_modes_get_active_device();
    do {
        pmw33xx_report_t device_report  = pmw33xx_read_burst(device);
        if (!device_report.motion.b.is_lifted && device_report.motion.b.is_motion) {
            // create temporary mouse_report
            report_mouse_t device_mouse_report = {0};
            device_mouse_report.x = constrain_hid_xy(device_report.delta_x);
            device_mouse_report.y = constrain_hid_xy(device_report.delta_y);
            // set pointing mode device and process pointing mode for that device
            pointing_modes_set_active_device(device);
            device_mouse_report = pointing_modes_device_task(device_mouse_report);
            // merge modified mouse report
            mouse_report.x = constrain_hid_xy(mouse_report.x + device_mouse_report.x);
            mouse_report.y = constrain_hid_xy(mouse_report.y + device_mouse_report.y);
        }
    } while(device--);
    // reset device id
    pointing_modes_set_active_device(stored_device);
    return pointing_device_task_user(mouse_report);
}
#endif
```

### Single Device Control of Multiple Devices

When `POINTING_MODES_NUM_DEVICES > 1` and `POINTING_MODES_SINGLE_CONTROL` is defined, then only a single set of pointing modes data (`mode_id`, `toggle_id`, `residuals`, held keys, and `precision`) is tracked, but it is possible to switch which device is currently has the mode id active through use of `pointing_mode_set_active_device`  This handles two pointing devices _(left and right)_ natively when `SPLIT_POINTING_ENABLE` and `POINTING_DEVICE_COMBINED` are both defined but for more than two pointing devices custom `pointing_device_task` code will be needed.

::: tip

The `*_pointing_mode_device` functions do not change any internal behaviour when pointing modes is in single device mode, instead these functions are intended to simply track the controlled pointing device (this is handled automatically for two devices when `SPLIT_POINTING_ENABLE` and `POINTING_DEVICE_COMBINED` are active)

:::
