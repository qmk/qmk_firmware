#!/bin/sh
# Pick the correct install script based on the current OS

util_dir=$(dirname "$0")

case $(uname) in
	Darwin)
		exec "${util_dir}/macos_install.sh"
	;;
	Linux)
		exec "${util_dir}/linux_install.sh"
	;;
	MSYS_NT*|MINGW_64*)
		exec "${util_dir}/msys2_install.sh"
	;;
esac
