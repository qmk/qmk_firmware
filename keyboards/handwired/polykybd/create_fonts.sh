#! /bin/bash

echo "Enter Latin/Greek font size (eg. 14):"
read size_lat

echo "Enter Korean font size (eg. 19):"
read size_kr

echo "Enter Japanese font size (eg. 15):"
read size_jp

echo "Enter Arabic font size (eg. 16):"
read size_ar

echo "Enter Emoji font size (eg. 20):"
read size_em

fontconvert -f~/repos/noto-sans/NotoSans-Regular.ttf "-s${size_lat}" -v _Base_ 0x20 0x7e > "base/fonts/generated/0NotoSans_Regular_Base_${size_lat}pt.h"
fontconvert -f~/repos/noto-sans/NotoSans-Regular.ttf "-s${size_lat}" -v _SupAndExtA_  0xa1 0x16d > "base/fonts/generated/1NotoSans_Regular_SupAndExtA_${size_lat}pt.h"
fontconvert -f~/repos/noto-sans/NotoSans-Regular.ttf "-s${size_lat}" -v _EuroSign_  0x20ac 0x20ac > "base/fonts/generated/2NotoSans_Regular_EuroSign_${size_lat}pt.h"
fontconvert -f~/repos/noto-sans/NotoSans-Regular.ttf "-s${size_lat}" -v _GreekChi_ 0x2c7 0x2c7 > "base/fonts/generated/NotoSans_Regular_GreekChi_${size_lat}pt.h"
fontconvert -f~/repos/noto-sans/NotoSans-Regular.ttf "-s${size_lat}" -v _GreekTonos_  0x384 0x385 > "base/fonts/generated/NotoSans_Regular_GreekTonos_${size_lat}pt.h"
fontconvert -f~/repos/noto-sans/NotoSans-Regular.ttf "-s${size_lat}" -v _GreekBase_  0x391 0x3c9 > "base/fonts/generated/NotoSans_Regular_GreekBase_${size_lat}pt.h"
fontconvert -f~/repos/noto-sans-jp/NotoSansJP-Regular.otf "-s${size_jp}" -v _Hiragana_ 0x3041 0x309f > "base/fonts/generated/NotoSansJP_Regular_Hiragana_${size_jp}pt.h"
fontconvert -f~/repos/noto-sans-jp/NotoSansJP-Regular.otf "-s${size_jp}" -v _Punct_ 0x3001 0x3002 0x300c 0x300d > "base/fonts/generated/NotoSansJP_Regular_Punct_${size_jp}pt.h"
fontconvert -f~/repos/noto-sans-jp/NotoSansJP-Regular.otf "-s${size_jp}" -v _PunctSupl_ 0x30fb 0x30fc > "base/fonts/generated/NotoSansJP_Regular_PunctSupl_${size_jp}pt.h"
fontconvert -f~/repos/noto-sans-kr/NotoSansKR-Regular.otf "-s${size_kr}" -v _Vowels_ 0x1161 0x1169 0x116d 0x116e 0x1172 0x1175 > "base/fonts/generated/NotoSansKR_Regular_Vowels_${size_kr}pt.h"
fontconvert -f~/repos/noto-sans-kr/NotoSansKR-Regular.otf "-s${size_kr}" -v _Consonants_ 0x1100 0x1112 > "base/fonts/generated/NotoSansKR_Regular_Consonants_${size_kr}pt.h"
fontconvert -f~/repos/noto-sans-arabic/static/NotoSansArabic/NotoSansArabic-Regular.ttf "-s${size_ar}" -r40 -v _Isolated_ 0x60c 0x669 > "base/fonts/generated/NotoSansAR_Regular_Isolated_${size_ar}pt.h"
fontconvert -f~/repos/noto-sans-arabic/static/NotoSansArabic/NotoSansArabic-Regular.ttf "-s${size_ar}" -r40 -v _FormsB_ 0xfef5 0xfef5 0xfefb 0xfefb > "base/fonts/generated/NotoSansAR_Regular_FormsB_${size_ar}pt.h"
fontconvert -f~/repos/Noto_Emoji/static/NotoEmoji-Medium.ttf "-s${size_em}" -r50 -v _World_ -n0x11000 0x1F310 0x1F310 > "base/fonts/generated/3NotoEmoji_Medium_World_${size_em}pt.h"
#fontconvert -f~/repos/Noto_Emoji/static/NotoEmoji-Medium.ttf "-s${size_em}" -r50 -v _Home_ -n0x11000 0x1F3E0 0x1F3E0 > "base/fonts/generated/3NotoEmoji_Medium_Home_${size_em}pt.h"
fontconvert -f~/repos/Noto_Emoji/static/NotoEmoji-Medium.ttf "-s${size_em}" -r50 -v _Lock_ -n0x11000 0x1F512 0x1F512 > "base/fonts/generated/3NotoEmoji_Medium_Lock_${size_em}pt.h"
fontconvert -f~/repos/Noto_Sans_Symbols_2/NotoSansSymbols2-Regular.ttf "-s${size_em}" -r50 -v _Technical_ 0x2318 0x2318 0x2325 0x2326 0x232B 0x232B > "base/fonts/generated/3NotoSansSymbols2_Regular_Technical_${size_em}pt.h"
fontconvert -f~/repos/Noto_Sans_Symbols_2/NotoSansSymbols2-Regular.ttf "-s${size_em}" -r50 -v _Arrows_ 	0x2B70 0x2B73 0x2B7E 0x2B7E 0x2BA0 0x2BA0 > "base/fonts/generated/3NotoSansSymbols2_Regular_Arrows_${size_em}pt.h"
fontconvert -f~/repos/Noto_Sans_Symbols_2/NotoSansSymbols2-Regular.ttf "-s${size_em}" -r50 -v _Cut_ 0x2702 0x2702 > "base/fonts/generated/3NotoSansSymbols2_Regular_Cut_${size_em}pt.h"
fontconvert -f~/repos/Noto_Sans_Symbols_2/NotoSansSymbols2-Regular.ttf "-s${size_em}" -r50 -v _Diamond_ 0x2756 0x2756 > "base/fonts/generated/3NotoSansSymbols2_Regular_Diamond_${size_em}pt.h"

#    	0x1F568 	0x1F56A //mute vol dn vol up
#        	0x1F4CB //clipboard copy
#            0x1F5C7 //clipboard paste
#            0x2702 //cut
#2399 print scrn
#            		0x1F5B3 //my computer
#               -     //HDD
#                0x1F5B5 //screen
#                	0x1F5B6 //print
#                    	0x1F5A9 //calculator
#                        0x1F5A9 //floppy disk / save
#                        0x1F5D5 // window minimize
#                        0x1F5D6 // window max
#                        	0x1F5D7 // window switch
#                            0x1F5D8 // refresh
#                            0x1F5D9 // delete
#                            0x1F5DA // inc font size
#                            0x1F5DB // dec font size
cd base/fonts
echo -e "#pragma once\n" > gfx_used_fonts.h
ls -1 generated/*pt.h | while read line; do echo '#include "'${line}'"'; done >> gfx_used_fonts.h
echo -e '#include "gfx_icons.h"\n' >> gfx_used_fonts.h
echo -e '#include "FreeSansBold24pt7b.h"\n' >> gfx_used_fonts.h
echo -e 'const GFXfont* ALL_FONTS [] = {' >> gfx_used_fonts.h
echo -e '  &IconsFont,' >> gfx_used_fonts.h
cat  generated/*pt.h | grep -oP 'const GFXfont \K\w+' | while read line; do echo "  &"${line}","; done >> gfx_used_fonts.h
echo -e '};\n' >> gfx_used_fonts.h
