DMBS - Dean's Makefile Build System
===================================


Module: CORE
------------

The CORE module provides the core DMBS infrastructure used by other DMBS
modules, and must always be imported. Additionally, this module provides the
help system for DMBS.

## Importing This Module into a Makefile:

To use this module in your application makefile, add the following code to your
makefile:

    include $(DMBS_PATH)/core.mk

## Prerequisites:

None.

## Build Targets:

The following targets are supported by this module:

<table>
 <tbody>
   <tr>
    <td>help</td>
    <td>Show help for the current project, including a list of all available targets, variables and macros from the imported modules.</td>
   </tr>
   <tr>
    <td>list_targets</td>
    <td>Show a list of all build targets from the imported modules.</td>
   </tr>
   <tr>
    <td>list_modules</td>
    <td>Show a list of all imported modules.</td>
   </tr>
   <tr>
    <td>list_mandatory</td>
    <td>Show a list of all mandatory variables from the imported modules.</td>
   </tr>
   <tr>
    <td>list_optional</td>
    <td>Show a list of all optional variables from the imported modules.</td>
   </tr>
   <tr>
    <td>list_provided</td>
    <td>Show a list of all variables provided by the imported modules.</td>
   </tr>
   <tr>
    <td>list_macros</td>
    <td>Show a list of all macros provided by the imported modules.</td>
   </tr>
 </tbody>
</table>

## Mandatory Variables:

The following variables must be defined (with a `NAME = VALUE` syntax, one
variable per line) in the user makefile to be able to use this module:

<table>
 <tbody>
   <tr>
    <td>N/A</td>
    <td>This module has no mandatory variables.</td>
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
    <td>DMBS_VERSION</td>
    <td>Current version of this DMBS release.</td>
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
