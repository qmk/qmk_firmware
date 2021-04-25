# Debug version matrix.c

This matrix.c is quantum/matrix.c with the following additions:

* Added the MATRIX_DEBUG_SCAN_{START/END} macro to measure the execution time of matrix_scan().
* Added the MATRIX_DEBUG_DELAY_{START/END} macro to measure delay time.
* Added the MATRIX_MUL_SELECT handling for symmetric70_proto.

## Compile

* Set MATRIX_IO_DELAY value
  `make MTEST=mdelay0 symmetric70_proto/promicro:default:flash`
  `make MTEST=mdelay1 symmetric70_proto/promicro:default:flash`
  `make MTEST=mdelay2 symmetric70_proto/promicro:default:flash`
  `make MTEST=mdelay3 symmetric70_proto/promicro:default:flash`
  `make MTEST=mdelay4 symmetric70_proto/promicro:default:flash`
  `make MTEST=mdelay5 symmetric70_proto/promicro:default:flash`
  `make MTEST=mdelay10 symmetric70_proto/promicro:default:flash`
  `make MTEST=mdelay20 symmetric70_proto/promicro:default:flash`
  `make MTEST=mdelay30 symmetric70_proto/promicro:default:flash`
* Measure the execution time of matrix_scan()
  `make MTEST=matrix_debug_scan[,<other options>..] symmetric70_proto/promicro:default:flash`
* Measure delay time.
  `make MTEST=matrix_debug_delay[,<other options>..] symmetric70_proto/promicro:default:flash`
* Change the behavior of delay
  `make MTEST=matrix_debug_delay,allways_delay symmetric70_proto/promicro:default:flash`
  `make MTEST=matrix_debug_delay,adaptive_delay,mdelay0 symmetric70_proto/promicro:default:flash`
