from sortedcontainers import SortedDict

# === TODO ===
# -replace NEO with new layout optimized for German, English, Spanish
# -optimize punctuation layer
# -block or reuse Calc-, L3- and L4-modifiers, when one of them is pressed
# -is it better to put Shift in the middle position?
# -mouse layer "Beg" = "Begin", what does it do?
# -should Ctrl and Alt be switched?
# -add macro rec
# -complete greek layer
# -complete lang layer
# -maybe extend math layer with latin and greek alphabet
#
#
# === optional ===
# Cyrilic: ???
#
# === missing ===
# Troy's 40%:     special layer (Record Macro, Lock GUI+L) & mouse mode (Print out layers, Config console, Boot), context menu

# Add all used Unicode symbols to this list.
# The key (e.g. "SNEK") is used in keymap.c for "enum", "unicode_map" and "keymaps", so it needs to be a valid C variable name.
# The key is also used in this file to define the layout, so use recognizeable names.
# The value (e.g. "0x1f40d") is used in keymap.c for "unicode_map" and to automatically generate the comments.
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
# The key is also used in this file to define the layout, so use recognizeable names.
# The value (e.g. "0x1f40d") is used in keymap.c for "unicode_map" and to automatically generate the comments.
# When adding new Unicode names, use "0x1f40d" until you looked up the correct Unicode code point.
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
    "Pr Scr": "KC_PSCR", "Scr Lck": "KC_SLCK", "Pause": "KC_BRK", "Insert": "KC_INS",
    "Home": "KC_HOME", "Pg Up": "KC_PGUP", "Del": "KC_DEL", "End": "KC_END",
    "Pg Down": "KC_PGDN", "> Arrow": "KC_RIGHT", "< Arrow": "KC_LEFT",
    "v Arrow": "KC_DOWN", "^ Arrow": "KC_UP",
    # Keypad keycodes missing
    "App": "KC_APP", "Menu": "KC_MENU",
    # Command keycodes missing (Execute, Help, ..., Find)
    # Basic Keycodes missing from Print Screen onwards, included as fallback
    # random Keycodes
    "Gui": "KC_LGUI", "Alt": "KC_LALT", "Shift": "KC_LSFT", "Ctrl": "KC_LCTRL",
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

    # custom keys
    "altF4": "LALT(KC_F4)",
    "Undo": "LCTL(KC_Z)", "Cut": "LCTL(KC_X)", "Copy": "LCTL(KC_C)", "Paste": "LCTL(KC_V)",
    "< Tab": "LCTL(S(KC_TAB))", "> Tab": "LCTL(KC_TAB)",
    "C+A+Del": "LCTL(LALT(KC_DEL))", "Mic 0": "LCTL(KC_M)",

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

static = ["NEO", "GAME", "GREEK", "MATH", "SYMBOL", "MOUSE"]

# mutex_layers = {"GREEK": 12, "SYMBOL": 16, "MATH": 18, "GAME": 23, "MOUSE": 24}
# layer_graph = ...

# 0
qwertz = [["Esc", "!", "@", "#", "$", "?",                  "{", "(", "ACUTE", ")", "}", "Del"],
        ["Tab", "q", "w", "e", "r", "t",                  "z", "u", "i", "o", "p", "Enter"],
        ["L1",  "a", "s", "d", "f", "g",                  "h", "j", "k", "l", "'", "L1"],
        ["Gui", "y", "x", "c", "v", "b",                  "n", "m", ",", ".", "-", "BSpace"],
                               ["L6", "L4", "Ctrl",   "Alt", "Space", "L8"]]

# 1
QWERTZ = [["Esc", "INV_EXCL", "&", "/", "%", "INV_QST",                  "<", "[", "_", "]", ">", "Del"],
        ["S_Tab", "Q", "W", "E", "R", "T",                  "Z", "U", "I", "O", "P", "S_Enter"],
        ["L1",  "A", "S", "D", "F", "G",                  "H", "J", "K", "L", "\"", "L1"],
        ["T1", "Y", "X", "C", "V", "B",                  "N", "M", ";", ":", "=", "BSpace"],
                               ["L6", "L4", "Ctrl",   "Alt", "Space", "L8"]]

# 2
neo = [["Esc", "!", "@", "#", "$", "?",                  "{", "(", "ACUTE", ")", "}", "Del"],
        ["Tab", "x", "v", "l", "c", "w",                  "k", "h", "g", "f", "q", "Enter"],
        ["L3",  "u", "i", "a", "e", "o",                  "s", "n", "r", "t", "d", "L3"],
        ["Gui", "'", "j", "y", "p", "z",                  "b", "m", ",", ".", "-", "BSpace"],
                               ["L6", "L4", "Ctrl",   "Alt", "Space", "L8"]]

# 3
NEO = [["Esc", "INV_EXCL", "&", "/", "%", "INV_QST",                  "<", "[", "_", "]", ">", "Del"],
        ["S_Tab", "X", "V", "L", "C", "W",                  "K", "H", "G", "F", "Q", "S_Enter"],
        ["L3",  "U", "I", "A", "E", "O",                  "S", "N", "R", "T", "D", "L3"],
        ["T3", "\"", "J", "Y", "P", "Z",                  "B", "M", ";", ":", "=", "BSpace"],
                               ["L6", "L4", "Ctrl",   "Alt", "Space", "L8"]]

# 4
numpad = [["Esc", "SUP1", "SUP2", "SUP3", "SUP_MIN", "ROOT",                  "[", "(", "%", ")", "]", "Del"],
        ["Tab", "CURRENCY", ":", "DEGREE", "MINUTE", "SECOND",                  "*", "7", "8", "9", "/", "Enter"],
        ["L1",  "CENT", "YEN", "POUND", "EURO", "$",                  "+", "4", "5", "6", "-", "L1"],
        ["T4", "DIVISION", "MICRO", "OHM", "BITCOIN", "SECTION",                  "^", "1", "2", "3", "\"", "BSpace"],
                               ["XXX", "L4", "Ctrl",   ".", "0", ","]]

# 5
FN_MEDIA = [["Esc", "XXX", "XXX", "XXX", "XXX", "XXX",                  "XXX", "XXX", "UC_win", "UC_mac", "UC_lnx", "Del"],
        ["Tab", "F1", "F2", "F3", "F4", "altF4",                  "Led +", "Led 0", "Led -", "Led ~", "XXX", "Enter"],
        ["L1",  "F5", "F6", "F7", "F8", "XXX",                  "Vol +", "Vol 0", "Vol -", "Mic 0", "XXX", "L1"],
        ["T5", "F9", "F10", "F11", "F12", "XXX",                  "|<<", "play/ps", ">>|", "XXX", "XXX", "BSpace"],
                               ["XXX", "L4", "Ctrl",   "Alt", "Space", "XXX"]]

# 6
punct = [["Esc", "XXX", "XXX", "|", "XXX", "XXX",                  "XXX", "XXX", ":", "XXX", "XXX", "Del"],
        ["Tab", "!", "@", "#", "$", "?",                  "{", "(", ",", ")", "}", "Enter"],
        ["L1",  "'", "*", "\\", "\"", "=",                  "+", ".", "_", ";", "-", "L1"],
        ["T6", "~", "&", "/", "%", "^",                  "<", "[", "SECTION", "]", ">", "BSpace"],
                               ["L6", "XXX", "Ctrl",   "Alt", "Space", "XXX"]]

# 7
NAV_TYPO = [["Esc", "SQT1", "SQT2", "SQT3", "SQT4", "SQT5",                  "Insert", "Scr Lck", "Pr Scr", "Pause", "C+A+Del", "Del"],
        ["Tab", "SUP_A", "SUP_O", "TMARK", "COPYR", "REGTM",                  "Pg Up", "Home", "^ Arrow", "End", "App", "Enter"],
        ["L1",  "DOTS", "CROSS", "BULLET", "EMDASH", "PERMIL",                  "Pg Down", "< Arrow", "v Arrow", "> Arrow", "Menu", "L1"],
        ["T7", "DQT1", "DQT2", "DQT3", "DQT4", "DQT5",                  "Macro 1", "Macro 2", "Macro 3", "Macro 4", "Macro 5", "BSpace"],
                               ["L6", "XXX", "Ctrl",   "Alt", "Space", "XXX"]]

# 8
lang = [["Esc", "XXX", "XXX", "XXX", "XXX", "XXX",                  "XXX", "XXX", "XXX", "XXX", "XXX", "Del"],
        ["Compose", "XXX", "XXX", "XXX", "XXX", "XXX",                  "XXX", "ue", "XXX", "oe", "XXX", "Enter"],
        ["L1",  "ae", "sz", "XXX", "XXX", "XXX",                  "XXX", "XXX", "XXX", "XXX", "XXX", "L1"],
        ["T8", "XXX", "XXX", "XXX", "XXX", "XXX",                  "n_tilde", "XXX", "XXX", "XXX", "XXX", "BSpace"],
                               ["XXX", "XXX", "Ctrl",   "Alt", "Space", "L8"]]

# 9
LANG = [["Esc", "XXX", "XXX", "XXX", "XXX", "XXX",                  "XXX", "XXX", "XXX", "XXX", "XXX", "Del"],
        ["Compose", "XXX", "XXX", "XXX", "XXX", "XXX",                  "XXX", "UE", "XXX", "OE", "XXX", "Enter"],
        ["L1",  "AE", "SZ", "XXX", "XXX", "XXX",                  "XXX", "XXX", "XXX", "XXX", "XXX", "L1"],
        ["T9", "XXX", "XXX", "XXX", "XXX", "XXX",                  "N_TILDE", "XXX", "XXX", "XXX", "XXX", "BSpace"],
                               ["XXX", "XXX", "Ctrl",   "Alt", "Space", "L8"]]

# 10
neo_lang = [["Esc", "XXX", "XXX", "XXX", "XXX", "XXX",                  "XXX", "XXX", "XXX", "XXX", "XXX", "Del"],
        ["Compose", "XXX", "XXX", "XXX", "XXX", "XXX",                  "XXX", "XXX", "XXX", "XXX", "XXX", "Enter"],
        ["L1",  "ue", "XXX", "ae", "XXX", "oe",                  "sz", "n_tilde", "XXX", "XXX", "XXX", "L1"],
        ["T8", "XXX", "XXX", "XXX", "XXX", "XXX",                  "XXX", "XXX", "XXX", "XXX", "XXX", "BSpace"],
                               ["XXX", "XXX", "Ctrl",   "Alt", "Space", "L8"]]

# 11
NEO_LANG = [["Esc", "XXX", "XXX", "XXX", "XXX", "XXX",                  "XXX", "XXX", "XXX", "XXX", "XXX", "Del"],
        ["Compose", "XXX", "XXX", "XXX", "XXX", "XXX",                  "XXX", "XXX", "XXX", "XXX", "XXX", "Enter"],
        ["L1",  "UE", "XXX", "AE", "XXX", "OE",                  "SZ", "N_TILDE", "XXX", "XXX", "XXX", "L1"],
        ["T9", "XXX", "XXX", "XXX", "XXX", "XXX",                  "XXX", "XXX", "XXX", "XXX", "XXX", "BSpace"],
                               ["XXX", "XXX", "Ctrl",   "Alt", "Space", "L8"]]

# 12 - missing: beta2, epsilon2, pi2
greek = [["Esc", "XXX", "digamma", "stigma", "heta", "san",                  "kappa2", "koppa", "sampi", "scho", "XXX", "Del"],
        ["Tab", "xi", "sigma2", "lambda", "chi", "omega",                  "kappa", "psi", "gamma", "phi", "phi2", "Enter"],
        ["L1",  "ypsilon", "iota", "alpha", "epsilon", "omikron",                  "sigma", "ny", "rho", "tau", "delta", "L1"],
        ["Gui", "XXX", "kappa2", "eta", "pi", "zeta",                  "beta", "my", "rho2", "theta", "theta2", "BSpace"],
                               ["L6", "L4", "Alt",   "Ctrl", "Space", "L8"]]

# 13 - missing: YPSILON2
GREEK = [["Esc", "XXX", "DIGAMMA", "STIGMA", "HETA", "SAN",                  "XXX", "KOPPA", "SAMPI", "SCHO", "XXX", "Del"],
        ["Tab", "XI", "XXX", "LAMBDA", "CHI", "OMEGA",                  "KAPPA", "PSI", "GAMMA", "PHI", "XXX", "Enter"],
        ["L1",  "YPSILON", "IOTA", "ALPHA", "EPSILON", "OMIKRON",                  "SIGMA", "NY", "RHO", "TAU", "DELTA", "L1"],
        ["Gui", "XXX", "XXX", "ETA", "PI", "ZETA",                  "BETA", "MY", "XXX", "THETA", "XXX", "BSpace"],
                               ["L6", "L4", "Alt",   "Ctrl", "Space", "L8"]]

# 14 - missing: beta2, epsilon2, pi2
neo_greek = [["Esc", "XXX", "digamma", "stigma", "heta", "san",                  "kappa2", "koppa", "sampi", "scho", "XXX", "Del"],
        ["Tab", "xi", "sigma2", "lambda", "chi", "omega",                  "kappa", "psi", "gamma", "phi", "phi2", "Enter"],
        ["L1",  "ypsilon", "iota", "alpha", "epsilon", "omikron",                  "sigma", "ny", "rho", "tau", "delta", "L1"],
        ["Gui", "XXX", "kappa2", "eta", "pi", "zeta",                  "beta", "my", "rho2", "theta", "theta2", "BSpace"],
                               ["L6", "L4", "Alt",   "Ctrl", "Space", "L8"]]

# 15 - missing: YPSILON2
NEO_GREEK = [["Esc", "XXX", "DIGAMMA", "STIGMA", "HETA", "SAN",                  "XXX", "KOPPA", "SAMPI", "SCHO", "XXX", "Del"],
        ["Tab", "XI", "XXX", "LAMBDA", "CHI", "OMEGA",                  "KAPPA", "PSI", "GAMMA", "PHI", "XXX", "Enter"],
        ["L1",  "YPSILON", "IOTA", "ALPHA", "EPSILON", "OMIKRON",                  "SIGMA", "NY", "RHO", "TAU", "DELTA", "L1"],
        ["Gui", "XXX", "XXX", "ETA", "PI", "ZETA",                  "BETA", "MY", "XXX", "THETA", "XXX", "BSpace"],
                               ["L6", "L4", "Alt",   "Ctrl", "Space", "L8"]]

# 16
symbol = [["Esc", "SHOGI_WD", "FLAG_W", "LETTER", "PHONE", "INFO",                  "REWIND", "PLAY", "FORWARD", "STOP", "EJECT", "Del"],
        ["Tab", "SHOGI_W", "FEMALE", "MALE", "NO", "YES",                           "FLAT", "NATURAL", "SHARP", "COMMON_T", "ALLA_BR", "Enter"],
        ["L1",  "PAWN_W", "DIAMS_W", "HEARTS_W", "SPADES_W", "CLUBS_W",                  "WHOLE_N", "HALF_N", "QUART_N", "EIGHTH_N", "SIXT_N", "L1"],
        ["Gui", "ROOK_W", "KNIGHT_W", "BISHOP_W", "QUEEN_W", "KING_W",                  "C_CLEF", "G_CLEF", "F_CLEF", "PEDAL", "PEDAL_UP", "BSpace"],
                               ["L6", "L4", "Alt",   "Ctrl", "Space", "L8"]]

# 17
SYMBOL = [["Esc", "SHOGI_BD", "FLAG_B", "XXX", "XXX", "XXX",                  "SPEAKER_UP", "SPEAKER_TG", "SPEAKER_DN", "XXX", "XXX", "Del"],
        ["Tab", "SHOGI_B", "KEY", "LOCK", "LOCK_OPEN", "XXX",                  "STAFF", "BARLINE", "BARLINE_D", "BARLINE_FIN", "CODA", "Enter"],
        ["L1",  "PAWN_B", "DIAMS_B", "HEARTS_B", "SPADES_B", "CLUBS_B",                  "WHOLE_P", "HALF_P", "QUART_P", "EIGHTH_P", "SIXT_P", "L1"],
        ["Gui", "ROOK_B", "KNIGHT_B", "BISHOP_B", "QUEEN_B", "KING_B",                  "REPEAT_S", "REPEAT_E", "SEGNO", "DALSEGNO", "DACAPO", "BSpace"],
                               ["L6", "L4", "Alt",   "Ctrl", "Space", "L8"]]

# 18
math = [["Esc", "EXISTS", "FORALL", "EQUIV", "CORRESP", "INEQUAL",                  "DEFINE", "TO", "MAPSTO", "SETMINUS", "QED", "Del"],
        ["Tab", "OR_", "AND_", "OR", "AND", "NOT",                  "BICOND", "IMPL_REV", "IMPL", "TOP", "BOTTOM", "Enter"],
        ["L1",  "SUM_", "PROD_", "+", "MDOT", "NOTIN",                  "IN", "LS_EQ", "GR_EQ", "INFTY", "epsilon", "L1"],
        ["Gui", "UNION_", "INTERS_", "UNION", "INTERS", "NOTSUBS",                  "PR_SUBSET", "SUBSET", "SUBSET_REV", "OMEGA", "EMPTYSET", "BSpace"],
                               ["L6", "L4", "Alt",   "Ctrl", "Space", "L8"]]

# 19
MATHSCRIPT = [["Esc", "LEFT_CEIL", "DELTA", "REAL_P", "NABLA", "RIGHT_CEIL",                  "LEFT_FLOOR", "BRA", "IMAG_P", "KET", "RIGHT_FLOOR", "Del"],
        ["Tab", "Q_SET", "XXX", "e_FUN", "R_SET", "XXX",                  "Z_SET", "U_SET", "i_UNIT", "BIG_O", "POWERSET", "Enter"],
        ["L1",  "A_SET", "INTEGRAL", "PARTIAL", "F_SET", "XXX",                  "H_SET", "XXX", "K_SET", "LENGTH", "XXX", "L1"],
        ["Gui", "ALEPH", "BETH", "C_SET", "XXX", "B_SET",                  "N_SET", "INDICATOR", "FOURIER", "HAMILTON", "LAPLACE", "BSpace"],
                               ["L6", "L4", "Alt",   "Ctrl", "Space", "L8"]]

# 20
NEO_MATHSCRIPT = [["Esc", "LEFT_CEIL", "DELTA", "REAL_P", "NABLA", "RIGHT_CEIL",                  "LEFT_FLOOR", "BRA", "IMAG_P", "KET", "RIGHT_FLOOR", "Del"],
        ["Tab", "a", "A", "0", "i", "j",                  "0", "1", "2", "3", "4", "Enter"],
        ["L1",  "k", "KC_PSCR", "m", "n", "o",                  "5", "6", "7", "8", "9", "L1"],
        ["Gui", "ALEPH", "BETH", "r", "s", "t",                  "a", "INDICATOR", "FOURIER", "HAMILTON", "LAPLACE", "BSpace"],
                               ["L6", "L4", "Alt",   "Ctrl", "Space", "L8"]]

# 21
mathnum = [["Esc", "SUP1", "SUP2", "SUP3", "SUP_MIN", "ROOT",                  "[", "(", "%", ")", "]", "Del"],
        ["Tab", "CURRENCY", ":", "DEGREE", "MINUTE", "SECOND",                  "*", "7", "8", "9", "/", "Enter"],
        ["L1",  "CENT", "YEN", "POUND", "EURO", "$",                  "+", "4", "5", "6", "-", "L1"],
        ["T4", "DIVISION", "MICRO", "OHM", "BITCOIN", "SECTION",                  "^", "1", "2", "3", "\"", "BSpace"],
                               ["XXX", "L4", "Ctrl",   ".", "0", ","]]

# 22
MATHEXT = [["Esc", "RIGHT_TACK", "MODELS", "AB_VEC", "AB_LINE", "AB_ARC",                  "LESS_LESS", "PRED", "EMBED", "SUCC", "GREAT_GREAT", "Del"],
        ["Tab", "XXX", "XXX", "TRIANGLE", "SQUARE", "CIRCLE",                  "DOT_OP", "PLUS_OP", "MINUS_OP", "ROUGHLY", "ISOMORPH", "Enter"],
        ["L1",  "LTIMES", "RTIMES", "BOWTIE", "M_ANGLE", "ANGLE",                  "CIRC_MID", "AST_MID", "TIMES", "PLUS_MINUS", "MINUS_PLUS", "L1"],
        ["Gui", "LEFT_OUTER", "RIGHT_OUTER", "FULL_OUTER", "SQ_LS", "SQ_LS_EQ",                  "PROP_TO", "PARALLEL", "NOT_PARA", "TIMES_OP", "NOT_DIV", "BSpace"],
                               ["L6", "L4", "Alt",   "Ctrl", "Space", "L8"]]

# 23
game = [["Esc", "1", "2", "3", "4", "5",                  "6", "7", "8", "9", "0", "Del"],
        ["Tab", "q", "w", "e", "r", "t",                  "y", "u", "i", "o", "p", "Enter"],
        ["Caps",  "a", "s", "d", "f", "g",                  "h", "j", "k", "l", "^ Arrow", "Shift"],
        ["Shift", "z", "x", "c", "v", "b",                  "n", "m", ",", "< Arrow", "v Arrow", "> Arrow"],
                               ["Alt", "Space", "Ctrl",   "Enter", "RShift", "Ctrl"]]

# 24
mouse = [["Esc", "XXX", "XXX", "XXX", "XXX", "XXX",                  "XXX", "XXX", "XXX", "XXX", "XXX", "Del"],
        ["Tab", "Menu", "< Tab", "^ Arrow", "> Tab", "Pg Up",                  "Pr Scr", "Mouse 1", "^ Mouse", "Mouse 2", "Scr Lck", "Enter"],
        ["Shift",  "BSpace", "< Arrow", "v Arrow", "> Arrow", "Pg Down",                  "XXX", "< Mouse", "v Mouse", "> Mouse", "XXX", "Shift"],
        ["Enter", "Undo", "Cut", "Copy", "Paste", "Del",                  "Macro 1", "Macro 2", "Macro 3", "Macro 4", "Macro 5", "BSpace"],
                               ["Alt", "Space", "Ctrl",   "Mouse 3", "Mouse 1", "Mouse 2"]]


# # 18
# cyr = [["Esc", "INV_EXCL", "b", "INV_QST", "b", "j",                  "u", "v", "w", "x", "y", "Del"],
#         ["Tab", "a", "A", "0", "i", "j",                  "0", "1", "2", "3", "4", "Enter"],
#         ["L1",  "k", "KC_PSCR", "m", "n", "o",                  "5", "6", "7", "8", "9", "L1"],
#         ["Gui", "p", "q", "r", "s", "t",                  "a", "b", "c", "d", "e", "BSpace"],
#                                ["L6", "L4", "Alt",   "Ctrl", "Space", "L8"]]
#
# # 19
# cyrSH = [["Esc", "INV_EXCL", "b", "INV_QST", "b", "j",                  "u", "v", "w", "x", "y", "Del"],
#         ["Tab", "a", "A", "0", "i", "j",                  "0", "1", "2", "3", "4", "Enter"],
#         ["L1",  "k", "KC_PSCR", "m", "n", "o",                  "5", "6", "7", "8", "9", "L1"],
#         ["Gui", "p", "q", "r", "s", "t",                  "a", "b", "c", "d", "e", "BSpace"],
#                                ["L6", "L4", "Alt",   "Ctrl", "Space", "L8"]]


layers = [qwertz, QWERTZ, neo, NEO, numpad, FN_MEDIA, punct, NAV_TYPO, lang, LANG, neo_lang, NEO_LANG, greek, GREEK, neo_greek, NEO_GREEK,
symbol, SYMBOL, math, MATHSCRIPT, NEO_MATHSCRIPT, mathnum, MATHEXT, game, mouse]
