#!/bin/sh
git describe --abbrev=0 --tags
rm -f quantum/qmk_version.h
echo "#define QMK_VERSION_BYTE_1 `(git describe --tags | cut -d. -f1)`" >> quantum/qmk_version.h
echo "#define QMK_VERSION_BYTE_2 `(git describe --tags | cut -d. -f2)`" >> quantum/qmk_version.h
echo "#define QMK_VERSION_BYTE_3 `(git describe --tags | cut -d. -f3 | cut -d- -f1)`" >> quantum/qmk_version.h
