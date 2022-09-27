#! /bin/bash

echo "Enter Latin font size (eg. 12):"
read size_lat

echo "Enter Korean font size (eg. 12):"
read size_kr

echo "Enter Japanese font size (eg. 12):"
read size_jp

echo "Enter Arabic font size (eg. 12):"
read size_ar

fontconvert -f~/repos/noto-sans/NotoSans-Regular.ttf "-s${size_lat}" -v _Base_ 0x20 0x7e > "NotoSans_Regular_Base_${size_lat}pt.h"
fontconvert -f~/repos/noto-sans/NotoSans-Regular.ttf "-s${size_lat}" -v _SupAndExtA_  0xa1 0x16d > "NotoSans_Regular_SupAndExtA_${size_lat}pt.h"
fontconvert -f~/repos/noto-sans-jp/NotoSansJP-Regular.otf "-s${size_jp}" 12353 12447 > "NotoSansJP_Regular_${size_jp}pt.h"
fontconvert -f~/repos/noto-sans-kr/NotoSansKR-Regular.otf "-s${size_kr}" -v _Vowels_ 0x1161 0x1169 0x116d 0x116e 0x1172 0x1175 > "NotoSansKR_Regular_Vowels_${size_kr}pt.h"
fontconvert -f~/repos/noto-sans-kr/NotoSansKR-Regular.otf "-s${size_kr}" -v _Consonants_ 0x1100 0x1112 > "NotoSansKR_Regular_Consonants_${size_kr}pt.h"
fontconvert -f~/repos/noto-sans-arabic/static/NotoSansArabic/NotoSansArabic-Regular.ttf "-s${size_ar}" 0x61f 0x64a 0x660 0x669 > "NotoSansArabicStatic_Regular_${size_ar}pt.h"

echo -e "#pragma once\n" >gfx_used_fonts.h
ls -1 *pt.h | while read line; do echo '#include "'${line}'"'; done >> gfx_used_fonts.h
echo -e '#include "gfx_icons.h"\n' >> gfx_used_fonts.h
echo -e '#include "gfx_used_symbols.h"\n' >> gfx_used_fonts.h
echo -e '#include "FreeSansBold24pt7b.h"\n' >> gfx_used_fonts.h
echo -e 'const GFXfont* ALL_FONTS [] = {' >> gfx_used_fonts.h
echo -e '  &IconsFont,' >> gfx_used_fonts.h
cat  *pt.h | grep -oP 'const GFXfont \K\w+' | while read line; do echo "  &"${line}","; done >> gfx_used_fonts.h
echo -e '};\n' >> gfx_used_fonts.h
