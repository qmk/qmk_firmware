# Optical Sensor Driver

## PixArt PMW3360 Optical Sensor

The PixArt PMW3360 Motion Sensor is an optical sensor that is commonly used in mice and trackballs, but can be used for other motion input devices, as well.  But it works exceptionally well with QMK's Pointing Device feature. 

The PMW3360 Motion Sensor interfaces via SPI, and does require SPI to be configured properly, as well. Details on how to do so are in the [SPI Driver doc](spi_driver.md).

### Configuration Options

`config.h` override                  | Description                                                                   | AVR Default
-------------------------------------|-------------------------------------------------------------------------------|--------------
`#define SPI_DIVISOR`                | The divisor used (docs target 2.0MHz)                                         | `8`
`#define SS_CS_PIN`                  | The chip select pin used to "select" the PMW3360 sensor. Can be any GPIO pin. | `hi`
`#define PMW3360_FIRMWARE_H`         | If you have a custom firmware blob for the sensor, you can specify it here.   | _not defined_ 
`#define PMW3360_CPI`                | Sets the default CPI/DPI for the sensor (any value between 100 and 12000).    | `1600`
`#define ROTATIONAL_TRANSFORM_ANGLE` | Sets the rotation for the sensor (between -30 and 30) in degrees.             | _not defined_

If you include a custom firmware blob, you must include these settings: 

Setting                                 | Description                     | Default
----------------------------------------|---------------------------------|--------------
`#define PMW3360_PRODUCT_ID`            | Product ID of firmware          | `0x42`
`#define PMW3360_INVERSE_PRODUCT_ID`    | Bitwise invesion of Product ID  | `0xBD`
`#define PMW3360_SROM_VERSION`          | Firmware version                | `0x04`
`const uint16_t firmware_length`        | Length of array for firmware    |
`const uint8_t PROGMEM firmware_data[]` | array of firmware data          |

### Functions

#### `void pmw3360_spi_init(void)`

This initializes both SPI, in general, and the PMW3360 sensor.  It also uploads the firmware, and verifies the firmware signature (to ensure proper upload). 

#### `report_pmw_t pmw3360_read_burst(void)`

This reads from the sensor, and returns motion data. 

Mostly, the dx and dy data structures are what you want to read.
