#!/usr/bin/env bash
# Attempt to build every possible keyboard + keymap

# Homebrew on OSX:
# brew tap PX4/homebrew-px4
# brew tap osx-cross/avr
# brew update
# brew install avr-libc gcc-arm-none-eabi-49

# list of failures
declare -a FAILED

declare -a BROKEN
BROKEN+=(
  "keyboard/mbed_onekey"
  "keyboard/planck:david"
)
NBROKEN=${#BROKEN[@]}

known_broken() {
  configuration="$1"
  for (( i=0; i < $NBROKEN; i++ )) ; do
    if [ "$configuration" = ${BROKEN[$i]} ]; then
      return 0
    fi
  done
  return 1
}

compile() {
  make="$1"
  label="$2"

  $make clean
  echo $make
  if ! $make ; then
    if ! known_broken $label ; then
      FAILED+=("$make")
    fi
  fi
}

keymap_param() {
  keymap="$1"
  if [ -d $keymap ] ; then
    basename $keymap
    return 0
  fi

  # Translate keymap_foo.c -> foo
  basename $keymap | sed -e 's/keymap_//;' | sed -e 's/\.c$//;'
  return 0
}

for kbd in keyboard/* ; do
  for makefile in Makefile Makefile.lufa ; do
    if [ -f $kbd/$makefile ] ; then
      compile "make -C $kbd -f $makefile" $kbd
      if [ -d $kbd/keymaps ] ; then
        for keymap in $kbd/keymaps/* ; do
          KEYMAP=$(keymap_param $keymap)
          compile "make -C $kbd -f $makefile KEYMAP=$KEYMAP" "$kbd:$KEYMAP"
        done
      fi
    fi
  done
done

FAIL_COUNT=${#FAILED[@]}
if (( $FAIL_COUNT > 0 )) ; then
  echo "$FAIL_COUNT failures:"
  for (( i=0; i < $FAIL_COUNT ; i++)); do
    echo "  ${FAILED[$i]}"
  done
  exit 1
fi

echo "You didn't break anything!"
exit 0
