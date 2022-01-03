#!/usr/bin/env bash

# This script is used to build the complete site with translations. You do not need to use this normally.

set -e
#set -x

if [ -z "$1" ]; then
	echo "usage: $0 <branch>"
	exit 1
fi

# Prepare the site dir
rm -rf site/??/

# Set the site URL
pushd "$(dirname "${BASH_SOURCE[0]}")"/docs
sed -i 's,/devel/,/'$1'/,' */mkdocs.yml

# Setup the language switcher
cp versions.json ../site/

# Build the translations
for translation in ??/; do
	echo '*** Setting up symlinks for language' $translation
	../symlink_translation.sh $translation

	echo '*** Building site for language' $translation
	pushd $translation
	mkdocs build
	popd

	echo "*** Moving $translation/site to site/$translation"
	mv $translation/site ../site/$translation
done
popd
