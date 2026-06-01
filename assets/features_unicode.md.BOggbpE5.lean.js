import { _ as _export_sfc, C as resolveComponent, o as openBlock, c as createElementBlock, al as createStaticVNode, E as createVNode, w as withCtx, j as createBaseVNode, a as createTextVNode } from "./chunks/framework.8zKZLKO7.js";
const __pageData = JSON.parse('{"title":"Unicode","description":"","frontmatter":{},"headers":[],"relativePath":"features/unicode.md","filePath":"features/unicode.md","lastUpdated":null}');
const _sfc_main = { name: "features/unicode.md" };
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  const _component_PluginTabsTab = resolveComponent("PluginTabsTab");
  const _component_PluginTabs = resolveComponent("PluginTabs");
  return openBlock(), createElementBlock("div", null, [
    _cache[9] || (_cache[9] = createStaticVNode("", 18)),
    createVNode(_component_PluginTabs, null, {
      default: withCtx(() => [
        createVNode(_component_PluginTabsTab, { label: "Basic" }, {
          default: withCtx(() => [..._cache[0] || (_cache[0] = [
            createBaseVNode("p", null, [
              createTextVNode("This is the easiest to use, albeit somewhat limited. It supports code points up to "),
              createBaseVNode("code", null, "U+7FFF"),
              createTextVNode(", which covers characters for most modern languages (including East Asian), as well as many symbols, but does not include emoji.")
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("To enable Basic Unicode, add the following to your "),
              createBaseVNode("code", null, "rules.mk"),
              createTextVNode(":")
            ], -1),
            createBaseVNode("div", { class: "language-make vp-adaptive-theme" }, [
              createBaseVNode("button", {
                title: "Copy Code",
                class: "copy"
              }),
              createBaseVNode("span", { class: "lang" }, "make"),
              createBaseVNode("pre", {
                class: "shiki shiki-themes github-light github-dark vp-code",
                tabindex: "0"
              }, [
                createBaseVNode("code", null, [
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "UNICODE_ENABLE = yes")
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("You can then add "),
              createBaseVNode("code", null, "UC(c)"),
              createTextVNode(" keycodes to your keymap, where "),
              createBaseVNode("em", null, "c"),
              createTextVNode(" is the code point of the desired character (in hexadecimal - the "),
              createBaseVNode("code", null, "U+"),
              createTextVNode(" prefix will not work). For example, "),
              createBaseVNode("code", null, "UC(0x40B)"),
              createTextVNode(" will output "),
              createBaseVNode("a", {
                href: "https://unicode-table.com/en/040B/",
                target: "_blank",
                rel: "noreferrer"
              }, "Ћ"),
              createTextVNode(", and "),
              createBaseVNode("code", null, "UC(0x30C4)"),
              createTextVNode(" will output "),
              createBaseVNode("a", {
                href: "https://unicode-table.com/en/30C4",
                target: "_blank",
                rel: "noreferrer"
              }, "ツ"),
              createTextVNode(".")
            ], -1)
          ])]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "Unicode Map" }, {
          default: withCtx(() => [..._cache[1] || (_cache[1] = [
            createBaseVNode("p", null, [
              createTextVNode("Unicode Map supports all possible code points (up to "),
              createBaseVNode("code", null, "U+10FFFF"),
              createTextVNode("). Here, the code points are stored in a separate mapping table (which may contain at most 16,384 entries), instead of directly in the keymap.")
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("To enable Unicode Map, add the following to your "),
              createBaseVNode("code", null, "rules.mk"),
              createTextVNode(":")
            ], -1),
            createBaseVNode("div", { class: "language-make vp-adaptive-theme" }, [
              createBaseVNode("button", {
                title: "Copy Code",
                class: "copy"
              }),
              createBaseVNode("span", { class: "lang" }, "make"),
              createBaseVNode("pre", {
                class: "shiki shiki-themes github-light github-dark vp-code",
                tabindex: "0"
              }, [
                createBaseVNode("code", null, [
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "UNICODEMAP_ENABLE = yes")
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("Then, you will need to create a mapping table in your "),
              createBaseVNode("code", null, "keymap.c"),
              createTextVNode(", and (optionally) an enum for naming the array indices, like so:")
            ], -1),
            createBaseVNode("div", { class: "language-c vp-adaptive-theme" }, [
              createBaseVNode("button", {
                title: "Copy Code",
                class: "copy"
              }),
              createBaseVNode("span", { class: "lang" }, "c"),
              createBaseVNode("pre", {
                class: "shiki shiki-themes github-light github-dark vp-code",
                tabindex: "0"
              }, [
                createBaseVNode("code", null, [
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "enum"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " unicode_names {")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    BANG,")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    IRONY,")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    SNEK")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "};")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "const"),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " uint32_t"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " PROGMEM unicode_map"),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "[]"),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " ="),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " {")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    [BANG]  "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " 0x"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "203D"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ","),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "  // ‽")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    [IRONY] "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " 0x"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "2E2E"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ","),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "  // ⸮")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    [SNEK]  "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " 0x"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "1F40D"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ","),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // 🐍")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "};")
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("Finally, add "),
              createBaseVNode("code", null, "UM(i)"),
              createTextVNode(" keycodes to your keymap, where "),
              createBaseVNode("em", null, "i"),
              createTextVNode(" is an index into the "),
              createBaseVNode("code", null, "unicode_map[]"),
              createTextVNode(" array. If you defined the enum above, you can use those names instead, for example "),
              createBaseVNode("code", null, "UM(BANG)"),
              createTextVNode(" or "),
              createBaseVNode("code", null, "UM(SNEK)"),
              createTextVNode(".")
            ], -1),
            createBaseVNode("h4", {
              id: "unicodemap-pairs",
              tabindex: "-1"
            }, [
              createTextVNode("Lower and Upper Case Pairs "),
              createBaseVNode("a", {
                class: "header-anchor",
                href: "#unicodemap-pairs",
                "aria-label": 'Permalink to "Lower and Upper Case Pairs {#unicodemap-pairs}"'
              }, "​")
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("Some writing systems have lowercase and uppercase variants of each character, such as å and Å. To make inputting these characters easier, you can use the "),
              createBaseVNode("code", null, "UP(i, j)"),
              createTextVNode(" keycode in your keymap, where "),
              createBaseVNode("em", null, "i"),
              createTextVNode(" and "),
              createBaseVNode("em", null, "j"),
              createTextVNode(" are the mapping table indices of the lowercase and uppercase characters, respectively. If you're holding down Shift or have Caps Lock turned on when you press the key, the uppercase character will be inserted; otherwise, the lowercase character will be inserted.")
            ], -1),
            createBaseVNode("div", { class: "language-c vp-adaptive-theme" }, [
              createBaseVNode("button", {
                title: "Copy Code",
                class: "copy"
              }),
              createBaseVNode("span", { class: "lang" }, "c"),
              createBaseVNode("pre", {
                class: "shiki shiki-themes github-light github-dark vp-code",
                tabindex: "0"
              }, [
                createBaseVNode("code", null, [
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "const"),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " uint32_t"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " PROGMEM unicode_map"),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "[]"),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " ="),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " {")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    [AE_LOWER] "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " 0x"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "00E6"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ","),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "  // æ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    [AE_UPPER] "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " 0x"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "00C6"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ","),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "  // Æ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "};")
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("p", null, "This is most useful when creating a keymap for an international layout with special characters. Instead of having to put the lower and upper case versions of a character on separate keys, you can have them both on the same key. This helps blend Unicode keys in with regular keycodes.", -1),
            createBaseVNode("p", null, [
              createTextVNode("Due to keycode size constraints, "),
              createBaseVNode("em", null, "i"),
              createTextVNode(" and "),
              createBaseVNode("em", null, "j"),
              createTextVNode(" can each only refer to one of the first 128 characters in your "),
              createBaseVNode("code", null, "unicode_map"),
              createTextVNode(". In other words, 0 ≤ "),
              createBaseVNode("em", null, "i"),
              createTextVNode(" ≤ 127 and 0 ≤ "),
              createBaseVNode("em", null, "j"),
              createTextVNode(" ≤ 127.")
            ], -1)
          ])]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "UCIS" }, {
          default: withCtx(() => [..._cache[2] || (_cache[2] = [
            createBaseVNode("p", null, "As with Unicode Map, the UCIS method also supports all possible code points, and requires the use of a mapping table. However, it works much differently - Unicode characters are input by replacing a typed mnemonic.", -1),
            createBaseVNode("p", null, [
              createTextVNode("To enable UCIS, add the following to your keymap's "),
              createBaseVNode("code", null, "rules.mk"),
              createTextVNode(":")
            ], -1),
            createBaseVNode("div", { class: "language-make vp-adaptive-theme" }, [
              createBaseVNode("button", {
                title: "Copy Code",
                class: "copy"
              }),
              createBaseVNode("span", { class: "lang" }, "make"),
              createBaseVNode("pre", {
                class: "shiki shiki-themes github-light github-dark vp-code",
                tabindex: "0"
              }, [
                createBaseVNode("code", null, [
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "UCIS_ENABLE = yes")
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("Then, create a mapping table in your "),
              createBaseVNode("code", null, "keymap.c"),
              createTextVNode(":")
            ], -1),
            createBaseVNode("div", { class: "language-c vp-adaptive-theme" }, [
              createBaseVNode("button", {
                title: "Copy Code",
                class: "copy"
              }),
              createBaseVNode("span", { class: "lang" }, "c"),
              createBaseVNode("pre", {
                class: "shiki shiki-themes github-light github-dark vp-code",
                tabindex: "0"
              }, [
                createBaseVNode("code", null, [
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "const"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " ucis_symbol_t"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " ucis_symbol_table"),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "[]"),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " ="),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " UCIS_TABLE"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "    UCIS_SYM"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                    createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '"poop"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "0x"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "1F4A9"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "),"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "                // 💩")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "    UCIS_SYM"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                    createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '"rofl"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "0x"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "1F923"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "),"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "                // 🤣")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "    UCIS_SYM"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                    createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '"ukr"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "0x"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "1F1FA"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "0x"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "1F1E6"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "),"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "        // 🇺🇦")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "    UCIS_SYM"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                    createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '"look"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "0x"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "0CA0"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "0x"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "005F"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "0x"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "0CA0"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ")"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "  // ಠ_ಠ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("By default, each table entry may be up to three code points long. This can be changed by adding "),
              createBaseVNode("code", null, "#define UCIS_MAX_CODE_POINTS n"),
              createTextVNode(" to your keymap's "),
              createBaseVNode("code", null, "config.h"),
              createTextVNode(".")
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("To invoke UCIS input, the "),
              createBaseVNode("code", null, "ucis_start()"),
              createTextVNode(' function must first be called (for example, in a custom "Unicode" keycode). Then, type the mnemonic for the mapping table entry (such as "rofl"), and hit Space or Enter. The "rofl" text will be backspaced and the emoji inserted.')
            ], -1)
          ])]),
          _: 1
        })
      ]),
      _: 1
    }),
    _cache[10] || (_cache[10] = createStaticVNode("", 6)),
    createVNode(_component_PluginTabs, null, {
      default: withCtx(() => [
        createVNode(_component_PluginTabsTab, { label: "macOS" }, {
          default: withCtx(() => [..._cache[3] || (_cache[3] = [
            createBaseVNode("p", null, [
              createBaseVNode("strong", null, "Mode Name:"),
              createTextVNode(),
              createBaseVNode("code", null, "UNICODE_MODE_MACOS")
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("macOS has built-in support for Unicode input as its own input source. It supports all possible code points by way of surrogate pairs for code points above "),
              createBaseVNode("code", null, "U+FFFF"),
              createTextVNode(".")
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("To enable, go to "),
              createBaseVNode("strong", null, "System Preferences → Keyboard → Input Sources"),
              createTextVNode(", then add Unicode Hex Input to the list (under Other), and activate it from the input dropdown in the menu bar. Note that this may disable some Option-based shortcuts such as Option+Left and Option+Right.")
            ], -1)
          ])]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "Linux (IBus)" }, {
          default: withCtx(() => [..._cache[4] || (_cache[4] = [
            createBaseVNode("p", null, [
              createBaseVNode("strong", null, "Mode Name:"),
              createTextVNode(),
              createBaseVNode("code", null, "UNICODE_MODE_LINUX")
            ], -1),
            createBaseVNode("p", null, "For Linux distros with IBus, Unicode input is enabled by default, supports all possible code points, and works almost anywhere. Without IBus, it works under GTK apps, but rarely anywhere else.", -1),
            createBaseVNode("p", null, "Users who would like support in non-GTK apps without IBus may need to resort to a more indirect method, such as creating a custom keyboard layout.", -1)
          ])]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "Windows (WinCompose)" }, {
          default: withCtx(() => [..._cache[5] || (_cache[5] = [
            createBaseVNode("p", null, [
              createBaseVNode("strong", null, "Mode Name:"),
              createTextVNode(),
              createBaseVNode("code", null, "UNICODE_MODE_WINCOMPOSE")
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("This mode requires a third-party tool called "),
              createBaseVNode("a", {
                href: "https://github.com/samhocevar/wincompose",
                target: "_blank",
                rel: "noreferrer"
              }, "WinCompose"),
              createTextVNode(". It supports all possible code points, and is the recommended input mode for Windows.")
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("To enable, install the "),
              createBaseVNode("a", {
                href: "https://github.com/samhocevar/wincompose/releases/latest",
                target: "_blank",
                rel: "noreferrer"
              }, "latest release from GitHub"),
              createTextVNode(". Once installed, it will automatically run on startup. This works reliably under all versions of Windows supported by WinCompose.")
            ], -1)
          ])]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "Windows (HexNumpad)" }, {
          default: withCtx(() => [..._cache[6] || (_cache[6] = [
            createBaseVNode("p", null, [
              createBaseVNode("strong", null, "Mode Name:"),
              createTextVNode(),
              createBaseVNode("code", null, "UNICODE_MODE_WINDOWS")
            ], -1),
            createBaseVNode("div", { class: "warning custom-block" }, [
              createBaseVNode("p", { class: "custom-block-title" }, "WARNING"),
              createBaseVNode("p", null, [
                createTextVNode("This input mode is "),
                createBaseVNode("em", null, "not"),
                createTextVNode(' the "Alt code" system. Alt codes are not Unicode; they instead follow '),
                createBaseVNode("a", {
                  href: "https://en.wikipedia.org/wiki/Alt_code",
                  target: "_blank",
                  rel: "noreferrer"
                }, "the Windows-1252 character set"),
                createTextVNode(".")
              ])
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("This is Windows' built-in hex numpad Unicode input mode. It only supports code points up to "),
              createBaseVNode("code", null, "U+FFFF"),
              createTextVNode(", and is not recommended due to reliability and compatibility issues.")
            ], -1),
            createBaseVNode("p", null, "To enable, run the following as an administrator, then reboot:", -1),
            createBaseVNode("div", { class: "language- vp-adaptive-theme" }, [
              createBaseVNode("button", {
                title: "Copy Code",
                class: "copy"
              }),
              createBaseVNode("span", { class: "lang" }),
              createBaseVNode("pre", {
                class: "shiki shiki-themes github-light github-dark vp-code",
                tabindex: "0"
              }, [
                createBaseVNode("code", null, [
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, 'reg add "HKCU\\Control Panel\\Input Method" -v EnableHexNumpad -t REG_SZ -d 1')
                  ])
                ])
              ])
            ], -1)
          ])]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "Emacs" }, {
          default: withCtx(() => [..._cache[7] || (_cache[7] = [
            createBaseVNode("p", null, [
              createBaseVNode("strong", null, "Mode Name:"),
              createTextVNode(),
              createBaseVNode("code", null, "UNICODE_MODE_EMACS")
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("Emacs supports code point input with the "),
              createBaseVNode("code", null, "insert-char"),
              createTextVNode(" command.")
            ], -1)
          ])]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "BSD" }, {
          default: withCtx(() => [..._cache[8] || (_cache[8] = [
            createBaseVNode("p", null, [
              createBaseVNode("strong", null, "Mode Name:"),
              createTextVNode(),
              createBaseVNode("code", null, "UNICODE_MODE_BSD")
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("Not currently implemented. If you're a BSD user and want to contribute support for this input mode, please "),
              createBaseVNode("a", { href: "./../contributing" }, "feel free"),
              createTextVNode("!")
            ], -1)
          ])]),
          _: 1
        })
      ]),
      _: 1
    }),
    _cache[11] || (_cache[11] = createStaticVNode("", 108))
  ]);
}
const unicode = /* @__PURE__ */ _export_sfc(_sfc_main, [["render", _sfc_render]]);
export {
  __pageData,
  unicode as default
};
