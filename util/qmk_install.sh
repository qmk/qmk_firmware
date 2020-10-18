#!/bin/sh
# Pick the correct install script based on the current OS

util_dir=$(dirname "$0")

case $(uname -a) in
	*Darwin*)
		exec "${util_dir}/macos_install.sh"
	;;
	*FreeBSD*)
		exec "${util_dir}/freebsd_install.sh"
	;;
	*Linux*)
		exec "${util_dir}/linux_install.sh"
	;;
	MINGW64_NT*)
		exec "${util_dir}/msys2_install.sh"
	;;
	MSYS_NT*|MINGW32_NT*)
		echo "Please open a MinGW 64-bit terminal window and re-run this script."
		exit 1
	;;
	*)
		echo "Environment not supported. Please see https://docs.qmk.fm for details on how to configure the QMK Firmware build tools manually."
		exit 1
	;;
esac
