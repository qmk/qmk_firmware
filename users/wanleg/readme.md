# Contents  
  * [Git Basics](#git-basics)  
       * [Update a Feature Branch](#update-a-development-branch)  
       * [Delete Branch Locally and Remotely](#delete-branch-locally-and-remotely)
       * [Merge TEST branch into DEV branch](#merge-test-branch-into-dev-branch)
  * [STM32F103C8T6 Setup](#STM32F103C8T6-setup)
       * [Bootloader](#bootloader)
       * [Flashing QMK](#flashing-qmk)

---
## Git Basics  
### Update a Development Branch

This is how to update a working branch with upstream changes.
First we'll update your local master branch. Go to your local project and check out the branch you want to merge into (your local master branch)
```bash
$ git checkout master
```

Fetch the remote, bringing the branches and their commits from the remote repository.
You can use the -p, --prune option to delete any remote-tracking references that no longer exist in the remote. Commits to master will be stored in a local branch, remotes/origin/master
```bash
$ git fetch -p origin
```

Merge the changes from origin/master into your local master branch. This brings your master branch in sync with the remote repository, without losing your local changes. If your local branch didn't have any unique commits, Git will instead perform a "fast-forward".
```bash
$ git merge origin/master
```

Checkout the branch you want to merge into
```bash
$ git checkout <feature-branch>
```

Merge your (now updated) master branch into your feature branch to update it with the latest changes from your team.
```bash
$ git merge master
```

This will open your git-configured text editor. Edit the message as desired, save, and exit the editor.

The above steps only update your local feature branch. To update it on GitHub, push your changes.
```bash
$ git push origin <feature-branch>
```

### Delete Branch Locally and Remotely

Executive Summary
```bash
$ git push --delete <remote_name> <branch_name>
$ git branch -d <branch_name>
```
Note that in most cases the remote name is origin.

Delete Local Branch
To delete the local branch use one of the following:
```bash
$ git branch -d branch_name
$ git branch -D branch_name
```
Note: The -d option is an alias for --delete, which only deletes the branch if it has already been fully merged in its upstream branch. You could also use -D, which is an alias for --delete --force, which deletes the branch "irrespective of its merged status." [Source: man git-branch]

Delete Remote Branch [Updated on 8-Sep-2017]
As of Git v1.7.0, you can delete a remote branch using
```bash
$ git push <remote_name> --delete <branch_name>
```
which might be easier to remember than
```bash
$ git push <remote_name> :<branch_name>
```
which was added in Git v1.5.0 "to delete a remote branch or a tag."

Starting on Git v2.8.0 you can also use `git push` with the `-d` option as an alias for `--delete`.

Therefore, the version of Git you have installed will dictate whether you need to use the easier or harder syntax.

### Merge TEST branch into DEV branch

Executive Summary
```bash
$ git checkout DEV
$ git merge TEST
$ git push <remote_name> DEV
$ git branch -d TEST
$ git push <remote_name> :TEST
```
Note that in most cases the remote name is origin.  
The above code will merge, push to remote, and delete both the local and remote TEST branches

---  
## STM32F103C8T6 Setup
Cheap "Blue/Black Pills" typically do not come with a bootloader installed. The Black Pill uses [generic_boot20_pb12.bin](https://github.com/rogerclarkmelbourne/STM32duino-bootloader/blob/master/binaries/generic_boot20_pb12.bin). The Blue Pill uses [generic_boot20_pc13.bin](https://github.com/rogerclarkmelbourne/STM32duino-bootloader/blob/master/binaries/generic_boot20_pc13.bin).  
The following instructions have been adapted from [here](http://wiki.stm32duino.com/index.php?title=Burning_the_bootloader).
### Bootloader
Flashing a bootloader on to a Black Pill can be done via a USB to Serial converter (e.g. CP2102). This process should be roughly the same for all F103 boards.

1. Download the correct bootloader binary  
2. Set the 'boot 0' pin/jumper high, and 'boot 1' low  
  B0+ to center pin  
  B1- to center pin  
3. Connect the board to the PC using a USB to serial converter  
  RX to PA9  
  TX to PA10  
  GND to Ground  
  3.3V to 3.3 Volts  
4. Download and install __Flash Loader Demonstrator__ from [here](http://www.st.com/content/st_com/en/products/development-tools/software-development-tools/stm32-software-development-tools/stm32-programmers/flasher-stm32.html)  
5. Use __Flash Loader Demonstrator__ to flash the bootloader  
  Ensure the correct COM port is selected. Leave other options with their default values/selections.  
  Use the "Download to Device" option, with "Erase necessary pages" selected  
6. After a successful flash, set 'boot 0' pin/jumper low  
  B0- to center pin  
  B1- to center pin (no change)  

### Flashing QMK
As of April 2019, the `:dfu-util` target doesn't work on a \*Pill. You will need to use dfu-util directly.
1. Use QMK to build your `.bin`
2. Run `dfu-util.exe -d 1eaf:0003 -a 2 -D YOUR_FIRMWARE.bin"`  
  If this is the first QMK flash on the \*Pill, you will need to synchronize your Reset Button-push with starting the command. By default, the \*Pill only stays in bootloader mode for about 3 seconds before returning to normal operation.  

See [this page](https://docs.qmk.fm/#/faq_build?id=unknown-device-for-dfu-bootloader) if Windows can't see anything to upload to.  

---
