# rsmorley's endgame config

### This config goes to endgame as t -> infinity

This layout has evolved through various 40% keebs. Starting with a JD40 ii
and then a MiniVan and finally a Reviung39s. The Reviung challenged me to 
whittle down my keymap to only the ensentials. This required that I learn
more advanced QMK features and lead to this config.

Layers 1 and 2 are accessed by holding Enter and Space respectively.
RGB controls are accessed by holding down Enter and Space simultaneously.

Layers:
* NUM_SCHAR - numbers and special characters
* NAV_MEDIA - arrow keys and media controls
* ADJUST - RGB controls and reset

Base Layer, bottom row: Tap Enter, Hold Layer1    | Tap F3, Hold Cmd   | Tab Space, Hold Layer2

Recent changes:
* lowering my TAPPING_TERM to make QMK keycodes work with my typing speed.
  * reverted
  * Doesn't appear to have resolved the issue. Need to check solder joints on switch and associated diode.
* adding dedicated Copy/Paste key via tap_dance.