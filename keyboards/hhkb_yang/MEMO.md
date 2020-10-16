## Hardware Information

The YANG HHKB BLE controller design is similiar to hasu's
controller. Most pins are compatiable.

**MCU**: ATmega32U4  
**Bluetooth**:  MDBT40 (nRF51822-based), with Adafruit Bluefruit LE UART Friend firmware.  
**Power**: 3.3V  
**CPU Frequency**: 8MHz  
**Bootloader**: Lufa MassStorage  

## Pin usage

| Description                          | HASU pin usage         | YANG mod changed           |
|:------------------------------------ | ---------------------- | -------------------------- |
| ~KEY: Lo(0) when key is pressed      | PD7 input(with pullup) |                            |
| Hysteresis: Hi(1) if key was pressed | PB7 output             |                            |
| Row selector bit0                    | PB0 output             |                            |
| Row selector bit1                    | PB1 output             |                            |
| Row selector bit2                    | PB2 output             |                            |
| Col selector bit0                    | PB3 output             |                            |
| Col selector bit1                    | PB4 output             |                            |
| Col selector bit2                    | PB5 output             |                            |
| Key unable                           | PB6 output             |                            |
| Switch power                         | PD4 output             | PD6 output (PMOS FET)      |
| Bluetooth UART Rx                    | PC4 input              | PD2                        |
| Bluetooth UART Tx                    | PC5 output             | PD3                        |
| Bluetooth power                      |                        | PD5 output (low: power on) |
| LED 0                                |                        | PF4                        |
| LED 2                                |                        | PF1                        |
| LED 4                                |                        | PF0                        |
| Unused for PRO2                      | PC6                    |                            |
| Unused for PRO2                      | PC7                    |                            |
| Inner USB power                      |                        | PF7                        |

## How to flash LUFA MassStorage bootloader on Linux

The FAT filesystem on Linux very often cannot flush the write cache,
leading to broken firmware in the flash.

We can use `dd` to write to the virtual block storage directly to
bypass the vfs layer.

```
dd if=FLASH.bin of=/dev/sda seek=4
```

Skip 4 sectors because the default sector size of the virtual device
and dd is 512 bytes and the emulated flash file starts at 5th sector.

## Adafruit Bluefruit LE UART configuraton

The default baud rate used by the firmware is 76800 although adafruit
do not recommend using higher baudrates than 9600 because the nRF51
UART can drop characters.

Double speed mode to get more accurate async reading because the F_CPU
speed is 8MHz.

## Power saving mode design

Power saving is only enabled when USB is detached and using battery
power. Here we define several levels of power saving mode, each saves
more power but takes longer to resume operation.

1. Level 1: idle mode is activated after a short configurable time
   (MATRIX_POWER_SAVE_TIMEOUT_MS) MCU is put into sleep mode and only
   scan the matrix per 15ms. PORTB pins are set to input with pull-up
   to save power. Sensing PCB is powered down between scans.

2. Level 2: after idling for longer (MATRIX_POWER_SAVE_TIMEOUT_L2_MS)
   we entry this state. Matrix scan is skipped until the time lapses
   900ms.

2. Level 3: sleep mode is activated after a longer timeout
   (MATRIX_POWER_SAVE_TIMEOUT_L3_MS) Bluetooth module is powered down.

## Batter reading

VBAT is connected to AIN6 pin on the MDBT40 module and the AREF pin is
the reference voltage. Doing a ADC with AT+HWDAC=6 will return the
difference between VBAT and VREF.

It seems when fully charged the ADC read is 550. Likely VREF is 3311mV
and the fully charged VBAT is thus 3861mV.

Enable battery service with AT+GLEBATTEN=1 first then we can update the
battery level by using AT+GLEBATTVAL=%d

## References

* https://github.com/joric/qmk/wiki/hhkb_ble
* https://github.com/tomsmalley/custom-topre-guide
* https://github.com/abcminiuser/lufa/blob/master/Bootloaders/MassStorage/Lib/VirtualFAT.h
