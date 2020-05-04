# KOY Layout for the atreus62 pcb board
Compile the layout
```bash
qmk compile -kb atreus62 -km ScheiklP
```
disable this service that interfers with the pro micro
```
sudo systemctl stop ModemManager.service
```
and flash it to the board
```bash
qmk flash -kb atreus62 -km ScheiklP
```
