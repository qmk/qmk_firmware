#!/usr/bin/env python3
# pip install pillow to get the PIL module

# Script from the Adafruit Monochrome OLED SSD1306 drivers

import sys
from PIL import Image

def main(fn, id):
  image = Image.open(fn)
  print("\nenum {{ {id}_width = {w}, {id}_height = {h} }};\n"
        "const uint8_t PROGMEM {id}_data[] = {{\n"
        .format(id=id, w=image.width, h=image.height), end='')
  for y in range(0, image.height):
    for x in range(0, (image.width + 7)//8 * 8):
      if x == 0:
        print("  ", end='')
      if x % 8 == 0:
        print("0b", end='')

      bit = '0'
      if x < image.width and image.getpixel((x,y)) != 0:
        bit = '1'
      print(bit, end='')

      if x % 8 == 7:
        print(",", end='')
    print()
  print("};")

if __name__ == '__main__':
    if len(sys.argv) < 3:
      print("Usage: {} <imagefile> <id>\n".format(sys.argv[0]), file=sys.stderr);
      sys.exit(1)
    fn = sys.argv[1]
    id = sys.argv[2]
    main(fn, id)
