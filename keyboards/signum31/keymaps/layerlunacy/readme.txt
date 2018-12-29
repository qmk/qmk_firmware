This keyboard was built using the following steps:

Download the appropriate json file from
http://troyfletcher.net/config.html

Importing it in
https://kbfirmware.com/
and then downloading the zip file from the "compile" tab.

Using the video tutorial on QMK from Chokkan on YT to 
-setup MSYS2
-fork and clone the GitHub repo
-compile it for the first time

Problems encountered:
-cloning with MSYS2 wasn't successful -> used Ubuntu as a Linux Subsystem for Windows to clone via HTTPS
-all further steps were done in the Ubuntu subsystem installation
-install make: "sudo apt install make"
-first attempt to build via "make signum_dz:dz_v1" failed, because avr-gcc wasn't found
-installing avr-gcc or gcc-avr wasn't successful, as the package couldn't be located
-"sudo apt update" and "sudo apt upgrade" didn't fix the problem

According to this reddit thread
https://www.reddit.com/r/MechanicalKeyboards/comments/8v1j91/qmk_question_unable_to_locate_avrgcc/
I downloaded the Arduino IDE, which includes the required package, and added the path to the $PATH variable:

multiple versions were tried, not sure, which one worked:
-"export PATH=$PATH:/c/users/_____/Desktop/arduino-1.8.8/hardware/tools/avr/lib/gcc/avr"
-"export PATH=$PATH:/C/Users/_____/Desktop/arduino-1.8.8/hardware/tools/avr/lib/gcc/avr"
-"export PATH=$PATH:/mnt/c/Users/_____/Desktop/arduino-1.8.8/hardware/tools/avr/lib/gcc/avr"
where "_____" has to be substituted with your username and the Arduino IDE was located on the Desktop.

It wasn't tried to add this line to the ~/.bashrc file, yet.

-then "sudo apt install gcc-avr" worked
-the build process failed again, complaining about a missing "avr/io.h"

According to this StackOverflow thread
https://stackoverflow.com/questions/34184335/avr-gcc-command-not-found-on-ubuntu
it seemd lilke installing avr-libc would fix the issue

-"sudo apt install avr-libc"
-then the build process would reach my keymap for the first time
-after fixing some typos, removing a call to UC() and commenting out some code in "action_get_macro", the build succeeded for the first time
-the hex file was located in the hidden folder /qmk_firmware/.build
-the make process said, the file has 17676 bytes, Windows said it had 49KB ???

The RESET key was put in column 0, row 4, which should be controlled by pins B4 and B2.
