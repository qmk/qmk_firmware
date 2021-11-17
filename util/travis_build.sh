#!/bin/bash

source util/travis_utils.sh

NUM_CORE_CHANGES=$(echo "$QMK_CHANGES" | grep -Ecv -e '^(docs/)' -e '^(keyboards/)' -e '^(layouts/)' -e '^(util/)' -e '^(lib/python/)' -e '^(bin/qmk)' -e '^(requirements.txt)' -e '(.travis.yml)')

if [[ "$TRAVIS_COMMIT_MESSAGE" == *"[skip build]"* ]]; then
    echo "Skipping due to commit message"
    exit 0
fi

if [ "$LOCAL_BRANCH" == "master" ] || [ "$NUM_CORE_CHANGES" != "0" ]; then
    echo "Making default keymaps for all keyboards"
    make all:default
    exit $?
fi

exit_code=0

for KB in $(make list-keyboards); do
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

exit $exit_code
