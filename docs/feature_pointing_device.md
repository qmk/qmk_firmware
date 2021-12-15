# Pointing Device :id=pointing-device

Pointing Device is a generic name for a feature intended to be generic: moving the system pointer around.  There are certainly other options for it - like mousekeys - but this aims to be easily modifiable and hardware driven.  You can implement custom keys to control functionality, or you can gather information from other peripherals and insert it directly here - let QMK handle the processing for you.

To enable Pointing Device, uncomment the following line in your rules.mk:

```make
POINTING_DEVICE_ENABLE = yes
```

## Sensor Drivers

There are a number of sensors that are supported by default. Note that only one sensor can be enabled by `POINTING_DEVICE_DRIVER` at a time.  If you need to enable more than one sensor, then you need to implement it manually.

### ADNS 5050 Sensor

To use the ADNS 5050 sensor, add this to your `rules.mk`

```make
POINTING_DEVICE_DRIVER = adns5050
```

The ADNS 5050 sensor uses a serial type protocol for communication, and requires an additional light source. 

| Setting            | Description                                                         |
|--------------------|---------------------------------------------------------------------|
|`ADNS5050_SCLK_PIN` | (Required) The pin connected to the clock pin of the sensor.        |
|`ADNS5050_SDIO_PIN` | (Required) The pin connected to the data pin of the sensor.         |
|`ADNS5050_CS_PIN`   | (Required) The pin connected to the cable select pin of the sensor. |

The CPI range is 125-1375, in increments of 125. Defaults to 500 CPI.

### ADSN 9800 Sensor

To use the ADNS 9800 sensor, add this to your `rules.mk`

```make
POINTING_DEVICE_DRIVER = adns9800
```

The ADNS 9800 is an SPI driven optical sensor, that uses laser output for surface tracking. 

| Setting                | Description                                                            | Default       |
|------------------------|------------------------------------------------------------------------|---------------|
|`ADNS9800_CLOCK_SPEED`  | (Optional) Sets the clock speed that the sensor runs at.               | `2000000`     |
|`ADNS9800_SPI_LSBFIRST` | (Optional) Sets the Least/Most Significant Byte First setting for SPI. | `false`       |
|`ADNS9800_SPI_MODE`     | (Optional) Sets the SPI Mode for the sensor.                           | `3`           |
|`ADNS9800_SPI_DIVISOR`  | (Optional) Sets the SPI Divisor used for SPI communication.            | _varies_      |
|`ADNS9800_CS_PIN`       | (Required) Sets the Cable Select pin connected to the sensor.          | _not defined_ |


The CPI range is 800-8200, in increments of 200. Defaults to 1800 CPI. 

### Analog Joystick

To use an analog joystick to control the pointer, add this to your `rules.mk`

```make
POINTING_DEVICE_DRIVER = analog_joystick
```

The Analog Joystick is an analog (ADC) driven sensor.  There are a variety of joysticks that you can use for this.

| Setting                          | Description                                                                | Default       |
|----------------------------------|----------------------------------------------------------------------------|---------------|
|`ANALOG_JOYSTICK_X_AXIS_PIN`      | (Required) The pin used for the vertical/X axis.                           | _not defined_ |
|`ANALOG_JOYSTICK_Y_AXIS_PIN`      | (Required) The pin used for the horizontal/Y axis.                         | _not defined_ |
|`ANALOG_JOYSTICK_AXIS_MIN`        | (Optional) Sets the lower range to be considered movement.                 | `0`           |
|`ANALOG_JOYSTICK_AXIS_MAX`        | (Optional) Sets the upper range to be considered movement.                 | `1023`        |
|`ANALOG_JOYSTICK_SPEED_REGULATOR` | (Optional) The divisor used to slow down movement. (lower makes it faster) | `20`          |
|`ANALOG_JOYSTICK_READ_INTERVAL`   | (Optional) The interval in milliseconds between reads.                     | `10`          |
|`ANALOG_JOYSTICK_SPEED_MAX`       | (Optional) The maxiumum value used for motion.                             | `2`           |
|`ANALOG_JOYSTICK_CLICK_PIN`       | (Optional) The pin wired up to the press switch of the analog stick.       | _not defined_ |


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

| Setting                         | Description                                                                     | Default               |
|---------------------------------|---------------------------------------------------------------------------------|-----------------------|
|`CIRQUE_PINNACLE_X_LOWER`        | (Optional) The minimum reachable X value on the sensor.                         | `127`                 |
|`CIRQUE_PINNACLE_X_UPPER`        | (Optional) The maximum reachable X value on the sensor.                         | `1919`                |
|`CIRQUE_PINNACLE_Y_LOWER`        | (Optional) The minimum reachable Y value on the sensor.                         | `63`                  |
|`CIRQUE_PINNACLE_Y_UPPER`        | (Optional) The maximum reachable Y value on the sensor.                         | `1471`                |
|`CIRQUE_PINNACLE_TAPPING_TERM`   | (Optional) Length of time that a touch can be to be considered a tap.           | `TAPPING_TERM`/`200`  |
|`CIRQUE_PINNACLE_TOUCH_DEBOUNCE` | (Optional) Length of time that a touch can be to be considered a tap.           | `TAPPING_TERM`/`200`  |

| I2C Setting              | Description                                                                     | Default |
|--------------------------|---------------------------------------------------------------------------------|---------|
|`CIRQUE_PINNACLE_ADDR`    | (Required) Sets the I2C Address for the Cirque Trackpad                         | `0x2A`  |
|`CIRQUE_PINNACLE_TIMEOUT` | (Optional) The timeout for i2c communication with the trackpad in milliseconds. | `20`    |

| SPI Setting                   | Description                                                            | Default       |
|-------------------------------|------------------------------------------------------------------------|---------------|
|`CIRQUE_PINNACLE_CLOCK_SPEED`  | (Optional) Sets the clock speed that the sensor runs at.               | `1000000`     |
|`CIRQUE_PINNACLE_SPI_LSBFIRST` | (Optional) Sets the Least/Most Significant Byte First setting for SPI. | `false`       |
|`CIRQUE_PINNACLE_SPI_MODE`     | (Optional) Sets the SPI Mode for the sensor.                           | `1`           |
|`CIRQUE_PINNACLE_SPI_DIVISOR`  | (Optional) Sets the SPI Divisor used for SPI communication.            | _varies_      |
|`CIRQUE_PINNACLE_SPI_CS_PIN`   | (Required) Sets the Cable Select pin connected to the sensor.          | _not defined_ |

Default Scaling/CPI is 1024.

### Pimoroni Trackball

To use the Pimoroni Trackball module, add this to your `rules.mk`:

```make
POINTING_DEVICE_DRIVER = pimoroni_trackball
```

The Pimoroni Trackball module is a I2C based breakout board with an RGB enable trackball. 

| Setting                             | Description                                                                        | Default |
|-------------------------------------|------------------------------------------------------------------------------------|---------|
|`PIMORONI_TRACKBALL_ADDRESS`         | (Required) Sets the I2C Address for the Pimoroni Trackball.                        | `0x0A`  |
|`PIMORONI_TRACKBALL_TIMEOUT`         | (Optional) The timeout for i2c communication with the trackpad in milliseconds.    | `100`   |
|`PIMORONI_TRACKBALL_INTERVAL_MS`     | (Optional) The update/read interval for the sensor in milliseconds.                | `8`     |
|`PIMORONI_TRACKBALL_SCALE`           | (Optional) The multiplier used to generate reports from the sensor.                | `5`     |
|`PIMORONI_TRACKBALL_DEBOUNCE_CYCLES` | (Optional) The number of scan cycles used for debouncing on the ball press.        | `20`    |
|`PIMORONI_TRACKBALL_ERROR_COUNT`     | (Optional) Specifies the number of read/write errors until the sensor is disabled. | `10`  |

### PMW 3360 Sensor

To use the PMW 3360 sensor, add this to your `rules.mk`

```make
POINTING_DEVICE_DRIVER = pmw3360
```

The PMW 3360 is an SPI driven optical sensor, that uses a built in IR LED for surface tracking.

| Setting                     | Description                                                                                | Default       |
|-----------------------------|--------------------------------------------------------------------------------------------|---------------|
|`PMW3360_CS_PIN`             | (Required) Sets the Cable Select pin connected to the sensor.                              | _not defined_ |
|`PMW3360_CLOCK_SPEED`        | (Optional) Sets the clock speed that the sensor runs at.                                   | `2000000`     |
|`PMW3360_SPI_LSBFIRST`       | (Optional) Sets the Least/Most Significant Byte First setting for SPI.                     | `false`       |
|`PMW3360_SPI_MODE`           | (Optional) Sets the SPI Mode for the sensor.                                               | `3`           |
|`PMW3360_SPI_DIVISOR`        | (Optional) Sets the SPI Divisor used for SPI communication.                                | _varies_      |
|`PMW3360_LIFTOFF_DISTANCE`   | (Optional) Sets the lift off distance at run time                                          | `0x02`        |
|`ROTATIONAL_TRANSFORM_ANGLE` | (Optional) Allows for the sensor data to be rotated +/- 30 degrees directly in the sensor. | `0`           |

The CPI range is 100-12000, in increments of 100. Defaults to 1600 CPI.


### Custom Driver

If you have a sensor type that isn't supported here, you can manually implement it, by adding these functions (with the correct implementation for your device):

```c
void           pointing_device_driver_init(void) {}
report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report) { return mouse_report; }
uint16_t       pointing_device_driver_get_cpi(void) { return 0; }
void           pointing_device_driver_set_cpi(uint16_t cpi) {}
```

!> Ideally, new sensor hardware should be added to `drivers/sensors/` and `quantum/pointing_device_drivers.c`, but there may be cases where it's very specific to the hardware.  So these functions are provided, just in case. 

## Common Configuration

| Setting                       | Description                                                           | Default       |
|-------------------------------|-----------------------------------------------------------------------|---------------|
|`POINTING_DEVICE_ROTATION_90`  | (Optional) Rotates the X and Y data by  90 degrees.                   | _not defined_ |
|`POINTING_DEVICE_ROTATION_180` | (Optional) Rotates the X and Y data by 180 degrees.                   | _not defined_ |
|`POINTING_DEVICE_ROTATION_270` | (Optional) Rotates the X and Y data by 270 degrees.                   | _not defined_ |
|`POINTING_DEVICE_INVERT_X`     | (Optional) Inverts the X axis report.                                 | _not defined_ |
|`POINTING_DEVICE_INVERT_Y`     | (Optional) Inverts the Y axis report.                                 | _not defined_ |
|`POINTING_DEVICE_MOTION_PIN`   | (Optional) If supported, will only read from sensor if pin is active. | _not defined_ |


## Callbacks and Functions 

| Function                          | Description                                                                                                                            |
|-----------------------------------|----------------------------------------------------------------------------------------------------------------------------------------|
| `pointing_device_init_kb(void)`                            | Callback to allow for keyboard level initialization. Useful for additional hardware sensors.                  |
| `pointing_device_init_user(void)`                          | Callback to allow for user level initialization. Useful for additional hardware sensors.                      |
| `pointing_device_task_kb(mouse_report)`                    | Callback that sends sensor data, so keyboard code can intercept and modify the data.  Returns a mouse report. |
| `pointing_device_task_user(mouse_report)`                  | Callback that sends sensor data, so user coe can intercept and modify the data.  Returns a mouse report.      |
| `pointing_device_handle_buttons(buttons, pressed, button)` | Callback to handle hardware button presses. Returns a `uint8_t`.                                              |
| `pointing_device_get_cpi(void)`                            | Gets the current CPI/DPI setting from the sensor, if supported.                                               |
| `pointing_device_set_cpi(uint16_t)`                        | Sets the CPI/DPI, if supported.                                                                               |
| `pointing_device_get_report(void)`                         | Returns the current mouse report (as a `mouse_report_t` data structure).                                      | 
| `pointing_device_set_report(mouse_report)`                 | Sets the mouse report to the assigned `mouse_report_t` data structured passed to the function.                | 
| `pointing_device_send(void)`                               | Sends the current mouse report to the host system.  Function can be replaced.                                 | 
| `has_mouse_report_changed(old, new)`                       | Compares the old and new `mouse_report_t` data and returns true only if it has changed.                       |


# Manipulating Mouse Reports

The report_mouse_t (here "mouseReport") has the following properties:

* `mouseReport.x` - this is a signed int from -127 to 127 (not 128, this is defined in USB HID spec) representing movement (+ to the right, - to the left) on the x axis.
* `mouseReport.y` - this is a signed int from -127 to 127 (not 128, this is defined in USB HID spec) representing movement (+ upward, - downward) on the y axis.
* `mouseReport.v` - this is a signed int from -127 to 127 (not 128, this is defined in USB HID spec) representing vertical scrolling (+ upward, - downward).
* `mouseReport.h` - this is a signed int from -127 to 127 (not 128, this is defined in USB HID spec) representing horizontal scrolling (+ right, - left).
* `mouseReport.buttons` - this is a uint8_t in which all 8 bits are used.  These bits represent the mouse button state - bit 0 is mouse button 1, and bit 7 is mouse button 8.

To manually manipulate the mouse reports outside of the `pointing_device_task_*` functions, you can use:

* `pointing_device_get_report()` - Returns the current report_mouse_t that represents the information sent to the host computer
* `pointing_device_set_report(report_mouse_t newMouseReport)` - Overrides and saves the report_mouse_t to be sent to the host computer
* `pointing_device_send()` - Sends the mouse report to the host and zeroes out the report. 

When the mouse report is sent, the x, y, v, and h values are set to 0 (this is done in `pointing_device_send()`, which can be overridden to avoid this behavior).  This way, button states persist, but movement will only occur once.  For further customization, both `pointing_device_init` and `pointing_device_task` can be overridden.

Additionally, by default, `pointing_device_send()` will only send a report when the report has actually changed.  This prevents it from continuously sending mouse reports, which will keep the host system awake.  This behavior can be changed by creating your own `pointing_device_send()` function.

Also, you use the `has_mouse_report_changed(new, old)` function to check to see if the report has changed.

## Example

In the following example, a custom key is used to click the mouse and scroll 127 units vertically and horizontally, then undo all of that when released - because that's a totally useful function.  Listen, this is an example:

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
