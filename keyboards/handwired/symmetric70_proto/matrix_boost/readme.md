# Debug version matrix.c(0.18.0), matrix_extension_74hc157.c and matrix_read_cols_on_row.c

This directory is provided for testing and performance evaluation of [`users/mtei/matrix_read_cols_on_row.c`](../../../../users/mtei/readme_matrix_read_cols_on_row.md)  using symmetric70_proto.

The matrix.c in this directory is 0.18.0:quantum/matrix.c with the following additions:

* Added the MATRIX_DEBUG_SCAN_{START/END} macro to measure the execution time of matrix_scan().
* Added the MATRIX_DEBUG_DELAY_{START/END} macro to measure delay time.

The matrix_extension_74hc157.c in this directory provides `matrix_read_cols_on_row()` that adds support for 74hc157 used in the symmetric70_proto/promicro hardware.

## Current performance

### Without fast `matrix_read_cols_on_rows() in users/mtei/`

* Measurement with QMK 0.18.0

| MCU                        | execution time of `matrix_scan()` | matrix scan rate |
|----------------------------|---------------|--------------------------|
| Pro Micro (16MHz)          | 579.95 us     | 1634 scans/sec (611.95us)|
| Proton C (72MHz)           | 253.9 us      | 3793 scans/sec (263.6us) |
| Raspberry Pi Pico (125MHz) | 181.38 us     | 5262 scans/sec (190us)   |

### With fast `matrix_read_cols_on_rows() in users/mtei/`

* Measurement with QMK 0.18.0

| MCU                        | execution time of `matrix_scan()` | matrix scan rate |
|----------------------------|---------------|---------------------------|
| Pro Micro (16MHz)          | 90.9 us       |  8140 scans/sec (122.85us)|
| Proton C (72MHz)           | 56.94 us      | 15024 scans/sec (66.56us) |
| Raspberry Pi Pico (125MHz) | 30.03 us      | 26116 scans/sec (38.29us) |

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
### Pro Micro (ATmega32u4 16MHz)
#### Default setting (without fast `matrix_read_cols_on_rows()`)
 - `make MTEST=matrix_debug_scan,matrix_debug_delay handwired/symmetric70_proto/promicro/normal:default:flash`

<img width="80%" alt="sym70_oc_di_promicro_normal2" src="https://user-images.githubusercontent.com/2170248/204037443-2db56b4a-c482-40e6-a211-95a8fddb625d.png">


#### Default setting (with fast `matrix_read_cols_on_rows()`)
 - `make MTEST=matrix_debug_scan,matrix_debug_delay handwired/symmetric70_proto/promicro/boost:default:flash`

<img width="80%" alt="sym70_oc_di_promicro_boost2" src="https://user-images.githubusercontent.com/2170248/204037530-f977bb88-0fcf-499f-929a-62e4103ba46c.png">
<img width="80%" alt="sym70_oc_di_promicro_boost_zoom2" src="https://user-images.githubusercontent.com/2170248/204037578-410b815c-8a99-4c8d-ae56-be54f92d4dd8.png">

### Proton C (STM32F303 72MHz)
#### Default setting (without fast `matrix_read_cols_on_rows()`)
 - `make MTEST=matrix_debug_scan,matrix_debug_delay handwired/symmetric70_proto/proton_c/normal:default:flash`

<img width="80%" alt="sym70_oc_di_proton_c_normal_10k" src="https://user-images.githubusercontent.com/2170248/203856220-c408b005-1dd2-4b96-b233-5dba849afd83.png">

#### Default setting (with fast `matrix_read_cols_on_rows()`)
 - `make MTEST=matrix_debug_scan,matrix_debug_delay handwired/symmetric70_proto/proton_c/boost:default:flash`

<img width="80%" alt="sym70_oc_di_proton_c_boost_10k" src="https://user-images.githubusercontent.com/2170248/203856256-30da3e66-a51f-45e7-ada8-e91658b54be0.png">

##### Press R0C5, R1C5, R2C5, R3C5, R4C5 keys

<img width="80%" alt="sym70_oc_di_proton_c_boost_10k_zoom2_C5" src="https://user-images.githubusercontent.com/2170248/203856457-2469b3e2-9c52-497a-a5bb-4069bfe29728.png">

##### Connect a 500pF capacitor between C5 line and GND, Press R0C5, R1C5, R2C5, R3C5, R4C5 keys

<img width="80%" alt="sym70_oc_di_proton_c_boost_10k_zoom2_C5_500pf" src="https://user-images.githubusercontent.com/2170248/203856491-bcbe78be-f87c-4583-83a4-45e82cd39b89.png">

 ##### Connect a 1000pF capacitor between C5 line and GND, Press R0C5, R1C5, R2C5, R3C5, R4C5 keys

<img width="80%" alt="sym70_oc_di_proton_c_boost_10k_zoom2_C5_1000pf" src="https://user-images.githubusercontent.com/2170248/203856536-e7b90f59-2bb0-4131-ad2c-03e56d1376ae.png">

### Raspberry Pi Pico (RP2040 125MHz)
#### Default setting (without fast `matrix_read_cols_on_rows()`)
 - `make MTEST=matrix_debug_scan,matrix_debug_delay handwired/symmetric70_proto/rp_pico/normal:default:flash`

<img width="80%" alt="sym70_oc_di_rp_pico_normal_10k" src="https://user-images.githubusercontent.com/2170248/203856051-1a9642ad-9659-4e35-92e5-5c5fe1ee2df1.png">

#### Default setting (with fast `matrix_read_cols_on_rows()`)
 - `make MTEST=matrix_debug_scan,matrix_debug_delay handwired/symmetric70_proto/pr_pico/boost:default:flash`

<img width="80%" alt="sym70_oc_di_rp_pico_boost_10k_4" src="https://user-images.githubusercontent.com/2170248/204024953-7cbcfb47-053b-4763-b356-40023aa346a5.png">

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
