DMBS - Dean's Makefile Build System
===================================


Writing Your Own Modules
------------------------

A DMBS module consists of the several boilerplate sections, explained below.

## The DMBS module hooks

Your module needs to advertise to DMBS its name, its makefile targets, the
required and optional variables, and the variables and macros the module
provides for use elsewhere. This is achieved with the following section:

    DMBS_BUILD_MODULES         += EXAMPLE
    DMBS_BUILD_TARGETS         += example-target another-target
    DMBS_BUILD_MANDATORY_VARS  += MANDATORY_NAME ALSO_MANDATORY
    DMBS_BUILD_OPTIONAL_VARS   += OPTIONAL_NAME ALSO_OPTIONAL
    DMBS_BUILD_PROVIDED_VARS   += MEANING_OF_LIFE
    DMBS_BUILD_PROVIDED_MACROS += STRIP_WHITESPACE

The example above declares that this module is called `EXAMPLE`, and exposes the
listed targets, variable requirements and provides variables and macros.

Your module name and provided variable/macro names must be unique, however you
can (and should) re-use variable names where appropriate if they apply to
several modules (such as `ARCH` to specify the project's microcontroller
architecture). Re-using targets is not recommended, but can be used to extend
the dependencies of another module's targets.

## Importing the CORE module

Next, your module should always import the DMBS `CORE` module, via the
following:

    # Conditionally import the CORE module of DMBS if it is not already imported
    DMBS_MODULE_PATH := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))
    ifeq ($(findstring CORE, $(DMBS_BUILD_MODULES)),)
      include $(DMBS_MODULE_PATH)/core.mk
    endif

This ensures that the `make help` target is always available. In addition, the
`CORE` module exposes some [commonly used macros and variables](core.md) to
your module.

## Setting optional variable's defaults

If a variable is optional, you should provide a default value. Do this via the
`?=` operator of `make`, which sets a variable's value if it has not yet been
set:

    MY_OPTIONAL_VARIABLE ?= some_default_value

## Sanity checking user input

Sanity checks are what make DMBS useful. Where possible, validate user input and
convert generated errors to human-friendly messages. This can be achieved by
enforcing that all the declared module mandatory variables have been set by the
user:

    # Sanity-check values of mandatory user-supplied variables
    $(foreach MANDATORY_VAR, $(DMBS_BUILD_MANDATORY_VARS), $(call ERROR_IF_UNSET, $(MANDATORY_VAR)))

As well as complaining if they are set, but currently empty:
    $(call ERROR_IF_EMPTY, SOME_MANDATORY_VARIABLE)
    $(call ERROR_IF_EMPTY, SOME_OPTIONAL_BUT_NON_EMPTY_VARIABLE)

Or even if they are boolean (`Y` or `N`) variables that have an invalid value:

    $(call ERROR_IF_NONBOOL, SOME_BOOL_VARIABLE)

## Adding targets

The meat of a DMBS module is the targets, which are run when the user types
`make {target name}` from the command line. These can be as complex or simple
as you like. See the GNU make manual for information on writing make targets.

    example-target:
        echo "Your DMBS module works!"

## And finally, list the PHONYs

Important in GNU Make is the concept of phony targets; this special directive
tells make that a given target should never be considered a valid file. Listing
phonies ensures that, for example, if your module had a target called `build`,
it would always run when the user types `make build` from the command line, even
if a file called `build` existed in the user project folder.

You can list module-internal targets here, as well as mark all public targets
via the module header's `DMBS_BUILD_TARGETS` variable.

    # Phony build targets for this module
    .PHONY: $(DMBS_BUILD_TARGETS) some-module-internal-target another-internal-target
