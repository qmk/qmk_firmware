Workman for Atreus
==================

This is the Workman layout for Atreus. You can get PDF and SVG files
for the keymap from the author's
[website](https://alexschroeder.ch/pdfs/workman/).

```
  q      d      r      w      b        ||       j      f      u      p      ;
  a      s      h      t      g        ||       y      n      e      o      i
  z      x      m      c      v        ||       k      l      ,      .      /
 esc    tab   super  shift  bksp  ctrl || alt  space   RS     LW     '     ret


Raised layer (RS)

  !       @     {      }      |        ||       -      7      8      9      *
  #       $     (      )      `        ||       .      4      5      6      +
  %       ^     [      ]      ~        ||       &      1      2      3      \
 menu    caps   <      >     del       ||       _                    0      =


Lower layer (LW)

 insert  home   up    end    pgup      ||      vol+    F7     F8     F9    F10
  del    left  down  right   pgdn      ||      vol-    F4     F5     F6    F11
                                       ||      mute    F1     F2     F3    F12
                                       ||        –                    ¨    reset
```

A note on the EN DASH and DIARESIS mappings on the lower layer: these
only work if you set up CAPS as your *Multi Key* because they
effectively send `<CAPS> - - .` and `<CAPS> "`, respectively.
