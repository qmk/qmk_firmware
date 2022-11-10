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
