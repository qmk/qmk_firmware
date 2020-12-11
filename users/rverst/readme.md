# Overview

This is my userspace, main goal is to unify the experience between different 
keyboard models and operating systems. 

Most (all?) user handlers (`<handler>_user`) are received here and call a 
correspondend `<handler>_keymap` function to use in `keymap.c`.

