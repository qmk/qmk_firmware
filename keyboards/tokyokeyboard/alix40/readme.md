# alix40

![alix40](https://i2.wp.com/tokyokeyboard.com/wp-content/uploads/2020/08/hello-alix.png)

Minimal hacker style mechanical keyboard designed in Tokyo. Cherry MX compatible. More Info at [Tokyo Keyboard](http://tokyokeyboard.com).  

* Keyboard Maintainer: [quadcube](https://github.com/quadcube)  
* Hardware Supported: alix40 rev1  
* Hardware Availability: [Tokyo Keyboard](http://tokyokeyboard.com)

Make example for this keyboard (after setting up your build environment):

    make tokyokeyboard/alix40:default

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

Note:
1. Be very careful and gentle when disassembling the PCB from the bottom case
2. alix40 battery power switch (shown in the image below) is used to toggle battery usage (on: battery will be charged when USB is connected, keyboard will be on when USB is disconnected/off:battery will not be charged when USB is connected, keyboard will be off when USB is disconnected)
![alix40pwrtoggle](https://i.imgur.com/zr0DODl.jpg)
3. Install the slider on the battery power switch (bundled together with the 3M feets)
4. Underglow RGBs are switched off when alix40 is running on battery power (hardware feature to extend battery usage time)
