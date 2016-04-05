DMBS - Dean's Makefile Build System
===================================


Module: AVRDUDE
-----------------

The AVRDUDE module provides build targets for use with the official
open source `AVRDUDE` programmer utility, for the reprogramming of Atmel devices
using a wide variety of official and non-official programming devices and
bootloaders.

## Importing This Module into a Makefile:

To use this module in your application makefile, add the following code to your
makefile:

    include $(DMBS_PATH)/avrdude.mk

## Prerequisites:

This module requires the `avrdude` utility to be available in your
system's `PATH` variable. The `avrdude` utility is distributed on the project's
[official site](https://savannah.nongnu.org/projects/avrdude) but is also
made available in many *nix operating system's package managers.

## Build Targets:

The following targets are supported by this module:

<table>
 <tbody>
   <tr>
    <td>avrdude</td>
    <td>Program the device FLASH memory with the application's executable data.</td>
   </tr>
   <tr>
    <td>avrdude-ee</td>
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
    <td>AVRDUDE_PROGRAMMER</td>
    <td>Name of the programmer/debugger tool or bootloader to communicate with (e.g. `jtagicemkii`). Default is `jtagicemkii`.</td>
   </tr>
   <tr>
    <td>AVRDUDE_PORT</td>
    <td>Name of the communication port to use when when programming with a serially connected tool (e.g. `COM2`). Default is `usb`.</td>
   </tr>
   <tr>
    <td>AVRDUDE_FLAGS</td>
    <td>Additional flags to pass to `avrdude` when invoking the tool. Default is empty (no additional flags).</td>
   </tr>
   <tr>
    <td>AVRDUDE_MEMORY</td>
    <td>Memory space to program when executing the `avrdude` target (e.g. 'application` for an XMEGA device). Default is `flash`.</td>
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
