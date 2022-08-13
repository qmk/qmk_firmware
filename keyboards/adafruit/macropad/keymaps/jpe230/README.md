# Jpe230's Adafruit Macropad Layout

## Layers
This keymap includes the following layers:
- Media Controls
- Teams Macros
- Edge/Chrome Macrops
- VSCode Macros
- Visual Studio Macros
- Discord Macros
- Configuration
- Another Configurations
- Lockscreen (Unusable in the public version)
- Time-based one-time password (Unusable in the public version)
- Empty Layers (Mainly for showcase)


## OLED
There are 3 oled `renderers`:
- Indicators: Shows visually the current layer
- Bongo Cat: Shows Bongo Cat
- Logo: Shows QMK Logo

## RGB
The RGB can display 1 of 3 things:
- Indicators for each key in each layer
- Masking the current RGB animation in indicators keys
- Show the full RGB animations

## RTC
This keymap uses a DS3231 to show the current time and calculate the TOPT (Unusable in the public version)

## Transpiler
Due to the complexity of this keymap, it uses a transpiler to create each layer
`python3 transpiler/transpile_keymap.py`
