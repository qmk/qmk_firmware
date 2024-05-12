
## Setup
1. Install the QMK WSL environment
2. Clone our fork
3. Run these commands
```
    qmk setup -h <path to fork>
    git submodule init
    git submodule update
```
## Build
```
    qmk compile
```
## Flash
1. Make sure the board is connected through (qmk toolbox is a good tool)
2. Run this command  
```
    sudo qmk flash -kb 0_f103_split -km default -bl dfu-util-split-right
    sudo qmk flash -kb 0_f103_split -km default -bl dfu-util-split-left
```
