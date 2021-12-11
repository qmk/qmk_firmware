git remote add upstream https://github.com/qmk/qmk-firmware.git
git fetch upstream
git checkout master
git rebase upstream/master
git push -f origin master
qmk setup

