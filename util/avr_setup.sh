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
    dfu-util

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
    dfu-util

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
    dfu-util

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
    dfu-programmer

fi
