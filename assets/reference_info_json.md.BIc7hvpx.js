import { _ as _export_sfc, C as resolveComponent, o as openBlock, c as createElementBlock, al as createStaticVNode, j as createBaseVNode, a as createTextVNode, E as createVNode, w as withCtx } from "./chunks/framework.8zKZLKO7.js";
const __pageData = JSON.parse('{"title":"info.json Reference","description":"","frontmatter":{},"headers":[],"relativePath":"reference_info_json.md","filePath":"reference_info_json.md","lastUpdated":null}');
const _sfc_main = { name: "reference_info_json.md" };
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  const _component_Badge = resolveComponent("Badge");
  return openBlock(), createElementBlock("div", null, [
    _cache[1107] || (_cache[1107] = createStaticVNode('<h1 id="info-json-reference" tabindex="-1"><code>info.json</code> Reference <a class="header-anchor" href="#info-json-reference" aria-label="Permalink to &quot;`info.json` Reference {#info-json-reference}&quot;">​</a></h1><p>The information contained in <code>info.json</code> is combined with the <code>config.h</code> and <code>rules.mk</code> files, dynamically generating the necessary configuration for your keyboard at compile time. It is also used by the <a href="https://github.com/qmk/qmk_api" target="_blank" rel="noreferrer">QMK API</a>, and contains the information <a href="https://config.qmk.fm/" target="_blank" rel="noreferrer">QMK Configurator</a> needs to display a representation of your keyboard. Its key/value pairs are ruled by the <a href="https://github.com/qmk/qmk_firmware/blob/master/data/schemas/keyboard.jsonschema" target="_blank" rel="noreferrer"><code>data/schemas/keyboard.jsonschema</code></a> file. To learn more about the why and how of the schema file see the <a href="./data_driven_config">Data Driven Configuration</a> page.</p><p>You can create <code>info.json</code> files at every level under <code>qmk_firmware/keyboards/&lt;keyboard&gt;</code>. These files are combined, with more specific files overriding keys in less specific files. This means you do not need to duplicate your metadata information. For example, <code>qmk_firmware/keyboards/clueboard/info.json</code> specifies information common to all Clueboard products, such as <code>manufacturer</code> and <code>maintainer</code>, while <code>qmk_firmware/keyboards/clueboard/66/info.json</code> contains more specific information about Clueboard 66%.</p><h2 id="general-metadata" tabindex="-1">General Metadata <a class="header-anchor" href="#general-metadata" aria-label="Permalink to &quot;General Metadata {#general-metadata}&quot;">​</a></h2>', 4)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[2] || (_cache[2] = createBaseVNode("code", null, "keyboard_name", -1)),
        _cache[3] || (_cache[3] = createTextVNode()),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [..._cache[0] || (_cache[0] = [
            createTextVNode("String", -1)
          ])]),
          _: 1
        }),
        _cache[4] || (_cache[4] = createTextVNode()),
        createVNode(_component_Badge, null, {
          default: withCtx(() => [..._cache[1] || (_cache[1] = [
            createTextVNode("Required", -1)
          ])]),
          _: 1
        }),
        _cache[5] || (_cache[5] = createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            createTextVNode("A free-form text string describing the keyboard. This will be used as the USB product string. Can include Unicode characters, escaped to ASCII eg. "),
            createBaseVNode("code", null, "\\u03A8"),
            createTextVNode(" (Ψ).")
          ]),
          createBaseVNode("li", null, [
            createTextVNode("Example: "),
            createBaseVNode("code", null, '"Clueboard 66%"')
          ])
        ], -1))
      ]),
      createBaseVNode("li", null, [
        _cache[8] || (_cache[8] = createBaseVNode("code", null, "maintainer", -1)),
        _cache[9] || (_cache[9] = createTextVNode()),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [..._cache[6] || (_cache[6] = [
            createTextVNode("String", -1)
          ])]),
          _: 1
        }),
        _cache[10] || (_cache[10] = createTextVNode()),
        createVNode(_component_Badge, null, {
          default: withCtx(() => [..._cache[7] || (_cache[7] = [
            createTextVNode("Required", -1)
          ])]),
          _: 1
        }),
        _cache[11] || (_cache[11] = createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            createTextVNode("GitHub username of the maintainer, or "),
            createBaseVNode("code", null, "qmk"),
            createTextVNode(" for community maintained boards.")
          ]),
          createBaseVNode("li", null, [
            createTextVNode("Example: "),
            createBaseVNode("code", null, '"skullydazed"')
          ])
        ], -1))
      ]),
      createBaseVNode("li", null, [
        _cache[14] || (_cache[14] = createBaseVNode("code", null, "manufacturer", -1)),
        _cache[15] || (_cache[15] = createTextVNode()),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [..._cache[12] || (_cache[12] = [
            createTextVNode("String", -1)
          ])]),
          _: 1
        }),
        _cache[16] || (_cache[16] = createTextVNode()),
        createVNode(_component_Badge, null, {
          default: withCtx(() => [..._cache[13] || (_cache[13] = [
            createTextVNode("Required", -1)
          ])]),
          _: 1
        }),
        _cache[17] || (_cache[17] = createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            createTextVNode("A free-form text string describing the keyboard's manufacturer. This will be used as the USB manufacturer string. Can include Unicode characters, escaped to ASCII eg. "),
            createBaseVNode("code", null, "\\u03A8"),
            createTextVNode(" (Ψ).")
          ]),
          createBaseVNode("li", null, [
            createTextVNode("Example: "),
            createBaseVNode("code", null, '"Clueboard"')
          ])
        ], -1))
      ]),
      createBaseVNode("li", null, [
        _cache[20] || (_cache[20] = createBaseVNode("code", null, "url", -1)),
        _cache[21] || (_cache[21] = createTextVNode()),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [..._cache[18] || (_cache[18] = [
            createTextVNode("String", -1)
          ])]),
          _: 1
        }),
        _cache[22] || (_cache[22] = createTextVNode()),
        createVNode(_component_Badge, null, {
          default: withCtx(() => [..._cache[19] || (_cache[19] = [
            createTextVNode("Required", -1)
          ])]),
          _: 1
        }),
        _cache[23] || (_cache[23] = createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            createTextVNode("A URL to the keyboard's product page, "),
            createBaseVNode("a", {
              href: "https://browse.qmk.fm/",
              target: "_blank",
              rel: "noreferrer"
            }, "QMK Keyboards"),
            createTextVNode(" page, or other page describing information about the keyboard.")
          ]),
          createBaseVNode("li", null, [
            createTextVNode("Example: "),
            createBaseVNode("code", null, '"https://clueboard.co"')
          ])
        ], -1))
      ]),
      createBaseVNode("li", null, [
        _cache[25] || (_cache[25] = createBaseVNode("code", null, "bootloader_instructions", -1)),
        _cache[26] || (_cache[26] = createTextVNode()),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [..._cache[24] || (_cache[24] = [
            createTextVNode("String", -1)
          ])]),
          _: 1
        }),
        _cache[27] || (_cache[27] = createBaseVNode("ul", null, [
          createBaseVNode("li", null, "Instructions for putting the keyboard into a mode that allows for firmware flashing."),
          createBaseVNode("li", null, [
            createTextVNode("Example: "),
            createBaseVNode("code", null, '"Press the button marked RESET on the back of the PCB"')
          ])
        ], -1))
      ]),
      createBaseVNode("li", null, [
        _cache[29] || (_cache[29] = createBaseVNode("code", null, "tags", -1)),
        _cache[30] || (_cache[30] = createTextVNode()),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [..._cache[28] || (_cache[28] = [
            createTextVNode("Array: String", -1)
          ])]),
          _: 1
        }),
        _cache[31] || (_cache[31] = createBaseVNode("ul", null, [
          createBaseVNode("li", null, "A list of tags describing the keyboard."),
          createBaseVNode("li", null, [
            createTextVNode("Example: "),
            createBaseVNode("code", null, '["ortho", "split", "rgb"]')
          ])
        ], -1))
      ])
    ]),
    _cache[1108] || (_cache[1108] = createBaseVNode("h2", {
      id: "hardware-configuration",
      tabindex: "-1"
    }, [
      createTextVNode("Hardware Configuration "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#hardware-configuration",
        "aria-label": 'Permalink to "Hardware Configuration {#hardware-configuration}"'
      }, "​")
    ], -1)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[33] || (_cache[33] = createBaseVNode("code", null, "board", -1)),
        _cache[34] || (_cache[34] = createTextVNode()),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [..._cache[32] || (_cache[32] = [
            createTextVNode("String", -1)
          ])]),
          _: 1
        }),
        _cache[35] || (_cache[35] = createBaseVNode("ul", null, [
          createBaseVNode("li", null, "Override the default ChibiOS board name (ARM-based keyboards only)."),
          createBaseVNode("li", null, [
            createTextVNode("Example: "),
            createBaseVNode("code", null, '"BLACKPILL_STM32_F411"')
          ])
        ], -1))
      ]),
      createBaseVNode("li", null, [
        _cache[37] || (_cache[37] = createBaseVNode("code", null, "bootloader", -1)),
        _cache[38] || (_cache[38] = createTextVNode()),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [..._cache[36] || (_cache[36] = [
            createTextVNode("String", -1)
          ])]),
          _: 1
        }),
        _cache[39] || (_cache[39] = createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            createTextVNode("The bootloader in use on the keyboard. Required if "),
            createBaseVNode("code", null, "development_board"),
            createTextVNode(" is not specified.")
          ])
        ], -1))
      ]),
      createBaseVNode("li", null, [
        _cache[41] || (_cache[41] = createBaseVNode("code", null, "development_board", -1)),
        _cache[42] || (_cache[42] = createTextVNode()),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [..._cache[40] || (_cache[40] = [
            createTextVNode("String", -1)
          ])]),
          _: 1
        }),
        _cache[43] || (_cache[43] = createBaseVNode("ul", null, [
          createBaseVNode("li", null, "The microcontroller development board, if applicable."),
          createBaseVNode("li", null, [
            createTextVNode("Example: "),
            createBaseVNode("code", null, '"promicro"')
          ])
        ], -1))
      ]),
      createBaseVNode("li", null, [
        _cache[45] || (_cache[45] = createBaseVNode("code", null, "pin_compatible", -1)),
        _cache[46] || (_cache[46] = createTextVNode()),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [..._cache[44] || (_cache[44] = [
            createTextVNode("String", -1)
          ])]),
          _: 1
        }),
        _cache[47] || (_cache[47] = createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            createTextVNode("The form factor of the development board, if applicable. Must be one of "),
            createBaseVNode("code", null, "elite_c"),
            createTextVNode(", "),
            createBaseVNode("code", null, "promicro"),
            createTextVNode(".")
          ])
        ], -1))
      ]),
      createBaseVNode("li", null, [
        _cache[49] || (_cache[49] = createBaseVNode("code", null, "processor", -1)),
        _cache[50] || (_cache[50] = createTextVNode()),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [..._cache[48] || (_cache[48] = [
            createTextVNode("String", -1)
          ])]),
          _: 1
        }),
        _cache[51] || (_cache[51] = createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            createTextVNode("The microcontroller in use on the keyboard. Required if "),
            createBaseVNode("code", null, "development_board"),
            createTextVNode(" is not specified.")
          ])
        ], -1))
      ])
    ]),
    _cache[1109] || (_cache[1109] = createBaseVNode("h2", {
      id: "firmware-configuration",
      tabindex: "-1"
    }, [
      createTextVNode("Firmware Configuration "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#firmware-configuration",
        "aria-label": 'Permalink to "Firmware Configuration {#firmware-configuration}"'
      }, "​")
    ], -1)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[61] || (_cache[61] = createBaseVNode("code", null, "build", -1)),
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _cache[53] || (_cache[53] = createBaseVNode("code", null, "debounce_type", -1)),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[52] || (_cache[52] = [
                createTextVNode("String", -1)
              ])]),
              _: 1
            }),
            _cache[54] || (_cache[54] = createStaticVNode("<ul><li>The debounce algorithm to use. Must be one of <code>asym_eager_defer_pk</code>, <code>custom</code>, <code>sym_defer_g</code>, <code>sym_defer_pk</code>, <code>sym_defer_pr</code>, <code>sym_eager_pk</code>, <code>sym_eager_pr</code>.</li></ul>", 1))
          ]),
          createBaseVNode("li", null, [
            _cache[56] || (_cache[56] = createBaseVNode("code", null, "firmware_format", -1)),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[55] || (_cache[55] = [
                createTextVNode("String", -1)
              ])]),
              _: 1
            }),
            _cache[57] || (_cache[57] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("The format of the final output binary. Must be one of "),
                createBaseVNode("code", null, "bin"),
                createTextVNode(", "),
                createBaseVNode("code", null, "hex"),
                createTextVNode(", "),
                createBaseVNode("code", null, "uf2"),
                createTextVNode(".")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[59] || (_cache[59] = createBaseVNode("code", null, "lto", -1)),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[58] || (_cache[58] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[60] || (_cache[60] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Enable Link-Time Optimization."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ])
        ])
      ]),
      createBaseVNode("li", null, [
        _cache[63] || (_cache[63] = createBaseVNode("code", null, "features", -1)),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [..._cache[62] || (_cache[62] = [
            createTextVNode("Object: Boolean", -1)
          ])]),
          _: 1
        }),
        _cache[64] || (_cache[64] = createStaticVNode('<ul><li>A dictionary of features to enable or disable.</li><li>Example:</li></ul><div class="language-json vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">json</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">{</span></span>\n<span class="line"><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">    &quot;rgb_matrix&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">: </span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">true</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">,</span></span>\n<span class="line"><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">    &quot;rgblight&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">: </span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">false</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">}</span></span></code></pre></div>', 2))
      ]),
      createBaseVNode("li", null, [
        _cache[82] || (_cache[82] = createBaseVNode("code", null, "qmk", -1)),
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _cache[73] || (_cache[73] = createBaseVNode("code", null, "locking", -1)),
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _cache[66] || (_cache[66] = createBaseVNode("code", null, "enabled", -1)),
                _cache[67] || (_cache[67] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[65] || (_cache[65] = [
                    createTextVNode("Boolean", -1)
                  ])]),
                  _: 1
                }),
                _cache[68] || (_cache[68] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "Enable locking switch support."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "false")
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[70] || (_cache[70] = createBaseVNode("code", null, "resync", -1)),
                _cache[71] || (_cache[71] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[69] || (_cache[69] = [
                    createTextVNode("Boolean", -1)
                  ])]),
                  _: 1
                }),
                _cache[72] || (_cache[72] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "Keep switch state consistent with keyboard LED state."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "false")
                  ])
                ], -1))
              ])
            ])
          ]),
          createBaseVNode("li", null, [
            _cache[75] || (_cache[75] = createBaseVNode("code", null, "tap_capslock_delay", -1)),
            _cache[76] || (_cache[76] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[74] || (_cache[74] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[77] || (_cache[77] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The delay between keydown and keyup for Caps Lock tap events in milliseconds."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "80"),
                createTextVNode(" (80 ms)")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[79] || (_cache[79] = createBaseVNode("code", null, "tap_keycode_delay", -1)),
            _cache[80] || (_cache[80] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[78] || (_cache[78] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[81] || (_cache[81] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The delay between keydown and keyup for tap events in milliseconds."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "0"),
                createTextVNode(" (no delay)")
              ])
            ], -1))
          ])
        ])
      ]),
      createBaseVNode("li", null, [
        _cache[123] || (_cache[123] = createBaseVNode("code", null, "tapping", -1)),
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _cache[84] || (_cache[84] = createBaseVNode("code", null, "chordal_hold", -1)),
            _cache[85] || (_cache[85] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[83] || (_cache[83] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[86] || (_cache[86] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[88] || (_cache[88] = createBaseVNode("code", null, "hold_on_other_key_press", -1)),
            _cache[89] || (_cache[89] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[87] || (_cache[87] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[90] || (_cache[90] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[92] || (_cache[92] = createBaseVNode("code", null, "hold_on_other_key_press_per_key", -1)),
            _cache[93] || (_cache[93] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[91] || (_cache[91] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[94] || (_cache[94] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[96] || (_cache[96] = createBaseVNode("code", null, "permissive_hold", -1)),
            _cache[97] || (_cache[97] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[95] || (_cache[95] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[98] || (_cache[98] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[100] || (_cache[100] = createBaseVNode("code", null, "permissive_hold_per_key", -1)),
            _cache[101] || (_cache[101] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[99] || (_cache[99] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[102] || (_cache[102] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[104] || (_cache[104] = createBaseVNode("code", null, "retro", -1)),
            _cache[105] || (_cache[105] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[103] || (_cache[103] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[106] || (_cache[106] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[108] || (_cache[108] = createBaseVNode("code", null, "retro_per_key", -1)),
            _cache[109] || (_cache[109] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[107] || (_cache[107] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[110] || (_cache[110] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[112] || (_cache[112] = createBaseVNode("code", null, "term", -1)),
            _cache[113] || (_cache[113] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[111] || (_cache[111] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[114] || (_cache[114] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "200"),
                createTextVNode(" (200 ms)")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[116] || (_cache[116] = createBaseVNode("code", null, "term_per_key", -1)),
            _cache[117] || (_cache[117] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[115] || (_cache[115] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[118] || (_cache[118] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[120] || (_cache[120] = createBaseVNode("code", null, "toggle", -1)),
            _cache[121] || (_cache[121] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[119] || (_cache[119] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[122] || (_cache[122] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "5")
              ])
            ], -1))
          ])
        ])
      ])
    ]),
    _cache[1110] || (_cache[1110] = createBaseVNode("h2", {
      id: "apa102",
      tabindex: "-1"
    }, [
      createTextVNode("APA102 "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#apa102",
        "aria-label": 'Permalink to "APA102 {#apa102}"'
      }, "​")
    ], -1)),
    _cache[1111] || (_cache[1111] = createBaseVNode("p", null, [
      createTextVNode("Configures the "),
      createBaseVNode("a", { href: "./drivers/apa102" }, "APA102"),
      createTextVNode(" driver.")
    ], -1)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[140] || (_cache[140] = createBaseVNode("code", null, "apa102", -1)),
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _cache[126] || (_cache[126] = createBaseVNode("code", null, "clock_pin", -1)),
            _cache[127] || (_cache[127] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[124] || (_cache[124] = [
                createTextVNode("Pin", -1)
              ])]),
              _: 1
            }),
            _cache[128] || (_cache[128] = createTextVNode()),
            createVNode(_component_Badge, null, {
              default: withCtx(() => [..._cache[125] || (_cache[125] = [
                createTextVNode("Required", -1)
              ])]),
              _: 1
            }),
            _cache[129] || (_cache[129] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("The GPIO pin connected to "),
                createBaseVNode("code", null, "CI"),
                createTextVNode(" on the first LED in the chain.")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[132] || (_cache[132] = createBaseVNode("code", null, "data_pin", -1)),
            _cache[133] || (_cache[133] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[130] || (_cache[130] = [
                createTextVNode("Pin", -1)
              ])]),
              _: 1
            }),
            _cache[134] || (_cache[134] = createTextVNode()),
            createVNode(_component_Badge, null, {
              default: withCtx(() => [..._cache[131] || (_cache[131] = [
                createTextVNode("Required", -1)
              ])]),
              _: 1
            }),
            _cache[135] || (_cache[135] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("The GPIO pin connected to "),
                createBaseVNode("code", null, "DI"),
                createTextVNode(" on the first LED in the chain.")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[137] || (_cache[137] = createBaseVNode("code", null, "default_brightness", -1)),
            _cache[138] || (_cache[138] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[136] || (_cache[136] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[139] || (_cache[139] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The initial global brightness level (independent of the RGB data), from 0 to 31."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "31")
              ])
            ], -1))
          ])
        ])
      ])
    ]),
    _cache[1112] || (_cache[1112] = createBaseVNode("h2", {
      id: "audio",
      tabindex: "-1"
    }, [
      createTextVNode("Audio "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#audio",
        "aria-label": 'Permalink to "Audio {#audio}"'
      }, "​")
    ], -1)),
    _cache[1113] || (_cache[1113] = createBaseVNode("p", null, [
      createTextVNode("Configures the "),
      createBaseVNode("a", { href: "./features/audio" }, "Audio"),
      createTextVNode(" feature.")
    ], -1)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[177] || (_cache[177] = createBaseVNode("code", null, "audio", -1)),
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _cache[149] || (_cache[149] = createBaseVNode("code", null, "default", -1)),
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _cache[142] || (_cache[142] = createBaseVNode("code", null, "on", -1)),
                _cache[143] || (_cache[143] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[141] || (_cache[141] = [
                    createTextVNode("Boolean", -1)
                  ])]),
                  _: 1
                }),
                _cache[144] || (_cache[144] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The default audio enabled state."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "true")
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[146] || (_cache[146] = createBaseVNode("code", null, "clicky", -1)),
                _cache[147] || (_cache[147] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[145] || (_cache[145] = [
                    createTextVNode("Boolean", -1)
                  ])]),
                  _: 1
                }),
                _cache[148] || (_cache[148] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The default audio clicky enabled state."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "true")
                  ])
                ], -1))
              ])
            ])
          ]),
          createBaseVNode("li", null, [
            _cache[151] || (_cache[151] = createBaseVNode("code", null, "driver", -1)),
            _cache[152] || (_cache[152] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[150] || (_cache[150] = [
                createTextVNode("String", -1)
              ])]),
              _: 1
            }),
            _cache[153] || (_cache[153] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("The driver to use. Must be one of "),
                createBaseVNode("code", null, "dac_additive"),
                createTextVNode(", "),
                createBaseVNode("code", null, "dac_basic"),
                createTextVNode(", "),
                createBaseVNode("code", null, "pwm_software"),
                createTextVNode(", "),
                createBaseVNode("code", null, "pwm_hardware"),
                createTextVNode(".")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[155] || (_cache[155] = createBaseVNode("code", null, "macro_beep", -1)),
            _cache[156] || (_cache[156] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[154] || (_cache[154] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[157] || (_cache[157] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("Play a short beep for "),
                createBaseVNode("code", null, "\\a"),
                createTextVNode(" (ASCII "),
                createBaseVNode("code", null, "BEL"),
                createTextVNode(") characters in Send String macros.")
              ]),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[160] || (_cache[160] = createBaseVNode("code", null, "pins", -1)),
            _cache[161] || (_cache[161] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[158] || (_cache[158] = [
                createTextVNode("Array: Pin", -1)
              ])]),
              _: 1
            }),
            _cache[162] || (_cache[162] = createTextVNode()),
            createVNode(_component_Badge, null, {
              default: withCtx(() => [..._cache[159] || (_cache[159] = [
                createTextVNode("Required", -1)
              ])]),
              _: 1
            }),
            _cache[163] || (_cache[163] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The GPIO pin(s) connected to the speaker(s).")
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[172] || (_cache[172] = createBaseVNode("code", null, "power_control", -1)),
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _cache[165] || (_cache[165] = createBaseVNode("code", null, "on_state", -1)),
                _cache[166] || (_cache[166] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[164] || (_cache[164] = [
                    createTextVNode("0|1", -1)
                  ])]),
                  _: 1
                }),
                _cache[167] || (_cache[167] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The logical GPIO state required to turn the speaker on."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "1"),
                    createTextVNode(" (on = high)")
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[169] || (_cache[169] = createBaseVNode("code", null, "pin", -1)),
                _cache[170] || (_cache[170] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[168] || (_cache[168] = [
                    createTextVNode("Pin", -1)
                  ])]),
                  _: 1
                }),
                _cache[171] || (_cache[171] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The GPIO pin connected to speaker power circuit.")
                ], -1))
              ])
            ])
          ]),
          createBaseVNode("li", null, [
            _cache[174] || (_cache[174] = createBaseVNode("code", null, "voices", -1)),
            _cache[175] || (_cache[175] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[173] || (_cache[173] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[176] || (_cache[176] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Use multiple audio voices."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ])
        ])
      ])
    ]),
    _cache[1114] || (_cache[1114] = createBaseVNode("h2", {
      id: "backlight",
      tabindex: "-1"
    }, [
      createTextVNode("Backlight "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#backlight",
        "aria-label": 'Permalink to "Backlight {#backlight}"'
      }, "​")
    ], -1)),
    _cache[1115] || (_cache[1115] = createBaseVNode("p", null, [
      createTextVNode("Configures the "),
      createBaseVNode("a", { href: "./features/backlight" }, "Backlight"),
      createTextVNode(" feature.")
    ], -1)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[227] || (_cache[227] = createBaseVNode("code", null, "backlight", -1)),
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _cache[179] || (_cache[179] = createBaseVNode("code", null, "as_caps_lock", -1)),
            _cache[180] || (_cache[180] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[178] || (_cache[178] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[181] || (_cache[181] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Use the backlight as a Caps Lock indicator."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[183] || (_cache[183] = createBaseVNode("code", null, "breathing", -1)),
            _cache[184] || (_cache[184] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[182] || (_cache[182] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[185] || (_cache[185] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Whether backlight breathing is enabled."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[187] || (_cache[187] = createBaseVNode("code", null, "breathing_period", -1)),
            _cache[188] || (_cache[188] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[186] || (_cache[186] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[189] || (_cache[189] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The length of one backlight breathing cycle in seconds."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "6"),
                createTextVNode(" (6 seconds)")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[202] || (_cache[202] = createBaseVNode("code", null, "default", -1)),
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _cache[191] || (_cache[191] = createBaseVNode("code", null, "on", -1)),
                _cache[192] || (_cache[192] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[190] || (_cache[190] = [
                    createTextVNode("Boolean", -1)
                  ])]),
                  _: 1
                }),
                _cache[193] || (_cache[193] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The default backlight enabled state."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "true")
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[195] || (_cache[195] = createBaseVNode("code", null, "breathing", -1)),
                _cache[196] || (_cache[196] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[194] || (_cache[194] = [
                    createTextVNode("Boolean", -1)
                  ])]),
                  _: 1
                }),
                _cache[197] || (_cache[197] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The default backlight breathing state."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "false")
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[199] || (_cache[199] = createBaseVNode("code", null, "brightness", -1)),
                _cache[200] || (_cache[200] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[198] || (_cache[198] = [
                    createTextVNode("Number", -1)
                  ])]),
                  _: 1
                }),
                _cache[201] || (_cache[201] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The default brightness level."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "max_brightness")
                  ])
                ], -1))
              ])
            ])
          ]),
          createBaseVNode("li", null, [
            _cache[204] || (_cache[204] = createBaseVNode("code", null, "driver", -1)),
            _cache[205] || (_cache[205] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[203] || (_cache[203] = [
                createTextVNode("String", -1)
              ])]),
              _: 1
            }),
            _cache[206] || (_cache[206] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("The driver to use. Must be one of "),
                createBaseVNode("code", null, "custom"),
                createTextVNode(", "),
                createBaseVNode("code", null, "pwm"),
                createTextVNode(", "),
                createBaseVNode("code", null, "software"),
                createTextVNode(", "),
                createBaseVNode("code", null, "timer"),
                createTextVNode(".")
              ]),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, '"pwm"')
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[208] || (_cache[208] = createBaseVNode("code", null, "levels", -1)),
            _cache[209] || (_cache[209] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[207] || (_cache[207] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[210] || (_cache[210] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The number of brightness levels (excluding off), from 1 to 31."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "3")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[212] || (_cache[212] = createBaseVNode("code", null, "max_brightness", -1)),
            _cache[213] || (_cache[213] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[211] || (_cache[211] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[214] || (_cache[214] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The maximum PWM value which brightness is scaled to, from 0 to 255."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "255")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[216] || (_cache[216] = createBaseVNode("code", null, "on_state", -1)),
            _cache[217] || (_cache[217] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[215] || (_cache[215] = [
                createTextVNode("0|1", -1)
              ])]),
              _: 1
            }),
            _cache[218] || (_cache[218] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The logical GPIO state required to turn the LEDs on."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "1"),
                createTextVNode(" (on = high)")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[220] || (_cache[220] = createBaseVNode("code", null, "pin", -1)),
            _cache[221] || (_cache[221] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[219] || (_cache[219] = [
                createTextVNode("Pin", -1)
              ])]),
              _: 1
            }),
            _cache[222] || (_cache[222] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The GPIO pin connected to the backlight circuit.")
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[224] || (_cache[224] = createBaseVNode("code", null, "pins", -1)),
            _cache[225] || (_cache[225] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[223] || (_cache[223] = [
                createTextVNode("Array: Pin", -1)
              ])]),
              _: 1
            }),
            _cache[226] || (_cache[226] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("A list of GPIO pins connected to the backlight LEDs ("),
                createBaseVNode("code", null, "software"),
                createTextVNode(" and "),
                createBaseVNode("code", null, "timer"),
                createTextVNode(" drivers only).")
              ])
            ], -1))
          ])
        ])
      ])
    ]),
    _cache[1116] || (_cache[1116] = createBaseVNode("h2", {
      id: "battery",
      tabindex: "-1"
    }, [
      createTextVNode("Battery "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#battery",
        "aria-label": 'Permalink to "Battery"'
      }, "​")
    ], -1)),
    _cache[1117] || (_cache[1117] = createBaseVNode("p", null, [
      createTextVNode("Configures the "),
      createBaseVNode("a", { href: "./features/battery" }, "Battery"),
      createTextVNode(" feature.")
    ], -1)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[261] || (_cache[261] = createBaseVNode("code", null, "battery", -1)),
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _cache[250] || (_cache[250] = createBaseVNode("code", null, "adc", -1)),
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _cache[230] || (_cache[230] = createBaseVNode("code", null, "pin", -1)),
                _cache[231] || (_cache[231] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[228] || (_cache[228] = [
                    createTextVNode("Pin", -1)
                  ])]),
                  _: 1
                }),
                _cache[232] || (_cache[232] = createTextVNode()),
                createVNode(_component_Badge, null, {
                  default: withCtx(() => [..._cache[229] || (_cache[229] = [
                    createTextVNode("Required", -1)
                  ])]),
                  _: 1
                }),
                _cache[233] || (_cache[233] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The GPIO pin connected to the voltage divider.")
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[235] || (_cache[235] = createBaseVNode("code", null, "reference_voltage", -1)),
                _cache[236] || (_cache[236] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[234] || (_cache[234] = [
                    createTextVNode("Number", -1)
                  ])]),
                  _: 1
                }),
                _cache[237] || (_cache[237] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The ADC reverence voltage, in millivolts."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "3300")
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[239] || (_cache[239] = createBaseVNode("code", null, "divider_r1", -1)),
                _cache[240] || (_cache[240] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[238] || (_cache[238] = [
                    createTextVNode("Number", -1)
                  ])]),
                  _: 1
                }),
                _cache[241] || (_cache[241] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The voltage divider resistance, in kOhm. Set to 0 to disable."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "100")
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[243] || (_cache[243] = createBaseVNode("code", null, "divider_r2", -1)),
                _cache[244] || (_cache[244] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[242] || (_cache[242] = [
                    createTextVNode("Number", -1)
                  ])]),
                  _: 1
                }),
                _cache[245] || (_cache[245] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The voltage divider resistance, in kOhm. Set to 0 to disable."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "100")
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[247] || (_cache[247] = createBaseVNode("code", null, "resolution", -1)),
                _cache[248] || (_cache[248] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[246] || (_cache[246] = [
                    createTextVNode("Number", -1)
                  ])]),
                  _: 1
                }),
                _cache[249] || (_cache[249] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The ADC resolution configured for the ADC Driver."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "10")
                  ])
                ], -1))
              ])
            ])
          ]),
          createBaseVNode("li", null, [
            _cache[253] || (_cache[253] = createBaseVNode("code", null, "driver", -1)),
            _cache[254] || (_cache[254] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[251] || (_cache[251] = [
                createTextVNode("String", -1)
              ])]),
              _: 1
            }),
            _cache[255] || (_cache[255] = createTextVNode()),
            createVNode(_component_Badge, null, {
              default: withCtx(() => [..._cache[252] || (_cache[252] = [
                createTextVNode("Required", -1)
              ])]),
              _: 1
            }),
            _cache[256] || (_cache[256] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("The driver to use. Must be one of "),
                createBaseVNode("code", null, "adc"),
                createTextVNode(", "),
                createBaseVNode("code", null, "custom"),
                createTextVNode(", "),
                createBaseVNode("code", null, "vendor"),
                createTextVNode(".")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[258] || (_cache[258] = createBaseVNode("code", null, "sample_interval", -1)),
            _cache[259] || (_cache[259] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[257] || (_cache[257] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[260] || (_cache[260] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The delay between sampling the battery in milliseconds."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "30000"),
                createTextVNode(" (30 s)")
              ])
            ], -1))
          ])
        ])
      ])
    ]),
    _cache[1118] || (_cache[1118] = createBaseVNode("h2", {
      id: "bluetooth",
      tabindex: "-1"
    }, [
      createTextVNode("Wireless/Bluetooth "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#bluetooth",
        "aria-label": 'Permalink to "Wireless/Bluetooth {#bluetooth}"'
      }, "​")
    ], -1)),
    _cache[1119] || (_cache[1119] = createBaseVNode("p", null, [
      createTextVNode("Configures the "),
      createBaseVNode("a", { href: "./features/wireless" }, "Wireless"),
      createTextVNode(" feature.")
    ], -1)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[266] || (_cache[266] = createBaseVNode("code", null, "bluetooth", -1)),
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _cache[263] || (_cache[263] = createBaseVNode("code", null, "driver", -1)),
            _cache[264] || (_cache[264] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[262] || (_cache[262] = [
                createTextVNode("String", -1)
              ])]),
              _: 1
            }),
            _cache[265] || (_cache[265] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("The driver to use. Must be one of "),
                createBaseVNode("code", null, "custom"),
                createTextVNode(", "),
                createBaseVNode("code", null, "bluefruit_le"),
                createTextVNode(", "),
                createBaseVNode("code", null, "rn42"),
                createTextVNode(".")
              ])
            ], -1))
          ])
        ])
      ])
    ]),
    _cache[1120] || (_cache[1120] = createBaseVNode("h2", {
      id: "bootmagic",
      tabindex: "-1"
    }, [
      createTextVNode("Bootmagic "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#bootmagic",
        "aria-label": 'Permalink to "Bootmagic {#bootmagic}"'
      }, "​")
    ], -1)),
    _cache[1121] || (_cache[1121] = createBaseVNode("p", null, [
      createTextVNode("Configures the "),
      createBaseVNode("a", { href: "./features/bootmagic" }, "Bootmagic"),
      createTextVNode(" feature.")
    ], -1)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[275] || (_cache[275] = createBaseVNode("code", null, "bootmagic", -1)),
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _cache[268] || (_cache[268] = createBaseVNode("code", null, "enabled", -1)),
            _cache[269] || (_cache[269] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[267] || (_cache[267] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[270] || (_cache[270] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Enables the Bootmagic feature."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[272] || (_cache[272] = createBaseVNode("code", null, "matrix", -1)),
            _cache[273] || (_cache[273] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[271] || (_cache[271] = [
                createTextVNode("Matrix", -1)
              ])]),
              _: 1
            }),
            _cache[274] || (_cache[274] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The matrix position of the key to check during startup. This should generally be set to the (physically) top left key."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "[0, 0]")
              ])
            ], -1))
          ])
        ])
      ])
    ]),
    _cache[1122] || (_cache[1122] = createBaseVNode("h2", {
      id: "caps-word",
      tabindex: "-1"
    }, [
      createTextVNode("Caps Word "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#caps-word",
        "aria-label": 'Permalink to "Caps Word {#caps-word}"'
      }, "​")
    ], -1)),
    _cache[1123] || (_cache[1123] = createBaseVNode("p", null, [
      createTextVNode("Configures the "),
      createBaseVNode("a", { href: "./features/caps_word" }, "Caps Word"),
      createTextVNode(" feature.")
    ], -1)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[296] || (_cache[296] = createBaseVNode("code", null, "caps_word", -1)),
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _cache[277] || (_cache[277] = createBaseVNode("code", null, "both_shifts_turns_on", -1)),
            _cache[278] || (_cache[278] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[276] || (_cache[276] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[279] || (_cache[279] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Activate Caps Word by pressing both Shift keys."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[281] || (_cache[281] = createBaseVNode("code", null, "double_tap_shift_turns_on", -1)),
            _cache[282] || (_cache[282] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[280] || (_cache[280] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[283] || (_cache[283] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Activate Caps Word by pressing Left Shift twice."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[285] || (_cache[285] = createBaseVNode("code", null, "enabled", -1)),
            _cache[286] || (_cache[286] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[284] || (_cache[284] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[287] || (_cache[287] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Enables the Caps Word feature."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[289] || (_cache[289] = createBaseVNode("code", null, "idle_timeout", -1)),
            _cache[290] || (_cache[290] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[288] || (_cache[288] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[291] || (_cache[291] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The amount of time before Caps Word automatically deactivates in milliseconds."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "5000"),
                createTextVNode(" (5 seconds)")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[293] || (_cache[293] = createBaseVNode("code", null, "invert_on_shift", -1)),
            _cache[294] || (_cache[294] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[292] || (_cache[292] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[295] || (_cache[295] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Invert shift state instead of deactivating Caps Word when Shift is pressed."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ])
        ])
      ])
    ]),
    _cache[1124] || (_cache[1124] = createBaseVNode("h2", {
      id: "combo",
      tabindex: "-1"
    }, [
      createTextVNode("Combo "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#combo",
        "aria-label": 'Permalink to "Combo {#combo}"'
      }, "​")
    ], -1)),
    _cache[1125] || (_cache[1125] = createBaseVNode("p", null, [
      createTextVNode("Configures the "),
      createBaseVNode("a", { href: "./features/combo" }, "Combo"),
      createTextVNode(" feature.")
    ], -1)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[301] || (_cache[301] = createBaseVNode("code", null, "combo", -1)),
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _cache[298] || (_cache[298] = createBaseVNode("code", null, "term", -1)),
            _cache[299] || (_cache[299] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[297] || (_cache[297] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[300] || (_cache[300] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The amount of time to recognize a combo in milliseconds."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "50"),
                createTextVNode(" (50 ms)")
              ])
            ], -1))
          ])
        ])
      ])
    ]),
    _cache[1126] || (_cache[1126] = createBaseVNode("h2", {
      id: "dip-switch",
      tabindex: "-1"
    }, [
      createTextVNode("DIP Switches "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#dip-switch",
        "aria-label": 'Permalink to "DIP Switches {#dip-switch}"'
      }, "​")
    ], -1)),
    _cache[1127] || (_cache[1127] = createBaseVNode("p", null, [
      createTextVNode("Configures the "),
      createBaseVNode("a", { href: "./features/dip_switch" }, "DIP Switches"),
      createTextVNode(" feature.")
    ], -1)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[314] || (_cache[314] = createBaseVNode("code", null, "dip_switch", -1)),
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _cache[303] || (_cache[303] = createBaseVNode("code", null, "enabled", -1)),
            _cache[304] || (_cache[304] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[302] || (_cache[302] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[305] || (_cache[305] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Enable the DIP Switches feature."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[307] || (_cache[307] = createBaseVNode("code", null, "pins", -1)),
            _cache[308] || (_cache[308] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[306] || (_cache[306] = [
                createTextVNode("Array: Pin", -1)
              ])]),
              _: 1
            }),
            _cache[309] || (_cache[309] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "A list of GPIO pins connected to the MCU.")
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[311] || (_cache[311] = createBaseVNode("code", null, "matrix_grid", -1)),
            _cache[312] || (_cache[312] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[310] || (_cache[310] = [
                createTextVNode("Array: Matrix", -1)
              ])]),
              _: 1
            }),
            _cache[313] || (_cache[313] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "A list of matrix locations in the key matrix."),
              createBaseVNode("li", null, [
                createTextVNode("Example: "),
                createBaseVNode("code", null, "[ [0,6], [1,6], [2,6] ]")
              ])
            ], -1))
          ])
        ])
      ])
    ]),
    _cache[1128] || (_cache[1128] = createBaseVNode("h2", {
      id: "eeprom",
      tabindex: "-1"
    }, [
      createTextVNode("EEPROM "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#eeprom",
        "aria-label": 'Permalink to "EEPROM {#eeprom}"'
      }, "​")
    ], -1)),
    _cache[1129] || (_cache[1129] = createBaseVNode("p", null, [
      createTextVNode("Configures the "),
      createBaseVNode("a", { href: "./drivers/eeprom" }, "EEPROM"),
      createTextVNode(" driver.")
    ], -1)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[332] || (_cache[332] = createBaseVNode("code", null, "eeprom", -1)),
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _cache[316] || (_cache[316] = createBaseVNode("code", null, "driver", -1)),
            _cache[317] || (_cache[317] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[315] || (_cache[315] = [
                createTextVNode("String", -1)
              ])]),
              _: 1
            }),
            _cache[318] || (_cache[318] = createStaticVNode("<ul><li>The EEPROM backend to use. Must be one of <code>custom</code>, <code>i2c</code>, <code>legacy_stm32_flash</code>, <code>spi</code>, <code>transient</code>, <code>vendor</code>, <code>wear_leveling</code>.</li><li>Default: <code>&quot;vendor&quot;</code></li></ul>", 1))
          ]),
          createBaseVNode("li", null, [
            _cache[331] || (_cache[331] = createBaseVNode("code", null, "wear_leveling", -1)),
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _cache[320] || (_cache[320] = createBaseVNode("code", null, "driver", -1)),
                _cache[321] || (_cache[321] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[319] || (_cache[319] = [
                    createTextVNode("String", -1)
                  ])]),
                  _: 1
                }),
                _cache[322] || (_cache[322] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, [
                    createTextVNode("The driver to use. Must be one of "),
                    createBaseVNode("code", null, "embedded_flash"),
                    createTextVNode(", "),
                    createBaseVNode("code", null, "legacy"),
                    createTextVNode(", "),
                    createBaseVNode("code", null, "rp2040_flash"),
                    createTextVNode(", "),
                    createBaseVNode("code", null, "spi_flash"),
                    createTextVNode(", "),
                    createBaseVNode("code", null, "custom"),
                    createTextVNode(".")
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[324] || (_cache[324] = createBaseVNode("code", null, "backing_size", -1)),
                _cache[325] || (_cache[325] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[323] || (_cache[323] = [
                    createTextVNode("Number", -1)
                  ])]),
                  _: 1
                }),
                _cache[326] || (_cache[326] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "Number of bytes used by the wear-leveling algorithm for its underlying storage, and needs to be a multiple of the logical size.")
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[328] || (_cache[328] = createBaseVNode("code", null, "logical_size", -1)),
                _cache[329] || (_cache[329] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[327] || (_cache[327] = [
                    createTextVNode("Number", -1)
                  ])]),
                  _: 1
                }),
                _cache[330] || (_cache[330] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "Number of bytes “exposed” to the rest of QMK and denotes the size of the usable EEPROM.")
                ], -1))
              ])
            ])
          ])
        ])
      ])
    ]),
    _cache[1130] || (_cache[1130] = createBaseVNode("h2", {
      id: "encoder",
      tabindex: "-1"
    }, [
      createTextVNode("Encoder "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#encoder",
        "aria-label": 'Permalink to "Encoder {#encoder}"'
      }, "​")
    ], -1)),
    _cache[1131] || (_cache[1131] = createBaseVNode("p", null, [
      createTextVNode("Configures the "),
      createBaseVNode("a", { href: "./features/encoders" }, "Encoder"),
      createTextVNode(" feature.")
    ], -1)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[353] || (_cache[353] = createBaseVNode("code", null, "encoder", -1)),
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _cache[351] || (_cache[351] = createBaseVNode("code", null, "rotary", -1)),
            _cache[352] || (_cache[352] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[333] || (_cache[333] = [
                createTextVNode("Array: Object", -1)
              ])]),
              _: 1
            }),
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _cache[350] || (_cache[350] = createTextVNode("A list of encoder objects. ", -1)),
                createBaseVNode("ul", null, [
                  createBaseVNode("li", null, [
                    _cache[336] || (_cache[336] = createBaseVNode("code", null, "pin_a", -1)),
                    _cache[337] || (_cache[337] = createTextVNode()),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [..._cache[334] || (_cache[334] = [
                        createTextVNode("Pin", -1)
                      ])]),
                      _: 1
                    }),
                    _cache[338] || (_cache[338] = createTextVNode()),
                    createVNode(_component_Badge, null, {
                      default: withCtx(() => [..._cache[335] || (_cache[335] = [
                        createTextVNode("Required", -1)
                      ])]),
                      _: 1
                    }),
                    _cache[339] || (_cache[339] = createBaseVNode("ul", null, [
                      createBaseVNode("li", null, [
                        createTextVNode("The GPIO pin connected to the encoder's "),
                        createBaseVNode("code", null, "A"),
                        createTextVNode(" pin.")
                      ])
                    ], -1))
                  ]),
                  createBaseVNode("li", null, [
                    _cache[342] || (_cache[342] = createBaseVNode("code", null, "pin_b", -1)),
                    _cache[343] || (_cache[343] = createTextVNode()),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [..._cache[340] || (_cache[340] = [
                        createTextVNode("Pin", -1)
                      ])]),
                      _: 1
                    }),
                    _cache[344] || (_cache[344] = createTextVNode()),
                    createVNode(_component_Badge, null, {
                      default: withCtx(() => [..._cache[341] || (_cache[341] = [
                        createTextVNode("Required", -1)
                      ])]),
                      _: 1
                    }),
                    _cache[345] || (_cache[345] = createBaseVNode("ul", null, [
                      createBaseVNode("li", null, [
                        createTextVNode("The GPIO pin connected to the encoder's "),
                        createBaseVNode("code", null, "B"),
                        createTextVNode(" pin.")
                      ])
                    ], -1))
                  ]),
                  createBaseVNode("li", null, [
                    _cache[347] || (_cache[347] = createBaseVNode("code", null, "resolution", -1)),
                    _cache[348] || (_cache[348] = createTextVNode()),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [..._cache[346] || (_cache[346] = [
                        createTextVNode("Number", -1)
                      ])]),
                      _: 1
                    }),
                    _cache[349] || (_cache[349] = createBaseVNode("ul", null, [
                      createBaseVNode("li", null, "The number of edge transitions on both pins required to register an input."),
                      createBaseVNode("li", null, [
                        createTextVNode("Default: "),
                        createBaseVNode("code", null, "4")
                      ])
                    ], -1))
                  ])
                ])
              ])
            ])
          ])
        ])
      ])
    ]),
    _cache[1132] || (_cache[1132] = createBaseVNode("h2", {
      id: "host",
      tabindex: "-1"
    }, [
      createTextVNode("Host "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#host",
        "aria-label": 'Permalink to "Host {#host}"'
      }, "​")
    ], -1)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[359] || (_cache[359] = createBaseVNode("code", null, "host", -1)),
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _cache[358] || (_cache[358] = createBaseVNode("code", null, "default", -1)),
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _cache[355] || (_cache[355] = createBaseVNode("code", null, "nkro", -1)),
                _cache[356] || (_cache[356] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[354] || (_cache[354] = [
                    createTextVNode("Boolean", -1)
                  ])]),
                  _: 1
                }),
                _cache[357] || (_cache[357] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The default nkro state."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "false")
                  ])
                ], -1))
              ])
            ])
          ])
        ])
      ])
    ]),
    _cache[1133] || (_cache[1133] = createBaseVNode("h2", {
      id: "indicators",
      tabindex: "-1"
    }, [
      createTextVNode("Indicators "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#indicators",
        "aria-label": 'Permalink to "Indicators {#indicators}"'
      }, "​")
    ], -1)),
    _cache[1134] || (_cache[1134] = createBaseVNode("p", null, [
      createTextVNode("Configures the "),
      createBaseVNode("a", { href: "./features/led_indicators" }, "LED Indicators"),
      createTextVNode(" feature.")
    ], -1)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[384] || (_cache[384] = createBaseVNode("code", null, "indicators", -1)),
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _cache[361] || (_cache[361] = createBaseVNode("code", null, "caps_lock", -1)),
            _cache[362] || (_cache[362] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[360] || (_cache[360] = [
                createTextVNode("Pin", -1)
              ])]),
              _: 1
            }),
            _cache[363] || (_cache[363] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The GPIO pin connected to the Caps Lock LED.")
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[365] || (_cache[365] = createBaseVNode("code", null, "compose", -1)),
            _cache[366] || (_cache[366] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[364] || (_cache[364] = [
                createTextVNode("Pin", -1)
              ])]),
              _: 1
            }),
            _cache[367] || (_cache[367] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The GPIO pin connected to the Compose LED.")
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[369] || (_cache[369] = createBaseVNode("code", null, "kana", -1)),
            _cache[370] || (_cache[370] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[368] || (_cache[368] = [
                createTextVNode("Pin", -1)
              ])]),
              _: 1
            }),
            _cache[371] || (_cache[371] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The GPIO pin connected to the Kana LED.")
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[373] || (_cache[373] = createBaseVNode("code", null, "num_lock", -1)),
            _cache[374] || (_cache[374] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[372] || (_cache[372] = [
                createTextVNode("Pin", -1)
              ])]),
              _: 1
            }),
            _cache[375] || (_cache[375] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The GPIO pin connected to the Num Lock LED.")
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[377] || (_cache[377] = createBaseVNode("code", null, "on_state", -1)),
            _cache[378] || (_cache[378] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[376] || (_cache[376] = [
                createTextVNode("0|1", -1)
              ])]),
              _: 1
            }),
            _cache[379] || (_cache[379] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The logical GPIO state required to turn the LEDs on."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "1"),
                createTextVNode(" (on = high)")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[381] || (_cache[381] = createBaseVNode("code", null, "scroll_lock", -1)),
            _cache[382] || (_cache[382] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[380] || (_cache[380] = [
                createTextVNode("Pin", -1)
              ])]),
              _: 1
            }),
            _cache[383] || (_cache[383] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The GPIO pin connected to the Scroll Lock LED.")
            ], -1))
          ])
        ])
      ])
    ]),
    _cache[1135] || (_cache[1135] = createBaseVNode("h2", {
      id: "keycodes",
      tabindex: "-1"
    }, [
      createTextVNode("(Custom) Keycodes "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#keycodes",
        "aria-label": 'Permalink to "(Custom) Keycodes {#keycodes}"'
      }, "​")
    ], -1)),
    _cache[1136] || (_cache[1136] = createBaseVNode("p", null, [
      createTextVNode("Defines "),
      createBaseVNode("a", { href: "./custom_quantum_functions#definining-a-new-keycode" }, "custom keycodes"),
      createTextVNode(" for use within keymaps.")
    ], -1)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[401] || (_cache[401] = createBaseVNode("code", null, "keycodes", -1)),
        _cache[402] || (_cache[402] = createTextVNode()),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [..._cache[385] || (_cache[385] = [
            createTextVNode("Array: Object", -1)
          ])]),
          _: 1
        }),
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _cache[400] || (_cache[400] = createTextVNode("A list of keycode objects. ", -1)),
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _cache[388] || (_cache[388] = createBaseVNode("code", null, "key", -1)),
                _cache[389] || (_cache[389] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[386] || (_cache[386] = [
                    createTextVNode("String", -1)
                  ])]),
                  _: 1
                }),
                _cache[390] || (_cache[390] = createTextVNode()),
                createVNode(_component_Badge, null, {
                  default: withCtx(() => [..._cache[387] || (_cache[387] = [
                    createTextVNode("Required", -1)
                  ])]),
                  _: 1
                }),
                _cache[391] || (_cache[391] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The enum name of the custom keycode."),
                  createBaseVNode("li", null, [
                    createTextVNode("Example: "),
                    createBaseVNode("code", null, "LAYER_CHANGE_BEEP_ON")
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[393] || (_cache[393] = createBaseVNode("code", null, "label", -1)),
                _cache[394] || (_cache[394] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[392] || (_cache[392] = [
                    createTextVNode("String", -1)
                  ])]),
                  _: 1
                }),
                _cache[395] || (_cache[395] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "A short description of the custom keycode.")
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[397] || (_cache[397] = createBaseVNode("code", null, "aliases", -1)),
                _cache[398] || (_cache[398] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[396] || (_cache[396] = [
                    createTextVNode("Array: String", -1)
                  ])]),
                  _: 1
                }),
                _cache[399] || (_cache[399] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "A list of shortened names for the custom keycode."),
                  createBaseVNode("li", null, [
                    createTextVNode("Example: "),
                    createBaseVNode("code", null, '["LCBON", "LCB_ON"]')
                  ])
                ], -1))
              ])
            ])
          ])
        ])
      ])
    ]),
    _cache[1137] || (_cache[1137] = createStaticVNode('<h2 id="layouts" tabindex="-1">Layouts <a class="header-anchor" href="#layouts" aria-label="Permalink to &quot;Layouts {#layouts}&quot;">​</a></h2><p>The <code>layouts</code> portion of the dictionary contains several nested dictionaries. The outer layer consists of QMK layout names, for example <code>LAYOUT_60_ansi</code> or <code>LAYOUT_60_iso</code>.</p><p>Each key dictionary in a layout describes the physical properties of a key. If you are familiar with the Raw Data format for <a href="https://keyboard-layout-editor.com" target="_blank" rel="noreferrer">Keyboard Layout Editor</a>, you will find many of the concepts the same. Key names and layout choices are reused wherever possible, but unlike KLE each key is stateless, inheriting no properties from the keys that came before it.</p><p>All key positions and rotations are specified in relation to the top-left corner of the keyboard, and the top-left corner of each key.</p><p>The ISO enter key is represented by a 1.25u×2uh key. Renderers which utilize info.json layout data (such as <code>qmk info -l</code> and the QMK Configurator) should display this key as expected.</p>', 5)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[404] || (_cache[404] = createBaseVNode("code", null, "community_layouts", -1)),
        _cache[405] || (_cache[405] = createTextVNode()),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [..._cache[403] || (_cache[403] = [
            createTextVNode("Array: String", -1)
          ])]),
          _: 1
        }),
        _cache[406] || (_cache[406] = createBaseVNode("ul", null, [
          createBaseVNode("li", null, "A list of community layouts supported by the keyboard."),
          createBaseVNode("li", null, [
            createTextVNode("Example: "),
            createBaseVNode("code", null, '["60_ansi", "60_iso"]')
          ])
        ], -1))
      ]),
      createBaseVNode("li", null, [
        _cache[408] || (_cache[408] = createBaseVNode("code", null, "layout_aliases", -1)),
        _cache[409] || (_cache[409] = createTextVNode()),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [..._cache[407] || (_cache[407] = [
            createTextVNode("Object: String", -1)
          ])]),
          _: 1
        }),
        _cache[410] || (_cache[410] = createStaticVNode('<ul><li>A mapping of layout aliases to layout definitions.</li><li>Example:</li></ul><div class="language-json vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">json</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">{</span></span>\n<span class="line"><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">    &quot;LAYOUT_ansi&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">: </span><span style="--shiki-light:#032F62;--shiki-dark:#9ECBFF;">&quot;LAYOUT_60_ansi&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">,</span></span>\n<span class="line"><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">    &quot;LAYOUT_iso&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">: </span><span style="--shiki-light:#032F62;--shiki-dark:#9ECBFF;">&quot;LAYOUT_60_iso&quot;</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">}</span></span></code></pre></div>', 2))
      ]),
      createBaseVNode("li", null, [
        _cache[471] || (_cache[471] = createBaseVNode("code", null, "layouts", -1)),
        _cache[472] || (_cache[472] = createTextVNode()),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [..._cache[411] || (_cache[411] = [
            createTextVNode("Object", -1)
          ])]),
          _: 1
        }),
        createBaseVNode("ul", null, [
          _cache[470] || (_cache[470] = createBaseVNode("li", null, "A dictionary of layouts supported by the keyboard.", -1)),
          createBaseVNode("li", null, [
            _cache[468] || (_cache[468] = createBaseVNode("code", null, "LAYOUT_<layout_name>", -1)),
            _cache[469] || (_cache[469] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[412] || (_cache[412] = [
                createTextVNode("Object", -1)
              ])]),
              _: 1
            }),
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _cache[466] || (_cache[466] = createBaseVNode("code", null, "layout", -1)),
                _cache[467] || (_cache[467] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[413] || (_cache[413] = [
                    createTextVNode("Array: Object", -1)
                  ])]),
                  _: 1
                }),
                createBaseVNode("ul", null, [
                  createBaseVNode("li", null, [
                    _cache[465] || (_cache[465] = createTextVNode("A list of key dictionaries comprising the layout. Each key dictionary contains: ", -1)),
                    createBaseVNode("ul", null, [
                      createBaseVNode("li", null, [
                        _cache[416] || (_cache[416] = createBaseVNode("code", null, "matrix", -1)),
                        _cache[417] || (_cache[417] = createTextVNode()),
                        createVNode(_component_Badge, { type: "info" }, {
                          default: withCtx(() => [..._cache[414] || (_cache[414] = [
                            createTextVNode("Matrix", -1)
                          ])]),
                          _: 1
                        }),
                        _cache[418] || (_cache[418] = createTextVNode()),
                        createVNode(_component_Badge, null, {
                          default: withCtx(() => [..._cache[415] || (_cache[415] = [
                            createTextVNode("Required", -1)
                          ])]),
                          _: 1
                        }),
                        _cache[419] || (_cache[419] = createBaseVNode("ul", null, [
                          createBaseVNode("li", null, "The matrix position for the key."),
                          createBaseVNode("li", null, [
                            createTextVNode("Example: "),
                            createBaseVNode("code", null, "[0, 4]"),
                            createTextVNode(" (row 0, column 4)")
                          ])
                        ], -1))
                      ]),
                      createBaseVNode("li", null, [
                        _cache[422] || (_cache[422] = createBaseVNode("code", null, "x", -1)),
                        _cache[423] || (_cache[423] = createTextVNode()),
                        createVNode(_component_Badge, { type: "info" }, {
                          default: withCtx(() => [..._cache[420] || (_cache[420] = [
                            createTextVNode("KeyUnit", -1)
                          ])]),
                          _: 1
                        }),
                        _cache[424] || (_cache[424] = createTextVNode()),
                        createVNode(_component_Badge, null, {
                          default: withCtx(() => [..._cache[421] || (_cache[421] = [
                            createTextVNode("Required", -1)
                          ])]),
                          _: 1
                        }),
                        _cache[425] || (_cache[425] = createBaseVNode("ul", null, [
                          createBaseVNode("li", null, "The absolute position of the key in the horizontal axis, in key units.")
                        ], -1))
                      ]),
                      createBaseVNode("li", null, [
                        _cache[428] || (_cache[428] = createBaseVNode("code", null, "y", -1)),
                        _cache[429] || (_cache[429] = createTextVNode()),
                        createVNode(_component_Badge, { type: "info" }, {
                          default: withCtx(() => [..._cache[426] || (_cache[426] = [
                            createTextVNode("KeyUnit", -1)
                          ])]),
                          _: 1
                        }),
                        _cache[430] || (_cache[430] = createTextVNode()),
                        createVNode(_component_Badge, null, {
                          default: withCtx(() => [..._cache[427] || (_cache[427] = [
                            createTextVNode("Required", -1)
                          ])]),
                          _: 1
                        }),
                        _cache[431] || (_cache[431] = createBaseVNode("ul", null, [
                          createBaseVNode("li", null, "The absolute position of the key in the vertical axis, in key units.")
                        ], -1))
                      ]),
                      createBaseVNode("li", null, [
                        _cache[433] || (_cache[433] = createBaseVNode("code", null, "h", -1)),
                        _cache[434] || (_cache[434] = createTextVNode()),
                        createVNode(_component_Badge, { type: "info" }, {
                          default: withCtx(() => [..._cache[432] || (_cache[432] = [
                            createTextVNode("KeyUnit", -1)
                          ])]),
                          _: 1
                        }),
                        _cache[435] || (_cache[435] = createBaseVNode("ul", null, [
                          createBaseVNode("li", null, "The height of the key, in key units."),
                          createBaseVNode("li", null, [
                            createTextVNode("Default: "),
                            createBaseVNode("code", null, "1"),
                            createTextVNode(" (1u)")
                          ])
                        ], -1))
                      ]),
                      createBaseVNode("li", null, [
                        _cache[437] || (_cache[437] = createBaseVNode("code", null, "hand", -1)),
                        _cache[438] || (_cache[438] = createTextVNode()),
                        createVNode(_component_Badge, { type: "info" }, {
                          default: withCtx(() => [..._cache[436] || (_cache[436] = [
                            createTextVNode("String", -1)
                          ])]),
                          _: 1
                        }),
                        _cache[439] || (_cache[439] = createBaseVNode("ul", null, [
                          createBaseVNode("li", null, [
                            createTextVNode("The handedness of the key for Chordal Hold, either "),
                            createBaseVNode("code", null, '"L"'),
                            createTextVNode(" (left hand), "),
                            createBaseVNode("code", null, '"R"'),
                            createTextVNode(" (right hand), or "),
                            createBaseVNode("code", null, '"*"'),
                            createTextVNode(" (either or exempted handedness).")
                          ])
                        ], -1))
                      ]),
                      createBaseVNode("li", null, [
                        _cache[441] || (_cache[441] = createBaseVNode("code", null, "label", -1)),
                        _cache[442] || (_cache[442] = createTextVNode()),
                        createVNode(_component_Badge, { type: "info" }, {
                          default: withCtx(() => [..._cache[440] || (_cache[440] = [
                            createTextVNode("String", -1)
                          ])]),
                          _: 1
                        }),
                        _cache[443] || (_cache[443] = createBaseVNode("ul", null, [
                          createBaseVNode("li", null, [
                            createTextVNode("What to name the key. This is "),
                            createBaseVNode("em", null, "not"),
                            createTextVNode(" a key assignment as in the keymap, but should usually correspond to the keycode for the first layer of the default keymap.")
                          ]),
                          createBaseVNode("li", null, [
                            createTextVNode("Example: "),
                            createBaseVNode("code", null, '"Escape"')
                          ])
                        ], -1))
                      ]),
                      createBaseVNode("li", null, [
                        _cache[445] || (_cache[445] = createBaseVNode("code", null, "r", -1)),
                        _cache[446] || (_cache[446] = createTextVNode()),
                        createVNode(_component_Badge, { type: "info" }, {
                          default: withCtx(() => [..._cache[444] || (_cache[444] = [
                            createTextVNode("Number", -1)
                          ])]),
                          _: 1
                        }),
                        _cache[447] || (_cache[447] = createBaseVNode("ul", null, [
                          createBaseVNode("li", null, "The rotation angle in degrees. Currently not implemented.")
                        ], -1))
                      ]),
                      createBaseVNode("li", null, [
                        _cache[449] || (_cache[449] = createBaseVNode("code", null, "rx", -1)),
                        _cache[450] || (_cache[450] = createTextVNode()),
                        createVNode(_component_Badge, { type: "info" }, {
                          default: withCtx(() => [..._cache[448] || (_cache[448] = [
                            createTextVNode("Number", -1)
                          ])]),
                          _: 1
                        }),
                        _cache[451] || (_cache[451] = createBaseVNode("ul", null, [
                          createBaseVNode("li", null, "The absolute X position of the rotation axis. Currently not implemented.")
                        ], -1))
                      ]),
                      createBaseVNode("li", null, [
                        _cache[453] || (_cache[453] = createBaseVNode("code", null, "ry", -1)),
                        _cache[454] || (_cache[454] = createTextVNode()),
                        createVNode(_component_Badge, { type: "info" }, {
                          default: withCtx(() => [..._cache[452] || (_cache[452] = [
                            createTextVNode("Number", -1)
                          ])]),
                          _: 1
                        }),
                        _cache[455] || (_cache[455] = createBaseVNode("ul", null, [
                          createBaseVNode("li", null, "The absolute Y position of the rotation axis. Currently not implemented.")
                        ], -1))
                      ]),
                      createBaseVNode("li", null, [
                        _cache[457] || (_cache[457] = createBaseVNode("code", null, "w", -1)),
                        _cache[458] || (_cache[458] = createTextVNode()),
                        createVNode(_component_Badge, { type: "info" }, {
                          default: withCtx(() => [..._cache[456] || (_cache[456] = [
                            createTextVNode("KeyUnit", -1)
                          ])]),
                          _: 1
                        }),
                        _cache[459] || (_cache[459] = createBaseVNode("ul", null, [
                          createBaseVNode("li", null, "The width of the key, in key units."),
                          createBaseVNode("li", null, [
                            createTextVNode("Default: "),
                            createBaseVNode("code", null, "1"),
                            createTextVNode(" (1u)")
                          ])
                        ], -1))
                      ]),
                      createBaseVNode("li", null, [
                        _cache[461] || (_cache[461] = createBaseVNode("code", null, "encoder", -1)),
                        _cache[462] || (_cache[462] = createTextVNode()),
                        createVNode(_component_Badge, { type: "info" }, {
                          default: withCtx(() => [..._cache[460] || (_cache[460] = [
                            createTextVNode("Number", -1)
                          ])]),
                          _: 1
                        }),
                        _cache[463] || (_cache[463] = createBaseVNode("ul", null, [
                          createBaseVNode("li", null, "The index of an encoder this key should be linked to")
                        ], -1))
                      ]),
                      _cache[464] || (_cache[464] = createBaseVNode("li", null, [
                        createTextVNode("Example: "),
                        createBaseVNode("code", null, '{"label": "Shift", "matrix": [4, 0], "x": 0, "y": 4.25, "w": 2.25}')
                      ], -1))
                    ])
                  ])
                ])
              ])
            ])
          ])
        ])
      ])
    ]),
    _cache[1138] || (_cache[1138] = createBaseVNode("h2", {
      id: "leader-key",
      tabindex: "-1"
    }, [
      createTextVNode("Leader Key "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#leader-key",
        "aria-label": 'Permalink to "Leader Key {#leader-key}"'
      }, "​")
    ], -1)),
    _cache[1139] || (_cache[1139] = createBaseVNode("p", null, [
      createTextVNode("Configures the "),
      createBaseVNode("a", { href: "./features/leader_key" }, "Leader Key"),
      createTextVNode(" feature.")
    ], -1)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[485] || (_cache[485] = createBaseVNode("code", null, "leader_key", -1)),
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _cache[474] || (_cache[474] = createBaseVNode("code", null, "timing", -1)),
            _cache[475] || (_cache[475] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[473] || (_cache[473] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[476] || (_cache[476] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("Reset the "),
                createBaseVNode("code", null, "timeout"),
                createTextVNode(" on each keypress.")
              ]),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[478] || (_cache[478] = createBaseVNode("code", null, "strict_processing", -1)),
            _cache[479] || (_cache[479] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[477] || (_cache[477] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[480] || (_cache[480] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Do not extract the tap keycodes from Layer-Tap and Mod-Tap key events."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[482] || (_cache[482] = createBaseVNode("code", null, "timeout", -1)),
            _cache[483] || (_cache[483] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[481] || (_cache[481] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[484] || (_cache[484] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The amount of time to complete a leader sequence in milliseconds."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "300"),
                createTextVNode(" (300 ms)")
              ])
            ], -1))
          ])
        ])
      ])
    ]),
    _cache[1140] || (_cache[1140] = createBaseVNode("h2", {
      id: "led-matrix",
      tabindex: "-1"
    }, [
      createTextVNode("LED Matrix "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#led-matrix",
        "aria-label": 'Permalink to "LED Matrix {#led-matrix}"'
      }, "​")
    ], -1)),
    _cache[1141] || (_cache[1141] = createBaseVNode("p", null, [
      createTextVNode("Configures the "),
      createBaseVNode("a", { href: "./features/led_matrix" }, "LED Matrix"),
      createTextVNode(" feature.")
    ], -1)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[590] || (_cache[590] = createBaseVNode("code", null, "led_matrix", -1)),
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _cache[487] || (_cache[487] = createBaseVNode("code", null, "animations", -1)),
            _cache[488] || (_cache[488] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[486] || (_cache[486] = [
                createTextVNode("Object: Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[489] || (_cache[489] = createStaticVNode('<ul><li>A dictionary of effects to enable or disable. Effects which are absent default to <code>false</code>.</li><li>Example:</li></ul><div class="language-json vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">json</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">{</span></span>\n<span class="line"><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">    &quot;alphas_mods&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">: </span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">true</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">,</span></span>\n<span class="line"><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">    &quot;breathing&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">: </span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">true</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">,</span></span>\n<span class="line"><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">    &quot;cycle_left_right&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">: </span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">false</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">}</span></span></code></pre></div>', 2))
          ]),
          createBaseVNode("li", null, [
            _cache[491] || (_cache[491] = createBaseVNode("code", null, "center_point", -1)),
            _cache[492] || (_cache[492] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[490] || (_cache[490] = [
                createTextVNode("Array: Number", -1)
              ])]),
              _: 1
            }),
            _cache[493] || (_cache[493] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The centroid (geometric center) of the LEDs. Used for certain effects."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "[112, 32]")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[495] || (_cache[495] = createBaseVNode("code", null, "flag_steps", -1)),
            _cache[496] || (_cache[496] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[494] || (_cache[494] = [
                createTextVNode("Array: Number", -1)
              ])]),
              _: 1
            }),
            _cache[497] || (_cache[497] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "A list of flag bitfields that can be cycled through."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "[255, 5, 0]")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[518] || (_cache[518] = createBaseVNode("code", null, "default", -1)),
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _cache[499] || (_cache[499] = createBaseVNode("code", null, "animation", -1)),
                _cache[500] || (_cache[500] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[498] || (_cache[498] = [
                    createTextVNode("String", -1)
                  ])]),
                  _: 1
                }),
                _cache[501] || (_cache[501] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, [
                    createTextVNode("The default effect. Must be one of "),
                    createBaseVNode("code", null, "led_matrix.animations")
                  ]),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, '"solid"')
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[503] || (_cache[503] = createBaseVNode("code", null, "on", -1)),
                _cache[504] || (_cache[504] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[502] || (_cache[502] = [
                    createTextVNode("Boolean", -1)
                  ])]),
                  _: 1
                }),
                _cache[505] || (_cache[505] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The default enabled state."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "true")
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[507] || (_cache[507] = createBaseVNode("code", null, "val", -1)),
                _cache[508] || (_cache[508] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[506] || (_cache[506] = [
                    createTextVNode("Number", -1)
                  ])]),
                  _: 1
                }),
                _cache[509] || (_cache[509] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The default brightness level."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "max_brightness")
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[511] || (_cache[511] = createBaseVNode("code", null, "speed", -1)),
                _cache[512] || (_cache[512] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[510] || (_cache[510] = [
                    createTextVNode("Number", -1)
                  ])]),
                  _: 1
                }),
                _cache[513] || (_cache[513] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The default animation speed."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "128")
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[515] || (_cache[515] = createBaseVNode("code", null, "flags", -1)),
                _cache[516] || (_cache[516] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[514] || (_cache[514] = [
                    createTextVNode("Number", -1)
                  ])]),
                  _: 1
                }),
                _cache[517] || (_cache[517] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The default LED flags."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "255")
                  ])
                ], -1))
              ])
            ])
          ]),
          createBaseVNode("li", null, [
            _cache[521] || (_cache[521] = createBaseVNode("code", null, "driver", -1)),
            _cache[522] || (_cache[522] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[519] || (_cache[519] = [
                createTextVNode("String", -1)
              ])]),
              _: 1
            }),
            _cache[523] || (_cache[523] = createTextVNode()),
            createVNode(_component_Badge, null, {
              default: withCtx(() => [..._cache[520] || (_cache[520] = [
                createTextVNode("Required", -1)
              ])]),
              _: 1
            }),
            _cache[524] || (_cache[524] = createStaticVNode("<ul><li>The driver to use. Must be one of <code>custom</code>, <code>is31fl3218</code>, <code>is31fl3731</code>, <code>is31fl3733</code>, <code>is31fl3736</code>, <code>is31fl3737</code>, <code>is31fl3741</code>, <code>is31fl3742a</code>, <code>is31fl3743a</code>, <code>is31fl3745</code>, <code>is31fl3746a</code>, <code>snled27351</code>.</li></ul>", 1))
          ]),
          createBaseVNode("li", null, [
            _cache[551] || (_cache[551] = createBaseVNode("code", null, "layout", -1)),
            _cache[552] || (_cache[552] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[525] || (_cache[525] = [
                createTextVNode("Array: Object", -1)
              ])]),
              _: 1
            }),
            _cache[553] || (_cache[553] = createTextVNode()),
            createVNode(_component_Badge, null, {
              default: withCtx(() => [..._cache[526] || (_cache[526] = [
                createTextVNode("Required", -1)
              ])]),
              _: 1
            }),
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _cache[550] || (_cache[550] = createTextVNode("List of LED configuration dictionaries. Each dictionary contains: ", -1)),
                createBaseVNode("ul", null, [
                  createBaseVNode("li", null, [
                    _cache[529] || (_cache[529] = createBaseVNode("code", null, "flags", -1)),
                    _cache[530] || (_cache[530] = createTextVNode()),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [..._cache[527] || (_cache[527] = [
                        createTextVNode("Number", -1)
                      ])]),
                      _: 1
                    }),
                    _cache[531] || (_cache[531] = createTextVNode()),
                    createVNode(_component_Badge, null, {
                      default: withCtx(() => [..._cache[528] || (_cache[528] = [
                        createTextVNode("Required", -1)
                      ])]),
                      _: 1
                    }),
                    _cache[532] || (_cache[532] = createBaseVNode("ul", null, [
                      createBaseVNode("li", null, "A bitfield of flags describing the type of LED.")
                    ], -1))
                  ]),
                  createBaseVNode("li", null, [
                    _cache[535] || (_cache[535] = createBaseVNode("code", null, "x", -1)),
                    _cache[536] || (_cache[536] = createTextVNode()),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [..._cache[533] || (_cache[533] = [
                        createTextVNode("Number", -1)
                      ])]),
                      _: 1
                    }),
                    _cache[537] || (_cache[537] = createTextVNode()),
                    createVNode(_component_Badge, null, {
                      default: withCtx(() => [..._cache[534] || (_cache[534] = [
                        createTextVNode("Required", -1)
                      ])]),
                      _: 1
                    }),
                    _cache[538] || (_cache[538] = createBaseVNode("ul", null, [
                      createBaseVNode("li", null, "The position of the LED in the horizontal axis, from 0 to 224.")
                    ], -1))
                  ]),
                  createBaseVNode("li", null, [
                    _cache[541] || (_cache[541] = createBaseVNode("code", null, "y", -1)),
                    _cache[542] || (_cache[542] = createTextVNode()),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [..._cache[539] || (_cache[539] = [
                        createTextVNode("Number", -1)
                      ])]),
                      _: 1
                    }),
                    _cache[543] || (_cache[543] = createTextVNode()),
                    createVNode(_component_Badge, null, {
                      default: withCtx(() => [..._cache[540] || (_cache[540] = [
                        createTextVNode("Required", -1)
                      ])]),
                      _: 1
                    }),
                    _cache[544] || (_cache[544] = createBaseVNode("ul", null, [
                      createBaseVNode("li", null, "The position of the LED in the vertical axis, from 0 to 64.")
                    ], -1))
                  ]),
                  createBaseVNode("li", null, [
                    _cache[546] || (_cache[546] = createBaseVNode("code", null, "matrix", -1)),
                    _cache[547] || (_cache[547] = createTextVNode()),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [..._cache[545] || (_cache[545] = [
                        createTextVNode("Matrix", -1)
                      ])]),
                      _: 1
                    }),
                    _cache[548] || (_cache[548] = createBaseVNode("ul", null, [
                      createBaseVNode("li", null, "The key matrix position associated with the LED."),
                      createBaseVNode("li", null, [
                        createTextVNode("Example: "),
                        createBaseVNode("code", null, "[0, 2]")
                      ])
                    ], -1))
                  ]),
                  _cache[549] || (_cache[549] = createBaseVNode("li", null, [
                    createTextVNode("Example: "),
                    createBaseVNode("code", null, '{"matrix": [2, 1], "x": 20, "y": 48, "flags": 2}')
                  ], -1))
                ])
              ])
            ])
          ]),
          createBaseVNode("li", null, [
            _cache[555] || (_cache[555] = createBaseVNode("code", null, "led_flush_limit", -1)),
            _cache[556] || (_cache[556] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[554] || (_cache[554] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[557] || (_cache[557] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Limits in milliseconds how frequently an animation will update the LEDs."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "16")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[559] || (_cache[559] = createBaseVNode("code", null, "led_process_limit", -1)),
            _cache[560] || (_cache[560] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[558] || (_cache[558] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[561] || (_cache[561] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "(led_count + 4) / 5")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[563] || (_cache[563] = createBaseVNode("code", null, "max_brightness", -1)),
            _cache[564] || (_cache[564] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[562] || (_cache[562] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[565] || (_cache[565] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The maximum value which brightness is scaled to, from 0 to 255."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "255")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[567] || (_cache[567] = createBaseVNode("code", null, "react_on_keyup", -1)),
            _cache[568] || (_cache[568] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[566] || (_cache[566] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[569] || (_cache[569] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Animations react to keyup instead of keydown."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[571] || (_cache[571] = createBaseVNode("code", null, "sleep", -1)),
            _cache[572] || (_cache[572] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[570] || (_cache[570] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[573] || (_cache[573] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Turn off the LEDs when the host goes to sleep."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[575] || (_cache[575] = createBaseVNode("code", null, "speed_steps", -1)),
            _cache[576] || (_cache[576] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[574] || (_cache[574] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[577] || (_cache[577] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The value by which to increment the speed."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "16")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[579] || (_cache[579] = createBaseVNode("code", null, "split_count", -1)),
            _cache[580] || (_cache[580] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[578] || (_cache[578] = [
                createTextVNode("Array: Number", -1)
              ])]),
              _: 1
            }),
            _cache[581] || (_cache[581] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "For split keyboards, the number of LEDs on each half."),
              createBaseVNode("li", null, [
                createTextVNode("Example: "),
                createBaseVNode("code", null, "[16, 16]")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[583] || (_cache[583] = createBaseVNode("code", null, "timeout", -1)),
            _cache[584] || (_cache[584] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[582] || (_cache[582] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[585] || (_cache[585] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The LED activity timeout in milliseconds."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "0"),
                createTextVNode(" (no timeout)")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[587] || (_cache[587] = createBaseVNode("code", null, "val_steps", -1)),
            _cache[588] || (_cache[588] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[586] || (_cache[586] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[589] || (_cache[589] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The value by which to increment the brightness."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "8")
              ])
            ], -1))
          ])
        ])
      ])
    ]),
    _cache[1142] || (_cache[1142] = createBaseVNode("h2", {
      id: "matrix",
      tabindex: "-1"
    }, [
      createTextVNode("Matrix "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#matrix",
        "aria-label": 'Permalink to "Matrix {#matrix}"'
      }, "​")
    ], -1)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[592] || (_cache[592] = createBaseVNode("code", null, "debounce", -1)),
        _cache[593] || (_cache[593] = createTextVNode()),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [..._cache[591] || (_cache[591] = [
            createTextVNode("Number", -1)
          ])]),
          _: 1
        }),
        _cache[594] || (_cache[594] = createBaseVNode("ul", null, [
          createBaseVNode("li", null, "The debounce time in milliseconds."),
          createBaseVNode("li", null, [
            createTextVNode("Default: "),
            createBaseVNode("code", null, "5"),
            createTextVNode(" (5 ms)")
          ])
        ], -1))
      ]),
      createBaseVNode("li", null, [
        _cache[596] || (_cache[596] = createBaseVNode("code", null, "diode_direction", -1)),
        _cache[597] || (_cache[597] = createTextVNode()),
        createVNode(_component_Badge, { type: "info" }, {
          default: withCtx(() => [..._cache[595] || (_cache[595] = [
            createTextVNode("String", -1)
          ])]),
          _: 1
        }),
        _cache[598] || (_cache[598] = createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            createTextVNode('Which way the diodes are "pointing". Unused for '),
            createBaseVNode("code", null, "matrix_pins.direct"),
            createTextVNode(". Must be one of "),
            createBaseVNode("code", null, "COL2ROW"),
            createTextVNode(", "),
            createBaseVNode("code", null, "ROW2COL"),
            createTextVNode(".")
          ])
        ], -1))
      ]),
      createBaseVNode("li", null, [
        _cache[635] || (_cache[635] = createBaseVNode("code", null, "matrix_pins", -1)),
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _cache[600] || (_cache[600] = createBaseVNode("code", null, "cols", -1)),
            _cache[601] || (_cache[601] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[599] || (_cache[599] = [
                createTextVNode("Array: Pin", -1)
              ])]),
              _: 1
            }),
            _cache[602] || (_cache[602] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "A list of GPIO pins connected to the matrix columns."),
              createBaseVNode("li", null, [
                createTextVNode("Example: "),
                createBaseVNode("code", null, '["A0", "A1", "A2"]')
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[604] || (_cache[604] = createBaseVNode("code", null, "custom", -1)),
            _cache[605] || (_cache[605] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[603] || (_cache[603] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[606] || (_cache[606] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Whether to use a custom matrix scanning implementation."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[608] || (_cache[608] = createBaseVNode("code", null, "custom_lite", -1)),
            _cache[609] || (_cache[609] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[607] || (_cache[607] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[610] || (_cache[610] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, 'Whether to use a "lite" custom matrix scanning implementation.'),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[612] || (_cache[612] = createBaseVNode("code", null, "direct", -1)),
            _cache[613] || (_cache[613] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[611] || (_cache[611] = [
                createTextVNode("Array: Array: Pin", -1)
              ])]),
              _: 1
            }),
            _cache[614] || (_cache[614] = createStaticVNode('<ul><li>A 2-dimensional list of GPIO pins connected to each keyswitch, forming the &quot;matrix&quot; rows and columns.</li><li>Example:</li></ul><div class="language-json vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">json</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">[</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    [</span><span style="--shiki-light:#032F62;--shiki-dark:#9ECBFF;">&quot;A0&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span><span style="--shiki-light:#032F62;--shiki-dark:#9ECBFF;">&quot;A1&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span><span style="--shiki-light:#032F62;--shiki-dark:#9ECBFF;">&quot;A2&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">],</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    [</span><span style="--shiki-light:#032F62;--shiki-dark:#9ECBFF;">&quot;B0&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span><span style="--shiki-light:#032F62;--shiki-dark:#9ECBFF;">&quot;B1&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span><span style="--shiki-light:#032F62;--shiki-dark:#9ECBFF;">&quot;B2&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">],</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    [</span><span style="--shiki-light:#032F62;--shiki-dark:#9ECBFF;">&quot;C0&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span><span style="--shiki-light:#032F62;--shiki-dark:#9ECBFF;">&quot;C1&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span><span style="--shiki-light:#032F62;--shiki-dark:#9ECBFF;">&quot;C2&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">]</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">]</span></span></code></pre></div>', 2))
          ]),
          createBaseVNode("li", null, [
            _cache[616] || (_cache[616] = createBaseVNode("code", null, "ghost", -1)),
            _cache[617] || (_cache[617] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[615] || (_cache[615] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[618] || (_cache[618] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Whether the matrix has no anti-ghosting diodes."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[620] || (_cache[620] = createBaseVNode("code", null, "input_pressed_state", -1)),
            _cache[621] || (_cache[621] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[619] || (_cache[619] = [
                createTextVNode("0|1", -1)
              ])]),
              _: 1
            }),
            _cache[622] || (_cache[622] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The logical GPIO state of the input pins when a key is pressed."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "0"),
                createTextVNode(" (pressed = low)")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[624] || (_cache[624] = createBaseVNode("code", null, "io_delay", -1)),
            _cache[625] || (_cache[625] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[623] || (_cache[623] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[626] || (_cache[626] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The amount of time to wait between row/col selection and col/row pin reading, in microseconds."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "30"),
                createTextVNode(" (30 µs)")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[628] || (_cache[628] = createBaseVNode("code", null, "masked", -1)),
            _cache[629] || (_cache[629] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[627] || (_cache[627] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[630] || (_cache[630] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Whether unconfigured intersections should be ignored."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[632] || (_cache[632] = createBaseVNode("code", null, "rows", -1)),
            _cache[633] || (_cache[633] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[631] || (_cache[631] = [
                createTextVNode("Array: Pin", -1)
              ])]),
              _: 1
            }),
            _cache[634] || (_cache[634] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "A list of GPIO pins connected to the matrix rows."),
              createBaseVNode("li", null, [
                createTextVNode("Example: "),
                createBaseVNode("code", null, '["B0", "B1", "B2"]')
              ])
            ], -1))
          ])
        ])
      ])
    ]),
    _cache[1143] || (_cache[1143] = createBaseVNode("h2", {
      id: "mouse-keys",
      tabindex: "-1"
    }, [
      createTextVNode("Mouse Keys "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#mouse-keys",
        "aria-label": 'Permalink to "Mouse Keys {#mouse-keys}"'
      }, "​")
    ], -1)),
    _cache[1144] || (_cache[1144] = createBaseVNode("p", null, [
      createTextVNode("Configures the "),
      createBaseVNode("a", { href: "./features/mouse_keys" }, "Mouse Keys"),
      createTextVNode(" feature.")
    ], -1)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[655] || (_cache[655] = createBaseVNode("code", null, "mouse_key", -1)),
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _cache[637] || (_cache[637] = createBaseVNode("code", null, "delay", -1)),
            _cache[638] || (_cache[638] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[636] || (_cache[636] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            })
          ]),
          createBaseVNode("li", null, [
            _cache[640] || (_cache[640] = createBaseVNode("code", null, "enabled", -1)),
            _cache[641] || (_cache[641] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[639] || (_cache[639] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[642] || (_cache[642] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Enables the Mouse Keys feature."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[644] || (_cache[644] = createBaseVNode("code", null, "interval", -1)),
            _cache[645] || (_cache[645] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[643] || (_cache[643] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            })
          ]),
          createBaseVNode("li", null, [
            _cache[647] || (_cache[647] = createBaseVNode("code", null, "max_speed", -1)),
            _cache[648] || (_cache[648] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[646] || (_cache[646] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            })
          ]),
          createBaseVNode("li", null, [
            _cache[650] || (_cache[650] = createBaseVNode("code", null, "time_to_max", -1)),
            _cache[651] || (_cache[651] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[649] || (_cache[649] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            })
          ]),
          createBaseVNode("li", null, [
            _cache[653] || (_cache[653] = createBaseVNode("code", null, "wheel_delay", -1)),
            _cache[654] || (_cache[654] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[652] || (_cache[652] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            })
          ])
        ])
      ])
    ]),
    _cache[1145] || (_cache[1145] = createBaseVNode("h2", {
      id: "one-shot",
      tabindex: "-1"
    }, [
      createTextVNode("One Shot "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#one-shot",
        "aria-label": 'Permalink to "One Shot {#one-shot}"'
      }, "​")
    ], -1)),
    _cache[1146] || (_cache[1146] = createBaseVNode("p", null, [
      createTextVNode("Configures "),
      createBaseVNode("a", { href: "./one_shot_keys" }, "One Shot keys"),
      createTextVNode(".")
    ], -1)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[664] || (_cache[664] = createBaseVNode("code", null, "oneshot", -1)),
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _cache[657] || (_cache[657] = createBaseVNode("code", null, "tap_toggle", -1)),
            _cache[658] || (_cache[658] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[656] || (_cache[656] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[659] || (_cache[659] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The number of times to tap the key in order to hold it.")
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[661] || (_cache[661] = createBaseVNode("code", null, "timeout", -1)),
            _cache[662] || (_cache[662] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[660] || (_cache[660] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[663] || (_cache[663] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The amount of time before the key is released in milliseconds.")
            ], -1))
          ])
        ])
      ])
    ]),
    _cache[1147] || (_cache[1147] = createBaseVNode("h2", {
      id: "ps2",
      tabindex: "-1"
    }, [
      createTextVNode("PS/2 "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#ps2",
        "aria-label": 'Permalink to "PS/2 {#ps2}"'
      }, "​")
    ], -1)),
    _cache[1148] || (_cache[1148] = createBaseVNode("p", null, [
      createTextVNode("Configures the "),
      createBaseVNode("a", { href: "./features/ps2_mouse" }, "PS/2"),
      createTextVNode(" feature.")
    ], -1)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[685] || (_cache[685] = createBaseVNode("code", null, "ps2", -1)),
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _cache[666] || (_cache[666] = createBaseVNode("code", null, "clock_pin", -1)),
            _cache[667] || (_cache[667] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[665] || (_cache[665] = [
                createTextVNode("Pin", -1)
              ])]),
              _: 1
            }),
            _cache[668] || (_cache[668] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("The GPIO pin connected to "),
                createBaseVNode("code", null, "CLK"),
                createTextVNode(" on the PS/2 device.")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[670] || (_cache[670] = createBaseVNode("code", null, "data_pin", -1)),
            _cache[671] || (_cache[671] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[669] || (_cache[669] = [
                createTextVNode("Pin", -1)
              ])]),
              _: 1
            }),
            _cache[672] || (_cache[672] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("The GPIO pin connected to "),
                createBaseVNode("code", null, "DATA"),
                createTextVNode(" on the PS/2 device.")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[674] || (_cache[674] = createBaseVNode("code", null, "driver", -1)),
            _cache[675] || (_cache[675] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[673] || (_cache[673] = [
                createTextVNode("String", -1)
              ])]),
              _: 1
            }),
            _cache[676] || (_cache[676] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("The PS/2 driver to use. Must be one of "),
                createBaseVNode("code", null, "busywait"),
                createTextVNode(", "),
                createBaseVNode("code", null, "interrupt"),
                createTextVNode(", "),
                createBaseVNode("code", null, "usart"),
                createTextVNode(", "),
                createBaseVNode("code", null, "vendor"),
                createTextVNode(".")
              ]),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, '"busywait"')
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[678] || (_cache[678] = createBaseVNode("code", null, "enabled", -1)),
            _cache[679] || (_cache[679] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[677] || (_cache[677] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[680] || (_cache[680] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Enable the PS/2 feature."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[682] || (_cache[682] = createBaseVNode("code", null, "mouse_enabled", -1)),
            _cache[683] || (_cache[683] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[681] || (_cache[681] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[684] || (_cache[684] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Enable the PS/2 mouse handling."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ])
        ])
      ])
    ]),
    _cache[1149] || (_cache[1149] = createBaseVNode("h2", {
      id: "qmk-lufa-bootloader",
      tabindex: "-1"
    }, [
      createTextVNode("QMK LUFA Bootloader "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#qmk-lufa-bootloader",
        "aria-label": 'Permalink to "QMK LUFA Bootloader {#qmk-lufa-bootloader}"'
      }, "​")
    ], -1)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[706] || (_cache[706] = createBaseVNode("code", null, "qmk_lufa_bootloader", -1)),
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _cache[688] || (_cache[688] = createBaseVNode("code", null, "esc_input", -1)),
            _cache[689] || (_cache[689] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[686] || (_cache[686] = [
                createTextVNode("Pin", -1)
              ])]),
              _: 1
            }),
            _cache[690] || (_cache[690] = createTextVNode()),
            createVNode(_component_Badge, null, {
              default: withCtx(() => [..._cache[687] || (_cache[687] = [
                createTextVNode("Required", -1)
              ])]),
              _: 1
            }),
            _cache[691] || (_cache[691] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode(`The GPIO pin connected to the designated "exit bootloader" key's row (if `),
                createBaseVNode("code", null, "COL2ROW"),
                createTextVNode(").")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[694] || (_cache[694] = createBaseVNode("code", null, "esc_output", -1)),
            _cache[695] || (_cache[695] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[692] || (_cache[692] = [
                createTextVNode("Pin", -1)
              ])]),
              _: 1
            }),
            _cache[696] || (_cache[696] = createTextVNode()),
            createVNode(_component_Badge, null, {
              default: withCtx(() => [..._cache[693] || (_cache[693] = [
                createTextVNode("Required", -1)
              ])]),
              _: 1
            }),
            _cache[697] || (_cache[697] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode(`The GPIO pin connected to the designated "exit bootloader" key's column (if `),
                createBaseVNode("code", null, "COL2ROW"),
                createTextVNode(").")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[699] || (_cache[699] = createBaseVNode("code", null, "led", -1)),
            _cache[700] || (_cache[700] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[698] || (_cache[698] = [
                createTextVNode("Pin", -1)
              ])]),
              _: 1
            }),
            _cache[701] || (_cache[701] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The GPIO pin connected to an LED to flash.")
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[703] || (_cache[703] = createBaseVNode("code", null, "speaker", -1)),
            _cache[704] || (_cache[704] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[702] || (_cache[702] = [
                createTextVNode("Pin", -1)
              ])]),
              _: 1
            }),
            _cache[705] || (_cache[705] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The GPIO pin connected to a speaker to click (can also be used for a second LED).")
            ], -1))
          ])
        ])
      ])
    ]),
    _cache[1150] || (_cache[1150] = createBaseVNode("h2", {
      id: "rgblight",
      tabindex: "-1"
    }, [
      createTextVNode("RGBLight "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#rgblight",
        "aria-label": 'Permalink to "RGBLight {#rgblight}"'
      }, "​")
    ], -1)),
    _cache[1151] || (_cache[1151] = createBaseVNode("p", null, [
      createTextVNode("Configures the "),
      createBaseVNode("a", { href: "./features/rgblight" }, "RGB Lighting"),
      createTextVNode(" feature.")
    ], -1)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[791] || (_cache[791] = createBaseVNode("code", null, "rgblight", -1)),
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _cache[709] || (_cache[709] = createBaseVNode("code", null, "led_count", -1)),
            _cache[710] || (_cache[710] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[707] || (_cache[707] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[711] || (_cache[711] = createTextVNode()),
            createVNode(_component_Badge, null, {
              default: withCtx(() => [..._cache[708] || (_cache[708] = [
                createTextVNode("Required", -1)
              ])]),
              _: 1
            }),
            _cache[712] || (_cache[712] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The number of LEDs in the chain.")
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[714] || (_cache[714] = createBaseVNode("code", null, "animations", -1)),
            _cache[715] || (_cache[715] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[713] || (_cache[713] = [
                createTextVNode("Object: Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[716] || (_cache[716] = createStaticVNode('<ul><li>A dictionary of effects to enable or disable. Effects which are absent default to <code>false</code>.</li><li>Example:</li></ul><div class="language-json vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">json</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">{</span></span>\n<span class="line"><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">    &quot;breathing&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">: </span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">true</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">,</span></span>\n<span class="line"><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">    &quot;rainbow_mood&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">: </span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">true</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">,</span></span>\n<span class="line"><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">    &quot;snake&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">: </span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">false</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">}</span></span></code></pre></div>', 2))
          ]),
          createBaseVNode("li", null, [
            _cache[718] || (_cache[718] = createBaseVNode("code", null, "brightness_steps", -1)),
            _cache[719] || (_cache[719] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[717] || (_cache[717] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[720] || (_cache[720] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The value by which to increment the brightness."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "17")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[745] || (_cache[745] = createBaseVNode("code", null, "default", -1)),
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _cache[722] || (_cache[722] = createBaseVNode("code", null, "animation", -1)),
                _cache[723] || (_cache[723] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[721] || (_cache[721] = [
                    createTextVNode("String", -1)
                  ])]),
                  _: 1
                }),
                _cache[724] || (_cache[724] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, [
                    createTextVNode("The default effect. Must be one of "),
                    createBaseVNode("code", null, "rgblight.animations")
                  ]),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, '"static_light"')
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[726] || (_cache[726] = createBaseVNode("code", null, "on", -1)),
                _cache[727] || (_cache[727] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[725] || (_cache[725] = [
                    createTextVNode("Boolean", -1)
                  ])]),
                  _: 1
                }),
                _cache[728] || (_cache[728] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The default enabled state."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "true")
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[730] || (_cache[730] = createBaseVNode("code", null, "hue", -1)),
                _cache[731] || (_cache[731] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[729] || (_cache[729] = [
                    createTextVNode("Number", -1)
                  ])]),
                  _: 1
                }),
                _cache[732] || (_cache[732] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The default hue value."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "0")
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[734] || (_cache[734] = createBaseVNode("code", null, "sat", -1)),
                _cache[735] || (_cache[735] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[733] || (_cache[733] = [
                    createTextVNode("Number", -1)
                  ])]),
                  _: 1
                }),
                _cache[736] || (_cache[736] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The default saturation value."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "255")
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[738] || (_cache[738] = createBaseVNode("code", null, "val", -1)),
                _cache[739] || (_cache[739] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[737] || (_cache[737] = [
                    createTextVNode("Number", -1)
                  ])]),
                  _: 1
                }),
                _cache[740] || (_cache[740] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The default brightness level."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "max_brightness")
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[742] || (_cache[742] = createBaseVNode("code", null, "speed", -1)),
                _cache[743] || (_cache[743] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[741] || (_cache[741] = [
                    createTextVNode("Number", -1)
                  ])]),
                  _: 1
                }),
                _cache[744] || (_cache[744] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The default animation speed."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "0")
                  ])
                ], -1))
              ])
            ])
          ]),
          createBaseVNode("li", null, [
            _cache[747] || (_cache[747] = createBaseVNode("code", null, "driver", -1)),
            _cache[748] || (_cache[748] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[746] || (_cache[746] = [
                createTextVNode("String", -1)
              ])]),
              _: 1
            }),
            _cache[749] || (_cache[749] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("The driver to use. Must be one of "),
                createBaseVNode("code", null, "apa102"),
                createTextVNode(", "),
                createBaseVNode("code", null, "custom"),
                createTextVNode(", "),
                createBaseVNode("code", null, "ws2812"),
                createTextVNode(".")
              ]),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, '"ws2812"')
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[751] || (_cache[751] = createBaseVNode("code", null, "hue_steps", -1)),
            _cache[752] || (_cache[752] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[750] || (_cache[750] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[753] || (_cache[753] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The value by which to increment the hue."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "8")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[766] || (_cache[766] = createBaseVNode("code", null, "layers", -1)),
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _cache[755] || (_cache[755] = createBaseVNode("code", null, "blink", -1)),
                _cache[756] || (_cache[756] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[754] || (_cache[754] = [
                    createTextVNode("Boolean", -1)
                  ])]),
                  _: 1
                }),
                _cache[757] || (_cache[757] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "Enable layer blinking API."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "false")
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[759] || (_cache[759] = createBaseVNode("code", null, "enabled", -1)),
                _cache[760] || (_cache[760] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[758] || (_cache[758] = [
                    createTextVNode("Boolean", -1)
                  ])]),
                  _: 1
                }),
                _cache[761] || (_cache[761] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "Enable RGB Lighting Layers."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "false")
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[763] || (_cache[763] = createBaseVNode("code", null, "max", -1)),
                _cache[764] || (_cache[764] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[762] || (_cache[762] = [
                    createTextVNode("Number", -1)
                  ])]),
                  _: 1
                }),
                _cache[765] || (_cache[765] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The maximum layer count, from 1 to 32."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "8")
                  ])
                ], -1))
              ])
            ])
          ]),
          createBaseVNode("li", null, [
            _cache[768] || (_cache[768] = createBaseVNode("code", null, "led_map", -1)),
            _cache[769] || (_cache[769] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[767] || (_cache[767] = [
                createTextVNode("Array: Number", -1)
              ])]),
              _: 1
            }),
            _cache[770] || (_cache[770] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Remap LED indices."),
              createBaseVNode("li", null, [
                createTextVNode("Example: "),
                createBaseVNode("code", null, "[4, 3, 2, 1, 0]")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[772] || (_cache[772] = createBaseVNode("code", null, "max_brightness", -1)),
            _cache[773] || (_cache[773] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[771] || (_cache[771] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[774] || (_cache[774] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, 'The maximum value which the HSV "V" component is scaled to, from 0 to 255.'),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "255")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[776] || (_cache[776] = createBaseVNode("code", null, "saturation_steps", -1)),
            _cache[777] || (_cache[777] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[775] || (_cache[775] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[778] || (_cache[778] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The value by which to increment the suturation."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "17")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[780] || (_cache[780] = createBaseVNode("code", null, "sleep", -1)),
            _cache[781] || (_cache[781] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[779] || (_cache[779] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[782] || (_cache[782] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Turn off the LEDs when the host goes to sleep."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[784] || (_cache[784] = createBaseVNode("code", null, "split", -1)),
            _cache[785] || (_cache[785] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[783] || (_cache[783] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[786] || (_cache[786] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Enable synchronization between split halves."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[788] || (_cache[788] = createBaseVNode("code", null, "split_count", -1)),
            _cache[789] || (_cache[789] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[787] || (_cache[787] = [
                createTextVNode("Array: Number", -1)
              ])]),
              _: 1
            }),
            _cache[790] || (_cache[790] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("When "),
                createBaseVNode("code", null, "rgblight.split"),
                createTextVNode(" is enabled, the number of LEDs on each half.")
              ]),
              createBaseVNode("li", null, [
                createTextVNode("Example: "),
                createBaseVNode("code", null, "[10, 10]")
              ])
            ], -1))
          ])
        ])
      ])
    ]),
    _cache[1152] || (_cache[1152] = createBaseVNode("h2", {
      id: "rgb-matrix",
      tabindex: "-1"
    }, [
      createTextVNode("RGB Matrix "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#rgb-matrix",
        "aria-label": 'Permalink to "RGB Matrix {#rgb-matrix}"'
      }, "​")
    ], -1)),
    _cache[1153] || (_cache[1153] = createBaseVNode("p", null, [
      createTextVNode("Configures the "),
      createBaseVNode("a", { href: "./features/rgb_matrix" }, "RGB Matrix"),
      createTextVNode(" feature.")
    ], -1)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[912] || (_cache[912] = createBaseVNode("code", null, "rgb_matrix", -1)),
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _cache[793] || (_cache[793] = createBaseVNode("code", null, "animations", -1)),
            _cache[794] || (_cache[794] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[792] || (_cache[792] = [
                createTextVNode("Object: Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[795] || (_cache[795] = createStaticVNode('<ul><li>A dictionary of effects to enable or disable. Effects which are absent default to <code>false</code>.</li><li>Example:</li></ul><div class="language-json vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">json</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">{</span></span>\n<span class="line"><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">    &quot;alphas_mods&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">: </span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">true</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">,</span></span>\n<span class="line"><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">    &quot;breathing&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">: </span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">true</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">,</span></span>\n<span class="line"><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">    &quot;cycle_left_right&quot;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">: </span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">false</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">}</span></span></code></pre></div>', 2))
          ]),
          createBaseVNode("li", null, [
            _cache[797] || (_cache[797] = createBaseVNode("code", null, "center_point", -1)),
            _cache[798] || (_cache[798] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[796] || (_cache[796] = [
                createTextVNode("Array: Number", -1)
              ])]),
              _: 1
            }),
            _cache[799] || (_cache[799] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The centroid (geometric center) of the LEDs. Used for certain effects."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "[112, 32]")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[801] || (_cache[801] = createBaseVNode("code", null, "flag_steps", -1)),
            _cache[802] || (_cache[802] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[800] || (_cache[800] = [
                createTextVNode("Array: Number", -1)
              ])]),
              _: 1
            }),
            _cache[803] || (_cache[803] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "A list of flag bitfields that can be cycled through."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "[255, 5, 2, 0]")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[832] || (_cache[832] = createBaseVNode("code", null, "default", -1)),
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _cache[805] || (_cache[805] = createBaseVNode("code", null, "animation", -1)),
                _cache[806] || (_cache[806] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[804] || (_cache[804] = [
                    createTextVNode("String", -1)
                  ])]),
                  _: 1
                }),
                _cache[807] || (_cache[807] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, [
                    createTextVNode("The default effect. Must be one of "),
                    createBaseVNode("code", null, "rgb_matrix.animations")
                  ]),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, '"solid_color"')
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[809] || (_cache[809] = createBaseVNode("code", null, "on", -1)),
                _cache[810] || (_cache[810] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[808] || (_cache[808] = [
                    createTextVNode("Boolean", -1)
                  ])]),
                  _: 1
                }),
                _cache[811] || (_cache[811] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The default enabled state."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "true")
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[813] || (_cache[813] = createBaseVNode("code", null, "hue", -1)),
                _cache[814] || (_cache[814] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[812] || (_cache[812] = [
                    createTextVNode("Number", -1)
                  ])]),
                  _: 1
                }),
                _cache[815] || (_cache[815] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The default hue value."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "0")
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[817] || (_cache[817] = createBaseVNode("code", null, "sat", -1)),
                _cache[818] || (_cache[818] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[816] || (_cache[816] = [
                    createTextVNode("Number", -1)
                  ])]),
                  _: 1
                }),
                _cache[819] || (_cache[819] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The default saturation value."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "255")
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[821] || (_cache[821] = createBaseVNode("code", null, "val", -1)),
                _cache[822] || (_cache[822] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[820] || (_cache[820] = [
                    createTextVNode("Number", -1)
                  ])]),
                  _: 1
                }),
                _cache[823] || (_cache[823] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The default brightness level."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "max_brightness")
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[825] || (_cache[825] = createBaseVNode("code", null, "speed", -1)),
                _cache[826] || (_cache[826] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[824] || (_cache[824] = [
                    createTextVNode("Number", -1)
                  ])]),
                  _: 1
                }),
                _cache[827] || (_cache[827] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The default animation speed."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "128")
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[829] || (_cache[829] = createBaseVNode("code", null, "flags", -1)),
                _cache[830] || (_cache[830] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[828] || (_cache[828] = [
                    createTextVNode("Number", -1)
                  ])]),
                  _: 1
                }),
                _cache[831] || (_cache[831] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The default LED flags."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "255")
                  ])
                ], -1))
              ])
            ])
          ]),
          createBaseVNode("li", null, [
            _cache[835] || (_cache[835] = createBaseVNode("code", null, "driver", -1)),
            _cache[836] || (_cache[836] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[833] || (_cache[833] = [
                createTextVNode("String", -1)
              ])]),
              _: 1
            }),
            _cache[837] || (_cache[837] = createTextVNode()),
            createVNode(_component_Badge, null, {
              default: withCtx(() => [..._cache[834] || (_cache[834] = [
                createTextVNode("Required", -1)
              ])]),
              _: 1
            }),
            _cache[838] || (_cache[838] = createStaticVNode("<ul><li>The driver to use. Must be one of <code>aw20216s</code>, <code>custom</code>, <code>is31fl3218</code>, <code>is31fl3236</code>, <code>is31fl3729</code>, <code>is31fl3731</code>, <code>is31fl3733</code>, <code>is31fl3736</code>, <code>is31fl3737</code>, <code>is31fl3741</code>, <code>is31fl3742a</code>, <code>is31fl3743a</code>, <code>is31fl3745</code>, <code>is31fl3746a</code>, <code>snled27351</code>, <code>ws2812</code>.</li></ul>", 1))
          ]),
          createBaseVNode("li", null, [
            _cache[840] || (_cache[840] = createBaseVNode("code", null, "hue_steps", -1)),
            _cache[841] || (_cache[841] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[839] || (_cache[839] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[842] || (_cache[842] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The value by which to increment the hue."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "8")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[869] || (_cache[869] = createBaseVNode("code", null, "layout", -1)),
            _cache[870] || (_cache[870] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[843] || (_cache[843] = [
                createTextVNode("Array: Object", -1)
              ])]),
              _: 1
            }),
            _cache[871] || (_cache[871] = createTextVNode()),
            createVNode(_component_Badge, null, {
              default: withCtx(() => [..._cache[844] || (_cache[844] = [
                createTextVNode("Required", -1)
              ])]),
              _: 1
            }),
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _cache[868] || (_cache[868] = createTextVNode("List of LED configuration dictionaries. Each dictionary contains: ", -1)),
                createBaseVNode("ul", null, [
                  createBaseVNode("li", null, [
                    _cache[847] || (_cache[847] = createBaseVNode("code", null, "flags", -1)),
                    _cache[848] || (_cache[848] = createTextVNode()),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [..._cache[845] || (_cache[845] = [
                        createTextVNode("Number", -1)
                      ])]),
                      _: 1
                    }),
                    _cache[849] || (_cache[849] = createTextVNode()),
                    createVNode(_component_Badge, null, {
                      default: withCtx(() => [..._cache[846] || (_cache[846] = [
                        createTextVNode("Required", -1)
                      ])]),
                      _: 1
                    }),
                    _cache[850] || (_cache[850] = createBaseVNode("ul", null, [
                      createBaseVNode("li", null, "A bitfield of flags describing the type of LED.")
                    ], -1))
                  ]),
                  createBaseVNode("li", null, [
                    _cache[853] || (_cache[853] = createBaseVNode("code", null, "x", -1)),
                    _cache[854] || (_cache[854] = createTextVNode()),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [..._cache[851] || (_cache[851] = [
                        createTextVNode("Number", -1)
                      ])]),
                      _: 1
                    }),
                    _cache[855] || (_cache[855] = createTextVNode()),
                    createVNode(_component_Badge, null, {
                      default: withCtx(() => [..._cache[852] || (_cache[852] = [
                        createTextVNode("Required", -1)
                      ])]),
                      _: 1
                    }),
                    _cache[856] || (_cache[856] = createBaseVNode("ul", null, [
                      createBaseVNode("li", null, "The position of the LED in the horizontal axis, from 0 to 224.")
                    ], -1))
                  ]),
                  createBaseVNode("li", null, [
                    _cache[859] || (_cache[859] = createBaseVNode("code", null, "y", -1)),
                    _cache[860] || (_cache[860] = createTextVNode()),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [..._cache[857] || (_cache[857] = [
                        createTextVNode("Number", -1)
                      ])]),
                      _: 1
                    }),
                    _cache[861] || (_cache[861] = createTextVNode()),
                    createVNode(_component_Badge, null, {
                      default: withCtx(() => [..._cache[858] || (_cache[858] = [
                        createTextVNode("Required", -1)
                      ])]),
                      _: 1
                    }),
                    _cache[862] || (_cache[862] = createBaseVNode("ul", null, [
                      createBaseVNode("li", null, "The position of the LED in the vertical axis, from 0 to 64.")
                    ], -1))
                  ]),
                  createBaseVNode("li", null, [
                    _cache[864] || (_cache[864] = createBaseVNode("code", null, "matrix", -1)),
                    _cache[865] || (_cache[865] = createTextVNode()),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [..._cache[863] || (_cache[863] = [
                        createTextVNode("Matrix", -1)
                      ])]),
                      _: 1
                    }),
                    _cache[866] || (_cache[866] = createBaseVNode("ul", null, [
                      createBaseVNode("li", null, "The key matrix position associated with the LED."),
                      createBaseVNode("li", null, [
                        createTextVNode("Example: "),
                        createBaseVNode("code", null, "[0, 2]")
                      ])
                    ], -1))
                  ]),
                  _cache[867] || (_cache[867] = createBaseVNode("li", null, [
                    createTextVNode("Example: "),
                    createBaseVNode("code", null, '{"matrix": [2, 1], "x": 20, "y": 48, "flags": 2}')
                  ], -1))
                ])
              ])
            ])
          ]),
          createBaseVNode("li", null, [
            _cache[873] || (_cache[873] = createBaseVNode("code", null, "led_flush_limit", -1)),
            _cache[874] || (_cache[874] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[872] || (_cache[872] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[875] || (_cache[875] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Limits in milliseconds how frequently an animation will update the LEDs."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "16")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[877] || (_cache[877] = createBaseVNode("code", null, "led_process_limit", -1)),
            _cache[878] || (_cache[878] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[876] || (_cache[876] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[879] || (_cache[879] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "(led_count + 4) / 5")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[881] || (_cache[881] = createBaseVNode("code", null, "max_brightness", -1)),
            _cache[882] || (_cache[882] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[880] || (_cache[880] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[883] || (_cache[883] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, 'The maximum value which the HSV "V" component is scaled to, from 0 to 255.'),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "255")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[885] || (_cache[885] = createBaseVNode("code", null, "react_on_keyup", -1)),
            _cache[886] || (_cache[886] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[884] || (_cache[884] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[887] || (_cache[887] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Animations react to keyup instead of keydown."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[889] || (_cache[889] = createBaseVNode("code", null, "sat_steps", -1)),
            _cache[890] || (_cache[890] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[888] || (_cache[888] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[891] || (_cache[891] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The value by which to increment the saturation."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "16")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[893] || (_cache[893] = createBaseVNode("code", null, "sleep", -1)),
            _cache[894] || (_cache[894] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[892] || (_cache[892] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[895] || (_cache[895] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Turn off the LEDs when the host goes to sleep."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[897] || (_cache[897] = createBaseVNode("code", null, "speed_steps", -1)),
            _cache[898] || (_cache[898] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[896] || (_cache[896] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[899] || (_cache[899] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The value by which to increment the speed."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "16")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[901] || (_cache[901] = createBaseVNode("code", null, "split_count", -1)),
            _cache[902] || (_cache[902] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[900] || (_cache[900] = [
                createTextVNode("Array: Number", -1)
              ])]),
              _: 1
            }),
            _cache[903] || (_cache[903] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "For split keyboards, the number of LEDs on each half."),
              createBaseVNode("li", null, [
                createTextVNode("Example: "),
                createBaseVNode("code", null, "[16, 16]")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[905] || (_cache[905] = createBaseVNode("code", null, "timeout", -1)),
            _cache[906] || (_cache[906] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[904] || (_cache[904] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[907] || (_cache[907] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The LED activity timeout in milliseconds."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "0"),
                createTextVNode(" (no timeout)")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[909] || (_cache[909] = createBaseVNode("code", null, "val_steps", -1)),
            _cache[910] || (_cache[910] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[908] || (_cache[908] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[911] || (_cache[911] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The value by which to increment the brightness."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "16")
              ])
            ], -1))
          ])
        ])
      ])
    ]),
    _cache[1154] || (_cache[1154] = createBaseVNode("h2", {
      id: "secure",
      tabindex: "-1"
    }, [
      createTextVNode("Secure "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#secure",
        "aria-label": 'Permalink to "Secure {#secure}"'
      }, "​")
    ], -1)),
    _cache[1155] || (_cache[1155] = createBaseVNode("p", null, [
      createTextVNode("Configures the "),
      createBaseVNode("a", { href: "./features/secure" }, "Secure"),
      createTextVNode(" feature.")
    ], -1)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[929] || (_cache[929] = createBaseVNode("code", null, "secure", -1)),
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _cache[914] || (_cache[914] = createBaseVNode("code", null, "enabled", -1)),
            _cache[915] || (_cache[915] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[913] || (_cache[913] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[916] || (_cache[916] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Enable the Secure feature."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[918] || (_cache[918] = createBaseVNode("code", null, "idle_timeout", -1)),
            _cache[919] || (_cache[919] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[917] || (_cache[917] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[920] || (_cache[920] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("Timeout while unlocked before returning to the locked state. Set to "),
                createBaseVNode("code", null, "0"),
                createTextVNode(" to disable.")
              ]),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "60000"),
                createTextVNode(" (1 minute)")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[922] || (_cache[922] = createBaseVNode("code", null, "unlock_sequence", -1)),
            _cache[923] || (_cache[923] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[921] || (_cache[921] = [
                createTextVNode("Array: Matrix", -1)
              ])]),
              _: 1
            }),
            _cache[924] || (_cache[924] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, 'A list of up to five matrix locations comprising the "unlock sequence".'),
              createBaseVNode("li", null, [
                createTextVNode("Example: "),
                createBaseVNode("code", null, "[[0, 0], [0, 1], [4, 3]]")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[926] || (_cache[926] = createBaseVNode("code", null, "unlock_timeout", -1)),
            _cache[927] || (_cache[927] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[925] || (_cache[925] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[928] || (_cache[928] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("Timeout for the user to perform the unlock sequence. Set to "),
                createBaseVNode("code", null, "0"),
                createTextVNode(" to disable.")
              ]),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "5000"),
                createTextVNode(" (5 seconds)")
              ])
            ], -1))
          ])
        ])
      ])
    ]),
    _cache[1156] || (_cache[1156] = createBaseVNode("h2", {
      id: "split-keyboard",
      tabindex: "-1"
    }, [
      createTextVNode("Split Keyboard "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#split-keyboard",
        "aria-label": 'Permalink to "Split Keyboard {#split-keyboard}"'
      }, "​")
    ], -1)),
    _cache[1157] || (_cache[1157] = createBaseVNode("p", null, [
      createTextVNode("Configures the "),
      createBaseVNode("a", { href: "./features/split_keyboard" }, "Split Keyboard"),
      createTextVNode(" feature.")
    ], -1)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[1026] || (_cache[1026] = createBaseVNode("code", null, "split", -1)),
        createBaseVNode("ul", null, [
          _cache[1023] || (_cache[1023] = createStaticVNode('<li><code>bootmagic</code><ul><li><code>matrix</code><ul><li>See <a href="#bootmagic">Bootmagic</a> config.</li></ul></li></ul></li><li><code>dip_switch</code><ul><li><code>right</code><ul><li><code>pins</code><ul><li>See <a href="#dip-switch">DIP Switches</a> config.</li></ul></li></ul></li></ul></li>', 2)),
          createBaseVNode("li", null, [
            _cache[931] || (_cache[931] = createBaseVNode("code", null, "enabled", -1)),
            _cache[932] || (_cache[932] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[930] || (_cache[930] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[933] || (_cache[933] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Enable the Split Keyboard feature."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          _cache[1024] || (_cache[1024] = createBaseVNode("li", null, [
            createBaseVNode("code", null, "encoder"),
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createBaseVNode("code", null, "right"),
                createBaseVNode("ul", null, [
                  createBaseVNode("li", null, [
                    createBaseVNode("code", null, "rotary"),
                    createBaseVNode("ul", null, [
                      createBaseVNode("li", null, [
                        createTextVNode("See "),
                        createBaseVNode("a", { href: "#encoder" }, "Encoder"),
                        createTextVNode(" config.")
                      ])
                    ])
                  ])
                ])
              ])
            ])
          ], -1)),
          createBaseVNode("li", null, [
            _cache[942] || (_cache[942] = createBaseVNode("code", null, "handedness", -1)),
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _cache[935] || (_cache[935] = createBaseVNode("code", null, "pin", -1)),
                _cache[936] || (_cache[936] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[934] || (_cache[934] = [
                    createTextVNode("Pin", -1)
                  ])]),
                  _: 1
                }),
                _cache[937] || (_cache[937] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The GPIO pin connected to determine handedness.")
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[939] || (_cache[939] = createBaseVNode("code", null, "matrix_grid", -1)),
                _cache[940] || (_cache[940] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[938] || (_cache[938] = [
                    createTextVNode("Array: Pin", -1)
                  ])]),
                  _: 1
                }),
                _cache[941] || (_cache[941] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The GPIO pins of the matrix position which determines the handedness."),
                  createBaseVNode("li", null, [
                    createTextVNode("Example: "),
                    createBaseVNode("code", null, '["A1", "B5"]')
                  ])
                ], -1))
              ])
            ])
          ]),
          _cache[1025] || (_cache[1025] = createBaseVNode("li", null, [
            createBaseVNode("code", null, "matrix_pins"),
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createBaseVNode("code", null, "right"),
                createBaseVNode("ul", null, [
                  createBaseVNode("li", null, [
                    createTextVNode("See "),
                    createBaseVNode("a", { href: "#matrix" }, "Matrix"),
                    createTextVNode(" config.")
                  ])
                ])
              ])
            ])
          ], -1)),
          createBaseVNode("li", null, [
            _cache[955] || (_cache[955] = createBaseVNode("code", null, "serial", -1)),
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _cache[944] || (_cache[944] = createBaseVNode("code", null, "driver", -1)),
                _cache[945] || (_cache[945] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[943] || (_cache[943] = [
                    createTextVNode("String", -1)
                  ])]),
                  _: 1
                }),
                _cache[946] || (_cache[946] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, [
                    createTextVNode("The driver to use. Must be one of "),
                    createBaseVNode("code", null, "bitbang"),
                    createTextVNode(", "),
                    createBaseVNode("code", null, "usart"),
                    createTextVNode(", "),
                    createBaseVNode("code", null, "vendor"),
                    createTextVNode(".")
                  ]),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, '"bitbang"')
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[948] || (_cache[948] = createBaseVNode("code", null, "pin", -1)),
                _cache[949] || (_cache[949] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[947] || (_cache[947] = [
                    createTextVNode("Pin", -1)
                  ])]),
                  _: 1
                }),
                _cache[950] || (_cache[950] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The GPIO pin to use for transmit and receive.")
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[952] || (_cache[952] = createBaseVNode("code", null, "speed", -1)),
                _cache[953] || (_cache[953] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[951] || (_cache[951] = [
                    createTextVNode("Number", -1)
                  ])]),
                  _: 1
                }),
                _cache[954] || (_cache[954] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, [
                    createTextVNode("The protocol speed, from "),
                    createBaseVNode("code", null, "0"),
                    createTextVNode(" to "),
                    createBaseVNode("code", null, "5"),
                    createTextVNode(" (fastest to slowest).")
                  ]),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "1")
                  ])
                ], -1))
              ])
            ])
          ]),
          createBaseVNode("li", null, [
            _cache[1009] || (_cache[1009] = createBaseVNode("code", null, "transport", -1)),
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _cache[957] || (_cache[957] = createBaseVNode("code", null, "protocol", -1)),
                _cache[958] || (_cache[958] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[956] || (_cache[956] = [
                    createTextVNode("String", -1)
                  ])]),
                  _: 1
                }),
                _cache[959] || (_cache[959] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, [
                    createTextVNode("The split transport protocol to use. Must be one of "),
                    createBaseVNode("code", null, "custom"),
                    createTextVNode(", "),
                    createBaseVNode("code", null, "i2c"),
                    createTextVNode(", "),
                    createBaseVNode("code", null, "serial"),
                    createTextVNode(".")
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[1e3] || (_cache[1e3] = createBaseVNode("code", null, "sync", -1)),
                createBaseVNode("ul", null, [
                  createBaseVNode("li", null, [
                    _cache[961] || (_cache[961] = createBaseVNode("code", null, "activity", -1)),
                    _cache[962] || (_cache[962] = createTextVNode()),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [..._cache[960] || (_cache[960] = [
                        createTextVNode("Boolean", -1)
                      ])]),
                      _: 1
                    }),
                    _cache[963] || (_cache[963] = createBaseVNode("ul", null, [
                      createBaseVNode("li", null, "Mirror the activity timestamps to the secondary half."),
                      createBaseVNode("li", null, [
                        createTextVNode("Default: "),
                        createBaseVNode("code", null, "false")
                      ])
                    ], -1))
                  ]),
                  createBaseVNode("li", null, [
                    _cache[965] || (_cache[965] = createBaseVNode("code", null, "detected_os", -1)),
                    _cache[966] || (_cache[966] = createTextVNode()),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [..._cache[964] || (_cache[964] = [
                        createTextVNode("Boolean", -1)
                      ])]),
                      _: 1
                    }),
                    _cache[967] || (_cache[967] = createBaseVNode("ul", null, [
                      createBaseVNode("li", null, [
                        createTextVNode("Mirror the "),
                        createBaseVNode("a", { href: "./features/os_detection" }, "detected OS"),
                        createTextVNode(" to the secondary half.")
                      ]),
                      createBaseVNode("li", null, [
                        createTextVNode("Default: "),
                        createBaseVNode("code", null, "false")
                      ])
                    ], -1))
                  ]),
                  createBaseVNode("li", null, [
                    _cache[969] || (_cache[969] = createBaseVNode("code", null, "haptic", -1)),
                    _cache[970] || (_cache[970] = createTextVNode()),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [..._cache[968] || (_cache[968] = [
                        createTextVNode("Boolean", -1)
                      ])]),
                      _: 1
                    }),
                    _cache[971] || (_cache[971] = createBaseVNode("ul", null, [
                      createBaseVNode("li", null, "Mirror the haptic state and process haptic feedback to the secondary half."),
                      createBaseVNode("li", null, [
                        createTextVNode("Default: "),
                        createBaseVNode("code", null, "false")
                      ])
                    ], -1))
                  ]),
                  createBaseVNode("li", null, [
                    _cache[973] || (_cache[973] = createBaseVNode("code", null, "layer_state", -1)),
                    _cache[974] || (_cache[974] = createTextVNode()),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [..._cache[972] || (_cache[972] = [
                        createTextVNode("Boolean", -1)
                      ])]),
                      _: 1
                    }),
                    _cache[975] || (_cache[975] = createBaseVNode("ul", null, [
                      createBaseVNode("li", null, "Mirror the layer state to the secondary half."),
                      createBaseVNode("li", null, [
                        createTextVNode("Default: "),
                        createBaseVNode("code", null, "false")
                      ])
                    ], -1))
                  ]),
                  createBaseVNode("li", null, [
                    _cache[977] || (_cache[977] = createBaseVNode("code", null, "indicators", -1)),
                    _cache[978] || (_cache[978] = createTextVNode()),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [..._cache[976] || (_cache[976] = [
                        createTextVNode("Boolean", -1)
                      ])]),
                      _: 1
                    }),
                    _cache[979] || (_cache[979] = createBaseVNode("ul", null, [
                      createBaseVNode("li", null, "Mirror the indicator state to the secondary half."),
                      createBaseVNode("li", null, [
                        createTextVNode("Default: "),
                        createBaseVNode("code", null, "false")
                      ])
                    ], -1))
                  ]),
                  createBaseVNode("li", null, [
                    _cache[981] || (_cache[981] = createBaseVNode("code", null, "matrix_state", -1)),
                    _cache[982] || (_cache[982] = createTextVNode()),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [..._cache[980] || (_cache[980] = [
                        createTextVNode("Boolean", -1)
                      ])]),
                      _: 1
                    }),
                    _cache[983] || (_cache[983] = createBaseVNode("ul", null, [
                      createBaseVNode("li", null, "Mirror the main/primary half's matrix state to the secondary half."),
                      createBaseVNode("li", null, [
                        createTextVNode("Default: "),
                        createBaseVNode("code", null, "false")
                      ])
                    ], -1))
                  ]),
                  createBaseVNode("li", null, [
                    _cache[985] || (_cache[985] = createBaseVNode("code", null, "modifiers", -1)),
                    _cache[986] || (_cache[986] = createTextVNode()),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [..._cache[984] || (_cache[984] = [
                        createTextVNode("Boolean", -1)
                      ])]),
                      _: 1
                    }),
                    _cache[987] || (_cache[987] = createBaseVNode("ul", null, [
                      createBaseVNode("li", null, "Mirror the modifier state to the secondary half."),
                      createBaseVNode("li", null, [
                        createTextVNode("Default: "),
                        createBaseVNode("code", null, "false")
                      ])
                    ], -1))
                  ]),
                  createBaseVNode("li", null, [
                    _cache[989] || (_cache[989] = createBaseVNode("code", null, "oled", -1)),
                    _cache[990] || (_cache[990] = createTextVNode()),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [..._cache[988] || (_cache[988] = [
                        createTextVNode("Boolean", -1)
                      ])]),
                      _: 1
                    }),
                    _cache[991] || (_cache[991] = createBaseVNode("ul", null, [
                      createBaseVNode("li", null, "Mirror the OLED on/off status to the secondary half."),
                      createBaseVNode("li", null, [
                        createTextVNode("Default: "),
                        createBaseVNode("code", null, "false")
                      ])
                    ], -1))
                  ]),
                  createBaseVNode("li", null, [
                    _cache[993] || (_cache[993] = createBaseVNode("code", null, "st7565", -1)),
                    _cache[994] || (_cache[994] = createTextVNode()),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [..._cache[992] || (_cache[992] = [
                        createTextVNode("Boolean", -1)
                      ])]),
                      _: 1
                    }),
                    _cache[995] || (_cache[995] = createBaseVNode("ul", null, [
                      createBaseVNode("li", null, "Mirror the ST7565 on/off status to the secondary half."),
                      createBaseVNode("li", null, [
                        createTextVNode("Default: "),
                        createBaseVNode("code", null, "false")
                      ])
                    ], -1))
                  ]),
                  createBaseVNode("li", null, [
                    _cache[997] || (_cache[997] = createBaseVNode("code", null, "wpm", -1)),
                    _cache[998] || (_cache[998] = createTextVNode()),
                    createVNode(_component_Badge, { type: "info" }, {
                      default: withCtx(() => [..._cache[996] || (_cache[996] = [
                        createTextVNode("Boolean", -1)
                      ])]),
                      _: 1
                    }),
                    _cache[999] || (_cache[999] = createBaseVNode("ul", null, [
                      createBaseVNode("li", null, "Mirror the current WPM value to the secondary half."),
                      createBaseVNode("li", null, [
                        createTextVNode("Default: "),
                        createBaseVNode("code", null, "false")
                      ])
                    ], -1))
                  ])
                ])
              ]),
              createBaseVNode("li", null, [
                _cache[1002] || (_cache[1002] = createBaseVNode("code", null, "watchdog", -1)),
                _cache[1003] || (_cache[1003] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[1001] || (_cache[1001] = [
                    createTextVNode("Boolean", -1)
                  ])]),
                  _: 1
                }),
                _cache[1004] || (_cache[1004] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "Reboot the secondary half if it loses connection."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "false")
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[1006] || (_cache[1006] = createBaseVNode("code", null, "watchdog_timeout", -1)),
                _cache[1007] || (_cache[1007] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[1005] || (_cache[1005] = [
                    createTextVNode("Number", -1)
                  ])]),
                  _: 1
                }),
                _cache[1008] || (_cache[1008] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The amount of time to wait for communication from the primary half in milliseconds.")
                ], -1))
              ])
            ])
          ]),
          createBaseVNode("li", null, [
            _cache[1022] || (_cache[1022] = createBaseVNode("code", null, "usb_detect", -1)),
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _cache[1011] || (_cache[1011] = createBaseVNode("code", null, "enabled", -1)),
                _cache[1012] || (_cache[1012] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[1010] || (_cache[1010] = [
                    createTextVNode("Boolean", -1)
                  ])]),
                  _: 1
                }),
                _cache[1013] || (_cache[1013] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "Detect USB connection when determining split half roles.")
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[1015] || (_cache[1015] = createBaseVNode("code", null, "polling_interval", -1)),
                _cache[1016] || (_cache[1016] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[1014] || (_cache[1014] = [
                    createTextVNode("Number", -1)
                  ])]),
                  _: 1
                }),
                _cache[1017] || (_cache[1017] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The polling frequency in milliseconds."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "10"),
                    createTextVNode(" (10 ms)")
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[1019] || (_cache[1019] = createBaseVNode("code", null, "timeout", -1)),
                _cache[1020] || (_cache[1020] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[1018] || (_cache[1018] = [
                    createTextVNode("Number", -1)
                  ])]),
                  _: 1
                }),
                _cache[1021] || (_cache[1021] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "The amount of time to wait for a USB connection in milliseconds."),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "2000"),
                    createTextVNode(" (2 seconds)")
                  ])
                ], -1))
              ])
            ])
          ])
        ])
      ])
    ]),
    _cache[1158] || (_cache[1158] = createBaseVNode("h2", {
      id: "stenography",
      tabindex: "-1"
    }, [
      createTextVNode("Stenography "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#stenography",
        "aria-label": 'Permalink to "Stenography {#stenography}"'
      }, "​")
    ], -1)),
    _cache[1159] || (_cache[1159] = createBaseVNode("p", null, [
      createTextVNode("Configures the "),
      createBaseVNode("a", { href: "./features/stenography" }, "Stenography"),
      createTextVNode(" feature.")
    ], -1)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[1035] || (_cache[1035] = createBaseVNode("code", null, "stenography", -1)),
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _cache[1028] || (_cache[1028] = createBaseVNode("code", null, "enabled", -1)),
            _cache[1029] || (_cache[1029] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[1027] || (_cache[1027] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[1030] || (_cache[1030] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Enable the Stenography feature."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[1032] || (_cache[1032] = createBaseVNode("code", null, "protocol", -1)),
            _cache[1033] || (_cache[1033] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[1031] || (_cache[1031] = [
                createTextVNode("String", -1)
              ])]),
              _: 1
            }),
            _cache[1034] || (_cache[1034] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("The Steno protocol to use. Must be one of "),
                createBaseVNode("code", null, "all"),
                createTextVNode(", "),
                createBaseVNode("code", null, "geminipr"),
                createTextVNode(", "),
                createBaseVNode("code", null, "txbolt"),
                createTextVNode(".")
              ]),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, '"all"')
              ])
            ], -1))
          ])
        ])
      ])
    ]),
    _cache[1160] || (_cache[1160] = createBaseVNode("h2", {
      id: "usb",
      tabindex: "-1"
    }, [
      createTextVNode("USB "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#usb",
        "aria-label": 'Permalink to "USB {#usb}"'
      }, "​")
    ], -1)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[1083] || (_cache[1083] = createBaseVNode("code", null, "usb", -1)),
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _cache[1038] || (_cache[1038] = createBaseVNode("code", null, "device_version", -1)),
            _cache[1039] || (_cache[1039] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[1036] || (_cache[1036] = [
                createTextVNode("String", -1)
              ])]),
              _: 1
            }),
            _cache[1040] || (_cache[1040] = createTextVNode()),
            createVNode(_component_Badge, null, {
              default: withCtx(() => [..._cache[1037] || (_cache[1037] = [
                createTextVNode("Required", -1)
              ])]),
              _: 1
            }),
            _cache[1041] || (_cache[1041] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("A BCD version number in the format "),
                createBaseVNode("code", null, "MM.m.r"),
                createTextVNode(" (up to "),
                createBaseVNode("code", null, "99.9.9"),
                createTextVNode(").")
              ]),
              createBaseVNode("li", null, [
                createTextVNode("Example: "),
                createBaseVNode("code", null, '"1.0.0"')
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[1044] || (_cache[1044] = createBaseVNode("code", null, "pid", -1)),
            _cache[1045] || (_cache[1045] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[1042] || (_cache[1042] = [
                createTextVNode("String", -1)
              ])]),
              _: 1
            }),
            _cache[1046] || (_cache[1046] = createTextVNode()),
            createVNode(_component_Badge, null, {
              default: withCtx(() => [..._cache[1043] || (_cache[1043] = [
                createTextVNode("Required", -1)
              ])]),
              _: 1
            }),
            _cache[1047] || (_cache[1047] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The USB product ID as a four-digit hexadecimal number."),
              createBaseVNode("li", null, [
                createTextVNode("Example: "),
                createBaseVNode("code", null, '"0x23B0"')
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[1050] || (_cache[1050] = createBaseVNode("code", null, "vid", -1)),
            _cache[1051] || (_cache[1051] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[1048] || (_cache[1048] = [
                createTextVNode("String", -1)
              ])]),
              _: 1
            }),
            _cache[1052] || (_cache[1052] = createTextVNode()),
            createVNode(_component_Badge, null, {
              default: withCtx(() => [..._cache[1049] || (_cache[1049] = [
                createTextVNode("Required", -1)
              ])]),
              _: 1
            }),
            _cache[1053] || (_cache[1053] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The USB vendor ID as a four-digit hexadecimal number."),
              createBaseVNode("li", null, [
                createTextVNode("Example: "),
                createBaseVNode("code", null, '"0xC1ED"')
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[1055] || (_cache[1055] = createBaseVNode("code", null, "max_power", -1)),
            _cache[1056] || (_cache[1056] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[1054] || (_cache[1054] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[1057] || (_cache[1057] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The maximum current draw the host should expect from the device. This does not control the actual current usage."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "500"),
                createTextVNode(" (500 mA)")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[1059] || (_cache[1059] = createBaseVNode("code", null, "no_startup_check", -1)),
            _cache[1060] || (_cache[1060] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[1058] || (_cache[1058] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[1061] || (_cache[1061] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Disable USB suspend check after keyboard startup."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[1063] || (_cache[1063] = createBaseVNode("code", null, "polling_interval", -1)),
            _cache[1064] || (_cache[1064] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[1062] || (_cache[1062] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[1065] || (_cache[1065] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The frequency at which the host should poll the keyboard for reports."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "1"),
                createTextVNode(" (1 ms/1000 Hz)")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[1074] || (_cache[1074] = createBaseVNode("code", null, "shared_endpoint", -1)),
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                _cache[1067] || (_cache[1067] = createBaseVNode("code", null, "keyboard", -1)),
                _cache[1068] || (_cache[1068] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[1066] || (_cache[1066] = [
                    createTextVNode("Boolean", -1)
                  ])]),
                  _: 1
                }),
                _cache[1069] || (_cache[1069] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, 'Send keyboard reports through the "shared" USB endpoint.'),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "false")
                  ])
                ], -1))
              ]),
              createBaseVNode("li", null, [
                _cache[1071] || (_cache[1071] = createBaseVNode("code", null, "mouse", -1)),
                _cache[1072] || (_cache[1072] = createTextVNode()),
                createVNode(_component_Badge, { type: "info" }, {
                  default: withCtx(() => [..._cache[1070] || (_cache[1070] = [
                    createTextVNode("Boolean", -1)
                  ])]),
                  _: 1
                }),
                _cache[1073] || (_cache[1073] = createBaseVNode("ul", null, [
                  createBaseVNode("li", null, 'Send mouse reports through the "shared" USB endpoint.'),
                  createBaseVNode("li", null, [
                    createTextVNode("Default: "),
                    createBaseVNode("code", null, "true")
                  ])
                ], -1))
              ])
            ])
          ]),
          createBaseVNode("li", null, [
            _cache[1076] || (_cache[1076] = createBaseVNode("code", null, "suspend_wakeup_delay", -1)),
            _cache[1077] || (_cache[1077] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[1075] || (_cache[1075] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[1078] || (_cache[1078] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "The amount of time to wait after sending a wakeup packet, in milliseconds."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "0"),
                createTextVNode(" (disabled)")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[1080] || (_cache[1080] = createBaseVNode("code", null, "wait_for_enumeration", -1)),
            _cache[1081] || (_cache[1081] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[1079] || (_cache[1079] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[1082] || (_cache[1082] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Force the keyboard to wait for USB enumeration before starting up."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ])
        ])
      ])
    ]),
    _cache[1161] || (_cache[1161] = createBaseVNode("h2", {
      id: "ws2812",
      tabindex: "-1"
    }, [
      createTextVNode("WS2812 "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#ws2812",
        "aria-label": 'Permalink to "WS2812 {#ws2812}"'
      }, "​")
    ], -1)),
    _cache[1162] || (_cache[1162] = createBaseVNode("p", null, [
      createTextVNode("Configures the "),
      createBaseVNode("a", { href: "./drivers/ws2812" }, "WS2812"),
      createTextVNode(" driver.")
    ], -1)),
    createBaseVNode("ul", null, [
      createBaseVNode("li", null, [
        _cache[1106] || (_cache[1106] = createBaseVNode("code", null, "ws2812", -1)),
        createBaseVNode("ul", null, [
          createBaseVNode("li", null, [
            _cache[1085] || (_cache[1085] = createBaseVNode("code", null, "driver", -1)),
            _cache[1086] || (_cache[1086] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[1084] || (_cache[1084] = [
                createTextVNode("String", -1)
              ])]),
              _: 1
            }),
            _cache[1087] || (_cache[1087] = createStaticVNode("<ul><li>The driver to use. Must be one of <code>bitbang</code>, <code>custom</code>, <code>i2c</code>, <code>pwm</code>, <code>spi</code>, <code>vendor</code>.</li><li>Default: <code>&quot;bitbang&quot;</code></li></ul>", 1))
          ]),
          createBaseVNode("li", null, [
            _cache[1090] || (_cache[1090] = createBaseVNode("code", null, "pin", -1)),
            _cache[1091] || (_cache[1091] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[1088] || (_cache[1088] = [
                createTextVNode("Pin", -1)
              ])]),
              _: 1
            }),
            _cache[1092] || (_cache[1092] = createTextVNode()),
            createVNode(_component_Badge, null, {
              default: withCtx(() => [..._cache[1089] || (_cache[1089] = [
                createTextVNode("Required", -1)
              ])]),
              _: 1
            }),
            _cache[1093] || (_cache[1093] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("The GPIO pin connected to "),
                createBaseVNode("code", null, "DI"),
                createTextVNode(" on the first LED in the chain ("),
                createBaseVNode("code", null, "bitbang"),
                createTextVNode(", "),
                createBaseVNode("code", null, "pwm"),
                createTextVNode(", "),
                createBaseVNode("code", null, "spi"),
                createTextVNode(" and "),
                createBaseVNode("code", null, "vendor"),
                createTextVNode(" drivers only).")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[1095] || (_cache[1095] = createBaseVNode("code", null, "i2c_address", -1)),
            _cache[1096] || (_cache[1096] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[1094] || (_cache[1094] = [
                createTextVNode("String", -1)
              ])]),
              _: 1
            }),
            _cache[1097] || (_cache[1097] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("The I²C address of the WS2812 controller ("),
                createBaseVNode("code", null, "i2c"),
                createTextVNode(" driver only).")
              ]),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, '"0xB0"')
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[1099] || (_cache[1099] = createBaseVNode("code", null, "i2c_timeout", -1)),
            _cache[1100] || (_cache[1100] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[1098] || (_cache[1098] = [
                createTextVNode("Number", -1)
              ])]),
              _: 1
            }),
            _cache[1101] || (_cache[1101] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("The I²C timeout in milliseconds ("),
                createBaseVNode("code", null, "i2c"),
                createTextVNode(" driver only).")
              ]),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "100"),
                createTextVNode(" (100 ms)")
              ])
            ], -1))
          ]),
          createBaseVNode("li", null, [
            _cache[1103] || (_cache[1103] = createBaseVNode("code", null, "rgbw", -1)),
            _cache[1104] || (_cache[1104] = createTextVNode()),
            createVNode(_component_Badge, { type: "info" }, {
              default: withCtx(() => [..._cache[1102] || (_cache[1102] = [
                createTextVNode("Boolean", -1)
              ])]),
              _: 1
            }),
            _cache[1105] || (_cache[1105] = createBaseVNode("ul", null, [
              createBaseVNode("li", null, "Enable RGBW LEDs."),
              createBaseVNode("li", null, [
                createTextVNode("Default: "),
                createBaseVNode("code", null, "false")
              ])
            ], -1))
          ])
        ])
      ])
    ])
  ]);
}
const reference_info_json = /* @__PURE__ */ _export_sfc(_sfc_main, [["render", _sfc_render]]);
export {
  __pageData,
  reference_info_json as default
};
