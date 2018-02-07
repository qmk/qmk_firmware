echo "hit reset" && sleep 3s && avrdude.exe -p atmega32u4 -c avr109 -U flash:w:../../../handwired_core_default.hex:i -P COM7
