# How to Use GitHub with QMK

GitHub can be a little tricky to those that aren't familiar with it - this guide will walk through each step of forking, cloning, and submitting a pull request with QMK.

?> This guide assumes you're somewhat comfortable with running things at the command line, and have git installed on your system.

Start on the [QMK GitHub page](https://github.com/qmk/qmk_firmware), and you'll see a button in the upper right that says "Fork":

![Fork on GitHub](https://i.imgur.com/8Toomz4.jpg)

If you're a part of an organization, you'll need to choose which account to fork it to. In most circumstances, you'll want to fork it to your personal account. Once your fork is completed (sometimes this takes a little while), click the "Clone or Download" button:

![Download from GitHub](https://i.imgur.com/N1NYcSz.jpg)

And be sure to select "HTTPS", and select the link and copy it:

![HTTPS link](https://i.imgur.com/eGO0ohO.jpg)

From here, enter `git clone --recurse-submodules ` into the command line, and then paste your link:

```
user@computer:~$ git clone --recurse-submodules https://github.com/whoeveryouare/qmk_firmware.git
Cloning into 'qmk_firmware'...
remote: Enumerating objects: 9, done.
remote: Counting objects: 100% (9/9), done.
remote: Compressing objects: 100% (5/5), done.
remote: Total 183883 (delta 5), reused 4 (delta 4), pack-reused 183874
Receiving objects: 100% (183883/183883), 132.90 MiB | 9.57 MiB/s, done.
Resolving deltas: 100% (119972/119972), done.
...
Submodule path 'lib/chibios': checked out '587968d6cbc2b0e1c7147540872f2a67e59ca18b'
Submodule path 'lib/chibios-contrib': checked out 'ede48346eee4b8d6847c19bc01420bee76a5e486'
Submodule path 'lib/googletest': checked out 'ec44c6c1675c25b9827aacd08c02433cccde7780'
Submodule path 'lib/lufa': checked out 'ce10f7642b0459e409839b23cc91498945119b4d'
Submodule path 'lib/ugfx': checked out '3e97b74e03c93631cdd3ddb2ce43b963fdce19b2'
```

You now have your QMK fork on your local machine, and you can add your keymap, compile it and flash it to your board. Once you're happy with your changes, you can add, commit, and push them to your fork like this:

```
user@computer:~$ git add .
user@computer:~$ git commit -m "adding my keymap"
[master cccb1608] adding my keymap
 1 file changed, 1 insertion(+)
 create mode 100644 keyboards/planck/keymaps/mine/keymap.c
user@computer:~$ git push
Counting objects: 1, done.
Delta compression using up to 4 threads.
Compressing objects: 100% (1/1), done.
Writing objects: 100% (1/1), 1.64 KiB | 0 bytes/s, done.
Total 1 (delta 1), reused 0 (delta 0)
remote: Resolving deltas: 100% (1/1), completed with 1 local objects.
To https://github.com/whoeveryouare/qmk_firmware.git
 + 20043e64...7da94ac5 master -> master
```

Your changes now exist on your fork on GitHub - if you go back there (`https://github.com/<whoeveryouare>/qmk_firmware`), you can create a "New Pull Request" by clicking this button:

![New Pull Request](https://i.imgur.com/DxMHpJ8.jpg)

Here you'll be able to see exactly what you've committed - if it all looks good, you can finalize it by clicking "Create Pull Request":

![Create Pull Request](https://i.imgur.com/Ojydlaj.jpg)

After submitting, we may talk to you about your changes, ask that you make changes, and eventually accept it! Thanks for contributing to QMK :)
