# Hex to Image Converter
# Copyright (c) 2018 MakotoKurauchi
# MIT License

from PIL import Image
from numpy import *
import sys

argvs = sys.argv
argc = len(argvs)

if (argc != 3):
	print ('Usage: $ python %s file output-file' % argvs[0])
	quit()

f = open(argvs[1])
txt = f.read()
f.close()

lines = txt.split('\n')
arr = []
for line in lines:
	line = line.split('//')
	data = line[0].split(',')
	ar = []
	for hex in data:
		hex = hex.strip()
		if hex.startswith('0x'):
			ar.append(int(hex.replace('0x',''),16))
	arr.append(ar)
#print (arr)

img = []

colmax = 32
rowmax = len(arr)//colmax
fontw = 6
fonth = 8
for colc in range(colmax):
	for fontwc in range(len(arr[0])):
		tmp=[]
		for rowc in range(rowmax):
			for i in range(fonth):
				val = arr[colmax*(rowmax-1)-colmax*rowc+colc][fontwc]
				v = 0 if (val>>(7-i))&1 else 255
				if (fontwc == 5 and v) or (i==0 and v):
					tmp.append([200,255,255])
				else:
					tmp.append([v,v,v])
		img.append(tmp)
#print (img)

Image.fromarray(uint8(img)).rotate(90, expand=True).save(argvs[2]+'.bmp')
