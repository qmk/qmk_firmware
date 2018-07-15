# FaceW

A 60% no frills keyboard.

The FaceW is a special run of the WKL B.Face sourced from Sprit that doesn't have underglow RGB LEDs
but does have in switch LEDs. Also unlike the B.Face, it is based on ps2avru instead of ps2avrGB. It 
is designed and manufactured in Korea.  It originally uses BootMapperClient for programming but 
can now also use QMK. 

Keyboard Maintainer: [MechMerlin](www.github.com/mechmerlin)
Hardware Supported: FaceW Sprit Edition PCB
Hardware Availability: https://mechanicalkeyboards.com/shop/index.php?l=product_detail&p=1352

## Keyboard Notes
- The FaceW Sprit Edition can be purchased on [mechanicalkeyboards.com](www.mechanicalkeyboards.com)
- Uses ps2avru instead of ps2avrgb
- To put in reset mode hold `q` while inserting the USB cable
- When flashing, type `bootloadHID -r yourfile.hex` and wait awhile

Make example for this keyboard (after setting up your build environment):

    make facew:default

See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.
