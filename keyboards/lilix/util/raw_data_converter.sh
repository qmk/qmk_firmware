#!/bin/zsh
#
# Author:       Elizabeth Bodaneze 2021
# Description:  Convert pictures to the raw format used by SSD1306 on QMK
# Requires:     zsh, imagemagick, sed
# Usage:        ./raw_data_converter.sh picture.ext
#               Output can also be redirected to a file by adding " > file.h" to the line above
#
# Thanks to those who wrote the OLED driver guide at
# https://beta.docs.qmk.fm/using-qmk/hardware-features/displays/feature_oled_driver ,
# especially the buffer read example, and the online conversion tool at
# https://joric.github.io/qle/ , which helped me to understand how SSD1306 pixel
# scanning and encoding work.

input_file=$1

if [[ -z "${input_file}" ]] || ! [[ -a "${input_file}" ]]; then
    printf 'File "%s" not found.\n' "${input_file}"
    exit 1
fi

width=$(convert $input_file xbm:- | grep width | cut -d' ' -f3)
bit_weight=1
line_counter=0

# First convert our picture to a 1-bit per pixel image, then convert it
# to an X11 PixMap and delete the lines containing metadata; This might
# seem a bit of a mess, but it's better than converting to an X11 BitMap
# or straight up using the PBM, because then you'd have to disentangle
# the internal representation of 8 pixels wide as a single byte
convert $input_file pbm:-  \
    | convert pbm:- xpm:-  \
    | sed -e '1,7d'   \
        -e '$d'       \
        -e 's/"//g'   \
        -e 's/,$//'   \
        -e 's/\./1/g' \
        -e 's/ /0/g'  \
    | while read line ; do
        # Read the input characters one by one and add everything to an
        # array as we go, combining every 8 characters tall into a single
        # byte. Pixel weight looks like this:
        #
        # col 1  col 2  col 3  col 4  col 5  col 6  col 7  col 8
        #   1      1      1      1      1      1      1      1
        #   2      2      2      2      2      2      2      2
        #   4      4      4      4      4      4      4      4
        #   8      8      8      8      8      8      8      8
        #  16     16     16     16     16     16     16     16
        #  32     32     32     32     32     32     32     32
        #  64     64     64     64     64     64     64     64
        # 128    128    128    128    128    128    128    128
        #
        # Thus, an 8x8 area with all pixels turned on gives the raw data:
        #
        # 255,   255,   255,   255,   255,   255,   255,   255
        #
        for ((i=0;i<=width;i++)); do
            # Read just a single character from $line and put it on the bit variable
            bit=${line:$i:1}
            (( current_char = (line_counter * width) + i + 1 ))
            (( char[current_char] += bit * bit_weight ))
        done

        # Double the bit weight for every $width characters on the line
        (( bit_weight = bit_weight * 2 ))

        # ...but limit it to 128, and advance a line when we've reached 8 pixels tall
        if (( bit_weight > 128 )) ; then
            (( bit_weight = 1 ))
            (( line_counter++ ))
        fi
    done


# Spit everything out, neatly formatted

(( total_chars = width * line_counter ))
stripped_filename=$( echo $input_file | sed "s/\..*//;s/ /_/g" )

printf "static void render_logo(void) {\n"
printf "    static const char %s[] PROGMEM = {\n" "$stripped_filename"

for ((y=0;y<line_counter;y++)); do
    printf "        "

    for ((x=0;x<width;x++)); do
        (( current_char = (y * width) + x + 1 ))

        if (( current_char < total_chars )) ; then
            printf "%3d," "$char[current_char]"
        else
            # Don't end the line with "," if we're on the last character,
            # close the array with "};" instead
            printf "%3d\n" "$char[current_char]"
            printf "    };"
        fi
    done

    printf "\n"
done

printf "\n    oled_write_raw_P(%s, sizeof(%s));\n" "$stripped_filename" "$stripped_filename"
printf "}\n"
