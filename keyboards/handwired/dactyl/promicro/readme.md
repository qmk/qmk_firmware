# Dactyl (Pro Micro)

The modernised Dactyl uses two Arduino Pro Micro controllers.
Wiring of the rows to each micro controller is identical approach to the Dactyl ManuForm, in that:
- Left Half: Row pins are wired to this controller in sequence as specified (in [info.json](./info.json)).
- Right Half: Row pins are wired to this controller in reverse order.

| Row# | Left | Right | 
| :---: | :---: | :---: |
| Row1 | F6 | B6 |
| Row2 | F7 | B2 |
| Row5 | B1 | B3 |
| Row4 | B3 | B1 |
| Row5 | B2 | F7 |
| Row6 | B6 | F6 |
