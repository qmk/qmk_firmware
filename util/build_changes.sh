#!/bin/bash

# QMK_CHANGES=$(git diff --name-only master...) # grab local changes
QMK_CHANGES=$(cat) # read changes from stdin
QMK_KEYBOARDS=$(make list-keyboards)

NUM_CORE_CHANGES=$(echo "$QMK_CHANGES" | grep -Ecv -e '^(docs/)' -e '^(keyboards/)' -e '^(users/)' -e '^(layouts/)' -e '^(util/)' -e '^(lib/python/)' -e '^(bin/qmk)' -e '^(requirements.txt)' -e '^(Makefile)' -e '^(.github/workflows/)')

if [ "$NUM_CORE_CHANGES" != "0" ]; then
    echo "Making default keymaps for all keyboards"
    make all:default
    exit $?
fi

exit_code=0

for KB in $QMK_KEYBOARDS; do
	KEYBOARD_CHANGES=$(echo "$QMK_CHANGES" | grep -E '^(keyboards/'${KB}'/)')
	if [[ -z "$KEYBOARD_CHANGES" ]]; then
		# skip as no changes for this keyboard
		continue
	fi

	KEYMAP_ONLY=$(echo "$KEYBOARD_CHANGES" | grep -cv /keymaps/)
	if [[ $KEYMAP_ONLY -gt 0 ]]; then
		echo "Making all keymaps for $KB"
		make ${KB}:all
		: $((exit_code = $exit_code + $?))
	else
		CHANGED_KEYMAPS=$(echo "$KEYBOARD_CHANGES" | grep -oP '(?<=keyboards/'${KB}'/keymaps/)([a-zA-Z0-9_-]+)(?=\/)')
		for KM in $CHANGED_KEYMAPS ; do
			echo "Making $KM for $KB"
			make ${KB}:${KM}
			: $((exit_code = $exit_code + $?))
		done
	fi
done

# As there is no clean way to associate community layouts or users with boards,
# we blindly build all keymaps for that user. This might incrementally build
# a user keymap again but its better to be safe than sorry...
USER_CHANGES=$(echo "$QMK_CHANGES" | grep -E -e '^(users/)' | cut -d "/" -f2)
USER_COMMUNITY=$(echo "$QMK_CHANGES" | grep -E -e '^(layouts/community/)' | cut -d "/" -f4)
USERS=$(echo "$USER_CHANGES" "$USER_COMMUNITY" | sort -u)

for USER in $USERS; do
	make all:$USER
done

exit $exit_code
