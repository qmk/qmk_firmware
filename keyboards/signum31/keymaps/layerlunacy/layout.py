from sortedcontainers import SortedDict

uc_dict = SortedDict({
    "SNEK": "0x1F40D", ## Error
    ## base
    "ACUTE": "0x00b4",
    ## baseSH
    "INV_EXCL": "0x00a1",
    "INV_QST": "0x00bf",
    ## calc
    "SUP1": "0x00b9",
    "SUP2": "0x00b2",
    "SUP3": "0x00b3",
    "SUP_MIN": "0x207b",
    "ROOT": "0x221a",
    "YES": "0x2713",
    "NO": "0x2717",
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
    ## calcSH
    "CLUBS": "0x2663",
    "DIAMS": "0x2666",
    "HEARTS": "0x2665",
    "SPADES": "0x2660",
    ## lay3SH
    "SQT1": "0x2039",
    "SQT2": "0x201a",
    "SQT3": "0x2018",
    "SQT4": "0x2019",
    "SQT5": "0x203a",
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
    "DQT1": "0x00ab",
    "DQT2": "0x201e",
    "DQT3": "0x201c",
    "DQT4": "0x201d",
    "DQT5": "0x00bb",
    ## lay4
    "ae": "0x00e4",
    "oe": "0x00f6",
    "ue": "0x00fc",
    "sz": "0x00df",
    "n_tilde": "0x00f1",
    ## lay4SH
    "AE": "0x00c4",
    "OE": "0x00d6",
    "UE": "0x00dc",
    "SZ": "0x1e9e",
    "N_TILDE": "0x00d1",


})

qmk_dict = {
    # test cases
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
    "C+A+Del": "LCTL(LALT(KC_DEL))", "Mic 0": "LCTL(KC_M)"
}

# 0
base = [["Esc", "!", "@", "#", "$", "?",                  "{", "(", "ACUTE", ")", "}", "Del"],
        ["Tab", "q", "w", "e", "r", "t",                  "z", "u", "i", "o", "p", "Enter"],
        ["L1",  "a", "s", "d", "f", "g",                  "h", "j", "k", "l", "'", "L1"],
        ["Gui", "y", "x", "c", "v", "b",                  "n", "m", ",", ".", "-", "BSpace"],
                               ["L6", "L4", "Ctrl",   "Alt", "Space", "L8"]]

# 1
baseSH = [["Esc", "INV_EXCL", "&", "/", "%", "INV_QST",                  "<", "[", "_", "]", ">", "Del"],
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
neoSH = [["Esc", "INV_EXCL", "&", "/", "%", "INV_QST",                  "<", "[", "_", "]", ">", "Del"],
        ["S_Tab", "X", "V", "L", "C", "W",                  "K", "H", "G", "F", "Q", "S_Enter"],
        ["L3",  "U", "I", "A", "E", "O",                  "S", "N", "R", "T", "D", "L3"],
        ["T3", "\"", "J", "Y", "P", "Z",                  "B", "M", ";", ":", "=", "BSpace"],
                               ["L6", "L4", "Ctrl",   "Alt", "Space", "L8"]]

# 4
calc = [["Esc", "SUP1", "SUP2", "SUP3", "SUP_MIN", "ROOT",                  "YES", "=", "%", "^", "NO", "Del"],
        ["Tab", "CURRENCY", ":", "DEGREE", "MINUTE", "SECOND",                  "*", "7", "8", "9", "/", "Enter"],
        ["L1",  "CENT", "YEN", "POUND", "EURO", "$",                  "+", "4", "5", "6", "-", "L1"],
        ["T4", "DIVISION", "MICRO", "OHM", "BITCOIN", "SECTION",                  "(", "1", "2", "3", ")", "BSpace"],
                               ["XXX", "L4", "Ctrl",   ".", "0", ","]]

# 5
calcSH = [["Esc", "L_Symb", "L_Greek", "L_Math", "L_Mouse", "L_Game",                  "L_Cyr", "TGL_neo", "UC_win", "UC_mac", "UC_lnx", "Del"],
        ["Tab", "F1", "F2", "F3", "F4", "altF4",                  "Led +", "Led 0", "Led -", "Led ~", "XXX", "Enter"],
        ["L1",  "F5", "F6", "F7", "F8", "XXX",                  "Vol +", "Vol 0", "Vol -", "Mic 0", "XXX", "L1"],
        ["T5", "F9", "F10", "F11", "F12", "XXX",                  "|<<", "play/ps", ">>|", "XXX", "XXX", "BSpace"],
                               ["XXX", "L4", "Ctrl",   "Alt", "Space", "XXX"]]

# 6
lay3 = [["Esc", "XXX", "XXX", "|", "XXX", "XXX",                  "XXX", "XXX", ":", "XXX", "XXX", "Del"],
        ["Tab", "!", "@", "#", "$", "?",                  "{", "(", ",", ")", "}", "Enter"],
        ["L1",  "'", "*", "\\", "\"", "=",                  "+", ".", "_", ";", "-", "L1"],
        ["T6", "~", "&", "/", "%", "^",                  "<", "[", "SECTION", "]", ">", "BSpace"],
                               ["L6", "XXX", "Ctrl",   "Alt", "Space", "XXX"]]

# 7
lay3SH = [["Esc", "SQT1", "SQT2", "SQT3", "SQT4", "SQT5",                  "Insert", "Scr Lck", "Pr Scr", "Pause", "C+A+Del", "Del"],
        ["Tab", "SUP_A", "SUP_O", "TMARK", "COPYR", "REGTM",                  "Pg Up", "Home", "^ Arrow", "End", "XXX", "Enter"],
        ["L1",  "DOTS", "CROSS", "BULLET", "EMDASH", "PERMIL",                  "Pg Down", "< Arrow", "v Arrow", "> Arrow", "Menu", "L1"],
        ["T7", "DQT1", "DQT2", "DQT3", "DQT4", "DQT5",                  "App 1", "App 2", "App 3", "App 4", "App 5", "BSpace"],
                               ["L6", "XXX", "Ctrl",   "Alt", "Space", "XXX"]]

# 8
lay4 = [["Esc", "XXX", "XXX", "XXX", "XXX", "XXX",                  "XXX", "XXX", "XXX", "XXX", "XXX", "Del"],
        ["Compose", "XXX", "XXX", "XXX", "XXX", "XXX",                  "XXX", "XXX", "XXX", "XXX", "XXX", "Enter"],
        ["L1",  "ue", "oe", "ae", "XXX", "XXX",                  "sz", "n_tilde", "XXX", "XXX", "XXX", "L1"],
        ["T8", "XXX", "XXX", "XXX", "XXX", "XXX",                  "XXX", "XXX", "XXX", "XXX", "XXX", "BSpace"],
                               ["XXX", "XXX", "Ctrl",   "Alt", "Space", "L8"]]

# 9
lay4SH = [["Esc", "XXX", "XXX", "XXX", "XXX", "XXX",                  "XXX", "XXX", "XXX", "XXX", "XXX", "Del"],
        ["Compose", "XXX", "XXX", "XXX", "XXX", "XXX",                  "XXX", "XXX", "XXX", "XXX", "XXX", "Enter"],
        ["L1",  "UE", "OE", "AE", "XXX", "XXX",                  "SZ", "N_TILDE", "XXX", "XXX", "XXX", "L1"],
        ["T9", "XXX", "XXX", "XXX", "XXX", "XXX",                  "XXX", "XXX", "XXX", "XXX", "XXX", "BSpace"],
                               ["XXX", "XXX", "Ctrl",   "Alt", "Space", "L8"]]

# 10
game = [["Esc", "1", "2", "3", "4", "5",                  "6", "7", "8", "9", "0", "Del"],
        ["Tab", "q", "w", "e", "r", "t",                  "y", "u", "i", "o", "p", "Enter"],
        ["Caps",  "a", "s", "d", "f", "g",                  "h", "j", "k", "l", "^ Arrow", "Shift"],
        ["Shift", "z", "x", "c", "v", "b",                  "n", "m", "untoggle", "< Arrow", "v Arrow", "> Arrow"],
                               ["Alt", "Space", "Ctrl",   "Enter", "RShift", "Ctrl"]]

# 11
mouse = [["Esc", "XXX", "XXX", "Enter", "XXX", "XXX",                  "XXX", "XXX", "XXX", "XXX", "XXX", "Del"],
        ["Tab", "Menu", "< Tab", "^ Arrow", "> Tab", "Pg Up",                  "Pr Scr", "Mouse 1", "^ Mouse", "Mouse 2", "Scr Lck", "Enter"],
        ["Shift",  "BSpace", "< Arrow", "v Arrow", "> Arrow", "Pg Down",                  "XXX", "< Mouse", "v Mouse", "> Mouse", "XXX", "Shift"],
        ["untoggle", "Undo", "Cut", "Copy", "Paste", "Del",                  "XXX", "XXX", "XXX", "XXX", "XXX", "BSpace"],
                               ["Alt", "Space", "Ctrl",   "Mouse 3", "Mouse 1", "Mouse 2"]]

# 12
math = [["Esc", "INV_EXCL", "b", "INV_QST", "b", "j",                  "u", "v", "w", "x", "y", "Del"],
        ["Tab", "a", "A", "0", "i", "j",                  "0", "1", "2", "3", "4", "Enter"],
        ["L1",  "k", "KC_PSCR", "m", "n", "o",                  "5", "6", "7", "8", "9", "L1"],
        ["Gui", "p", "q", "r", "s", "t",                  "a", "b", "c", "d", "e", "BSpace"],
                               ["L6", "L4", "Alt",   "Ctrl", "Space", "L8"]]

# 13
mathSH = [["Esc", "INV_EXCL", "b", "INV_QST", "b", "j",                  "u", "v", "w", "x", "y", "Del"],
        ["Tab", "a", "A", "0", "i", "j",                  "0", "1", "2", "3", "4", "Enter"],
        ["L1",  "k", "KC_PSCR", "m", "n", "o",                  "5", "6", "7", "8", "9", "L1"],
        ["Gui", "p", "q", "r", "s", "t",                  "a", "b", "c", "d", "e", "BSpace"],
                               ["L6", "L4", "Alt",   "Ctrl", "Space", "L8"]]

# 14
greek = [["Esc", "INV_EXCL", "b", "INV_QST", "b", "j",                  "u", "v", "w", "x", "y", "Del"],
        ["Tab", "a", "A", "0", "i", "j",                  "0", "1", "2", "3", "4", "Enter"],
        ["L1",  "k", "KC_PSCR", "m", "n", "o",                  "5", "6", "7", "8", "9", "L1"],
        ["Gui", "p", "q", "r", "s", "t",                  "a", "b", "c", "d", "e", "BSpace"],
                               ["L6", "L4", "Alt",   "Ctrl", "Space", "L8"]]

# 15
greekSH = [["Esc", "INV_EXCL", "b", "INV_QST", "b", "j",                  "u", "v", "w", "x", "y", "Del"],
        ["Tab", "a", "A", "0", "i", "j",                  "0", "1", "2", "3", "4", "Enter"],
        ["L1",  "k", "KC_PSCR", "m", "n", "o",                  "5", "6", "7", "8", "9", "L1"],
        ["Gui", "p", "q", "r", "s", "t",                  "a", "b", "c", "d", "e", "BSpace"],
                               ["L6", "L4", "Alt",   "Ctrl", "Space", "L8"]]

# 16
symb = [["Esc", "CLUBS", "DIAMS", "HEARTS", "SPADES", "j",                  "u", "v", "w", "x", "y", "Del"],
        ["Tab", "a", "A", "0", "i", "j",                  "0", "1", "2", "3", "4", "Enter"],
        ["L1",  "k", "KC_PSCR", "m", "n", "o",                  "5", "6", "7", "8", "9", "L1"],
        ["Gui", "p", "q", "r", "s", "t",                  "a", "b", "c", "d", "e", "BSpace"],
                               ["L6", "L4", "Alt",   "Ctrl", "Space", "L8"]]

# 17
symbSH = [["Esc", "INV_EXCL", "b", "INV_QST", "b", "j",                  "u", "v", "w", "x", "y", "Del"],
        ["Tab", "a", "A", "0", "i", "j",                  "0", "1", "2", "3", "4", "Enter"],
        ["L1",  "k", "KC_PSCR", "m", "n", "o",                  "5", "6", "7", "8", "9", "L1"],
        ["Gui", "p", "q", "r", "s", "t",                  "a", "b", "c", "d", "e", "BSpace"],
                               ["L6", "L4", "Alt",   "Ctrl", "Space", "L8"]]

# 18
cyr = [["Esc", "INV_EXCL", "b", "INV_QST", "b", "j",                  "u", "v", "w", "x", "y", "Del"],
        ["Tab", "a", "A", "0", "i", "j",                  "0", "1", "2", "3", "4", "Enter"],
        ["L1",  "k", "KC_PSCR", "m", "n", "o",                  "5", "6", "7", "8", "9", "L1"],
        ["Gui", "p", "q", "r", "s", "t",                  "a", "b", "c", "d", "e", "BSpace"],
                               ["L6", "L4", "Alt",   "Ctrl", "Space", "L8"]]

# 19
cyrSH = [["Esc", "INV_EXCL", "b", "INV_QST", "b", "j",                  "u", "v", "w", "x", "y", "Del"],
        ["Tab", "a", "A", "0", "i", "j",                  "0", "1", "2", "3", "4", "Enter"],
        ["L1",  "k", "KC_PSCR", "m", "n", "o",                  "5", "6", "7", "8", "9", "L1"],
        ["Gui", "p", "q", "r", "s", "t",                  "a", "b", "c", "d", "e", "BSpace"],
                               ["L6", "L4", "Alt",   "Ctrl", "Space", "L8"]]


layers = [base, baseSH, neo, neoSH, calc, calcSH, lay3, lay3SH, lay4, lay4SH, game, mouse #, math, mathSH, greek, greekSH, symb, symbSH, cyr, cyrSH
]
