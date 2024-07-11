#!/bin/bash

DEBUG=0

die() {
	echo "fatal error: $*"
	exit 2
}

compare()
{
	result=$(dc -e "[[yes] n] sY $3 $1 $2Y") || die 'calculating' "$1 $2 $3"
	[ "$result" = "yes" ] && return 0
	return 1
}

lt() {
	compare "$1" '<' "$2"
}
gt() {
	compare "$1" '>' "$2"
}

nthLine() {
    n="$1"
    shift
    echo "$@" | awk "NR==$n{printf \$0}"
}

labelToKey() {
    l="$1"

    case "$l" in
        "~") k="KC_GRV";;
        "1") k="KC_1";;
        "2") k="KC_2";;
        "3") k="KC_3";;
        "4") k="KC_4";;
        "5") k="KC_5";;
        "6") k="KC_6";;
        "7") k="KC_7";;
        "8") k="KC_8";;
        "9") k="KC_9";;
        "0") k="KC_0";;

        "A") k="KC_A";;
        "B") k="KC_B";;
        "C") k="KC_C";;
        "D") k="KC_D";;
        "E") k="KC_E";;
        "F") k="KC_F";;
        "G") k="KC_G";;
        "H") k="KC_H";;
        "I") k="KC_I";;
        "J") k="KC_J";;
        "K") k="KC_K";;
        "L") k="KC_L";;
        "M") k="KC_M";;
        "N") k="KC_N";;
        "O") k="KC_O";;
        "P") k="KC_P";;
        "Q") k="KC_Q";;
        "R") k="KC_R";;
        "S") k="KC_S";;
        "T") k="KC_T";;
        "U") k="KC_U";;
        "V") k="KC_V";;
        "W") k="KC_W";;
        "X") k="KC_X";;
        "Y") k="KC_Y";;
        "Z") k="KC_Z";;

        "=") k="KC_EQL";;
        ":") k="KC_SCLN";;
        "|") k="KC_BSLS";;
        "\"") k="KC_QUOT";;
        ",") k="KC_COMM";;
        ".") k="KC_DOT";;
        "/") k="KC_SLSH";;
        "-") k="KC_MINS";;
        "[") k="KC_LBRC";;
        "]") k="KC_RBRC";;

        "TAB") k="KC_TAB";;
        "LGUI") k="KC_LGUI";;
        "RGUI") k="KC_RGUI";;
        "Spce") k="KC_SPC";;
        "Home") k="KC_HOME";;
        "End") k="KC_END";;
        "PgUp") k="KC_PGUP";;
        "PgDn") k="KC_PGDN";;
        "Del") k="KC_DEL";;
        "Menu") k="KC_MENU";;
        "Esc") k="KC_ESC";;
        "Bksp") k="KC_BSPC";;
        "Entr") k="KC_ENT";;

        "CpLk") k="KC_LCAP";;
        "Shft") k="KC_LSFT";;
        "Ctrl") k="KC_LCTL";;
        "Alt") k="KC_LALT";;
        "AltGr") k="KC_ALGR";;

        *) k="$l";;
    esac

    echo "$k"
}

printRawLayout()
{
    Layout="$1" # Sorted layout
    Char="$2"

    local interWidth=1
    local interHeight=1
    local lastX=0
    local lastY=0

    for p in $Layout; do
        x=${p%,*}
        y=${p#*,}

        toSkipY=$((y - lastY))
        if [ $toSkipY -ge 1 ]; then
            eval "printf '\n%0.s' {1..$((interHeight*toSkipY))}"
            lastX='-1' # '-1' (instead of 0) is to accomodate for empty space at the beginning of row
        fi

        toSkipX=$((x - lastX -1))
        if [ "$toSkipX" -gt 0 ]; then
            eval "printf ' %0.s' {1..$((interWidth*toSkipX))}"
        fi

        echo -n "$Char"

        lastX="$x"
        lastY="$y"
    done
}

isSplit() {
    Layout="$1"
    Char="$2"

    declare -A filledCols
    IFS='
'
    row=0
    maxCol=0
    for layLine in $Layout; do
        for (( i=0; i<${#layLine}; i++ )); do
            [ $i -gt $maxCol ] && maxCol=$i
            char="${layLine:$i:1}"
            [ "$char" = "$Char" ] && filledCols[$i]='1'
        done
    done

    for (( i=0; i<maxCol; i++ )); do
        [ -z "${filledCols[$i]}" ] && { echo "$i"; return 0; }
    done

    return 1
}

countKeys() {
    echo -n "$1" | tr -d '\n ' | wc -c
}

genWrapper() {
    Layout="$1"
    FilledChar="$2"
    SplitDiv="$3"

    echo '#define LAYOUT_wrapper( '\\

    keysCount=$(countKeys "$Layout")

    digits='0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ'
    IFS='
'
    row=0
    k=0
    for layLine in $Layout; do
        n=0
        echo -ne "\t\t"
        for (( i=0; i<${#layLine}; i++ )); do

            keyChar='K'
            [ -n "$SplitDiv" ] && [ $i -lt "$SplitDiv" ] && keyChar='L'
            [ -n "$SplitDiv" ] && [ $i -eq "$SplitDiv" ] && keyChar='L'
            [ -n "$SplitDiv" ] && [ $i -gt "$SplitDiv" ] && keyChar='R'

            layChar="${layLine:$i:1}"
                dr=${digits:$row:1}
                dc=${digits:$n:1}

                str=$(echo -n "$keyChar$dr$dc, ")
            if [ "$layChar" = "$FilledChar" ]; then
                n=$((n+1))
                k=$((k+1))
                [ "$k" -eq "$keysCount" ] && str=$(echo -n "$str" | tr -d ',')
                echo -n "$str"
            else
                echo -n "$(echo -n "$str" | tr '[:graph:]' '[ *]')"
            fi
        done

        echo \\
        row=$((row+1))
    done

    echo -e "\t)"
}

enrichRawLayout()
{
	KeyCharmap="$1"
    KeysPlacement="$2"
    KeyChar="$3"
    local -n Layout="$4"
    Prefixes="$5"

    placeholderChar='@'
	keyHeight=$(echo "$KeyCharmap" | wc -l)
    placeholderLen=$(echo "$KeyCharmap" | sed -n "/$placeholderChar/ s/[^$placeholderChar]\+//g; T; p" | wc -L)
    keysCount=$(countKeys "$KeysPlacement")

    IFS='
'
    row=0
    k=0

    # For each line from the layout
    for placementLine in $KeysPlacement; do

        # Repeat for each line of the key image/charmap (it should be multiline)
        for keyLineIdx in $(seq "$keyHeight"); do
            keyFieldTmpl=$(nthLine "$keyLineIdx" "$KeyCharmap")
            blankField=$(echo "$keyFieldTmpl" | awk '{gsub(".", " "); printf $0}')
            prefix=$(nthLine "$keyLineIdx" "$Prefixes")

            [ -n "$Prefixes" ] && printf '%s' "$prefix"

            col=0

            # Iterate over all the keys in tne line layout
            for (( i=0; i<${#placementLine}; i++ )); do
                placementChar="${placementLine:$i:1}" # this is the key from layout

                if [ "$KeyChar" = "$placementChar" ]; then
                    label=$(echo "${Layout[$col,$row]}" |
                        awk '{match($0, "[^=]+="); printf substr($0, RLENGTH+1)} ')

                    keycode=$(labelToKey "$label")
                    alignedLabel=$(printf "%-${placeholderLen}s" "$keycode")
                    keyField=$(echo "$keyFieldTmpl" |
                        awk "{sub(\"$placementChar+\", \"$alignedLabel\"); printf \$0;}")

                    [ $DEBUG -eq 1 ] && echo "[keyLine: $keyLineIdx/$keyHeight] $col,$row => $label [$keycode] || template: $keyFieldTmpl" 1>&2

                    # If the template contains lavel placeholder then increase key count by one
                    [ -n "$(echo "$keyFieldTmpl" | tr -dc "$placementChar")" ] && k=$((k+1))
                    [ "$k" -eq "$keysCount" ] && keyField=$(echo "$keyField" | tr -d ',')

                    echo -n "$keyField"
                else
                    echo -n "$blankField"
                fi
                col=$((col+1))
            done
            echo
        done

        row=$((row+1))
    done

    set +x
}

Layout="${1:-LAYOUT}"
keys=$(jq -r ".layouts.$Layout.layout | .[] | [ .matrix[], .x, .y, .label ] | @tsv" info.json)

declare -A positions

first=$(echo "$keys" | head -1)
lowx=$(echo "$first" | awk '{print $3}'); hix=$lowx;
lowy=$(echo "$first" | awk '{print $4}'); hiy=$lowy;

origIFS="$IFS"
IFS='
'
for line in $keys; do
    row=$(echo "$line" | awk '{printf $2}')
    col=$(echo "$line" | awk '{printf $1}')
    xpos=$(echo "$line" | awk '{printf $3}')
    ypos=$(echo "$line" | awk '{printf $4}')
    label=$(echo "$line" | awk '{printf $5}')

	lt "$xpos" "$lowx" && lowx="$xpos"
	gt "$xpos" "$hix" && hix="$xpos"
	lt "$ypos" "$lowy" && lowy="$ypos"
	gt "$ypos" "$hiy" && hiy="$ypos"

    # Truncated to integers - will fail for negatives (probably won't be ever used)
	trx=$(echo "$xpos" | cut -f 1 -d '.')
	try=$(echo "$ypos" | cut -f 1 -d '.')

	positions["$trx,$try"]="$row:$col@$xpos,$ypos=$label"

    [ $DEBUG -eq 1 ] && echo "key: $key => $row, $col @ $xpos($trx), $ypos($try) => $label || LINE:$line"

done

IFS="$origIFS"

# Sorted is a multiline string containing all the positions with keys sorted by row, then col (physical place)
sorted=$(echo "${!positions[@]}" | tr ' ' '\n' | sort -t ',' -n -k 2,2 -k 1,1)

key='┌─────────┐
  @@@@@@@ ,
└─────────┘'
#key='┌─┐
#└─┘'
linePrefixes=$(printf '%s\n%s\n%s' '// ' '   ' '// ')

echo

rawL=$(printRawLayout "$sorted" '@')

split=0
division=$(isSplit "$rawL" '@')
[ -n "$division" ] && split=1

wrapper=$(genWrapper "$rawL" '@' "$division")
richL=$(enrichRawLayout "$key" "$rawL" '@' positions "$linePrefixes")

echo "/*"
[ $split -eq 1 ] && echo "Split (division col = $division)"
echo "range: (physical)"
echo "x: ($lowx, $hix)"
echo "y: ($lowy, $hiy)"
echo "*/"

echo "$wrapper"
echo "$richL"
echo

