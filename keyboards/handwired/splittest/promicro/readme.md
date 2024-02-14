# Pro Micro splittest

To trigger keypress, short together pins *B3* and *B6* (marked on the PCB as *14* and *10*).

## Wiring
- Add switches to both Pro Micros across B3 and B6 pins
- Add pull-up resistor to left side between VCC and F6
- Add pull-down resistors to right side between GND and F6
- Connect the following pins on both sides together: D0, D1, GND, VCC
- Add I2C 4.7kOhm resistors between D0 and VCC, and D1 and VCC
- Wire Di of RGB strip for each half to D3
