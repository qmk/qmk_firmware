# Fast and extensible matrix.c

This matrix.c is faster and more extensible than the standard quantum/matrix.c.

* The execution speed of the `matrix_scan()` function is several times faster than quantum/matrix.c.
* In addition to handling MCU GPIOs, it can be extended to handle I/O extenders.

## ToDo list
- [x] support Pro Micro
- [x] support Proton-C
- [x] support DIRECT_PINS
- [x] support DIODE_DIRECTION == ROW2COL
- [x] support 74HC157: quadruple 2-line to 1-line data selectors / multiplexers
- [x] support 74HC153: dual 4-line to 1-line data selectors / multiplexers
- [ ] support I/O expander (MCP23018)
- [ ] support MCU & I/O expander (MCP23018) mixture like ErgoDox

## Current performance

  | MCU               | delay type    | execution time <br> of <br> `matrix_scan()` | matrix scan rate |
  |-------------------|---------------|------------|-----------------|
  | Pro Micro (16MHz) | fast adaptive | 75.6us     |  8090 scans/sec |
  | Proton C (72MHz)  | fast adaptive | 49.8us     | 15100 scans/sec |

## Configuration

This matrix.c requires a different configuration than quantum/matrix.c.

### Output pins configuration

The output pins is the Row pins if `DIODE_DIRECTION == COL2ROW`, and the Col pins if `DIODE_DIRECTION == ROW2COL`. When DIRECT_PINS is defined, the output pins do not need to be set.

Example:
```c
// list of OUTPUT(row) ports
#define MATRIX_OUT_PORTS  \
    (Port_D, MCU_GPIO, D0), \
    (Port_C, MCU_GPIO, C0), \
    (Port_E, MCU_GPIO, E0), \
    (Port_B, MCU_GPIO, B0)
// list of OUTPUT pins
#define MATRIX_OUT_PINS  \
    (0, Port_D, 4), \
    (1, Port_C, 6), \
    (2, Port_D, 7), \
    (3, Port_E, 6), \
    (4, Port_B, 4), \
    (5, Port_B, 5)
```

### Input pins configuration

The input pins is the Col pins if `DIODE_DIRECTION == COL2ROW`, and the Row pins if `DIODE_DIRECTION == ROW2COL`. When DIRECT_PINS is defined, the input pin settings will enumerate the connection pins of all switches.

Example:
```c
// list of INPUT ports
#define MATRIX_IN_PORTS (Port_F, MCU_GPIO, F0), (Port_B, MCU_GPIO, B0)
// list of INPUT pins
#define MATRIX_IN_PINS \
    (0, Port_F, 4), \
    (1, Port_F, 5), \
    (2, Port_F, 6), \
    (3, Port_F, 7), \
    (4, Port_B, 1), \
    (5, Port_B, 3)
```

### Multiplexer Extension

By defining the `MATRIX_EXTENSION_74HC157` macro or `MATRIX_EXTENSION_74HC153` macro, you can connect a multiplexer to the GPIO to extend the input pins.

Example:
```c
#define MATRIX_EXTENSION_74HC157 B2 /* or #define MATRIX_EXTENSION_74HC153 B2, B6 */

// list of OUTPUT ports
#define MATRIX_OUT_PORTS (Port_D, MCU_GPIO, D0), (Port_C, MCU_GPIO, C0), (Port_E, MCU_GPIO, E0), (Port_B, MCU_GPIO, B0)
// list of OUTPUT pins
#define MATRIX_OUT_PINS  (0, Port_D, 4), (1, Port_C, 6), (2, Port_D, 7), (3, Port_E, 6), (4, Port_B, 4), (5, Port_B, 5)

// list of INPUT ports
#define MATRIX_IN_PORTS \
    (Port_Fa, MCU_GPIOa, F0), \
    (Port_Ba, MCU_GPIOa, B0), \
    (Port_Fb, MCU_GPIOb, F0), \
    (Port_Bb, MCU_GPIOb, B0)
// list of INPUT pins
#define MATRIX_IN_PINS \
    (0, Port_Fa, 4), \
    (1, Port_Fb, 5), \
    (2, Port_Fb, 6), \
    (3, Port_Fa, 7), \
    (4, Port_Ba, 1), \
    (5, Port_Bb, 3)
```

### I/O expander Extension

I plan to provide extensions to support I/O expanders such as MCP23018 and PCA9555.

## Compile

* Measure the execution time of matrix_scan()
  * `make MTEST=matrix_debug_scan[,<other options>..] handwired/symmetric70_proto/promicro/fast:default:flash`
* Measure delay time.
  * `make MTEST=matrix_debug_delay[,<other options>..] handwired/symmetric70_proto/promicro/fast:default:flash`

## Measurement result
### Pro Micro (ATmega32u4 16Mhz)
#### Default setting (show `matrix_scan()` time)
 - `make MTEST=matrix_debug_scan handwired/symmetric70_proto/promicro/fast:default:flash`
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Row 4
 - CH4: matrix_scan()
 - Execution time of matrix_scan()  75.6us
 - Frequency of matrix scan 8.09kHz (123.6us)
 ![DS1Z_QuickPrint7](https://user-images.githubusercontent.com/2170248/116003927-538d9100-a63b-11eb-9b36-7db47d9b1541.png)

#### Default setting (show delay time)
 - `make MTEST=matrix_debug_delay handwired/symmetric70_proto/promicro/fast:default:flash`
##### Press R0C0 key
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Row 4
 - CH4: delay time
 - Frequency of matrix scan 7.84kHz (127.6us)

![DS1Z_QuickPrint9](https://user-images.githubusercontent.com/2170248/116003974-99e2f000-a63b-11eb-9c9e-3b3b1025db66.png)
![DS1Z_QuickPrint10](https://user-images.githubusercontent.com/2170248/116003978-a1a29480-a63b-11eb-97d8-5a6e11c0db2f.png)

### Proton C
#### Default setting (show `matrix_scan()` time)
 - `make MTEST=matrix_debug_scan handwired/symmetric70_proto/proton_c/fast:default:flash`
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Row 4
 - CH4: matrix_scan()
 - Execution time of matrix_scan()  49.8us
 - Frequency of matrix scan 15.1kHz (66.2.6us)

![DS1Z_QuickPrint11](https://user-images.githubusercontent.com/2170248/116088141-8cca0d80-a6dc-11eb-8782-1d29c57690b8.png)

#### Default setting (show delay time)
 - `make MTEST=matrix_debug_delay handwired/symmetric70_proto/proton_c/fast:default:flash`
##### Press R0C0 key
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Row 4
 - CH4: delay time
 - Frequency of matrix scan 13.9kHz (71.8us)

![DS1Z_QuickPrint12](https://user-images.githubusercontent.com/2170248/116088247-a8cdaf00-a6dc-11eb-8a47-104694a40117.png)
![DS1Z_QuickPrint13](https://user-images.githubusercontent.com/2170248/116088262-ac613600-a6dc-11eb-804c-7dcbd71c83d5.png)

##### Connect a 500pF capacitor between C0 line and GND, Press R0C0, R1C0, R2C0,  R3C0,  R4C0 keys
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Col 0
 - CH4: delay time
 - Delay time 11.6us
 - Threshold Voltage 1.9V

![DS1Z_QuickPrint14](https://user-images.githubusercontent.com/2170248/116089205-90aa5f80-a6dd-11eb-89c4-72315c80ba0e.png)

##### Connect a 1000pF capacitor between C0 line and GND, Press R0C0, R1C0, R2C0,  R3C0,  R4C0 keys
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Col 0
 - CH4: delay time
 - Delay time 18.6us
 - Threshold Voltage 1.9V

![DS1Z_QuickPrint15](https://user-images.githubusercontent.com/2170248/116089229-96a04080-a6dd-11eb-8b63-f91b03a9db0c.png)
