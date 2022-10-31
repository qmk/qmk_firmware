# GPIO Driver :id=gpio-driver

Use GPIO driver to expand the number of input or output pins on your microcontroller.

| Driver   | Description  |
|----------|--------------|
| sn74x165 | The 74HC165 is a Parallel-in/serial-out shift register, which let you expand 8 digital input pins for your microcontroller. You can daisy-chain them to expand 16, 24, 32 or more.

## SN74x165 Driver Configuration :id=sn74x165-driver-configuration

The driver reads 74HC165 on SPI.

!>Be aware that the 74HC165 is not SPI compliant. If 74HC165 is the only device on your SPI bus, then you don't care, if there are other devices on the bus, you have to use a tri-state buffer like SN74LVC1G125 to ensure the SPI is under normal operation. 

To enable it, add this to your `rules.mk`:

```make
VPATH += drivers/gpio
SRC += sn74x165.c
QUANTUM_LIB_SRC += spi_master.c
```

You can define the following items in `config.h`, based on how the hardware is set up.

| Variable | Description | Default |
|----------|-------------|---------|
| `SN74X165_LENGTH` | (Optional) How many you use 74HC165 chip aka daisy-chain. | 1 |
| `SN74X165_SPI_CLOCK_DIVISOR` | (Optional) The clock divisor for SPI to ensure that the MCU is within the specifications of 74HC165. | 64 |
| `SN74X165_SPI_MODE` | (Optional) The SPI mode to communicate with 74HC165. | 0 |
| `SN74X165_SPI_LSBFIRST` | (Optional) Whether or not the SPI communication between the microcontroller and 74HC165 should be LSB-first. | false |
| `SN74X165_SPI_SLAVE_SELECT_PIN` | (Required) Set which pin is connected to the OE of tri-state buffer. If tri-state buffer is not used, this pin can be connected to CE/CLK_INH of 74HC165. |
| `SN74X165_PL_PIN` | (Required) Set which pin is connected to the PL/SH/LD of 74HC165. |

Example configuration when using SPI to drive 74HC165:

```c
#define SN74X165_SPI_SLAVE_SELECT_PIN A4
#define SN74X165_PL_PIN A2
#define SN74X165_LENGTH 2
```

Typical hardware connection between 74HC165 and microcontroller when using SPI (with tri-state buffer):

```
                                                  +----------------------+
                                   +<-------------| SPI_SLAVE_SELECT_PIN |
                                   |              +----------------------+
                                   OE
+---------------+      +------------------+       +----------+
| 74HC165 Q7/QH |---->A| tri-state buffer |Y----->| SPI_MISO |
+---------------+      +------------------+       +----------+

+----------------+                                +---------+
| 74HC165 CP/CLK |<-------------------------------| SPI_SCK |
+----------------+                                +---------+

+------------------+                              +--------+
| 74HC165 PL/SH/LD |<-----------------------------| PL_PIN |
+------------------+                              +--------+
```

Typical hardware connection between 74HC165 and microcontroller when using SPI (without tri-state buffer):

```
+---------------+                                 +----------+
| 74HC165 Q7/QH |-------------------------------->| SPI_MISO |
+---------------+                                 +----------+

+----------------+                                +---------+
| 74HC165 CP/CLK |<-------------------------------| SPI_SCK |
+----------------+                                +---------+

+------------------+                              +--------+
| 74HC165 PL/SH/LD |<-----------------------------| PL_PIN |
+------------------+                              +--------+
```

#### Functions :id=functions

#### `void sn74x165_init(void)`

Initialize the sn74x165 driver.

---

#### `bool sn74x165_spi_receive(uint8_t* out)`

Receive a byte or multiple bytes from 74HC165.

##### Arguments

 - `uint8_t* out`  
    The received byte array, depending on how many daisy-chained 74HC165 you have.

##### Returns

 - `bool`  
    returns `true` if SPI reading is successful, `false` otherwise.