# Image to Hex Converter
# Copyright (c) 2018 MakotoKurauchi
# MIT License

from PIL import Image
from numpy import *
import sys

argvs = sys.argv
argc = len(argvs)

if (argc != 2):
	print ('Usage: $ python %s filename' % argvs[0])
	quit()

im = array(Image.open(argvs[1]).rotate(-90, expand=True))

#print (im)

fontw = 6
fonth = 8
rowmax = 32
colmax = len(im[0])//fonth 

for colc in range(colmax):
	for rowc in range(rowmax):
		line = ""
		for fontwc in range(fontw):
			val=0
			for fonthc in range(fonth):
				b = 1 if im[fontw*rowc+fontwc][fonth*(colmax-1)-fonth*colc+fonthc][0]<128 else 0
				val = (val<<1)|b
			line += '0x%02X' % val + ', '
		print (line)
