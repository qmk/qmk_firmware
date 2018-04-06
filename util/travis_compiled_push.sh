#!/bin/bash

TRAVIS_BRANCH="${TRAVIS_BRANCH:master}"
TRAVIS_PULL_REQUEST="${TRAVIS_PULL_REQUEST:false}"
TRAVIS_COMMIT_MESSAGE="${TRAVIS_COMMIT_MESSAGE:-none}"
TRAVIS_COMMIT_RANGE="${TRAVIS_COMMIT_RANGE:-HEAD~1..HEAD}"

set -o errexit -o nounset

rev=$(git rev-parse --short HEAD)

if [[ "$TRAVIS_BRANCH" == "master" && "$TRAVIS_PULL_REQUEST" == "false" ]] ; then

git config --global user.name "QMK Bot"
git config --global user.email "hello@qmk.fm"

openssl aes-256-cbc -K $encrypted_b0ee987fd0fc_key -iv $encrypted_b0ee987fd0fc_iv -in secrets.tar.enc -out secrets.tar -d
tar xvf secrets.tar

chmod 600 id_rsa_qmk_firmware
chmod 600 id_rsa_qmk.fm
eval `ssh-agent -s`
ssh-add id_rsa_qmk_firmware

# convert to unix line-endings
git checkout master
git diff --diff-filter=M --name-only -n 1 -z ${TRAVIS_COMMIT_RANGE} | xargs -0 dos2unix
git diff --diff-filter=M --name-only -n 1 -z ${TRAVIS_COMMIT_RANGE} | xargs -0 git add
git commit -m "convert to unix line-endings [skip ci]" && git push git@github.com:qmk/qmk_firmware.git master

increment_version ()
{
  declare -a part=( ${1//\./ } )
  part[2]=$((part[2] + 1))
  new="${part[*]}"
  echo -e "${new// /.}"
} 

git diff --name-only -n 1 ${TRAVIS_COMMIT_RANGE}

NEFM=$(git diff --name-only -n 1 ${TRAVIS_COMMIT_RANGE} | grep -Ev '^(keyboards/)' | grep -Ev '^(docs/)' | grep -Ev '^(users/)' | grep -Ev '^(layouts/)' | wc -l)
if [[ $NEFM -gt 0 ]] ; then
	echo "Essential files modified."
	git fetch --tags
	#lasttag=$(git describe --tags $(git rev-list --tags --max-count=10) | grep -Ev '\-' | xargs -I@ git log --format=format:"%ai @%n" -1 @ | sort -V | awk '{print $4}' | tail -1)
	lasttag=$(git describe --tags $(git rev-list --tags --max-count=10) | grep -Ev '\-' | sort -V | tail -1)
	newtag=$(increment_version $lasttag)
	until git tag $newtag; do
		newtag=$(increment_version $newtag)
	done
	git push --tags git@github.com:qmk/qmk_firmware.git
else
	echo "No essential files modified."
fi

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
	for file in ../qmk_firmware/keyboards/*/keymaps/*/*_default.hex; do mv -v "$file" "compiled/${file##*/}" || true; done
	for file in ../qmk_firmware/keyboards/*/*/keymaps/*/*_default.hex; do mv -v "$file" "compiled/${file##*/}" || true; done
	for file in ../qmk_firmware/keyboards/*/*/*/keymaps/*/*_default.hex; do mv -v "$file" "compiled/${file##*/}" || true; done
	for file in ../qmk_firmware/keyboards/*/*/*/*/keymaps/*/*_default.hex; do mv -v "$file" "compiled/${file##*/}" || true; done
	bash _util/generate_keyboard_page.sh
	git add -A
	git commit -m "generated from qmk/qmk_firmware@${rev}" 
	git push git@github.com:qmk/qmk.fm.git

fi

fi
