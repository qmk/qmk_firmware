# Ishtob's userspace

under developement

# Secret Macros

This section is a modified version of what @drashna did in his userspace: https://github.com/qmk/qmk_firmware/tree/master/users/drashna#secret-macros

`macros_private.c` will be used if it exsists in the userspace folder during compiling.

To get started, put the following in rules.mk. this will have the compiler include the macros_private.c file if it exsists.
```
SRC += ishtob.c
ifneq ($(wildcard $(USER_PATH)/macros_private.c),"")
  SRC += macros_private.c
endif
ifeq ($(strip $(NO_SECRETS)), yes)
    OPT_DEFS += -DNO_SECRETS
endif
```

Remember that all macro keycode has to be present in the header file (ishtob.h) to prevent error during compile.

Next, you setup macros_private.c, ensure the keycodes are defined in ishtob.h (or your keymap.h).
Here is an example of my macros with the sensitive login information removed:
```
#include "ishtob.h" //replace this with your userspace or keymap
#include "quantum.h"

#pragma message "secret macros included" //debug line to let me know this file is included in the compile

//this str is for the monthly password rotation per my workplace's security policy
char my_str[5] = "stuff";

bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
      //my login macros
      case P_CITRIX:
          SEND_STRING("username"SS_TAP(X_TAB)"something");
          send_string(my_str);
          return false;
      case P_MPASS:
          SEND_STRING("something");
          send_string(my_str);
          return false;
      case P_META:
          SEND_STRING("metausername");
          return false;
      //my work macros for the meta application
      case O_RTQ6H:
          SEND_STRING(SS_TAP(X_TAB)"0300"SS_TAP(X_TAB)SS_TAP(X_DOWN)SS_TAP(X_TAB)"0900"SS_TAP(X_TAB)SS_TAP(X_DOWN)SS_TAP(X_TAB)"1500"SS_TAP(X_TAB)SS_TAP(X_DOWN)SS_TAP(X_TAB)"2100"SS_TAP(X_TAB)SS_LALT("o"));
          return false;
      case O_AUTODC:
          SEND_STRING(SS_LALT("v")SS_TAP(X_TAB)SS_TAP(X_TAB)SS_TAP(X_TAB)SS_TAP(X_TAB)SS_TAP(X_TAB)SS_TAP(X_TAB)SS_TAP(X_TAB)SS_TAP(X_TAB)SS_TAP(X_TAB)"T"SS_TAP(X_TAB)"N"SS_LALT("s"));
          return false;
      case O_DAYRN:
          SEND_STRING(SS_TAP(X_TAB)SS_TAP(X_TAB)SS_TAP(X_TAB)SS_TAP(X_TAB)SS_TAP(X_TAB)"1"SS_LALT("s"));
          return false;
      //Ops macros
      case M_EMAIL:
          SEND_STRING("privatemail@email.com");
          return false;       
      case M_EMAIL2:
          SEND_STRING("workemail@work.com");
          return false;
     }
   }
  return true;
} 
```


Finally, add the following to .git/info/exclude to prevent private macros from being committed to git.
```
# git ls-files --others --exclude-from=.git/info/exclude
# Lines that start with '#' are comments.
# For a project mostly in C, the following would be a good set of
# exclude patterns (uncomment them if you want to use them):
# *.[oa]
# *~
/users/ishtob/macros_private.c
```

# Special mentions

special thanks to @drashna for helping me through quite a bit of these codes.