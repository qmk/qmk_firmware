function compile() {
  make $1 $2 helix/rev2/oled/back:five_rows:clean
  echo "================"
  echo $1 $2 $3
  make $1 $2 helix/rev2/oled/back:five_rows$3
  echo $1 $2 $3
}
flash=$1

# compile LTO_ENABLE=yes NO_LTO_SRC_TEST=lto $1    # compile ok, don't work
# compile LTO_ENABLE=yes NO_LTO_SRC_TEST=no-lto $1 # compile ok, work
# compile LTO_ENABLE=no NO_LTO_SRC_TEST=lto $1     # compile ok, work
# compile LTO_ENABLE=no NO_LTO_SRC_TEST=no-lto $1  # compile ok, work
# compile LTO_ENABLE=yes NO_LTO_LIB_TEST=lto $1    # compile ok, don't work
# compile LTO_ENABLE=yes NO_LTO_LIB_TEST=no-lto $1 # compile ok, work
# compile LTO_ENABLE=no NO_LTO_LIB_TEST=lto $1     # compile ok, work
# compile LTO_ENABLE=no NO_LTO_LIB_TEST=no-lto $1  # compile ok, work
