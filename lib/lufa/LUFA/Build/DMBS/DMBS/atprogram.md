DMBS - Dean's Makefile Build System
===================================


Module: ATPROGRAM
-----------------

The ATPROGRAM module provides build targets for use with the official
`ATPROGRAM` back-end utility distributed with the free
[Atmel Studio](http://www.atmel.com) software released by Atmel.

## Importing This Module into a Makefile:

To use this module in your application makefile, add the following code to your
makefile:

    include $(DMBS_PATH)/atprogram.mk

## Prerequisites:

This module requires the `atprogram.exe` utility to be available in your
system's `PATH` variable. The `atprogram.exe` utility is distributed in Atmel
Studio (usually) inside the application install folder's `atbackend`
subdirectory.

## Build Targets:

The following targets are supported by this module:

<table>
 <tbody>
   <tr>
    <td>atprogram</td>
    <td>Program the device FLASH memory with the application's executable data.</td>
   </tr>
   <tr>
    <td>atprogram-ee</td>
    <td>Program the device EEPROM memory with the application's EEPROM data.</td>
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
    <td>ATPROGRAM_PROGRAMMER</td>
    <td>Name of the Atmel programmer or debugger tool to communicate with (e.g. `jtagice3`). Default is `atmelice`.</td>
   </tr>
   <tr>
    <td>ATPROGRAM_INTERFACE</td>
    <td>Name of the programming interface to use when programming the target (e.g. `spi`). Default is `jtag`.</td>
   </tr>
   <tr>
    <td>ATPROGRAM_PORT</td>
    <td>Name of the communication port to use when when programming with a serially connected tool (e.g. `COM2`). Default is `usb`.</td>
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
