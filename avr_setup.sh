#!/usr/bin/env bash
# This script will attempt to setup the Linux dependencies for compiling QMK/TMK

# This could probably go much lower, but since we are including an Arch vagrant,
# making it the first match makes sense

if [[ -n "$(type -P pacman )" ]]; then
  # Arch linux and derivatives like Apricity
  pacman -S --needed --noconfirm base-devel avr-gcc avr-binutils avr-libc dfu-utils

elif [[ -n "$(type -P apt-get)" ]]; then
  # Debian and derivatives
  apt-get install -y build-essential gcc unzip wget zip gcc-avr binutils-avr avr-libc
  
elif [[ -n "$(type -P yum)" ]]; then
  # Fedora, CentOS or RHEL and derivatives
  yum -y install gcc glibc-headers kernel-devel kernel-headers make perl git wget

elif [[ -n "$(type -P zypper)" ]]; then
  # openSUSE
  zypper --non-interactive install git make gcc kernel-devel patch wget

fi
