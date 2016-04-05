DMBS - Dean's Makefile Build System
===================================


Module: HID
-----------------

The HID module provides build targets to program a target running a PJRC Teensy
or LUFA compatible HID class bootloader.

## Importing This Module into a Makefile:

To use this module in your application makefile, add the following code to your
makefile:

    include $(DMBS_PATH)/hid.mk

## Prerequisites:

This module requires the `teensy_loader_cli` utility to be available in your
system's `PATH` variable. The `teensy_loader_cli` utility is distributed in
a modified form (from PJRC) in the LUFA project's
[official site](http://www.lufa-lib.org/), but is also
made available in its original form directly from the 
[PJRC website](https://www.pjrc.com/teensy/loader_cli.html). Note that the
original tool works with Teensy boards only, and not LUFA HID bootloader
devices.

This module requires the `hid_bootloader_cli` utility to be available in your
system's `PATH` variable. The `hid_bootloader_cli` Python script utility is
distributed in LUFA project's [official site](http://www.lufa-lib.org/).

This module requires the AVR-GCC compiler to be installed and available in the
system's `PATH` variable.

## Build Targets:

The following targets are supported by this module:

<table>
 <tbody>
   <tr>
    <td>hid</td>
    <td>Program a LUFA HID class bootloader device, using the `hid_bootloader_cli.py` Python script.</td>
   </tr>
   <tr>
    <td>hid-ee</td>
    <td>Program a LUFA HID class bootloader device's EEPROM, using the `hid_bootloader_cli.py` Python script and a shim application which is programmed into the target's flash.</td>
   </tr>
   <tr>
    <td>teensy</td>
    <td>Program a LUFA HID class bootloader device or Teensy board, using the `teensy_loader_cli` tool.</td>
   </tr>
   <tr>
    <td>teensy-ee</td>
    <td>Program a LUFA HID class bootloader device's EEPROM, using the `teensy_loader_cli` tool and a shim application which is programmed into the target's flash.</td>
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
