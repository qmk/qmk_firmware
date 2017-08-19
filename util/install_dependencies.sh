#!/usr/bin/env bash
# This script will attempt to setup the Linux dependencies for compiling QMK/TMK

# This could probably go much lower, but since we are including an Arch vagrant,
# making it the first match makes sense

if [[ -n "$(type -P pacman )" ]]; then
  # Arch linux and derivatives like Apricity
  # Future improvements:
  # Allow user to speed up package installs using powerpill/wget tweaks
  # Always run the pacman mirror update script if possible when vagrant comes up
  # This will ensure that users never get stalled on a horribly slow mirror
  pacman -Syyu --needed --noconfirm
  pacman -S --needed --noconfirm \
    base-devel \
    avr-gcc \
    avr-binutils \
    avr-libc \
    dfu-util \
    arm-none-eabi-gcc \
    arm-none-eabi-binutils \
    arm-none-eabi-newlib \
    git \
    diffutils

elif [[ -n "$(type -P apt-get)" ]]; then
  # Debian and derivatives
  # This block performs completely non-interactive updates {{
  export DEBIAN_FRONTEND=noninteractive
  export DEBCONF_NONINTERACTIVE_SEEN=true
  echo "grub-pc hold" | dpkg --set-selections
  apt-get -y update
  apt-get -y --allow-unauthenticated upgrade \
	  -o Dpkg::Options::="--force-confdef" \
	  -o Dpkg::Options::="--force-confold"
  # }}
  apt-get install -y \
    build-essential \
    gcc \
    unzip \
    wget \
    zip \
    gcc-avr \
    binutils-avr \
    avr-libc \
    dfu-programmer \
    dfu-util \
    gcc-arm-none-eabi \
    binutils-arm-none-eabi \
    libnewlib-arm-none-eabi \
    git \
    diffutils

elif [[ -n "$(type -P yum)" ]]; then
  # Fedora, CentOS or RHEL and derivatives
  yum -y makecache && yum -y update
  yum -y install \
    gcc \
    glibc-headers \
    kernel-devel \
    kernel-headers \
    make \
    perl \
    git \
    wget \
    avr-binutils \
    avr-gcc \
    avr-libc \
    dfu-programmer \
    dfu-util \
    arm-none-eabi-gcc-cs \
    arm-none-eabi-newlib \
    git \
    diffutils
  # The listed eabi pacackes do unfortunately not exist for CentOS,
  # But at least in Fedora they do, so try to install them anyway
  # TODO: Build them from sources, if the installation fails

elif [[ -n "$(type -P zypper)" ]]; then
  # openSUSE
  zypper --non-interactive refresh  && zypper --non-interactive update
  zypper --non-interactive install \
    git \
    make \
    gcc \
    kernel-devel \
    patch \
    wget \
    dfu-programmer \
    git \
    diffutils
  # TODO: The avr and eabi tools are not available as default packages, so we need 
  # another way to install them

elif [[ -n "$(type -P pkg)" ]]; then
  # FreeBSD
  pkg update
  pkg install -y \
    git \
    wget \
    gmake \
    gcc \
    zip \
    unzip \
    avr-binutils \
    avr-gcc \
    avr-libc \
    dfu-programmer \
    dfu-util \
    arm-none-eabi-gcc \
    arm-none-eabi-binutils \
    arm-none-eabi-newlib \
    diffutils
elif [[ -n "$(type -P emerge)" ]]; then
    echo 'Please check that your gcc is built with the multilib use flag enabled.'
    emerge -vq sys-devel/crossdev
    USE="-openmp -hardened -sanitize -vtv" crossdev -s4 --stable --g =4.9.4 --portage --verbose --target avr
fi
