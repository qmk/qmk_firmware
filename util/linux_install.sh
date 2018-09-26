#!/bin/sh
if grep ID /etc/os-release | grep -qE "rhel|fedora"; then
	# RPM based OS
	sudo dnf install gcc unzip wget zip dfu-util dfu-programmer avr-gcc \
	    avr-libc binutils-avr32-linux-gnu arm-none-eabi-gcc-cs \
	    arm-none-eabi-binutils-cs arm-none-eabi-newlib
elif grep ID /etc/os-release | grep -q debian; then
	sudo apt-get update
	sudo apt-get install gcc unzip wget zip gcc-avr binutils-avr avr-libc \
	    dfu-programmer dfu-util gcc-arm-none-eabi binutils-arm-none-eabi \
	    libnewlib-arm-none-eabi
elif grep ID /etc/os-release | grep -q 'arch\|manjaro'; then
  # install avr-gcc 8.1 until 8.3 is available. See #3657 for details of the bug.
  sudo pacman -U https://archive.archlinux.org/packages/a/avr-gcc/avr-gcc-8.1.0-1-x86_64.pkg.tar.xz
	sudo pacman -S gcc unzip wget zip avr-binutils avr-libc \
	    dfu-util arm-none-eabi-gcc arm-none-eabi-binutils \
	    arm-none-eabi-newlib
	git clone https://aur.archlinux.org/dfu-programmer.git /tmp/dfu-programmer
	cd /tmp/dfu-programmer
	makepkg -sic
	rm -rf /tmp/dfu-programmer/
elif grep ID /etc/os-release | grep -q gentoo; then
  echo "This script will make a USE change in order to ensure that that QMK works on your system. All changes will be sent to the the file /etc/portage/package.use/qmk_firmware -- please review it, and read Portage's output carefully before installing any packages on your system. You will also need to ensure that your kernel is compiled with support for the keyboard chip that you are using (e.g. enable Arduino for the Pro Micro). Further information can be found on the Gentoo wiki."
  echo -n "Proceed (y/N)? "
  old_stty_cfg=$(stty -g)
  stty raw -echo
  answer=$( while ! head -c 1 | grep -i '[ny]' ;do true ;done )
  stty $old_stty_cfg
    if echo "$answer" | grep -iq "^y" ;then
      sudo touch /etc/portage/package.use/qmkfirmware
      echo "sys-devel/gcc multilib" | sudo tee --append /etc/portage/package.use/qmkfirmware > /dev/null
      sudo emerge -auN sys-devel/gcc app-arch/unzip app-arch/zip net-misc/wget app-mobilephone/dfu-util sys-devel/crossdev dev-embedded/avrdude
      sudo crossdev -s4 --stable --g =4.9.4 --portage --verbose --target avr
      echo Done!
    else
    echo "Quitting..."
fi
else
	echo "Sorry, we don't recognize your OS. Help us by contributing support!"
	echo
	echo "https://docs.qmk.fm/contributing.html"
fi
