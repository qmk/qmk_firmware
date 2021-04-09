# XD75RE  

Copyright 2018 Kolja Brauns  

### Current release: 1.7

**Features**  
A keymap for German users of the XD75RE keyboard, customized to my needs. Not optimized for ten-finger typing. Some choices are due to me being a lefty.  
Designed to ease transition from staggered layouts, with the most important keys in the same positions. All German alphanumerics on main layer. Keyboard language should be set to DE in your OS.  
Lots of dual-use keys, mostly with hold/tap. See visual representation below.
Some 2u keys, using PoS caps. If you don't have any you'll have to replace the dummy keys with the relevant keycodes.  
Full nav keys on main layer.  
Designed to be used with an additional macropad, no numpad configured.  

 **QWZ** - Layer 0, Default Layer. QWERTZ layout.  
 
 
  .-----------------------------------------------------------------------------------------------------------------------.
  |  Esc  |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |   0   |   ß   |   ´   | BckSpc|  Esc  |
  |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
  |  Tab  |   Q   |   W   |   E   |   R   |   T   |   Z   |   U   |   I   |   O   |   P   |   Ü   |   +   |       |  PgUp |
  |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------| Enter |-------|
  | Ctrl/ |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |   Ö   |   Ä   |   #   |       |  PgDn |
  | GUITab|       |       |       |       |       |       |       |       |       |       |       |       |       |       |
  |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
  | LShift|   Y   |   X   |    C  |   V   |   B   |   N   |   M   |   ,   |   .   |   -   |   ^   | Home/ |  Up   |  End  |
  |       |       |       |       |       |       |       |       |       |       |       |       | RShift|       |       |
  |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
  | LCtrl | LAlt  | MO(1)/|     Space     |   Backspace   | MO(1)/|AltGr/ |  Win  |   <   |  Del  | Left  | Down  | Right |
  |       |       | Enter |               |               | TO(1) |Pause  |       |       |       |       |       |       |
  °-----------------------------------------------------------------------------------------------------------------------°
 

 
 
**FNC** - Layer 1, Function Layer. F-Keys, additional useful keys. Usually accessed temporarily, can be toggled if necessary.  


  .-----------------------------------------------------------------------------------------------------------------------.
  | Reset |   F1  |   F2  |   F3  |   F4  |   F5  |   F6  |   F7  |   F8  |   F9  |   F10 |  F11  |  F12  | _____ | _____ |
  |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
  | _____ | _____ | _____ |Bright+| _____ | _____ | _____ | _____ | _____ |   Up  | PrtSc | _____ | _____ | _____ | _____ |
  |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
  | _____ | _____ | _____ |RGB Tog|RGB Mod| _____ | _____ | _____ | Left  |  Down | Right | _____ | _____ | Play  | _____ |
  |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
  | CpsLck| _____ | _____ |Bright-| _____ | _____ | _____ | _____ | _____ | _____ | _____ | _____ | _____ | VolUp | Mute  |
  |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
  | TO(0) | _____ | _____ | _____ | _____ | _____ | _____ | _____ | _____ | _____ | _____ | _____ | Prev  | VolDn | Next  |
  °-----------------------------------------------------------------------------------------------------------------------°
  


*Release 1.1*  

Added Printscreen to second layer.  
Added shortcut to Launchy to AltGr.  

*Release 1.3*  

Now using PoS keys for 2u keys, added dummy keys accordingly (not strictly necessary since debouncing handles this, but without this you'll have double input rarely.)  
Cleaned keymap up & removed unnecessary layers.  

*Release 1.4*  
Fixed position of the reset key, replaced right spacebar with backspace.  

*Release 1.5*  
Reset moved to Esc. Removed Numpad since it wasn't getting any use. Removed random other keys on function layer that weren't getting any use or are covered by my macropad. Added RShift for held home key.  
Added secondary arrow keys on JIKL.  

*Release 1.6*  
Major rework and cleanup.   
Capslock removed. Caps now temporarily toggles function layer when held, Esc when tapped. LShift is Capslock when tapped. Esc is Ctrl-Alt-Del on tap.  
Left lower MO(1) is now Enter on tap. Right lower Layer(1) is now Tap-Toggle (Toggle:_Tap thrice).  
Media keys moved to nav section - Enter=Play, Up=VolUp, Down=VolDn, Left=Prev, Right=Next, End=Mute.  
Added PrintScreen on P on Layer 1.  
Added cleaner visual representation since the multi-function keys make the actual keymap messy.  
Moved old versions into folder together, only current version in root keymap directory now. 

*Release 1.7*  
Backspace split, includes Esc now.  
Capslock moved to function layer to keep smoother LShift operation.  
Original Caps key now Ctrl, Alt+GUI on double-tap - inspired by Android.  
Cleaned up visual representation in readme.
