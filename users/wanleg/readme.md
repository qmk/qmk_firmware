# Contents  
  * [Git Basics](#git-basics)  
       * [Update a Feature Branch](#update-a-development-branch)  
       * [Delete Branch Locally and Remotely](#delete-branch-locally-and-remotely)
       * [Merge TEST branch into DEV branch](#merge-test-branch-into-dev-branch)
  * [STM32F103C8T6 Preparation](#STM32F103C8T6-preparation)
       * [Flashing](#flashing)

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
## STM32F103C8T6 Preparation
Cheap "Blue/Black Pills" typically do not come with a bootloader. The Black Pill uses [generic_boot20_pb12.bin](https://github.com/rogerclarkmelbourne/STM32duino-bootloader/blob/master/binaries/generic_boot20_pb12.bin). The Blue Pill uses [generic_boot20_pc13.bin](https://github.com/rogerclarkmelbourne/STM32duino-bootloader/blob/master/binaries/generic_boot20_pc13.bin).  
The following instructions are adapted from [here](http://wiki.stm32duino.com/index.php?title=Burning_the_bootloader).
### Flashing 
Flashing the bootloader onto the Black Pill via USB to Serial converter using UART1
The Black Pill does not come with any USB bootloader. This process should be roughly the same for all F103 boards.

Download the correct bootloader binary, in this case generic_boot20_pb12.bin [2]
Set the 'boot 0' pin/jumper high, and 'boot 1' low
B0+ to center pin
B1- to center pin
Connect the board to the PC using a USB to serial converter
RX to PA9
TX to PA10
GND to G on the ST-Link connector
3.3V to V3 on the ST-Link connector
Ensure the USB to serial converter is in 3.3 V mode
Reset the board, the user LED should now be off
Download and install Flash Loader Demonstrator from here: [3]
Use Flash Loader Demonstrator to flash the bootloader
See screenshots below
Select the correct COM port, yours will be different from the screenshots
For normal use, set both boot pins low
B0- to center pin B1 stays the same
