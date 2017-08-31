# How to use Github with QMK

Github can be a little tricky to those that aren't familiar with it - this guide will walk through each step of forking, cloning, and submitting a pull request with QMK.

{% hint style='info' %}
This guide assumes you're somewhat comfortable with running things at the command line, and have git installed on your system.
{% endhint %}

Start on the [QMK Github page](https://github.com/qmk/qmk_firmware), and you'll see a button in the upper right that says "Fork":

![Fork on Github](http://i.imgur.com/8Toomz4.jpg)

If you're apart of an organization, you'll need to choose which account to fork it to. In most circumstances, you'll want to fork it to your personal account. Once your fork is completed (sometimes this takes a little while), click the "Clone or Download" button:

![Download from Github](http://i.imgur.com/N1NYcSz.jpg)

And be sure to select "HTTPS", and select the link and copy it:

![HTTPS link](http://i.imgur.com/eGO0ohO.jpg)

From here, enter `git clone ` into the command line, and then paste your link:

```
**[terminal]
**[prompt you@computer]**[path ~]**[delimiter  $ ]**[command git clone https://github.com/whoeveryouare/qmk_firmware.git]
Cloning into 'qmk_firmware'...
remote: Counting objects: 46625, done.
remote: Compressing objects: 100% (2/2), done.
remote: Total 46625 (delta 0), reused 0 (delta 0), pack-reused 46623
Receiving objects: 100% (46625/46625), 84.47 MiB | 3.14 MiB/s, done.
Resolving deltas: 100% (29362/29362), done.
Checking out files: 100% (2799/2799), done.
```

You now have your QMK fork on your local machine, and you can add your keymap, compile it and flash it to your board. Once you're happy with your changes, you can add, commit, and push them to your fork like this:

```
**[terminal]
**[prompt you@computer]**[path ~/qmk_firmware]**[delimiter  $ ]**[command git add .]
**[prompt you@computer]**[path ~/qmk_firmware]**[delimiter  $ ]**[command git commit -m "adding my keymap"]
[master cccb1608] adding my keymap
 1 file changed, 1 insertion(+)
 create mode 100644 keyboards/planck/keymaps/mine/keymap.c
**[prompt you@computer]**[path ~/qmk_firmware]**[delimiter  $ ]**[command git push]
Counting objects: 1, done.
Delta compression using up to 4 threads.
Compressing objects: 100% (1/1), done.
Writing objects: 100% (1/1), 1.64 KiB | 0 bytes/s, done.
Total 1 (delta 1), reused 0 (delta 0)
remote: Resolving deltas: 100% (1/1), completed with 1 local objects.
To https://github.com/whoeveryouare/qmk_firmware.git
 + 20043e64...7da94ac5 master -> master
```

Your changes now exist on your fork on Github - if you go back there (https://github.com/<whoeveryouare>/qmk_firmware), you can create a "New Pull Request" by clicking this button:

![New Pull Request](http://i.imgur.com/DxMHpJ8.jpg)

Here you'll be able to see exactly what you've committed - if it all looks good, you can finalize it by clicking "Create Pull Request":

![Create Pull Request](http://i.imgur.com/Ojydlaj.jpg)

After submitting, we may talk to you about your changes, ask that you make changes, and eventually accept it! Thanks for contributing to QMK :)