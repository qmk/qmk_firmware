This is a full-featured bm43a layout inspired by the smaller "Super Micro gherkin" and "jj28" sisters.

In addition to the default key layer, there is a function/numbers/symbols layer easily activated with either one of the two "meta" (red) keys and containing almost all keyset missing.

On top of this, activated with both meta keys, there a system layer where are placed media keys, mouse emulation, and Numpad in addition to the PrintScreen/ScrLock/Pause keys. 

The below picture show all layers on the actual keys (if someone would be able to print these labels let me know! :)).

![layout](https://raw.githubusercontent.com/stevexyz/qmk_firmware/master/keyboards/bm43a/keymaps/stevexyz/layout.jpeg)

Notes:
- The Windows/OS key is overlayed with the Esc one
- To activate permanently the function/number/symbols layer you can use the "layer tap toggle" functionality (now set to the default 5 presses). For the system layer to be activated permanently is enough to hit shift in this layer (so with the two meta keys pressed)
- From the System Layer you can "jump" to an additional Lights layer pressing the control key
- Meta-Esc (or simply Esc from the System and Lights layers) and the keyboard is coming back to default key layer in case they are activated permanently


And a view on the actual build:

![layout](https://raw.githubusercontent.com/stevexyz/qmk_firmware/master/keyboards/bm43a/keymaps/stevexyz/actualbuild.jpeg)

In order to compile the module from qmk root directory use the command 'make bm43a:stevexyz'

And in order to upload the new firmware use the command: 'bin/qmk flash -kb bm43a -km stevexyz' (you can initiate programming with keyboard RESET key, that in this keymap has been moved on the backspace button in the "lights" layer)

