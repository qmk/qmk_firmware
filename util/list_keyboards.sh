#!/bin/sh
# Temporary shell script to find keyboards
#
# This allows us to exclude keyboards by including a .noci file.

find -L keyboards -type f -name rules.mk | grep -v keymaps | while read keyboard; do
	keyboard=$(echo $keyboard | sed 's!keyboards/\(.*\)/rules.mk!\1!')

	[ "$1" = "noci" -a -e "keyboards/${keyboard}/.noci" ] || echo "$keyboard"
done
