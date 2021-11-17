# Cross-compile on Linux, for Windows

1) ```docker build -t winbuilder .```
2) ```docker run -it --rm -v `pwd`/../../:/xwhatsit -w /xwhatsit/util/util winbuilder /bin/bash```
   a) ```i686-w64-mingw32.static-qmake-qt5 util.pro```
   b) ```make```

```util.exe``` is put in keyboards/xwhatsite/util/util/release folder, you may need to move it to 
keyboards/xwhatsite/util/util for it to find the layout files.

Note:

* I tested the resulting statically compiled .exe on windows7 and windows10 successfully.
* It fails on windows XP.
* It also fails when trying to run with wine on my machine with Xorg, but it opens up a window when running the same .exe on vncserver. This may be
caused by a combination of: ATI graphics, wine, and the version of Qt that is statically compiled into the .exe. Anyway, not a serious issue,
since running this application on wine is useless, the only treason this NOTE is here to avoid future head-scratching.
