# Dactyl (Pro Micro)

The modernised Dactyl uses two Pro Micro development boards, one per half. The method of wiring matrix rows is identical to the Dactyl ManuForm, in that:
- Left Half: Row pins are wired to controller in sequence as specified in [keyboard.json](./keyboard.json).
- Right Half: Row pins are wired to controller in reverse order of Left Half.

| Row# | Left | Right | 
| :---: | :---: | :---: |
| Row1 | F6 | B6 |
| Row2 | F7 | B2 |
| Row5 | B1 | B3 |
| Row4 | B3 | B1 |
| Row5 | B2 | F7 |
| Row6 | B6 | F6 |
