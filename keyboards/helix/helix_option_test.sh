export SKIP_VERSION=yes
export SKIP_DEBUG_INFO=yes
git status | grep "On branch"
BRANCH=`git status | awk '/^On branch/ { print $3 }' | sed "s'/'_'" `
LOG=/tmp/helix-option-test-$BRANCH.txt
echo $LOG
git status | grep "On branch" > $LOG
date >> $LOG

helix_keymap_list2a="
helix/rev2:default
helix/rev2:five_rows
helix/rev2:five_rows_jis
helix/rev2:yshrsmz
helix/rev2:edvorakjp
"

helix_keymap_list3="
helix/pico:default
helix/pico:mtei
helix/pico:biacco
"

result_files=

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
   result_file=`find . -depth 2 -newer /tmp/cstamp -name \*.hex`
   result_file=`basename $result_file`
   result_files="$result_files $result_file"
   echo $result_file | xargs md5 >> $LOG
   rm /tmp/cstamp
   echo >> $LOG
   make $opt $src:clean
}

function comptest() {
    rev=$1
    keymap=$2
    option1=$3
    option2=$4
    result_files=
    compiletest helix/$rev:$keymap HELIX=$option1
    compiletest helix/$rev$option2:$keymap
    echo Result compare >> $LOG
    md5 $result_files >> $LOG
    echo cmp $result_files >> $LOG
    cmp $result_files >> $LOG
    diff $result_files | head
    diff $result_files | head >> $LOG
    echo >> $LOG
}

# this will be error
echo Force error >> $LOG
comptest pico default "" /under

for i in default mtei biacco
do
    comptest pico $i "" ""
    comptest pico $i back /back
    comptest pico $i under /under
    comptest pico $i oled /oled
    date >> $LOG
done

for i in default five_rows five_rows_jis yshrsmz edvorakjp
do
    comptest rev2 $i "" ""
    comptest rev2 $i back /back
    comptest rev2 $i under /under
    comptest rev2 $i oled /oled
    comptest rev2 $i oled,back /oled/back
    comptest rev2 $i oled,under /oled/under
    date >> $LOG
done

# this will be error
echo Force error >> $LOG
comptest rev2 default back /under
