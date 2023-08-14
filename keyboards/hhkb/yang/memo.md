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
dd if=FLASH.bin of=<path of virtual block device> seek=4
```

Skip 4 sectors because the default sector size of the virtual device
and dd is 512 bytes and the emulated flash file starts at 5th sector.

## How to find the path of the virtual block device

After the keyboard boots into flash mode, on Linux system you should
be able to find the block device in `dmesg` logs.

For exmaple if you type

```
sudo dmesg
```

You should find something like

```
[357885.143593] usb 1-1.4: USB disconnect, device number 24
[357885.627740] usb 1-1.4: new full-speed USB device number 25 using xhci_hcd
[357885.729486] usb 1-1.4: New USB device found, idVendor=03eb, idProduct=1962, bcdDevice= 0.01
[357885.729492] usb 1-1.4: New USB device strings: Mfr=0, Product=0, SerialNumber=0
[357885.745620] SCSI subsystem initialized
[357885.746712] usb-storage 1-1.4:1.0: USB Mass Storage device detected
[357885.746818] scsi host0: usb-storage 1-1.4:1.0
[357885.746919] usbcore: registered new interface driver usb-storage
[357885.747689] usbcore: registered new interface driver uas
[357886.766755] scsi 0:0:0:0: Direct-Access     LUFA     Bootloader       0.00 PQ: 0 ANSI: 0
[357886.773216] scsi 0:0:0:0: Attached scsi generic sg0 type 0
[357886.777474] sd 0:0:0:0: [sdx] 134 512-byte logical blocks: (68.6 kB/67.0 KiB)
[357886.780300] sd 0:0:0:0: [sdx] Write Protect is off
[357886.780302] sd 0:0:0:0: [sdx] Mode Sense: 00 00 00 00
[357886.783113] sd 0:0:0:0: [sdx] Asking for cache data failed
[357886.783114] sd 0:0:0:0: [sdx] Assuming drive cache: write through
[357886.842676]  sdx:
[357886.859528] sd 0:0:0:0: [sdx] Attached SCSI removable disk
```

The `sdx` is the block device name and the full path is at `/dev/sdx`
The above flash command will become

```
dd if=FLASH.bin of=/dev/sdx seek=4
```

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

## Battery reading

VBAT is connected to AIN6 pin on the MDBT40 module and the AREF pin is
the reference voltage. Doing a ADC with AT+HWDAC=6 will return the
difference between VBAT and VREF.

It seems when fully charged the ADC read is 550. Likely VREF is 3311mV
and the fully charged VBAT is thus 3861mV.

Enable battery service with AT+BLEBATTEN=1 first then we can update the
battery level by using AT+BLEBATTVAL=%d

## References

* https://github.com/joric/qmk/wiki/hhkb_ble
* https://github.com/tomsmalley/custom-topre-guide
* https://github.com/abcminiuser/lufa/blob/master/Bootloaders/MassStorage/Lib/VirtualFAT.h
