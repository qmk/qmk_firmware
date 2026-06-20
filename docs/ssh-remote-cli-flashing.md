# Command Line Flashing Through SSH on Remote Linux Session

To flash QMK through a DFU bootloader while logged into a remote linux machine, and the keyboard target plugged into USB on that remote machine, you will need to modify the UDEV rules to specify the user. The included `50-qmk.rules` file assumes that you are logged in locally to the machine.

Modify 
```
/etc/udev/rules.d/50-qmk.rules
```

```
IS:
# Apply tag if QMK endpoint found
ENV{ID_QMK}=="1", TAG+="uaccess"
```
```
SHOULD BE:
# Apply tag if QMK endpoint found
ENV{ID_QMK}=="1", GROUP="qmk", MODE="0660"
```

Add your username to `qmk` group. Log out and log back in for the new group to become effective.

You can now run through the SSH session to flash the keyboard.
```sh
qmk flash -kb <my_keyboard> -km <my_keymap>
```
