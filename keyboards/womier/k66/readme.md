# Womier / K66

K66

Keyboard Maintainer: toast, xyz
Hardware Supported: SN32F248BF

# Womier K66 QMK

## FAQ:

1. What is QMK for?

   QMK lets you create a custom fimrware to your keyboard so you can change the keymap to fit your needs.

2. Is there any chance that this process bricks my keyboard?

   Yes and we are not responsible for that.

3. Is it worth it?

   If you don't miss any key on the original firmware, it's not worth it.

   If you boughtthe kb only because of the LEDs, it's not worth it.

   If you like creating custom keymaps, it's SUPER worth it.

4. Do I lose the LEDs if I flash QMK?

   Just the edge leds will be turned off. But keep in mind that the stock LEDs effects are lost. There are some custom effects made by users, but they are not the same as the ones that comes with the kb... The color picking mode is also lost. You can try to create custom effects but that will require some knowledge.


############## flash jlink with zadig
grab msys 2. not mingw.
pull qmk
pacman --needed --noconfirm --disable-download-timeout -S git mingw-w64-x86_64-toolchain mingw-w64-x86_64-python3-pip
cd qmk_firmware/util
run msys_setup.sh or w/e

Steps to flash your keyboard:

1. Download https://www.msys2.org/ and follow the all the steps of the installation guide
2. Clone the QMK firmware to your msys user directory, usually c:\msys64\home\[user]\ using the following command:

```
git clone -b womier-k66-rgb-support --recurse-submodules -j8 https://github.com/smp4488/qmk_firmware.git
```

3. Search for the application "MSYS MinGW 64-bit" or "MSYS2 MSYS" and open it. Navigate to ~\qmk_firmware\util and run ./msys2_install.sh

4. After successful installation close "MSYS MinGW 64-bit". This may take a while.

5. Open "MSYS MinGW 64-bit" or "MSYS2 MSYS" again, navigate to ~\qmk_firmware and run:

```
sed -i 's/Vector84,/RgbIsr,/g' lib/chibios/os/common/startup/ARMCMx/compilers/GCC/vectors.S
```

6. Verify changes have been made on 2 and only 2 lines to the vectors.S file

7) Run `make womier/k66:default`

8) If everything goes fine, there should be a folder called ".build" with a .bin file (and some other things)

9) Now it's time to flash that .bin file into your keyboard. To do that, clone https://github.com/xyzz/womier-flasher and follow the readme to start the program

10) With the program open, you should plug in your keyboard, click "refresh" and select "Womier K66". Note: If you see a list of 5 "Womier K66", you'll have to try the next step for each one of them until the keyboard stops responding.

11) Click on "Reboot to Bootloader". The keyboard should stop responding.

12) Click on "Flash Jumploader".

13) Click on "Flash QMK" and select the .bin file we talked about in step 8.

14) If you did everything correct, your kb should be working now. Some basic controls are:
    - CAPS works like FN
    - CAPS + S + 1 or 2 change the LED effect
    - CAPS + S + Insert or Delete change the LED brightness

15. To take advantage of QMK, you'll have to read the docs a little to understand how the keymap works.
    - The file with the keymap is in keyboards/womier/k66/keymaps/default/keymap.c
    - The keycodes are listed in https://beta.docs.qmk.fm/using-qmk/simple-keycodes/keycodes
    - More info about keymaps here: https://beta.docs.qmk.fm/using-qmk/guides/keymap
