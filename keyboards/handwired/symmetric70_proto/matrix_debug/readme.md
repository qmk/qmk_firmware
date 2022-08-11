# Debug version matrix.c

This matrix.c is 0.13.19:quantum/matrix.c with the following additions:

* Added the MATRIX_DEBUG_SCAN_{START/END} macro to measure the execution time of matrix_scan().
* Added the MATRIX_DEBUG_DELAY_{START/END} macro to measure delay time.
* Added the MATRIX_MUL_SELECT handling for symmetric70_proto.

## Current performance

  | MCU               | delay type    | execution time <br> of <br> `matrix_scan()` | matrix scan rate |
  |-------------------|---------------|------------|----------------|
  | Pro Micro (16MHz) | default       | 503us      | 1810 scans/sec |
  | Pro Micro (16MHz) | adaptive      | 383us      | 2320 scans/sec |
  | Pro Micro (16MHz) | fast adaptive | 382us      | 2330 scans/sec |
  | Proton C (72MHz)  | default       | 210us      | 4350 scans/sec |
  | Proton C (72MHz)  | adaptive      | 76.4us     | 10600 scans/sec |
  | Proton C (72MHz)  | fast adaptive | 75.6us     | 10800 scans/sec |

## Compile

* Set MATRIX_IO_DELAY value
  * `make MTEST=mdelay0 handwired/symmetric70_proto/promicro/normal:default:flash`
  * `make MTEST=mdelay=1 handwired/symmetric70_proto/promicro/normal:default:flash`
  * `make MTEST=mdelay=2 handwired/symmetric70_proto/promicro/normal:default:flash`
  * `make MTEST=mdelay=3 handwired/symmetric70_proto/promicro/normal:default:flash`
  * `make MTEST=mdelay=4 handwired/symmetric70_proto/promicro/normal:default:flash`
  * `make MTEST=mdelay=5 handwired/symmetric70_proto/promicro/normal:default:flash`
  * `make MTEST=mdelay=10 handwired/symmetric70_proto/promicro/normal:default:flash`
  * `make MTEST=mdelay=20 handwired/symmetric70_proto/promicro/normal:default:flash`
  * `make MTEST=mdelay=30 handwired/symmetric70_proto/promicro/normal:default:flash`
* Measure the execution time of matrix_scan()
  * `make MTEST=matrix_debug_scan[,<other options>..] handwired/symmetric70_proto/promicro/normal:default:flash`
* Measure delay time.
  * `make MTEST=matrix_debug_delay[,<other options>..] handwired/symmetric70_proto/promicro/normal:default:flash`
* Change the behavior of delay
  * `make MTEST=matrix_debug_delay,always_delay handwired/symmetric70_proto/promicro/normal:default:flash`
  * `make MTEST=matrix_debug_delay,adaptive_delay,mdelay0 handwired/symmetric70_proto/promicro/normal:default:flash`
  * `make MTEST=matrix_debug_delay,adaptive_delay_fast,mdelay0 handwired/symmetric70_proto/promicro/normal:default:flash`

## Measurement result
### Pro Micro (ATmega32u4 16Mhz)
#### Default setting (show `matrix_scan()` time)
 - `make MTEST=matrix_debug_scan handwired/symmetric70_proto/promicro/normal:default:flash`
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Row 4
 - CH4: matrix_scan()
 - Execution time of matrix_scan()  503us
 - Frequency of matrix scan 1.81kHz (551.0us)  
   ![DS1Z_QuickPrint2](https://user-images.githubusercontent.com/2170248/115994477-0ba64400-a612-11eb-98ba-b8cc362f26ac.png)

#### Always call `matrix_output_unselect_delay()` (show `matrix_scan()` time, default MATRIX_IO_DELAY)
 - `make MTEST=matrix_debug_scan,always_delay handwired/symmetric70_proto/promicro/normal:default:flash`
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Row 4
 - CH4: matrix_scan()
 - Execution time of matrix_scan()  521us
 - Frequency of matrix scan 1.76kHz (568.5us)  
   ![DS1Z_QuickPrint1](https://user-images.githubusercontent.com/2170248/115994488-1660d900-a612-11eb-83b1-cd820607db03.png)

#### Adaptive delay (show `matrix_scan()` time, MATRIX_IO_DELAY = 0)
 - `make MTEST=matrix_debug_scan,mdelay0,adaptive_delay handwired/symmetric70_proto/promicro/normal:default:flash`
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Row 4
 - CH4: matrix_scan()
 - Execution time of matrix_scan()  383us
 - Frequency of matrix scan 2.32kHz (431us)  
   ![DS1Z_QuickPrint3](https://user-images.githubusercontent.com/2170248/115994939-034f0880-a614-11eb-861f-b83a31efa51a.png)

#### Adaptive delay (show delay time, MATRIX_IO_DELAY = 0)
 - `make MTEST=matrix_debug_delay,mdelay0,adaptive_delay handwired/symmetric70_proto/promicro/normal:default:flash`

##### Press R0C1, R1C1 key
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Row 4
 - CH4: delay time
 - Delay time 68us
 - Frequency of matrix scan 1.77kHz (565us)  
   ![DS1Z_QuickPrint55](https://user-images.githubusercontent.com/2170248/119561268-ead33900-bddf-11eb-9cc4-7e04826486cf.png)

#### Fast adaptive delay (show `matrix_scan()` time, MATRIX_IO_DELAY = 0)
 - `make MTEST=matrix_debug_scan,mdelay0,adaptive_delay_fast handwired/symmetric70_proto/promicro/normal:default:flash`
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Row 4
 - CH4: matrix_scan()
 - Execution time of matrix_scan()  382us
 - Frequency of matrix scan 2.33kHz (428us)  
   ![DS1Z_QuickPrint56](https://user-images.githubusercontent.com/2170248/119561280-eeff5680-bddf-11eb-9576-e4cf64751955.png)

#### Fast adaptive delay (show delay time, MATRIX_IO_DELAY = 0)
 - `make MTEST=matrix_debug_delay,mdelay0,adaptive_delay_fast handwired/symmetric70_proto/promicro/normal:default:flash`

##### Press R0C1, R1C1 key
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Row 4
 - CH4: delay time
 - Delay time 11us
 - Frequency of matrix scan 2.21kHz (452us)  
   ![DS1Z_QuickPrint57](https://user-images.githubusercontent.com/2170248/119561318-faeb1880-bddf-11eb-8592-694f9ecb2248.png)

### Proton C (STM32F303 72MHz)
#### Default setting (show `matrix_scan()` time)
 - `make MTEST=matrix_debug_scan handwired/symmetric70_proto/proton_c/normal:default:flash`
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Row 4
 - CH4: matrix_scan()
 - Execution time of matrix_scan()  210us
 - Frequency of matrix scan 4.35kHz (230.0us)  
   ![DS1Z_QuickPrint16](https://user-images.githubusercontent.com/2170248/116131295-2ad2cd80-a707-11eb-8d0a-6f7912456e03.png)

#### Always call `matrix_output_unselect_delay()` (show `matrix_scan()` time, default MATRIX_IO_DELAY)
 - `make MTEST=matrix_debug_scan,always_delay handwired/symmetric70_proto/proton_c/normal:default:flash`
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Row 4
 - CH4: matrix_scan()
 - Execution time of matrix_scan()  242us
 - Frequency of matrix scan 3.85kHz (260.0us)  
   ![DS1Z_QuickPrint17](https://user-images.githubusercontent.com/2170248/116131308-31f9db80-a707-11eb-8db7-d1960fa7b068.png)

#### Adaptive delay (show `matrix_scan()` time, MATRIX_IO_DELAY = 0)
 - `make MTEST=matrix_debug_scan,mdelay0,adaptive_delay handwired/symmetric70_proto/proton_c/normal:default:flash`
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Row 4
 - CH4: matrix_scan()
 - Execution time of matrix_scan()  76.4us
 - Frequency of matrix scan 10.6kHz (94.4us)  
   ![DS1Z_QuickPrint18](https://user-images.githubusercontent.com/2170248/116131369-44741500-a707-11eb-9c74-fa39d9e80947.png)

#### Adaptive delay (show delay time, MATRIX_IO_DELAY = 0)
 - `make MTEST=matrix_debug_delay,mdelay0,adaptive_delay handwired/symmetric70_proto/proton_c/normal:default:flash`

##### Press R0C1, R1C1 key
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Row 4
 - CH4: delay time
 - Delay time 7.6us
 - Frequency of matrix scan 9.47kHz (105.6us)  
   ![DS1Z_QuickPrint58](https://user-images.githubusercontent.com/2170248/119666783-a3e15400-be70-11eb-9a58-220032117efd.png)

##### Connect a 500pF capacitor between C2 line and GND, Press R0C2, R1C2, R2C2, R3C2, R4C2 keys
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Col 2
 - CH4: delay time
 - Delay time 12us + alpha
 - Frequency of matrix scan 5.45kHz (183us)
 - Threshold Voltage 1.9V  
   ![DS1Z_QuickPrint59](https://user-images.githubusercontent.com/2170248/119666946-cc694e00-be70-11eb-9b97-4c500416d774.png)

##### Connect a 1000pF capacitor between C2 line and GND, Press R0C2, R1C2, R2C2, R3C2, R4C2 keys
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Col 2
 - CH4: delay time
 - Delay time 20us + alpha
 - Frequency of matrix scan 4.48kHz (223us)
 - Threshold Voltage 1.9V  
   ![DS1Z_QuickPrint60](https://user-images.githubusercontent.com/2170248/119667127-f3c01b00-be70-11eb-8e7f-6f0a81f95e97.png)

#### Fast adaptive delay (show `matrix_scan()` time, MATRIX_IO_DELAY = 0)
 - `make MTEST=matrix_debug_scan,mdelay0,adaptive_delay_fast handwired/symmetric70_proto/proton_c/normal:default:flash`
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Row 4
 - CH4: matrix_scan()
 - Execution time of matrix_scan()  75.6us
 - Frequency of matrix scan 10.8kHz (92.2us)  
   ![DS1Z_QuickPrint62](https://user-images.githubusercontent.com/2170248/119667218-0b979f00-be71-11eb-946c-16f0a0454056.png)

#### Fast adaptive delay (show delay time, MATRIX_IO_DELAY = 0)
 - `make MTEST=matrix_debug_delay,mdelay0,adaptive_delay_fast handwired/symmetric70_proto/proton_c/normal:default:flash`

##### Press R0C1, R1C1 key
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Row 4
 - CH4: delay time
 - Delay time 1.6us
 - Frequency of matrix scan 10.6kHz (94.4us)  
   ![DS1Z_QuickPrint63](https://user-images.githubusercontent.com/2170248/119667378-33870280-be71-11eb-95aa-64213138ddac.png)
   ![DS1Z_QuickPrint64](https://user-images.githubusercontent.com/2170248/119667504-52859480-be71-11eb-963e-eebc6e3da9dc.png)

##### Connect a 500pF capacitor between C2 line and GND, Press R0C2, R1C2, R2C2, R3C2, R4C2 keys
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Col 2
 - CH4: delay time
 - Delay time 13.2us
 - Frequency of matrix scan 6.58kHz (152.6us)
 - Threshold Voltage 1.9V  
   ![DS1Z_QuickPrint65](https://user-images.githubusercontent.com/2170248/119667644-72b55380-be71-11eb-8030-854de1900408.png)

##### Connect a 1000pF capacitor between C2 line and GND, Press R0C2, R1C2, R2C2, R3C2, R4C2 keys
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Col 2
 - CH4: delay time
 - Delay time 20us
 - Frequency of matrix scan 5.30kHz (188.8us)
 - Threshold Voltage 1.9V  
   ![DS1Z_QuickPrint66](https://user-images.githubusercontent.com/2170248/119667785-8f518b80-be71-11eb-8d40-fc3293aa072b.png)
