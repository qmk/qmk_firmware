# Brazilian keymap for the BM40RGB keyboard

![qwerty](https://user-images.githubusercontent.com/62627597/133182509-a57f73f8-c2dc-4cd8-8a48-91a0e6a968dc.png)

This keymap deviates somewhat from the generally used conventions of Planck style keyboards. 
It's built on the following principles:

1. Availability of different base layers. QWERTY, Dvorak, Colemak and Workman are available. They can be chosen with the four right hand home row keys on the ADJUST layer (NAV + NUM keys). The base layout you choose gets stored on the keyboard EEPROM, so it will still be set if you unplug or reset the keyboard. I use Workman, so it's the default, but you can change to QWERTY easily with NAV + NUM + J  (the J in QWERTY).
2. Frequent use of navigation keys such as the arrow keys, home, end, and hotkeys using those keycodes. For that reason, it keeps the navigation keys on a dedicated nav layer, on the home row, under the right hand. The nav layer gets the highly accessible layer toggle button usually used for the LOWER layer on most Planck style keymaps. I find this much better than using dedicated arrow keys on the bottom right of the keyboard, as the very reason I swapped to a 40% is to move my hands less.
3. Accessibility of the ´ ` ^ ~ ç symbols. There are several blank spaces left on the symbols layer, if you need access to other symbols or diacritics.
4. Proper touch typing, and hotkey access, with the Ctrl, Shift, Win/Super and Alt modifiers on both sides. I found my hands very much expect Ctrl to be on the edge of the keyboard, and as such I've kept both bottom corner keys as Ctrl. Using those keys as layer modifiers, albeit common in many keymaps, is something I found to be somewhat awkward, as it makes it basically impossible to use the hand used to press them.
5. Numbers and navigation keys should be slightly more accessible than symbols and function keys. If you use symbols more often, consider swapping the NUM and SYM layer toggle keys.
6. It's easier to remember layers when they make sense conceptually. Hence, there are dedicated layers for navigation/utility (NAV), numbers (NUM), symbols (SYM) and function keys (FN). I'll implement a MIDI layer later on.
7. Tap hold is a good tool and you should use it if you can. Backspace and Delete are set as tap functions on the two more accessible layer toggle keys.

It will only work as intended if your system keyboard layout is set to Brazilian ABNT2. It may work with other international layouts, but some keys, including brackets and the ´ ` ~ ^ keys, will get broken. 

# Layers and functions

In each key:
Top left: Symbols; 
Top right: Functions;
Bottom left: Navigation;
Bottom right: Numbers;
Bottom: secondary function (tap/hold)

# QWERTY
![qwerty](https://user-images.githubusercontent.com/62627597/133182509-a57f73f8-c2dc-4cd8-8a48-91a0e6a968dc.png)
# Dvorak
![dvorak](https://user-images.githubusercontent.com/62627597/133182499-7005ca02-b268-4238-a33d-514c20cafc87.png)
# Colemak
![colemak](https://user-images.githubusercontent.com/62627597/133182489-e3de66b8-5591-4c9d-86a1-468c519dc92b.png)
# Workman
![workman](https://user-images.githubusercontent.com/62627597/133182517-bb31346f-adbc-4106-b415-a3a81b3138de.png)
# Adjust (NAV+NUM)
![adjust](https://user-images.githubusercontent.com/62627597/133182475-1994e733-71a2-42ee-88fe-9a15e711b938.png)
