# Launch Pad
The guidance computer inside the [Launch Pad](https://ungodly.design/products/launch-pad) by Ungodly Design.

**Features:**
* Onboard atmega32u4 controller, 5V @ 16MHz
* Kaihl hotswap sockets
* USB-C connector
* 18 in-switch RGB LEDs
* 4 underglow RGB LEDs
* 100 Ω potentiometer slider
* (optional) M2 pcb mounting holes
* (optional) pcb-mount stablizer footprints
* (optional) pin breakout:
  * F5, F4, F1, F0, VBUS, GND

PCB Front             |  PCB Back
:-------------------------:|:-------------------------:
![Numpad](https://i.imgur.com/f47ZFZZl.png)  |  ![5x4](https://i.imgur.com/wZH76Ppl.png)

Numpad Layout             |  5x4 Layout
:-------------------------:|:-------------------------:
![Numpad](https://i.imgur.com/4XvqCBHl.jpg)  |  ![5x4](https://i.imgur.com/mwtGnPSl.jpg)




* Keyboard Maintainer: [Luis Godinez](https://github.com/luis-godinez)
* Hardware Supported: Launch Pad PCB
* Hardware Availability: [Ungodly.Design](https://ungodly.design/products/launch-pad-pcb)

Make example for this keyboard (after setting up your build environment):

    make ungodly/launch_pad:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

# Firmware
- [v1.0](https://github.com/luis-godinez/qmk_firmware/releases/tag/launch_pad)

# Reset Bootloader

<table>
	<tr>
		<td>Use tweezers to short the two bottom pins of the J-Link pinout.</td>
		<td><img src="https://i.imgur.com/ArSIcK0.pngl" width="300"/></td>
	</tr>
</table>

# Midi Setup

<table>
    <tr>
        <th>Windows</th>
        <th>Mac</th>
    </tr>
    <tr>
    	<td valign="top">
    	<ul>
    	    <li>Midi Mixer</li>
        	<ul>
            	<li><a href="https://github.com/jpwilliams/midi-mixer-releases/releases">Download the latest version of Midi Mixer</a></li>
            	<li>Run the exe to install the application.</li><li>Launch the MIDI Mixer application.</li>
            	<li>Navigate to the "Profiles" tab and select the "Ungodly Design Launch Pad" preset.</li>
            	<li>Navigate to the "Groups" tab and select the audio source you would like to control.
            	<br><img src="https://imgur.com/MmdDcTm.pngl" alt="Midi Mixer" width="800"></li>
            	<li>Optionally, Navigate to the "Settings" tab and enable/disable "Logarithmic volume curve".</li>
        	</ul>
    	</ul>
    	</td>
    	<td valign="top">
        	<ul>
            	<li><a href="https://rsjaffe.github.io/MIDI2LR/">Midi2Lightroom</a></li>
            	<li><a href="https://www.orderedbytes.com/controllermate/">ControllerMate</a></li>
        	</ul>
    	</td>
    </tr>
</table>

# Custom OLED Displays

Layer | Graphic
:----:|:----:
home  |  ![home](https://i.imgur.com/tK3u7ZU.png)
nav  |  ![nav](https://i.imgur.com/J0FNZfR.png)
rgb  |  ![rgb](https://i.imgur.com/XK6r6KL.png)

* These instructions require compiling your own firmware. [Ensure that your build environenment is setup](https://beta.docs.qmk.fm/tutorial/newbs_getting_started).
* Use [QMK Logo Editor](https://joric.github.io/qle/) to create your own LCD graphics.
* Copy the generated output into your keymap ([sample code](https://github.com/qmk/qmk_firmware/blob/master/keyboards/ungodly/launch_pad/keymaps/default/keymap.c))
    * Note: By default, the LCD is configured as a vertical display with a 180 degree rotation. You may need to change the `OLED_ROTATION` value in the `keymap.c` to achieve your desired effect.
* Compile the firmware and flash it to your launch pad.
