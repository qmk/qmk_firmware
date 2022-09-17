# Optical Keyboard - rev1

* Keyboard Maintainer: [Girish](https://github.com/girishji)
* Hardware Supported: Black pill STM32F401

This keyboard uses optical switches instead of mechanical switches.
PCB for this keyboard can be found on [github](https://github.com/girishji/optical-keyboard-mx).
The matrix implementation uses column-to-row arrangement. All the IR's (infra-red led) in a
column are turned on before reading the digital input pins connected to rows. After
reading all the rows, column is powered off and subsequent column is powered on before
repeating the reading process. There is a delay after a column is powered on in order to
accommodate PT (Phototransistor) 'rise' time. 

This is not a high-performance keyboard since the IR's are provided with very
minimal current (way below the suggested operating value). This is done so as
to keep the design simple. A single GPIO pin of STM32F4 set as output
can provide 20 ma. Each IR is supplied with ~3.6 ma, so that the total current for 5
rows (IRs) falls within the allowable maximum current per pin. Yet it achieves
a scan rate of 400 hz. Since there is no debounce delay, the latency before USB
transit is 2.5 ms. Compared to mechanical keyboards (with 5 ms debounce delay)
this keyboard achieves respectable performance. It is possible to push scanning
rate much higher, but it requires a different matrix design and additional switching
components to increase current to IR.

## Build

Make example for this keyboard (after setting up your build environment):

    make opticalkb/rev1:default

Flashing example for this keyboard:

    make opticalkb/rev1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Physical reset button**: Briefly press the button BOOT and then button NRST, release NRST first and then BOOT 
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

Verify that it entered DFU (bootloader) mode through QMK Toolbox before
flashing.

## Wiring Instructions

There is only one way to solder Blackpill (STM32F401) to the [PCB](https://github.com/girishji/optical-keyboard-mx).
If you are going to use Blackpill in other projects, note that certain pins are [not usable](https://docs.qmk.fm/#/platformdev_blackpill_f411).

