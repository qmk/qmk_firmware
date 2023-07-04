## Custom Layout
Kinesis Contoured family of keyboards belong to a relatively small group of keyboards that utilize thumb clusters. The keycap profiles of thumb cluster keys make it easy to press multiple keys simultaneously by a thumb finger. Co-locating CTRL, SHIFT and KEYPAD modifiers in the thumb cluster gives truly unique capabilities to these keyboards.

### Software Developer Layout
The **soft_dev** layout is optimized for software development on a Windows machine. It is a result of many years of daily usage. It is a great starting point for your own design.

#### Layout Features
- 3 layers: default layer, keypad layer, numpad layer
- keypad layer allows for 2 finger operation using **arrow** keys together with
    - **CTRL** and/or **SHIFT** modifiers OR
    - **HOME/END** keys OR
    - **PAGEUP/PAGEDOWN** keys.  
- two finger operations can be achieved by holding up to 3 modifier keys (KEYPAD/SHIFT/CTRL) with a thumb finger and using index/middle/ring finger by pressing keywell keys. For example, you can fully control caret position and text selection of:  
    - each letter
    - each word
    - from a current caret position to the beginning of the line
    - from a current caret position to the end of the line
    - multiple lines
    - multiple pages
- with little practice you will be able to string together different key combinations. For example, executing `KEYPAD + O` and then `KEYPAD + SHIFT + U` selects the whole line of text with barely any finger movement. The best part is that it works in any text editor!
- keypad layer allows accessing **F1-F12** and **ESC** keys by moving only a single finger away from the home row, making it very fast and convenient
- **KEYPAD** key can be used to access US ANSI Shifted Symbols instead of pressing a SHIFT key. This gives you two advantages: it makes KEYPAD key a "go to" key which is used in almost all operations unrelated to typing of letters. To understand the second advantage, compare pressing `SHIFT + 0` and `KEYPAD + 0` using the right hand
- **NUMPAD** "momentary" modifier key can be used to quickly switch to a numeric pad while typing alphanumeric strings. In a stock Kinesis firmware you would have to switch to KEYPAD layer and then press NUMLOCK key which makes it unusable for this task
- **NUMPAD** key in the right thumb cluster can be used to switch to a numeric pad for long numeric sequences

#### Layout Layers

<img src="https://i.imgur.com/86LCI3zh.jpg"> 
<img src="https://i.imgur.com/Gv4WBw7h.jpg"/> 
<img src="https://i.imgur.com/gKXMUI2h.jpg"/> 

#### Notes
- MO(1) - switch to **KEYPAD** layer while key is being pressed
- MO(2) - switch to **NUMPAD** layer while key is being pressed
- TO(0) - switch to **BASE** layer 
- TO(2) - switch to **NUMPAD** layer 
- Rsft(Enter) - acts as an ENTER key when pressed and released. Acts as a SHIFT modifier in combination with other keys
- Bt - enter bootloader mode
- Alt(Tab) - toggle between last two active applications
- Ctrl(Tab) - toggle between last two active tabs


### Differences From Stock
- **{}[]** keys are moved to the left side of the keywell to be easily accessible
- **-** and **+** keys are switched
- **CAPS LOCK** key is moved to **KEYPAD** layer and is mapped to **DELETE** on **BASE** layer

### Shortcuts


|Shortcut             | Control Caret                         |
|---------------------|---------------------------------------|
|`KEYPAD + J`         | move caret one character left         | 
|`KEYPAD + L`         | move caret one character right        | 
|`KEYPAD + I`         | move caret one line up                | 
|`KEYPAD + K`         | move caret one line down              | 
|`KEYPAD + CTRL + J`  | move caret one word to the left       | 
|`KEYPAD + CTRL + L`  | move caret one word to the right      | 
|`KEYPAD + U`         | move caret to the start of the line   | 
|`KEYPAD + O`         | move caret to the end of the line     | 
|`KEYPAD + H`         | move caret one page up                | 
|`KEYPAD + N`         | move caret one page down              | 


|Shortcut             | Scroll Lock                           |
|---------------------|---------------------------------------|
|`KEYPAD + CTRL + I`  | scroll page up                        | 
|`KEYPAD + CTRL + K`  | scroll page down                      | 


|Shortcut                     | Select Text                   |
|-----------------------------|-------------------------------|
|`KEYPAD + CTRL + SHIFT + J`  | select one word to the left   | 
|`KEYPAD + CTRL + SHIFT + L`  | select one word to the right  | 
|`KEYPAD + CTRL + SHIFT + I`  | select one line up            | 
|`KEYPAD + CTRL + SHIFT + K`  | select one line down          | 
|`KEYPAD + SHIFT + H`         | select one page up            | 
|`KEYPAD + SHIFT + N`         | select one page down          | 
|`KEYPAD + CTRL + SHIFT + U`  | select from beginning of the file up to the caret position   | 
|`KEYPAD + CTRL + SHIFT + O`  | select from caret position to the end of the file  | 


|Shortcut             | US ANSI Shifted Symbols               |
|---------------------|---------------------------------------|
|`KEYPAD + -`         | _                                     | 
|`KEYPAD + 1`         | !                                     | 
|`KEYPAD + 2`         | @                                     | 
|`KEYPAD + 3`         | #                                     | 
|`KEYPAD + 4`         | $                                     | 
|`KEYPAD + 5`         | %                                     | 
|`KEYPAD + 6`         | ^                                     | 
|`KEYPAD + 7`         | &                                     | 
|`KEYPAD + 8`         | *                                     | 
|`KEYPAD + 9`         | (                                     | 
|`KEYPAD + 0`         | )                                     | 
|`KEYPAD + =`         | +                                     | 
|`KEYPAD + \`         | \|                                    | 
|`KEYPAD + '`         | "                                     | 
|`KEYPAD + ;`         | :                                     | 
|`KEYPAD + /`         | ?                                     | 
|`KEYPAD + [`         | {                                     | 
|`KEYPAD + ]`         | }                                     | 
|`KEYPAD + ,`         | <                                     | 
|`KEYPAD + .`         | >                                     | 
|`KEYPAD + BACKTICK`  | ~                                     | 