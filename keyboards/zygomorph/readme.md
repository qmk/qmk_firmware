# Zygomorph

![Zygomorph](https://cdn.shopify.com/s/files/1/0008/8827/5005/files/20181219_001748_grande.jpg?v=1545236621)

Zygomorph is the thinnest keyboard with a fully enclosed case. It's only 3.3mm thick below the switches, including screws. It can be used in 5x6 and 4x6 split, or 5x12 and 4x12 combined. It has per-key RGB, supports kailh choc and MX switches, and has 10 rotary encoder positions per half (only one cas be used per half). The board has presoldered components, including type C ports and ATmega32U4.

# Legonut's quick build guide:

1. Be careful of the 3 springpins on the underside of the switchboard, they bend easily.
2. Snap off all external boards. Don't split the sidebars if you're using 5x6.
3. The 4 triangle pieces can be soldered onto the 3 pads near the USB ports to reinforce that area.
4. The side bars are soldered over the pads on the LED pcb. I found the best method was to put some solder down on one set of pads, then place the bar holes over it. Heat it up from the top and push down. Once it's all aligned, add enough solder to fill the holes, don't overfill it. Make sure they're lined up properly. I'll be making both sides thru-holes for the production run.
5. Use a knife/file to scrape off the jagged edges of the PCB joints.
6. Solder switches on with plate/case. Trim the pegs and pins as low as possible (<1mm height).
7. To configure USB ports: There is a column of 3-pad jumpers above the MCU. Solder the middle pad to the pad in the direction of the port you want to connect to the PC. Do this for all 4. 
8. You will also need to solder SJ2 on the master side. Hold wire/metal to connect the pads for flashing the slave side. I'm not sure if disconnecting SJ2 while flashing will brick the board, so be careful. SJ1 is the reset pads.
9. Place nuts into cutouts. You may need to push the switchplate back down and/or force the nuts in.

# Please do not post any prototype pics of Zygomorph without asking me first.

Pictures for the build guide will be coming later. Currently the firmware is not setup at all.

Keyboard Maintainer: [Legonut](https://github.com/Legonut)  
Hardware Supported: Zygomorph R1.0  
Hardware Availability: [RGBKB](https://www.rgbkb.net)

Make example for this keyboard (after setting up your build environment):

    make zygomorph:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
