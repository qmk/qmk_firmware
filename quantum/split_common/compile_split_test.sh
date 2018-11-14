#
# split keyboards compile test
#
git status | grep "On branch"
BRANCH=`git status | awk '/^On branch/ { print $3 }'`
LOG=/tmp/split-compile-$BRANCH.txt
echo $LOG
git status | grep "On branch" > $LOG
date >> $LOG

split_kbd_list_old="6lit:all
divergetm2:all
ergotravel:all
foobar:all
handwired/dactyl_manuform/4x5:all
handwired/dactyl_manuform/4x6:all
handwired/dactyl_manuform/5x6:all
handwired/dactyl_manuform/5x7:all
handwired/dactyl_manuform/6x6:all
handwired/qc60:all
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
lets_split_eh:bbaserdem
lets_split_eh:default
lets_split_eh:romus
lets_split_eh:that_canadian
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
qwertyydox:default
redox:all
rorschach:all"

split_kbd_list="diverge3:all
40percentclub/25:all
40percentclub/6lit:all
40percentclub/foobar:all
"

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


