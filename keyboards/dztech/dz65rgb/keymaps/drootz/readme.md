![DZ65RGBv2 Layout Image - MAIN](https://res.cloudinary.com/drootz/image/upload/c_scale,w_800/v1582000645/drootz_dz65rgb_layer_0_main_n61oxl.jpg)

# Drootz's DZ65RGBv2 ANSI Layout

This layout fit best people who mainly type in English but regularly need to type in French _(using an English keyboard in OS setting)_. There are also some cool LED indicator effects and tons of Leader Key bindings/macros designed to work on both Mac and Windows OS. I tried to keep things as simple as possible from a usability perspective. Enjoy!

- [LAYERS](#LAYERS)
- [LEADER KEY BINDINGS:](#LEADER-KEY-BINDINGS)
	- [OS and Keyboard Macros](#OS-and-Keyboard-Macros)
	- [French Accents](#French-Accents)
	- [Special Characters and Punctuation](#Special-Characters-and-Punctuation)
	- [Text Selection Macros](#Text-Selection-Macros)
	- [Expanded Space Cadet Macros](#Expanded-Space-Cadet-Macros)
	- [Text Expanders](#Text-Expanders)
- [STEP BY STEP FLASH INSTRUCTIONS](#STEP-BY-STEP-FLASH-INSTRUCTIONS)

## HIGH LEVEL DESCRIPTION

#### Dual function Capslock key
- Single tap to trigger the Leader Key
- Double tap to toggle Capslock ON/OFF

#### 70+ useful Leader Key bindings and macros 
- "Designed" to work on both Mac and Windows OS with an English keyboard OS setting
- Per key timing set at 425ms. Never a key sequence!
- 20+ Punctuation, ASCII, System shortcuts and macros
- 15+ French accents (è, é, ê, È, É, Ê, à, etc.)
	- No need to switch to a French keyboard OS setting!
	- Preserve Capslock if enabled
- 8 Text "selection" shortcuts
- 20+ Expanded "Space Cadet" feature with Shift, Ctrl, Alt and DoubleQuote for (), [], {} and ""
- Few useful strings output for my workflow (You may want to change or remove them...)

#### Dynamic Macros enabled
- Record/Play up to 2 Macros
- Nesting allowed

#### Kept only 4 RGB matrix animations due to size of firmware
- Typing Heatmap => How hot is your WPM! (preferred animation because of LED indicators)
- Matrix Splash => Full gradient & value pulse away from a single key hit then fades value out 
- Solid Splash => Hue & value pulse away from a single key hit then fades value out 
- Solid Color => Static single hue, no speed support

#### LED indicators and animations
- White led when Capslock toggle ON
- The brightness of all the other indicator can be adjusted globally with the RGB matrix brightness setting on layer \_FN
- White LED indicator for layer selection and current layer identification
- Red and green blinking indicator when "recording" or "playing" Dynamic Macros
- Leader Key LED indicator:
	- Persistent 50% dimmed under-glow on top right corner key
	- Light up at 100% for the duration of the Leader Key timeout when activated
	- Hue, saturation and brightness can be globally adjusted with the RGB matrix settings on layer \_FN

#### 3 Layers
- \_MAIN: Default layer for Windows OS
- \_MAC: Transparent layer that switch left hand modifier KC_LALT and KC_LGUI keys for MacOS
- \_FN: Functions & settings layer:
	- Macro 1 & 2 keycodes (Record, Stop, Play) with LED indicators
	- F Keys (F1...F12) on number row
	- RGB matrix & animation settings
	- Screen brightness & volume system controls
	- Layer selection

## LAYERS

- Colored keys on the layout visuals below represent the position of the LED indicators on each layer.
- Press down and hold the MO(\_FN) key to access the \_FN layer
- Double tap on the Capslock key to toggle Capslock ON/OFF
- \_TRNS keys use the next lowest non-transparent key (on lower layers)
- \_NO keys are ignored (nothing happens)

### [Layer 0: \_MAIN](http://www.keyboard-layout-editor.com/#/gists/67c22220856a927766bd3e0331ed782a)
![DZ65RGBv2 Layout Image - MAIN](https://res.cloudinary.com/drootz/image/upload/c_scale,w_800/v1582000645/drootz_dz65rgb_layer_0_main_n61oxl.jpg)

### [Layer 1: \_MAC](http://www.keyboard-layout-editor.com/#/gists/4a32d80c67c778658febf28524fb5000)
![DZ65RGBv2 Layout Image - MAC](https://res.cloudinary.com/drootz/image/upload/c_scale,w_800/v1582000653/drootz_dz65rgb_layer_1_mac_z4tsaw.jpg)

### [Layer 2: \_FN](http://www.keyboard-layout-editor.com/#/gists/b583bd7cc5b0a75b4610bbda18fba65e)
![DZ65RGBv2 Layout Image - FN](https://res.cloudinary.com/drootz/image/upload/c_scale,w_800/v1582000661/drootz_dz65rgb_layer_2_fn_zv8yte.jpg)

## LEADER KEY BINDINGS

The Leader Key on this layout is triggered by tapping the Capslock key once. Once triggered, we have 450ms between each key press to type any one of the sequences listed below. All sequences are designed to work on both Mac and Windows with an English keyboard OS setting.

- [OS and Keyboard Macros](#OS-and-Keyboard-Macros)
- [French Accents](#French-Accents)
- [Special Characters and Ponctuation](#Special-Characters-and-Ponctuation)
- [Text Selection Macros](#Text-Selection-Macros)
- [Expanded Space Cadet Macros](#Expanded-Space-Cadet-Macros)
- [Text Expanders](#Text-Expanders)

#### Legend:

| Acronym | Description |
| :--- | :--- |
| LDR | Leader Key |
| SFT | Shift key |
| CTL | Control key |
| ESC | Escape key |
| ¶ | Text cursor position |

### OS and Keyboard Macros

| Output | Sequence | Description
| :--- | :--- | :--- |
| Toggle Capslock | `LDR  LDR` | Single tap Capslock to trigger the LDR key |
| Delete all previous characters in word on cursor OR; | `LDR  BACKSPACE` | n/a |
| => Delete previous word if triggered repeatedly | `LDR  BACKSPACE` | n/a |
| Delete all forward characters in word on cursor OR; | `LDR  DEL` | n/a |
| => Delete next word if triggered repeatedly | `LDR  DEL` | n/a |
| Backward Delete whole word on cursor | `LDR  BACKSPACE BACKSPACE` | n/a |
| Forward Delete whole word on cursor | `LDR  DEL DEL` | n/a |
| Printscreen | `LDR  INSERT` | n/a |
| Home | `LDR  PAGE-UP` | n/a |
| End | `LDR  PAGE-DOWN` | n/a |
| OS: Close current file/tab | `LDR  W` | n/a |
| OS: Close current application | `LDR  Q` | n/a |
| OS: Show Desktop(Win) or Mission Control(Mac)  | `LDR  D` | The Mac sequence will work with LaunchBar (Cmd+Space) |

### French Accents

| Output | Sequence | Description
| :--- | :--- | :--- |
| `à`¶ &nbsp;&nbsp;or&nbsp;&nbsp; `À`¶ | `LDR  A` | Will output upper character if Capslock enabled. |
| `â`¶ &nbsp;&nbsp;or&nbsp;&nbsp; `Â`¶ | `LDR  A  A` | Will output upper character if Capslock enabled. |
| `ç`¶ &nbsp;&nbsp;or&nbsp;&nbsp; `Ç`¶ | `LDR  C` | Will output upper character if Capslock enabled. |
| `è`¶ &nbsp;&nbsp;or&nbsp;&nbsp; `È`¶ | `LDR  E` | Will output upper character if Capslock enabled. |
| `ê`¶ &nbsp;&nbsp;or&nbsp;&nbsp; `Ê`¶ | `LDR  E  E` | Will output upper character if Capslock enabled. |
| `é`¶ &nbsp;&nbsp;or&nbsp;&nbsp; `É`¶ | `LDR  /` | Will output upper character if Capslock enabled |
| `î`¶ &nbsp;&nbsp;or&nbsp;&nbsp; `Î`¶ | `LDR  I  I` | Will output upper character if Capslock enabled. |
| `ô`¶ &nbsp;&nbsp;or&nbsp;&nbsp; `Ô`¶ | `LDR  O  O` | Will output upper character if Capslock enabled. |
| `ù`¶ &nbsp;&nbsp;or&nbsp;&nbsp; `Ù`¶ | `LDR  U` | Will output upper character if Capslock enabled. |
| `û`¶ &nbsp;&nbsp;or&nbsp;&nbsp; `Û`¶ | `LDR  U  U` | Will output upper character if Capslock enabled. |

### Special Characters and Punctuation

| Output | Sequence | Description |
| :--- | :--- | :--- |
| `±`¶ | `LDR  =  -` | n/a |
| `≤`¶ | `LDR  -  =` | n/a |
| `≥`¶ | `LDR  =  =` | n/a |
| `=>`¶ | `LDR  ,  ,` | n/a |
| `<=`¶ | `LDR  .  .` | n/a |
| ``` ` ``` ¶ | `LDR  ESC` | n/a |
| \`\`\` ¶ | `LDR  ESC  ESC  ESC` | n/a |
| `,` space ¶ | `LDR  SPACE` | n/a |
| `.` space ¶ | `LDR  SPACE  SPACE` | n/a |

### Text Selection Macros

| Output | Sequence |
| :--- | :--- |
| Select everything on this line before cursor | `LDR  LEFT-ARROW` |
| Select everything on this line after cursor | `LDR  RIGHT-ARROW` |
| Select everything on this line before cursor up to end of previous line | `LDR  LEFT-ARROW  LEFT-ARROW` | n/a |
| Select everything on this line | `LDR  RIGHT-ARROW  LEFT-ARROW` |
| Select 1x Page Up on the page before the cursor | `LDR  UP-ARROW` |
| Select 1x Page Down on the page after the cursor | `LDR  DOWN-ARROW` |
| Select everything on the page before the cursor | `LDR  UP-ARROW  UP-ARROW` |
| Select everything on the page after the cursor | `LDR  DOWN-ARROW  DOWN-ARROW` |

### Expanded Space Cadet Macros

| Output | Sequence | Description |
| :--- | :--- | :--- |
| `"`¶ | `LDR  '` | Will output single double-quote |
| `"`¶`"` | `LDR  '  '` | Will wrap cursor between two double-quotes |
| `"`WORD`"`¶ | `LDR  '  '  '` | Will wrap word on cursor between two double-quotes |
| `(`¶ | `LDR  LEFT-SFT` | Will output single left parenthesis |
| `)`¶ | `LDR  RIGHT-SFT` | Will output single right parenthesis |
| `(`¶`)` | `LDR  LEFT-SFT  LEFT-SFT` | Will wrap cursor between two parenthesis' |
| `(`¶`)` | `LDR  RIGHT-SFT  RIGHT-SFT` | Will wrap cursor between two parenthesis' |
| `(`WORD`)`¶ | `LDR  LEFT-SFT  W` | Will wrap word on cursor between two parenthesis' |
| `(`WORD`)`¶ | `LDR  RIGHT-SFT  W` | Will wrap word on cursor between two parenthesis' |
| `(`SELECTION`)`¶ | `LDR  LEFT-SFT  W  W` | Will wrap selection between two parenthesis' |
| `(`SELECTION`)`¶ | `LDR  RIGHT-SFT  W  W` | Will wrap selection between two parenthesis' |
| `[`¶ | `LDR  LEFT-CTL` | Will output single left bracket |
| `]`¶ | `LDR  RIGHT-CTL` | Will output single right bracket |
| `[`¶`]` | `LDR  LEFT-CTL  LEFT-CTL` | Will wrap cursor between two brackets' |
| `[`¶`]` | `LDR  RIGHT-CTL  RIGHT-CTL` | Will wrap cursor between two brackets' |
| `[`WORD`]`¶ | `LDR  LEFT-CTL  W` | Will wrap word on cursor between two brackets' |
| `[`WORD`]`¶ | `LDR  RIGHT-CTL  W` | Will wrap word on cursor between two brackets' |
| `[`SELECTION`]`¶ | `LDR  LEFT-CTL  W  W` | Will wrap selection between two brackets' |
| `[`SELECTION`]`¶ | `LDR  RIGHT-CTL  W  W` | Will wrap selection between two brackets' |
| `{`¶ | `LDR  LEFT-ALT` | Will output single left curly brace |
| `}`¶ | `LDR  RIGHT-ALT` | Will output single right curly brace |
| `{`¶`}` | `LDR  LEFT-ALT  LEFT-ALT` | Will wrap cursor between two curly braces' |
| `{`¶`}` | `LDR  RIGHT-ALT  RIGHT-ALT` | Will wrap cursor between two curly braces' |
| `{`WORD`}`¶ | `LDR  LEFT-ALT  W` | Will wrap word on cursor between two curly braces' |
| `{`WORD`}`¶ | `LDR  RIGHT-ALT  W` | Will wrap word on cursor between two curly braces' |
| `{`SELECTION`}`¶ | `LDR  LEFT-ALT  W  W` | Will wrap selection between two curly braces' |
| `{`SELECTION`}`¶ | `LDR  RIGHT-ALT  W  W` | Will wrap selection between two curly braces' |

### Text Expanders

| Output | Sequence | Description |
| :--- | :--- | :--- |
| https://google.ca | `LDR  G  G` | n/a |
| Layout Help URL | `LDR  ESC  ESC  ESC  ESC  ESC` | URL to this readme.md page |
| My Gmail | `LDR  M L T` | You may want to update this before compiling the firmware |

## STEP BY STEP FLASH INSTRUCTIONS
1. Build the Firmware. Run build command in directory: `make dztech/dz65rgb/v2:drootz`
	- Approximate firmware size: 27302/28672 (95%, 1370 bytes free)
2. Flash the Firmware:
    - Open QMK Toolbox Application
    - Open firmware file: dztech_dz65rgb_v2_drootz.hex
    - Unplug keyboard USB, and hold the ESC key while plugging it back in
    - Check that QMK Toolbox displays: *** DFU device connected. 
    - Hit the flash button!
