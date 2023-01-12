./send.sh "0000000000000000" # Finish last message and reset.
./send.sh "1" # Begin.
./send.sh $(echo -n "$1" | perl -lpe '$_=join " ", unpack"(B8)*"' | sed "s/ //g") # Send.
