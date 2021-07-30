#!/bin/sh
# Temporary shell script to find keyboards
#
# This allows us to exclude keyboards by including a .noci file.

find -L keyboards -type f -name rules.mk | grep -v keymaps | sed 's!keyboards/\(.*\)/rules.mk!\1!' | while read keyboard; do
	if [ "$1" = "noci" ]; then
		case "$keyboard" in
			handwired/*)
				;;
			*)
				test -e "keyboards/${keyboard}/.noci" || echo "$keyboard"
				;;
		esac
	else
		echo "$keyboard"
	fi
done
