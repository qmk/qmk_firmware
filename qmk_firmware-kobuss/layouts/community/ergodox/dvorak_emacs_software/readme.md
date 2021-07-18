# Ergodox Dvorak Layout with emacs binding in mind - software version

This configuration is the same as the dvorak_emacs layout, but using a sofware dvorak configuration
instead of a firmware configuration. This layout is for those who run their computer in dvorak mode.

 * Control & Alt key on the thumbs (activated if pressed with another key).
 * In the same way, "U" and "R" are the shift modifier if pressed with another key.
 * "I" and "D" set the layer 1 for the auxiliary keys if pressed with another key.
 * Software layout set to english.

## Keymap Layers
 - L0: dvorak with some customizations (see layout below)
 - L1: auxiliary keys (includes function keys, numpad...)


### Keymap 0: Base layer
Keys with double values (like U/LSft) correspond to the 'tapped' key and the 'held' key, respectively

<pre><code>

,--------------------------------------------------.           ,--------------------------------------------------.
|        |   1  |   2  |   3  |   4  |   5  |  Esc |           |  Esc |   6  |   7  |   8  |   9  |   0  |   =    |
|--------|------|------|------|------|-------------|           |------|------|------|------|------|------|--------|
|   ~    |  '   |   ,  |   .  |   P  |   Y  |   [  |           |   ]  |   F  |   G  |   C  |   H  |   L  |   /    |
|--------|------|------|------|------|------|   {  |           |   }  |------|------|------|------|------|--------|
|  Tab   |   A  |   O  |   E  |U/LSft| I/L1 |------|           |------|  D/L1|R/RSft|   T  |   N  |   S  |   -    |
|--------|------|------|------|------|------| LGUI |           | LGUI |------|------|------|------|------|--------|
| {/LSft |   ;  |   Q  |   J  |   K  |   X  |      |           |      |   B  |   M  |   W  |   V  |   Z  | }/RSft |
`--------|------|------|------|------|-------------'           `-------------|------|------|------|------|--------'
  |      |      |      |      | ~L1  |                                       | ~L1  |      |      |   \  |      |
  `----------------------------------'                                       `----------------------------------'
                                       ,-------------.       ,-------------.
                                       | HOME |  END |       | LEFT | RIGHT|
                                ,------|------|------|       |------|--------|------.
                                | BSPC |  DEL | PGUP |       |  UP  | SPACE  |RETURN|
                                |  /   |  /   |------|       |------|   /    |  /   |
                                | LCTL | LALT |PGDWN |       | DOWN | LALT   | LCTL |
                                `--------------------'       `----------------------'

</pre></code>

### Keymap 1: Aux layer

<pre><code>

,--------------------------------------------------.           ,--------------------------------------------------.
|  VolUp |      |      |      |      |      | SLEEP            | PWR  |      |      |      |      |      |        |
|--------|------|------|------|------|-------------|           |------|------|------|------|------|------|--------|
|  VolDn |  F1  |  F2  |  F3  |  F4  |      |      |           |      |      |   7  |   8  |   9  |   *  |        |
|--------|------|------|------|------|------|      |           |      |------|------|------|------|------|--------|
|        |  F5  |  F6  |  F7  |  F8  | TRANS|------|           |------|TRANS |   4  |   5  |   6  |   +  |        |
|--------|------|------|------|------|------|      |           |PSCR  |------|------|------|------|------|--------|
|  TRANS |  F9  |  F10 |  F11 |  F12 |      |      |           |      |      |   1  |   2  |   3  |   /  |  TRANS |
`--------|------|------|------|------|-------------'           `-------------|------|------|------|------|--------'
  |CTRL-S|CTRL-Z|CTRL-X|CTRL-C| TRANS|                                       | TRANS|    . |   0  |   =  |      |
  `----------------------------------'                                       `----------------------------------'
                                       ,-------------.       ,-------------.
                                       | TRANS| TRANS|       | TRANS| TRANS|
                                ,------|------|------|       |------|------|------.
                                |      |      | TRANS|       | TRANS|      |      |
                                |TRANS |TRANS |------|       |------| TRANS| TRANS|
                                |      |      | TRANS|       | TRANS|      |      |
                                `--------------------'       `--------------------'

</pre></code>



## Generation of .hex file
> In the "qmk_firmware/keyboards/ergodox" directory.

> Execute "make dvorak_emacs". Then the hex file "ergodox_ez_dvorak_emacs.hex" is in the root directory : "qmk_firmware".

> Flash with `teensy_loader` binary
