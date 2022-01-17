# Firmware Code Generator for QMK

Since QMK currently doesn't support changing key layout etc via EPPROM, we need to flash the firmware everytime the layout changes. The firmware obviously is a binaries that needs to be compiled from source - and if we need to update the firmware we need to update the source. This is the code generator that is responsble for generating the necessary configuration in plain c.
