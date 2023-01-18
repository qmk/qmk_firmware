# Full-featured Corne layout for Linux and MacOS

This is a generic layout for Corne, especially for someone who:

* has to type in English
* occasionally has to type in Swedish
* Switches regularly between Linux and MacOS
* Prioritizes text navigation
  * This includes selecting whole lines and deleting words
* uses VIM or VIM bindings for text navigation
* uses the 'compose' feature in Linux and uses the 'mac user dictionary' trick for getting compose features
* Home row modifiers for optimal ergo (hopefully optimal)

This also features:
* OLED displays:
 * indicating OS and LED status (scroll lock, numlock, caps, compose) on the master side
 * layer and modifiers on the slave side
* LED lights:
 * color changes to indicate layer and modifier status
 * LED matrix effects around keypresses
 
## Major notes

### OS 'detection'
* I assume MacOS as the default. Using the ctrl/gui swap magic keycode switches everything to Linux
 * Most of the Linux codes should work in Windows
 * Yes, there are lots of if-statements around which key code to send here... this isn't the most sustainable way to do it, but is the most memory-efficient way I could come up with
 
### RGB matrix effects
* Not all RGB matrix effects are compatible with changing the color on layer/mod change. Some of them get caught in a loop and freeze half of the keyboard, so beware of which ones you activate
* Some RGB settings are stored in eeprom (despite me using the `noeeprom()` version of functions) If something is weird, try clearing eeprom
* The color-changing function probably _should_ be in the `layer_state_set_user` function, except that function doesn't give the state of the modifiers. So instead I have it done in a call that updates the OLEDs

### LED state explicitly not shared
* For some reason, sharing the LED state (as a split keyboard function) will cause the slave side of the keyboard to freeze up if you type too fast. Don't do it!

### Windowing shortcuts
* Again, MacOS is assumed to be the default so I changed as many Linux shortcuts as I could to make them compatible with MacOS. Some of them don't have default shortcuts defined (such as 'move window left' or 'launch calculator') so I just made those as needed

### Right-shift preferred
* At the time of this writing, left-shift wasn't always being registered as a modifier key when checking modmasks, so I stuck with everything using right-shift as it had the expected effects

### Compose key
* I used [macos compose](https://github.com/Granitosaurus/macos-compose) 
  

   
