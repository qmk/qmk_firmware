#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../../MS_sculpt_mobile/config.h"

#define USE_BABLPASTE

// Expect to get errors if you comment a feature out and leave it in your keymap. 

#ifdef USE_BABLPASTE
//define BabblePaste maps
// Windows. 
#define MAC_MODE   0
#define MS_MODE 1
//aka gnome+KDE
//#define LINUX_MODE 2 
//#define EMACS_MODE 3
#define VI_MODE 3
// Readline and tmux
#define READMUX_MODE 2 
//#define WORDSTAR_MODE 5
#endif

// Uncomment if you need more free flash space

// This removes everything but cursor movement
//#define BABL_MOVEMENTONLY
// and this just removes browser shortcuts
//#define BABL_NOBROWSER

// place overrides here
#endif
