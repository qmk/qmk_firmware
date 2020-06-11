# S50

![S50](https://i.imgur.com/9aGFOUi.jpg)

![S50](https://imgur.com/LofLd4F.jpg)


Keyboard Maintainer: [Eye Oh Designs](https://github.com/joedinkle)  



See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

# Hardware Build

Let’s start by taking a look at all the needed components.  You’ll receive the following items in separate bags:

-S50 FR4 Switch Plate

-S50 PCB

-S50 FR4 Bottom

![PCBs](https://imgur.com/buXCI84.jpg)
 
Resistors/Encoder Bag.  Contains:

-1k Ohm resistor (x1)

-10k Ohm resistor (x4)

-470 Ohm resistor (x54)

-Rotary Encoder (x1)

![Bag 1](https://imgur.com/yfbxBKN.jpg)

Diodes/Transistor Bag.  Contains:

LEDs (x54)

Diodes (x55)

4.7 uF capacitor  (x2)

NPN Transistor  (x1)

![Bag 2](https://imgur.com/rW7Ji5s.jpg)
 
Hardware Bag.  Contains:

-M2 x 4 mm screws (x22)

-M2 x 10 mm spacers  (x11)

![Bag 3](https://imgur.com/DEotoAs.jpg)
 
Parts you’ll need to supply to build this kit are:

1.	Switches

2.	Keycaps

3.	Knob([Recommended Knobs](https://www.digikey.com/products/en/hardware-fasteners-accessories/knobs/568?k=kilo+international&k=&pkeyword=kilo+international&sv=0&pv76=25530&pv76=25551&pv76=29348&pv76=29363&pv76=32833&pv76=32847&pv76=32849&sf=0&FV=73%7C15346%2C-8%7C568&quantity=&ColumnSort=0&page=1&pageSize=25))

4.	Pro Micro and header pins(normally included)

5.	Stabilizers

Tools you’ll need to build this kit are:

1.	Soldering iron

2.	Screw driver/Hex driver

3.	Snips

Now that we’ve got all the parts, let’s put the kit together.  We’ll tackle the build in the following order:

1.	Place then solder resistors, diodes (not LEDs), capacitors, and transistor

2.	Place and solder Pro Micro header

3.	Place and solder encoder

4.	Install stabilizers

5.	Install screws and stand-offs on PCB

6.	Mount switches to plate then solder to PCB

7.	Place then solder LEDs

8.	Solder Pro Micro on header

9.  Install the software	

10. Mount keyboard bottom

11.	Install keycaps and knob

## Step 1: Place then solder resistors, diodes (not LEDs), capacitors, and transistor

Our method will be to place all the 2-pin through-hole components into their space and bend the legs to prevent them from coming out.  Once they’re all in we’ll solder all the 2-pin through-hole components. 

We’ll start with the parts with the smallest quantities, which would be the 1k Ohm resistor, 4.7u capacitors, and 10k Ohm resistors.  These components don’t have a polarity and can be inserted in either direction on the bottom of the PCB.

Getting the resistors to fit neatly takes a bit of care.  [Here’s a quick how-to](https://streamable.com/cv3ux9)

The 1k Ohm goes in the R59 spot near the top of the keyboard
![1K](https://imgur.com/tXVYFGJ.jpg)

Place the 10k Ohm resistors in R55-R58 spots under the encoder
![10K](https://imgur.com/hGLM99v.jpg)

Place the capacitors in C1 and C2
![Caps](https://imgur.com/zDEPFBI.jpg)

All of the remaining resistor spots are for the 470 ohm resistors.  Insert them and bend the legs to hold them in place.

Next is to place the diodes. Unlike the resistors, these can be bent in bulk.  I like to use my phone using the method shown here:
![Diode bending](https://imgur.com/rdnlWI3.jpg)
![Diode bending](https://imgur.com/ESdJ8Lq.jpg)
 
IF YOU THINK YOUR PHONE SCREEN IS SUSCEPTIBLE TO SCRATCHING, DON’T USE THIS METHOD!
The diodes have a polarity, and must be installed as shown, with the black part of the diode and thick portion of the diode icon on the same side.
 
Now let’s solder the capacitors, diodes, and resistors.  This is best done with the components facing up.  Once all the components are soldered, flip the PCB over, raise the component legs, and use your snips to remove the excess.
 
 
For the last part of step one, we’ll solder the transistor.  
![Transistor](https://imgur.com/qmmZG6A.jpg)

Ensure the flat part of the PCB icon matches the flat part of the transistor.  We want to get the transistor body as close to the PCB as possible.  To do this, use some force to press the body as close to the PCB before soldering , or push just enough of the legs through to solder, and bend the transistor so that it’s parallel with the PCB.

## Step 2:  Place and install the Pro Micro Header

If you’ve done this before, you know this part won’t be fun.  The Pro micro adds thickness to the keyboard, and we want to minimize that.  The best way to do this is to remove the plastic portion of the header pin.  This is not easy and requires a bit of force.  You’ll have a few options:

1.	 Solder the pins then remove the plastic.  This will require a scary amount of force.  You can use your snips or hot soldering iron to separate the portions of the plastic.  If you do this, be careful not to damage other components.

2.	Remove the plastic then place and solder the pins.  This will still require some force, but not while the pins are attached to the board.  You’ll need to place each pin individually and need to take care to install them as straight as possible.  Placing the Pro Micro over the pins while you solder the pins (DON’T SOLDER THE PRO MICRO YET!!!) will help ensuring the pins are straight.

3.	Leave the plastic on and go with a chunky monkey keeb.  You may need to pick up some bigger M2 spacers if you go this route.  It shouldn't add too much overall thickness.
  

## Step 3:  Place and solder the encoder

This part is simple enough. 

## Step 4: Install stabilizers

Use this image to help make sure you’re installing the stabilizers for the layout you’re planning.
Make sure the stabilizer bar is closest to the larger holes.

![Layouts](https://imgur.com/fN097Gh.jpg)

## Step 5: Install screws and stand-offs on PCB

You have to do this part now!  If you try and install your switches before putting in the screws, you’re going to be very sad!

## Step 6:  Mount switches to plate then solder to PCB

Did you complete Step 5?  Are you sure?  Take another look!  Okay.  Snap one switch into the plate, then solder it.  Next, place each switch into the plate.  The pins should fall into place on the PCB with no problem.  Once all your switches are in, solder them in place.

## Step 7:  Place then solder LEDs

Install the LEDs by placing them through the slots on the switches.  Check the underside of the PCB to ensure the long leg of the LED goes through the hole labeled “+” and the short leg through the hole labeled “-”.  Bend the legs to keep them in place until you’re ready to solder.

## Step 8:  Solder Pro Micro on header

Before you solder your Pro Micro, check the soldering on K2, L2, K16, and L 16.  This will be your last chance to fix any issues with these switches and LEDs.
Turn the PCB so the diodes and resistors are facing up, and place the Pro Micro on the header with Pin 1 (usually square) to the top left.  Slide the Pro Micro as far down the header pins as you can.  Solder away.

## Step 9: Install the Software

1.	Follow the instructions [here](https://beta.docs.qmk.fm/tutorial/newbs_getting_started) to install QMK and learn how to flash.

2.	Download the Eye Oh Designs folder() into your QMK keyboards folder.

3.	Plug up your keyboard(duh)

4.	If using command line, use one of the following commands

a.	make:eyeohdesigns/s50:default:dfu

b.	make:eyeohdesigns/s50:default:avrdude

Replace ‘default’ with whichever layout you’d like, or one you made yourself.  Generally speaking, USB-C based Pro Micros use the dfu command and all other Pro Micros use the avrdude command.  Reset your Pro Micro based on its design (installed button if included, short reset to ground if not).  At this point you should have a working keyboard.

## Step 10:  Mount Keyboard Bottom

Do it.

## Step 11: Install keycaps and knob

Do it. 

## Step 12: Take pretty pictures of your new keeb and spam /r/mechanicalkeyboards and /r/olkb
