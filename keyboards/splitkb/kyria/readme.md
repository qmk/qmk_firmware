# Kyria

![Kyria](https://cdn.shopify.com/s/files/1/0227/9171/6941/products/PlateCase_f1870016-98b8-43a9-8aed-3eaf073b367b_900x.jpg?v=1568934600)

An ergonomical 40% split keyboard

Keyboard Maintainer: [splitkb.com](https://github.com/splitkb)  
Hardware Supported: Pro Micro 5V/16MHz and compatible.  
Hardware Availability: [splitkb.com](https://splitkb.com) and partners.

Make example for this keyboard (after setting up your build environment):

    make splitkb/kyria/rev2:default
    make splitkb/kyria/rev2/proton_c:default

Example of flashing this keyboard:

    make splitkb/kyria/rev2:default:flash

Replace "rev2" with "rev1" if you have a Kyria of revision 1.4 or below.
Not sure what revision yours is? It is printed on the outer lower edge of the PCB!
As a rule of thumb, all Kyrias sold after January 1st 2022 are revision 2.x.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

A build guide for the Kyria can be found at [docs.splitkb.com](https://docs.splitkb.com/hc/en-us/articles/360010552059-Kyria-Build-Guide-Introduction).

## Proton C Conversion Guide

If you're one of the lucky people to have Proton Cs to use with their Kyria, there are a couple of caveats to getting this working.

1. You need to have 2x Proton Cs, as you cannot mix and match with Pro Micros or Elite C's.  They both need to be Proton Cs.
2. You'll need to do some modding to enable proper support with the Proton C.

By design, the Kyria uses every available pin on the Pro Micro footprint.  This includes using D3 (RX) for RGB.  This poses a challenge with using the Proton C, since it needs both the TX and RX pins. The Proton C needs both pins, especially if you plan on using Full Duplex Serial. 

To fix this, you need to break off the last header position on the right-hand side on the footprint. This is the `TX0/D3` pad. Leave this pad without a header connected to.

From the A9 pin on the Proton C, you want to run a wire from it to the `SDA + Extra Data` pad near the TRRS jack on the PCB. This will allow for proper, full duplex communication over the TRRS cable. 

To get RGB working properly, as well, you want to run a wire from the `A3` pin on the Proton C, next to the GND and DFU pin, right under the USB port.  Run this to the `TX0/D3` pad (the one you left without a header pin on the PCB).

Once you've done that, you can solder in the Proton C. and flash it.

![Proton C](https://i.imgur.com/nICqWLo.jpg)
