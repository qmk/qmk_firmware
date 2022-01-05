#!/usr/bin/env bash

# Remove the symlinks from a translation

set -e
#set -x

if [ -z "$1" ]; then
	echo "usage: $0 <translation>"
	exit 1
fi

translation=$1

if [ "$translation" = "-a" ]; then
	translation=""
fi

cd "$(dirname "${BASH_SOURCE[0]}")"/docs/$translation
find . -type l | xargs rm
