#!/usr/bin/env bash

source util/travis_utils.sh
source util/travis_push.sh

set -o errexit -o nounset

rev=$(git rev-parse --short HEAD)
echo "Using git hash ${rev}"

if [[ "$TRAVIS_BRANCH" == "master" && "$TRAVIS_PULL_REQUEST" == "false" ]] ; then

git checkout master

git diff --name-only -n 1 ${TRAVIS_COMMIT_RANGE}

if [[ "$TRAVIS_COMMIT_MESSAGE" != *"[skip build]"* ]] ; then
	make generate-keyboards-file SILENT=true > .keyboards
	cd ..
	git clone git@github.com:qmk/qmk.fm.git
	cd qmk.fm
	mv ../qmk_firmware/id_rsa_qmk.fm id_rsa_qmk.fm
	mv ../qmk_firmware/.keyboards .
	ssh-add -D
	eval `ssh-agent -s`
	ssh-add id_rsa_qmk.fm

	# don't delete files in case not all keyboards are built
	# rm -f compiled/*.hex

	# ignore errors here
	# In theory, this is more flexible, and will allow for additional expansion of additional types of files and other names
	mv ../qmk_firmware/*_default.*{hex,bin} ./compiled/ || true

	# get the list of keyboards
	readarray -t keyboards < .keyboards

	# replace / with _
	keyboards=("${keyboards[@]//[\/]/_}")

	# remove all binaries that don't belong to a keyboard in .keyboards
	for file in "./compiled"/* ; do
		match=0
		for keyboard in "${keyboards[@]}" ; do
			if [[ ${file##*/} = "${keyboard}_default.bin" ]] || [[ ${file##*/} = "${keyboard}_default.hex" ]]; then
				match=1
				break
			fi
		done
		if [[ $match = 0 ]]; then
			echo "Removing deprecated binary: $file"
			rm "$file"
		fi
	done

	bash _util/generate_keyboard_page.sh
	git add -A
	git commit -m "generated from qmk/qmk_firmware@${rev}"
	git push git@github.com:qmk/qmk.fm.git

fi

fi
