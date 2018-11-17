#!/bin/sh

# Note: This file uses tabs to indent. Please don't mix tabs and spaces.

GENTOO_WARNING="This script will make a USE change in order to ensure that that QMK works on your system. All changes will be sent to the the file /etc/portage/package.use/qmk_firmware -- please review it, and read Portage's output carefully before installing any packages on your system. You will also need to ensure that your kernel is compiled with support for the keyboard chip that you are using (e.g. enable Arduino for the Pro Micro). Further information can be found on the Gentoo wiki."

SLACKWARE_WARNING="You will need the following packages from slackbuilds.org:\n\tarm-binutils\n\tarm-gcc\n\tavr-binutils\n\tavr-gcc\n\tavr-libc\n\tavrdude\n\tdfu-programmer\n\tdfu-util\n\tnewlib\nThese packages will be installed with sudo and sboinstall, so ensure that your user is added to sudoers and that sboinstall is configured."

if grep ID /etc/os-release | grep -qE "fedora"; then
	sudo dnf install \
		arm-none-eabi-binutils-cs \
		arm-none-eabi-gcc-cs \
		arm-none-eabi-newlib \
		avr-binutils \
		avr-gcc \
		avr-libc \
		binutils-avr32-linux-gnu \
		dfu-util \
		dfu-programmer \
		diffutils \
		git \
		gcc \
		glibc-headers \
		kernel-devel \
		kernel-headers \
		make \
		perl \
		unzip \
		wget \
		zip

elif grep ID /etc/os-release | grep -qE 'debian|ubuntu'; then
	DEBIAN_FRONTEND=noninteractive
	DEBCONF_NONINTERACTIVE_SEEN=true
        export DEBIAN_FRONTEND DEBCONF_NONINTERACTIVE_SEEN
	sudo apt-get update
	sudo apt-get install \
		build-essential \
		avr-libc \
		binutils-arm-none-eabi \
		binutils-avr \
		dfu-programmer \
		dfu-util \
		diffutils \
		gcc \
		gcc-arm-none-eabi \
		gcc-avr \
		git \
		libnewlib-arm-none-eabi \
		unzip \
		wget \
		zip

elif grep ID /etc/os-release | grep -q 'arch\|manjaro'; then
	# install avr-gcc 8.1 until 8.3 is available. See #3657 for details of the bug.
	sudo pacman -U https://archive.archlinux.org/packages/a/avr-gcc/avr-gcc-8.1.0-1-x86_64.pkg.tar.xz
	sudo pacman -S \
		arm-none-eabi-binutils \
		arm-none-eabi-gcc \
		arm-none-eabi-newlib \
		avr-binutils \
		avr-libc \
		avr-gcc \
    base-devel \
		dfu-util \
		diff-utils \
		gcc \
		git \
		unzip \
		wget \
		zip
	git clone https://aur.archlinux.org/dfu-programmer.git /tmp/dfu-programmer
	cd /tmp/dfu-programmer
	makepkg -sic
	rm -rf /tmp/dfu-programmer/

elif grep ID /etc/os-release | grep -q gentoo; then
	echo GENTOO_WARNING | fmt
	echo -n "Proceed (y/N)? "
	old_stty_cfg=$(stty -g)
	stty raw -echo
	answer=$( while ! head -c 1 | grep -i '[ny]' ;do true ;done )
	stty $old_stty_cfg
	if echo "$answer" | grep -iq "^y" ;then
		sudo touch /etc/portage/package.use/qmkfirmware
		echo "sys-devel/gcc multilib" | sudo tee --append /etc/portage/package.use/qmkfirmware > /dev/null
		sudo emerge -auN \
			app-arch/unzip \
			app-arch/zip \
			app-mobilephone/dfu-util \
			dev-embedded/avrdude \
			net-misc/wget \
			sys-devel/gcc \
			sys-devel/crossdev
		sudo crossdev -s4 --stable --g =4.9.4 --portage --verbose --target avr
		echo "Done!"
	else
		echo "Quitting..."
	fi

elif grep ID /etc/os-release | grep -q sabayon; then
	sudo equo install \
		app-arch/unzip \
		app-arch/zip \
		app-mobilephone/dfu-util \
		dev-embedded/avrdude \
		net-misc/wget \
		sys-devel/gcc \
		sys-devel/crossdev
	sudo crossdev -s4 --stable --g =4.9.4 --portage --verbose --target avr
	echo "Done!"

elif grep ID /etc/os-release | grep -qE "opensuse|tumbleweed"; then
	CROSS_AVR_GCC=cross-avr-gcc8
	CROSS_ARM_GCC=cross-arm-none-gcc8
	if grep ID /etc/os-release | grep -q "15.0"; then
		CROSS_AVR_GCC=cross-avr-gcc7
		CROSS_ARM_GCC=cross-arm-none-gcc7
	fi
	sudo zypper install \
		avr-libc \
		$CROSS_AVR_GCC \
		$CROSS_ARM_GCC \
		cross-avr-binutils \
		cross-arm-none-newlib-devel \
		cross-arm-binutils cross-arm-none-newlib-devel \
		dfu-tool \
		dfu-programmer \
		gcc \
		unzip \
		wget \
		zip

elif grep ID /etc/os-release | grep -q slackware; then
	printf "$SLACKWARE_WARNING\n"
	printf "\nProceed (y/N)? "
	read -r answer
	if echo "$answer" | grep -iq "^y" ;then
		sudo sboinstall \
			avr-binutils \
			avr-gcc \
			avr-libc \
			avrdude \
			dfu-programmer \
			dfu-util \
			arm-binutils \
			arm-gcc \
			newlib
		echo "Done!"
	else
		echo "Quitting..."
	fi

else
	echo "Sorry, we don't recognize your OS. Help us by contributing support!"
	echo
	echo "https://docs.qmk.fm/#/contributing"
fi
