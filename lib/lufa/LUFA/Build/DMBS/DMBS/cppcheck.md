DMBS - Dean's Makefile Build System
===================================


Module: CPPCHECK
-----------------

The CPPCHECK module provides build targets to perform static analysis of the
user application, using the open source `cppcheck` tool.

## Importing This Module into a Makefile:

To use this module in your application makefile, add the following code to your
makefile:

    include $(DMBS_PATH)/cppcheck.mk

## Prerequisites:

This module requires the `cppcheck` utility to be available in your system's
`PATH` variable. The `cppcheck` utility is distributed on the project's
[official site](http://cppcheck.sourceforge.net/) but is also
made available in many *nix operating system's package managers.

## Build Targets:

The following targets are supported by this module:

<table>
 <tbody>
   <tr>
    <td>cppcheck</td>
    <td>Scan the project with CPPCHECK, and show all discovered issues.</td>
   </tr>
   <tr>
    <td>cppcheck-config</td>
    <td>Check the project with CPPCHECK, to find missing header paths.</td>
   </tr>
 </tbody>
</table>

## Mandatory Variables:

The following variables must be defined (with a `NAME = VALUE` syntax, one
variable per line) in the user makefile to be able to use this module:

<table>
 <tbody>
   <tr>
    <td>SRC</td>
    <td>List of all project source files to scan.</td>
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
    <td>CPPCHECK_INCLUDES</td>
    <td>Extra include paths to search, for any missing header files. Default is empty (no additional paths).</td>
   </tr>
   <tr>
    <td>CPPCHECK_EXCLUDES</td>
    <td>List of source files, file paths or path fragments to exclude from the scan. Default is empty (no exclusions).</td>
   </tr>
   <tr>
    <td>CPPCHECK_MSG_TEMPLATE</td>
    <td>Template for error and warning message output. Default is `{file}:{line}: {severity} ({id}): {message}`.</td>
   </tr>
   <tr>
    <td>CPPCHECK_ENABLE</td>
    <td>List of CPPCHECK checks to enable. Default is `all`.</td>
   </tr>
   <tr>
    <td>CPPCHECK_SUPPRESS</td>
    <td>List of CPPCHECK checks to ignore. Default is `variableScope missingInclude`.</td>
   </tr>
   <tr>
    <td>CPPCHECK_FAIL_ON_WARNING</td>
    <td>Boolean, if `Y` the build will fail if CPPCHECK discovers any errors or warnings. If `N`, fail only on errors. Default is `Y`.</td>
   </tr>
   <tr>
    <td>CPPCHECK_QUIET</td>
    <td>Boolean, if `Y` CPPCHECK will suppress all output except for discovered errors or warnings. If `N`, scan progress will be emitted. Default is `Y`.</td>
   </tr>
   <tr>
    <td>CPPCHECK_FLAGS_</td>
    <td>Additional flags to pass to CPPCHECK when scans are started. Default is empty (no additional flags).</td>
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
