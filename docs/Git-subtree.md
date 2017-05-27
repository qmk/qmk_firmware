## Update core branch procedure
    git co master
    git subtree split -P tmk_core -b <tmp_branch>
    git co core
    git merge <tmp_branch>
    git co master
    git subtree merge -P tmk_core --squash
