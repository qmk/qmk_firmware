# Debug version matrix.c

This matrix.c is quantum/matrix.c with the following additions:

* Added the MATRIX_DEBUG_SCAN_{START/END} macro to measure the execution time of matrix_scan().
* Added the MATRIX_DEBUG_DELAY_{START/END} macro to measure delay time.
* Added the MATRIX_MUL_SELECT handling for symmetric70_proto.

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
  * `make MTEST=matrix_debug_delay,allways_delay handwired/symmetric70_proto/promicro/normal:default:flash`
  * `make MTEST=matrix_debug_delay,adaptive_delay,mdelay0 handwired/symmetric70_proto/promicro/normal:default:flash`

## Measurement result
### Pro Micro
#### `make MTEST=matrix_debug_scan handwired/symmetric70_proto/promicro/normal:default:flash`
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Row 4
 - CH4: matrix_scan()
 - Execution time of matrix_scan()  503us
 - Frequency of matrix scan 1.81kHz (551.0us)
 ![DS1Z_QuickPrint2](https://user-images.githubusercontent.com/2170248/115994477-0ba64400-a612-11eb-98ba-b8cc362f26ac.png)

#### `make MTEST=matrix_debug_scan,allways_delay handwired/symmetric70_proto/promicro/normal:default:flash`
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Row 4
 - CH4: matrix_scan()
 - Execution time of matrix_scan()  521us
 - Frequency of matrix scan 1.76kHz (568.5us)
 ![DS1Z_QuickPrint1](https://user-images.githubusercontent.com/2170248/115994488-1660d900-a612-11eb-83b1-cd820607db03.png)

#### `make MTEST=matrix_debug_scan,mdelay0,adaptive_delay handwired/symmetric70_proto/promicro/normal:default:flash`
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Row 4
 - CH4: matrix_scan()
 - Execution time of matrix_scan()  383us
 - Frequency of matrix scan 2.32kHz (431us)
 ![DS1Z_QuickPrint3](https://user-images.githubusercontent.com/2170248/115994939-034f0880-a614-11eb-861f-b83a31efa51a.png)

#### `make MTEST=matrix_debug_delay,mdelay0,adaptive_delay handwired/symmetric70_proto/promicro/normal:default:flash`
##### Press R0C0 key
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Row 4
 - CH4: delay time
 - Frequency of matrix scan 1.98kHz (505us)

![DS1Z_QuickPrint6](https://user-images.githubusercontent.com/2170248/115995982-7ce8f580-a618-11eb-870c-a043747d1288.png)
![DS1Z_QuickPrint5](https://user-images.githubusercontent.com/2170248/115995533-98eb9780-a616-11eb-8270-c1f145576b88.png)

### Proton C
#### `make MTEST=matrix_debug_scan handwired/symmetric70_proto/proton_c/normal:default:flash`
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Row 4
 - CH4: matrix_scan()
 - Execution time of matrix_scan()  210us
 - Frequency of matrix scan 4.35kHz (230.0us)

![DS1Z_QuickPrint16](https://user-images.githubusercontent.com/2170248/116131295-2ad2cd80-a707-11eb-8d0a-6f7912456e03.png)

#### `make MTEST=matrix_debug_scan,allways_delay handwired/symmetric70_proto/proton_c/normal:default:flash`
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Row 4
 - CH4: matrix_scan()
 - Execution time of matrix_scan()  242us
 - Frequency of matrix scan 3.85kHz (260.0us)

![DS1Z_QuickPrint17](https://user-images.githubusercontent.com/2170248/116131308-31f9db80-a707-11eb-8db7-d1960fa7b068.png)

#### `make MTEST=matrix_debug_scan,mdelay0,adaptive_delay handwired/symmetric70_proto/proton_c/normal:default:flash`
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Row 4
 - CH4: matrix_scan()
 - Execution time of matrix_scan()  76.4us
 - Frequency of matrix scan 10.6kHz (94.4us)

![DS1Z_QuickPrint18](https://user-images.githubusercontent.com/2170248/116131369-44741500-a707-11eb-9c74-fa39d9e80947.png)

#### `make MTEST=matrix_debug_delay,mdelay0,adaptive_delay handwired/symmetric70_proto/proton_c/normal:default:flash`

##### Press R0C0 key
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Row 4
 - CH4: delay time
 - Delay time 7us
 - Frequency of matrix scan 9.6kHz (104.2us)

![DS1Z_QuickPrint19](https://user-images.githubusercontent.com/2170248/116131414-55bd2180-a707-11eb-9cb4-29ee25407c3b.png)
![DS1Z_QuickPrint20](https://user-images.githubusercontent.com/2170248/116131443-5ce42f80-a707-11eb-847f-932949a7ddc3.png)

##### Connect a 500pF capacitor between C0 line and GND, Press R0C0, R1C0, R2C0,  R3C0,  R4C0 keys
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Col 0
 - CH4: delay time
 - Delay time 12us
 - Threshold Voltage 1.9V

![DS1Z_QuickPrint21](https://user-images.githubusercontent.com/2170248/116131494-6c637880-a707-11eb-8efd-2088a6091892.png)

##### Connect a 1000pF capacitor between C0 line and GND, Press R0C0, R1C0, R2C0,  R3C0,  R4C0 keys
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Col 0
 - CH4: delay time
 - Delay time 19.6us
 - Threshold Voltage 1.9V

![DS1Z_QuickPrint22](https://user-images.githubusercontent.com/2170248/116131520-74231d00-a707-11eb-9812-ef6a38f99feb.png)
