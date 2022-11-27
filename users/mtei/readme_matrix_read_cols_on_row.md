# Fast version of `matrix_read_cols_on_rows()`

Starting with QMK firmware version 0.14.0, the following functions in quantum/matrix.c can be overridden by user-defined functions.

```c
// user-defined overridable functions
__attribute__((weak)) void matrix_init_pins(void);
__attribute__((weak)) void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row);
__attribute__((weak)) void matrix_read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col);
```

The matrix_read_cols_on_rows.c in this directory provides a fast version of matrix_read_cols_on_rows().

## How to use `matrix_read_cols_on_rows.c` with an existing keyboard.

`matrix_read_cols_on_rows.c` can be used on many standard keyboards with DIODE_DIRECTION set to COL2ROW. You can try the following steps.

1) Create the `keyboards/KEYBOARD/boost` subdirectory.
   ```shell
   mkdir keyboards/KEYBOARD/boost
   ```
2) Create the file `keyboards/KEYBOARD/boost/rules.mk` and write the following
   ```makefile
   # rules.mk for matrix_read_cols_on_rows.c
   SRC += matrix_read_cols_on_row.c
   ```
3) Convert the keyboard matrix configuration to the format for `matrix_read_cols_on_rows.c` by following these steps
   * If MATRIX_COL_PINS and MATRIX_ROW_PINS are defined in config.h, do the following
     ```shell
     python3 users/mtei/convert_matrix_config.py keyboards/KEYBOARD/config.h > keyboards/KEYBOARD/boost/config.h
     ```
   * If "matrix_pins" is defined in info.json, do the following
     ```shell
     python3 users/mtei/convert_matrix_config.py keyboards/KEYBOARD/info.json > keyboards/KEYBOARD/boost/config.h
     ```
4) Copy files into `keyboards/KEYBOARD/boost`
   ```shell
   cp users/mtei/matrix_read_cols_on_row.c keyboards/KEYBOARD/boost
   cp users/mtei/cpp_map.h keyboards/KEYBOARD/boost
   ```
   * If the MCU is AVR-based, do the following
     ```shell
     cp users/mtei/platforms/avr/gpio_extr.h keyboards/KEYBOARD/boost
     ```
   * If the MCU is ARM-based, do the following
     ```shell
     cp users/mtei/platforms/chibios/gpio_extr.h keyboards/KEYBOARD/boost
     ```
5) Build and write the firmware.
   ```shell
   make KEYBOARD/boost:KEYMAP:flash
   ```

## Convert Configuration

fast `matrix_read_cols_on_rows()` requires a different macros than the existing matrix configuration. We have a converter for creating new macros from existing configurations.

Generate the required configuration by running the converter as follows

```shell
python3 users/mtei/convert_matrix_config.py <config.h or info.json>
```

## Configuration

 * [Matrix configuration](#matrix-configuration)
   * [`#define SWITCH_MATRIX_INPUT_0`](#define-switch_matrix_input_0)
   * [`#define SWITCH_MATRIX_OUTPUT_0`](#define-switch_matrix_output_0)
   * [`#define MATRIX_EXTENSION_74HC157`](#define-matrix_extension_74hc157)
   * [`#define MATRIX_SWITCH_LOGIC_IS_ACTIVE_HIGH`](#define-matrix_switch_logic_is_active_high)
   * [`#define MATRIX_USE_OPENDRAIN_PULLUP`](#define-matrix_use_opendrain_pullup)
   * [For split keyboards with different configurations on the left and right.](#for-split-keyboards-with-different-configurations-on-the-left-and-right)
 * [Delay configuration](#delay-configuration)
   * [`#define MATRIX_IO_DELAY_TYPE ADAPTIVE_TO_INPUT`](#define-matrix_io_delay_type-adaptive_to_input)
   * [`#define MATRIX_IO_DELAY_TYPE FORCE_INPUT_UP_TO_VCC`](#define-matrix_io_delay_type-force_input_up_to_vcc)
   * [`#define MATRIX_IO_DELAY_TYPE WAIT_SPECIFIED_TIME`](#define-matrix_io_delay_type-wait_specified_time)

### Matrix configuration

#### `#define SWITCH_MATRIX_INPUT_0`

The SWITCH_MATRIX_INPUT_0 macro defines input pins similar to the MATRIX_COL_PINS macro in a COL2ROW type matrix.

For example, suppose we have a definition like the following example
```c
#define MATRIX_COL_PINS { B4 }
```
In SWITCH_MATRIX_INPUT_0 The same pin assignment is written as follows
```c
#define SWITCH_MATRIX_INPUT_0 \
    /* ( ( <port>, <mask>, <dev> ), ... ) */ \
    ( (B0, 0x10, MCU_GPIO) ),\
    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \
    ( (0, 0x10, 0x01) )
```
Also, for example, suppose we have a definition like the following example
```c
#define MATRIX_COL_PINS { B4, B6 }
```
In SWITCH_MATRIX_INPUT_0 The same pin assignment is written as follows
```c
#define SWITCH_MATRIX_INPUT_0 \
    /* ( ( <port>, <mask>, <dev> ), ... ) */ \
    ( (B0, 0x50, MCU_GPIO) ),\
    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \
    ( (0, 0x10, 0x01), \
      (0, 0x40, 0x02) )
```
Also, for example, suppose we have a definition like the following example
```c
#define MATRIX_COL_PINS { B4, B6, C3 }
```
In SWITCH_MATRIX_INPUT_0 The same pin assignment is written as follows
```c
#define SWITCH_MATRIX_INPUT_0 \
    /* ( ( <port>, <mask>, <dev> ), ... ) */ \
    ( (B0, 0x50, MCU_GPIO), \
      (C0, 0x08, MCU_GPIO) ),\
    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \
    ( (0, 0x10, 0x01), \
      (0, 0x40, 0x02), \
      (1, 0x08, 0x04) )
```

As the above examples shows, SWITCH_MATRIX_INPUT_0 consists of two parts: a port list and a pin list.

```
#define SWITCH_MATRIX_INPUT_0 ( <port_list> ), ( <pin_list> )
```

The port list is a comma-separated list of port definitions in the following formats:

```
( <port_name>, <port_mask>, <device_name> )
```
* `<device_name>` can currently only be filled in for `MCU_GPIO`.
* In `<port_name>`, the number 0 of the GPIO pin notation, such as `B0`, `C0`, is written as a representative of the port.
* `<port_mask>` describes the sum of `<port_mask>` of the following pin list.

The pin list is a comma-separated list of port definitions in the following formats:
```
( <port_list_index>, <port_mask>, <matrix_row_mask> )
```
* `<port_list_index>` specifies the port number in the above port list.
* `<port_mask>` is a mask value for the pin number. That is `(1<<pin_number)`.
* `<matrix_row_mask>` specifies which bit of the matrix row data should be set to 1 when this pin is input.

The following data that has `NO_PIN` specified in MATRIX_COL_PINS
```c
#define MATRIX_COL_PINS { B4, B6, NO_PIN, C3 }
```
In SWITCH_MATRIX_INPUT_0 The same pin assignment is written as follows. You can see that `NO_PIN` does not appear in the pin list, but the `<matrix_row_mask>` is adjusted so that the pin is not reflected in the matrix row data.
```c
#define SWITCH_MATRIX_INPUT_0 \
    /* ( ( <port>, <mask>, <dev> ), ... ) */ \
    ( (B0, 0x50, MCU_GPIO), \
      (C0, 0x08, MCU_GPIO) ),\
    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \
    ( (0, 0x10, 0x01), \
      (0, 0x40, 0x02), \
      (1, 0x08, 0x08) )
```

#### `#define SWITCH_MATRIX_OUTPUT_0`

The SWITCH_MATRIX_OUTPUT_0 macro defines output pins similar to the MATRIX_ROW_PINS macro in a COL2ROW type matrix. The format is almost the same as SWITCH_MATRIX_INPUT_0.

The difference is that the `<matrix_row_mask>` in the pin definition does not have much meaning, and any number other than 0 is allowed.

For example, suppose we have a definition like the following example
```c
#define MATRIX_ROW_PINS { B3, D1, B6 }
```
In SWITCH_MATRIX_OUTPUT_0 The same pin assignment is written as follows
```c
#define SWITCH_MATRIX_OUTPUT_0 \
    /* ( ( <port>, <mask>, <dev> ), ... ) */ \
    ( (B0, 0x48, MCU_GPIO), \
      (D0, 0x02, MCU_GPIO) ),\
    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \
    ( (0, 0x08, 0x01), \
      (1, 0x02, 0x02), \
      (0, 0x40, 0x04) )
```

If the `<matrix_row_mask>` of the pin definition is 0, it has the meaning equivalent to NO_PIN in the MATRIX_ROW_PINS definition.

For example, suppose we have a definition like the following example
```c
#define MATRIX_ROW_PINS { B3, D1, NO_PIN, B6 }
```
In SWITCH_MATRIX_OUTPUT_0 The same pin assignment is written as follows
```c
#define SWITCH_MATRIX_OUTPUT_0 \
    /* ( ( <port>, <mask>, <dev> ), ... ) */ \
    ( (B0, 0x48, MCU_GPIO), \
      (D0, 0x02, MCU_GPIO) ),\
    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \
    ( (0, 0x08, 0x01), \
      (1, 0x02, 0x02), \
      (0, 0x00,      0x00/* <-- 0 means NO_PIN */), \
      (0, 0x40, 0x08) )
```

#### `#define MATRIX_EXTENSION_74HC157`

If the connection between the MCU and the keyswitch matrix is via the 74HC157, this macro specifies the GPIO pin that connects the 74HC157 A/B selection pin.

If this macro is defined, MCU_GPIO_74HC157_A and MCU_GPIO_74HC157_B can be specified in addition to MCU_GPIO for the device specification of the SWITCH_MATRIX_INPUT_0 macro.

#### `#define MATRIX_SWITCH_LOGIC_IS_ACTIVE_HIGH`

Define this macro when the input pin of the keyswitch is active high.

#### `#define MATRIX_USE_OPENDRAIN_PULLUP`

On un-select of matrix pins, rather than setting pins to input-high, sets them to opendrain-high.

#### For split keyboards with different configurations on the left and right.

Define SWITCH_MATRIX_INPUT_1 and SWITCH_MATRIX_OUTPUT_1 in the same format as above.

### Delay configuration

fast matrix_read_cols_on_rows() provides three delay methods to avoid ghosting of the input line after unselecting the output line during matrix scan. The delay method can be specified with the configuration macro MATRIX_IO_DELAY_TYPE. If not specified, the default `ADAPTIVE_TO_INPUT` is assumed.

#### `#define MATRIX_IO_DELAY_TYPE ADAPTIVE_TO_INPUT`
If ADAPTIVE_TO_INPUT is specified, the input is monitored and delayed until the ghost disappears.

* If there is no input, there will be no delay.

  <img width="50%" alt="adaptive0" src="https://user-images.githubusercontent.com/2170248/177012498-73799157-0001-4609-9756-645003a83ec0.png">

* If there is an input, it will be delayed by the required length.

  <img width="50%" alt="adaptive1" src="https://user-images.githubusercontent.com/2170248/177012505-4a12a663-b7b3-4965-ae0c-65ba94843626.png">
  <img width="50%" alt="adaptive2" src="https://user-images.githubusercontent.com/2170248/177012509-a93feea3-b42b-459c-b0ec-21fd0e611971.png">
  <img width="50%" alt="adaptive3" src="https://user-images.githubusercontent.com/2170248/177012513-e6925110-a0f2-4e1a-805d-32d39de14149.png">

#### `#define MATRIX_IO_DELAY_TYPE ADAPTIVE_TO_INPUT_WITH_TIME`
If ADAPTIVE_TO_INPUT_WITH_TIME is specified, the input is monitored and delayed until the ghost disappears then delays for the specified time.

#### `#define MATRIX_IO_DELAY_TYPE FORCE_INPUT_UP_TO_VCC`
If FORCE_INPUT_UP_TO_VCC is specified, the input line is temporarily switched to output for high output, and then returned to input mode.

<img width="50%" alt="inputpull" src="https://user-images.githubusercontent.com/2170248/177012515-dff260ba-3924-401d-9d5c-c61691e660e0.png">

#### `#define MATRIX_IO_DELAY_TYPE WAIT_SPECIFIED_TIME`
Delays for the specified time regardless of whether or not there is an input.

<img width="50%" alt="time0" src="https://user-images.githubusercontent.com/2170248/177012518-e70a43c9-b0c0-414b-8765-a8bcd3f4b585.png">

<img width="50%" alt="time1" src="https://user-images.githubusercontent.com/2170248/177012525-61d67b8d-d95d-4236-ac22-cca5cd152a11.png">

## Performance

The timing chart of the firmware using the normal firmware and fast matrix_read_cols_on_rows() on the Helix keyboard (AVR-based split keyboard) is as follows.

* Without fast matrix_read_cols_on_rows().
  <img width="80%" alt="helix-normal" src="https://user-images.githubusercontent.com/2170248/176904371-bce2ee2b-c616-42ec-b37c-b939d36096cf.png">

* With fast matrix_read_cols_on_rows().
  <img width="80%" alt="helix-boost" src="https://user-images.githubusercontent.com/2170248/176904404-a78a5b56-65ae-4e8c-a32b-d48a679e8cb5.png">

[See symmetric70_proto/matrix_boost/readme.md for further information on other cases.](../../keyboards/handwired/symmetric70_proto/matrix_boost/readme.md)
