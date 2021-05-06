#!/bin/zsh

image_file=lili
source_file=helixfont.h

to_source() {
  (
  echo '// Custom OLED display font'
  echo
  echo '#include "progmem.h"'
  echo
  echo 'static const unsigned char font[] PROGMEM = {'
  python3 FontConverter/img2hex.py "${image_file}.bmp" \
    | sed  -e 's/^/  /' \
           -e '$s/\, $//g'
  echo '};'
  ) > "${source_file}"
}

to_image() {
  sed '1,5d;$d' helixfont.h > font.hex
  python3 FontConverter/hex2img.py font.hex "${image_file}"
}

usage="\
Usage edit_font.sh -[e[k]|r] -[f str] -[s str] -[h]\n\
\n\
Options:\n\
  -e      edit mode, converts the source to a BMP image\n\
  -r      record mode, converts a BMP image to a source files\n\
  -f str  specify a filename for the BMP that's not \"${image_file}\"\n\
  -s str  specify a filename for the soruce that's not \"${source_file}\"\n\
  -k      opens the resulting bitmap with krita after converting\n\
  -h      this help text\n"

while getopts ':erf:s:kh' opt ; do
  case $opt in
    e) edit=1                    ;;
    r) record=1                  ;;
    f) image_file=$OPTARG        ;;
    s) source_file=$OPTARG       ;;
    k) krita=1                   ;;
    h) echo -n "$usage" ; exit 0 ;;
    ?) echo -n "$usage" ; exit 1 ;;
  esac
done

if [[ -n $edit ]] ; then
  to_image
  [[ -n $krita ]] && krita "${image_file}.bmp"
elif [[ -n $record ]] ; then
  to_source
fi
