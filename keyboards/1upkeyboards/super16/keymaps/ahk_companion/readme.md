## AutoHotKey Companion  ##

### Overview ### 
AutoHotKey Companion Keymap for <a href="https://www.1upkeyboards.com/shop/keyboard-kits/macro-pads/super-16-macro-pad/">1upkeyboards Super16</a> is designed be a quick and easy way to get started with AutoHotKey and to provide a foundation for customizing your own macropad. I chose the Super16 because it provided an easy way (RGB) to identify what layer I was on with a quick glance or peripheral vision. The F13 to F24 keys were selected as they are rarely used so you won't run into conflicts with existing application shortcuts and AutoHotKey recognizes them without any issues. 

Same functionality can be accomplished with other similar applications on the host system like Keyboard Maestro, AutoIt, etc. 

* <a href="https://www.autohotkey.com">AutoHotKey</a>(Windows)
* <a href="https://www.autoitscript.com/site/autoit/">AutoIT</a> (Windows)
* <a href="https://www.keyboardmaestro.com/main/">Keyboard Maestro</a>(Mac)
* <a href="https://github.com/autokey/autokey">AutoKey</a>(Linux)

This keymap allows for a total of 48 Function/Macro keys that are accessible within 2 sequential key presses (or more when extended with your own code and additional layers) 

### Alternate Implementations ###
I chose to use <a href="https://docs.qmk.fm/#/feature_layers?id=switching-and-toggling-layers">QMK OSL</a> (One Shot Layer) functionality to avoid having to hold a key while selecting the next key and to have my layers always go back to the default layer as the starting point. This also helps me avoid having to cognitively remember what layer I am on. 

If persistent behavior is prefered, OSL can be swapped for TG which will toggle the layer on/off with a key press instead of clearing the layer once the Function key is pressed. This is useful if a layer contains several keys that need to be used in sequence. I also added a OSL timeout of 3 seconds, so that if the key is not pressed within 3 seconds the layer will go back to default. This can be adjusted in the config.h file by increasing 3000 to a desired value: `#define ONESHOT_TIMEOUT 3000` 




### Layers ###

While the first 5 layers are accessible with only 1 key press at most, the 5th (less frequently used) layer is accessed by first going to the 4th layer, which makes the TG(5) button available on the bottom left. Space for additional 2 more layer toggles is available on the 2 middle buttons on the bottom row. Please refer to the layer diagrams.


* Layer 0 (Base Layer) - the default layer and functions like sending the F13 to F24 keys along with the bottom row to activate another 4 layers. 

    ![Image of Base Layer ](https://i.imgur.com/0LhityX.png)

* Layer 1 (Alt Layer) - Equivalent to Alt+Fxx key being pressed 

    ![Image of Layer 1 ](https://i.imgur.com/ZblqLZt.png)

* Layer 2 (Shift Layer) - Equivalent to Shift+Fxx key being pressed

    ![Image of Layer 2 ](https://i.imgur.com/ZQHwLC0.png)

* Layer 3 (Control Layer) - Equivalent to Ctrl+Fxx key being pressed

    ![Image of Layer 3 ](https://i.imgur.com/JkM8bqV.png)

* Layer 4 (Config Layer) - Layer for multimedia. You can replace the KC_TRNS on this layer in keymap.c to TG(x) to enable additional layers.

    ![Image of Layer 4 ](https://i.imgur.com/srDp5Lv.png)
    
* Layer 5 (RGB Control/QMK) - RGB control layer and Quantum functions (Reset, EEPROM Reset, )

    ![Image of Layer 5 ](https://i.imgur.com/Os3n8dx.png)
    
### Host Configuration ### 

Once the keymap has been flashed to the Super16, you can download the accompanying AutoHotKey file or create your own and have it start automatically either via a Windows Task or another way. Using AutoHotKey allows adjustment of functionality of the buttons without the need to change your map and reflash the macropad every time.
Starting the AHK file can be done either by:
* Creating a Windows Task 
* Adding the AHK to the startup folder
* Launch manually
