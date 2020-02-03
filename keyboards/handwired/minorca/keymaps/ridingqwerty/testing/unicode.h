#pragma once
//#include "minorca.h"

enum unicode_name {
  // upper greek
  UALP,
  UBET,
  UGAM,
  UDEL,
  UEPS,
  UZET,
  UETA,
  UTHE,
  UIOT,
  UKAP,
  ULAM,
  UMU,
  UNU,
  UXI,
  UOMI,
  UPI,
  URHO,
  USIG,
  UTAU,
  UUPS,
  UPHI,
  UCHI,
  UPSI,
  UOME,
  // lower greek
  LALP,
  LBET,
  LGAM,
  LDEL,
  LEPS,
  LZET,
  LETA,
  LTHE,
  LIOT,
  LKAP,
  LLAM,
  LMU,
  LNU,
  LXI,
  LOMI,
  LPI,
  LRHO,
  LSIG,
  LTAU,
  LUPS,
  LPHI,
  LCHI,
  LPSI,
  LOME,
  //
  // Elder Futhark
  // https://en.wikipedia.org/wiki/Runic_(Unicode_block)
  FE,
  UR,
  THURS,
  ANSUZ,
  RAIDO,
  KAUNA,
  GEBO,
  WUNJO,
  HAGLZ,
  NAUDZ,
  ISAZ,
  JERAN,
  IWAZ,
  PERTH,
  ALGIZ,
  SOWIL,
  TIWAZ,
  BEORC,
  EHWAZ,
  MANNZ,
  LAUKZ,
  INGWZ,
  DAGAZ,
  ETHEL,
};

const uint32_t PROGMEM unicode_map[] = {
  // upper greek
  [UALP] = 0x0391, // Α
  [UBET] = 0x0392, // Β
  [UGAM] = 0x0393, // Γ
  [UDEL] = 0x0394, // Δ
  [UEPS] = 0x0395, // Ε
  [UZET] = 0x0396, // Ζ
  [UETA]  = 0x0397, // Η
  [UTHE] = 0x0398, // Θ
  [UIOT] = 0x0399, // Ι
  [UKAP] = 0x039A, // Κ
  [ULAM] = 0x039B, // Λ
  [UMU]   = 0x039C, // M
  [UNU]   = 0x039D, // Ν
  [UXI]   = 0x039E, // Ξ
  [UOMI] = 0x039F, // Ο
  [UPI]   = 0x03A0, // Π
  [URHO]  = 0x03A1, // Ρ
  [USIG] = 0x03A3, // Σ
  [UTAU]  = 0x03A4, // Τ
  [UUPS] = 0x03A5, // Υ
  [UPHI]  = 0x03A6, // Φ
  [UCHI]  = 0x03A7, // Χ
  [UPSI]  = 0x03A8, // Ψ
  [UOME] = 0x03A9, // Ω
  // lower greek
  [LALP] = 0x03B1, // α
  [LBET] = 0x03B2, // β
  [LGAM] = 0x03B3, // γ
  [LDEL] = 0x03B4, // δ
  [LEPS] = 0x03B5, // ε
  [LZET] = 0x03B6, // ζ
  [LETA]  = 0x03B7, // η
  [LTHE] = 0x03B8, // θ
  [LIOT] = 0x03B9, // ι
  [LKAP] = 0x03BA, // κ
  [LLAM] = 0x03BB, // λ
  [LMU]   = 0x03BC, // μ
  [LNU]   = 0x03BD, // ν
  [LXI]   = 0x03BE, // ξ
  [LOMI] = 0x03BF, // ο
  [LPI]   = 0x03C0, // π
  [LRHO]  = 0x03C1, // ρ
  [LSIG] = 0x03C3, // σ
  [LTAU]  = 0x03C4, // τ
  [LUPS] = 0x03C5, // υ
  [LPHI]  = 0x03C6, // φ
  [LCHI]  = 0x03C7, // χ
  [LPSI]  = 0x03C8, // ψ
  [LOME] = 0x03C9, // ω
  // elder futhark
  [FE]    = 0x16A0, // ᚠ
  [UR]    = 0x16A2, // ᚢ
  [THURS] = 0x16A6, // ᚦ
  [ANSUZ] = 0x16A8, // ᚨ
  [RAIDO] = 0x16B1, // ᚱ
  [KAUNA] = 0x16B2, // ᚲ
  [GEBO]  = 0x16B7, // ᚷ
  [WUNJO] = 0x16B9, // ᚹ
  [HAGLZ] = 0x16BA, // ᚺ
  [NAUDZ] = 0x16BE, // ᚾ
  [ISAZ]  = 0x16C1, // ᛁ
  [JERAN] = 0x16C3, // ᛃ
  [IWAZ]  = 0x16C7, // ᛇ
  [PERTH] = 0x16C8, // ᛈ
  [ALGIZ] = 0x16C9, // ᛉ
  [SOWIL] = 0x16CA, // ᛊ 
  [TIWAZ] = 0x16CF, // ᛏ
  [BEORC] = 0x16D2, // ᛒ
  [EHWAZ] = 0x16D6, // ᛖ
  [MANNZ] = 0x16D7, // ᛗ
  [LAUKZ] = 0x16DA, // ᛚ
  [INGWZ] = 0x16DC, // ᛜ
  [DAGAZ] = 0x16DE, // ᛞ
  [ETHEL] = 0x16DF, // ᛟ
};

#define ALPHA XP(0,25)
/*
  [BETA] = 0x03B2, // β
  [GAMMA] = 0x03B3, // γ
  [DELTA] = 0x03B4, // δ
  [EPSLN] = 0x03B5, // ε
  [ZETA] = 0x03B6, // ζ
  [ETA]  = 0x03B7, // η
  [THETA] = 0x03B8, // θ
  [IOTA] = 0x03B9, // ι
  [KAPPA] = 0x03BA, // κ
  [LAMDA] = 0x03BB, // λ
  [MU]   = 0x03BC, // μ
  [NU]   = 0x03BD, // ν
  [XI]   = 0x03BE, // ξ
  [OMCRN] = 0x03BF, // ο
  [PI]   = 0x03C0, // π
  [RHO]  = 0x03C1, // ρ
  [SIG] = 0x03C3, // σ
  [TAU]  = 0x03C4, // τ
  [UPS] = 0x03C5, // υ
  [PHI]  = 0x03C6, // φ
  [CHI]  = 0x03C7, // χ
  [PSI]  = 0x03C8, // ψ
  [OMEGA] = 0x03C9, // ω
*/
