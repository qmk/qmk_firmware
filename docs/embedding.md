# WARNING: Until issue [#173](https://github.com/tmk/tmk_keyboard/issues/173) goes through, the [core][1] repository will not be up-to-date with the latest changes and fixes, but can still be used.

If you want to use TMK for your own keyboard project, you've got three options for embedding the [core][1].  
The recommended option is [subtrees](#1-git-subtree).

After adding the embed you'll need to [modify the Makefile](#modifications-to-the-makefile) of your project to point to the core correctly.

## 1. git subtree

In order to set up the subtree in your project, first add the core repository as a remote:  
```
git remote add -f core https://github.com/tmk/tmk_core
```

Then add the core as a subtree (directory) in your local repository:  
```
git subtree add -P tmk_core core master --squash
```

And that's it!

When you want to update the subtree in your repository to match the master on [tmk_core][1], do this:  
```
git subtree pull -P tmk_core core master --squash
```

## 2. git submodule

In order to set up the submodule in your project, first add a new submodule:  
```
git submodule add https://github.com/tmk/tmk_core tmk_core
```

Then pull, sync and update the submodule:  
```
git pull
git submodule sync --recursive
git submodule update --init --recursive
```

And that's it!

When you want to update the subtree in your repository to match the master on [tmk_core][1], follow the same steps as above.

If you want to clone a repository from GitHub that has submodule(s) in it, pass <kbd>--recursive</kbd> when cloning, like so:  
`git clone --recursive https://github.com/<username>/<repository>`

## 3. Manually (without git)

*Note: This is not recommended in any way, but it's still possible.*

Download a zipped version of the [tmk_core][1] repository using this link:  
<https://github.com/tmk/tmk_core/archive/master.zip>

Extract the zip in your project's directory, then rename the folder to <kbd>tmk_core</kbd>.

## Modifications to the *Makefile*

The one thing you have to make sure to change in the *Makefile* (compared to [tmk_keyboard](https://github.com/tmk/tmk_keyboard) drivers' *[Makefile](https://github.com/tmk/tmk_keyboard/blob/master/keyboard/gh60/Makefile#L45)*) is the "TMK_DIR" variable, which needs to point to the embed directory:  
```Makefile
TMK_DIR = ./tmk_core
```

[1]: https://github.com/tmk/tmk_core