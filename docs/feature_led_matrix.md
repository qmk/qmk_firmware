# LED Matrix Lighting

This feature allows you to use LED matrices driven by external drivers. It hooks into the [backlight subsystem](feature_backlight.md) so you can use the same keycodes as backlighting to control it. Many of the same configuration settings apply as well.

If you want to use RGB LED's you should use the [RGB Matrix Subsystem](feature_rgb_matrix.md) instead.

LED Matrix supports LEDs that are connected directly to the MCU and LEDs connected to an external controller IC (such as the IS31FL3731 from ISSI.)

## Directly Connected LEDs

There are two ways that LEDs can be connected to the LED Matrix- 

* Direct Pin: One pin per LED
* Direct Pin Matrix: LED matrix with rows and columns

### Direct Pin

This driver uses LEDs that are connected directly to to a pin on the PCB. If you are not familiar with how to wire an LED directly to a microcontroller you can [follow this guide](https://create.arduino.cc/projecthub/rowan07/make-a-simple-led-circuit-ce8308). The process is similar for every microcontroller that QMK supports.

You can configure the driver to either source or sink current, but that setting applies to all LEDs.

Settings needed in `rules.mk`:

| Variable | Description |
|----------|-------------|
| `BACKLIGHT_ENABLE = yes` | Turn on the backlight subsystem |
| `LED_MATRIX_ENABLE = pins` | Enable the LED Matrix subsystem and configure it for directly connected LEDs |

Settings needed in `config.h`:

| Variable | Description | Default |
|----------|-------------|---------|
| `LED_MATRIX_PINS` | A list of pins with connected LEDs. | `{ }` |
| `LED_DRIVER_LED_COUNT` | The number of LEDs connected to pins |

### Direct Pin Matrix

This driver supports driving an LED matrix that is connected directly to the local controller in a common-row cathode orientation. For more general information on LED matrices and how to design them there are several useful outside resources:

* https://www.circuitspecialists.com/blog/build-8x8-led-matrix/
* https://www.instructables.com/id/Make-Your-Own-LED-Matrix-/
* https://appelsiini.net/2011/how-does-led-matrix-work/

Settings needed in `rules.mk`:

| Variable | Description |
|----------|-------------|
| `BACKLIGHT_ENABLE = yes` | Turn on the backlight subsystem |
| `LED_MATRIX_ENABLE = pinmatrix` | Enable the LED Matrix subsystem and configure it for a matrix |

Settings needed in `config.h`:

| Variable | Description | Default |
|----------|-------------|---------|
| `LED_DRIVER_LED_COUNT` | (Required) How many LED lights are present | (none) |
| `LED_MATRIX_COLS` | (Required) The number of columns (current sources) your matrix has | (none) |
| `LED_MATRIX_COL_PINS` | (Required) A list of column pins, EG `{ B1, B2, B3, B4 }`| (none) |
| `LED_MATRIX_ROWS` | (Required) The number of rows (current sinks) your matrix has | (none) |
| `LED_MATRIX_ROW_PINS` | (Required) A list of row pins, EG `{ B5, B6, B7, B8 }` | (none) |

## LED Driver ICs

You can also use an LED driver chip. The IS31 series of ICs is popular and well supported in QMK.

### IS31FL3731

There is basic support for addressable LED matrix lighting with the I2C IS31FL3731 RGB controller. To enable it, add this to your `rules.mk`:

    LED_MATRIX_ENABLE = IS31FL3731
    
You can use between 1 and 4 IS31FL3731 IC's. Do not specify `LED_DRIVER_ADDR_<N>` defines for IC's that are not present on your keyboard. You can define the following items in `config.h`:

| Variable | Description | Default |
|----------|-------------|---------|
| `ISSI_TIMEOUT` | (Optional) How long to wait for i2c messages | 100 |
| `ISSI_PERSISTENCE` | (Optional) Retry failed messages this many times | 0 |
| `LED_DRIVER_COUNT` | (Required) How many LED driver IC's are present | |
| `LED_DRIVER_LED_COUNT` | (Required) How many LED lights are present across all drivers | |
| `LED_DRIVER_ADDR_1` | (Required) Address for the first LED driver | |
| `LED_DRIVER_ADDR_2` | (Optional) Address for the second LED driver | |
| `LED_DRIVER_ADDR_3` | (Optional) Address for the third LED driver | |
| `LED_DRIVER_ADDR_4` | (Optional) Address for the fourth LED driver | |

Here is an example using 2 drivers.

	// This is a 7-bit address, that gets left-shifted and bit 0
	// set to 0 for write, 1 for read (as per I2C protocol)
	// The address will vary depending on your wiring:
	// 0b1110100 AD <-> GND
	// 0b1110111 AD <-> VCC
	// 0b1110101 AD <-> SCL
	// 0b1110110 AD <-> SDA
	#define LED_DRIVER_ADDR_1 0b1110100
	#define LED_DRIVER_ADDR_2 0b1110110

	#define LED_DRIVER_COUNT 2
	#define LED_DRIVER_1_LED_COUNT 25
	#define LED_DRIVER_2_LED_COUNT 24
	#define LED_DRIVER_LED_COUNT LED_DRIVER_1_LED_TOTAL + LED_DRIVER_2_LED_TOTAL

Currently only 2 drivers are supported, but it would be trivial to support all 4 combinations.

Define these arrays listing all the LEDs in your `<keyboard>.c`:

	const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
	/* Refer to IS31 manual for these locations
	 *   driver
	 *   |  LED address
	 *   |  | */
	    {0, C3_3},
	    ....
	}

Where `Cx_y` is the location of the LED in the matrix defined by [the datasheet](http://www.issi.com/WW/pdf/31FL3731.pdf) and the header file `drivers/issi/is31fl3731-simple.h`. The `driver` is the index of the driver you defined in your `config.h` (`0`, `1`, `2`, or `3` ).

## Keycodes

All LED matrix keycodes are currently shared with the [backlight system](feature_backlight.md).

## LED Matrix Effects

Currently no LED matrix effects have been created.

## Custom layer effects

Custom layer effects can be done by defining this in your `<keyboard>.c`:

    void led_matrix_indicators_kb(void) {
        led_matrix_set_index_value(index, value);
    }

A similar function works in the keymap as `led_matrix_indicators_user`.

## Suspended state

To use the suspend feature, add this to your `<keyboard>.c`:

	void suspend_power_down_kb(void)
	{
	    led_matrix_set_suspend_state(true);
	}

	void suspend_wakeup_init_kb(void)
	{
	    led_matrix_set_suspend_state(false);
	}
