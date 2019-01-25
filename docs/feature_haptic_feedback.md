--this document is still under developement---

# Haptic Feedback

## Haptic feedback rules.mk options

The following options are currently available for haptic feedback:

* HAPTIC_ENABLE = DRV2605L
* HAPTIC_ENABLE = SOLENOID

## Known Supported Hardware


### Solenoids

Firs you will need a build a circuit to drive the solenoid through a mosfet as most MCU will not be able to provide the current needed to drive the coil in the solenoid.

[Wiring diagram provided by Adafruid](https://playground.arduino.cc/uploads/Learning/solenoid_driver.pdf)

Select a pin that has PWM

* #define   #define SOLENOID_PIN *PIN*

### DRV2605L


## Haptic Keycodes

Not all keycodes below will work depending on which haptic mechanism you have chosen.

|Name      |Description                                   |
|----------|----------------------------------------------|
|`HAPT_ON`|Automatically switch between USB and Bluetooth|
|`HAPT_OFF` |USB only                                      |
|`HAPT_TOGGLE`  |                                |
|`HAPT_RESET`  |                                |
|`HAPT_FEEDBACK`  |                                |
|`HAPT_MODE_INC`  |                                |
|`SOLENOID_DWELL_INC`  |                                |
|`SOLENOID_DWELL_DEC`  |                                |
