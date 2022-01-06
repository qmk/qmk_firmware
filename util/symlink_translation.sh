#!/usr/bin/env bash

# Setup the symlinks for working on a translation

set -e
#set -x

if [ -z "$1" ]; then
	echo "usage: $0 <translation>"
	exit 1
fi

translation=$1

cd "$(dirname "${BASH_SOURCE[0]}")"/../docs/en

for file in $(find docs -type f); do
	if ! [ -e ../${translation}/${file} ]; then
		# Ugly hack, but ChangeLog is the only subdir we have...
		if echo $file | grep -q '/.*/'; then
			mkdir -p ../$(dirname ${translation}/${file})
			ln -s ../../../en/${file} ../${translation}/${file}
		else
			ln -s ../../en/${file} ../${translation}/${file}
		fi
	fi
done
