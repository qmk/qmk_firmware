# 6yozo_crkbd_miryoku qmk_keymap

Design goals for the layout:
---

- Shold be touch type friendly.
- Use the well thought out Miryoku layout with minimal modifications to it.
- Should be able to use hungarian accents.
- The host keyboard layout should be set to Hungarian.
- Multiple OSs must be supported: Windows / Linux / Mac
- Use Colemak DH layout on Corne which is the default in Miryoku layout.
- There must be a 1 to 1 mapping for every button on the Hungarian ISO layout

Hungarian accents:
---

The hungarian accents in prevalence(The source is probably not accurate, but it is a good start)

áéóöőíúűü

Source:
[https://www.reddit.com/r/hungary/comments/st8nwe/az_egyes_bet%C5%B1k_gyakoris%C3%A1ga_a_magyar_wordle/]

There are 2x3 extra keys on the Corne, so on the base layout 6
hungarian accents can be defined, the remaining three accents will be
defined on NAV layer.

The placement of the characters is based on the effort grid for matrix
keyboards as described on
[https://colemakmods.github.io/mod-dh/model.html]

á left pinky home
é right pinky home
ó left pinky top
ö right pinky top
ő left pinky bottom
í right pinky bottom
ú nav layer right pinky home
ü nav layer right pinky top
ű nav layer right pinky bottom.

The RAlt on KC_DOT seems to disable keyoverride, so both RALTs is
moved to the upper row.

Implementation
---

The keys are moved around on the keymap so they will emit the desired
character on a host with a hungarian layout. For some symbols there is
no such key on the hungarian keyboard because modifiers must be used
to type them (For example: '[' is typed by AltGr-f). In this case
there is no key to move - more precisly whichever key is used both the
base character and its shifted pair must be overriden - in this
case I have decided to move F1..Fx keys (these are dummy Fn buttons).

Caps word
---

It is a QMK feature, implemented by adding a dedicated CAPS WORD
TOGGLE button. The ordinary Caps Lock is still kept.



TODO
---

- Try to restore RALT to its original position.

- On Fun layer make the shifted key versions the same as the unshifted
  buttons.

- Disable the effect of any modifier apart from shift on dummy Fn
  buttons at a minimum.

Keyboard layout
---

BASE:

```
                                                                  "
Ó     Q     W     F     P     B           J     É     U     Y     '     Ö
            RALT                                            RALT


Á     A     R     S     T     G           M     N     E     I     O     É
      SUPER ALT   CTR   SHIFT                   SHIFT CTR   ALT   SUP

                                          <     >     ?
Ő     Z     X     C     D     V           K     H     ,     .     /     Í
      BTN                                                         BTN


                  ESC   SPC   TAB         ENT   BSP   DEL
	          MED   NAV   MOUSE       SYM   NUM   FUN

```

NAV:

```

            RALT                          AGAIN PASTE COPY  CUT   UNDO  Ü



      SUPER ALT   CTR   SHIFT CAPS        CAPS  <-    \/    /\    ->    Ú
                              WORD


                                          INS   HOME  PgDwn PgUp  End   Í
      BTN


                                          ENT   BSP   DEL


```

NUM:

```
      {     &     *     (     }
      [     7     8     9     ]                             RALT


      :     $     %     ^     +
      ;     4     5     6     =                 SHIFT CTR   ALT   SUP


      ~     !     @     #     |
      `     1     2     3     \



                  >     )     _
	          .     0     -

```

SYM:

```

      {     &     *     (     }                             RALT



      :     $     %     ^     +                 SHIFT CTR   ALT   SUP



      ~     !     @     #     |



                  (     )     _


```

Setup qmk cli
---
qmk setup -H /home/gaspa/qmk_firmware_lottie 6yozo/qmk_firmware_lottie
git remote set-url origin git@github.com:6yozo/qmk_firmware_lottie.git
