import { _ as _export_sfc, D as resolveComponent, c as createElementBlock, I as createVNode, w as withCtx, a8 as createStaticVNode, o as openBlock, l as createBaseVNode, a as createTextVNode } from "./chunks/framework.Clpp4x2N.js";
const __pageData = JSON.parse('{"title":"Unicode","description":"","frontmatter":{},"headers":[],"relativePath":"features/unicode.md","filePath":"features/unicode.md"}');
const _sfc_main = { name: "features/unicode.md" };
const _hoisted_1 = /* @__PURE__ */ createStaticVNode("", 17);
const _hoisted_18 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("This is the easiest to use, albeit somewhat limited. It supports code points up to "),
  /* @__PURE__ */ createBaseVNode("code", null, "U+7FFF"),
  /* @__PURE__ */ createTextVNode(", which covers characters for most modern languages (including East Asian), as well as many symbols, but does not include emoji.")
], -1);
const _hoisted_19 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("To enable Basic Unicode, add the following to your "),
  /* @__PURE__ */ createBaseVNode("code", null, "rules.mk"),
  /* @__PURE__ */ createTextVNode(":")
], -1);
const _hoisted_20 = /* @__PURE__ */ createBaseVNode("div", { class: "language-make vp-adaptive-theme" }, [
  /* @__PURE__ */ createBaseVNode("button", {
    title: "Copy Code",
    class: "copy"
  }),
  /* @__PURE__ */ createBaseVNode("span", { class: "lang" }, "make"),
  /* @__PURE__ */ createBaseVNode("pre", { class: "shiki shiki-themes github-light github-dark vp-code" }, [
    /* @__PURE__ */ createBaseVNode("code", null, [
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "UNICODE_ENABLE = yes")
      ])
    ])
  ])
], -1);
const _hoisted_21 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("You can then add "),
  /* @__PURE__ */ createBaseVNode("code", null, "UC(c)"),
  /* @__PURE__ */ createTextVNode(" keycodes to your keymap, where "),
  /* @__PURE__ */ createBaseVNode("em", null, "c"),
  /* @__PURE__ */ createTextVNode(" is the code point of the desired character (in hexadecimal - the "),
  /* @__PURE__ */ createBaseVNode("code", null, "U+"),
  /* @__PURE__ */ createTextVNode(" prefix will not work). For example, "),
  /* @__PURE__ */ createBaseVNode("code", null, "UC(0x40B)"),
  /* @__PURE__ */ createTextVNode(" will output "),
  /* @__PURE__ */ createBaseVNode("a", {
    href: "https://unicode-table.com/en/040B/",
    target: "_blank",
    rel: "noreferrer"
  }, "Ћ"),
  /* @__PURE__ */ createTextVNode(", and "),
  /* @__PURE__ */ createBaseVNode("code", null, "UC(0x30C4)"),
  /* @__PURE__ */ createTextVNode(" will output "),
  /* @__PURE__ */ createBaseVNode("a", {
    href: "https://unicode-table.com/en/30C4",
    target: "_blank",
    rel: "noreferrer"
  }, "ツ"),
  /* @__PURE__ */ createTextVNode(".")
], -1);
const _hoisted_22 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Unicode Map supports all possible code points (up to "),
  /* @__PURE__ */ createBaseVNode("code", null, "U+10FFFF"),
  /* @__PURE__ */ createTextVNode("). Here, the code points are stored in a separate mapping table (which may contain at most 16,384 entries), instead of directly in the keymap.")
], -1);
const _hoisted_23 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("To enable Unicode Map, add the following to your "),
  /* @__PURE__ */ createBaseVNode("code", null, "rules.mk"),
  /* @__PURE__ */ createTextVNode(":")
], -1);
const _hoisted_24 = /* @__PURE__ */ createBaseVNode("div", { class: "language-make vp-adaptive-theme" }, [
  /* @__PURE__ */ createBaseVNode("button", {
    title: "Copy Code",
    class: "copy"
  }),
  /* @__PURE__ */ createBaseVNode("span", { class: "lang" }, "make"),
  /* @__PURE__ */ createBaseVNode("pre", { class: "shiki shiki-themes github-light github-dark vp-code" }, [
    /* @__PURE__ */ createBaseVNode("code", null, [
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "UNICODEMAP_ENABLE = yes")
      ])
    ])
  ])
], -1);
const _hoisted_25 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Then, you will need to create a mapping table in your "),
  /* @__PURE__ */ createBaseVNode("code", null, "keymap.c"),
  /* @__PURE__ */ createTextVNode(", and (optionally) an enum for naming the array indices, like so:")
], -1);
const _hoisted_26 = /* @__PURE__ */ createBaseVNode("div", { class: "language-c vp-adaptive-theme" }, [
  /* @__PURE__ */ createBaseVNode("button", {
    title: "Copy Code",
    class: "copy"
  }),
  /* @__PURE__ */ createBaseVNode("span", { class: "lang" }, "c"),
  /* @__PURE__ */ createBaseVNode("pre", { class: "shiki shiki-themes github-light github-dark vp-code" }, [
    /* @__PURE__ */ createBaseVNode("code", null, [
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "enum"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " unicode_names {")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    BANG,")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    IRONY,")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    SNEK")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "};")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "const"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " uint32_t"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " PROGMEM unicode_map"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "[]"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " ="),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " {")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    [BANG]  "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " 0x"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "203D"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ","),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "  // ‽")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    [IRONY] "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " 0x"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "2E2E"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ","),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "  // ⸮")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    [SNEK]  "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " 0x"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "1F40D"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ","),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // 🐍")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "};")
      ])
    ])
  ])
], -1);
const _hoisted_27 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Finally, add "),
  /* @__PURE__ */ createBaseVNode("code", null, "UM(i)"),
  /* @__PURE__ */ createTextVNode(" keycodes to your keymap, where "),
  /* @__PURE__ */ createBaseVNode("em", null, "i"),
  /* @__PURE__ */ createTextVNode(" is an index into the "),
  /* @__PURE__ */ createBaseVNode("code", null, "unicode_map[]"),
  /* @__PURE__ */ createTextVNode(" array. If you defined the enum above, you can use those names instead, for example "),
  /* @__PURE__ */ createBaseVNode("code", null, "UM(BANG)"),
  /* @__PURE__ */ createTextVNode(" or "),
  /* @__PURE__ */ createBaseVNode("code", null, "UM(SNEK)"),
  /* @__PURE__ */ createTextVNode(".")
], -1);
const _hoisted_28 = /* @__PURE__ */ createBaseVNode("h4", {
  id: "unicodemap-pairs",
  tabindex: "-1"
}, [
  /* @__PURE__ */ createTextVNode("Lower and Upper Case Pairs "),
  /* @__PURE__ */ createBaseVNode("a", {
    class: "header-anchor",
    href: "#unicodemap-pairs",
    "aria-label": 'Permalink to "Lower and Upper Case Pairs {#unicodemap-pairs}"'
  }, "​")
], -1);
const _hoisted_29 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Some writing systems have lowercase and uppercase variants of each character, such as å and Å. To make inputting these characters easier, you can use the "),
  /* @__PURE__ */ createBaseVNode("code", null, "UP(i, j)"),
  /* @__PURE__ */ createTextVNode(" keycode in your keymap, where "),
  /* @__PURE__ */ createBaseVNode("em", null, "i"),
  /* @__PURE__ */ createTextVNode(" and "),
  /* @__PURE__ */ createBaseVNode("em", null, "j"),
  /* @__PURE__ */ createTextVNode(" are the mapping table indices of the lowercase and uppercase characters, respectively. If you're holding down Shift or have Caps Lock turned on when you press the key, the uppercase character will be inserted; otherwise, the lowercase character will be inserted.")
], -1);
const _hoisted_30 = /* @__PURE__ */ createBaseVNode("div", { class: "language-c vp-adaptive-theme" }, [
  /* @__PURE__ */ createBaseVNode("button", {
    title: "Copy Code",
    class: "copy"
  }),
  /* @__PURE__ */ createBaseVNode("span", { class: "lang" }, "c"),
  /* @__PURE__ */ createBaseVNode("pre", { class: "shiki shiki-themes github-light github-dark vp-code" }, [
    /* @__PURE__ */ createBaseVNode("code", null, [
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "const"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " uint32_t"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " PROGMEM unicode_map"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "[]"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " ="),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " {")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    [AE_LOWER] "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " 0x"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "00E6"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ","),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "  // æ")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    [AE_UPPER] "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " 0x"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "00C6"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ","),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "  // Æ")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "};")
      ])
    ])
  ])
], -1);
const _hoisted_31 = /* @__PURE__ */ createBaseVNode("p", null, "This is most useful when creating a keymap for an international layout with special characters. Instead of having to put the lower and upper case versions of a character on separate keys, you can have them both on the same key. This helps blend Unicode keys in with regular keycodes.", -1);
const _hoisted_32 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Due to keycode size constraints, "),
  /* @__PURE__ */ createBaseVNode("em", null, "i"),
  /* @__PURE__ */ createTextVNode(" and "),
  /* @__PURE__ */ createBaseVNode("em", null, "j"),
  /* @__PURE__ */ createTextVNode(" can each only refer to one of the first 128 characters in your "),
  /* @__PURE__ */ createBaseVNode("code", null, "unicode_map"),
  /* @__PURE__ */ createTextVNode(". In other words, 0 ≤ "),
  /* @__PURE__ */ createBaseVNode("em", null, "i"),
  /* @__PURE__ */ createTextVNode(" ≤ 127 and 0 ≤ "),
  /* @__PURE__ */ createBaseVNode("em", null, "j"),
  /* @__PURE__ */ createTextVNode(" ≤ 127.")
], -1);
const _hoisted_33 = /* @__PURE__ */ createBaseVNode("p", null, "As with Unicode Map, the UCIS method also supports all possible code points, and requires the use of a mapping table. However, it works much differently - Unicode characters are input by replacing a typed mnemonic.", -1);
const _hoisted_34 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("To enable UCIS, add the following to your keymap's "),
  /* @__PURE__ */ createBaseVNode("code", null, "rules.mk"),
  /* @__PURE__ */ createTextVNode(":")
], -1);
const _hoisted_35 = /* @__PURE__ */ createBaseVNode("div", { class: "language-make vp-adaptive-theme" }, [
  /* @__PURE__ */ createBaseVNode("button", {
    title: "Copy Code",
    class: "copy"
  }),
  /* @__PURE__ */ createBaseVNode("span", { class: "lang" }, "make"),
  /* @__PURE__ */ createBaseVNode("pre", { class: "shiki shiki-themes github-light github-dark vp-code" }, [
    /* @__PURE__ */ createBaseVNode("code", null, [
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "UCIS_ENABLE = yes")
      ])
    ])
  ])
], -1);
const _hoisted_36 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Then, create a mapping table in your "),
  /* @__PURE__ */ createBaseVNode("code", null, "keymap.c"),
  /* @__PURE__ */ createTextVNode(":")
], -1);
const _hoisted_37 = /* @__PURE__ */ createBaseVNode("div", { class: "language-c vp-adaptive-theme" }, [
  /* @__PURE__ */ createBaseVNode("button", {
    title: "Copy Code",
    class: "copy"
  }),
  /* @__PURE__ */ createBaseVNode("span", { class: "lang" }, "c"),
  /* @__PURE__ */ createBaseVNode("pre", { class: "shiki shiki-themes github-light github-dark vp-code" }, [
    /* @__PURE__ */ createBaseVNode("code", null, [
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "const"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " ucis_symbol_t"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " ucis_symbol_table"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "[]"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " ="),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " UCIS_TABLE"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "    UCIS_SYM"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '"poop"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "0x"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "1F4A9"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "),"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "                // 💩")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "    UCIS_SYM"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '"rofl"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "0x"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "1F923"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "),"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "                // 🤣")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "    UCIS_SYM"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '"ukr"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "0x"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "1F1FA"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "0x"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "1F1E6"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "),"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "        // 🇺🇦")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "    UCIS_SYM"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '"look"'),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "0x"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "0CA0"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "0x"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "005F"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "0x"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "0CA0"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ")"),
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "  // ಠ_ಠ")
      ]),
      /* @__PURE__ */ createTextVNode("\n"),
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
      ])
    ])
  ])
], -1);
const _hoisted_38 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("By default, each table entry may be up to three code points long. This can be changed by adding "),
  /* @__PURE__ */ createBaseVNode("code", null, "#define UCIS_MAX_CODE_POINTS n"),
  /* @__PURE__ */ createTextVNode(" to your keymap's "),
  /* @__PURE__ */ createBaseVNode("code", null, "config.h"),
  /* @__PURE__ */ createTextVNode(".")
], -1);
const _hoisted_39 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("To invoke UCIS input, the "),
  /* @__PURE__ */ createBaseVNode("code", null, "ucis_start()"),
  /* @__PURE__ */ createTextVNode(' function must first be called (for example, in a custom "Unicode" keycode). Then, type the mnemonic for the mapping table entry (such as "rofl"), and hit Space or Enter. The "rofl" text will be backspaced and the emoji inserted.')
], -1);
const _hoisted_40 = /* @__PURE__ */ createStaticVNode("", 6);
const _hoisted_46 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createBaseVNode("strong", null, "Mode Name:"),
  /* @__PURE__ */ createTextVNode(),
  /* @__PURE__ */ createBaseVNode("code", null, "UNICODE_MODE_MACOS")
], -1);
const _hoisted_47 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("macOS has built-in support for Unicode input as its own input source. It supports all possible code points by way of surrogate pairs for code points above "),
  /* @__PURE__ */ createBaseVNode("code", null, "U+FFFF"),
  /* @__PURE__ */ createTextVNode(".")
], -1);
const _hoisted_48 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("To enable, go to "),
  /* @__PURE__ */ createBaseVNode("strong", null, "System Preferences → Keyboard → Input Sources"),
  /* @__PURE__ */ createTextVNode(", then add Unicode Hex Input to the list (under Other), and activate it from the input dropdown in the menu bar. Note that this may disable some Option-based shortcuts such as Option+Left and Option+Right.")
], -1);
const _hoisted_49 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createBaseVNode("strong", null, "Mode Name:"),
  /* @__PURE__ */ createTextVNode(),
  /* @__PURE__ */ createBaseVNode("code", null, "UNICODE_MODE_LINUX")
], -1);
const _hoisted_50 = /* @__PURE__ */ createBaseVNode("p", null, "For Linux distros with IBus, Unicode input is enabled by default, supports all possible code points, and works almost anywhere. Without IBus, it works under GTK apps, but rarely anywhere else.", -1);
const _hoisted_51 = /* @__PURE__ */ createBaseVNode("p", null, "Users who would like support in non-GTK apps without IBus may need to resort to a more indirect method, such as creating a custom keyboard layout.", -1);
const _hoisted_52 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createBaseVNode("strong", null, "Mode Name:"),
  /* @__PURE__ */ createTextVNode(),
  /* @__PURE__ */ createBaseVNode("code", null, "UNICODE_MODE_WINCOMPOSE")
], -1);
const _hoisted_53 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("This mode requires a third-party tool called "),
  /* @__PURE__ */ createBaseVNode("a", {
    href: "https://github.com/samhocevar/wincompose",
    target: "_blank",
    rel: "noreferrer"
  }, "WinCompose"),
  /* @__PURE__ */ createTextVNode(". It supports all possible code points, and is the recommended input mode for Windows.")
], -1);
const _hoisted_54 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("To enable, install the "),
  /* @__PURE__ */ createBaseVNode("a", {
    href: "https://github.com/samhocevar/wincompose/releases/latest",
    target: "_blank",
    rel: "noreferrer"
  }, "latest release from GitHub"),
  /* @__PURE__ */ createTextVNode(". Once installed, it will automatically run on startup. This works reliably under all versions of Windows supported by WinCompose.")
], -1);
const _hoisted_55 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createBaseVNode("strong", null, "Mode Name:"),
  /* @__PURE__ */ createTextVNode(),
  /* @__PURE__ */ createBaseVNode("code", null, "UNICODE_MODE_WINDOWS")
], -1);
const _hoisted_56 = /* @__PURE__ */ createBaseVNode("div", { class: "warning custom-block" }, [
  /* @__PURE__ */ createBaseVNode("p", { class: "custom-block-title" }, "WARNING"),
  /* @__PURE__ */ createBaseVNode("p", null, [
    /* @__PURE__ */ createTextVNode("This input mode is "),
    /* @__PURE__ */ createBaseVNode("em", null, "not"),
    /* @__PURE__ */ createTextVNode(' the "Alt code" system. Alt codes are not Unicode; they instead follow '),
    /* @__PURE__ */ createBaseVNode("a", {
      href: "https://en.wikipedia.org/wiki/Alt_code",
      target: "_blank",
      rel: "noreferrer"
    }, "the Windows-1252 character set"),
    /* @__PURE__ */ createTextVNode(".")
  ])
], -1);
const _hoisted_57 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("This is Windows' built-in hex numpad Unicode input mode. It only supports code points up to "),
  /* @__PURE__ */ createBaseVNode("code", null, "U+FFFF"),
  /* @__PURE__ */ createTextVNode(", and is not recommended due to reliability and compatibility issues.")
], -1);
const _hoisted_58 = /* @__PURE__ */ createBaseVNode("p", null, "To enable, run the following as an administrator, then reboot:", -1);
const _hoisted_59 = /* @__PURE__ */ createBaseVNode("div", { class: "language- vp-adaptive-theme" }, [
  /* @__PURE__ */ createBaseVNode("button", {
    title: "Copy Code",
    class: "copy"
  }),
  /* @__PURE__ */ createBaseVNode("span", { class: "lang" }),
  /* @__PURE__ */ createBaseVNode("pre", { class: "shiki shiki-themes github-light github-dark vp-code" }, [
    /* @__PURE__ */ createBaseVNode("code", null, [
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", null, 'reg add "HKCU\\Control Panel\\Input Method" -v EnableHexNumpad -t REG_SZ -d 1')
      ])
    ])
  ])
], -1);
const _hoisted_60 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createBaseVNode("strong", null, "Mode Name:"),
  /* @__PURE__ */ createTextVNode(),
  /* @__PURE__ */ createBaseVNode("code", null, "UNICODE_MODE_EMACS")
], -1);
const _hoisted_61 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Emacs supports code point input with the "),
  /* @__PURE__ */ createBaseVNode("code", null, "insert-char"),
  /* @__PURE__ */ createTextVNode(" command.")
], -1);
const _hoisted_62 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createBaseVNode("strong", null, "Mode Name:"),
  /* @__PURE__ */ createTextVNode(),
  /* @__PURE__ */ createBaseVNode("code", null, "UNICODE_MODE_BSD")
], -1);
const _hoisted_63 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Not currently implemented. If you're a BSD user and want to contribute support for this input mode, please "),
  /* @__PURE__ */ createBaseVNode("a", { href: "./../contributing" }, "feel free"),
  /* @__PURE__ */ createTextVNode("!")
], -1);
const _hoisted_64 = /* @__PURE__ */ createStaticVNode("", 108);
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  const _component_PluginTabsTab = resolveComponent("PluginTabsTab");
  const _component_PluginTabs = resolveComponent("PluginTabs");
  return openBlock(), createElementBlock("div", null, [
    _hoisted_1,
    createVNode(_component_PluginTabs, null, {
      default: withCtx(() => [
        createVNode(_component_PluginTabsTab, { label: "Basic" }, {
          default: withCtx(() => [
            _hoisted_18,
            _hoisted_19,
            _hoisted_20,
            _hoisted_21
          ]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "Unicode Map" }, {
          default: withCtx(() => [
            _hoisted_22,
            _hoisted_23,
            _hoisted_24,
            _hoisted_25,
            _hoisted_26,
            _hoisted_27,
            _hoisted_28,
            _hoisted_29,
            _hoisted_30,
            _hoisted_31,
            _hoisted_32
          ]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "UCIS" }, {
          default: withCtx(() => [
            _hoisted_33,
            _hoisted_34,
            _hoisted_35,
            _hoisted_36,
            _hoisted_37,
            _hoisted_38,
            _hoisted_39
          ]),
          _: 1
        })
      ]),
      _: 1
    }),
    _hoisted_40,
    createVNode(_component_PluginTabs, null, {
      default: withCtx(() => [
        createVNode(_component_PluginTabsTab, { label: "macOS" }, {
          default: withCtx(() => [
            _hoisted_46,
            _hoisted_47,
            _hoisted_48
          ]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "Linux (IBus)" }, {
          default: withCtx(() => [
            _hoisted_49,
            _hoisted_50,
            _hoisted_51
          ]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "Windows (WinCompose)" }, {
          default: withCtx(() => [
            _hoisted_52,
            _hoisted_53,
            _hoisted_54
          ]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "Windows (HexNumpad)" }, {
          default: withCtx(() => [
            _hoisted_55,
            _hoisted_56,
            _hoisted_57,
            _hoisted_58,
            _hoisted_59
          ]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "Emacs" }, {
          default: withCtx(() => [
            _hoisted_60,
            _hoisted_61
          ]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "BSD" }, {
          default: withCtx(() => [
            _hoisted_62,
            _hoisted_63
          ]),
          _: 1
        })
      ]),
      _: 1
    }),
    _hoisted_64
  ]);
}
const unicode = /* @__PURE__ */ _export_sfc(_sfc_main, [["render", _sfc_render]]);
export {
  __pageData,
  unicode as default
};
