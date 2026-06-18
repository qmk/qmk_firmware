#!/bin/bash -ex

# install_name_tool -change '/usr/local/opt/isl/lib/libisl.21.dylib' /usr/local/opt/isl/lib/libisl.dylib /usr/local/Cellar/avr-gcc@8/8.3.0/libexec/gcc/avr/8.3.0/cc1
# git submodule foreach git reset --hard
# make git-submodule
make keebio/iris/rev2:urecho \
 && sudo make keebio/iris/rev2:urecho:flash

