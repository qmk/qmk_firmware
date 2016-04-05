DMBS - Dean's Makefile Build System
===================================


Module: DOXYGEN
-----------------

The DOXYGEN module provides build targets to automatically generate API
documentation for a project, using the open-source Doxygen tool.

## Importing This Module into a Makefile:

To use this module in your application makefile, add the following code to your
makefile:

    include $(DMBS_PATH)/doxygen.mk

## Prerequisites:

This module requires the `doxygen` utility to be available in your system's
`PATH` variable. The `doxygen` utility is distributed on the project's
[official site](http://doxygen.org/) but is also
made available in many *nix operating system's package managers.

## Build Targets:

The following targets are supported by this module:

<table>
 <tbody>
   <tr>
    <td>doxygen</td>
    <td>Generate project documentation, via Doxygen.</td>
   </tr>
   <tr>
    <td>doxygen-create</td>
    <td>Create a new project Doxygen template, which can then be customized.</td>
   </tr>
   <tr>
    <td>doxygen-upgrade</td>
    <td>Upgrade an existing project Doxygen template to the latest Doxygen version.</td>
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
    <td>DOXYGEN_CONF</td>
    <td>Name of the Doxygen project configuration file that should be used when generating documentation, or creating/upgrading the configuration file.</td>
   </tr>
   <tr>
    <td>DOXYGEN_FAIL_ON_WARNING</td>
    <td>Boolean, if `Y` the build will fail if Doxygen encounters any errors or warnings. If `N`, fail only on errors. Default is `Y`.</td>
   </tr>
   <tr>
    <td>DOXYGEN_OVERRIDE_PARAMS</td>
    <td>List of `NAME=VALUE` parameters which should override the values specified in the project configuration file, when building documentation.</td>
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
