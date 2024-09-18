import { _ as _export_sfc, D as resolveComponent, c as createElementBlock, I as createVNode, w as withCtx, a8 as createStaticVNode, o as openBlock, l as createBaseVNode, a as createTextVNode } from "./chunks/framework.Clpp4x2N.js";
const __pageData = JSON.parse('{"title":"Unicode","description":"","frontmatter":{},"headers":[],"relativePath":"features/unicode.md","filePath":"features/unicode.md"}');
const _sfc_main = { name: "features/unicode.md" };
const _hoisted_1 = /* @__PURE__ */ createStaticVNode('<h1 id="unicode" tabindex="-1">Unicode <a class="header-anchor" href="#unicode" aria-label="Permalink to &quot;Unicode {#unicode}&quot;">​</a></h1><p>With a little help from your OS, practically any Unicode character can be input using your keyboard.</p><h2 id="caveats" tabindex="-1">Caveats <a class="header-anchor" href="#caveats" aria-label="Permalink to &quot;Caveats {#caveats}&quot;">​</a></h2><p>There are some limitations to this feature. Because there is no &quot;standard&quot; method of Unicode input across all operating systems, each of them require their own setup process on both the host <em>and</em> in the firmware, which may involve installation of additional software. This also means Unicode input will not &quot;just work&quot; when the keyboard is plugged into another device.</p><h2 id="usage" tabindex="-1">Usage <a class="header-anchor" href="#usage" aria-label="Permalink to &quot;Usage {#usage}&quot;">​</a></h2><p>The core Unicode API can be used purely programmatically. However, there are also additional subsystems which build on top of it and come with keycodes to make things easier. See below for more details.</p><p>Add the following to your keymap&#39;s <code>rules.mk</code>:</p><div class="language-make vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">make</span><pre class="shiki shiki-themes github-light github-dark vp-code"><code><span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">UNICODE_COMMON = yes</span></span></code></pre></div><h2 id="basic-configuration" tabindex="-1">Basic Configuration <a class="header-anchor" href="#basic-configuration" aria-label="Permalink to &quot;Basic Configuration {#basic-configuration}&quot;">​</a></h2><p>Add the following to your <code>config.h</code>:</p><table><thead><tr><th>Define</th><th>Default</th><th>Description</th></tr></thead><tbody><tr><td><code>UNICODE_KEY_MAC</code></td><td><code>KC_LEFT_ALT</code></td><td>The key to hold when beginning a Unicode sequence with the macOS input mode</td></tr><tr><td><code>UNICODE_KEY_LNX</code></td><td><code>LCTL(LSFT(KC_U))</code></td><td>The key to tap when beginning a Unicode sequence with the Linux input mode</td></tr><tr><td><code>UNICODE_KEY_WINC</code></td><td><code>KC_RIGHT_ALT</code></td><td>The key to hold when beginning a Unicode sequence with the WinCompose input mode</td></tr><tr><td><code>UNICODE_SELECTED_MODES</code></td><td><code>-1</code></td><td>A comma separated list of input modes for cycling through</td></tr><tr><td><code>UNICODE_CYCLE_PERSIST</code></td><td><code>true</code></td><td>Whether to persist the current Unicode input mode to EEPROM</td></tr><tr><td><code>UNICODE_TYPE_DELAY</code></td><td><code>10</code></td><td>The amount of time to wait, in milliseconds, between Unicode sequence keystrokes</td></tr></tbody></table><h3 id="audio-feedback" tabindex="-1">Audio Feedback <a class="header-anchor" href="#audio-feedback" aria-label="Permalink to &quot;Audio Feedback {#audio-feedback}&quot;">​</a></h3><p>If you have the <a href="./audio">Audio</a> feature enabled on your board, you can configure it to play sounds when the input mode is changed.</p><p>Add the following to your <code>config.h</code>:</p><table><thead><tr><th>Define</th><th>Default</th><th>Description</th></tr></thead><tbody><tr><td><code>UNICODE_SONG_MAC</code></td><td><em>n/a</em></td><td>The song to play when the macOS input mode is selected</td></tr><tr><td><code>UNICODE_SONG_LNX</code></td><td><em>n/a</em></td><td>The song to play when the Linux input mode is selected</td></tr><tr><td><code>UNICODE_SONG_BSD</code></td><td><em>n/a</em></td><td>The song to play when the BSD input mode is selected</td></tr><tr><td><code>UNICODE_SONG_WIN</code></td><td><em>n/a</em></td><td>The song to play when the Windows input mode is selected</td></tr><tr><td><code>UNICODE_SONG_WINC</code></td><td><em>n/a</em></td><td>The song to play when the WinCompose input mode is selected</td></tr></tbody></table><h2 id="input-subsystems" tabindex="-1">Input Subsystems <a class="header-anchor" href="#input-subsystems" aria-label="Permalink to &quot;Input Subsystems {#input-subsystems}&quot;">​</a></h2><p>Each of these subsystems have their own pros and cons in terms of flexibility and ease of use. Choose the one that best fits your needs.</p>', 17);
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
const _hoisted_40 = /* @__PURE__ */ createStaticVNode('<h2 id="input-modes" tabindex="-1">Input Modes <a class="header-anchor" href="#input-modes" aria-label="Permalink to &quot;Input Modes {#input-modes}&quot;">​</a></h2><p>Unicode input works by typing a sequence of characters, similar to a macro. However, since this sequence depends on your OS, you will need to prepare both your host machine and QMK to recognise and send the correct Unicode input sequences respectively.</p><p>To set the list of enabled input modes, add the <code>UNICODE_SELECTED_MODES</code> define to your keymap&#39;s <code>config.h</code>, for example:</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#define</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> UNICODE_SELECTED_MODES</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> UNICODE_MODE_LINUX</span></span>\n<span class="line"><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">// or</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#define</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> UNICODE_SELECTED_MODES</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> UNICODE_MODE_MACOS, UNICODE_MODE_WINCOMPOSE</span></span></code></pre></div><p>These modes can then be cycled through using the <code>UC_NEXT</code> and <code>UC_PREV</code> keycodes. You can also switch to any input mode, even if it is not specified in <code>UNICODE_SELECTED_MODES</code>, using their respective keycodes.</p><p>If your keyboard has working EEPROM, it will remember the last used input mode and continue using it on the next power up. This can be disabled by defining <code>UNICODE_CYCLE_PERSIST</code> to <code>false</code>.</p>', 6);
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
const _hoisted_64 = /* @__PURE__ */ createStaticVNode('<h2 id="keycodes" tabindex="-1">Keycodes <a class="header-anchor" href="#keycodes" aria-label="Permalink to &quot;Keycodes {#keycodes}&quot;">​</a></h2><table><thead><tr><th>Key</th><th>Aliases</th><th>Description</th></tr></thead><tbody><tr><td><code>UC(c)</code></td><td></td><td>Send Unicode code point <code>c</code>, up to <code>0x7FFF</code></td></tr><tr><td><code>UM(i)</code></td><td></td><td>Send Unicode code point at index <code>i</code> in <code>unicode_map</code></td></tr><tr><td><code>UP(i, j)</code></td><td></td><td>Send Unicode code point at index <code>i</code>, or <code>j</code> if Shift/Caps is on</td></tr><tr><td><code>QK_UNICODE_MODE_NEXT</code></td><td><code>UC_NEXT</code></td><td>Cycle through selected input modes</td></tr><tr><td><code>QK_UNICODE_MODE_PREVIOUS</code></td><td><code>UC_PREV</code></td><td>Cycle through selected input modes in reverse</td></tr><tr><td><code>QK_UNICODE_MODE_MACOS</code></td><td><code>UC_MAC</code></td><td>Switch to macOS input</td></tr><tr><td><code>QK_UNICODE_MODE_LINUX</code></td><td><code>UC_LINX</code></td><td>Switch to Linux input</td></tr><tr><td><code>QK_UNICODE_MODE_WINDOWS</code></td><td><code>UC_WIN</code></td><td>Switch to Windows input</td></tr><tr><td><code>QK_UNICODE_MODE_BSD</code></td><td><code>UC_BSD</code></td><td>Switch to BSD input (not implemented)</td></tr><tr><td><code>QK_UNICODE_MODE_WINCOMPOSE</code></td><td><code>UC_WINC</code></td><td>Switch to Windows input using WinCompose</td></tr><tr><td><code>QK_UNICODE_MODE_EMACS</code></td><td><code>UC_EMAC</code></td><td>Switch to emacs (<code>C-x-8 RET</code>)</td></tr></tbody></table><h2 id="api" tabindex="-1">API <a class="header-anchor" href="#api" aria-label="Permalink to &quot;API {#api}&quot;">​</a></h2><h3 id="api-get-unicode-input-mode" tabindex="-1"><code>uint8_t get_unicode_input_mode(void)</code> <a class="header-anchor" href="#api-get-unicode-input-mode" aria-label="Permalink to &quot;`uint8_t get_unicode_input_mode(void)` {#api-get-unicode-input-mode}&quot;">​</a></h3><p>Get the current Unicode input mode.</p><h4 id="api-get-unicode-input-mode-return-value" tabindex="-1">Return Value <a class="header-anchor" href="#api-get-unicode-input-mode-return-value" aria-label="Permalink to &quot;Return Value {#api-get-unicode-input-mode-return-value}&quot;">​</a></h4><p>The currently active Unicode input mode.</p><hr><h3 id="api-set-unicode-input-mode" tabindex="-1"><code>void set_unicode_input_mode(uint8_t mode)</code> <a class="header-anchor" href="#api-set-unicode-input-mode" aria-label="Permalink to &quot;`void set_unicode_input_mode(uint8_t mode)` {#api-set-unicode-input-mode}&quot;">​</a></h3><p>Set the Unicode input mode.</p><h4 id="api-set-unicode-input-mode-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-set-unicode-input-mode-arguments" aria-label="Permalink to &quot;Arguments {#api-set-unicode-input-mode-arguments}&quot;">​</a></h4><ul><li><code>uint8_t mode</code><br> The input mode to set.</li></ul><hr><h3 id="api-unicode-input-mode-step" tabindex="-1"><code>void unicode_input_mode_step(void)</code> <a class="header-anchor" href="#api-unicode-input-mode-step" aria-label="Permalink to &quot;`void unicode_input_mode_step(void)` {#api-unicode-input-mode-step}&quot;">​</a></h3><p>Change to the next Unicode input mode.</p><hr><h3 id="api-unicode-input-mode-step-reverse" tabindex="-1"><code>void unicode_input_mode_step_reverse(void)</code> <a class="header-anchor" href="#api-unicode-input-mode-step-reverse" aria-label="Permalink to &quot;`void unicode_input_mode_step_reverse(void)` {#api-unicode-input-mode-step-reverse}&quot;">​</a></h3><p>Change to the previous Unicode input mode.</p><hr><h3 id="api-unicode-input-mode-set-user" tabindex="-1"><code>void unicode_input_mode_set_user(uint8_t input_mode)</code> <a class="header-anchor" href="#api-unicode-input-mode-set-user" aria-label="Permalink to &quot;`void unicode_input_mode_set_user(uint8_t input_mode)` {#api-unicode-input-mode-set-user}&quot;">​</a></h3><p>User-level callback, invoked when the input mode is changed.</p><h4 id="api-unicode-input-mode-set-user-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-unicode-input-mode-set-user-arguments" aria-label="Permalink to &quot;Arguments {#api-unicode-input-mode-set-user-arguments}&quot;">​</a></h4><ul><li><code>uint8_t input_mode</code><br> The new input mode.</li></ul><hr><h3 id="api-unicode-input-mode-set-kb" tabindex="-1"><code>void unicode_input_mode_set_kb(uint8_t input_mode)</code> <a class="header-anchor" href="#api-unicode-input-mode-set-kb" aria-label="Permalink to &quot;`void unicode_input_mode_set_kb(uint8_t input_mode)` {#api-unicode-input-mode-set-kb}&quot;">​</a></h3><p>Keyboard-level callback, invoked when the input mode is changed.</p><h4 id="api-unicode-input-mode-set-kb-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-unicode-input-mode-set-kb-arguments" aria-label="Permalink to &quot;Arguments {#api-unicode-input-mode-set-kb-arguments}&quot;">​</a></h4><ul><li><code>uint8_t input_mode</code><br> The new input mode.</li></ul><hr><h3 id="api-unicode-input-start" tabindex="-1"><code>void unicode_input_start(void)</code> <a class="header-anchor" href="#api-unicode-input-start" aria-label="Permalink to &quot;`void unicode_input_start(void)` {#api-unicode-input-start}&quot;">​</a></h3><p>Begin the Unicode input sequence. The exact behavior depends on the currently selected input mode:</p><ul><li><strong>macOS</strong>: Hold <code>UNICODE_KEY_MAC</code></li><li><strong>Linux</strong>: Tap <code>UNICODE_KEY_LNX</code></li><li><strong>WinCompose</strong>: Tap <code>UNICODE_KEY_WINC</code>, then U</li><li><strong>HexNumpad</strong>: Hold Left Alt, then tap Numpad +</li><li><strong>Emacs</strong>: Tap Ctrl+X, then 8, then Enter</li></ul><p>This function is weakly defined, and can be overridden in user code.</p><hr><h3 id="api-unicode-input-finish" tabindex="-1"><code>void unicode_input_finish(void)</code> <a class="header-anchor" href="#api-unicode-input-finish" aria-label="Permalink to &quot;`void unicode_input_finish(void)` {#api-unicode-input-finish}&quot;">​</a></h3><p>Complete the Unicode input sequence. The exact behavior depends on the currently selected input mode:</p><ul><li><strong>macOS</strong>: Release <code>UNICODE_KEY_MAC</code></li><li><strong>Linux</strong>: Tap Space</li><li><strong>WinCompose</strong>: Tap Enter</li><li><strong>HexNumpad</strong>: Release Left Alt</li><li><strong>Emacs</strong>: Tap Enter</li></ul><p>This function is weakly defined, and can be overridden in user code.</p><hr><h3 id="api-unicode-input-cancel" tabindex="-1"><code>void unicode_input_cancel(void)</code> <a class="header-anchor" href="#api-unicode-input-cancel" aria-label="Permalink to &quot;`void unicode_input_cancel(void)` {#api-unicode-input-cancel}&quot;">​</a></h3><p>Cancel the Unicode input sequence. The exact behavior depends on the currently selected input mode:</p><ul><li><strong>macOS</strong>: Release <code>UNICODE_KEY_MAC</code></li><li><strong>Linux</strong>: Tap Escape</li><li><strong>WinCompose</strong>: Tap Escape</li><li><strong>HexNumpad</strong>: Release Left Alt</li><li><strong>Emacs</strong>: Tap Ctrl+G</li></ul><p>This function is weakly defined, and can be overridden in user code.</p><hr><h3 id="api-register-unicode" tabindex="-1"><code>void register_unicode(uint32_t code_point)</code> <a class="header-anchor" href="#api-register-unicode" aria-label="Permalink to &quot;`void register_unicode(uint32_t code_point)` {#api-register-unicode}&quot;">​</a></h3><p>Input a single Unicode character. A surrogate pair will be sent if required by the input mode.</p><h4 id="api-register-unicode-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-register-unicode-arguments" aria-label="Permalink to &quot;Arguments {#api-register-unicode-arguments}&quot;">​</a></h4><ul><li><code>uint32_t code_point</code><br> The code point of the character to send.</li></ul><hr><h3 id="api-send-unicode-string" tabindex="-1"><code>void send_unicode_string(const char *str)</code> <a class="header-anchor" href="#api-send-unicode-string" aria-label="Permalink to &quot;`void send_unicode_string(const char *str)` {#api-send-unicode-string}&quot;">​</a></h3><p>Send a string containing Unicode characters.</p><h4 id="api-send-unicode-string-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-send-unicode-string-arguments" aria-label="Permalink to &quot;Arguments {#api-send-unicode-string-arguments}&quot;">​</a></h4><ul><li><code>const char *str</code><br> The string to send.</li></ul><hr><h3 id="api-unicodemap-index" tabindex="-1"><code>uint8_t unicodemap_index(uint16_t keycode)</code> <a class="header-anchor" href="#api-unicodemap-index" aria-label="Permalink to &quot;`uint8_t unicodemap_index(uint16_t keycode)` {#api-unicodemap-index}&quot;">​</a></h3><p>Get the index into the <code>unicode_map</code> array for the given keycode, respecting shift state for pair keycodes.</p><h4 id="api-unicodemap-index-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-unicodemap-index-arguments" aria-label="Permalink to &quot;Arguments {#api-unicodemap-index-arguments}&quot;">​</a></h4><ul><li><code>uint16_t keycode</code><br> The Unicode Map keycode to get the index of.</li></ul><h4 id="api-unicodemap-index-return-value" tabindex="-1">Return Value <a class="header-anchor" href="#api-unicodemap-index-return-value" aria-label="Permalink to &quot;Return Value {#api-unicodemap-index-return-value}&quot;">​</a></h4><p>An index into the <code>unicode_map</code> array.</p><hr><h3 id="api-unicodemap-get-code-point" tabindex="-1"><code>uint32_t unicodemap_get_code_point(uint8_t index)</code> <a class="header-anchor" href="#api-unicodemap-get-code-point" aria-label="Permalink to &quot;`uint32_t unicodemap_get_code_point(uint8_t index)` {#api-unicodemap-get-code-point}&quot;">​</a></h3><p>Get the code point for the given index in the <code>unicode_map</code> array.</p><h4 id="unicodemap-get-code-point-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#unicodemap-get-code-point-arguments" aria-label="Permalink to &quot;Arguments {#unicodemap-get-code-point-arguments}&quot;">​</a></h4><ul><li><code>uint8_t index</code><br> The index into the <code>unicode_map</code> array.</li></ul><h4 id="unicodemap-get-code-point-return-value" tabindex="-1">Return Value <a class="header-anchor" href="#unicodemap-get-code-point-return-value" aria-label="Permalink to &quot;Return Value {#unicodemap-get-code-point-return-value}&quot;">​</a></h4><p>A Unicode code point value.</p><hr><h3 id="api-register-unicodemap" tabindex="-1"><code>void register_unicodemap(uint8_t index)</code> <a class="header-anchor" href="#api-register-unicodemap" aria-label="Permalink to &quot;`void register_unicodemap(uint8_t index)` {#api-register-unicodemap}&quot;">​</a></h3><p>Send the code point for the given index in the <code>unicode_map</code> array.</p><h4 id="api-register-unicodemap-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-register-unicodemap-arguments" aria-label="Permalink to &quot;Arguments {#api-register-unicodemap-arguments}&quot;">​</a></h4><ul><li><code>uint8_t index</code><br> The index into the <code>unicode_map</code> array.</li></ul><hr><h3 id="api-ucis-start" tabindex="-1"><code>void ucis_start(void)</code> <a class="header-anchor" href="#api-ucis-start" aria-label="Permalink to &quot;`void ucis_start(void)` {#api-ucis-start}&quot;">​</a></h3><p>Begin the input sequence.</p><hr><h3 id="api-ucis-active" tabindex="-1"><code>bool ucis_active(void)</code> <a class="header-anchor" href="#api-ucis-active" aria-label="Permalink to &quot;`bool ucis_active(void)` {#api-ucis-active}&quot;">​</a></h3><p>Whether UCIS is currently active.</p><h4 id="api-ucis-active-return-value" tabindex="-1">Return Value <a class="header-anchor" href="#api-ucis-active-return-value" aria-label="Permalink to &quot;Return Value {#api-ucis-active-return-value}&quot;">​</a></h4><p><code>true</code> if UCIS is active.</p><hr><h3 id="api-ucis-count" tabindex="-1"><code>uint8_t ucis_count(void)</code> <a class="header-anchor" href="#api-ucis-count" aria-label="Permalink to &quot;`uint8_t ucis_count(void)` {#api-ucis-count}&quot;">​</a></h3><p>Get the number of characters in the input sequence buffer.</p><h4 id="api-ucis-count-return-value" tabindex="-1">Return Value <a class="header-anchor" href="#api-ucis-count-return-value" aria-label="Permalink to &quot;Return Value {#api-ucis-count-return-value}&quot;">​</a></h4><p>The current input sequence buffer length.</p><hr><h3 id="api-ucis-add" tabindex="-1"><code>bool ucis_add(uint16_t keycode)</code> <a class="header-anchor" href="#api-ucis-add" aria-label="Permalink to &quot;`bool ucis_add(uint16_t keycode)` {#api-ucis-add}&quot;">​</a></h3><p>Add the given keycode to the input sequence buffer.</p><h4 id="api-ucis-add-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-ucis-add-arguments" aria-label="Permalink to &quot;Arguments {#api-ucis-add-arguments}&quot;">​</a></h4><ul><li><code>uint16_t keycode</code><br> The keycode to add. Must be between <code>KC_A</code> and <code>KC_Z</code>, or <code>KC_1</code> and <code>KC_0</code>.</li></ul><h4 id="api-ucis-add-return-value" tabindex="-1">Return Value <a class="header-anchor" href="#api-ucis-add-return-value" aria-label="Permalink to &quot;Return Value {#api-ucis-add-return-value}&quot;">​</a></h4><p><code>true</code> if the keycode was added.</p><hr><h3 id="api-ucis-remove-last" tabindex="-1"><code>bool ucis_remove_last(void)</code> <a class="header-anchor" href="#api-ucis-remove-last" aria-label="Permalink to &quot;`bool ucis_remove_last(void)` {#api-ucis-remove-last}&quot;">​</a></h3><p>Remove the last character from the input sequence buffer.</p><h4 id="api-ucis-remove-last-return-value" tabindex="-1">Return Value <a class="header-anchor" href="#api-ucis-remove-last-return-value" aria-label="Permalink to &quot;Return Value {#api-ucis-remove-last-return-value}&quot;">​</a></h4><p><code>true</code> if the sequence was not empty.</p><hr><h3 id="api-ucis-finish" tabindex="-1"><code>void ucis_finish(void)</code> <a class="header-anchor" href="#api-ucis-finish" aria-label="Permalink to &quot;`void ucis_finish(void)` {#api-ucis-finish}&quot;">​</a></h3><p>Mark the input sequence as complete, and attempt to match.</p><hr><h3 id="api-ucis-cancel" tabindex="-1"><code>void ucis_cancel(void)</code> <a class="header-anchor" href="#api-ucis-cancel" aria-label="Permalink to &quot;`void ucis_cancel(void)` {#api-ucis-cancel}&quot;">​</a></h3><p>Cancel the input sequence.</p><hr><h3 id="api-register-ucis" tabindex="-1"><code>void register_ucis(void)</code> <a class="header-anchor" href="#api-register-ucis" aria-label="Permalink to &quot;`void register_ucis(void)` {#api-register-ucis}&quot;">​</a></h3><p>Send the code point(s) for the given UCIS index.</p><h4 id="api-register-ucis-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-register-ucis-arguments" aria-label="Permalink to &quot;Arguments {#api-register-ucis-arguments}&quot;">​</a></h4><ul><li><code>uint8_t index</code><br> The index into the UCIS symbol table.</li></ul>', 108);
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
