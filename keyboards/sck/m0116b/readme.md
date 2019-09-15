# Golden Delicious aka M0116B

The Golden Delicious, or M0116B, is a replacement PCB for the Apple M0116 and M0118 keyboards, the best keyboard Apple ever made...

Installation Information:

The Golden Delicious comes with new daughter boards that use USB-B connectors. When installing the PCB you can use these new connectors, or you can reuse the old DIN type ADB connectors. Reusing the original ADB daughter boards will require you to put a USB-A connector on an original ADB cable and make sure that you are connecting the pins correctly (and is therefore slightly more advanced to use and setup as it requres a multimeter).

The daughter boards can easily be snapped off from the main PCB. In order to electrically connect them to the main PCB you will need to reuse the 6 wire ribbon cable from your original PCB (or use the supplied pieces of ribbon cable if the originals are damaged during desoldering).

When installing the PCB assembly back into the case, if you are using the new USB-B daughter boards, you will need to trim a small amount of the support brackets inside the case. This is to fit the new USB-B connectors in place of the original DIN type ADB connectors, since the new USB-B connectors are longer than the original ADB connectors. As can be seen [HERE](https://imgur.com/a/a1zIFUC).


Repo Information:

Keyboard Maintainer: [jrfhoutx](https://github.com/jrfhoutx)  
Hardware Supported: M0116B, ATMEGA32U4  
Hardware Availability: Wouldn't you like to know

Make example for this keyboard (after setting up your build environment):

    make m0116b:m0116

    make m0116b:m0118

See [build environment setup](https://docs.qmk.fm/build_environment_setup.html) then the [make instructions](https://docs.qmk.fm/make_instructions.html) for more information.
