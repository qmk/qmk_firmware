# brandonschlack's Macropad/Lightroom layout for BDN9
##### 2 encoders required

![brandonschlack BDN9](https://i.imgur.com/pai9M0m.jpg)

I built this pad to match my Lightroom photo editing workflow using
[Lightroom Classic Keyboard shortcuts](https://helpx.adobe.com/lightroom-classic/help/keyboard-shortcuts.html), and added on general macropad layers along the way.

I use macOS, so shortcuts and macros are configured as such. Encoder functionality is in the header of the tables, as clockwise/counterclockwise.

---

## Macropad Layers

### Reeder Layer
This layer is used for browsing [Reeder](https://reederapp.com/), an awesome RSS reader for Mac

| Prev/Next Item | **Knobs** | Prev/Next Subscription |
| --- | --- | --- |
| Open Item in Browser | Star Item/Save for Later | Sync  |
| Command+Tab | Toggle Read Status | Clear Read Items |
| Starred Items | Unread Items | All Items |


### Media Layer
This layer is used for media controls. Player button is a hotkey to focus the current media player with [BeardedSpice](https://beardedspice.github.io/)

| Volume Down/Up | **Knobs** | Prev/Next Track |
| --- | --- | --- |
| Mute | Current Player | Play/Pause |
| YouTube Rewind 10s (J) | YouTube Play/Pause (K) | YouTube Forward 10s (L) |
| Left | Space | Right |


### Navigation Layer
This layer is used for general window navigation around macOS

| Scroll Up/Down | **Knobs** | Next/Prev Tab |
| --- | --- | --- |
| Reopen Tab | Cmd+Tab | Close Tab |
| Page Down | Up | Page Up |
| Left | Down | Right |


### Macro Layer
This layer is used to send generic macro keys, meant to be remapped based on current app with [Karabiner](https://pqrs.org/osx/karabiner/)

| +/- | **Knobs** | =/. |
| --- | --- | --- |
| 1 | 2 | 3 |
| 4 | 5 | 6 |
| 7 | 8 | 9 |


## Lightroom Layers

### LR Navigation Layer
This layer is used for navigating Grid View in the Library Module.

| Inc/Dec Thumbnail Size | **Knobs** | Scroll Up/Dn Grid Thumbnails |
| --- | --- | --- |
| Review Layer | Cycle Grid View options | Edit Layer |
| Start of Grid View | Up | End of Grid View |
| Left | Down | Right |


### Lightroom Review Layer
This layer is used for Reviewing, Rating, and Culling images with the Loupe View in the Library Module.

| Inc/Dec Star Rating | **Knobs** | Inc/Dec Flag Status |
| --- | --- | --- |
| LR Navigation Layer | Yellow Label | Edit Layer |
| Remove Star Rating | Green Label | Unflag Photo |
| Left | Blue Label | Right |


### Lightroom Edit Layer
This layer is used for editing photos in the Develop Module

| Next/Prev Basic Panel Settings | **Knobs** | Inc/Dec Selected Slider |
| --- | --- | --- |
| Review Layer | Toggle Before View | LR Navigation Layer  |
| Flag Rejected | Undo | Flag Picked |
| Left | Redo | Right |


## Meta Layers

### Light Layer
This layer is used to control lighting for the pad. Currently nothing is saved in EEPROM, so it will reset after power loss. Also currently my userspace layer colors take priority until I build out that feature. This layer is accessed with a double tap of the middle right key via [tap dance](https://docs.qmk.fm/#/feature_tap_dance). A triple tap of the middle right key will also toggle lights on/off.

| Inc/Dec RGB Hue | **Knobs** | Inc/Dec RGB Saturation |
| --- | --- | --- |
| RGB Toggle | RGB Value Increase | Toggle Layer Off |
| RGB Mode Prev | RGB Value Decrease | RGB Mode Next |
| RGB Layer Indication | Cycle RGB Themes | XXX |


### Adjust Layer
This layer is used as a meta layer for the pad. This layer is accessed with a double tap of the bottom right key via [tap dance](https://docs.qmk.fm/#/feature_tap_dance).

| XXX | **Knobs** | XXX |
| --- | --- | --- |
| MAKE | **Reeder** Layer | **Light** Layer |
| **Media** Layer  | **Navigation** Layer | **Keypad** Layer |
| **Lightroom Review** Layer | **Lightroom Navigation** Layer | **Lightroom Edit** Layer |

