HS60
====

[HS60](https://mechboards.co.uk/wp-content/uploads/2018/04/IMG_20180420_140353.jpg)

This is a standard fixed layout 60% PCB. It comes in two varians, ISO and ANSI and support full per-key RGB.

Keyboard Maintainer: [Yiancar](http://yiancar-designs.com/) and on [GitHub](https://github.com/yiancar)  
Hardware Supported: HS60 ISO and ANSI PCBs with Atmega 32u4   
Hardware Availability: https://mechboards.co.uk/shop/all/hs60-pcb/   

If you're using the [community layouts feature](https://docs.qmk.fm/#/feature_layouts) and using the 60_ansi layout, you need to make sure that you include this on your config.h to ensure that the RGB Matrix is properly configured:

    #ifdef KEYBOARD_hs60
      #define HS60_ANSI
    #endif

Make example for this keyboard (after setting up your build environment):

    make hs60/v1:default

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.
