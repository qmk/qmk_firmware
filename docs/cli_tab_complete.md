# Tab Completion for QMK

If you are using Bash 4.2 or later, Zsh, or FiSH you can enable Tab Completion for the QMK CLI. This will let you tab complete the names of flags, keyboards, files, and other `qmk` options.

## Setup

There are several ways you can setup tab completion.

### For Your User Only

Add this to the end of your `.profile` or `.bashrc`:

    source ~/qmk_firmware/util/qmk_tab_complete.sh

If you put `qmk_firmware` into another location you will need to adjust this path.

### System Wide Symlink

If you want the tab completion available to all users of the system you can add a symlink to the `qmk_tab_complete.sh` script:

    ln -s ~/qmk_firmware/util/qmk_tab_complete.sh /etc/profile.d/qmk_tab_complete.sh

### System Wide Copy

In some cases a symlink may not work. Instead you can copy the file directly into place. Be aware that updates to the tab complete script may happen from time to time, you will want to recopy the file periodically.

    cp util/qmk_tab_complete.sh /etc/profile.d
