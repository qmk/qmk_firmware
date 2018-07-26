DMBS - Dean's Makefile Build System
===================================


Module: DFU
-----------------

The DFU module provides build targets to program a USB connected target running
a DFU class bootloader, via the official Atmel FLIP utility running via the
command line, or the open source `DFU-Programmer` tool.

## Importing This Module into a Makefile:

To use this module in your application makefile, add the following code to your
makefile:

    include $(DMBS_PATH)/dfu.mk

## Prerequisites:

This module requires the `batchisp` utility to be available in your system's
`PATH` variable. The `batchisp` utility is distributed as part of Atmel's FLIP
software which can be downloaded from the [official site](http://www.atmel.com).

This module requires the `dfu-programmer` utility to be available in your
system's `PATH` variable. The `dfu-programmer` utility is distributed from the
[official project site](https://dfu-programmer.github.io/).

## Build Targets:

The following targets are supported by this module:

<table>
 <tbody>
   <tr>
    <td>flip</td>
    <td>Program the application into the device's flash memory, using Atmel FLIP.</td>
   </tr>
   <tr>
    <td>flip-ee</td>
    <td>Program the application's EEPROM data into the device's EEPROM memory, using Atmel FLIP.</td>
   </tr>
   <tr>
    <td>dfu</td>
    <td>Program the application into the device's flash memory, using `dfu-programmer`.</td>
   </tr>
   <tr>
    <td>dfu-ee</td>
    <td>Program the application's EEPROM data into the device's EEPROM memory, using `dfu-programmer`.</td>
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
 </tbody>
</table>

## Optional Variables:

The following variables may be defined (with a `NAME = VALUE` syntax, one
variable per line) in the user makefile. If not specified, a default value will
be assumed.

<table>
 <tbody>
   <tr>
    <td>N/A</td>
    <td>This module has no optional variables.</td>
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

### 20160403
Initial release.
