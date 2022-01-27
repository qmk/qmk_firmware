/* Copyright 2021 @nstickney
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

enum {
	// Used on base

	// Used on US-International
	IEX, SS2, SS3, CUR, EUR, V14, V12, V34, LSQ, RSQ, YEN, MLT,
	A_D, A_R, E_A, REG, THR, U_D, U_A, I_A, O_A, O_D, LDA, RDA, NOT,
	A_A, S_S, ETH, EMD, OEL, O_S, PLC, ACT,
	AEL, CPR, N_T, MCR, C_C, IQM,

	// Used on US-International with Shift
	SS1, GBP, DIV,
	AXD, ACR, ECA, UCD, UCA, ICA, OCA, OCD, BKB,
	ACA, SEC, ETC, OEC, OCS, DEG, DIS,
	AEC, CNT, NCT, CCC,

	// Added to US-International

	// Added to US-International with Shift
	LDQ, RDQ,
	CPL
};

const uint32_t PROGMEM unicode_map[] = {
	[IEX] = 0xA1,   // ¡
	[SS2] = 0xB2,   // ²
	[SS3] = 0xB3,   // ³
	[CUR] = 0xA4,   // ¤
	[EUR] = 0x20AC, // €
	[V14] = 0xBC,   // ¼
	[V12] = 0xBD,   // ½
	[V34] = 0xBE,   // ¾
	[LSQ] = 0x2018, // ‘
	[RSQ] = 0x2019, // ’
	[YEN] = 0xA5,   // ¥
	[MLT] = 0xD7,   // ×
	[A_D] = 0xE4,   // ä
	[A_R] = 0xE5,   // å
	[E_A] = 0xE9,   // é
	[REG] = 0xAE,   // ®
	[THR] = 0xFE,   // þ
	[U_D] = 0xFC,   // ü
	[U_A] = 0xFA,   // ú
	[I_A] = 0xED,   // í
	[O_A] = 0xF3,   // ó
	[O_D] = 0xF6,   // ö
	[LDA] = 0xAB,   // «
	[RDA] = 0xBB,   // »
	[NOT] = 0xAC,   // ¬
	[A_A] = 0xE1,   // á
	[S_S] = 0xDF,   // ß
	[ETH] = 0xF0,   // ð
	[EMD] = 0x2014, // —
	[OEL] = 0x153,  // œ
	[O_S] = 0xF8,   // ø
	[PLC] = 0xB6,   // ¶
	[ACT] = 0xB4,   // ´
	[AEL] = 0xE6,   // æ
	[CPR] = 0xA9,   // ©
	[N_T] = 0xF1,   // ñ
	[MCR] = 0xB5,   // µ
	[C_C] = 0xE7,   // ç
	[IQM] = 0xBF,   // ¿
	[SS1] = 0xB9,   // ¹
	[GBP] = 0xA3,   // £
	[DIV] = 0xF7,   // ÷
	[AXD] = 0xC4,   // Ä
	[ACR] = 0xC5,   // Å
	[ECA] = 0xC9,   // É
	[UCD] = 0xDC,   // Ü
	[UCA] = 0xDA,   // Ú
	[ICA] = 0xCD,   // Í
	[OCA] = 0xD3,   // Ó
	[OCD] = 0xD6,   // Ö
	[BKB] = 0xA6,   // ¦
	[ACA] = 0xC1,   // Á
	[SEC] = 0xA7,   // §
	[ETC] = 0xD0,   // Ð
	[OEC] = 0x152,  // Œ
	[OCS] = 0xD8,   // Ø
	[DEG] = 0xB0,   // °
	[DIS] = 0xA8,   // ¨
	[AEC] = 0xC6,   // Æ
	[CNT] = 0xA2,   // ¢
	[NCT] = 0xD1,   // Ñ
	[CCC] = 0xC7,   // Ç
	[LDQ] = 0x201C, // “
	[RDQ] = 0x201D, // ”
	[CPL] = 0x1F12F // 🄯
};
