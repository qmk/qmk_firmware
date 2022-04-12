## Babblepaste, a universal translator for keyboard shortcuts

The idea is to have one "paste" key do the right thing for any operating system.
Put the keyboard in Windows mode, and  "paste" means Ctrl-v.
Switch to Emacs and "Paste" means Ctrl-y.  Mac is GUI-v and so on.

Currently supported modes are Windows, OS X, Gnome/KDE, Emacs, VI , ChromeOS, and Readline, with 70+ common macro actions.

The babblepaste library looks for the current OS in the babble_mode global variable.
To switch modes, run the switch_babble_mode() function, or a pre defined BABL_DO_x macro.

**BE CAREFUL**
  * Not all actions are defined for all OSes. The default is to do nothing.
  * Not all actions are _TESTED_ on all OSes.
  * Keys can have very different meanings between windows in the same OS. If you switch apps without switching modes, bad things can happen.

###To use the library
#### Add #defines to your config.h.
```
    #define USE_BABBLEPASTE
    
    //// Uncomment the modes you want to enable
    #define BABL_WINDOWS
    #define BABL_READMUX
    #define BABL_VI
    #define BABL_MAC
    #define BABL_LINUX
    #define BABL_EMACS
    #define BABL_NANO
    #define BABL_CHROMEOS
    
    //// These enable subsets of babble macros. Disable options to save space
    #define BABL_MOVE // Uncomment to add basic cursor movement
    #define BABL_OSKEYS // This adds Cut, paste, window movement and common OS shortcuts
    #define BABL_BROWSER // Browser shortcuts
    
    //// What Browser shortcuts?
    #define BABL_BROWSER_CHROME // Chrome browser, Google apps
    //#define BABL_BROWSER_MS
    //#define BABL_BROWSER_SAFARI // Safari, Apple defaults.
    
    //// applications vary even more between OSes. We'll do our best.
    #define BABL_APP
    // To enable specific App options.
    #define BABL_APP_CELLS // spreadsheets and tables
    #define BABL_APP_EDITOR // Fancy editor commands
    #define BABL_APP_WINDOWSPLITTING // splitting frames & windows
    
    //// What App keybinding is assumed?
    //#define BABL_APP_GOOGLE // Google office
    #define BABL_APP_MSOFFICE // MS office
    //#define BABL_APP_APPLE // Apple office
    #define BABL_APP_SUBLIME
```

#### Enable Babblepaste in your Keymap

Add the following to your keymap in process_record_user, before the main switch statement.
```
#ifdef USE_BABBLEPASTE
    if (keycode > BABBLE_START && keycode < BABBLE_END_RANGE) {
        if (record->event.pressed) { 
            babblePaste(keycode, 1);
        } else {
            babblePaste(keycode, 0);
        }
    }
#endif
```

#### Add makefile rules

Update your rules.mk to include the modes you want.

    `SRC += babblePaste.c babl_windows.c babl_mac.c  babl_nano babl_vi.c babl_readmux.c  babl_chromeos.c babl_emacs.c babl_linux.c`


#### Custom Keycodes

If you are using custom keycodes, update the safe range in your user.h
```
  #if defined(BABBLE_END_RANGE)
        #define USER_START BABBLE_END_RANGE
  #else
      #if defined(KEYMAP_SAFE_RANGE)
          #define USER_START KEYMAP_SAFE_RANGE
      #else
          #define USER_START SAFE_RANGE
      #endif
  #endif
```

#### Add Babblepaste actions to your keymap.
See the full list in babblePaste.h, or the list below
```
  B_WIN // switch babblepaste to  windows mode.
  B_MAC // Mac Mode
  B_LNX // switch to linux
  B_VI // switch to Vi mode
  B_EMAX //  switch mode to emacs
  B_NANO //  switch mode to emacs
  B_READ // switch to readline /tmux mode
  B_CROM // switch to chromeos mode.
  
  // Swap meaning of modifier key in most ergonomic location based on babble
  // mode. Eg Thumb gets CTL on Win/Linux, pinky gets Windows key. Reverse for 
  // OS X.  See first line in babblepaste function.   
  #define B_1ME BABL_PRIMARY_OS_MOD 
  #define B_2ME BABL_SECONDARY_OS_MOD
  #define B_3ME BABL_TERTIARY_OS_MOD

// Macros
  #define B_L1C  BABL_GO_LEFT_1C
  #define B_R1C  BABL_GO_RIGHT_1C
  #define B_L1W  BABL_GO_LEFT_WORD
  #define B_R1W  BABL_GO_RIGHT_WORD
  #define B_GSOL  BABL_GO_START_LINE
  #define B_GEOL  BABL_GO_END_LINE
  #define B_GTOP  BABL_GO_START_DOC
  #define B_GEND  BABL_GO_END_DOC
  #define B_DOWN  BABL_GO_NEXT_LINE
  #define B_UP    BABL_GO_PREV_LINE
  #define B_PTOP  BABL_GO_PARA_START
  #define B_PEND  BABL_GO_PARA_END
  #define B_PGDN  BABL_PGDN
  #define B_PGUP  BABL_PGUP
  #define B_DEL    BABL_DEL_RIGHT_1C
  #define B_DLW    BABL_DEL_LEFT_WORD
  #define B_DRW    BABL_DEL_RIGHT_WORD
  #define B_DEOL  BABL_DEL_TO_LINE_END // delete from cursor to end of line
  #define B_DSOL  BABL_DEL_TO_LINE_START // delete from cursor to begining line
  #define B_MODE   BABL_MODE //type out name of current mode.

  #define B_UNDO    BABL_UNDO
  #define B_REDO    BABL_REDO
  #define B_CUT     BABL_CUT
  #define B_COPY    BABL_COPY
  #define B_PASTE    BABL_PASTE
  #define B_SELALL    BABL_SELECT_ALL
  #define B_SELA    BABL_SELECT_ALL
  #define B_FIND     BABL_FIND
  #define B_FINDN    BABL_FIND_NEXT
  #define B_FINDP    BABL_FIND_PREV
  #define B_RPLACE    BABL_FIND_REPLACE
  #define B_RUNAPP    BABL_RUNAPP
  #define B_NAPP  BABL_SWITCH_APP_NEXT
  #define B_PAPP  BABL_SWITCH_APP_LAST // previous
  #define B_CAPP  BABL_CLOSE_APP
  #define B_HELP  BABL_HELP
  #define B_HELP  BABL_HELP
  #define B_LOCK  BABL_LOCK
  #define B_SCAP  BABL_SCREENCAPTURE
  #define B_KEYB  BABL_SWITCH_KEYBOARD_LAYOUT

  #define B_NTAB  BABL_BROWSER_NEW_TAB
  #define B_CTAB  BABL_BROWSER_CLOSE_TAB
  #define B_ROTB  BABL_BROWSER_REOPEN_LAST_TAB
  #define B_NXTB  BABL_BROWSER_NEXT_TAB
  #define B_PTAB  BABL_BROWSER_PREV_TAB
  #define B_NURL  BABL_BROWSER_URL_BAR
  #define B_BFWD  BABL_BROWSER_FORWARD
  #define B_BBAK  BABL_BROWSER_BACK
  #define B_BFND  BABL_BROWSER_FIND
  #define B_BOOK  BABL_BROWSER_BOOKMARK
  #define B_BDEV  BABL_BROWSER_DEV_TOOLS // hard one to remember
  #define B_BRLD  BABL_BROWSER_RELOAD
  #define B_BFULL BABL_BROWSER_FULLSCREEN
  #define B_ZIN   BABL_BROWSER_ZOOM_IN
  #define B_ZOUT  BABL_BROWSER_ZOOM_OUT

  #define B_SAVE  BABL_APP_SAVE
  #define B_PASTV BABL_APP_PASTE_VALUES
  #define B_CALN  BABL_APP_CENTER_ALIGN
  #define B_CFMT  BABL_APP_CLEAR_FORMATTING
  #define B_SCLA  BABL_APP_SCROLL_ACTIVE_CELL
  #define B_NCEL  BABL_NEWLINE_IN_CELL
  #define B_IPRW  BABL_INSERT_ROW_ABOVE
  #define B_ICOL  BABL_INSERT_COL_LEFT
  #define B_IROW  BABL_INSERT_ROW
  #define B_DROW  BABL_DELETE_ROW
  #define B_SELC  BABL_SELECT_COL
  #define B_SELR  BABL_SELECT_ROW

  #define B_MSEL    BABL_APP_MULTI_SELECT
  #define B_MARK    BABL_APP_SET_MARK
  #define B_VSPLIT  BABL_SPLIT_FRAME_VERT
  #define B_VUNSPT  BABL_UNSPLIT_FRAME_VERT
  #define B_HSPLIT  BABL_SPLIT_FRAME_HORIZONTAL
  #define B_HUNSPT  BABL_UNSPLIT_FRAME_HORIZONTAL
  #define B_NXTFM   BABL_NEXT_FRAME
  #define B_PRVFM   BABL_PREV_FRAME
```

####Add babblepaste functions to your keyboard or userspace
Functions babble_led_user() and babble_led_kb() are called when babble mode is changed. 
```
void babble_modeswitch_kb(uint8_t mode){
  #ifdef USE_BABBLEPASTE
      writePinLow(B3);      writePinLow(B2);
      switch(mode) {
        case(BABL_LINUX_MODE):
          writePinHigh(B2);
          backlight_level(1);
          break;
        case(BABL_MAC_MODE):  
          writePinHigh(B3);
          backlight_level(4);
          break;
      }
      // call the user function
    babble_modeswitch_user(mode);
  #endif
```



## Development FAQs

**Todos**
eeprom store state of babble_mode? or update docs so that people can change the order of the enum in babblespace.h?

**You have huge ifdef stanzas instead of functions**
This fails gracefully if you don't have all options defined. Patch if you can think how to use fewer defines.

**Why not an array of arrays as a lookup instead of a function?**
This would allow you to store the lookup table in PROGMEM.
True, but that takes more pre-processor skill than I have, and may be less portable to ARM or other flash mappings.

**Have you tested every key on every platform?**
No. Be careful, submit a patch.

**Why not change apps App babble modes at the same global level as the OS?**
This is only a good thing if it doesn't confuse the user. If you can show state of OS vs App, it's probably a good thing.

**Can the OS tell the keyboard what mode to use?**
The keyboard side is easy to do with virtser_recv & a function that updates babble_mode. It still needs a PC side app to track where the keyboard focus is.
One could use a keyboard macro to launch an app & switch modes for that app.

## Thanks

Thanks to [wikipedia shortcuts page](https://en.wikipedia.org/wiki/Table_of_keyboard_shortcuts)
and [Jeebak's keymap](https://github.com/qmk/qmk_firmware/blob/master/keyboards/planck/keymaps/jeebak/keymap.c)
this [howtogeek shortcuts page](https://www.howtogeek.com/115664/42-text-editing-keyboard-shortcuts-that-work-almost-everywhere/)
And of course QMK...
