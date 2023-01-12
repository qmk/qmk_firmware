function send0() {
  xdotool key "Num_Lock"
  xdotool key "Num_Lock"
}

function send1() {
  xdotool key "Caps_Lock"
  xdotool key "Num_Lock"
  xdotool key "Num_Lock"
  xdotool key "Caps_Lock"
}

bits="$1"
if [ -z "$bits" ]
then
  bits="0000000000000000"
fi

for b in $(echo "$bits" | grep -o ".")
do
  if [ "$b" == "0" ]
  then
    send0
  else
    if [ "$b" == "1" ]
    then
      send1
    else
      echo "unknown $b"
    fi
  fi
done
#xset -led named "Num Lock"
#xset -led named "Caps Lock"
