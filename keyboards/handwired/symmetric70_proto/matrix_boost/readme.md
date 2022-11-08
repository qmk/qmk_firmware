# Debug version matrix.c(0.18.0), matrix_extension_74hc157.c and matrix_read_cols_on_row.c

This directory is provided for testing and performance evaluation of [`users/mtei/matrix_read_cols_on_row.c`](../../../../users/mtei/readme_matrix_read_cols_on_row.md)  using symmetric70_proto.

The matrix.c in this directory is 0.17.0:quantum/matrix.c with the following additions:

* Added the MATRIX_DEBUG_SCAN_{START/END} macro to measure the execution time of matrix_scan().
* Added the MATRIX_DEBUG_DELAY_{START/END} macro to measure delay time.

The matrix_extension_74hc157.c in this directory provides `matrix_read_cols_on_row()` that adds support for 74hc157 used in the symmetric70_proto/promicro hardware.

## Current performance

### Without fast `matrix_read_cols_on_rows() in users/mtei/`

* Measurement with QMK 0.17.0

| MCU               | execution time of `matrix_scan()` | matrix scan rate |
|-------------------|---------------|----------------|
| Pro Micro (16MHz) | 588.7 us      | 1539 scans/sec (649.9us) |
| Proton C (72MHz)  | 274.7 us      | 3448 scans/sec (290us) |

### With fast `matrix_read_cols_on_rows() in users/mtei/`

* Measurement with QMK 0.17.0

| MCU               | execution time of `matrix_scan()` | matrix scan rate |
|-------------------|---------------|----------------|
| Pro Micro (16MHz) | 92.25 us      |  6536 scans/sec (153us)  |
| Proton C (72MHz)  | 55.25 us      | 14192 scans/sec (70.46us)|

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
  * `make CANCEL_BOOST=yes MTEST=[<other options>...] handwired/symmetric70_proto/promicro/boost:default:flash`

## Measurement result
### Pro Micro (ATmega32u4 16Mhz)
#### Default setting (without fast `matrix_read_cols_on_rows()`)
 - `make CANCEL_BOOST=yes MTEST=matrix_debug_scan,matrix_debug_delay handwired/symmetric70_proto/promicro/boost:default:flash`

<img width="80%" alt="sym70_normal_promicro" src="https://user-images.githubusercontent.com/2170248/179529297-80b0a96f-0f7b-4822-811b-4a13055088af.png">

#### Default setting (with fast `matrix_read_cols_on_rows()`)
 - `make MTEST=matrix_debug_scan,matrix_debug_delay handwired/symmetric70_proto/promicro/boost:default:flash`

<img width="80%" alt="sym70_fastread_promicro" src="https://user-images.githubusercontent.com/2170248/179529392-8a5693da-b8a7-4368-bf74-ffa58556ba1e.png">

### Proton C (STM32F303 72MHz)
#### Default setting (without fast `matrix_read_cols_on_rows()`)
 - `make CANCEL_BOOST=yes MTEST=matrix_debug_scan,matrix_debug_delay handwired/symmetric70_proto/proton_c/boost:default:flash`

<img width="80%" alt="sym70_normal_re_proton" src="https://user-images.githubusercontent.com/2170248/179954224-9ba65cc6-1136-42ee-bb8e-94d936d33071.png">

#### Default setting (with fast `matrix_read_cols_on_rows()`)
 - `make MTEST=matrix_debug_scan,matrix_debug_delay handwired/symmetric70_proto/proton_c/boost:default:flash`

<img width="80%" alt="sym70_fastread_re_proton" src="https://user-images.githubusercontent.com/2170248/179955112-0a077c82-0a79-4f1e-ba77-ba3318a7eac5.png">

##### Press R0C5, R1C5, R2C5, R3C5, R4C5 keys

<img width="80%" alt="sym70_fastread_re_proton_C5" src="https://user-images.githubusercontent.com/2170248/179964744-00a4b986-d7ab-4fd3-87bc-8c57e2032640.png">

##### Connect a 500pF capacitor between C5 line and GND, Press R0C5, R1C5, R2C5, R3C5, R4C5 keys

<img width="80%" alt="sym70_fastread_re_proton_500pF" src="https://user-images.githubusercontent.com/2170248/179964834-0f9862d6-bebe-4316-a173-ac5976ae9733.png">

 ##### Connect a 1000pF capacitor between C5 line and GND, Press R0C5, R1C5, R2C5, R3C5, R4C5 keys

<img width="80%" alt="sym70_fastread_re_proton_1000pF" src="https://user-images.githubusercontent.com/2170248/179964925-f876ab55-7276-47b3-af3b-d255d6a1bd18.png">
