## Flashing firmware:
* Clone this repository and `cd` into the `qmk_firmware` directory.
* After cloning, you probably need to run `make git-submodule`.
   - You may also need to install dependencies: `sudo apt install avrdude gcc-avr`
* To build the firmware without flashing the keyboard, use `make (keyboard name):(layout name)`
   - For example, if I want to build Levi's layout for the uglydense keyboard, I will run:
   `make system76/uglydense:levi`
* Before flashing firmware, disable your ModemManager: `systemctl stop ModemManager.service`
   - It messes with the flasher, so just stop it before flashing. You can disable it with `systemctl disable ModemManager.service` if you wish to.
* To flash the firmware, you'll use the same build command, but with `flash` added to the end:
   `make system76/uglydense:default:flash`
   - After it builds, you will see a message that says `Detecting USB port, reset your controller now...`. You then want to hit the "RESET" key on the keyboard if it is programmed into the layout. 
   - In the default layout and the `levi` layout, it is Fn+Esc. If a RESET key is not programmed into the layout, unplugging and re-plugging the keyboard sometimes begins the flashing process. If it doesn't, you'll have to briefly bridge the RST and GND pins on the Arduino Pro Micro inside the keyboard. Don't attempt this unless you know what you are doing.
   
## Making your own layout:
If you want to create your own layout, go to the `keymaps` directory and copy one of the maps in there. You'll probably want to start with the default layout. 
