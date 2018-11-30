#
# split keyboards compile test
#
export SKIP_VERSION=yes
export SKIP_DEBUG_INFO=yes
git status | grep "On branch"
BRANCH=`git status | awk '/^On branch/ { print $3 }' | sed "s'/'_'" `
LOG=/tmp/split-compile-$BRANCH.txt
echo $LOG
git status | grep "On branch" > $LOG
date >> $LOG

split_kbd_list_all="
40percentclub/25:all
40percentclub/6lit:all
40percentclub/foobar:all
diverge3:all
divergetm2:all
ergotravel:all
handwired/dactyl_manuform/4x5:all
handwired/dactyl_manuform/4x6:all
handwired/dactyl_manuform/5x6:all
handwired/dactyl_manuform/5x7:all
handwired/dactyl_manuform/6x6:all
handwired/qc60:all
handwired/xealous:all
iris:bmoorey
iris:broswen
iris:davidrambo
iris:dbroqua
iris:default
iris:dvp-zjpxshade
iris:edvorakjp
iris:fabian
iris:fate
iris:gsigler
iris:hag
iris:hexwire
iris:impstyle
iris:jennetters
iris:khord
iris:krusli
iris:lewisridden
iris:mtdjr
iris:olligranlund_nordic
iris:rdhaene
iris:s1carii
iris:saviof
iris:swedish
iris:transmogrified
iris:vyolle_steno
iris:xyverz
iris:yanfali
lets_split_eh:bakingpy
lets_split_eh:bbaserdem
lets_split_eh:buswerks
lets_split_eh:colemak_mod_dh_wide
lets_split_eh:crs
lets_split_eh:default
lets_split_eh:default_ortho_4x12
lets_split_eh:doxish_dvorak
lets_split_eh:ergodoxish
lets_split_eh:grahampheath
lets_split_eh:mindsound
lets_split_eh:romus
lets_split_eh:symbolic
lets_split_eh:talljoe
lets_split_eh:that_canadian
lets_split_eh:wanleg
lets_split_eh:xyverz
levinson:atreus
levinson:bakingpy
levinson:bakingpy2u
levinson:buswerks
levinson:colemak_mod_dh_wide
levinson:crs
levinson:default
levinson:default_ortho_4x12
levinson:ergodoxish
levinson:grahampheath
levinson:jyh
levinson:jyh2
levinson:losinggeneration
levinson:mindsound
levinson:mmacdougall
levinson:symbolic
levinson:talljoe
levinson:treadwell
levinson:valgrahf
levinson:wanleg
levinson:xtonhasvim
levinson:xyverz
miniaxe:all
nyquist:333fred
nyquist:DivergeJM
nyquist:bramver
nyquist:danielhklein
nyquist:default
nyquist:default_ortho_5x12
nyquist:hexwire
nyquist:jojiichan
nyquist:kim-kim
nyquist:losinggeneration
nyquist:mtdjr
nyquist:pitty
quefrency:all
qwertyydox:all
redox:all
rorschach:all
"

split_kbd_list_test1="ergotravel:all"

## use $(QUANTUM_DIR)/matrix.c
# planck:default alps64:default
## CUSTOM_MATRIX=yes
# al1:default amj96:default

## use $(QUANTUM_DIR)/split_common/matrix.c
# ergotravel:default
## CUSTOM_MATRIX=yes
# miniaxe:default

matrix_custom_list="planck:default alps64:default al1:default amj96:default ergotravel:default miniaxe:default"

split_kbd_list="$split_kbd_list_all"

function compiletest() {
   src=$1
   make $src:clean
   touch /tmp/cstamp
   echo make $src
   make $src
   echo make $src >> $LOG
   ELF=`find . -depth 2 -newer /tmp/cstamp -name \*.elf`
   avr-size $ELF | awk '/[0-9]/ { s = $1 + $2; printf(" * File size - %d/28672 %d free : " , s, 28672 - s ) }'; echo make $opt $src
  ( avr-size $ELF | awk '/[0-9]/ { s = $1 + $2; printf(" * File size - %d/28672 %d free : " , s, 28672 - s ) }'; echo  make $opt $src ) >> $LOG
   avr-size $ELF >> $LOG
   find . -depth 2 -newer /tmp/cstamp -name \*.hex | xargs md5 >> $LOG
   rm /tmp/cstamp
   echo >> $LOG
   make $src:clean
}

for i in $split_kbd_list
do
    compiletest $i
done


