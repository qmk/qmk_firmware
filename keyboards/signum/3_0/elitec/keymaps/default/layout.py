from sortedcontainers import SortedDict

# Add all used Unicode symbols to this list.
# The key (e.g. "SNEK") is used in keymap.c for "enum", "unicode_map" and "keymaps", so it needs to be a valid C variable name.
# The key is also used in this file to define the layout, so use recognizeable names.
# The value (e.g. "0x1f40d") is used in keymap.c for "unicode_map" and to automatically generate the "ASCII"-art comments.
# When adding new Unicode names, use "0x1f40d" until you looked up the correct Unicode code point.
uc_dict = SortedDict({
    "SNEK": "0x1f40d", ## Error
    ## qwertz
    "ACUTE": "0x00b4",
    ## QWERTZ
    "INV_EXCL": "0x00a1",
    "INV_QST": "0x00bf",
    ## numpad
    "SUP1": "0x00b9",
    "SUP2": "0x00b2",
    "SUP3": "0x00b3",
    "SUP_MIN": "0x207b",
    "ROOT": "0x221a",
    "DEGREE": "0x00b0",
    "MINUTE": "0x02b9",
    "SECOND": "0x02ba",
    "CURRENCY": "0x00a4",
    "CENT": "0x00a2",
    "YEN": "0x00a5",
    "POUND": "0x00a3",
    "EURO": "0x20ac",
    "DIVISION": "0x00f7",
    "MICRO": "0x00b5",
    "OHM": "0x2126",
    "BITCOIN": "0x20bf",
    "SECTION": "0x00a7",
    ## NAV_TYPO
    "SQT1": "0x203a",
    "SQT2": "0x201a",
    "SQT3": "0x2018",
    "SQT4": "0x2019",
    "SQT5": "0x2039",
    "SUP_A": "0x00aa",
    "SUP_O": "0x00ba",
    "TMARK": "0x2122",
    "COPYR": "0x00a9",
    "REGTM": "0x00ae",
    "DOTS": "0x2026",
    "CROSS": "0x2020",
    "BULLET": "0x2022",
    "EMDASH": "0x2014",
    "PERMIL": "0x2030",
    "DQT1": "0x00bb",
    "DQT2": "0x201e",
    "DQT3": "0x201c",
    "DQT4": "0x201d",
    "DQT5": "0x00ab",
    ## lang
    "ae": "0x00e4",
    "oe": "0x00f6",
    "ue": "0x00fc",
    "sz": "0x00df",
    "n_tilde": "0x00f1",
    ## LANG
    "AE": "0x00c4",
    "OE": "0x00d6",
    "UE": "0x00dc",
    "SZ": "0x1e9e",
    "N_TILDE": "0x00d1",
    ## greek
    "alpha": "0x03b1",
    "beta": "0x03b2",
    "gamma": "0x03b3",
    "delta": "0x03b4",
    "epsilon": "0x03b5",
    "zeta": "0x03b6",
    "eta": "0x03b7",
    "theta": "0x03b8",
    "iota": "0x03b9",
    "kappa": "0x03ba",
    "lambda": "0x03bb",
    "my": "0x03bc",
    "ny": "0x03bd",
    "xi": "0x03be",
    "omikron": "0x03bf",
    "pi": "0x03c0",
    "rho": "0x03c1",
    "sigma": "0x03c3",
    "tau": "0x03c4",
    "ypsilon": "0x03c5",
    "phi": "0x03c6",
    "chi": "0x03c7",
    "psi": "0x03c8",
    "omega": "0x03c9",
    # variants
    "beta2": "0x03d0",
    "epsi2": "0x03f5",
    "theta2": "0x03d1",
    "kappa2": "0x03f0",
    "pi2": "0x03d6",
    "rho2": "0x03f1",
    "sigma2": "0x03c2",
    "sigma3": "0x03f2",
    "phi2": "0x03d5",
    # non-standard
    "digamma": "0x03dd",
    "stigma": "0x03db",
    "heta": "0x0371",
    "san": "0x03fb",
    "koppa": "0x03d9",
    "sampi": "0x0373",
    "scho": "0x03f8",
    ## GREEK
    "ALPHA": "0x0391",
    "BETA": "0x0392",
    "GAMMA": "0x0393",
    "DELTA": "0x0394",
    "EPSILON": "0x0395",
    "ZETA": "0x0396",
    "ETA": "0x0397",
    "THETA": "0x0398",
    "IOTA": "0x0399",
    "KAPPA": "0x039a",
    "LAMBDA": "0x039b",
    "MY": "0x039c",
    "NY": "0x039d",
    "XI": "0x039e",
    "OMIKRON": "0x039f",
    "PI": "0x03a0",
    "RHO": "0x03a1",
    "SIGMA": "0x03a3",
    "TAU": "0x03a4",
    "YPSILON": "0x03a5",
    "PHI": "0x03a6",
    "CHI": "0x03a7",
    "PSI": "0x03a8",
    "OMEGA": "0x03a9",
    # variants
    "YPSI2": "0x03d2",
    # non-standard
    "DIGAMMA": "0x03dc",
    "STIGMA": "0x03da",
    "HETA": "0x0370",
    "SAN": "0x03fa",
    "KOPPA": "0x03d8",
    "SAMPI": "0x0372",
    "SCHO": "0x03f7",
    ## symbol
    "SHOGI_WD": "0x26c9",
    "FLAG_W": "0x2690",
    "LETTER": "0x2709",
    "PHONE": "0x2706",
    "INFO": "0x1f6c8",
    "REWIND": "0x23ee",
    "PLAY": "0x23ef",
    "FORWARD": "0x23ed",
    "STOP": "0x25fc",
    "EJECT": "0x23cf",
    "SHOGI_W": "0x2616",
    "FEMALE": "0x2640",
    "MALE": "0x2642",
    "NO": "0x2717",
    "YES": "0x2713",
    "FLAT": "0x266d",
    "NATURAL": "0x266e",
    "SHARP": "0x266f",
    "COMMON_T": "0x1d134",
    "ALLA_BR": "0x1d135",
    "PAWN_W": "0x2659",
    "DIAMS_W": "0x2662",
    "HEARTS_W": "0x2661",
    "SPADES_W": "0x2664",
    "CLUBS_W": "0x2667",
    "WHOLE_N": "0x1d15d",
    "HALF_N": "0x1d15e",
    "QUART_N": "0x1d15f",
    "EIGHTH_N": "0x1d160",
    "SIXT_N": "0x1d161",
    "ROOK_W": "0x2656",
    "KNIGHT_W": "0x2658",
    "BISHOP_W": "0x2657",
    "QUEEN_W": "0x2655",
    "KING_W": "0x2654",
    "C_CLEF": "0x1d121",
    "G_CLEF": "0x1d11e",
    "F_CLEF": "0x1d122",
    "PEDAL": "0x1d1ae",
    "PEDAL_UP": "0x1d1af",
    ## SYMBOL
    "SHOGI_BD": "0x26ca",
    "FLAG_B": "0x2691",
    "SPEAKER_UP": "0x1f50a",
    "SPEAKER_TG": "0x1f507",
    "SPEAKER_DN": "0x1f509",
    "SHOGI_B": "0x2617",
    "KEY": "0x1f511",
    "LOCK": "0x1f512",
    "LOCK_OPEN": "0x1f513",
    "STAFF": "0x1d11a",
    "BARLINE": "0x1d100",
    "BARLINE_D": "0x1d101",
    "BARLINE_FIN": "0x1d102",
    "CODA": "0x1d10c",
    "PAWN_B": "0x265f",
    "DIAMS_B": "0x2666",
    "HEARTS_B": "0x2665",
    "SPADES_B": "0x2660",
    "CLUBS_B": "0x2663",
    "WHOLE_P": "0x1d13b",
    "HALF_P": "0x1d13c",
    "QUART_P": "0x1d13d",
    "EIGHTH_P": "0x1d13e",
    "SIXT_P": "0x1d13f",
    "ROOK_B": "0x265c",
    "KNIGHT_B": "0x265e",
    "BISHOP_B": "0x265d",
    "QUEEN_B": "0x265b",
    "KING_B": "0x265a",
    "REPEAT_S": "0x1d106",
    "REPEAT_E": "0x1d107",
    "SEGNO": "0x1d10b",
    "DALSEGNO": "0x1d109",
    "DACAPO": "0x1d10a",
    ## math
    "EXISTS": "0x2203",
    "FORALL": "0x2200",
    "EQUIV": "0x2261",
    "CORRESP": "0x2259",
    "INEQUAL": "0x2260",
    "DEFINE": "0x2254",
    "TO": "0x27f6",
    "MAPSTO": "0x27fc",
    "SETMINUS": "0x2216",
    "QED": "0x220e",
    "OR_": "0x22c1",
    "AND_": "0x22c0",
    "OR": "0x2228",
    "AND": "0x2227",
    "NOT": "0x00ac",
    "BICOND": "0x21d4",
    "IMPL_REV": "0x21d0",
    "IMPL": "0x21d2",
    "TOP": "0x22a4",
    "BOTTOM": "0x22a5",
    "SUM_": "0x2211",
    "PROD_": "0x220f",
    "MDOT": "0x22c5",
    "NOTIN": "0x2209",
    "IN": "0x2208",
    "LS_EQ": "0x2264",
    "GR_EQ": "0x2265",
    "INFTY": "0x221e",
    "UNION_": "0x22c3",
    "INTERS_": "0x22c2",
    "UNION": "0x222a",
    "INTERS": "0x2229",
    "NOTSUBS": "0x2288",
    "PR_SUBSET": "0x2282",
    "SUBSET": "0x2286",
    "SUBSET_REV": "0x2287",
    "EMPTYSET": "0x2205",
    ## MATHSCRIPT
    "LEFT_CEIL": "0x2308",
    "REAL_P": "0x211c",
    "NABLA": "0x2207",
    "RIGHT_CEIL": "0x2309",
    "LEFT_FLOOR": "0x230a",
    "BRA": "0x27e8",
    "IMAG_P": "0x2111",
    "KET": "0x27e9",
    "RIGHT_FLOOR": "0x230b",
    "Q_SET": "0x211a",
    "e_FUN": "0x0065",
    "R_SET": "0x211d",
    "Z_SET": "0x2124",
    "U_SET": "0x1d54c",
    "i_UNIT": "0x0069",
    "BIG_O": "0x1d4aa",
    "POWERSET": "0x1d4ab",
    "A_SET": "0x1d538",
    "INTEGRAL": "0x222b",
    "PARTIAL": "0x2202",
    "F_SET": "0x1d53d",
    "H_SET": "0x210d",
    "K_SET": "0x1d542",
    "LENGTH": "0x2113",
    "ALEPH": "0x2135",
    "BETH": "0x2136",
    "C_SET": "0x2102",
    "B_SET": "0x1d539",
    "N_SET": "0x2115",
    "INDICATOR": "0x1d7cf",
    "FOURIER": "0x2131",
    "HAMILTON": "0x210b",
    "LAPLACE": "0x2112",
    ## MATHEXT
    "RIGHT_TACK": "0x22a2",
    "MODELS": "0x22a7",
    "AB_VEC": "0x20d7",
    "AB_LINE": "0x0305",
    "AB_ARC": "0x0361",
    "LESS_LESS": "0x226a",
    "PRED": "0x227a",
    "EMBED": "0x21aa",
    "SUCC": "0x227b",
    "GREAT_GREAT": "0x226b",
    "TRIANGLE": "0x25b3",
    "SQUARE": "0x25a1",
    "CIRCLE": "0x25cb",
    "DOT_OP": "0x2299",
    "PLUS_OP": "0x2295",
    "MINUS_OP": "0x2296",
    "ROUGHLY": "0x2248",
    "ISOMORPH": "0x2245",
    "LTIMES": "0x22c9",
    "RTIMES": "0x22ca",
    "BOWTIE": "0x22c8",
    "M_ANGLE": "0x2221",
    "ANGLE": "0x2220",
    "CIRC_MID": "0x2218",
    "AST_MID": "0x2217",
    "TIMES": "0x00d7",
    "PLUS_MINUS": "0x00b1",
    "MINUS_PLUS": "0x2213",
    "LEFT_OUTER": "0x27d5",
    "RIGHT_OUTER": "0x27d6",
    "FULL_OUTER": "0x27d7",
    "SQ_LS": "0x228f",
    "SQ_LS_EQ": "0x2291",
    "PROP_TO": "0x221d",
    "PARALLEL": "0x2225",
    "NOT_PARA": "0x2226",
    "TIMES_OP": "0x2297",
    "NOT_DIV": "0x2224"
})

# Add all used Keycodes to this list.
# The key (e.g. "a") is used in keymap.c to automatically generate the comments. The first 7 chars will show as a keycap legend.
qmk_dict = {
    # test cases (These are handled in generate_km.py within toKC() and toLgd(), so these definitions will be ignored.
    # If you find "BAD" in your keymaps, then something went wrong.)
    "a": "BAD", "A": "BAD", "0": "BAD",
    # Basic Keycodes
    "XXX": "XXXXXXX", "": "KC_TRNS",
    "!": "S(KC_1)", "@": "S(KC_2)", "#": "S(KC_3)", "$": "S(KC_4)", "%": "S(KC_5)",
    "^": "S(KC_6)", "&": "S(KC_7)", "*": "S(KC_8)", "(": "S(KC_9)", ")": "S(KC_0)",
    "Enter": "KC_ENT", "Esc": "KC_ESC", "BSpace": "KC_BSPC", "Tab": "KC_TAB",
    "Space": "KC_SPC", "-": "KC_MINS", "_": "S(KC_MINS)", "=": "KC_EQL",
    "+": "S(KC_EQL)", "[": "KC_LBRC", "{": "S(KC_LBRC)", "]": "KC_RBRC",
    "}": "S(KC_RBRC)", "\\": "KC_BSLS", "|": "S(KC_BSLS)", ";": "KC_SCLN",
    ":": "S(KC_SCLN)", "'": "KC_QUOT", "\"": "S(KC_QUOT)", "`": "KC_GRV",
    "~": "S(KC_GRV)", ",": "KC_COMM", "<": "S(KC_COMM)", ".": "KC_DOT",
    ">": "S(KC_DOT)", "/": "KC_SLSH", "?": "S(KC_SLSH)", "Caps": "KC_CAPS",
    "Pr Scr": "KC_PSCR", "Scr Lck": "KC_SLCK", "Pause": "KC_BRK", "Insert": "KC_INS", "SInsert": "SFT_T(KC_INS)",
    "Home": "KC_HOME", "Pg Up": "KC_PGUP", "Del": "KC_DEL", "End": "KC_END",
    "Pg Down": "KC_PGDN", "> Arrow": "KC_RIGHT", "< Arrow": "KC_LEFT",
    "v Arrow": "KC_DOWN", "^ Arrow": "KC_UP",
    # Keypad keycodes missing
    "App": "KC_APP", "Menu": "KC_MENU",
    # Command keycodes missing (Execute, Help, ..., Find)
    # Basic Keycodes missing from Print Screen onwards, included as fallback
    # random Keycodes
    "RGui": "KC_RGUI", "LGui": "KC_LGUI", "LAlt": "KC_LALT", "RAlt": "KC_RALT", "LShift": "KC_LSFT", "LCtrl": "KC_LCTRL", "RCtrl": "KC_RCTRL",
    "LShift(": "KC_LSPO", "RShift)": "KC_RSPC",
    "L1_ENT": "LT(1, KC_ENT)", "LT6_SPC": "LT(6, KC_SPC)",
    "CPg Dn": "CTL_T(KC_PGDN)", "CPg Up": "CTL_T(KC_PGUP)",
    "S_Enter": "S(KC_ENT)", "S_Tab": "S(KC_TAB)", "Compose": "KC_ALGR",
    "RShift": "KC_RSFT",
    "Vol 0": "KC_MUTE", "Vol +": "KC_VOLU", "Vol -": "KC_VOLD",
    ">>|": "KC_MNXT", "|<<": "KC_MPRV", "play/ps": "KC_MPLY",
    "Bri +": "KC_BRIU", "Bri -": "KC_BRID",
    # Quantum Keycodes
    "_reset": "RESET", "_debug": "DEBUG", "_eep_re": "EEP_RST",
    # Audio Keys missing
    # Backlighting
    "Led 0": "BL_TOGG", "Led +": "BL_INC", "Led -": "BL_DEC", "Led ~": "BL_BRTG",
    # Bootmagic missing
    # Bluetooth
    "OUT_AUTO": "OUT_AUTO", "OUT_USB": "OUT_USB", "OUT_BT": "OUT_BT",
    # Layer Switching missing, Lx -> MO(x), Tx -> TG(x)
    "qwertz": "DF(0)", "neo": "DF(2)",
    # Mouse Keys
    "^ Mouse": "KC_MS_U", "v Mouse": "KC_MS_D", "< Mouse": "KC_MS_L",
    "> Mouse": "KC_MS_R", "Mouse 1": "KC_BTN1", "Mouse 2": "KC_BTN2",
    "Mouse 3": "KC_BTN3", "Mouse 4": "KC_BTN4", "Mouse 5": "KC_BTN5",
    "^ Wheel": "KC_WH_U", "v Wheel": "KC_WH_D", "< Wheel": "KC_WH_L",
    "> Wheel": "KC_WH_R", "acc0": "KC_ACL0", "acc1": "KC_ACL1",
    "acc2": "KC_ACL2",
    # Modifiers missinng, add entry for each specific application
    # Mod-Tap Keys missing, add entry for each specific application
    "_Sh_swp": "LSFT_T(SH_TG)",
    # RGB Lighting missing
    # RGB Matrix Lighting missing
    # Thermal Printer missing
    # US ANSI Shifted Symbols done via S(), don't add KC_entries
    # One Shot Keys missing
    # Swap Hands
    "_sp_swp": "SHT(KC_SPC)",
    # Unicode support (via X()) included implicitly
    # Switching Unicode Input Modes
    "UC_win": "UC_M_WC", "UC_lnx": "UC_M_LN", "UC_osx": "UC_M_OS",

    # custom keys
    "altF4": "LALT(KC_F4)",
    "Undo": "LCTL(KC_Z)", "Cut": "LCTL(KC_X)", "Copy": "LCTL(KC_C)", "Paste": "LCTL(KC_V)",
    "< Tab": "LCTL(S(KC_TAB))", "> Tab": "LCTL(KC_TAB)",
    "Tab x": "LCTL(KC_W)", "Tab n": "LCTL(KC_T)",
    "Gui Tab":  "LGUI_T(KC_TAB)", "< Gui":  "LGUI_T(KC_LEFT)", "< Gui":  "LGUI_T(KC_RIGHT)",
    "C+A+Del": "LCTL(LALT(KC_DEL))", "Mic 0": "LCTL(KC_M)",
    "Power": "KC_PWR", "Sleep": "KC_SLEP",

    # macros
    "Macro 1": "KC_1", "Macro 2": "KC_2", "Macro 3": "KC_3", "Macro 4": "KC_4", "Macro 5": "KC_5",

    # custom layers
    "GREEK": "GREEK",
    "SYMBOL": "SYMBOL",
    "MATH": "MATH",
    "GAME": "GAME",
    "MOUSE": "MOUSE",
    "NEO": "TG(2)"
}

# These keys are repeated in all layers.
# Generate a keymap.c with the python script and refer to the "ASCII"-art comments, to see which positions this concerns.
# If you want to put different keycodes in these positions for different layers, you need to modify the python script by yourself.
static = ["NEO", "GREEK", "GREEK", "GREEK", "GREEK", "MOUSE"]

# mutex_layers = {"GREEK": 8, "GAME": 10, "MOUSE": 11}
# layer_graph = ...

# 0
qwerty = [
    ["Tab",     "q",    "w",       "e",       "r",       "t",       "y",       "u",       "i",       "o",       "p",       "["],
    ["LCtrl",   "a",    "s",       "d",       "f",       "g",       "h",       "j",       "k",       "l",       ";",       "'"],
    ["LShift(", "z",    "x",       "c",       "v",       "b",       "n",       "m",       ",",       ".",       "/",       "RShift)"],
    ["MO2",     "LGui", "LAlt",    "TT2",     "LT6_SPC", "TT4",     "Enter",   "Space",   "TT2",     "RAlt",    "RGui",    "RCtrl"],
    ]

# 1
colemak = [
    ["Tab",     "q",    "w",       "f",       "p",       "g",       "j",       "l",       "u",       "y",       ";",       "["],
    ["LCtrl",   "a",    "r",       "s",       "t",       "d",       "h",       "n",       "e",       "i",       "o",       "'"],
    ["LShift(", "z",    "x",       "c",       "v",       "b",       "k",       "m",       ",",       ".",       "/",       "RShift)"],
    ["MO2",     "LGui", "LAlt",    "TT2",     "LT6_SPC", "TT4",     "Enter",   "Space",   "TT2",     "RAlt",    "RGui",    "RCtrl"],
    ]

# 2
numpad = [
    ["`",       "1",    "2",       "3",       "4",       "5",       "6",       "7",       "8",       "9",       "0",       "]"],
    ["",        "DF0",  "DF1",     "XXX",     "XXX",     "MO3",     "4",       "4",       "5",       "6",       "-",       "="],
    ["",        "MO5",  "XXX",     "XXX",     "XXX",     "XXX",     "1",       "1",       "2",       "3",       "\\",      ""],
    ["TG2",     "",     "",        "",        "",        "",        "",        "",        "0",       "",        "",        ""],
    ]

# 3
fpad = [
    ["",        "F1",   "F2",      "F3",      "F4",      "F5",      "F6",      "F7",      "F8",      "F9",      "F10",     "XXX"],
    ["",        "XXX",  "XXX",     "XXX",     "XXX",     "MO3",     "F4",      "F4",      "F5",      "F6",      "XXX",     "XXX"],
    ["",        "XXX",  "XXX",     "XXX",     "XXX",     "XXX",     "F1",      "F1",      "F2",      "F3",      "XXX",     ""],
    ["TG3",     "",     "",        "",        "",        "",        "F10",     "F11",     "F12",     "",        "",        ""],
    ]

# 4
movement = [
    ["",        "Esc",  "Tab x",   "Tab n",   "CPg Dn",  "CPg Dn",  "Pg Down", "Home",    "^ Arrow", "Insert",  "SInsert", "Esc"],
    ["",        "Caps", "< Gui",   "Gui Tab", "> Gui",   "> Gui",   "< Arrow", "< Arrow", "v Arrow", "> Arrow", "End",     "Pr Scr"],
    ["",        "XXX",  "XXX",     "XXX",     "CPg Up",  "CPg Up",  "Pg Up",   "XXX",     "v Arrow", "XXX",     "App",     ""],
    ["TG4",     "",     "",        "",        "",        "",        "",        "",        "",        "",        "",        ""],
    ]

# 5
media = [
    ["",        "XXX",  "play/ps", "Vol +",   "Vol +",   "XXX",     "XXX",     "XXX",     "XXX",     "XXX",     "_reset",  "Power"],
    ["",        "XXX",  "|<<",     "Vol 0",   ">>|",     "XXX",     "XXX",     "XXX",     "XXX",     "XXX",     "XXX",     "Sleep"],
    ["",        "XXX",  "XXX",     "Vol -",   "Vol -",   "XXX",     "XXX",     "XXX",     "XXX",     "XXX",     "XXX",     "XXX"],
    ["TG5",     "",     "",        "",        "",        "",        "",        "",        "",        "",        "",        ""],
    ]

# 6
mouse = [
    ["",        "acc1", "XXX",     "XXX",     "XXX",     "XXX",     "^ Wheel", "< Wheel", "^ Mouse", "> Wheel", "XXX",     "XXX"],
    ["",        "acc2", "Mouse 3", "Mouse 2", "Mouse 1", "Mouse 1", "< Mouse", "< Mouse", "v Mouse", "> Mouse", "XXX",     "XXX"],
    ["",        "acc0", "XXX",     "XXX",     "XXX",     "XXX",     "v Wheel", "XXX",     "v Mouse", "XXX",     "XXX",     ""],
    ["TG6",     "",     "",        "",        "",        "",        "",        "",        "",        "",        "",        ""],
    ]

layers = [
    qwerty,
    colemak,
    numpad,
    fpad,
    movement,
    media,
    mouse
    ]
