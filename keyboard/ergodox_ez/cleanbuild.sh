make clean

if [ -n "$AVR_BIN" ]; then
    _PATH="$AVR_BIN:$PATH";
else
    _PATH=$PATH;
fi
PATH=$_PATH make KEYMAP=bheklilr
