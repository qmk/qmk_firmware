#! /bin/bash

#echo "Enter Latin/Greek font size (eg. 14):"
#read size_lat
size_lat=14

#echo "Enter Korean font size (eg. 19):"
#read size_kr
size_kr=19

#echo "Enter Japanese font size (eg. 15):"
#read size_jp
size_jp=15

#echo "Enter Arabic font size (eg. 16):"
#read size_ar
size_ar=16

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
fontconvert -f~/repos/Noto_Emoji/static/NotoEmoji-Medium.ttf "-s20" -r50 -v _World_ -n0x11000 0x1F310 0x1F310 > "base/fonts/generated/3NotoEmoji_Medium_World_20pt.h"
fontconvert -f~/repos/Noto_Emoji/static/NotoEmoji-Medium.ttf "-s20" -r50 -v _Meh_ -n0x11000 0x1F410 0x1F410 > "base/fonts/generated/3NotoEmoji_Medium_Meh_20pt.h"
fontconvert -f~/repos/Noto_Emoji/static/NotoEmoji-Medium.ttf "-s20" -r50 -v _Settings_ -n0x11000 0x1F527 0x1F527 > "base/fonts/generated/3NotoEmoji_Medium_Settings_20pt.h"
fontconvert -f~/repos/Noto_Emoji/static/NotoEmoji-Medium.ttf "-s18" -r48 -v _Hyper_ -n0x11000 0x1F4AB 0x1F4AB > "base/fonts/generated/3NotoEmoji_Medium_Hyper_18pt.h"
fontconvert -f~/repos/Noto_Emoji/static/NotoEmoji-Medium.ttf "-s20" -r50 -v _Light_ -n0x11000 0x1F4A1 0x1F4A1 > "base/fonts/generated/6NotoEmoji_Medium_Light_20pt.h"
fontconvert -f~/repos/Noto_Emoji/static/NotoEmoji-Medium.ttf "-s16" -r45 -v _Brightness_ -n0x11000 0x1F311 0x1F318 > "base/fonts/generated/5NotoEmoji_Medium_Brightness_16pt.h"
fontconvert -f~/repos/Noto_Emoji/static/NotoEmoji-Medium.ttf "-s20" -r50 -v _AI_ -n0x11000 0x1F300 0x1F300 > "base/fonts/generated/6NotoEmoji_Medium_AI_20pt.h"
fontconvert -f~/repos/Noto_Emoji/static/NotoEmoji-Medium.ttf "-s14" -r50 -v _FileOpen_ -n0x11000 0x1F4C2 0x1F4C2 > "base/fonts/generated/4NotoEmoji_Medium_FileOpen_14pt.h"
fontconvert -f~/repos/Noto_Emoji/static/NotoEmoji-Medium.ttf "-s18" -r50 -v _Lock_ -n0x11000 0x1F512 0x1F512 > "base/fonts/generated/5NotoEmoji_Medium_Lock_20pt.h"
fontconvert -f~/repos/Noto_Emoji/static/NotoEmoji-Medium.ttf "-s18" -r50 -v _ClipCpy_ -n0x11000 0x1F4CB 0x1F4CB > "base/fonts/generated/4NotoEmoji_Medium_Copy_18pt.h"
fontconvert -f~/repos/Noto_Emoji/static/NotoEmoji-Medium.ttf "-s18" -r50 -v _Find_ -n0x11000 0x1F50E 0x1F50E > "base/fonts/generated/4NotoEmoji_Medium_Find_18pt.h"
fontconvert -f~/repos/Noto_Emoji/static/NotoEmoji-Medium.ttf "-s12" -r50 -v _Note_ -n0x11000 0x1f4dd 0x1f4dd > "base/fonts/generated/5NotoEmoji_Medium_Note_12pt.h"
fontconvert -f~/repos/Noto_Emoji/static/NotoEmoji-Medium.ttf "-s20" -r50 -v _Emojis0_ -n0x10000 0x1f600 0x1f64f > "base/fonts/generated/6NotoEmoji_Medium_Emoji0_20pt.h"
fontconvert -f~/repos/Noto_Emoji/static/NotoEmoji-Medium.ttf "-s20" -r50 -v _Emojis1_ -n0xfd00 0x1f440 0x1f453 0x1f47b 0x1f496 0x1f4a1 0x1f4b1 > "base/fonts/generated/7NotoEmoji_Medium_Emoji1 _20pt.h"
fontconvert -f~/repos/Noto_Emoji/static/NotoEmoji-Medium.ttf "-s20" -r50 -v _Emojis2_ -n0x10100 0x1F912 0x1F919 > "base/fonts/generated/7NotoEmoji_Medium_Emoji2_20pt.h"
fontconvert -f~/repos/Noto_Sans_Symbols_2/NotoSansSymbols2-Regular.ttf "-s20" -r50 -v _Technical_ 0x2318 0x2318 0x2325 0x2326 0x232B 0x232B 0x2611 0x2611 > "base/fonts/generated/3NotoSansSymbols2_Regular_Technical_20pt.h"
fontconvert -f~/repos/Noto_Sans_Symbols_2/NotoSansSymbols2-Regular.ttf "-s20" -r50 -v _Box_ 0x2611 0x2611 > "base/fonts/generated/4NotoSansSymbols2_Regular_Box_20pt.h"
fontconvert -f~/repos/Noto_Sans_Symbols_2/NotoSansSymbols2-Regular.ttf "-s20" -r50 -v _Arrows_ 	0x2B6F 0x2B73 0x2B7E 0x2B7E 0x2B8C 0x2B8C 0x2B8E 0x2B8E 0x2BA0 0x2BA0 > "base/fonts/generated/3NotoSansSymbols2_Regular_Arrows_20pt.h"
fontconvert -f~/repos/Noto_Sans_Symbols_2/NotoSansSymbols2-Regular.ttf "-s20" -r50 -v _Diamond_ 0x2756 0x2756 > "base/fonts/generated/3NotoSansSymbols2_Regular_Diamond_20pt.h"
fontconvert -f~/repos/Noto_Sans_Symbols_2/NotoSansSymbols2-Regular.ttf "-s20" -r50 -v _ClipCut_ 0x2702 0x2702 > "base/fonts/generated/4NotoSansSymbols2_Regular_Cut_20pt.h"
fontconvert -f~/repos/Noto_Sans_Symbols_2/NotoSansSymbols2-Regular.ttf "-s20" -r50 -v _ClipPaste_ -n0x11000 0x1F5CA 0x1F5CA > "base/fonts/generated/4NotoSansSymbols2_Regular_Paste_20pt.h"
fontconvert -f~/repos/Noto_Sans_Symbols_2/NotoSansSymbols2-Regular.ttf "-s20" -r50 -v _Volume_ -n0x11000 0x1F568 0x1F56A > "base/fonts/generated/5NotoSansSymbols2_Regular_Volume_20pt.h"
fontconvert -f~/repos/Noto_Sans_Symbols_2/NotoSansSymbols2-Regular.ttf "-s20" -r50 -v _Calc_ -n0x11000 0x1F5A9 0x1F5AB > "base/fonts/generated/5NotoSansSymbols2_Regular_Calc_20pt.h"
fontconvert -f~/repos/Noto_Sans_Symbols_2/NotoSansSymbols2-Regular.ttf "-s20" -r50 -v _HW_ -n0x11000 0x1F5B3 0x1F5BC > "base/fonts/generated/5NotoSansSymbols2_Regular_Hardware_20pt.h"
fontconvert -f~/repos/Noto_Sans_Symbols_2/NotoSansSymbols2-Regular.ttf "-s18" -r50 -v _Window_ -n0x11000 0x1F5D5 0x1F5DB > "base/fonts/generated/5NotoSansSymbols2_Regular_Window_18pt.h"


cd base/fonts
echo -e "#pragma once\n" > gfx_used_fonts.h
ls -1 generated/*pt.h | while read line; do echo '#include "'${line}'"'; done >> gfx_used_fonts.h
echo -e '#include "gfx_icons.h"\n' >> gfx_used_fonts.h
echo -e '#include "FreeSansBold24pt7b.h"\n' >> gfx_used_fonts.h
echo -e 'const GFXfont* ALL_FONTS [] = {' >> gfx_used_fonts.h
echo -e '  &IconsFont,' >> gfx_used_fonts.h
cat  generated/*pt.h | grep -oP 'const GFXfont \K\w+' | while read line; do echo "  &"${line}","; done >> gfx_used_fonts.h
echo -e '};\n' >> gfx_used_fonts.h
