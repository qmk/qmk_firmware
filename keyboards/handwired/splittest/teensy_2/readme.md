# Teensy 2.0 splittest

To trigger keypress, short together pins *F5* and *F7*

## Wiring
- Add switches to both Teensy 2s across F5 and F7 pins
- Add pull-up resistor to left side between VCC and F0
- Add pull-down resistors to right side between GND and F0
- Connect the following pins on both sides together: D0, D1, GND, VCC
- Add I2C 4.7kOhm resistors between D0 and VCC, and D1 and VCC
- Wire Di of RGB strip for each half to D3
