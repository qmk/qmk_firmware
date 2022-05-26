#!/bin/bash

parse_args() {
    # Default values
    do_init_qmk=false
    do_compile=true
    do_flash_cli=false

    SHORT=i,c,C,f,F,p:,b:,h
    LONG=init,compile,no-compile,flash-cli,no-flash-cli,pcb:,bootloader:,help
    OPTS=$(getopt -a -n flash.sh --options $SHORT --longoptions $LONG -- "$@")

    eval set -- "$OPTS"

    while :; do
        case "$1" in
        -p | --pcb)
            pcb="$2"
            shift 2
            ;;
        -b | --bootloadre)
            bootloader="$2"
            shift 2
            ;;
        -i | --init)
            do_init_qmk=true
            shift 1
            ;;
        -c | --compile)
            do_compile=true
            shift 1
            ;;
        -C | --no-compile)
            do_compile=false
            shift 1
            ;;
        -f | --flash-cli)
            do_flash_cli=true
            shift 1
            ;;
        -F | --no-flash-cli)
            do_flash_cli=false
            shift 1
            ;;
        -h | --help)
            help
            ;;
        --)
            shift
            break
            ;;
        *)
            echo "Unexpected option: $1"
            help
            ;;
        esac
    done
}

help() {
    echo -e "${col_yellow}USAGE:$col_reset"
    echo -e "\tflash.sh [OPTIONS]"
    echo
    echo -e "${col_yellow}OPTINOS:$col_reset"
    out="$(col_opt i init "Initialize qmk config")"
    out="$out\n$(col_opt p pcb "Set pcb version")"
    out="$out\n$(col_opt b bootloader "Set bootloader type")"
    out="$out\n$(col_opt c compile "Compile the keymap")"
    out="$out\n$(col_opt C no-compile "Do not compile the keymap")"
    out="$out\n$(col_opt f flash-cli "Flash using the terminal")"
    out="$out\n$(col_opt F no-flash-cli "Flash using qmk toolbox")"
    out="$out\n$(col_opt h help "Print this help message")"
    echo -e "$out" | column -t -s $'\t' -o $'\t'
    exit 2
}

col_opt() {
    echo -e "\t$col_green-$1$col_reset, $col_green--$2$col_reset\t$3"
}
