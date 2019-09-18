export SKIP_VERSION=yes
export SKIP_DEBUG_INFO=yes
git status | grep "On branch"
BRANCH=`git status | awk '/^On branch/ { print $3 }' | sed "s'/'_'" `
LOG=/tmp/helix-compile-$BRANCH.txt
echo $LOG
git status | grep "On branch" > $LOG
date >> $LOG

helix_keymap_list1="
helix/rev1:default
helix/rev1:OLED_sample
"

helix_keymap_list2a="
helix/rev2:default
helix/rev2:five_rows
helix/rev2:five_rows_jis
helix/rev2:yshrsmz
helix/rev2:edvorakjp
"

helix_keymap_list2b="
helix/rev2:froggy
helix/rev2:led_test
helix/rev2:xulkal
"

helix_keymap_list3="
helix/pico:default
helix/pico:mtei
helix/pico:biacco
"

function compiletest() {
   src=$1
   opt=$2
   make $opt $src:clean
   touch /tmp/cstamp
   echo make $opt $src
   make $opt $src
   echo make $opt $src >> $LOG
   ELF=`find . -depth 2 -newer /tmp/cstamp -name \*.elf`
   avr-size $ELF | awk '/[0-9]/ { s = $1 + $2; printf(" * File size - %d/28672 %d free : " , s, 28672 - s ) }'; echo make $opt $src
  ( avr-size $ELF | awk '/[0-9]/ { s = $1 + $2; printf(" * File size - %d/28672 %d free : " , s, 28672 - s ) }'; echo  make $opt $src ) >> $LOG
   avr-size $ELF >> $LOG
   find . -depth 2 -newer /tmp/cstamp -name \*.hex | xargs md5 >> $LOG
   rm /tmp/cstamp
   echo >> $LOG
   make $opt $src:clean
}

for i in $helix_keymap_list2a
do
    compiletest $i
    compiletest $i HELIX=back
    compiletest $i HELIX=under
    compiletest $i HELIX=oled
    compiletest $i HELIX=back,oled
    compiletest $i HELIX=under,oled
done

for i in $helix_keymap_list3
do
    compiletest $i
    compiletest $i HELIX=back
    compiletest $i HELIX=under
    compiletest $i HELIX=oled
done

for i in $helix_keymap_list1 $helix_keymap_list2b
do
    compiletest $i
done
