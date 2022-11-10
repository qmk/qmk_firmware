# Debug version matrix.c(0.18.0), matrix_extension_74hc157.c and matrix_read_cols_on_row.c

This directory is provided for testing and performance evaluation of [`users/mtei/matrix_read_cols_on_row.c`](../../../../users/mtei/readme_matrix_read_cols_on_row.md)  using symmetric70_proto.

The matrix.c in this directory is 0.18.0:quantum/matrix.c with the following additions:

* Added the MATRIX_DEBUG_SCAN_{START/END} macro to measure the execution time of matrix_scan().
* Added the MATRIX_DEBUG_DELAY_{START/END} macro to measure delay time.

The matrix_extension_74hc157.c in this directory provides `matrix_read_cols_on_row()` that adds support for 74hc157 used in the symmetric70_proto/promicro hardware.

## Current performance

### Without fast `matrix_read_cols_on_rows() in users/mtei/`

* Measurement with QMK 0.18.0

| MCU               | execution time of `matrix_scan()` | matrix scan rate |
|-------------------|---------------|----------------|
| Pro Micro (16MHz) | 588.5 us      | 1612 scans/sec (620us) |
| Proton C (72MHz)  | 253.9 us      | 3794 scans/sec (263.5us) |

### With fast `matrix_read_cols_on_rows() in users/mtei/`

* Measurement with QMK 0.18.0

| MCU               | execution time of `matrix_scan()` | matrix scan rate |
|-------------------|---------------|----------------|
| Pro Micro (16MHz) | 92 us         |  8064 scans/sec (124us)  |
| Proton C (72MHz)  | 57.07 us      | 14995 scans/sec (66.69us)|

## Configuration

`users/mtei/matrix_read_cols_on_row.c` requires its own non-standard matrix configuration.
[see Configuration in users/mtei/readme_matrix_read_cols_on_row.md](../../../../users/mtei/readme_matrix_read_cols_on_row.md#configuration)

## Easy way to configure

[see How to use `matrix_read_cols_on_rows.c` in users/mtei/readme_matrix_read_cols_on_row.md](../../../../users/mtei/readme_matrix_read_cols_on_row.md#how-to-use-matrix_read_cols_on_rowsc-with-an-existing-keyboard)

## Compile

* Set MATRIX_IO_DELAY value
  * `make MTEST=mdelay0 handwired/symmetric70_proto/promicro/boost:default:flash`
  * `make MTEST=mdelay=1 handwired/symmetric70_proto/promicro/boost:default:flash`
  * `make MTEST=mdelay=30 handwired/symmetric70_proto/promicro/boost:default:flash`
* Measure the execution time of matrix_scan()
  * `make MTEST=matrix_debug_scan[,<other options>..] handwired/symmetric70_proto/promicro/boost:default:flash`
* Measure delay time.
  * `make MTEST=matrix_debug_delay[,<other options>..] handwired/symmetric70_proto/promicro/boost:default:flash`
* Measure the execution time of matrix_scan() and delay time.
  * `make MTEST=matrix_debug_delay,matrix_debug_scan[,<other options>..] handwired/symmetric70_proto/promicro/boost:default:flash`
* Change the behavior of delay
  * `make MTEST=matrix_debug_delay,mdelay_type=adaptive handwired/symmetric70_proto/promicro/boost:default:flash`
  * `make MTEST=matrix_debug_delay,mdelay_type=time,mdelay=30 handwired/symmetric70_proto/promicro/boost:default:flash`
  * `make MTEST=matrix_debug_delay,mdelay_type=ipullup handwired/symmetric70_proto/promicro/boost:default:flash`
* Don't use fast `matrix_read_cols_on_rows()`
  * `make MTEST=[<other options>...] handwired/symmetric70_proto/promicro/normal:default:flash`

## Measurement result
### Pro Micro (ATmega32u4 16Mhz)
#### Default setting (without fast `matrix_read_cols_on_rows()`)
 - `make MTEST=matrix_debug_scan,matrix_debug_delay handwired/symmetric70_proto/promicro/normal:default:flash`

<img width="80%" alt="sym70_promicro_normal" src="https://user-images.githubusercontent.com/2170248/201068411-7159393b-25ad-4c07-8893-25873f09ccc4.png">

#### Default setting (with fast `matrix_read_cols_on_rows()`)
 - `make MTEST=matrix_debug_scan,matrix_debug_delay handwired/symmetric70_proto/promicro/boost:default:flash`

<img width="80%" alt="sym70_promicro_boost" src="https://user-images.githubusercontent.com/2170248/201068474-6878803b-82a3-48fe-b0ba-5837df78328e.png">

### Proton C (STM32F303 72MHz)
#### Default setting (without fast `matrix_read_cols_on_rows()`)
 - `make MTEST=matrix_debug_scan,matrix_debug_delay handwired/symmetric70_proto/proton_c/normal:default:flash`

<img width="80%" alt="sym70_proton_c_normal" src="https://user-images.githubusercontent.com/2170248/201057666-c80db142-0924-433e-836b-7c658ca25e28.png">

#### Default setting (with fast `matrix_read_cols_on_rows()`)
 - `make MTEST=matrix_debug_scan,matrix_debug_delay handwired/symmetric70_proto/proton_c/boost:default:flash`

<img width="80%" alt="sym70_proton_c_boost" src="https://user-images.githubusercontent.com/2170248/201057777-1775adbf-1bbd-49ca-a156-f7b6bf956b54.png">

##### Press R0C5, R1C5, R2C5, R3C5, R4C5 keys

<img width="80%" alt="sym70_proton_c_boost_C5" src="https://user-images.githubusercontent.com/2170248/201057876-697be08c-9e47-4325-b9d3-4058f5a4c75f.png">

##### Connect a 500pF capacitor between C5 line and GND, Press R0C5, R1C5, R2C5, R3C5, R4C5 keys

<img width="80%" alt="sym70_proton_c_boost_C5_500p_re" src="https://user-images.githubusercontent.com/2170248/201057980-4ef7d52a-6b5b-451f-8026-a3e7f3495723.png">

 ##### Connect a 1000pF capacitor between C5 line and GND, Press R0C5, R1C5, R2C5, R3C5, R4C5 keys

<img width="80%" alt="sym70_proton_c_boost_C5_1000p" src="https://user-images.githubusercontent.com/2170248/201058046-ceee2a34-ef91-4277-968a-9c40dd198230.png">

## A quick explanation of the code in the fast `matrix_read_cols_on_row.c`

The fast version `matrix_read_cols_on_row()` has the following three features.

   * Don't do unnecessary `readPort()`.
   * If the read port data does not indicate a key press, do not calculate current_row_value.
   * Minimize delay after `unselect_row()` by monitoring Col pins.

By default, the preprocessor turns `matrix_read_cols_on_row()` into code like this:

```c
void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    port_data_t port_buffer[2];
    matrix_row_t current_row_value = 0;
    bool key_pressed;

    if (!current_sides_opins[current_row]) {
        return; // skip NO_PIN row
    }
    select_output_0(current_row);
    matrix_output_select_delay();
    read_all_pins_0(port_buffer);
    unselect_output_0(current_row);
    key_pressed = mask_and_adjust_pins_0(port_buffer);
    if (key_pressed) {
        current_row_value = build_line_0(port_buffer);
    }
    // wait unselect done
    if (key_pressed) {
        while (key_pressed) {
            read_all_pins_0(port_buffer);
            key_pressed = mask_and_adjust_pins_0(port_buffer);
        }
    }
    // Update the matrix
    current_matrix[current_row] = current_row_value;
}
```

As an example, let's say you have the following configuration:
```
#define MATRIX_COL_PINS { A2, A1, A0, B8, B13, B14, B15, B9, B0, B1, B2, B3, B4, B5, B6, B7 }
#define MATRIX_ROW_PINS { A4, A5, A6, A7, A8 }
```

This is converted by the convert_matrix_config.py script to:
```c
#define SWITCH_MATRIX_INPUT_0 \
    /* ( ( <port>, <mask>, <dev> ), ... ) */ \
    ( (A0, 0x07, MCU_GPIO),                           \
      (B0, 0xe3ff, MCU_GPIO) ),\
    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \
    ( (0, 0x04, 0x01), \
      (0, 0x02, 0x02), \
      (0, 0x01, 0x04), \
      (1, 0x100, 0x08), \
      (1, 0x2000, 0x10), \
      (1, 0x4000, 0x20), \
      (1, 0x8000, 0x40), \
      (1, 0x200, 0x80), \
      (1, 0x01, 0x100), \
      (1, 0x02, 0x200), \
      (1, 0x04, 0x400), \
      (1, 0x08, 0x800), \
      (1, 0x10, 0x1000), \
      (1, 0x20, 0x2000), \
      (1, 0x40, 0x4000), \
      (1, 0x80, 0x8000) )

#define SWITCH_MATRIX_OUTPUT_0 \
    /* ( ( <port>, <mask>, <dev> ), ... ) */ \
    ( (A0, 0x1f0, MCU_GPIO) ),\
    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \
    ( (0, 0x10, 0x01), \
      (0, 0x20, 0x02), \
      (0, 0x40, 0x04), \
      (0, 0x80, 0x08), \
      (0, 0x100, 0x10) )
```

Based on the above macros, the preprocessor expands the following code.
```c
static void read_all_pins_0(port_data_t *buffer) {
    // buffer[INDEX] = readMatrixPort(DEV,PORT);
    buffer[0] = readPort(A0);
    buffer[1] = readPort(B0);
}

__attribute__((always_inline)) inline
static port_data_t mask_and_adjust_a_port(port_data_t data, port_data_t mask) {
    data &= mask;
    data ^= mask; // change to active-High
    return data;
}

static bool mask_and_adjust_pins_0(port_data_t *buffer) {
    port_data_t keypushd = 0;
    port_data_t data;

    // data = mask_and_adjust_a_port(*buffer, MASK);
    // keypushd |= data;
    // *buffer++ = data;
    data = mask_and_adjust_a_port(*buffer, 0x07);
    keypushd |= data;
    *buffer++ = data;
    data = mask_and_adjust_a_port(*buffer, 0xe3ff);
    keypushd |= data;
    *buffer++ = data;
    return keypushd != 0;
}

static matrix_row_t build_line_0(port_data_t *buffer) {
    return 0
    //  | (buffer[PORT_INDEX] & SMASK ? DMASK : 0)
        | ((buffer[0] & 0x04) ? 0x01 : 0)
        | ((buffer[0] & 0x02) ? 0x02 : 0)
        | ((buffer[0] & 0x01) ? 0x04 : 0)
        | ((buffer[1] & 0x100) ? 0x08 : 0)
        | ((buffer[1] & 0x2000) ? 0x10 : 0)
        | ((buffer[1] & 0x4000) ? 0x20 : 0)
        | ((buffer[1] & 0x8000) ? 0x40 : 0)
        | ((buffer[1] & 0x200) ? 0x80 : 0)
        | ((buffer[1] & 0x01) ? 0x100 : 0)
        | ((buffer[1] & 0x02) ? 0x200 : 0)
        | ((buffer[1] & 0x04) ? 0x400 : 0)
        | ((buffer[1] & 0x08) ? 0x800 : 0)
        | ((buffer[1] & 0x10) ? 0x1000 : 0)
        | ((buffer[1] & 0x20) ? 0x2000 : 0)
        | ((buffer[1] & 0x40) ? 0x4000 : 0)
        | ((buffer[1] & 0x80) ? 0x8000 : 0)
        ;
}
```
