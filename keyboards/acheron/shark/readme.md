# SharkPCB QMK firmware

![sharkpcb](https://acheronproject.com/images/shark/shark_beta_pic3_small.jpg)

The SharkPCB is an open-source ortholinear 40% layout designed by Gondolindrim for the AcheronProject.

* Keyboard Maintainer: [Gondolindrim](https://github.com/gondolindrim)
* Hardware Availability: you can get release Beta SharkPCBs using the JLCPCB manufacturer using the files at [its documentation](http:/acheronproject.com/pcbs/shark/shark/)

## How to flash

### Enter bootloader

### Release Alpha:

The DFU state in the bootloader can be accessed in 2 ways:

* **Bootmagic reset**: hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: press the button on the back of the PCB
* **Keycode in layout**: press the key mapped to `QK_BOOT` if it is available (ESC key at layer 1 in the default layout)

### Release Beta:

The DFU state in the bootloader can be accessed in 3 ways:

* **Bootmagic reset**: hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: press the button on the back of the PCB, for at least five seconds
* **Keycode in layout**: press the key mapped to `QK_BOOT` if it is available (ESC key at layer 1 in the default layout)

## Compile firmware

### Release Alpha

After accessing the DFU state in your PCB, build the default layout using:

    make acheron/shark/alpha:default

### Release Beta

After accessing the DFU state in your PCB, build the default layout using:

    make acheron/shark/beta:default

Then download the resulting binary `*bin` file using `dfu-util` or QMK Toolbox.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
