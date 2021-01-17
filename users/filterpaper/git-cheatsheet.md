Copyright (C) 2021 @filterpaper

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

# Git cheatsheet
https://docs.qmk.fm/#/newbs_git_using_your_master_branch

## Setup QMK repository as upstream
One time setup of the original repository as a remote "upstream":
```
git remote add upstream https://github.com/qmk/qmk_firmware.git
```

## Sync upstream to own fork
```
git fetch upstream
git checkout master
git merge upstream/master
git push origin master
```

## Commit new changes
```
git commit -a -m ""
git push
```
