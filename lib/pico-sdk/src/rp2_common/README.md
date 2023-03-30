This directory contains libraries specifically targeting the RP2040 or possible future related devices. It is selected when
`PICO_PLATFORM=rp2040` (the default) is specified for the build

`hardware_` libraries exist for individual hardware components to provide a simple API
providing a thin abstraction hiding the details of accessing the hardware registers directly.

`pico_` provides higher level functionality you might generally find in say an OS kernel, as well
as runtime support familiar to most C programmers.
