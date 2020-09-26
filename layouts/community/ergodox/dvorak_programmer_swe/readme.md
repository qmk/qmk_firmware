# ErgoDox EZ Dvorak Programmer SWEDISH

Dvorak layout adjusted for a suitable programmer layout and swedish special characters added:

* åäö characters added
* Layout for common vb.net keywords
* Common Visual Studio commands like Save, Build, Debug

TODO:

* (Layer 4 is qwerty (for easier gaming & less fortunate keyboard users)) Like this idea, will add it later on

Known issues:

* Keymap 2 modifier has not gotten its place yet..


## Changelog
* 2019-03-11
  * Added currency $, £, € to keymap 3
  * Added pipe character to keymap 3
  * Added the acute accent character to keymap 3

* 2019-03-08
  * Switched position on Alt and Alt-shift
  * Added tilde character to symbol layer
  * Added Print Screen to keymap 3
  * Added ' (NO_APOS) to keymap 3
  * Added how to install help in this readme

* 2017-05-16
  * Initial release


# How to install - reminder
0. Docs:  https://docs.qmk.fm/#/newbs
1. Download flashing tool - teensy (from ergodox-ez visual designer)
2. Setup build environment: https://docs.qmk.fm/#/newbs_getting_started

QUICK HOWTO WSL:  (this is not supported anymore it seems, why?)
The Toolchain setup is done through the Windows Subsystem for Linux, and the process is fully automated. If you want to do everything manually, there are no other instructions than the scripts themselves, but you can always open issues and ask for more information.
Open "Bash On Ubuntu On Windows" from the start menu.
Go to the directory where you cloned qmk_firmware. Note that the paths start with /mnt/ in the WSL, so you have to write for example cd /mnt/c/path/to/qmk_firmware.
Run util/wsl_install.sh and follow the on-screen instructions.
Close the Bash command window, and re-open it.
You are ready to compile and flash the firmware!

3. Build the firmware with:  
Run the following in the root qmk folder:
make KEYBOARD=ergodox_ez KEYMAP=dvorak_programmer_swe


# Author
Christian Westerlund
cwesterlund @ github

Thanks to the author of keymap csharp_dev for inspiration!