# bluepill splittest

This is the splittest example for the bluepill MCU.
To trigger keypress, short together pins _B10_ and _B1_.

## Keyboard Configuration

The type of communication (bitbang, serial (half/full duplex)) is set by the keymap `config.h` file with variables with `SPLIT_` prefix.
So this example uses:

-   `config.h` to set which SDI to use for serial. Either define `USE_SDI1_ON_STANDARD_ROLE_PINS`, `USE_SDI1_ON_ALTERNATE_ROLE_PINS` or `USE_SDI2` before the `#ifdef` that configures the default case when none of these variable is defined.
-   `post_config.h` for defining the communication pins between the halves once the keymap is configured.

On your keyboard, you most likely will only use `config.h` because you'd have already chosen your communication scheme: serial type, SDI, pins.

## Wiring

### Switches

-   Add switches to both Bluepills across B10 and B1 pins

### Handedness

Have a look at the [handedness documentation](https://docs.qmk.fm/#/feature_split_keyboard?id=setting-handedness)

-   Add pull-up resistor to left side between VCC and A7
-   Add pull-down resistors to right side between GND and A7

### Send power to the other half

-   Connect the following pins on both sides together: GND, VCC

### Halves data connection

Choose one of the connection type

#### serial - bitbang

-   Connect the B8 pins on both sides together

#### serial - usart half duplex

Check the [documentation](https://docs.qmk.fm/#/serial_driver?id=usart-half-duplex) to determine the pull-up resistor.

-   To use the default usart (USART1) with the standard role pins,
    -   Connect the A9 pins on both sides together and to add a pull-up resistor on one of these pins
    -   Define USE_SDI1_ON_STANDARD_ROLE_PINS in config.h
-   To use the default usart (USART1) with the alternate role pins,
    -   Connect the B6 pins on both sides together and to add a pull-up resistor on one of these pins
    -   Define USE_SDI1_ON_ALTERNATE_ROLE_PINS in config.h
-   To use the usart2 (USART2) pins,
    -   Connect the A2 pins on both sides together and to add a pull-up resistor on one of these pins
    -   Define USE_SDI2 in config.h

#### serial - usart full duplex

-   To use the default usart (USART1) with the standard role pins,
    -   Connect the mpins on A9, A10 one to the other on each side
    -   Define USE_SDI1_ON_STANDARD_ROLE_PINS in config.h
-   To use the default usart (USART1) with the alternate role pins,
    -   Connect the pins B6, B7 one to the other on each side
    -   Define USE_SDI1_ON_ALTERNATE_ROLE_PINS in config.h
-   To use the usart2 (USART2) pins,
    -   Connect the pins A2, A3 one to the other on each side
    -   Define USE_SDI2 in config.h
