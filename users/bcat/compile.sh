#!/bin/bash

set -o errexit -o nounset

usage () {
  printf "\
usage: ./users/bcat/compile.sh [-c] [-j N]

Compiles all keyboards for which bcat maintains keymaps.

optional arguments:
  -c                    performs a clean build
  -j N                  runs N make tasks in parallel
  -v                    shows verbose output
"
}

compile () {
    local keyboard=$1 layout=${2:-}
    FORCE_LAYOUT="$layout" SILENT="$opt_silent" make -j "$opt_parallel" "$keyboard":bcat
}

opt_parallel=1
opt_silent=true

while getopts :chj:v opt; do
  case $opt in
    c) opt_clean=1 ;;
    j) opt_parallel=$OPTARG ;;
    v) opt_silent=false ;;
    h) usage; exit 0 ;;
    \?) usage >&2; exit 2 ;;
  esac
done

if [[ -n ${opt_clean:-} ]]; then
  SILENT="$opt_silent" make clean
fi

compile 9key
compile ai03/polaris 60_tsangan_hhkb
compile cannonkeys/an_c 60_tsangan_hhkb
compile cannonkeys/instant60 60_tsangan_hhkb
compile crkbd/rev1 split_3x6_3
compile dz60 60_ansi_split_bs_rshift
compile dz60 60_tsangan_hhkb
compile eco/rev2
compile kbdfans/kbd67/hotswap 65_ansi_blocker_split_bs
compile keebio/bdn9/rev1
compile keebio/quefrency/rev1
compile lily58/rev1
