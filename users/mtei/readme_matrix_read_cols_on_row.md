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
     ruby users/mtei/convert_matrix_config.rb keyboards/KEYBOARD/config.h > keyboards/KEYBOARD/boost/config.h
     ```
   * If "matrix_pins" is defined in info.json, do the following
     ```shell
     ruby users/mtei/convert_matrix_config.rb keyboards/KEYBOARD/info.json > keyboards/KEYBOARD/boost/config.h
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
ruby users/mtei/convert_matrix_config.rb <config.h or info.json>
```

## Configuration

### Matrix configuration

#### `#define SWITCH_MATRIX_INPUT_0`
TBD

#### `#define SWITCH_MATRIX_OUTPUT_0`
TBD

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

#### `#define MATRIX_IO_DELAY_TYPE FORCE_INPUT_UP_TO_VCC`
If FORCE_INPUT_UP_TO_VCC is specified, the input line is temporarily switched to output for high output, and then returned to input mode.

<img width="50%" alt="inputpull" src="https://user-images.githubusercontent.com/2170248/177012515-dff260ba-3924-401d-9d5c-c61691e660e0.png">

#### `#define MATRIX_IO_DELAY_TYPE WAIT_SPECIFIED_TIME`
Delays for the specified time regardless of whether or not there is an input.

<img width="50%" alt="time0" src="https://user-images.githubusercontent.com/2170248/177012518-e70a43c9-b0c0-414b-8765-a8bcd3f4b585.png">

<img width="50%" alt="time1" src="https://user-images.githubusercontent.com/2170248/177012525-61d67b8d-d95d-4236-ac22-cca5cd152a11.png">

## Performance

The timing chart of the firmware using the normal firmware and the high-speed version of matrix_read_cols_on_rows() on the Helix keyboard (AVR-based split keyboard) is as follows.

* Without fast matrix_read_cols_on_rows().
  <img width="80%" alt="helix-normal" src="https://user-images.githubusercontent.com/2170248/176904371-bce2ee2b-c616-42ec-b37c-b939d36096cf.png">

* With fast matrix_read_cols_on_rows().
  <img width="80%" alt="helix-boost" src="https://user-images.githubusercontent.com/2170248/176904404-a78a5b56-65ae-4e8c-a32b-d48a679e8cb5.png">

[See symmetric70_proto/matrix_boost/readme.md for further information on other cases.](../../keyboards/handwired/symmetric70_proto/matrix_boost/readme.md)
