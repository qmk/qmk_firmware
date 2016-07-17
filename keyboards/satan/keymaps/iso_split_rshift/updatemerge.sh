#!/bin/bash
git checkout iso_split_rshift # gets you "on branch dmgr2"
git fetch origin              # gets you up to date with origin
git merge origin/master
