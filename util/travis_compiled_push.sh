#!/bin/bash

set -o errexit -o nounset

rev=$(git rev-parse --short HEAD)

git config --global user.name "Travis CI"
git config --global user.email "jack.humb+travis.ci@gmail.com"

openssl aes-256-cbc -K $encrypted_b0ee987fd0fc_key -iv $encrypted_b0ee987fd0fc_iv -in util/qmk_firmware.enc -out qmk_firmware -d
openssl aes-256-cbc -K $encrypted_b0ee987fd0fc_key -iv $encrypted_b0ee987fd0fc_iv -in util/qmk.fm.enc -out qmk.fm -d
chmod 600 qmk_firmware
chmod 600 qmk.fm
eval `ssh-agent -s`
ssh-add qmk_firmware
ssh-add qmk.fm

if [[ "$TRAVIS_BRANCH" == "master" && "$TRAVIS_PULL_REQUEST" == "false" ]] ; then

increment_version ()
{
  declare -a part=( ${1//\./ } )
  part[2]=$((part[2] + 1))
  new="${part[*]}"
  echo -e "${new// /.}"
} 

NEFM=$(git diff --name-only -n 1 ${TRAVIS_COMMIT_RANGE} | grep -Ev '^(keyboards/)' | grep -Ev '^(docs/)' | wc -l)
if [[ $NEFM -gt 0 ]] ; then
	echo "Essential files modified."
	git fetch --tags
	lasttag=$(git tag | grep -Ev '\-' | xargs -I@ git log --format=format:"%ai @%n" -1 @ | sort -V | awk '{print $4}' | tail -1)
	newtag=$(increment_version $lasttag)
	git tag $newtag
	git push --tags
else
	echo "No essential files modified."
fi

if [[ "$TRAVIS_COMMIT_MESSAGE" != *"[skip build]"* ]] ; then

	make ergodox-ez AUTOGEN=true

	cd ..
	git clone git@github.com:qmk/qmk.fm.git
	cd qmk.fm
	#git submodule update --init --recursive
	#rm -rf keyboard
	#rm -rf keyboards
	#yes | cp -rf ../qmk_firmware/keyboards .
	#mkdir keyboards/ergodox_ez/
	#cp ../qmk_firmware/util/ergodox_ez.html keyboards/ergodox_ez/index.html
	#cp ../qmk_firmware/readme.md qmk_readme.md
	#./generate.sh
	rm -f _compiled/*.hex
	for file in ../qmk_firmware/keyboards/*/keymaps/*/*.hex; do mv -v "$file" "_compiled/${file##*/}"; done

	git add -A
	git commit -m "generated from qmk/qmk_firmware@${rev}" 
	git push

fi

fi