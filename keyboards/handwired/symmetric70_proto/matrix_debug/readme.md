# Debug version matrix.c

This matrix.c is quantum/matrix.c with the following additions:

* Added the MATRIX_DEBUG_SCAN_{START/END} macro to measure the execution time of matrix_scan().
* Added the MATRIX_DEBUG_DELAY_{START/END} macro to measure delay time.
* Added the MATRIX_MUL_SELECT handling for symmetric70_proto.

## Compile

* Set MATRIX_IO_DELAY value
  * `make MTEST=mdelay0 handwired/symmetric70_proto/promicro:default:flash`
  * `make MTEST=mdelay1 handwired/symmetric70_proto/promicro:default:flash`
  * `make MTEST=mdelay2 handwired/symmetric70_proto/promicro:default:flash`
  * `make MTEST=mdelay3 handwired/symmetric70_proto/promicro:default:flash`
  * `make MTEST=mdelay4 handwired/symmetric70_proto/promicro:default:flash`
  * `make MTEST=mdelay5 handwired/symmetric70_proto/promicro:default:flash`
  * `make MTEST=mdelay10 handwired/symmetric70_proto/promicro:default:flash`
  * `make MTEST=mdelay20 handwired/symmetric70_proto/promicro:default:flash`
  * `make MTEST=mdelay30 handwired/symmetric70_proto/promicro:default:flash`
* Measure the execution time of matrix_scan()
  * `make MTEST=matrix_debug_scan[,<other options>..] handwired/symmetric70_proto/promicro:default:flash`
* Measure delay time.
  * `make MTEST=matrix_debug_delay[,<other options>..] handwired/symmetric70_proto/promicro:default:flash`
* Change the behavior of delay
  * `make MTEST=matrix_debug_delay,allways_delay handwired/symmetric70_proto/promicro:default:flash`
  * `make MTEST=matrix_debug_delay,adaptive_delay,mdelay0 handwired/symmetric70_proto/promicro:default:flash`

## Measurement result
### Pro Micro
#### `make MTEST=matrix_debug_scan handwired/symmetric70_proto/promicro:default:flash`
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Row 4
 - CH4: matrix_scan()
 - Execution time of matrix_scan()  503us
 - Frequency of matrix scan 1.81kHz (551.0us)
 ![DS1Z_QuickPrint2](https://user-images.githubusercontent.com/2170248/115994477-0ba64400-a612-11eb-98ba-b8cc362f26ac.png)

#### `make MTEST=matrix_debug_scan,allways_delay handwired/symmetric70_proto/promicro:default:flash`
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Row 4
 - CH4: matrix_scan()
 - Execution time of matrix_scan()  521us
 - Frequency of matrix scan 1.76kHz (568.5us)
 ![DS1Z_QuickPrint1](https://user-images.githubusercontent.com/2170248/115994488-1660d900-a612-11eb-83b1-cd820607db03.png)

#### `make MTEST=matrix_debug_scan,mdelay0,adaptive_delay handwired/symmetric70_proto/promicro:default:flash`
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Row 4
 - CH4: matrix_scan()
 - Execution time of matrix_scan()  383us
 - Frequency of matrix scan 2.32kHz (431us)
 ![DS1Z_QuickPrint3](https://user-images.githubusercontent.com/2170248/115994939-034f0880-a614-11eb-861f-b83a31efa51a.png)

#### `make MTEST=matrix_debug_delay,mdelay0,adaptive_delay handwired/symmetric70_proto/promicro:default:flash`
 Press R0C0 key
 - CH1: Row 0
 - CH2: Row 1
 - CH3: Row 4
 - CH4: delay time
 - Frequency of matrix scan 1.98kHz (505us)

Press R0C0 key  
![DS1Z_QuickPrint6](https://user-images.githubusercontent.com/2170248/115995982-7ce8f580-a618-11eb-870c-a043747d1288.png)
![DS1Z_QuickPrint5](https://user-images.githubusercontent.com/2170248/115995533-98eb9780-a616-11eb-8270-c1f145576b88.png)
