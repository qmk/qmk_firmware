#!/bin/sh
# Pick the correct install script based on the current OS

util_dir=$(dirname "$0")

case $(uname -a) in
	*Darwin*)
		exec "${util_dir}/macos_install.sh"
	;;
	*Linux*Microsoft*)
		exec "${util_dir}/wsl_install.sh"
	;;
	*FreeBSD*)
		exec "${util_dir}/freebsd_install.sh"
	;;
	*Linux*)
		exec "${util_dir}/linux_install.sh"
	;;
	MSYS_NT*|MINGW64_NT*|MINGW32_NT*)
		exec "${util_dir}/msys2_install.sh"
	;;
	*)
		echo "Environment not supported. Please see https://docs.qmk.fm for details on how to configure the QMK Firmware build tools manually."
	;;
esac
