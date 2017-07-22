DMBS - Dean's Makefile Build System
===================================


Module: GCC
-----------------

The GCC module provides build targets to compile a user application, using a
variant of GCC for a specific target architecture (such as `avr-gcc`).

## Importing This Module into a Makefile:

To use this module in your application makefile, add the following code to your
makefile:

    include $(DMBS_PATH)/gcc.mk

## Prerequisites:

This module requires the GCC compiler to be installed and available in the
system's `PATH` variable for the desired target architecture.

## Build Targets:

The following targets are supported by this module:

<table>
 <tbody>
   <tr>
    <td>size</td>
    <td>Show the compiled binary size for the various memory segments.</td>
   </tr>
   <tr>
    <td>symbol-sizes</td>
    <td>Show the size of each symbol in the compiled binary (useful to find large functions to optimize further).</td>
   </tr>
   <tr>
    <td>all</td>
    <td>Build application and generate all binary (BIN, ELF, HEX) and auxiliary (LSS, MAP, SYM, etc.) output files.</td>
   </tr>
   <tr>
    <td>lib</td>
    <td>Generate a static `.a` library from the application code, containing the flash region's data.</td>
   </tr>
   <tr>
    <td>elf</td>
    <td>Generate an ELF debug file from the application code, containing all region's data.</td>
   </tr>
   <tr>
    <td>bin</td>
    <td>Generate a flat BIN binary file from the application code, containing the flash region's data.</td>
   </tr>
   <tr>
    <td>hex</td>
    <td>Generate a pair of Intel HEX files from the application code, containing the flash region's data (HEX) and EEPROM data (EEP).</td>
   </tr>
   <tr>
    <td>lss</td>
    <td>Generate a LSS listing file showing the disassembly of the compiled application.</td>
   </tr>
   <tr>
    <td>clean</td>
    <td>Remove all generated project intermediary and binary output files.</td>
   </tr>
   <tr>
    <td>mostlyclean</td>
    <td>Remove all generated project intermediary output files, but preserve the binary output files.</td>
   </tr>
 </tbody>
</table>

## Mandatory Variables:

The following variables must be defined (with a `NAME = VALUE` syntax, one
variable per line) in the user makefile to be able to use this module:

<table>
 <tbody>
   <tr>
    <td>MCU</td>
    <td>Name of the Atmel processor model (e.g. `at90usb1287`).</td>
   </tr>
   <tr>
    <td>TARGET</td>
    <td>Name of the application output file prefix (e.g. `TestApplication`).</td>
   </tr>
   <tr>
    <td>ARCH</td>
    <td>Target device architecture (e.g. `AVR8`).</td>
   </tr>
   <tr>
     <td>SRC</td>
     <td>List of all project source files (C, C++, ASM).</td>
   </tr>
 </tbody>
</table>

## Optional Variables:

The following variables may be defined (with a `NAME = VALUE` syntax, one
variable per line) in the user makefile. If not specified, a default value will
be assumed.

<table>
 <tbody>
   <tr>
    <td>COMPILER_PATH</td>
    <td>Path to the compiler to use, in case a specific compiler should be substituted for the one in the system's `PATH` variable. Default is blank (use `PATH` provided compiler).</td>
   </tr>
   <tr>
    <td>OPTIMIZATION</td>
    <td>Optimization level to use when compiling C and C++ source files. Default is `s` (optimize for smallest size).</td>
   </tr>
   <tr>
    <td>C_STANDARD</td>
    <td>C language standard used when compiling C language source files. Default is `gnu99` (C99 standard with GNU extensions)./td>
   </tr>
   <tr>
    <td>CPP_STANDARD</td>
    <td>C++ language standard used when compiling C++ language source files. Default is `gnu++98` (C++98 standard with GNU extensions)./td>
   </tr>
   <tr>
    <td>F_CPU</td>
    <td>Processor core clock frequency, in Hz. This is used by some architectures for functions such as software spin-loop delays. Default is blank (no value defined).</td>
   </tr>
   <tr>
    <td>C_FLAGS</td>
    <td>Common GCC flags passed to the compiler for C language (C) input files. Default is blank (no additional flags).</td>
   </tr>
   <tr>
    <td>CPP_FLAGS</td>
    <td>Common GCC flags passed to the compiler for C++ language (CPP) input files. Default is blank (no additional flags).</td>
   </tr>
   <tr>
    <td>ASM_FLAGS</td>
    <td>Common GCC flags passed to the assembler for assembly language (S) input files. Default is blank (no additional flags).</td>
   </tr>
   <tr>
    <td>CC_FLAGS</td>
    <td>Common GCC flags passed to the compiler for all source file types. Default is blank (no additional flags).</td>
   </tr>
   <tr>
    <td>LD_FLAGS</td>
    <td>Extra flags to pass to the GNU linker when linking the compiled object files into the resulting binary. Default is blank (no additional flags).</td>
   </tr>
   <tr>
    <td>LINKER_RELAXATIONS</td>
    <td>Boolean, if `Y` linker relaxations will be enabled to slightly reduce the resulting binary's size. Default is `Y`.</td>
   </tr>
   <tr>
    <td>JUMP_TABLES</td>
    <td>Boolean, if `Y` jump tables will be enabled to slightly reduce the resulting binary's size - note that this can cause incorrect jumps if the binary is relocated after compilation, such as for a bootloader. Default is `N`.</td>
   </tr>
   <tr>
    <td>OBJDIR</td>
    <td>Directory to store the intermediate object files, as they are generated from the source files. Default is `obj`.</td>
   </tr>
   <tr>
    <td>OBJECT_FILES</td>
    <td>List of additional `.o` object files to link into the final binary. Default is blank (no additional objects).</td>
   </tr>
   <tr>
    <td>DEBUG_FORMAT</td>
    <td>Debug ELF file format to generate. Default is `dwarf-2`.</td>
   </tr>
   <tr>
    <td>DEBUG_LEVEL</td>
    <td>Level of the debugging information to generate in the compiled object files. Debug is 2 (medium level debugging information).</td>
   </tr>
 </tbody>
</table>

## Provided Variables:

The following variables may be referenced in a user makefile (via `$(NAME)`
syntax) if desired, as they are provided by this module.

<table>
 <tbody>
   <tr>
    <td>N/A</td>
    <td>This module provides no variables.</td>
   </tr>
 </tbody>
</table>

## Provided Macros:

The following macros may be referenced in a user makefile (via
`$(call NAME, ARG1, ARG2, ...)` syntax) if desired, as they are provided by
this module.

<table>
 <tbody>
   <tr>
    <td>N/A</td>
    <td>This module provides no macros.</td>
   </tr>
 </tbody>
</table>

## Module Changelog:

The changes to this module since its initial release are listed below, as of the
DMBS version where the change was made.

### 20170426
Added `JUMP_TABLES` optional variable.

### 20160403
Initial release.
