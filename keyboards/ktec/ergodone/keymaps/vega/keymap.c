// Copyright 2021 Vega Carlson (@VegaDeftwing)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_names { BASE, GREL, GREU, SYMB, MATH, QWER, FNLR, TINY, FULL, FULU };

enum unicode_names {
    // MATH
    neq,     //≠
    intgrl,  //∫
    angl,    //∠
    imply,   //⇒
    equiv,   //⇔
    porp,    //∝
    exists,  //∃
    nexists, //∄
    forall,  //∀
    and,     //∧
    or
    ,             //∨
    xor,          //⊕
    apeql,        //≅
    root,         //√
    not,          //¬
    sum,          //∑
    plsminus,     //±
    infin,        //∞
    emtyset,      //∅
    Mn,           //ℕ
    Mz,           //ℤ
    Mq,           //ℚ
    Mr,           //ℝ
    Mc,           //ℂ
    eleof,        //∈
    member,       //∋
    neleof,       //∉
    nmember,      //∌
    subsetof,     //⊂
    suprsetof,    //⊃
    intersection, //∩
    Munion,       //∪

    // SYMB
    arwl,
    arwu,
    arwr,
    arwd,

    uxclm,
    cent,
    degree,
    trade,
    copy,
    numero,
    sect,
    mdot,
    rang,

    lshade,
    mshade,
    dshade,

    fire,
    water,
    cleft,
    baster,
    neteen,
    floppy,

    boxemp,
    boxchk,
    boxX,

    bbstr,
    bbstl,
    bbml,
    bbmr,
    bbmb,
    bbrtr,
    bbrbr,
    bbrtl,
    bbrbl,
    bbsbr,
    bbsbl,
    bbmbr,
    bbmbl,

    Agrave,
    Aacute,
    Acircm,
    Atilde,
    Abreve,
    Adiaer,
    Adacut,

    // not all ogham letters, as I
    // actually intend to use them for hex
    OS,
    Oa,
    Ob,
    Oc,
    Od,
    Oe,
    Of,
    Og,
    Oh,
    Oi,
    OA,
    OB,
    OC,
    OD,
    OE,
    OF,
    Os,
    OED,
    Ox,
    gnd,
    sqr,
    sine,
    opt,

    geq,
    leq,
    brkup,
    brkdn,
    perup,
    perdn,

    // GREEL
    rone, // 1:: ⅰ
    rtwo,
    rthree,
    rfour,  // 4:: ⅳ
    rfive,  // 5:: ⅴ
    rsix,   // 6:: ⅵ
    rseven, // 7:: ⅶ
    reight, // 8:: ⅷ
    rnine,  // 9:: ⅸ
    rten,   // 0:: ⅹ
    gq,     // q:: θ
    gw,     // w:: ω
    ge,     // e:: ε
    gr,     // r:: ρ
    gt,     // t:: τ
    gy,     // y:: ψ
    gu,     // u:: υ
    gi,     // i:: ι
    go,     // o:: ο
    gp,     // p:: π
    ga,     // a:: α
    gs,     // s:: σ
    gd,     // d:: δ
    gf,     // f:: φ
    gg,     // g:: γ
    gh,     // h:: η
    gj,     // j:: ϑ
    gk,     // k:: κ
    gl,     // l:: λ
    gz,     // z:: ζ
    gx,     // x:: ξ
    gc,     // c:: χ
    gv,     // v:: ς
    gb,     // b:: β
    gn,     // n:: ν
    gm,     // m:: μ

    // GREEU
    Rone,   // 1:: Ⅰ
    Rtwo,   // 2:: Ⅱ
    Rthree, // 3:: Ⅲ
    Rfour,  // 4:: Ⅳ
    Rfive,  // 5:: Ⅴ
    Rsix,   // 6:: Ⅵ
    Rseven, // 7:: Ⅶ
    Reight, // 8:: Ⅷ
    Rnine,  // 9:: Ⅸ
    Rten,
    Gq, // Q:: Θ
    Gw, // W:: Ω
    Ge, // E:: Ε
    Gr, // R:: Ρ
    Gt, // T:: Τ
    Gy, // Y:: Ψ
    Gu, // U:: Υ
    Gi, // I:: Ι
    Go, // O:: Ο
    Gp, // P:: Π
    Ga, // A:: Α
    Gs, // S:: Σ
    Gd, // D:: Δ
    Gf, // F:: Φ
    Gg, // G:: Γ
    Gh, // H:: Η
    Gj, // J:: J
    Gk, // K:: Κ
    Gl, // L:: Λ
    Gz, // Z:: Ζ
    Gx, // X:: Ξ
    Gc, // C:: Χ
    Gv, // V:: V
    Gb, // B:: Β
    Gn, // N:: Ν
    Gm, // M:: Μ
    // ᵃ ᵇ ᶜ ᵈ ᵉ ᶠ ᵍ ʰ ⁱ ʲ ᵏ ˡ ᵐ ⁿ ᵒ ᵖ ʳ ˢ ᵗ ᵘ ᵛ ʷ ˣ ʸ ᶻ ⁰ ¹ ² ³ ⁴ ⁵ ⁶ ⁷ ⁸ ⁹
    tone,   // 1:: ¹
    ttwo,   // 2:: ²
    tthree, // 3:: ³
    tfour,  // 4:: ⁴
    tfive,  // 5:: ⁵
    tsix,   // 6:: ⁶
    tseven, // 7:: ⁷
    teight, // 8:: ⁸
    tnine,  // 9:: ⁹
    tzero,  // 0 :: ⁰
    tq,     // Q:: ۹
    tw,     // W:: ʷ
    te,     // E:: ᵉ
    tr,     // R:: ʳ
    tt,     // T:: ᵗ
    ty,     // Y:: ʸ
    tu,     // U:: ᵘ
    ti,     // I:: ⁱ
    to,     // O:: ᵒ
    tp,     // P:: ᵖ
    ta,     // A:: ᵃ
    ts,     // S:: ˢ
    td,     // D:: ᵈ
    tf,     // F:: ᶠ
    tg,     // G:: ᵍ
    th,     // H:: ʰ
    tj,     // J:: ʲ
    tk,     // K:: ᵏ
    tl,     // L:: ˡ
    tz,     // Z:: ᶻ
    tx,     // X:: ˣ
    tc,     // C:: ᶜ
    tv,     // V:: ᵛ
    tb,     // B:: ᵇ
    tn,     // N:: ⁿ
    tm,     // M:: ᵐ
    // Fullwitdth - note, these are *not* the monospace unicode code points.
    // This is done to prevent something eating it and using a weird font, which,
    // presumably, isn't desired if doing this.
    fwone,   // 1:: １
    fwtwo,   // 2:: ２
    fwthree, // 3:: ３
    fwfour,  // 4:: ４
    fwfive,  // 5:: ５
    fwsix,   // 6:: ６
    fwseven, // 7:: ７
    fweight, // 8:: ８
    fwnine,  // 9:: ９
    fwzero,  // 0 :: ０
    fwq,     // Q:: ｑ
    fww,     // W:: ｗ
    fwe,     // E:: ｅ
    fwr,     // R:: ｒ
    fwt,     // T:: ｔ
    fwy,     // Y:: ｙ
    fwu,     // U:: ｕ
    fwi,     // I:: ｉ
    fwo,     // O:: ｏ
    fwp,     // P:: ｐ
    fwa,     // A:: ａ
    fws,     // S:: ｓ
    fwd,     // D:: ｄ
    fwf,     // F:: ｆ
    fwg,     // G:: ｇ
    fwh,     // H:: ｈ
    fwj,     // J:: ｊ
    fwk,     // K:: ｋ
    fwl,     // L:: ｌ
    fwz,     // Z:: ｚ
    fwx,     // X:: ｘ
    fwc,     // C:: ｃ
    fwv,     // V:: ｖ
    fwb,     // B:: ｂ
    fwn,     // N:: ｎ
    fwm,     // M:: ｍ
    // Full width caps + fractions, and a few extra symbols that lack a better place
    Fwone,   // 1:: ¼
    Fwtwo,   // 2:: ½
    Fwthree, // 3:: ¾
    Fwfour,  // 4:: ⅓
    Fwfive,  // 5:: ⅔
    Fwsix,   // 6:: ⅕
    Fwseven, // 7:: ⅛
    Fweight, // 8:: 𝒳
    Fwnine,  // 9:: 𝒴
    Fwzero,  // 0 :: 𝒵
    Fwq,     // Q:: Ｑ
    Fww,     // W:: Ｗ
    Fwe,     // E:: Ｅ
    Fwr,     // R:: Ｒ
    Fwt,     // T:: Ｔ
    Fwy,     // Y:: Ｙ
    Fwu,     // U:: Ｕ
    Fwi,     // I:: Ｉ
    Fwo,     // O:: Ｏ
    Fwp,     // P:: Ｐ
    Fwa,     // A:: Ａ
    Fws,     // S:: Ｓ
    Fwd,     // D:: Ｄ
    Fwf,     // F:: Ｆ
    Fwg,     // G:: Ｇ
    Fwh,     // H:: Ｈ
    Fwj,     // J:: Ｊ
    Fwk,     // K:: Ｋ
    Fwl,     // L:: Ｌ
    Fwz,     // Z:: Ｚ
    Fwx,     // X:: Ｘ
    Fwc,     // C:: Ｃ
    Fwv,     // V:: Ｖ
    Fwb,     // B:: Ｂ
    Fwn,     // N:: Ｎ
    Fwm,     // M:: Ｍ
    nbsp,    // You know what this is &nbsp;
    ibang,   //‽
    nullpic, // Null picture - ␀
};

const uint32_t PROGMEM unicode_map[] = {
    // MATH
    [neq]          = 0x2260, //≠
    [intgrl]       = 0x222B, //∫
    [angl]         = 0x2220, //∠
    [imply]        = 0x21D2, //⇒
    [equiv]        = 0x21D4, //⇔
    [porp]         = 0x221D, //∝
    [exists]       = 0x2203, //∃
    [nexists]      = 0x2204, //∄
    [forall]       = 0x2200, //∀
    [and]          = 0x2227, //∧
    [or]           = 0x2228, //∨
    [xor]          = 0x2295, //⊕
    [apeql]        = 0x2245, //≅
    [root]         = 0x221A, //√
    [not ]         = 0x00AC, //¬
    [sum]          = 0x2211, //∑
    [plsminus]     = 0x00B1, //±
    [infin]        = 0x221E, //∞
    [emtyset]      = 0x2205, //∅
    [Mn]           = 0x2115, //ℕ
    [Mz]           = 0x2124, //ℤ
    [Mq]           = 0x211A, //ℚ
    [Mr]           = 0x211D, //ℝ
    [Mc]           = 0x2102, //ℂ
    [eleof]        = 0x2208, //∈
    [member]       = 0x220B, //∋
    [neleof]       = 0x2209, //∉
    [nmember]      = 0x220C, //∌
    [subsetof]     = 0x2282, //⊂
    [suprsetof]    = 0x2283, //
    [intersection] = 0x2229, //∩
    [Munion]       = 0x222A, //∪
                             // Symbol
    [arwl] = 0x2190,         //←
    [arwu] = 0x2191,         //↑
    [arwr] = 0x2192,         //→
    [arwd] = 0x2193,         //↓

    [uxclm]  = 0x00A1, //¡
    [cent]   = 0x00A2, //¢
    [degree] = 0x00B0, //°
    [trade]  = 0x2122, //™
    [copy]   = 0x00A9, //©
    [numero] = 0x2116, //№
    [sect]   = 0x00A7, //§
    [mdot]   = 0x00B7, //·
    [rang]   = 0x299C, //⦜

    [lshade] = 0x2591, //░
    [mshade] = 0x2592, //▒
    [dshade] = 0x2593, //▓

    [fire]   = 0x1F525, //🔥
    [water]  = 0x1F322, //🌢
    [cleft]  = 0x1F12F, //🄯
    [baster] = 0x1F7BC, //🞼
    [neteen] = 0x1F51E, //🔞
    [floppy] = 0x1F5AB, //🖫

    [boxemp] = 0x2610, //☐
    [boxchk] = 0x2611, //☑
    [boxX]   = 0x2612, //☒

    [bbstr] = 0x23A1, //⎡
    [bbstl] = 0x23A4, //⎤
    [bbml]  = 0x23A8, //⎨
    [bbmr]  = 0x23AC, //⎬
    [bbmb]  = 0x23AA, //⎪
    [bbrtr] = 0x23A7, //⎧
    [bbrbr] = 0x23A9, //⎩
    [bbrtl] = 0x23AB, //⎫
    [bbrbl] = 0x23AD, //⎭
    [bbsbr] = 0x23A3, //⎣
    [bbsbl] = 0x23A6, //⎦
    [bbmbr] = 0x23A5, //⎥
    [bbmbl] = 0x23A2, //⎢

    [Agrave] = 0x0300, // è //above  [wtf] = 0x1242A, //𒐪
    [Aacute] = 0x0301, // é //1st
    [Acircm] = 0x0302, // ê //2nd
    [Atilde] = 0x0303, // ẽ //5th
    [Abreve] = 0x0306, // ĕ //4th
    [Adiaer] = 0x0308, // ë //3rd
    [Adacut] = 0x030B, // e̋

    // not all ogham letters, as I
    // actually intend to use them for hex
    [OS]  = 0x1680, // space
    [Oa]  = 0x1681, // 1
    [Ob]  = 0x1682, // 2
    [Oc]  = 0x1683, // 3
    [Od]  = 0x1684, // 4
    [Oe]  = 0x1685, // 5
    [Of]  = 0x1686, // 6
    [Og]  = 0x1687, // 7
    [Oh]  = 0x1688, // 8
    [Oi]  = 0x1689, // 9
    [OA]  = 0x168A, // A
    [OB]  = 0x168B, // B
    [OC]  = 0x168C, // C
    [OD]  = 0x168D, // D
    [OE]  = 0x168E, // E
    [OF]  = 0x168F, // F
    [Os]  = 0x169B, // Start
    [OED] = 0x169C, // End
    [Ox]  = 0x1695, // X

    [gnd]  = 0x23DA, //⏚
    [sqr]  = 0x238D, //⎍, actually monostable
    [sine] = 0x223F, //∿
    [opt]  = 0x2325, //⌥, actually option used for switch

    [geq]   = 0x2264, //≤
    [leq]   = 0x2265, //≥
    [brkup] = 0xFE38, //︸
    [brkdn] = 0xFE37, //︷
    [perup] = 0xFE35, //︵
    [perdn] = 0xFE36, //︶
    // GREEKL
    [rone]   = 0x2170, // 1:: ⅰ
    [rtwo]   = 0x2171, // 2:: ⅱ
    [rthree] = 0x2172, // 3:: ⅲ
    [rfour]  = 0x2173, // 4:: ⅳ
    [rfive]  = 0x2174, // 5:: ⅴ
    [rsix]   = 0x2175, // 6:: ⅵ
    [rseven] = 0x2176, // 7:: ⅶ
    [reight] = 0x2177, // 8:: ⅷ
    [rnine]  = 0x2178, // 9:: ⅸ
    [rten]   = 0x2179, // 0:: ⅹ
    [gq]     = 0x03B8, // q:: θ
    [gw]     = 0x03C9, // w:: ω
    [ge]     = 0x03B5, // e:: ε
    [gr]     = 0x03C1, // r:: ρ
    [gt]     = 0x03C4, // t:: τ
    [gy]     = 0x03C8, // y:: ψ
    [gu]     = 0x03C5, // u:: υ
    [gi]     = 0x03B9, // i:: ι
    [go]     = 0x03BF, // o:: ο
    [gp]     = 0x03C0, // p:: π
    [ga]     = 0x03B1, // a:: α
    [gs]     = 0x03C3, // s:: σ
    [gd]     = 0x03B4, // d:: δ
    [gf]     = 0x03C6, // f:: φ
    [gg]     = 0x03B3, // g:: γ
    [gh]     = 0x03B7, // h:: η
    [gj]     = 0x03D1, // j:: ϑ
    [gk]     = 0x03BA, // k:: κ
    [gl]     = 0x03BB, // l:: λ
    [gz]     = 0x03B6, // z:: ζ
    [gx]     = 0x03BE, // x:: ξ
    [gc]     = 0x03C7, // c:: χ
    [gv]     = 0x03C2, // v:: ς
    [gb]     = 0x03B2, // b:: β
    [gn]     = 0x03BD, // n:: ν
    [gm]     = 0x03BC, // m:: μ
                       // GREEKU
    [Rone]   = 0x2160, // 1:: Ⅰ
    [Rtwo]   = 0x2161, // 2:: Ⅱ
    [Rthree] = 0x2162, // 3:: Ⅲ
    [Rfour]  = 0x2163, // 4:: Ⅳ
    [Rfive]  = 0x2164, // 5:: Ⅴ
    [Rsix]   = 0x2165, // 6:: Ⅵ
    [Rseven] = 0x2166, // 7:: Ⅶ
    [Reight] = 0x2167, // 8:: Ⅷ
    [Rnine]  = 0x2168, // 9:: Ⅸ
    [Rten]   = 0x2169, // 0:: Ⅹ
    [Gq]     = 0x0398, // Q:: Θ
    [Gw]     = 0x03A9, // W:: Ω
    [Ge]     = 0x0395, // E:: Ε
    [Gr]     = 0x03A1, // R:: Ρ
    [Gt]     = 0x03A4, // T:: Τ
    [Gy]     = 0x03A8, // Y:: Ψ
    [Gu]     = 0x03A5, // U:: Υ
    [Gi]     = 0x0399, // I:: Ι
    [Go]     = 0x039F, // O:: Ο
    [Gp]     = 0x03A0, // P:: Π
    [Ga]     = 0x0391, // A:: Α
    [Gs]     = 0x03A3, // S:: Σ
    [Gd]     = 0x0394, // D:: Δ
    [Gf]     = 0x03A6, // F:: Φ
    [Gg]     = 0x0393, // G:: Γ
    [Gh]     = 0x0397, // H:: Η
    [Gj]     = 0x004A, // J:: J
    [Gk]     = 0x039A, // K:: Κ
    [Gl]     = 0x039B, // L:: Λ
    [Gz]     = 0x0396, // Z:: Ζ
    [Gx]     = 0x039E, // X:: Ξ
    [Gc]     = 0x03A7, // C:: Χ
    [Gv]     = 0x0056, // V:: V
    [Gb]     = 0x0392, // B:: Β
    [Gn]     = 0x039D, // N:: Ν
    [Gm]     = 0x039C, // M:: Μ

    [tone]   = 0x00B9, // 1:: ¹
    [ttwo]   = 0x00B2, // 2:: ²
    [tthree] = 0x00B3, // 3:: ³
    [tfour]  = 0x2074, // 4:: ⁴
    [tfive]  = 0x2075, // 5:: ⁵
    [tsix]   = 0x2076, // 6:: ⁶
    [tseven] = 0x2077, // 7:: ⁷
    [teight] = 0x2078, // 8:: ⁸
    [tnine]  = 0x2079, // 9:: ⁹
    [tzero]  = 0x2070, // 0 :: ⁰
    [tq]     = 0x06F9, // Q:: ۹ - superscript q doesn't exist.
    [tw]     = 0x02B7, // W:: ʷ
    [te]     = 0x1D49, // E:: ᵉ
    [tr]     = 0x02B3, // R:: ʳ
    [tt]     = 0x1D57, // T:: ᵗ
    [ty]     = 0x02B8, // Y:: ʸ
    [tu]     = 0x1D58, // U:: ᵘ
    [ti]     = 0x2071, // I:: ⁱ
    [to]     = 0x1D52, // O:: ᵒ
    [tp]     = 0x1D56, // P:: ᵖ
    [ta]     = 0x1D43, // A:: ᵃ
    [ts]     = 0x02E2, // S:: ˢ
    [td]     = 0x1D48, // D:: ᵈ
    [tf]     = 0x1DA0, // F:: ᶠ
    [tg]     = 0x1D4D, // G:: ᵍ
    [th]     = 0x02B0, // H:: ʰ
    [tj]     = 0x02B2, // J:: ʲ
    [tk]     = 0x1D4F, // K:: ᵏ
    [tl]     = 0x02E1, // L:: ˡ
    [tz]     = 0x1DBB, // Z:: ᶻ
    [tx]     = 0x02E3, // X:: ˣ
    [tc]     = 0x1D9C, // C:: ᶜ
    [tv]     = 0x1D5B, // V:: ᵛ
    [tb]     = 0x1D47, // B:: ᵇ
    [tn]     = 0x207F, // N:: ⁿ
    [tm]     = 0x1D50, // M:: ᵐ

    [fwone]   = 0xFF11, // 1:: １
    [fwtwo]   = 0xFF12, // 2:: ２
    [fwthree] = 0xFF13, // 3:: ３
    [fwfour]  = 0xFF14, // 4:: ４
    [fwfive]  = 0xFF15, // 5:: ５
    [fwsix]   = 0xFF16, // 6:: ６
    [fwseven] = 0xFF17, // 7:: ７
    [fweight] = 0xFF18, // 8:: ８
    [fwnine]  = 0xFF19, // 9:: ９
    [fwzero]  = 0xFF10, // 0 :: ０
    [fwq]     = 0xFF51, // Q:: ｑ
    [fww]     = 0xFF57, // W:: ｗ
    [fwe]     = 0xFF45, // E:: ｅ
    [fwr]     = 0xFF52, // R:: ｒ
    [fwt]     = 0xFF54, // T:: ｔ
    [fwy]     = 0xFF59, // Y:: ｙ
    [fwu]     = 0xFF55, // U:: ｕ
    [fwi]     = 0xFF49, // I:: ｉ
    [fwo]     = 0xFF4F, // O:: ｏ
    [fwp]     = 0xFF50, // P:: ｐ
    [fwa]     = 0xFF41, // A:: ａ
    [fws]     = 0xFF53, // S:: ｓ
    [fwd]     = 0xFF44, // D:: ｄ
    [fwf]     = 0xFF46, // F:: ｆ
    [fwg]     = 0xFF47, // G:: ｇ
    [fwh]     = 0xFF48, // H:: ｈ
    [fwj]     = 0xFF4A, // J:: ｊ
    [fwk]     = 0xFF4B, // K:: ｋ
    [fwl]     = 0xFF4C, // L:: ｌ
    [fwz]     = 0xFF5A, // Z:: ｚ
    [fwx]     = 0xFF58, // X:: ｘ
    [fwc]     = 0xFF43, // C:: ｃ
    [fwv]     = 0xFF56, // V:: ｖ
    [fwb]     = 0xFF42, // B:: ｂ
    [fwn]     = 0xFF4E, // N:: ｎ
    [fwm]     = 0xFF4D, // M:: ｍ
    // Full width caps + fractions, and a few extra symbols that lack a better place
    [Fwone]   = 0x00BC, // 1:: ¼
    [Fwtwo]   = 0x00BD, // 2:: ½
    [Fwthree] = 0x00BE, // 3:: ¾
    [Fwfour]  = 0x2153, // 4:: ⅓
    [Fwfive]  = 0x2154, // 5:: ⅔
    [Fwsix]   = 0x2155, // 6:: ⅕
    [Fwseven] = 0x215B, // 7:: ⅛
    [Fweight] = 0x00A0, // 8:: &nbsp
    [Fwnine]  = 0x203D, // 9:: ibang ‽
    [Fwzero]  = 0x2400, // 0 :: nullpic ␀
    [Fwq]     = 0xFF31, // Q:: Ｑ
    [Fww]     = 0xFF37, // W:: Ｗ
    [Fwe]     = 0xFF25, // E:: Ｅ
    [Fwr]     = 0xFF32, // R:: Ｒ
    [Fwt]     = 0xFF34, // T:: Ｔ
    [Fwy]     = 0xFF39, // Y:: Ｙ
    [Fwu]     = 0xFF35, // U:: Ｕ
    [Fwi]     = 0xFF29, // I:: Ｉ
    [Fwo]     = 0xFF2F, // O:: Ｏ
    [Fwp]     = 0xFF30, // P:: Ｐ
    [Fwa]     = 0xFF21, // A:: Ａ
    [Fws]     = 0xFF33, // S:: Ｓ
    [Fwd]     = 0xFF24, // D:: Ｄ
    [Fwf]     = 0xFF26, // F:: Ｆ
    [Fwg]     = 0xFF27, // G:: Ｇ
    [Fwh]     = 0xFF28, // H:: Ｈ
    [Fwj]     = 0xFF2A, // J:: Ｊ
    [Fwk]     = 0xFF2B, // K:: Ｋ
    [Fwl]     = 0xFF2C, // L:: Ｌ
    [Fwz]     = 0xFF3A, // Z:: Ｚ
    [Fwx]     = 0xFF38, // X:: Ｘ
    [Fwc]     = 0xFF23, // C:: Ｃ
    [Fwv]     = 0xFF36, // V:: Ｖ
    [Fwb]     = 0xFF22, // B:: Ｂ
    [Fwn]     = 0xFF2E, // N:: Ｎ
    [Fwm]     = 0xFF2D, // M:: Ｍ
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // clang-format off

[BASE] = LAYOUT_ergodox(  // layer 0 : default
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_GRV,
        KC_TAB, KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y, KC_BSLS,
        KC_EQL, KC_A, KC_O, KC_E, KC_U, KC_I,
        KC_LSPO, KC_SCLN, KC_Q, KC_J, KC_K, KC_X, KC_AMPR,
        OSL(FNLR), TT(GREL), TT(MATH), KC_UP, KC_DOWN,
        KC_LBRC, KC_HOME, KC_INS, KC_SPC, KC_LGUI, KC_DEL,

        OSL(FNLR), KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
        KC_PGUP, KC_F, KC_G, KC_C, KC_R, KC_L, KC_SLSH,
        KC_D, KC_H, KC_T, KC_N, KC_S, KC_MINS,
        KC_PGDN, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_RSPC,
        KC_LEFT, KC_RIGHT, KC_RALT, TT(SYMB), TT(QWER),
        KC_END, KC_RBRC, KC_PSCR, KC_RALT, KC_RCTL, KC_ENT
),

[FNLR] = LAYOUT_ergodox(
       // left hand
       UC_M_LN,   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_NO,
       UC_M_WC,KC_F11, KC_F12, KC_F13,KC_F14, KC_F15,  KC_NO,
       TO(TINY),KC_F21, KC_F22, KC_F23,KC_F24, MAGIC_TOGGLE_NKRO,
       TO(FULL),KC_PAUSE,KC_PSCR,KC_SLCK,KC_NO,KC_NO,KC_NO,
          EEP_RST,TO(BASE),TO(BASE),TO(BASE),TO(BASE),
                                       KC_NO,KC_NO,
                                               KC_NO,
                               KC_NO,KC_NO,KC_NO,
       // right hand
       TO(BASE), KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  UC_M_LN,
       KC_NO, KC_F16,  KC_F17,KC_F18,   KC_F19,  KC_F20,  UC_M_WI,
                KC_NO, KC_NO,   KC_NO,    KC_NO,    KC_NO, KC_NO,
       KC_NO, KC_NO, KC_NO,   KC_NO,    KC_NO,    KC_NO, KC_NO,
                         KC_NO,KC_NO,  KC_NO,    KC_NO,  KC_NO,
       KC_NO, KC_NO,
       KC_NO,
       KC_NO, KC_RCTL, KC_NO
),

[QWER] = LAYOUT_ergodox(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_GRV,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_BSLS,
        KC_AMPR, KC_A, KC_S, KC_D, KC_F, KC_G,
        KC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_QUOT,
        KC_BSLS, KC_LCTL, KC_LGUI, KC_RALT, KC_APP,
        KC_LBRC, KC_HOME, KC_PGUP, KC_SPC, KC_LSFT, KC_PGDN,

        OSL(FNLR), KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
        KC_MINS, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_SLSH,
        KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_ENT,
        KC_EQL, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC,
        KC_UP, KC_DOWN, KC_LEFT, KC_RIGHT, TO(BASE),
        KC_END, KC_INS, KC_DEL, KC_RGHT, KC_ENT, KC_SPC
),

[MATH] = LAYOUT_ergodox(
	KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_GRV,
	KC_TAB,	X(Mc),	X(Munion),	X(arwl),	X(or),	X(exists),	KC_BSLASH,
	X(arwr), X(root), X(and), X(imply), X(nexists), X(forall),
	KC_LSPO,	KC_SCLN,	X(intgrl),	X(Mn),	X(Mz),	X(member),	X(arwl),
	KC_MS_L, TO(BASE), TO(BASE), KC_INS, KC_DEL,
	KC_LBRC, KC_HOME, KC_UP, KC_SPC, KC_LGUI, KC_DOWN,

	TT(FNLR), KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
	KC_PGUP, X(plsminus),	X(infin),	X(neleof),	X(equiv),	X(Mq),	KC_EQL,
	X(sum),	X(emtyset),	X(porp),	X(suprsetof),	X(not),	X(neq),
	KC_PGDN,	X(subsetof),	X(intersection),	X(angl),	X(nmember),	X(eleof),	KC_RSPC,
	KC_RCTL, KC_RALT, KC_APP, TO(BASE), TO(BASE),
	KC_END, KC_RBRC, KC_LEFT, KC_RGHT, KC_ENT, KC_SPC
),

[SYMB] = LAYOUT_ergodox(
	X(Os), X(Oa), X(Ob), X(Oc), X(Od), X(Oe), X(mdot),
	X(boxemp), X(bbstr), X(bbrtr), X(bbrtl), X(bbstl), X(degree), X(brkdn),
	X(boxchk), X(bbmbl), X(bbml), X(bbmr), X(bbmbr), X(neteen),
	X(boxX), X(bbsbr), X(bbrbr), X(bbrbl), X(bbsbl), X(uxclm), X(brkup),
	X(floppy), TO(BASE), TO(BASE), X(arwu), X(arwd),
	X(fire), X(lshade), X(mshade), KC_SPC, X(OS), X(dshade),

	X(Ox), X(Of), X(Og), X(Oh), X(Oi), X(OA), X(OB),
	X(numero), X(trade), X(copy), X(cleft), X(cent), X(OED), X(OC),
	X(Agrave), X(gnd), X(sqr), X(sine), X(opt), X(OD),
	X(sect), X(Aacute), X(Acircm), X(Adiaer), X(Abreve), X(Atilde), X(OE),
	X(arwl), X(arwr), X(geq), X(leq), X(OF),
	X(rang), X(water), X(perup), X(perdn), X(baster), KC_ENT
),

[GREL] = LAYOUT_ergodox(
	KC_ESC, X(Rone), X(Rtwo), X(Rthree), X(Rfour), X(Rfive), KC_GRV,
	KC_TAB, KC_QUOT, KC_COMM, KC_DOT, X(gp), X(gy), KC_SLSH,
	KC_SLSH, X(ga), X(go), X(ge), X(gu), X(gi),
	MO(GREU), KC_SCLN, X(gq), X(gj), X(gk), X(gx), KC_AMPR,
	KC_MS_L, TO(BASE), TO(BASE), KC_INS, KC_DEL,
	KC_LBRC, KC_HOME, KC_UP, KC_SPC, KC_LGUI, KC_DOWN,

	TO(BASE), X(Rsix), X(Rseven), X(Reight), X(Rnine), X(Rten), KC_BSPC,
	KC_PGUP, X(gf), X(gg), X(gc), X(gr), X(gl), KC_EQL,
	X(gd), X(gh), X(gt), X(gn), X(gs), KC_MINS,
	KC_PGDN, X(gb), X(gm), X(gw), X(gv), X(gz), MO(GREU),
	KC_RCTL, KC_RALT, KC_APP, TO(BASE), TO(BASE),
	KC_END, KC_RBRC, KC_LEFT, KC_RGHT, KC_ENT, KC_SPC
),

[GREU] = LAYOUT_ergodox(
	KC_ESC, X(Rone), X(Rtwo), X(Rthree), X(Rfour), X(Rfive), KC_GRV,
	KC_TAB, KC_QUOT, KC_COMM, KC_DOT, X(Gp), X(Gy), KC_SLSH,
	KC_SLSH, X(Ga), X(Go), X(Ge), X(Gu), X(Gi),
	KC_TRNS, KC_SCLN, X(Gq), X(Gj), X(Gk), X(Gx), KC_AMPR,
	KC_MS_L, TO(BASE), TO(BASE), KC_INS, KC_DEL,
	KC_LBRC, KC_HOME, KC_UP, KC_SPC, KC_LGUI, KC_DOWN,

	TO(BASE), X(Rsix), X(Rseven), X(Reight), X(Rnine), X(Rten), KC_BSPC,
	KC_PGUP, X(Gf), X(Gg), X(Gc), X(Gr), X(Gl), KC_EQL,
	X(Gd), X(Gh), X(Gt), X(Gn), X(Gs), KC_MINS,
	KC_PGDN, X(Gb), X(Gm), X(Gw), X(Gv), X(Gz), KC_TRNS,
	KC_RCTL, KC_RALT, KC_APP, TO(BASE), TO(BASE),
	KC_END, KC_RBRC, KC_LEFT, KC_RGHT, KC_ENT, KC_SPC
),

[TINY] = LAYOUT_ergodox(
	KC_ESC, X(tone), X(ttwo), X(tthree), X(tfour), X(tfive), KC_GRV,
	KC_TAB, KC_QUOT, KC_COMM, KC_DOT, X(tp), X(ty), KC_SLSH,
	KC_SLSH, X(ta), X(to), X(te), X(tu), X(ti),
	KC_TRNS, KC_SCLN, X(tq), X(tj), X(tk), X(tx), KC_AMPR,
	KC_MS_L, TO(BASE), TO(BASE), KC_INS, KC_DEL,
	KC_LBRC, KC_HOME, KC_UP, KC_SPC, KC_LGUI, KC_DOWN,

	TO(BASE), X(tsix), X(tseven), X(teight), X(tnine), X(tzero), KC_BSPC,
	KC_PGUP, X(tf), X(tg), X(tc), X(tr), X(tl), KC_EQL,
	X(td), X(th), X(tt), X(tn), X(ts), KC_MINS,
	KC_PGDN, X(tb), X(tm), X(tw), X(tv), X(tz), KC_TRNS,
	KC_RCTL, KC_RALT, KC_APP, TO(BASE), TO(BASE),
	KC_END, KC_RBRC, KC_LEFT, KC_RGHT, KC_ENT, KC_SPC
),

[FULL] = LAYOUT_ergodox(
	KC_ESC, X(fwone), X(fwtwo), X(fwthree), X(fwfour), X(fwfive), KC_GRV,
	KC_TAB, KC_QUOT, KC_COMM, KC_DOT, X(fwp), X(fwy), KC_SLSH,
	KC_SLSH, X(fwa), X(fwo), X(fwe), X(fwu), X(fwi),
	MO(FULU), KC_SCLN, X(fwq), X(fwj), X(fwk), X(fwx), KC_AMPR,
	KC_MS_L, TO(BASE), TO(BASE), KC_INS, KC_DEL,
	KC_LBRC, KC_HOME, KC_UP, KC_SPC, KC_LGUI, KC_DOWN,

	TO(BASE), X(fwsix), X(fwseven), X(fweight), X(fwnine), X(fwzero), KC_BSPC,
	KC_PGUP, X(fwf), X(fwg), X(fwc), X(fwr), X(fwl), KC_EQL,
	X(fwd), X(fwh), X(fwt), X(fwn), X(fws), KC_MINS,
	KC_PGDN, X(fwb), X(fwm), X(fww), X(fwv), X(fwz), MO(FULU),
	KC_RCTL, KC_RALT, KC_APP, TO(BASE), TO(BASE),
	KC_END, KC_RBRC, KC_LEFT, KC_RGHT, KC_ENT, KC_SPC
),

[FULU] = LAYOUT_ergodox(
	KC_ESC, X(Fwone), X(Fwtwo), X(Fwthree), X(Fwfour), X(Fwfive), KC_GRV,
	KC_TAB, KC_QUOT, KC_COMM, KC_DOT, X(Fwp), X(Fwy), KC_SLSH,
	KC_SLSH, X(Fwa), X(Fwo), X(Fwe), X(Fwu), X(Fwi),
	KC_TRNS, KC_SCLN, X(Fwq), X(Fwj), X(Fwk), X(Fwx), KC_AMPR,
	KC_MS_L, TO(BASE), TO(BASE), KC_INS, KC_DEL,
	KC_LBRC, KC_HOME, KC_UP, KC_SPC, KC_LGUI, KC_DOWN,

	TO(BASE), X(Fwsix), X(Fwseven), X(Fweight), X(Fwnine), X(Fwzero), KC_BSPC,
	KC_PGUP, X(Fwf), X(Fwg), X(Fwc), X(Fwr), X(Fwl), KC_EQL,
	X(Fwd), X(Fwh), X(Fwt), X(Fwn), X(Fws), KC_MINS,
	KC_PGDN, X(Fwb), X(Fwm), X(Fww), X(Fwv), X(Fwz), KC_TRNS,
	KC_RCTL, KC_RALT, KC_APP, TO(BASE), TO(BASE),
	KC_END, KC_RBRC, KC_LEFT, KC_RGHT, KC_ENT, KC_SPC
),

    // clang-format on

};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void){

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    uint8_t layer = get_highest_layer(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
            // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }
};
