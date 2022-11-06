# ChibiOS Upgrade Procedure

ChibiOS and ChibiOS-Contrib need to be updated in tandem -- the latter has a branch tied to the ChibiOS version in use and should not be mixed with different versions.

## Getting ChibiOS

* `svn` Initialisation:
    * Only needed to be done once
    * You might need to separately install `git-svn` package in your OS's package manager
    * `git svn init --stdlayout --prefix='svn/' http://svn.osdn.net/svnroot/chibios/`
    * `git remote add qmk git@github.com:qmk/ChibiOS.git`
* Updating:
    * `git svn fetch`
    * First time around this will take several hours
    * Subsequent updates will be incremental only
* Tagging example (work out which version first!):
    * `git tag -a ver20.3.4 -m ver20.3.4 svn/tags/ver20.3.4`
    * `git push qmk ver20.3.4`
    * `git tag -a develop_YYYY_qN -m develop_YYYY_qN svn/tags/ver20.3.4`
    * `git push qmk develop_YYYY_qN`

## Getting ChibiOS-Contrib

* `git` Initialisation:
    * `git clone git@github.com:qmk/ChibiOS-Contrib`
    * `git remote add upstream https://github.com/ChibiOS/ChibiOS-Contrib`
    * `git checkout -b chibios-20.3.x upstream/chibios-20.3.x`
* Updating:
    * `git fetch --all --tags --prune`
    * `git checkout chibios-20.3.x`
    * `git pull --ff-only`
    * `git push origin chibios-20.3.x`
    * `git tag -a develop_YYYY_qN -m develop_YYYY_qN chibios-20.3.x`
    * `git push origin develop_YYYY_qN`

## Updating submodules

* Update the submodules
    * `cd $QMK_FIRMWARE`
    * `git checkout develop`
    * `git pull --ff-only`
    * `git checkout -b chibios-version-bump`
    * `cd lib/chibios`
    * `git fetch --all --tags --prune`
    * `git checkout develop_YYYY_qN`
    * `cd ../chibios-contrib`
    * `git fetch --all --tags --prune`
    * `git checkout develop_YYYY_qN`
* Update ChibiOS configs within QMK
    * `cd $QMK_FIRMWARE`
    * `./util/chibios_conf_updater.sh`
* Build everything
    * `cd $QMK_FIRMWARE`
    * `qmk mass-compile -j 4`
    * Make sure there are no errors
* Push to the repo
    * `git commit -am 'Update ChibiOS to 99.9.9'`
    * `git push --set-upstream origin chibios-version-bump`
* Make a PR to qmk_firmware with the new branch
