mcu_list="ATmega32U4 ATmega16U4 ATmega32U2 ATmega16U2 AT90USB1286 AT90USB646 ATmega32A ATmega328P"

function main {
  # you can get all AVR model list, but it's too many
  if [ -z "$mcu_list" ]; then
       mcu_list=`get_mcu_list`
  fi
  echotitle
  for amcu in $mcu_list
  do
      onedef $amcu
  done
}

function find_avr_io_h {
    echo "#include <avr/io.h>" \
	| avr-gcc -mmcu=atmega32u4 -x c -M -E -C -P - \
	| tr ' ' '\n' \
	| grep avr/io.h
}

function get_mcu_list {
    grep  'defined[ ]*(__AVR_' `find_avr_io_h` \
	| tr ' ' '\n' \
	| grep '(__AVR_AT' \
	| sed -e 's/(__AVR_//' -e 's/__)//'
}

function echotitle {
    echo "/*"
    echo " This is an automatically generated file using $0."
    echo " If you want to add more to this list,"
    echo "  * modify util/avr_gpio_address.sh first line"
    echo "  * Do \`sh util/avr_gpio_address.sh\`"
    echo "*/"
}

function echo_testcode {
    echo "#include <avr/io.h>"
}

function avr_gcc_run {
    avr-gcc -mmcu=$1 -x assembler-with-cpp -dM -E -C -P -
}

function onedef {
    mcu=$1
    echo "#ifdef __AVR_"$mcu"__"
    echo_testcode | avr_gcc_run $mcu \
	| grep ' PIN[ABCDEFGH] ' \
	| head -1 \
	| sed -e 's/_SFR_IO8//' -e 's/PIN[ABCDEFGH]/ADDRESS_BASE/' -e 's/)/ \& 0xf0)/'
    echo_testcode | avr_gcc_run $mcu \
	| grep ' PIN[ABCDEFGH] ' \
	| sed -e 's/PIN[ABCDEFGH]/&_ADDRESS/' -e 's/_SFR_MEM8//' -e 's/_SFR_IO8//' -e 's/)/ \& 0xf)/'
    echo "#endif"
}

main > quantum/avr_portaddress_defs.h
