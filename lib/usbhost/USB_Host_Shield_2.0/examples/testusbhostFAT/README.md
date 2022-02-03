This small sketch tests the USB host shield mass storage library.

__Note:__ This will not run a Arduino Uno due to the limited ram available in the ATmega328p.

The Arduino Mega (ATmega1280) and the Arduino Mega 2560 (ATmega2560) are confirmed to work with this test code.

To compile this example you will need the following libraries as well:

* [xmem2](https://github.com/xxxajk/xmem2)
* [generic_storage FATfs](https://github.com/xxxajk/generic_storage)
* [RTClib](https://github.com/xxxajk/RTClib)

The following shield is recommended for larger projects: <https://www.rugged-circuits.com/new-products/quadram>.

You may use the bundled [Makefile](Makefile) to compile the code instead of the Arduino IDE if you have problems or want a smaller binary. The master makefile is bundled as a submodule, but can also be downloaded manually at the following link: <https://github.com/xxxajk/Arduino_Makefile_master>.

To download the USB Host library and all the needed libraries for this test.

Run the following command in a terminal application:

```
git clone --recursive https://github.com/felis/USB_Host_Shield_2.0
```

If you want to update all the submodules run:

```
git submodule foreach --recursive git pull origin master
```
