# i2c_scanner

Aiming to provide a more qmk friendly version of <https://playground.arduino.cc/Main/I2cScanner/>

> This very simple ~~sketch~~ keymap scans the I2C-bus for devices. If a device is found, it is reported to the ~~Arduino serial monitor~~ console.


## Flashing

Pick a target that is aligned to the MCU you want to test:

```console
make handwired/onekey/elite_c:i2c_scanner:flash # also 34u2 + dfu bootloader
make handwired/onekey/promicro:i2c_scanner:flash
make handwired/onekey/teensy_2:i2c_scanner:flash

# ChibiOS is currently 'best effort' and might not report accurate results
make handwired/onekey/proton_c:i2c_scanner:flash
```

others might work with additional configuration.

## Usage

Output is viewable through a compatible tool <https://docs.qmk.fm/#/newbs_testing_debugging?id=debugging-tools>.

You can change the wires, and plug-in I2C devices while the i2c_scanner is running.

The output of the console will look like this:

```
Listening:
Scanning...
  I2C device found at address 0x20
done
```
