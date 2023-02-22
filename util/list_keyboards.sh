#!/bin/sh
# Temporary shell script to find keyboards
#
# This allows us to include DEFAULT_FOLDER targets.

find -L keyboards -type f -name rules.mk | grep -v keymaps | sed 's!keyboards/\(.*\)/rules.mk!\1!'
