# group `group_sam0_utils` {#group__group__sam0__utils}

Compiler abstraction layer and code utilities for Cortex-M0+ based Atmel SAM devices. This module provides various abstraction layers and utilities to make code compatible between different compilers.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`define `[`UNUSED`](#group__group__sam0__utils_1gada67c62b1c57e07efa04431bc40b9238)            | Marking *v* as a unused parameter or value.
`define `[`barrier`](#group__group__sam0__utils_1ga53290ac2df2384738b8769c76622f803)            | Memory barrier.
`define `[`COMPILER_PRAGMA`](#group__group__sam0__utils_1ga85a3ab5701281268521f109ed0078668)            | Emit the compiler pragma *arg*.
`define `[`COMPILER_PACK_SET`](#group__group__sam0__utils_1gae2c02ff865ca6538b4b1bddbf2a6876c)            | Set maximum alignment for subsequent struct and union definitions to *alignment*.
`define `[`COMPILER_PACK_RESET`](#group__group__sam0__utils_1ga38d28b622a4bc7b0f3fb2be2ef1e0086)            | Set default alignment for subsequent struct and union definitions.
`define `[`Assert`](#group__group__sam0__utils_1gaab1e54dcc40192f9704e8b252635450f)            | This macro is used to test fatal errors.
`define `[`Long_call`](#group__group__sam0__utils_1ga5b759626f343cc1af9159cc02b763837)            | Calls the routine at address *addr*.
`define `[`div_ceil`](#group__group__sam0__utils_1ga6d4ebd841bc96041a7f3a61e227c1fb2)            | Calculate $ \left\lceil \frac{a}{b} \right\rceil $ using integer arithmetic.
`define `[`FUNC_PTR`](#group__group__sam0__utils_1gacce64924b686dd08a83042b35d0d1480)            | 
`define `[`unused`](#group__group__sam0__utils_1ga417dba7f63dde98dbebd6336d8af9d91)            | Marking *v* as a unused parameter or value.
`define `[`MSB`](#group__group__sam0__utils_1gabee1b74eceef5a0cf26efbf3ff87ccbf)            | Most significant byte of *u16*.
`define `[`LSB`](#group__group__sam0__utils_1gabd2fa7b756342ae251e3a7a66670c2fe)            | Least significant byte of *u16*.
`define `[`MSH`](#group__group__sam0__utils_1ga2e9046f49816ad27148660f5ba993696)            | Most significant half-word of *u32*.
`define `[`LSH`](#group__group__sam0__utils_1gae79954742b5a668ce83ab79ac9d9804b)            | Least significant half-word of *u32*.
`define `[`MSB0W`](#group__group__sam0__utils_1ga25110f05bdb5b5ea3fcb2854a1a07d7a)            | Most significant byte of 1st rank of *u32*.
`define `[`MSB1W`](#group__group__sam0__utils_1ga0f90ecd0b0f0e15608a95b8367b77ece)            | Most significant byte of 2nd rank of *u32*.
`define `[`MSB2W`](#group__group__sam0__utils_1ga0207e10a3c4bcca172463cd5e3ebd865)            | Most significant byte of 3rd rank of *u32*.
`define `[`MSB3W`](#group__group__sam0__utils_1gad6ab5ac6e3e95525d56d757c9718e352)            | Most significant byte of 4th rank of *u32*.
`define `[`LSB3W`](#group__group__sam0__utils_1ga04e75e548b33b9cc22699b4249ff6c64)            | Least significant byte of 4th rank of *u32*.
`define `[`LSB2W`](#group__group__sam0__utils_1gad8fda97f8caa00fcfa84f712ee7627d6)            | Least significant byte of 3rd rank of *u32*.
`define `[`LSB1W`](#group__group__sam0__utils_1ga84cbbcad1971cdb2987418e6ae6cb4ff)            | Least significant byte of 2nd rank of *u32*.
`define `[`LSB0W`](#group__group__sam0__utils_1ga2ca8582260a8ada6cdd457cf37ba37a7)            | Least significant byte of 1st rank of *u32*.
`define `[`MSW`](#group__group__sam0__utils_1gad71e5e84d2cec4387415a55f5c62b01b)            | Most significant word of *u64*.
`define `[`LSW`](#group__group__sam0__utils_1ga0633993fb1f2d96a56385f09beed7bc7)            | Least significant word of *u64*.
`define `[`MSH0`](#group__group__sam0__utils_1ga280d6a94884872f6a5be80c873e8adc1)            | Most significant half-word of 1st rank of *u64*.
`define `[`MSH1`](#group__group__sam0__utils_1ga43de4fac62f938ff4eb448a87522ec0e)            | Most significant half-word of 2nd rank of *u64*.
`define `[`MSH2`](#group__group__sam0__utils_1ga5d32ec744212194c8106c51b89a5dfe9)            | Most significant half-word of 3rd rank of *u64*.
`define `[`MSH3`](#group__group__sam0__utils_1gabb233f238b63c12d2ff361d9ddb3114b)            | Most significant half-word of 4th rank of *u64*.
`define `[`LSH3`](#group__group__sam0__utils_1ga1ec33d340ef17c91cb0530d00ccb0ea8)            | Least significant half-word of 4th rank of *u64*.
`define `[`LSH2`](#group__group__sam0__utils_1ga2efccfe683ebf7d89a972fbbdea2c26d)            | Least significant half-word of 3rd rank of *u64*.
`define `[`LSH1`](#group__group__sam0__utils_1gac593b0be4555d883b4297b45cffc4168)            | Least significant half-word of 2nd rank of *u64*.
`define `[`LSH0`](#group__group__sam0__utils_1ga3026b9288b45a9794fd3eb585cbe10bc)            | Least significant half-word of 1st rank of *u64*.
`define `[`MSB0D`](#group__group__sam0__utils_1ga5f24ecf381776ee415991a545a05e4c7)            | Most significant byte of 1st rank of *u64*.
`define `[`MSB1D`](#group__group__sam0__utils_1ga97a0ab6790df95cb4d8021d8850487f8)            | Most significant byte of 2nd rank of *u64*.
`define `[`MSB2D`](#group__group__sam0__utils_1gad4ceacba543e7b8617ca4bd075abb146)            | Most significant byte of 3rd rank of *u64*.
`define `[`MSB3D`](#group__group__sam0__utils_1gaf7972d3282ec9ecb97afa34e848ede2c)            | Most significant byte of 4th rank of *u64*.
`define `[`MSB4D`](#group__group__sam0__utils_1ga1c891624c33b13808633af8dbcaafa5f)            | Most significant byte of 5th rank of *u64*.
`define `[`MSB5D`](#group__group__sam0__utils_1ga5e61db58aaf5cbb3051240cdcb1b5147)            | Most significant byte of 6th rank of *u64*.
`define `[`MSB6D`](#group__group__sam0__utils_1gacb8062d046ca06f5c28c9a015997494b)            | Most significant byte of 7th rank of *u64*.
`define `[`MSB7D`](#group__group__sam0__utils_1ga0cbce69964fa2dd7bf05911d0b99b014)            | Most significant byte of 8th rank of *u64*.
`define `[`LSB7D`](#group__group__sam0__utils_1ga79fb849e13082fdd4adb02debbad7f1a)            | Least significant byte of 8th rank of *u64*.
`define `[`LSB6D`](#group__group__sam0__utils_1gab90afefaf3b5cb2507ab3c496d8f643c)            | Least significant byte of 7th rank of *u64*.
`define `[`LSB5D`](#group__group__sam0__utils_1gac379acb246797736332fa1b8ae481b34)            | Least significant byte of 6th rank of *u64*.
`define `[`LSB4D`](#group__group__sam0__utils_1gaab745f30b9b841f9ccd9ace0a5a1a9e5)            | Least significant byte of 5th rank of *u64*.
`define `[`LSB3D`](#group__group__sam0__utils_1ga99213c01b979c347950eba4277f0499a)            | Least significant byte of 4th rank of *u64*.
`define `[`LSB2D`](#group__group__sam0__utils_1gaba3bea07dcc4a37039b7effd4da03b9e)            | Least significant byte of 3rd rank of *u64*.
`define `[`LSB1D`](#group__group__sam0__utils_1ga42179f159b798116eb615102a549aa85)            | Least significant byte of 2nd rank of *u64*.
`define `[`LSB0D`](#group__group__sam0__utils_1ga2e20f5ef87ccf0ad44c1d49d6ffd80a3)            | Least significant byte of 1st rank of *u64*.
`define `[`LSB0`](#group__group__sam0__utils_1ga844ec34df36feb927dc92007af14674a)            | Least significant byte of 1st rank of *u32*.
`define `[`LSB1`](#group__group__sam0__utils_1ga2d1e45154b07481f0579ecc725e4edff)            | Least significant byte of 2nd rank of *u32*.
`define `[`LSB2`](#group__group__sam0__utils_1ga8967f5ae0174b01ce44c502ebd14035a)            | Least significant byte of 3rd rank of *u32*.
`define `[`LSB3`](#group__group__sam0__utils_1ga5d9ff393e7c8764112a1167db19b16b1)            | Least significant byte of 4th rank of *u32*.
`define `[`MSB3`](#group__group__sam0__utils_1gaeeb8918fc580ce01d45f71863eebff90)            | Most significant byte of 4th rank of *u32*.
`define `[`MSB2`](#group__group__sam0__utils_1ga8683254be29bcfe3cf2fa646890d3942)            | Most significant byte of 3rd rank of *u32*.
`define `[`MSB1`](#group__group__sam0__utils_1ga3facab9f8ebf70ad6e16038465e2bedc)            | Most significant byte of 2nd rank of *u32*.
`define `[`MSB0`](#group__group__sam0__utils_1gafb81783b8186acd7182a971048b0c6b3)            | Most significant byte of 1st rank of *u32*.
`define `[`FLASH_DECLARE`](#group__group__sam0__utils_1ga9b84ecc6b34a71f797ceb8b8f7b8d384)            | 
`define `[`FLASH_EXTERN`](#group__group__sam0__utils_1gaaef0fd990bb5bd9cdf11334f7c689fd7)            | 
`define `[`PGM_READ_BYTE`](#group__group__sam0__utils_1gafe9b83c73d4840986478ec67d3eb7718)            | 
`define `[`PGM_READ_WORD`](#group__group__sam0__utils_1ga92576bffe51090dcb6d5c67e07b9eec7)            | 
`define `[`MEMCPY_ENDIAN`](#group__group__sam0__utils_1ga85a7d71a016789b1766f9b27d0530347)            | 
`define `[`PGM_READ_BLOCK`](#group__group__sam0__utils_1ga8900e4615b7d7143a6c38e2a39087538)            | 
`define `[`CMD_ID_OCTET`](#group__group__sam0__utils_1gabf2b95fa77301377cdcf79eb615551db)            | 
`define `[`CPU_ENDIAN_TO_LE16`](#group__group__sam0__utils_1ga7c15ca0f3159182efc4b80a00768c2c0)            | 
`define `[`CPU_ENDIAN_TO_LE32`](#group__group__sam0__utils_1gaa2fd4bfb7af44220ce4205e2aa371017)            | 
`define `[`CPU_ENDIAN_TO_LE64`](#group__group__sam0__utils_1ga6f1e86f452c8f327f9ca96cbf6a65c81)            | 
`define `[`LE16_TO_CPU_ENDIAN`](#group__group__sam0__utils_1gaceb02fdef243c22d2559e260185fb579)            | 
`define `[`LE32_TO_CPU_ENDIAN`](#group__group__sam0__utils_1ga2df63369ef525ba98832132ce5a43346)            | 
`define `[`LE64_TO_CPU_ENDIAN`](#group__group__sam0__utils_1gab675071ce5a4644b205cdbc858417ccd)            | 
`define `[`CLE16_TO_CPU_ENDIAN`](#group__group__sam0__utils_1ga4ac6e032d1ce0ae6d2e460da93ce8732)            | 
`define `[`CLE32_TO_CPU_ENDIAN`](#group__group__sam0__utils_1ga3ff07a7496222efe8bc7d7b7b0342b0d)            | 
`define `[`CLE64_TO_CPU_ENDIAN`](#group__group__sam0__utils_1gacbbba93256e2d892c748d56a42f00f9b)            | 
`define `[`CCPU_ENDIAN_TO_LE16`](#group__group__sam0__utils_1ga5fd2d3ed2fc9234277b659b67d33bc64)            | 
`define `[`CCPU_ENDIAN_TO_LE32`](#group__group__sam0__utils_1ga1e3290451e5c7b98175911c9219b5123)            | 
`define `[`CCPU_ENDIAN_TO_LE64`](#group__group__sam0__utils_1ga00483bf27ea1e8a2143c6baf22b31f16)            | 
`define `[`ADDR_COPY_DST_SRC_16`](#group__group__sam0__utils_1gac4609178e5c825e815f44fa123dcaaf7)            | 
`define `[`ADDR_COPY_DST_SRC_64`](#group__group__sam0__utils_1ga0454afa80924c2183c8c672c043440cc)            | 
`public inline static void `[`convert_64_bit_to_byte_array`](#group__group__sam0__utils_1gadca7cebb159c7ed180d3d07cccb74245)`(uint64_t value,uint8_t * data)`            | Converts a 64-Bit value into a 8 Byte array.
`public inline static void `[`convert_16_bit_to_byte_array`](#group__group__sam0__utils_1ga2de8d131d6afca8b368486f56c911e75)`(uint16_t value,uint8_t * data)`            | Converts a 16-Bit value into a 2 Byte array.
`public inline static void `[`convert_spec_16_bit_to_byte_array`](#group__group__sam0__utils_1gaa9724d81bfe44a06b0372d144cd98e36)`(uint16_t value,uint8_t * data)`            | 
`public inline static void `[`convert_16_bit_to_byte_address`](#group__group__sam0__utils_1ga9634f2d7292e1209fe3b83254a66c450)`(uint16_t value,uint8_t * data)`            | 
`public inline static uint16_t `[`convert_byte_array_to_16_bit`](#group__group__sam0__utils_1gad3726f56d0820acc7bae83993bd8897c)`(uint8_t * data)`            | 
`public inline static uint32_t `[`convert_byte_array_to_32_bit`](#group__group__sam0__utils_1ga6e01ed4a4718b439d295b5124ede09e3)`(uint8_t * data)`            | 
`public inline static uint64_t `[`convert_byte_array_to_64_bit`](#group__group__sam0__utils_1ga45ffdbdc2d7a6d1dbf91b2fe8d880347)`(uint8_t * data)`            | Converts a 8 Byte array into a 64-Bit value.
`struct `[`StructPtr`](#struct_struct_ptr) | Structure of pointers to 64-, 32-, 16- and 8-bit unsigned integers.
`struct `[`StructVPtr`](#struct_struct_v_ptr) | Structure of pointers to volatile 64-, 32-, 16- and 8-bit unsigned integers.
`struct `[`StructCPtr`](#struct_struct_c_ptr) | Structure of pointers to constant 64-, 32-, 16- and 8-bit unsigned integers.
`struct `[`StructCVPtr`](#struct_struct_c_v_ptr) | Structure of pointers to constant volatile 64-, 32-, 16- and 8-bit unsigned integers.
`union `[`Union16`](#union_union16) | 16-bit union.
`union `[`Union32`](#union_union32) | 32-bit union.
`union `[`Union64`](#union_union64) | 64-bit union.
`union `[`UnionPtr`](#union_union_ptr) | Union of pointers to 64-, 32-, 16- and 8-bit unsigned integers.
`union `[`UnionVPtr`](#union_union_v_ptr) | Union of pointers to volatile 64-, 32-, 16- and 8-bit unsigned integers.
`union `[`UnionCPtr`](#union_union_c_ptr) | Union of pointers to constant 64-, 32-, 16- and 8-bit unsigned integers.
`union `[`UnionCVPtr`](#union_union_c_v_ptr) | Union of pointers to constant volatile 64-, 32-, 16- and 8-bit unsigned integers.

## Members

#### `define `[`UNUSED`](#group__group__sam0__utils_1gada67c62b1c57e07efa04431bc40b9238) {#group__group__sam0__utils_1gada67c62b1c57e07efa04431bc40b9238}

Marking *v* as a unused parameter or value.

#### `define `[`barrier`](#group__group__sam0__utils_1ga53290ac2df2384738b8769c76622f803) {#group__group__sam0__utils_1ga53290ac2df2384738b8769c76622f803}

Memory barrier.

#### `define `[`COMPILER_PRAGMA`](#group__group__sam0__utils_1ga85a3ab5701281268521f109ed0078668) {#group__group__sam0__utils_1ga85a3ab5701281268521f109ed0078668}

Emit the compiler pragma *arg*.

#### Parameters
* `arg` The pragma directive as it would appear after *#pragma* (i.e. not stringified).

#### `define `[`COMPILER_PACK_SET`](#group__group__sam0__utils_1gae2c02ff865ca6538b4b1bddbf2a6876c) {#group__group__sam0__utils_1gae2c02ff865ca6538b4b1bddbf2a6876c}

Set maximum alignment for subsequent struct and union definitions to *alignment*.

#### `define `[`COMPILER_PACK_RESET`](#group__group__sam0__utils_1ga38d28b622a4bc7b0f3fb2be2ef1e0086) {#group__group__sam0__utils_1ga38d28b622a4bc7b0f3fb2be2ef1e0086}

Set default alignment for subsequent struct and union definitions.

#### `define `[`Assert`](#group__group__sam0__utils_1gaab1e54dcc40192f9704e8b252635450f) {#group__group__sam0__utils_1gaab1e54dcc40192f9704e8b252635450f}

This macro is used to test fatal errors.

The macro tests if the expression is false. If it is, a fatal error is detected and the application hangs up. If `TEST_SUITE_DEFINE_ASSERT_MACRO` is defined, a unit test version of the macro is used, to allow execution of further tests after a false expression.

#### Parameters
* `expr` Expression to evaluate and supposed to be nonzero.

#### `define `[`Long_call`](#group__group__sam0__utils_1ga5b759626f343cc1af9159cc02b763837) {#group__group__sam0__utils_1ga5b759626f343cc1af9159cc02b763837}

Calls the routine at address *addr*.

It generates a long call opcode.

For example, `Long_call(0x80000000)' generates a software reset on a UC3 if it is invoked from the CPU supervisor mode.

#### Parameters
* `addr` Address of the routine to call.

It may be used as a long jump opcode in some special cases.

#### `define `[`div_ceil`](#group__group__sam0__utils_1ga6d4ebd841bc96041a7f3a61e227c1fb2) {#group__group__sam0__utils_1ga6d4ebd841bc96041a7f3a61e227c1fb2}

Calculate $ \left\lceil \frac{a}{b} \right\rceil $ using integer arithmetic.

#### Parameters
* `a` An integer 

* `b` Another integer

#### Returns
(*a* / *b*) rounded up to the nearest integer.

#### `define `[`FUNC_PTR`](#group__group__sam0__utils_1gacce64924b686dd08a83042b35d0d1480) {#group__group__sam0__utils_1gacce64924b686dd08a83042b35d0d1480}

#### `define `[`unused`](#group__group__sam0__utils_1ga417dba7f63dde98dbebd6336d8af9d91) {#group__group__sam0__utils_1ga417dba7f63dde98dbebd6336d8af9d91}

Marking *v* as a unused parameter or value.

#### `define `[`MSB`](#group__group__sam0__utils_1gabee1b74eceef5a0cf26efbf3ff87ccbf) {#group__group__sam0__utils_1gabee1b74eceef5a0cf26efbf3ff87ccbf}

Most significant byte of *u16*.

#### `define `[`LSB`](#group__group__sam0__utils_1gabd2fa7b756342ae251e3a7a66670c2fe) {#group__group__sam0__utils_1gabd2fa7b756342ae251e3a7a66670c2fe}

Least significant byte of *u16*.

#### `define `[`MSH`](#group__group__sam0__utils_1ga2e9046f49816ad27148660f5ba993696) {#group__group__sam0__utils_1ga2e9046f49816ad27148660f5ba993696}

Most significant half-word of *u32*.

#### `define `[`LSH`](#group__group__sam0__utils_1gae79954742b5a668ce83ab79ac9d9804b) {#group__group__sam0__utils_1gae79954742b5a668ce83ab79ac9d9804b}

Least significant half-word of *u32*.

#### `define `[`MSB0W`](#group__group__sam0__utils_1ga25110f05bdb5b5ea3fcb2854a1a07d7a) {#group__group__sam0__utils_1ga25110f05bdb5b5ea3fcb2854a1a07d7a}

Most significant byte of 1st rank of *u32*.

#### `define `[`MSB1W`](#group__group__sam0__utils_1ga0f90ecd0b0f0e15608a95b8367b77ece) {#group__group__sam0__utils_1ga0f90ecd0b0f0e15608a95b8367b77ece}

Most significant byte of 2nd rank of *u32*.

#### `define `[`MSB2W`](#group__group__sam0__utils_1ga0207e10a3c4bcca172463cd5e3ebd865) {#group__group__sam0__utils_1ga0207e10a3c4bcca172463cd5e3ebd865}

Most significant byte of 3rd rank of *u32*.

#### `define `[`MSB3W`](#group__group__sam0__utils_1gad6ab5ac6e3e95525d56d757c9718e352) {#group__group__sam0__utils_1gad6ab5ac6e3e95525d56d757c9718e352}

Most significant byte of 4th rank of *u32*.

#### `define `[`LSB3W`](#group__group__sam0__utils_1ga04e75e548b33b9cc22699b4249ff6c64) {#group__group__sam0__utils_1ga04e75e548b33b9cc22699b4249ff6c64}

Least significant byte of 4th rank of *u32*.

#### `define `[`LSB2W`](#group__group__sam0__utils_1gad8fda97f8caa00fcfa84f712ee7627d6) {#group__group__sam0__utils_1gad8fda97f8caa00fcfa84f712ee7627d6}

Least significant byte of 3rd rank of *u32*.

#### `define `[`LSB1W`](#group__group__sam0__utils_1ga84cbbcad1971cdb2987418e6ae6cb4ff) {#group__group__sam0__utils_1ga84cbbcad1971cdb2987418e6ae6cb4ff}

Least significant byte of 2nd rank of *u32*.

#### `define `[`LSB0W`](#group__group__sam0__utils_1ga2ca8582260a8ada6cdd457cf37ba37a7) {#group__group__sam0__utils_1ga2ca8582260a8ada6cdd457cf37ba37a7}

Least significant byte of 1st rank of *u32*.

#### `define `[`MSW`](#group__group__sam0__utils_1gad71e5e84d2cec4387415a55f5c62b01b) {#group__group__sam0__utils_1gad71e5e84d2cec4387415a55f5c62b01b}

Most significant word of *u64*.

#### `define `[`LSW`](#group__group__sam0__utils_1ga0633993fb1f2d96a56385f09beed7bc7) {#group__group__sam0__utils_1ga0633993fb1f2d96a56385f09beed7bc7}

Least significant word of *u64*.

#### `define `[`MSH0`](#group__group__sam0__utils_1ga280d6a94884872f6a5be80c873e8adc1) {#group__group__sam0__utils_1ga280d6a94884872f6a5be80c873e8adc1}

Most significant half-word of 1st rank of *u64*.

#### `define `[`MSH1`](#group__group__sam0__utils_1ga43de4fac62f938ff4eb448a87522ec0e) {#group__group__sam0__utils_1ga43de4fac62f938ff4eb448a87522ec0e}

Most significant half-word of 2nd rank of *u64*.

#### `define `[`MSH2`](#group__group__sam0__utils_1ga5d32ec744212194c8106c51b89a5dfe9) {#group__group__sam0__utils_1ga5d32ec744212194c8106c51b89a5dfe9}

Most significant half-word of 3rd rank of *u64*.

#### `define `[`MSH3`](#group__group__sam0__utils_1gabb233f238b63c12d2ff361d9ddb3114b) {#group__group__sam0__utils_1gabb233f238b63c12d2ff361d9ddb3114b}

Most significant half-word of 4th rank of *u64*.

#### `define `[`LSH3`](#group__group__sam0__utils_1ga1ec33d340ef17c91cb0530d00ccb0ea8) {#group__group__sam0__utils_1ga1ec33d340ef17c91cb0530d00ccb0ea8}

Least significant half-word of 4th rank of *u64*.

#### `define `[`LSH2`](#group__group__sam0__utils_1ga2efccfe683ebf7d89a972fbbdea2c26d) {#group__group__sam0__utils_1ga2efccfe683ebf7d89a972fbbdea2c26d}

Least significant half-word of 3rd rank of *u64*.

#### `define `[`LSH1`](#group__group__sam0__utils_1gac593b0be4555d883b4297b45cffc4168) {#group__group__sam0__utils_1gac593b0be4555d883b4297b45cffc4168}

Least significant half-word of 2nd rank of *u64*.

#### `define `[`LSH0`](#group__group__sam0__utils_1ga3026b9288b45a9794fd3eb585cbe10bc) {#group__group__sam0__utils_1ga3026b9288b45a9794fd3eb585cbe10bc}

Least significant half-word of 1st rank of *u64*.

#### `define `[`MSB0D`](#group__group__sam0__utils_1ga5f24ecf381776ee415991a545a05e4c7) {#group__group__sam0__utils_1ga5f24ecf381776ee415991a545a05e4c7}

Most significant byte of 1st rank of *u64*.

#### `define `[`MSB1D`](#group__group__sam0__utils_1ga97a0ab6790df95cb4d8021d8850487f8) {#group__group__sam0__utils_1ga97a0ab6790df95cb4d8021d8850487f8}

Most significant byte of 2nd rank of *u64*.

#### `define `[`MSB2D`](#group__group__sam0__utils_1gad4ceacba543e7b8617ca4bd075abb146) {#group__group__sam0__utils_1gad4ceacba543e7b8617ca4bd075abb146}

Most significant byte of 3rd rank of *u64*.

#### `define `[`MSB3D`](#group__group__sam0__utils_1gaf7972d3282ec9ecb97afa34e848ede2c) {#group__group__sam0__utils_1gaf7972d3282ec9ecb97afa34e848ede2c}

Most significant byte of 4th rank of *u64*.

#### `define `[`MSB4D`](#group__group__sam0__utils_1ga1c891624c33b13808633af8dbcaafa5f) {#group__group__sam0__utils_1ga1c891624c33b13808633af8dbcaafa5f}

Most significant byte of 5th rank of *u64*.

#### `define `[`MSB5D`](#group__group__sam0__utils_1ga5e61db58aaf5cbb3051240cdcb1b5147) {#group__group__sam0__utils_1ga5e61db58aaf5cbb3051240cdcb1b5147}

Most significant byte of 6th rank of *u64*.

#### `define `[`MSB6D`](#group__group__sam0__utils_1gacb8062d046ca06f5c28c9a015997494b) {#group__group__sam0__utils_1gacb8062d046ca06f5c28c9a015997494b}

Most significant byte of 7th rank of *u64*.

#### `define `[`MSB7D`](#group__group__sam0__utils_1ga0cbce69964fa2dd7bf05911d0b99b014) {#group__group__sam0__utils_1ga0cbce69964fa2dd7bf05911d0b99b014}

Most significant byte of 8th rank of *u64*.

#### `define `[`LSB7D`](#group__group__sam0__utils_1ga79fb849e13082fdd4adb02debbad7f1a) {#group__group__sam0__utils_1ga79fb849e13082fdd4adb02debbad7f1a}

Least significant byte of 8th rank of *u64*.

#### `define `[`LSB6D`](#group__group__sam0__utils_1gab90afefaf3b5cb2507ab3c496d8f643c) {#group__group__sam0__utils_1gab90afefaf3b5cb2507ab3c496d8f643c}

Least significant byte of 7th rank of *u64*.

#### `define `[`LSB5D`](#group__group__sam0__utils_1gac379acb246797736332fa1b8ae481b34) {#group__group__sam0__utils_1gac379acb246797736332fa1b8ae481b34}

Least significant byte of 6th rank of *u64*.

#### `define `[`LSB4D`](#group__group__sam0__utils_1gaab745f30b9b841f9ccd9ace0a5a1a9e5) {#group__group__sam0__utils_1gaab745f30b9b841f9ccd9ace0a5a1a9e5}

Least significant byte of 5th rank of *u64*.

#### `define `[`LSB3D`](#group__group__sam0__utils_1ga99213c01b979c347950eba4277f0499a) {#group__group__sam0__utils_1ga99213c01b979c347950eba4277f0499a}

Least significant byte of 4th rank of *u64*.

#### `define `[`LSB2D`](#group__group__sam0__utils_1gaba3bea07dcc4a37039b7effd4da03b9e) {#group__group__sam0__utils_1gaba3bea07dcc4a37039b7effd4da03b9e}

Least significant byte of 3rd rank of *u64*.

#### `define `[`LSB1D`](#group__group__sam0__utils_1ga42179f159b798116eb615102a549aa85) {#group__group__sam0__utils_1ga42179f159b798116eb615102a549aa85}

Least significant byte of 2nd rank of *u64*.

#### `define `[`LSB0D`](#group__group__sam0__utils_1ga2e20f5ef87ccf0ad44c1d49d6ffd80a3) {#group__group__sam0__utils_1ga2e20f5ef87ccf0ad44c1d49d6ffd80a3}

Least significant byte of 1st rank of *u64*.

#### `define `[`LSB0`](#group__group__sam0__utils_1ga844ec34df36feb927dc92007af14674a) {#group__group__sam0__utils_1ga844ec34df36feb927dc92007af14674a}

Least significant byte of 1st rank of *u32*.

#### `define `[`LSB1`](#group__group__sam0__utils_1ga2d1e45154b07481f0579ecc725e4edff) {#group__group__sam0__utils_1ga2d1e45154b07481f0579ecc725e4edff}

Least significant byte of 2nd rank of *u32*.

#### `define `[`LSB2`](#group__group__sam0__utils_1ga8967f5ae0174b01ce44c502ebd14035a) {#group__group__sam0__utils_1ga8967f5ae0174b01ce44c502ebd14035a}

Least significant byte of 3rd rank of *u32*.

#### `define `[`LSB3`](#group__group__sam0__utils_1ga5d9ff393e7c8764112a1167db19b16b1) {#group__group__sam0__utils_1ga5d9ff393e7c8764112a1167db19b16b1}

Least significant byte of 4th rank of *u32*.

#### `define `[`MSB3`](#group__group__sam0__utils_1gaeeb8918fc580ce01d45f71863eebff90) {#group__group__sam0__utils_1gaeeb8918fc580ce01d45f71863eebff90}

Most significant byte of 4th rank of *u32*.

#### `define `[`MSB2`](#group__group__sam0__utils_1ga8683254be29bcfe3cf2fa646890d3942) {#group__group__sam0__utils_1ga8683254be29bcfe3cf2fa646890d3942}

Most significant byte of 3rd rank of *u32*.

#### `define `[`MSB1`](#group__group__sam0__utils_1ga3facab9f8ebf70ad6e16038465e2bedc) {#group__group__sam0__utils_1ga3facab9f8ebf70ad6e16038465e2bedc}

Most significant byte of 2nd rank of *u32*.

#### `define `[`MSB0`](#group__group__sam0__utils_1gafb81783b8186acd7182a971048b0c6b3) {#group__group__sam0__utils_1gafb81783b8186acd7182a971048b0c6b3}

Most significant byte of 1st rank of *u32*.

#### `define `[`FLASH_DECLARE`](#group__group__sam0__utils_1ga9b84ecc6b34a71f797ceb8b8f7b8d384) {#group__group__sam0__utils_1ga9b84ecc6b34a71f797ceb8b8f7b8d384}

#### `define `[`FLASH_EXTERN`](#group__group__sam0__utils_1gaaef0fd990bb5bd9cdf11334f7c689fd7) {#group__group__sam0__utils_1gaaef0fd990bb5bd9cdf11334f7c689fd7}

#### `define `[`PGM_READ_BYTE`](#group__group__sam0__utils_1gafe9b83c73d4840986478ec67d3eb7718) {#group__group__sam0__utils_1gafe9b83c73d4840986478ec67d3eb7718}

#### `define `[`PGM_READ_WORD`](#group__group__sam0__utils_1ga92576bffe51090dcb6d5c67e07b9eec7) {#group__group__sam0__utils_1ga92576bffe51090dcb6d5c67e07b9eec7}

#### `define `[`MEMCPY_ENDIAN`](#group__group__sam0__utils_1ga85a7d71a016789b1766f9b27d0530347) {#group__group__sam0__utils_1ga85a7d71a016789b1766f9b27d0530347}

#### `define `[`PGM_READ_BLOCK`](#group__group__sam0__utils_1ga8900e4615b7d7143a6c38e2a39087538) {#group__group__sam0__utils_1ga8900e4615b7d7143a6c38e2a39087538}

#### `define `[`CMD_ID_OCTET`](#group__group__sam0__utils_1gabf2b95fa77301377cdcf79eb615551db) {#group__group__sam0__utils_1gabf2b95fa77301377cdcf79eb615551db}

#### `define `[`CPU_ENDIAN_TO_LE16`](#group__group__sam0__utils_1ga7c15ca0f3159182efc4b80a00768c2c0) {#group__group__sam0__utils_1ga7c15ca0f3159182efc4b80a00768c2c0}

#### `define `[`CPU_ENDIAN_TO_LE32`](#group__group__sam0__utils_1gaa2fd4bfb7af44220ce4205e2aa371017) {#group__group__sam0__utils_1gaa2fd4bfb7af44220ce4205e2aa371017}

#### `define `[`CPU_ENDIAN_TO_LE64`](#group__group__sam0__utils_1ga6f1e86f452c8f327f9ca96cbf6a65c81) {#group__group__sam0__utils_1ga6f1e86f452c8f327f9ca96cbf6a65c81}

#### `define `[`LE16_TO_CPU_ENDIAN`](#group__group__sam0__utils_1gaceb02fdef243c22d2559e260185fb579) {#group__group__sam0__utils_1gaceb02fdef243c22d2559e260185fb579}

#### `define `[`LE32_TO_CPU_ENDIAN`](#group__group__sam0__utils_1ga2df63369ef525ba98832132ce5a43346) {#group__group__sam0__utils_1ga2df63369ef525ba98832132ce5a43346}

#### `define `[`LE64_TO_CPU_ENDIAN`](#group__group__sam0__utils_1gab675071ce5a4644b205cdbc858417ccd) {#group__group__sam0__utils_1gab675071ce5a4644b205cdbc858417ccd}

#### `define `[`CLE16_TO_CPU_ENDIAN`](#group__group__sam0__utils_1ga4ac6e032d1ce0ae6d2e460da93ce8732) {#group__group__sam0__utils_1ga4ac6e032d1ce0ae6d2e460da93ce8732}

#### `define `[`CLE32_TO_CPU_ENDIAN`](#group__group__sam0__utils_1ga3ff07a7496222efe8bc7d7b7b0342b0d) {#group__group__sam0__utils_1ga3ff07a7496222efe8bc7d7b7b0342b0d}

#### `define `[`CLE64_TO_CPU_ENDIAN`](#group__group__sam0__utils_1gacbbba93256e2d892c748d56a42f00f9b) {#group__group__sam0__utils_1gacbbba93256e2d892c748d56a42f00f9b}

#### `define `[`CCPU_ENDIAN_TO_LE16`](#group__group__sam0__utils_1ga5fd2d3ed2fc9234277b659b67d33bc64) {#group__group__sam0__utils_1ga5fd2d3ed2fc9234277b659b67d33bc64}

#### `define `[`CCPU_ENDIAN_TO_LE32`](#group__group__sam0__utils_1ga1e3290451e5c7b98175911c9219b5123) {#group__group__sam0__utils_1ga1e3290451e5c7b98175911c9219b5123}

#### `define `[`CCPU_ENDIAN_TO_LE64`](#group__group__sam0__utils_1ga00483bf27ea1e8a2143c6baf22b31f16) {#group__group__sam0__utils_1ga00483bf27ea1e8a2143c6baf22b31f16}

#### `define `[`ADDR_COPY_DST_SRC_16`](#group__group__sam0__utils_1gac4609178e5c825e815f44fa123dcaaf7) {#group__group__sam0__utils_1gac4609178e5c825e815f44fa123dcaaf7}

#### `define `[`ADDR_COPY_DST_SRC_64`](#group__group__sam0__utils_1ga0454afa80924c2183c8c672c043440cc) {#group__group__sam0__utils_1ga0454afa80924c2183c8c672c043440cc}

#### `public inline static void `[`convert_64_bit_to_byte_array`](#group__group__sam0__utils_1gadca7cebb159c7ed180d3d07cccb74245)`(uint64_t value,uint8_t * data)` {#group__group__sam0__utils_1gadca7cebb159c7ed180d3d07cccb74245}

Converts a 64-Bit value into a 8 Byte array.

#### Parameters
* `value` 64-Bit value 

* `data` Pointer to the 8 Byte array to be updated with 64-Bit value

#### `public inline static void `[`convert_16_bit_to_byte_array`](#group__group__sam0__utils_1ga2de8d131d6afca8b368486f56c911e75)`(uint16_t value,uint8_t * data)` {#group__group__sam0__utils_1ga2de8d131d6afca8b368486f56c911e75}

Converts a 16-Bit value into a 2 Byte array.

#### Parameters
* `value` 16-Bit value 

* `data` Pointer to the 2 Byte array to be updated with 16-Bit value

#### `public inline static void `[`convert_spec_16_bit_to_byte_array`](#group__group__sam0__utils_1gaa9724d81bfe44a06b0372d144cd98e36)`(uint16_t value,uint8_t * data)` {#group__group__sam0__utils_1gaa9724d81bfe44a06b0372d144cd98e36}

#### `public inline static void `[`convert_16_bit_to_byte_address`](#group__group__sam0__utils_1ga9634f2d7292e1209fe3b83254a66c450)`(uint16_t value,uint8_t * data)` {#group__group__sam0__utils_1ga9634f2d7292e1209fe3b83254a66c450}

#### `public inline static uint16_t `[`convert_byte_array_to_16_bit`](#group__group__sam0__utils_1gad3726f56d0820acc7bae83993bd8897c)`(uint8_t * data)` {#group__group__sam0__utils_1gad3726f56d0820acc7bae83993bd8897c}

#### `public inline static uint32_t `[`convert_byte_array_to_32_bit`](#group__group__sam0__utils_1ga6e01ed4a4718b439d295b5124ede09e3)`(uint8_t * data)` {#group__group__sam0__utils_1ga6e01ed4a4718b439d295b5124ede09e3}

#### `public inline static uint64_t `[`convert_byte_array_to_64_bit`](#group__group__sam0__utils_1ga45ffdbdc2d7a6d1dbf91b2fe8d880347)`(uint8_t * data)` {#group__group__sam0__utils_1ga45ffdbdc2d7a6d1dbf91b2fe8d880347}

Converts a 8 Byte array into a 64-Bit value.

#### Parameters
* `data` Specifies the pointer to the 8 Byte array

#### Returns
64-Bit value

# struct `StructPtr` {#struct_struct_ptr}

Structure of pointers to 64-, 32-, 16- and 8-bit unsigned integers.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public int64_t * `[`s64ptr`](#struct_struct_ptr_1ab436f27258753b9cf149312d1e668d7e) | 
`public uint64_t * `[`u64ptr`](#struct_struct_ptr_1a01a7db75ae97caa7457038b8ee801d1f) | 
`public int32_t * `[`s32ptr`](#struct_struct_ptr_1a106ea0461fc89cf4c58cec908c448aef) | 
`public uint32_t * `[`u32ptr`](#struct_struct_ptr_1a00500224ac165192ac888251a076606d) | 
`public int16_t * `[`s16ptr`](#struct_struct_ptr_1a55c23b18ff2cf478679ca49da3927345) | 
`public uint16_t * `[`u16ptr`](#struct_struct_ptr_1a15c8362aa58f36ae5de7f6180550d6b5) | 
`public int8_t * `[`s8ptr`](#struct_struct_ptr_1a874b2108143ffd4d2a83baa5d8fa8cad) | 
`public uint8_t * `[`u8ptr`](#struct_struct_ptr_1acc04e057a962c975bbdf62664c52ff2c) | 

## Members

#### `public int64_t * `[`s64ptr`](#struct_struct_ptr_1ab436f27258753b9cf149312d1e668d7e) {#struct_struct_ptr_1ab436f27258753b9cf149312d1e668d7e}

#### `public uint64_t * `[`u64ptr`](#struct_struct_ptr_1a01a7db75ae97caa7457038b8ee801d1f) {#struct_struct_ptr_1a01a7db75ae97caa7457038b8ee801d1f}

#### `public int32_t * `[`s32ptr`](#struct_struct_ptr_1a106ea0461fc89cf4c58cec908c448aef) {#struct_struct_ptr_1a106ea0461fc89cf4c58cec908c448aef}

#### `public uint32_t * `[`u32ptr`](#struct_struct_ptr_1a00500224ac165192ac888251a076606d) {#struct_struct_ptr_1a00500224ac165192ac888251a076606d}

#### `public int16_t * `[`s16ptr`](#struct_struct_ptr_1a55c23b18ff2cf478679ca49da3927345) {#struct_struct_ptr_1a55c23b18ff2cf478679ca49da3927345}

#### `public uint16_t * `[`u16ptr`](#struct_struct_ptr_1a15c8362aa58f36ae5de7f6180550d6b5) {#struct_struct_ptr_1a15c8362aa58f36ae5de7f6180550d6b5}

#### `public int8_t * `[`s8ptr`](#struct_struct_ptr_1a874b2108143ffd4d2a83baa5d8fa8cad) {#struct_struct_ptr_1a874b2108143ffd4d2a83baa5d8fa8cad}

#### `public uint8_t * `[`u8ptr`](#struct_struct_ptr_1acc04e057a962c975bbdf62664c52ff2c) {#struct_struct_ptr_1acc04e057a962c975bbdf62664c52ff2c}

# struct `StructVPtr` {#struct_struct_v_ptr}

Structure of pointers to volatile 64-, 32-, 16- and 8-bit unsigned integers.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public int64_t * `[`s64ptr`](#struct_struct_v_ptr_1a2908c8cb1c7d816d7f9d3a30531818f8) | 
`public uint64_t * `[`u64ptr`](#struct_struct_v_ptr_1a1acc0e7be6320444fc9a35fbd89f1f37) | 
`public int32_t * `[`s32ptr`](#struct_struct_v_ptr_1ac419cbdd704de7024e989caaf9e19a98) | 
`public uint32_t * `[`u32ptr`](#struct_struct_v_ptr_1abdec22b9984813fac831e57d45cae742) | 
`public int16_t * `[`s16ptr`](#struct_struct_v_ptr_1aee6c3ba77b4b25f556abb8a41053caf4) | 
`public uint16_t * `[`u16ptr`](#struct_struct_v_ptr_1ae008948f89e2a5ee3102016f82023b42) | 
`public int8_t * `[`s8ptr`](#struct_struct_v_ptr_1ab07ceff1caf6f3bb01bd31296a36daf9) | 
`public uint8_t * `[`u8ptr`](#struct_struct_v_ptr_1a4213589251839cd1f42c3343c6cb9be9) | 

## Members

#### `public int64_t * `[`s64ptr`](#struct_struct_v_ptr_1a2908c8cb1c7d816d7f9d3a30531818f8) {#struct_struct_v_ptr_1a2908c8cb1c7d816d7f9d3a30531818f8}

#### `public uint64_t * `[`u64ptr`](#struct_struct_v_ptr_1a1acc0e7be6320444fc9a35fbd89f1f37) {#struct_struct_v_ptr_1a1acc0e7be6320444fc9a35fbd89f1f37}

#### `public int32_t * `[`s32ptr`](#struct_struct_v_ptr_1ac419cbdd704de7024e989caaf9e19a98) {#struct_struct_v_ptr_1ac419cbdd704de7024e989caaf9e19a98}

#### `public uint32_t * `[`u32ptr`](#struct_struct_v_ptr_1abdec22b9984813fac831e57d45cae742) {#struct_struct_v_ptr_1abdec22b9984813fac831e57d45cae742}

#### `public int16_t * `[`s16ptr`](#struct_struct_v_ptr_1aee6c3ba77b4b25f556abb8a41053caf4) {#struct_struct_v_ptr_1aee6c3ba77b4b25f556abb8a41053caf4}

#### `public uint16_t * `[`u16ptr`](#struct_struct_v_ptr_1ae008948f89e2a5ee3102016f82023b42) {#struct_struct_v_ptr_1ae008948f89e2a5ee3102016f82023b42}

#### `public int8_t * `[`s8ptr`](#struct_struct_v_ptr_1ab07ceff1caf6f3bb01bd31296a36daf9) {#struct_struct_v_ptr_1ab07ceff1caf6f3bb01bd31296a36daf9}

#### `public uint8_t * `[`u8ptr`](#struct_struct_v_ptr_1a4213589251839cd1f42c3343c6cb9be9) {#struct_struct_v_ptr_1a4213589251839cd1f42c3343c6cb9be9}

# struct `StructCPtr` {#struct_struct_c_ptr}

Structure of pointers to constant 64-, 32-, 16- and 8-bit unsigned integers.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public const int64_t * `[`s64ptr`](#struct_struct_c_ptr_1ac9ea294aaa07e5a63204530ebf3dd3d2) | 
`public const uint64_t * `[`u64ptr`](#struct_struct_c_ptr_1abbc67642e882a52be564515f1c8f12cb) | 
`public const int32_t * `[`s32ptr`](#struct_struct_c_ptr_1af6182ebecd1280fa1714762f2d81d5d3) | 
`public const uint32_t * `[`u32ptr`](#struct_struct_c_ptr_1a12f0da0bcf30aca9703630565d8be204) | 
`public const int16_t * `[`s16ptr`](#struct_struct_c_ptr_1a153aa1a4a18fe39a05be056a372d19c9) | 
`public const uint16_t * `[`u16ptr`](#struct_struct_c_ptr_1a4ff05b3b8a78949bf0036fe340b98b05) | 
`public const int8_t * `[`s8ptr`](#struct_struct_c_ptr_1a2e21f1ae56dd4da3f534ccebfa234fcc) | 
`public const uint8_t * `[`u8ptr`](#struct_struct_c_ptr_1acb08e5689c70ca4ef5e0d984f15f47ae) | 

## Members

#### `public const int64_t * `[`s64ptr`](#struct_struct_c_ptr_1ac9ea294aaa07e5a63204530ebf3dd3d2) {#struct_struct_c_ptr_1ac9ea294aaa07e5a63204530ebf3dd3d2}

#### `public const uint64_t * `[`u64ptr`](#struct_struct_c_ptr_1abbc67642e882a52be564515f1c8f12cb) {#struct_struct_c_ptr_1abbc67642e882a52be564515f1c8f12cb}

#### `public const int32_t * `[`s32ptr`](#struct_struct_c_ptr_1af6182ebecd1280fa1714762f2d81d5d3) {#struct_struct_c_ptr_1af6182ebecd1280fa1714762f2d81d5d3}

#### `public const uint32_t * `[`u32ptr`](#struct_struct_c_ptr_1a12f0da0bcf30aca9703630565d8be204) {#struct_struct_c_ptr_1a12f0da0bcf30aca9703630565d8be204}

#### `public const int16_t * `[`s16ptr`](#struct_struct_c_ptr_1a153aa1a4a18fe39a05be056a372d19c9) {#struct_struct_c_ptr_1a153aa1a4a18fe39a05be056a372d19c9}

#### `public const uint16_t * `[`u16ptr`](#struct_struct_c_ptr_1a4ff05b3b8a78949bf0036fe340b98b05) {#struct_struct_c_ptr_1a4ff05b3b8a78949bf0036fe340b98b05}

#### `public const int8_t * `[`s8ptr`](#struct_struct_c_ptr_1a2e21f1ae56dd4da3f534ccebfa234fcc) {#struct_struct_c_ptr_1a2e21f1ae56dd4da3f534ccebfa234fcc}

#### `public const uint8_t * `[`u8ptr`](#struct_struct_c_ptr_1acb08e5689c70ca4ef5e0d984f15f47ae) {#struct_struct_c_ptr_1acb08e5689c70ca4ef5e0d984f15f47ae}

# struct `StructCVPtr` {#struct_struct_c_v_ptr}

Structure of pointers to constant volatile 64-, 32-, 16- and 8-bit unsigned integers.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public const volatile int64_t * `[`s64ptr`](#struct_struct_c_v_ptr_1aa79f3b96a6ad079e73cc0be13bd0e765) | 
`public const volatile uint64_t * `[`u64ptr`](#struct_struct_c_v_ptr_1a24a2bedaf12d427819c62babba34e2ef) | 
`public const volatile int32_t * `[`s32ptr`](#struct_struct_c_v_ptr_1a0aa7d6575057bad6b799c9b2909c077b) | 
`public const volatile uint32_t * `[`u32ptr`](#struct_struct_c_v_ptr_1a0e4e80d3c57067ad85c71af39d0ea817) | 
`public const volatile int16_t * `[`s16ptr`](#struct_struct_c_v_ptr_1a97b5d4643b545ecc9ac9c68fa35b74fe) | 
`public const volatile uint16_t * `[`u16ptr`](#struct_struct_c_v_ptr_1a288ff13c7abb2360d62009e2711e7485) | 
`public const volatile int8_t * `[`s8ptr`](#struct_struct_c_v_ptr_1afc839213e22402ccf98e7d143453b58d) | 
`public const volatile uint8_t * `[`u8ptr`](#struct_struct_c_v_ptr_1ae6228fb5d646745079910ea045f314e3) | 

## Members

#### `public const volatile int64_t * `[`s64ptr`](#struct_struct_c_v_ptr_1aa79f3b96a6ad079e73cc0be13bd0e765) {#struct_struct_c_v_ptr_1aa79f3b96a6ad079e73cc0be13bd0e765}

#### `public const volatile uint64_t * `[`u64ptr`](#struct_struct_c_v_ptr_1a24a2bedaf12d427819c62babba34e2ef) {#struct_struct_c_v_ptr_1a24a2bedaf12d427819c62babba34e2ef}

#### `public const volatile int32_t * `[`s32ptr`](#struct_struct_c_v_ptr_1a0aa7d6575057bad6b799c9b2909c077b) {#struct_struct_c_v_ptr_1a0aa7d6575057bad6b799c9b2909c077b}

#### `public const volatile uint32_t * `[`u32ptr`](#struct_struct_c_v_ptr_1a0e4e80d3c57067ad85c71af39d0ea817) {#struct_struct_c_v_ptr_1a0e4e80d3c57067ad85c71af39d0ea817}

#### `public const volatile int16_t * `[`s16ptr`](#struct_struct_c_v_ptr_1a97b5d4643b545ecc9ac9c68fa35b74fe) {#struct_struct_c_v_ptr_1a97b5d4643b545ecc9ac9c68fa35b74fe}

#### `public const volatile uint16_t * `[`u16ptr`](#struct_struct_c_v_ptr_1a288ff13c7abb2360d62009e2711e7485) {#struct_struct_c_v_ptr_1a288ff13c7abb2360d62009e2711e7485}

#### `public const volatile int8_t * `[`s8ptr`](#struct_struct_c_v_ptr_1afc839213e22402ccf98e7d143453b58d) {#struct_struct_c_v_ptr_1afc839213e22402ccf98e7d143453b58d}

#### `public const volatile uint8_t * `[`u8ptr`](#struct_struct_c_v_ptr_1ae6228fb5d646745079910ea045f314e3) {#struct_struct_c_v_ptr_1ae6228fb5d646745079910ea045f314e3}

