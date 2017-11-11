This is a dual English-Japanese keymap that utilises a thumb-shift system for Japanese input. You can read more about this layout on my blog [here](https://ishigoya.com). 

### Some Editing Necessary
The system I created this on is a Chromebook, and uses a Japanese keymap, so some of the key mappings may not be the same as those on your system. In particular, the Escape key on layer 0 is mapped to KC_LCTL.

### Layouts
------
#### English layer - layer 0
The English layout is a modified Workman layout, and is pictured below:

![English layout](https://i.imgur.com/X1j2Mya.png)

Some of the punctuation keys have been moved to a separate number/symbol layer.

#### Number / Symbol layer - layer 6

The Number / Symbol layer is reachable through a ACTION_LAYER_MOMENTARY function. The blue LED is illuminated when this layer is active. It is accessible from the English or Japanese layers.

![Number layout](https://i.imgur.com/oNSNXPU.png)

#### Japanese layers - layers 1-5

There are 5 layers involved in Japanese input. The TOJPLOUT macro is mapped to the En / 和 button, and switches default layer between layer 0 (English) and 1 (main Japanese layer). When layer 1 is the default layer, the red LED is on. It also outputs the ZKHK button to change the input method language.

On keypress, strings of romaji characters are output by the keyboard using macros, and these simulate the input of individual keys on a latin keyboard.

![Japanese layout](https://i.imgur.com/qMvt92j.png)

Layer 1 is the JP layer. Keys on this layer correspond to singleton keys, or keys on the bottom row where a key is shared. For example, pressing the "ふ や" key outputs `ふ` (or "fu").

Layer 2 is the JPXON layer, and is active while holding the Fn key. This prints keys that are prefaced by "x" when writing in romaji. For example, pressing the "ふ や" key while holding the Fn key outputs `ゃ` (or "xya").

Layer 3 is the JPKAZARI layer, and is active while holding the 飾り key. This provides letters with dakuten. For example, pressing the "ふ や" key while holding the 飾り key outputs `ぶ` (or "bu").

Layer 4 is the JPTOPROW layer, and is active while holding the シフト key. Keys on this line correspond to top row keys on shared keys in the image. For example, pressing the "ふ や" key while holding the シフト key outputs `や` (or "ya").

Layer 5 is the JPTRKZ layer, and is active while holding both the シフト key and the 飾り key. This layer contains handakuten keys. For example, pressing the "ふ や" while holding both the シフト key and the 飾り key outputs `ぷ` (or "pu").

I've also separated out the #define sections and the macros required for kana for easy copying, in case anyone else should wish to make a kana-based layout.

When tapped, the シフト key acts as a space key, and the 飾り key acts as a return key. This allows them to function as 変換 and 無変換, respectively, in many IMEs.

Furthermore the Fn key, when tapped, acts as an F7 key, providing easy switching to katakana in many IMEs.

### Other features
The cut/copy button gives copy functionality on a short press, and cut functionality on a long press.

The tmux prefix button outputs Control-B.

The Control & Shift key acts as holding the control and shift keys at the same time.

SelAll outputs Control-A.

Undo outputs Control-Z.
