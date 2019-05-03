This directory of documentation  was copied from https://github.com/wjanssens/tmk_keyboard/tree/master/keyboard/kinesis
and is probably Copyright 2014 Warren Janssens <warren.janssens@gmail.com>
and probably released under GPL v2, which may be recovered at <http://www.gnu.org/licenses/>.

Row configuration
PF0	A
PF1	B
PF2	C
PF3	G	0 = U4, 1 = U5

Column configuration
			4y0	4y1	4y2	4y3	4y4	4y5	4y6	4y7	5y0	5y1	5y2	5y3	5y4	5y5	5y6	5y7	
			r1	r2	 r3 r4	r5	r6	r7	r8	r9	r10	r11	r12	r13	r14	r15	r16	
PB0	21	c1	f6	f8	f7	5	4	3	2	1	=+								
PB1	22	c2	f3	f5	f4	t	r	e	w	q	TAB								
PB2	23	c3	ESC	f2	f1	g	f	d	s	a	CL								
PB3	24	c4	f9	f11	f10	b	v	c	x	z	LS	UP		DN		[{	]}		
PB4	25	c5  	f12	SL	PS	RT		LT	§±	`~		6	7	8		9	0	-_ 	
PB5	26	c6	PB	PGM	KPD							y	u	i		o	p	\	
PB6	27	c7  			LC	DL	BS	RC	EN	SP	h	j	k		l	;:	'"	
PB7	28	c8					RA		PU		PD	n	m	,<		.>	/?	RS	
 */

schematic:
https://i.imgur.com/cCmWH4E.png

photos:
https://i.imgur.com/xiaE4tk.jpg
https://i.imgur.com/PQ1y2vS.jpg
https://i.imgur.com/OoQvgfA.jpg

40 pin connector

   DL2	1	40	VCC
   DR1	2	39	A
   DR2	3	38	B
   DL1	4	37	C
   KPD	5	36	G
   PGM	6	35
   SCL	7	34
   SDA	8	33
   RST	9	32	BUZZ
    WP	10	31	EA
   FS1	11	30	ALE
 CLOCK	12	29	PSEN
  DATA	13	28	r8
	14	27	r7
   FS3	15	26	r6
	16	25	r5
   FS2	17	24	r4
 XTAL1	18	23	r3
 XTAL2	19	22	r2
   GND	20	21	r1


references:
https://github.com/chrisandreae/keyboard-firmware


