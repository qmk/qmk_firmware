import { _ as _export_sfc, C as resolveComponent, o as openBlock, c as createElementBlock, al as createStaticVNode, E as createVNode, w as withCtx, j as createBaseVNode, a as createTextVNode } from "./chunks/framework.8zKZLKO7.js";
const __pageData = JSON.parse('{"title":"Quantum Painter","description":"","frontmatter":{},"headers":[],"relativePath":"quantum_painter.md","filePath":"quantum_painter.md","lastUpdated":null}');
const _sfc_main = { name: "quantum_painter.md" };
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  const _component_PluginTabsTab = resolveComponent("PluginTabsTab");
  const _component_PluginTabs = resolveComponent("PluginTabs");
  return openBlock(), createElementBlock("div", null, [
    _cache[58] || (_cache[58] = createStaticVNode("", 14)),
    createVNode(_component_PluginTabs, null, {
      default: withCtx(() => [
        createVNode(_component_PluginTabsTab, { label: "`qmk painter-convert-graphics`" }, {
          default: withCtx(() => [..._cache[0] || (_cache[0] = [
            createBaseVNode("p", null, "This command converts images to a format usable by QMK, i.e. the QGF File Format.", -1),
            createBaseVNode("p", null, [
              createBaseVNode("strong", null, "Usage"),
              createTextVNode(":")
            ], -1),
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
                    createBaseVNode("span", null, "usage: qmk painter-convert-graphics [-h] [-w] [-d] [-r] -f FORMAT [-o OUTPUT] -i INPUT [-v]")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "options:")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "  -h, --help            show this help message and exit")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "  -w, --raw             Writes out the QGF file as raw data instead of c/h combo.")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "  -d, --no-deltas       Disables the use of delta frames when encoding animations.")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "  -r, --no-rle          Disables the use of RLE when encoding images.")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "  -f FORMAT, --format FORMAT")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "                        Output format, valid types: rgb888, rgb565, pal256, pal16, pal4, pal2, mono256, mono16, mono4, mono2")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "  -o OUTPUT, --output OUTPUT")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "                        Specify output directory. Defaults to same directory as input.")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "  -i INPUT, --input INPUT")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "                        Specify input graphic file.")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "  -v, --verbose         Turns on verbose output.")
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("The "),
              createBaseVNode("code", null, "INPUT"),
              createTextVNode(" argument can be any image file loadable by Python's Pillow module. Common formats include PNG, or Animated GIF.")
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("The "),
              createBaseVNode("code", null, "OUTPUT"),
              createTextVNode(" argument needs to be a directory, and will default to the same directory as the input argument.")
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("The "),
              createBaseVNode("code", null, "FORMAT"),
              createTextVNode(" argument can be any of the following:")
            ], -1),
            createBaseVNode("table", { tabindex: "0" }, [
              createBaseVNode("thead", null, [
                createBaseVNode("tr", null, [
                  createBaseVNode("th", null, "Format"),
                  createBaseVNode("th", null, "Meaning")
                ])
              ]),
              createBaseVNode("tbody", null, [
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "rgb888")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("16,777,216 colors in 8-8-8 RGB format (requires "),
                    createBaseVNode("code", null, "QUANTUM_PAINTER_SUPPORTS_NATIVE_COLORS"),
                    createTextVNode(")")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "rgb565")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("65,536 colors in 5-6-5 RGB format (requires "),
                    createBaseVNode("code", null, "QUANTUM_PAINTER_SUPPORTS_NATIVE_COLORS"),
                    createTextVNode(")")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "pal256")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("256-color palette (requires "),
                    createBaseVNode("code", null, "QUANTUM_PAINTER_SUPPORTS_256_PALETTE"),
                    createTextVNode(")")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "pal16")
                  ]),
                  createBaseVNode("td", null, "16-color palette")
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "pal4")
                  ]),
                  createBaseVNode("td", null, "4-color palette")
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "pal2")
                  ]),
                  createBaseVNode("td", null, "2-color palette")
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "mono256")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("256-shade grayscale (requires "),
                    createBaseVNode("code", null, "QUANTUM_PAINTER_SUPPORTS_256_PALETTE"),
                    createTextVNode(")")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "mono16")
                  ]),
                  createBaseVNode("td", null, "16-shade grayscale")
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "mono4")
                  ]),
                  createBaseVNode("td", null, "4-shade grayscale")
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "mono2")
                  ]),
                  createBaseVNode("td", null, "2-shade grayscale")
                ])
              ])
            ], -1),
            createBaseVNode("p", null, [
              createBaseVNode("strong", null, "Examples"),
              createTextVNode(":")
            ], -1),
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
                    createBaseVNode("span", null, "$ cd /home/qmk/qmk_firmware/keyboards/my_keeb")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "$ qmk painter-convert-graphics -f mono16 -i my_image.gif -o ./generated/")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "Writing /home/qmk/qmk_firmware/keyboards/my_keeb/generated/my_image.qgf.h...")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "Writing /home/qmk/qmk_firmware/keyboards/my_keeb/generated/my_image.qgf.c...")
                  ])
                ])
              ])
            ], -1)
          ])]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "`qmk painter-make-font-image`" }, {
          default: withCtx(() => [..._cache[1] || (_cache[1] = [
            createBaseVNode("p", null, "This command converts a TTF font to an intermediate format for editing, before converting to the QFF File Format.", -1),
            createBaseVNode("p", null, [
              createBaseVNode("strong", null, "Usage"),
              createTextVNode(":")
            ], -1),
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
                    createBaseVNode("span", null, "usage: qmk painter-make-font-image [-h] [-a] [-u UNICODE_GLYPHS] [-n] [-s SIZE] -o OUTPUT -f FONT")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "optional arguments:")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "  -h, --help            show this help message and exit")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "  -a, --no-aa           Disable anti-aliasing on fonts.")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "  -u UNICODE_GLYPHS, --unicode-glyphs UNICODE_GLYPHS")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "                        Also generate the specified unicode glyphs.")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "  -n, --no-ascii        Disables output of the full ASCII character set (0x20..0x7E), exporting only the glyphs specified.")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "  -s SIZE, --size SIZE  Specify font size. Default 12.")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "  -o OUTPUT, --output OUTPUT")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "                        Specify output image path.")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "  -f FONT, --font FONT  Specify input font file.")
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("The "),
              createBaseVNode("code", null, "FONT"),
              createTextVNode(" argument is generally a TrueType Font file (TTF).")
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("The "),
              createBaseVNode("code", null, "OUTPUT"),
              createTextVNode(" argument is the output image to generate, generally something like "),
              createBaseVNode("code", null, "my_font.png"),
              createTextVNode(".")
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("The "),
              createBaseVNode("code", null, "UNICODE_GLYPHS"),
              createTextVNode(" argument allows for specifying extra unicode glyphs to generate, and accepts a string.")
            ], -1),
            createBaseVNode("p", null, [
              createBaseVNode("strong", null, "Examples"),
              createTextVNode(":")
            ], -1),
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
                    createBaseVNode("span", null, '$ qmk painter-make-font-image --font NotoSans-ExtraCondensedBold.ttf --size 11 -o noto11.png --unicode-glyphs "ĄȽɂɻɣɈʣ"')
                  ])
                ])
              ])
            ], -1)
          ])]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "`qmk painter-convert-font-image`" }, {
          default: withCtx(() => [..._cache[2] || (_cache[2] = [
            createBaseVNode("p", null, "This command converts an intermediate font image to the QFF File Format.", -1),
            createBaseVNode("p", null, "This command expects an image that conforms to the following format:", -1),
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("Top-left pixel (at "),
                createBaseVNode("code", null, "0,0"),
                createTextVNode(') is the "delimiter" color: '),
                createBaseVNode("ul", null, [
                  createBaseVNode("li", null, "Each glyph in the font starts when a pixel of this color is found on the first row"),
                  createBaseVNode("li", null, "The first row is discarded when converting to the QFF format")
                ])
              ]),
              createBaseVNode("li", null, [
                createTextVNode("The number of delimited glyphs must match the supplied arguments to the command: "),
                createBaseVNode("ul", null, [
                  createBaseVNode("li", null, [
                    createTextVNode("The full ASCII set "),
                    createBaseVNode("code", null, "0x20..0x7E"),
                    createTextVNode(" (if "),
                    createBaseVNode("code", null, "--no-ascii"),
                    createTextVNode(" was not specified)")
                  ]),
                  createBaseVNode("li", null, [
                    createTextVNode("The corresponding number of unicode glyphs if any were specified with "),
                    createBaseVNode("code", null, "--unicode-glyphs")
                  ])
                ])
              ]),
              createBaseVNode("li", null, "The order of the glyphs matches the ASCII set, if any, followed by the Unicode glyph set, if any.")
            ], -1),
            createBaseVNode("p", null, [
              createBaseVNode("strong", null, "Usage"),
              createTextVNode(":")
            ], -1),
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
                    createBaseVNode("span", null, "usage: qmk painter-convert-font-image [-h] [-w] [-r] -f FORMAT [-u UNICODE_GLYPHS] [-n] [-o OUTPUT] [-i INPUT]")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "options:")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "  -h, --help            show this help message and exit")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "  -w, --raw             Writes out the QFF file as raw data instead of c/h combo.")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "  -r, --no-rle          Disable the use of RLE to minimise converted image size.")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "  -f FORMAT, --format FORMAT")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "                        Output format, valid types: rgb565, pal256, pal16, pal4, pal2, mono256, mono16, mono4, mono2")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "  -u UNICODE_GLYPHS, --unicode-glyphs UNICODE_GLYPHS")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "                        Also generate the specified unicode glyphs.")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "  -n, --no-ascii        Disables output of the full ASCII character set (0x20..0x7E), exporting only the glyphs specified.")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "  -o OUTPUT, --output OUTPUT")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "                        Specify output directory. Defaults to same directory as input.")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "  -i INPUT, --input INPUT")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "                        Specify input graphic file.")
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("The same arguments for "),
              createBaseVNode("code", null, "--no-ascii"),
              createTextVNode(" and "),
              createBaseVNode("code", null, "--unicode-glyphs"),
              createTextVNode(" need to be specified, as per "),
              createBaseVNode("code", null, "qmk painter-make-font-image"),
              createTextVNode(".")
            ], -1),
            createBaseVNode("p", null, [
              createBaseVNode("strong", null, "Examples"),
              createTextVNode(":")
            ], -1),
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
                    createBaseVNode("span", null, "$ cd /home/qmk/qmk_firmware/keyboards/my_keeb")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, '$ qmk painter-convert-font-image --input noto11.png -f mono4 --unicode-glyphs "ĄȽɂɻɣɈʣ"')
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "Writing /home/qmk/qmk_firmware/keyboards/my_keeb/generated/noto11.qff.h...")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", null, "Writing /home/qmk/qmk_firmware/keyboards/my_keeb/generated/noto11.qff.c...")
                  ])
                ])
              ])
            ], -1)
          ])]),
          _: 1
        })
      ]),
      _: 1
    }),
    _cache[59] || (_cache[59] = createBaseVNode("h2", {
      id: "quantum-painter-drivers",
      tabindex: "-1"
    }, [
      createTextVNode("Quantum Painter Display Drivers "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#quantum-painter-drivers",
        "aria-label": 'Permalink to "Quantum Painter Display Drivers {#quantum-painter-drivers}"'
      }, "​")
    ], -1)),
    createVNode(_component_PluginTabs, null, {
      default: withCtx(() => [
        createVNode(_component_PluginTabsTab, { label: "LCD" }, {
          default: withCtx(() => [
            _cache[10] || (_cache[10] = createBaseVNode("p", null, "Most TFT display panels use a 5-pin interface -- SPI SCK, SPI MOSI, SPI CS, D/C, and RST pins.", -1)),
            _cache[11] || (_cache[11] = createBaseVNode("p", null, [
              createTextVNode("For these displays, QMK's "),
              createBaseVNode("code", null, "spi_master"),
              createTextVNode(" must already be correctly configured for the platform you're building for.")
            ], -1)),
            _cache[12] || (_cache[12] = createBaseVNode("p", null, "The pin assignments for SPI CS, D/C, and RST are specified during device construction.", -1)),
            createVNode(_component_PluginTabs, null, {
              default: withCtx(() => [
                createVNode(_component_PluginTabsTab, { label: "GC9A01" }, {
                  default: withCtx(() => [..._cache[3] || (_cache[3] = [
                    createBaseVNode("p", null, [
                      createTextVNode("Enabling support for the GC9A01 in Quantum Painter is done by adding the following to "),
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
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "QUANTUM_PAINTER_ENABLE = yes")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "QUANTUM_PAINTER_DRIVERS += gc9a01_spi")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, "Creating a GC9A01 device in firmware can then be done with the following API:", -1),
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
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_gc9a01_make_spi_device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_width"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_height"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " chip_select_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " dc_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " reset_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " spi_divisor"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "int"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " spi_mode"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The device handle returned from the "),
                      createBaseVNode("code", null, "qp_gc9a01_make_spi_device"),
                      createTextVNode(" function can be used to perform all other drawing operations.")
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The maximum number of displays can be configured by changing the following in your "),
                      createBaseVNode("code", null, "config.h"),
                      createTextVNode(" (default is 1):")
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
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "// 3 displays:")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " GC9A01_NUM_DEVICES"),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 3")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, "Native color format rgb565 is compatible with GC9A01", -1)
                  ])]),
                  _: 1
                }),
                createVNode(_component_PluginTabsTab, { label: "ILI9163" }, {
                  default: withCtx(() => [..._cache[4] || (_cache[4] = [
                    createBaseVNode("p", null, [
                      createTextVNode("Enabling support for the ILI9163 in Quantum Painter is done by adding the following to "),
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
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "QUANTUM_PAINTER_ENABLE = yes")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "QUANTUM_PAINTER_DRIVERS += ili9163_spi")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, "Creating a ILI9163 device in firmware can then be done with the following API:", -1),
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
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_ili9163_make_spi_device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_width"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_height"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " chip_select_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " dc_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " reset_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " spi_divisor"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "int"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " spi_mode"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The device handle returned from the "),
                      createBaseVNode("code", null, "qp_ili9163_make_spi_device"),
                      createTextVNode(" function can be used to perform all other drawing operations.")
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The maximum number of displays can be configured by changing the following in your "),
                      createBaseVNode("code", null, "config.h"),
                      createTextVNode(" (default is 1):")
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
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "// 3 displays:")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " ILI9163_NUM_DEVICES"),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 3")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, "Native color format rgb565 is compatible with ILI9163", -1)
                  ])]),
                  _: 1
                }),
                createVNode(_component_PluginTabsTab, { label: "ILI9341" }, {
                  default: withCtx(() => [..._cache[5] || (_cache[5] = [
                    createBaseVNode("p", null, [
                      createTextVNode("Enabling support for the ILI9341 in Quantum Painter is done by adding the following to "),
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
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "QUANTUM_PAINTER_ENABLE = yes")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "QUANTUM_PAINTER_DRIVERS += ili9341_spi")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, "Creating a ILI9341 device in firmware can then be done with the following API:", -1),
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
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_ili9341_make_spi_device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_width"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_height"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " chip_select_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " dc_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " reset_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " spi_divisor"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "int"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " spi_mode"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The device handle returned from the "),
                      createBaseVNode("code", null, "qp_ili9341_make_spi_device"),
                      createTextVNode(" function can be used to perform all other drawing operations.")
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The maximum number of displays can be configured by changing the following in your "),
                      createBaseVNode("code", null, "config.h"),
                      createTextVNode(" (default is 1):")
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
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "// 3 displays:")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " ILI9341_NUM_DEVICES"),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 3")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, "Native color format rgb565 is compatible with ILI9341", -1)
                  ])]),
                  _: 1
                }),
                createVNode(_component_PluginTabsTab, { label: "ILI9486" }, {
                  default: withCtx(() => [..._cache[6] || (_cache[6] = [
                    createBaseVNode("p", null, [
                      createTextVNode("Enabling support for the ILI9486 in Quantum Painter is done by adding the following to "),
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
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "QUANTUM_PAINTER_ENABLE = yes")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "QUANTUM_PAINTER_DRIVERS += ili9486_spi")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, "Creating a ILI9486 device in firmware can then be done with the following API:", -1),
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
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_ili9486_make_spi_device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_width"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_height"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " chip_select_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " dc_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " reset_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " spi_divisor"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "int"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " spi_mode"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("There's another variant for this "),
                      createBaseVNode("a", {
                        href: "https://www.waveshare.com/wiki/3.5inch_TFT_Touch_Shield",
                        target: "_blank",
                        rel: "noreferrer"
                      }, "Waveshare module"),
                      createTextVNode(", because it has a quirky SPI->Parallel converter. You can create it with:")
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
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_ili9486_make_spi_waveshare_device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_width"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_height"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " chip_select_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " dc_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " reset_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " spi_divisor"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "int"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " spi_mode"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, "The device handle returned from these functions can be used to perform all other drawing operations.", -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The maximum number of displays can be configured by changing the following in your "),
                      createBaseVNode("code", null, "config.h"),
                      createTextVNode(" (default is 1):")
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
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "// 3 displays:")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " ILI9486_NUM_DEVICES"),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 3")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, "Native color format rgb888 is compatible with ILI9486 Native color format rgb565 is compatible with ILI9486 Waveshare", -1)
                  ])]),
                  _: 1
                }),
                createVNode(_component_PluginTabsTab, { label: "ILI9488" }, {
                  default: withCtx(() => [..._cache[7] || (_cache[7] = [
                    createBaseVNode("p", null, [
                      createTextVNode("Enabling support for the ILI9488 in Quantum Painter is done by adding the following to "),
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
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "QUANTUM_PAINTER_ENABLE = yes")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "QUANTUM_PAINTER_DRIVERS += ili9488_spi")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, "Creating a ILI9488 device in firmware can then be done with the following API:", -1),
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
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_ili9488_make_spi_device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_width"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_height"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " chip_select_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " dc_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " reset_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " spi_divisor"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "int"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " spi_mode"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The device handle returned from the "),
                      createBaseVNode("code", null, "qp_ili9488_make_spi_device"),
                      createTextVNode(" function can be used to perform all other drawing operations.")
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The maximum number of displays can be configured by changing the following in your "),
                      createBaseVNode("code", null, "config.h"),
                      createTextVNode(" (default is 1):")
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
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "// 3 displays:")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " ILI9488_NUM_DEVICES"),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 3")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, "Native color format rgb888 is compatible with ILI9488", -1)
                  ])]),
                  _: 1
                }),
                createVNode(_component_PluginTabsTab, { label: "ST7735" }, {
                  default: withCtx(() => [..._cache[8] || (_cache[8] = [
                    createBaseVNode("p", null, [
                      createTextVNode("Enabling support for the ST7735 in Quantum Painter is done by adding the following to "),
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
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "QUANTUM_PAINTER_ENABLE = yes")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "QUANTUM_PAINTER_DRIVERS += st7735_spi")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, "Creating a ST7735 device in firmware can then be done with the following API:", -1),
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
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_st7735_make_spi_device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_width"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_height"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " chip_select_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " dc_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " reset_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " spi_divisor"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "int"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " spi_mode"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The device handle returned from the "),
                      createBaseVNode("code", null, "qp_st7735_make_spi_device"),
                      createTextVNode(" function can be used to perform all other drawing operations.")
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The maximum number of displays can be configured by changing the following in your "),
                      createBaseVNode("code", null, "config.h"),
                      createTextVNode(" (default is 1):")
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
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "// 3 displays:")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " ST7735_NUM_DEVICES"),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 3")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, "Native color format rgb565 is compatible with ST7735", -1),
                    createBaseVNode("div", { class: "warning custom-block" }, [
                      createBaseVNode("p", { class: "custom-block-title" }, "WARNING"),
                      createBaseVNode("p", null, [
                        createTextVNode("Some ST7735 devices are known to have different drawing offsets -- despite being a 132x162 pixel display controller internally, some display panels are only 80x160, or smaller. These may require an offset to be applied; see "),
                        createBaseVNode("code", null, "qp_set_viewport_offsets"),
                        createTextVNode(" above for information on how to override the offsets if they aren't correctly rendered.")
                      ])
                    ], -1)
                  ])]),
                  _: 1
                }),
                createVNode(_component_PluginTabsTab, { label: "ST7789" }, {
                  default: withCtx(() => [..._cache[9] || (_cache[9] = [
                    createBaseVNode("p", null, [
                      createTextVNode("Enabling support for the ST7789 in Quantum Painter is done by adding the following to "),
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
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "QUANTUM_PAINTER_ENABLE = yes")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "QUANTUM_PAINTER_DRIVERS += st7789_spi")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, "Creating a ST7789 device in firmware can then be done with the following API:", -1),
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
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_st7789_make_spi_device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_width"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_height"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " chip_select_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " dc_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " reset_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " spi_divisor"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "int"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " spi_mode"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The device handle returned from the "),
                      createBaseVNode("code", null, "qp_st7789_make_spi_device"),
                      createTextVNode(" function can be used to perform all other drawing operations.")
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The maximum number of displays can be configured by changing the following in your "),
                      createBaseVNode("code", null, "config.h"),
                      createTextVNode(" (default is 1):")
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
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "// 3 displays:")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " ST7789_NUM_DEVICES"),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 3")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, "Native color format rgb565 is compatible with ST7789", -1),
                    createBaseVNode("div", { class: "warning custom-block" }, [
                      createBaseVNode("p", { class: "custom-block-title" }, "WARNING"),
                      createBaseVNode("p", null, [
                        createTextVNode("Some ST7789 devices are known to have different drawing offsets -- despite being a 240x320 pixel display controller internally, some display panels are only 240x240, or smaller. These may require an offset to be applied; see "),
                        createBaseVNode("code", null, "qp_set_viewport_offsets"),
                        createTextVNode(" above for information on how to override the offsets if they aren't correctly rendered.")
                      ])
                    ], -1)
                  ])]),
                  _: 1
                })
              ]),
              _: 1
            })
          ]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "OLED" }, {
          default: withCtx(() => [
            _cache[17] || (_cache[17] = createBaseVNode("p", null, "OLED displays tend to use 5-pin SPI when at larger resolutions, or when using color -- SPI SCK, SPI MOSI, SPI CS, D/C, and RST pins. Smaller OLEDs may use I2C instead.", -1)),
            _cache[18] || (_cache[18] = createBaseVNode("p", null, [
              createTextVNode("When using these displays, either "),
              createBaseVNode("code", null, "spi_master"),
              createTextVNode(" or "),
              createBaseVNode("code", null, "i2c_master"),
              createTextVNode(" must already be correctly configured for both the platform and panel you're building for.")
            ], -1)),
            _cache[19] || (_cache[19] = createBaseVNode("p", null, "For SPI, the pin assignments for SPI CS, D/C, and RST are specified during device construction -- for I2C the panel's address is specified instead.", -1)),
            createVNode(_component_PluginTabs, null, {
              default: withCtx(() => [
                createVNode(_component_PluginTabsTab, { label: "SSD1351" }, {
                  default: withCtx(() => [..._cache[13] || (_cache[13] = [
                    createBaseVNode("p", null, [
                      createTextVNode("Enabling support for the SSD1351 in Quantum Painter is done by adding the following to "),
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
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "QUANTUM_PAINTER_ENABLE = yes")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "QUANTUM_PAINTER_DRIVERS += ssd1351_spi")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, "Creating a SSD1351 device in firmware can then be done with the following API:", -1),
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
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_ssd1351_make_spi_device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_width"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_height"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " chip_select_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " dc_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " reset_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " spi_divisor"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "int"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " spi_mode"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The device handle returned from the "),
                      createBaseVNode("code", null, "qp_ssd1351_make_spi_device"),
                      createTextVNode(" function can be used to perform all other drawing operations.")
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The maximum number of displays can be configured by changing the following in your "),
                      createBaseVNode("code", null, "config.h"),
                      createTextVNode(" (default is 1):")
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
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "// 3 displays:")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " SSD1351_NUM_DEVICES"),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 3")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, "Native color format rgb565 is compatible with SSD1351", -1)
                  ])]),
                  _: 1
                }),
                createVNode(_component_PluginTabsTab, { label: "SH1106" }, {
                  default: withCtx(() => [..._cache[14] || (_cache[14] = [
                    createBaseVNode("p", null, [
                      createTextVNode("Enabling support for the SH1106 in Quantum Painter is done by adding the following to "),
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
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "QUANTUM_PAINTER_ENABLE = yes")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "# For SPI:")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "QUANTUM_PAINTER_DRIVERS += sh1106_spi")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "# For I2C:")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "QUANTUM_PAINTER_DRIVERS += sh1106_i2c")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, "Creating a SH1106 device in firmware can then be done with the following APIs:", -1),
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
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "// SPI-based SH1106:")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_sh1106_make_spi_device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_width"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_height"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " chip_select_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " dc_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " reset_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " spi_divisor"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "int"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " spi_mode"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "// I2C-based SH1106:")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_sh1106_make_i2c_device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_width"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_height"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " i2c_address"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The device handle returned from the "),
                      createBaseVNode("code", null, "qp_sh1106_make_???_device"),
                      createTextVNode(" function can be used to perform all other drawing operations.")
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The maximum number of displays of each type can be configured by changing the following in your "),
                      createBaseVNode("code", null, "config.h"),
                      createTextVNode(" (default is 1):")
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
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "// 3 SPI displays:")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " SH1106_NUM_SPI_DEVICES"),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 3")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "// 3 I2C displays:")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " SH1106_NUM_I2C_DEVICES"),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 3")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, "Native color format mono2 is compatible with SH1106", -1)
                  ])]),
                  _: 1
                }),
                createVNode(_component_PluginTabsTab, { label: "SSD1306" }, {
                  default: withCtx(() => [..._cache[15] || (_cache[15] = [
                    createBaseVNode("p", null, "SSD1306 and SH1106 are almost entirely identical, to the point of being indisinguishable by Quantum Painter. Enable SH1106 support in Quantum Painter and create SH1106 devices in firmware to perform drawing operations on SSD1306 displays.", -1)
                  ])]),
                  _: 1
                }),
                createVNode(_component_PluginTabsTab, { label: "LD7032" }, {
                  default: withCtx(() => [..._cache[16] || (_cache[16] = [
                    createBaseVNode("p", null, [
                      createTextVNode("Enabling support for the LD7032 in Quantum Painter is done by adding the following to "),
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
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "QUANTUM_PAINTER_ENABLE = yes")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "# For SPI:")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "QUANTUM_PAINTER_DRIVERS += ld7032_spi")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "# For I2C:")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "QUANTUM_PAINTER_DRIVERS += ld7032_i2c")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, "Creating a SH1106 device in firmware can then be done with the following APIs:", -1),
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
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "// SPI-based LD7032:")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_ld7032_make_spi_device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_width"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_height"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " chip_select_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " dc_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "pin_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " reset_pin"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " spi_divisor"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "int"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " spi_mode"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "// I2C-based LD7032:")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_ld7032_make_i2c_device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_width"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_height"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " i2c_address"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The device handle returned from the "),
                      createBaseVNode("code", null, "qp_ld7032_make_???_device"),
                      createTextVNode(" function can be used to perform all other drawing operations.")
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The maximum number of displays of each type can be configured by changing the following in your "),
                      createBaseVNode("code", null, "config.h"),
                      createTextVNode(" (default is 1):")
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
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "// 3 SPI displays:")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " LD7032_NUM_SPI_DEVICES"),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 3")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "// 3 I2C displays:")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " LD7032_NUM_I2C_DEVICES"),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 3")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, "Native color format mono2 is compatible with LD7032.", -1)
                  ])]),
                  _: 1
                })
              ]),
              _: 1
            })
          ]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "Surface" }, {
          default: withCtx(() => [..._cache[20] || (_cache[20] = [
            createBaseVNode("p", null, 'Quantum Painter has a surface driver which is able to target a buffer in RAM. In general, surfaces keep track of the "dirty" region -- the area that has been drawn to since the last flush -- so that when transferring to the display they can transfer the minimal amount of data to achieve the end result.', -1),
            createBaseVNode("div", { class: "warning custom-block" }, [
              createBaseVNode("p", { class: "custom-block-title" }, "WARNING"),
              createBaseVNode("p", null, "These generally require significant amounts of RAM, so at large sizes and/or higher bit depths, they may not be usable on all MCUs.")
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("Enabling support for surfaces in Quantum Painter is done by adding the following to "),
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
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "QUANTUM_PAINTER_ENABLE = yes")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "QUANTUM_PAINTER_DRIVERS += surface")
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("p", null, "Creating a surface in firmware can then be done with the following APIs:", -1),
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
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "// 24bpp RGB888 surface:")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_make_rgb888_surface"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                    createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_width"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                    createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_height"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " *"),
                    createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, "buffer"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "// 16bpp RGB565 surface:")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_make_rgb565_surface"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                    createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_width"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                    createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_height"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " *"),
                    createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, "buffer"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "// 1bpp monochrome surface:")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_make_mono1bpp_surface"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                    createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_width"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                    createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " panel_height"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " *"),
                    createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, "buffer"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("The "),
              createBaseVNode("code", null, "buffer"),
              createTextVNode(" is a user-supplied area of memory, which can be statically allocated using "),
              createBaseVNode("code", null, "SURFACE_REQUIRED_BUFFER_BYTE_SIZE"),
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
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "// Buffer required for a 240x80 16bpp surface:")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                    createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " framebuffer"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "["),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "SURFACE_REQUIRED_BUFFER_BYTE_SIZE"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "240"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "80"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "16"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ")];")
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("The device handle returned from the "),
              createBaseVNode("code", null, "qp_make_?????_surface"),
              createTextVNode(" function can be used to perform all other drawing operations.")
            ], -1),
            createBaseVNode("p", null, "Example:", -1),
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
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "static"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " painter_device_t"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " my_surface;")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "static"),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " uint8_t"),
                    createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " my_framebuffer"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "["),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "SURFACE_REQUIRED_BUFFER_BYTE_SIZE"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "240"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "80"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "16"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ")];"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // Allocate a buffer for a 16bpp 240x80 RGB565 display")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " keyboard_post_init_kb"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") {")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    my_surface "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_rgb565_make_surface"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "240"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "80"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", my_framebuffer);")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "    qp_init"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(my_surface, QP_ROTATION_0);")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "    keyboard_post_init_user"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "();")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "}")
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("The maximum number of surfaces can be configured by changing the following in your "),
              createBaseVNode("code", null, "config.h"),
              createTextVNode(" (default is 1):")
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
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "// 3 surfaces:")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " SURFACE_NUM_DEVICES"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 3")
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("p", null, "To transfer the contents of the surface to another display of the same pixel format, the following API can be invoked:", -1),
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
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "bool"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_surface_draw"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                    createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " surface"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                    createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " display"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                    createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " x"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                    createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " y"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "bool"),
                    createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " entire_surface"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("The "),
              createBaseVNode("code", null, "surface"),
              createTextVNode(" is the surface to copy out from. The "),
              createBaseVNode("code", null, "display"),
              createTextVNode(" is the target display to draw into. "),
              createBaseVNode("code", null, "x"),
              createTextVNode(" and "),
              createBaseVNode("code", null, "y"),
              createTextVNode(" are the target location to draw the surface pixel data. Under normal circumstances, the location should be consistent, as the dirty region is calculated with respect to the "),
              createBaseVNode("code", null, "x"),
              createTextVNode(" and "),
              createBaseVNode("code", null, "y"),
              createTextVNode(" coordinates -- changing those will result in partial, overlapping draws. "),
              createBaseVNode("code", null, "entire_surface"),
              createTextVNode(" whether the entire surface should be drawn, instead of just the dirty region.")
            ], -1),
            createBaseVNode("div", { class: "warning custom-block" }, [
              createBaseVNode("p", { class: "custom-block-title" }, "WARNING"),
              createBaseVNode("p", null, "The surface and display panel must have the same native pixel format.")
            ], -1),
            createBaseVNode("div", { class: "tip custom-block" }, [
              createBaseVNode("p", { class: "custom-block-title" }, "TIP"),
              createBaseVNode("p", null, [
                createTextVNode("Calling "),
                createBaseVNode("code", null, "qp_flush()"),
                createTextVNode(" on the surface resets its dirty region. Copying the surface contents to the display also automatically resets the dirty region.")
              ])
            ], -1)
          ])]),
          _: 1
        })
      ]),
      _: 1
    }),
    _cache[60] || (_cache[60] = createStaticVNode("", 4)),
    createVNode(_component_PluginTabs, null, {
      default: withCtx(() => [
        createVNode(_component_PluginTabsTab, { label: "General Notes" }, {
          default: withCtx(() => [..._cache[21] || (_cache[21] = [
            createBaseVNode("p", null, [
              createTextVNode("The coordinate system used in Quantum Painter generally accepts "),
              createBaseVNode("code", null, "left"),
              createTextVNode(", "),
              createBaseVNode("code", null, "top"),
              createTextVNode(", "),
              createBaseVNode("code", null, "right"),
              createTextVNode(", and "),
              createBaseVNode("code", null, "bottom"),
              createTextVNode(" instead of x/y/width/height, and each coordinate is inclusive of where pixels should be drawn. This is required as some datatypes used by display panels have a maximum value of "),
              createBaseVNode("code", null, "255"),
              createTextVNode(" -- for any value or geometry extent that matches "),
              createBaseVNode("code", null, "256"),
              createTextVNode(", this would be represented as a "),
              createBaseVNode("code", null, "0"),
              createTextVNode(", instead.")
            ], -1),
            createBaseVNode("div", { class: "tip custom-block" }, [
              createBaseVNode("p", { class: "custom-block-title" }, "TIP"),
              createBaseVNode("p", null, [
                createTextVNode("Drawing a horizontal line 8 pixels long, starting from 4 pixels inside the left side of the display, will need "),
                createBaseVNode("code", null, "left=4"),
                createTextVNode(", "),
                createBaseVNode("code", null, "right=11"),
                createTextVNode(".")
              ])
            ], -1),
            createBaseVNode("p", null, "All color data matches the standard QMK HSV triplet definitions:", -1),
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("Hue is of the range "),
                createBaseVNode("code", null, "0...255"),
                createTextVNode(" and is internally mapped to 0...360 degrees.")
              ]),
              createBaseVNode("li", null, [
                createTextVNode("Saturation is of the range "),
                createBaseVNode("code", null, "0...255"),
                createTextVNode(" and is internally mapped to 0...100% saturation.")
              ]),
              createBaseVNode("li", null, [
                createTextVNode("Value is of the range "),
                createBaseVNode("code", null, "0...255"),
                createTextVNode(" and is internally mapped to 0...100% brightness.")
              ])
            ], -1),
            createBaseVNode("div", { class: "tip custom-block" }, [
              createBaseVNode("p", { class: "custom-block-title" }, "TIP"),
              createBaseVNode("p", null, "Colors used in Quantum Painter are not subject to the RGB lighting CIE curve, if it is enabled.")
            ], -1)
          ])]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "Device Control" }, {
          default: withCtx(() => [
            createVNode(_component_PluginTabs, null, {
              default: withCtx(() => [
                createVNode(_component_PluginTabsTab, { label: "Display Initialisation" }, {
                  default: withCtx(() => [..._cache[22] || (_cache[22] = [
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
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "bool"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_init"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_rotation_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " rotation"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The "),
                      createBaseVNode("code", null, "qp_init"),
                      createTextVNode(" function is used to initialise a display device after it has been created. This accepts a rotation parameter ("),
                      createBaseVNode("code", null, "QP_ROTATION_0"),
                      createTextVNode(", "),
                      createBaseVNode("code", null, "QP_ROTATION_90"),
                      createTextVNode(", "),
                      createBaseVNode("code", null, "QP_ROTATION_180"),
                      createTextVNode(", "),
                      createBaseVNode("code", null, "QP_ROTATION_270"),
                      createTextVNode("), which makes sure that the orientation of what's drawn on the display is correct.")
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
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "static"),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " display;")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " keyboard_post_init_kb"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") {")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    display "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " qp_make_.......;"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "         // Create the display")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "    qp_init"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(display, QP_ROTATION_0);"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "   // Initialise the display")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "}")
                          ])
                        ])
                      ])
                    ], -1)
                  ])]),
                  _: 1
                }),
                createVNode(_component_PluginTabsTab, { label: "Display Power" }, {
                  default: withCtx(() => [..._cache[23] || (_cache[23] = [
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
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "bool"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_power"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "bool"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " power_on"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The "),
                      createBaseVNode("code", null, "qp_power"),
                      createTextVNode(" function instructs the display whether or not the display panel should be on or off.")
                    ], -1),
                    createBaseVNode("div", { class: "warning custom-block" }, [
                      createBaseVNode("p", { class: "custom-block-title" }, "WARNING"),
                      createBaseVNode("p", null, [
                        createTextVNode("If there is a separate backlight controlled through the normal QMK backlight API, this is not controlled by the "),
                        createBaseVNode("code", null, "qp_power"),
                        createTextVNode(" function and needs to be manually handled elsewhere.")
                      ])
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
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "static"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " last_backlight "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 255"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ";")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " suspend_power_down_user"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") {")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "    if"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " (last_backlight "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "=="),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 255"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") {")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "        last_backlight "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " get_backlight_level"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "();")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    }")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "    backlight_set"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "0"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "    rgb_matrix_set_suspend_state"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "    qp_power"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(display, "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "false"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "}")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " suspend_wakeup_init_user"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") {")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "    qp_power"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(display, "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "    rgb_matrix_set_suspend_state"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "false"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "    if"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " (last_backlight "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "!="),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 255"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") {")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "        backlight_set"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(last_backlight);")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    }")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    last_backlight "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 255"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ";")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "}")
                          ])
                        ])
                      ])
                    ], -1)
                  ])]),
                  _: 1
                }),
                createVNode(_component_PluginTabsTab, { label: "Display Clear" }, {
                  default: withCtx(() => [..._cache[24] || (_cache[24] = [
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
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "bool"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_clear"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The "),
                      createBaseVNode("code", null, "qp_clear"),
                      createTextVNode(" function clears the display's screen.")
                    ], -1)
                  ])]),
                  _: 1
                }),
                createVNode(_component_PluginTabsTab, { label: "Display Flush" }, {
                  default: withCtx(() => [..._cache[25] || (_cache[25] = [
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
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "bool"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_flush"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The "),
                      createBaseVNode("code", null, "qp_flush"),
                      createTextVNode(' function ensures that all drawing operations are "pushed" to the display. This should be done as the last operation whenever a sequence of draws occur, and guarantees that any changes are applied.')
                    ], -1),
                    createBaseVNode("div", { class: "warning custom-block" }, [
                      createBaseVNode("p", { class: "custom-block-title" }, "WARNING"),
                      createBaseVNode("p", null, [
                        createTextVNode("Some display panels may seem to work even without a call to "),
                        createBaseVNode("code", null, "qp_flush"),
                        createTextVNode(" -- this may be because the driver cannot queue drawing operations and needs to display them immediately when invoked. In general, calling "),
                        createBaseVNode("code", null, "qp_flush"),
                        createTextVNode(' at the end is still considered "best practice".')
                      ])
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
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " housekeeping_task_user"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") {")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "    static"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " uint32_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " last_draw "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 0"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ";")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "    if"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " ("),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "timer_elapsed32"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(last_draw) "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, ">"),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 33"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") {"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // Throttle to 30fps")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "        last_draw "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " timer_read32"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "();")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "        // Draw a rect based off the current RGB color")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "        qp_rect"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(display, "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "0"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "7"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "0"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "239"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "rgb_matrix_get_hue"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(), "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "255"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "255"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "        qp_flush"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(display);")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    }")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "}")
                          ])
                        ])
                      ])
                    ], -1)
                  ])]),
                  _: 1
                })
              ]),
              _: 1
            })
          ]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "Drawing Primitives" }, {
          default: withCtx(() => [
            createVNode(_component_PluginTabs, null, {
              default: withCtx(() => [
                createVNode(_component_PluginTabsTab, { label: "Set Pixel" }, {
                  default: withCtx(() => [..._cache[26] || (_cache[26] = [
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
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "bool"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_setpixel"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " x"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " y"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " hue"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " sat"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " val"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The "),
                      createBaseVNode("code", null, "qp_setpixel"),
                      createTextVNode(" can be used to set a specific pixel on the screen to the supplied color.")
                    ], -1),
                    createBaseVNode("div", { class: "tip custom-block" }, [
                      createBaseVNode("p", { class: "custom-block-title" }, "TIP"),
                      createBaseVNode("p", null, [
                        createTextVNode("Using "),
                        createBaseVNode("code", null, "qp_setpixel"),
                        createTextVNode(" for large amounts of drawing operations is inefficient and should be avoided unless they cannot be achieved with other drawing APIs.")
                      ])
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
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " housekeeping_task_user"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") {")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "    static"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " uint32_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " last_draw "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 0"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ";")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "    if"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " ("),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "timer_elapsed32"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(last_draw) "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, ">"),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 33"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") {"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // Throttle to 30fps")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "        last_draw "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " timer_read32"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "();")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "        // Draw a 240px high vertical rainbow line on X=0:")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "        for"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " ("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "int"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " i "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 0"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "; i "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "<"),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 239"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "; "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "++"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "i) {")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "            qp_setpixel"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(display, "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "0"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", i, i, "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "255"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "255"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "        }")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "        qp_flush"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(display);")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    }")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "}")
                          ])
                        ])
                      ])
                    ], -1)
                  ])]),
                  _: 1
                }),
                createVNode(_component_PluginTabsTab, { label: "Draw Line" }, {
                  default: withCtx(() => [..._cache[27] || (_cache[27] = [
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
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "bool"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_line"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " x0"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " y0"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " x1"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " y1"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " hue"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " sat"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " val"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The "),
                      createBaseVNode("code", null, "qp_line"),
                      createTextVNode(" can be used to draw lines on the screen with the supplied color.")
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
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " housekeeping_task_user"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") {")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "    static"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " uint32_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " last_draw "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 0"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ";")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "    if"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " ("),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "timer_elapsed32"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(last_draw) "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, ">"),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 33"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") {"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // Throttle to 30fps")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "        last_draw "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " timer_read32"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "();")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "        // Draw 8px-wide rainbow down the left side of the display")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "        for"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " ("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "int"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " i "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 0"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "; i "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "<"),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 239"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "; "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "++"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "i) {")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "            qp_line"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(display, "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "0"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", i, "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "7"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", i, i, "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "255"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "255"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "        }")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "        qp_flush"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(display);")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    }")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "}")
                          ])
                        ])
                      ])
                    ], -1)
                  ])]),
                  _: 1
                }),
                createVNode(_component_PluginTabsTab, { label: "Draw Rect" }, {
                  default: withCtx(() => [..._cache[28] || (_cache[28] = [
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
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "bool"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_rect"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " left"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " top"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " right"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " bottom"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " hue"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " sat"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " val"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "bool"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " filled"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The "),
                      createBaseVNode("code", null, "qp_rect"),
                      createTextVNode(" can be used to draw rectangles on the screen with the supplied color, with or without a background fill. If not filled, any pixels inside the rectangle will be left as-is.")
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
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " housekeeping_task_user"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") {")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "    static"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " uint32_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " last_draw "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 0"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ";")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "    if"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " ("),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "timer_elapsed32"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(last_draw) "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, ">"),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 33"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") {"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // Throttle to 30fps")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "        last_draw "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " timer_read32"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "();")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "        // Draw 8px-wide rainbow filled rectangles down the left side of the display")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "        for"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " ("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "int"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " i "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 0"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "; i "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "<"),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 239"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "; i"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "+="),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "8"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") {")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "            qp_rect"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(display, "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "0"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", i, "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "7"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", i"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "+"),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "7"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", i, "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "255"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "255"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "        }")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "        qp_flush"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(display);")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    }")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "}")
                          ])
                        ])
                      ])
                    ], -1)
                  ])]),
                  _: 1
                }),
                createVNode(_component_PluginTabsTab, { label: "Draw Circle" }, {
                  default: withCtx(() => [..._cache[29] || (_cache[29] = [
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
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "bool"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_circle"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " x"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " y"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " radius"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " hue"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " sat"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " val"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "bool"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " filled"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The "),
                      createBaseVNode("code", null, "qp_circle"),
                      createTextVNode(" can be used to draw circles on the screen with the supplied color, with or without a background fill. If not filled, any pixels inside the circle will be left as-is.")
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
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " housekeeping_task_user"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") {")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "    static"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " uint32_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " last_draw "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 0"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ";")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "    if"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " ("),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "timer_elapsed32"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(last_draw) "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, ">"),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 33"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") {"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // Throttle to 30fps")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "        last_draw "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " timer_read32"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "();")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "        // Draw r=4 filled circles down the left side of the display")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "        for"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " ("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "int"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " i "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 0"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "; i "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "<"),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 239"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "; i"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "+="),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "8"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") {")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "            qp_circle"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(display, "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "4"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "4"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "+"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "i, "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "4"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", i, "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "255"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "255"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "        }")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "        qp_flush"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(display);")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    }")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "}")
                          ])
                        ])
                      ])
                    ], -1)
                  ])]),
                  _: 1
                }),
                createVNode(_component_PluginTabsTab, { label: "Draw Ellipse" }, {
                  default: withCtx(() => [..._cache[30] || (_cache[30] = [
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
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "bool"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_ellipse"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " x"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " y"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " sizex"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " sizey"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " hue"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " sat"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " val"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "bool"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " filled"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The "),
                      createBaseVNode("code", null, "qp_ellipse"),
                      createTextVNode(" can be used to draw ellipses on the screen with the supplied color, with or without a background fill. If not filled, any pixels inside the ellipses will be left as-is.")
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
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " housekeeping_task_user"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") {")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "    static"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " uint32_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " last_draw "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 0"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ";")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "    if"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " ("),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "timer_elapsed32"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(last_draw) "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, ">"),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 33"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") {"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // Throttle to 30fps")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "        last_draw "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " timer_read32"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "();")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "        // Draw 16x8 filled ellipses down the left side of the display")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "        for"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " ("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "int"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " i "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 0"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "; i "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "<"),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 239"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "; i"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "+="),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "8"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") {")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "            qp_ellipse"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(display, "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "8"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "4"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "+"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "i, "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "16"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "8"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", i, "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "255"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "255"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "        }")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "        qp_flush"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(display);")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    }")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "}")
                          ])
                        ])
                      ])
                    ], -1)
                  ])]),
                  _: 1
                })
              ]),
              _: 1
            })
          ]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "Image Functions" }, {
          default: withCtx(() => [
            _cache[36] || (_cache[36] = createBaseVNode("p", null, [
              createTextVNode("Making an image available for use requires compiling it into your firmware. To do so, assuming you've created "),
              createBaseVNode("code", null, "my_image.qgf.c"),
              createTextVNode(" and "),
              createBaseVNode("code", null, "my_image.qgf.h"),
              createTextVNode(" as per the CLI examples above, you'd add the following to your "),
              createBaseVNode("code", null, "rules.mk"),
              createTextVNode(":")
            ], -1)),
            _cache[37] || (_cache[37] = createBaseVNode("div", { class: "language-make vp-adaptive-theme" }, [
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
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "SRC += my_image.qgf.c")
                  ])
                ])
              ])
            ], -1)),
            _cache[38] || (_cache[38] = createBaseVNode("p", null, [
              createTextVNode("...and in your "),
              createBaseVNode("code", null, "keymap.c"),
              createTextVNode(", you'd add to the top of the file:")
            ], -1)),
            _cache[39] || (_cache[39] = createBaseVNode("div", { class: "language-c vp-adaptive-theme" }, [
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
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#include"),
                    createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, ' "my_image.qgf.h"')
                  ])
                ])
              ])
            ], -1)),
            createVNode(_component_PluginTabs, null, {
              default: withCtx(() => [
                createVNode(_component_PluginTabsTab, { label: "Load Image" }, {
                  default: withCtx(() => [..._cache[31] || (_cache[31] = [
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
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_image_handle_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_load_image_mem"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "const"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " *"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, "buffer"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The "),
                      createBaseVNode("code", null, "qp_load_image_mem"),
                      createTextVNode(" function loads a QGF image from memory or flash.")
                    ], -1),
                    createBaseVNode("p", null, [
                      createBaseVNode("code", null, "qp_load_image_mem"),
                      createTextVNode(" returns a handle to the loaded image, which can then be used to draw to the screen using "),
                      createBaseVNode("code", null, "qp_drawimage"),
                      createTextVNode(", "),
                      createBaseVNode("code", null, "qp_drawimage_recolor"),
                      createTextVNode(", "),
                      createBaseVNode("code", null, "qp_animate"),
                      createTextVNode(", or "),
                      createBaseVNode("code", null, "qp_animate_recolor"),
                      createTextVNode(". If an image is no longer required, it can be unloaded by calling "),
                      createBaseVNode("code", null, "qp_close_image"),
                      createTextVNode(" below.")
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("See the "),
                      createBaseVNode("a", { href: "./quantum_painter#quantum-painter-cli" }, "CLI Commands"),
                      createTextVNode(" for instructions on how to convert images to "),
                      createBaseVNode("a", { href: "./quantum_painter_qgf" }, "QGF"),
                      createTextVNode(".")
                    ], -1),
                    createBaseVNode("div", { class: "tip custom-block" }, [
                      createBaseVNode("p", { class: "custom-block-title" }, "TIP"),
                      createBaseVNode("p", null, [
                        createTextVNode("The total number of images available to load at any one time is controlled by the configurable option "),
                        createBaseVNode("code", null, "QUANTUM_PAINTER_NUM_IMAGES"),
                        createTextVNode(" in the table above. If more images are required, the number should be increased in "),
                        createBaseVNode("code", null, "config.h"),
                        createTextVNode(".")
                      ])
                    ], -1),
                    createBaseVNode("p", null, "Image information is available through accessing the handle:", -1),
                    createBaseVNode("table", { tabindex: "0" }, [
                      createBaseVNode("thead", null, [
                        createBaseVNode("tr", null, [
                          createBaseVNode("th", null, "Property"),
                          createBaseVNode("th", null, "Accessor")
                        ])
                      ]),
                      createBaseVNode("tbody", null, [
                        createBaseVNode("tr", null, [
                          createBaseVNode("td", null, "Width"),
                          createBaseVNode("td", null, [
                            createBaseVNode("code", null, "image->width")
                          ])
                        ]),
                        createBaseVNode("tr", null, [
                          createBaseVNode("td", null, "Height"),
                          createBaseVNode("td", null, [
                            createBaseVNode("code", null, "image->height")
                          ])
                        ]),
                        createBaseVNode("tr", null, [
                          createBaseVNode("td", null, "Frame Count"),
                          createBaseVNode("td", null, [
                            createBaseVNode("code", null, "image->frame_count")
                          ])
                        ])
                      ])
                    ], -1)
                  ])]),
                  _: 1
                }),
                createVNode(_component_PluginTabsTab, { label: "Unload Image" }, {
                  default: withCtx(() => [..._cache[32] || (_cache[32] = [
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
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "bool"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_close_image"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_image_handle_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " image"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The "),
                      createBaseVNode("code", null, "qp_close_image"),
                      createTextVNode(" function releases resources related to the loading of the supplied image.")
                    ], -1)
                  ])]),
                  _: 1
                }),
                createVNode(_component_PluginTabsTab, { label: "Draw image" }, {
                  default: withCtx(() => [..._cache[33] || (_cache[33] = [
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
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "bool"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_drawimage"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " x"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " y"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_image_handle_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " image"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "bool"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_drawimage_recolor"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " x"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " y"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_image_handle_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " image"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " hue_fg"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " sat_fg"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " val_fg"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " hue_bg"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " sat_bg"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " val_bg"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The "),
                      createBaseVNode("code", null, "qp_drawimage"),
                      createTextVNode(" and "),
                      createBaseVNode("code", null, "qp_drawimage_recolor"),
                      createTextVNode(" functions draw the supplied image to the screen at the supplied location, with the latter function allowing for monochrome-based images to be recolored.")
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
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "// Draw an image on the bottom-right of the 240x320 display on initialisation")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "static"),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " painter_image_handle_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " my_image;")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " keyboard_post_init_kb"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") {")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    my_image "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_load_image_mem"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(gfx_my_image);")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "    if"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " (my_image "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "!="),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " NULL"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") {")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "        qp_drawimage"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(display, ("),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "240"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " -"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " my_image->width), ("),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "320"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " -"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " my_image->height), my_image);")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    }")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "}")
                          ])
                        ])
                      ])
                    ], -1)
                  ])]),
                  _: 1
                }),
                createVNode(_component_PluginTabsTab, { label: "Animate Image" }, {
                  default: withCtx(() => [..._cache[34] || (_cache[34] = [
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
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "deferred_token "),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "qp_animate"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " x"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " y"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_image_handle_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " image"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "deferred_token "),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "qp_animate_recolor"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " x"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " y"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_image_handle_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " image"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " hue_fg"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " sat_fg"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " val_fg"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " hue_bg"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " sat_bg"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " val_bg"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The "),
                      createBaseVNode("code", null, "qp_animate"),
                      createTextVNode(" and "),
                      createBaseVNode("code", null, "qp_animate_recolor"),
                      createTextVNode(" functions draw the supplied image to the screen at the supplied location, with the latter function allowing for monochrome-based animations to be recolored. They also set up internal timing such that each frame is rendered at the correct time as per the animated image.")
                    ], -1),
                    createBaseVNode("p", null, "Once an image has been set to animate, it will loop indefinitely until stopped, with no user intervention required.", -1),
                    createBaseVNode("p", null, [
                      createTextVNode("Both functions return a "),
                      createBaseVNode("code", null, "deferred_token"),
                      createTextVNode(", which can then be used to stop the animation, using "),
                      createBaseVNode("code", null, "qp_stop_animation"),
                      createTextVNode(" below.")
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
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "// Animate an image on the bottom-right of the 240x320 display on initialisation")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "static"),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " painter_image_handle_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " my_image;")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "static"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " deferred_token my_anim;")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " keyboard_post_init_kb"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") {")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    my_image "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_load_image_mem"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(gfx_my_image);")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "    if"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " (my_image "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "!="),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " NULL"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") {")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "        my_anim "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_animate"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(display, ("),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "240"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " -"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " my_image->width), ("),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "320"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " -"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " my_image->height), my_image);")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    }")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "}")
                          ])
                        ])
                      ])
                    ], -1)
                  ])]),
                  _: 1
                }),
                createVNode(_component_PluginTabsTab, { label: "Stop Animation" }, {
                  default: withCtx(() => [..._cache[35] || (_cache[35] = [
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
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_stop_animation"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(deferred_token "),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, "anim_token"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The "),
                      createBaseVNode("code", null, "qp_stop_animation"),
                      createTextVNode(" function stops the previously-started animation.")
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
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " housekeeping_task_user"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") {")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "    if"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " (some_random_stop_reason) {")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "        qp_stop_animation"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(my_anim);")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    }")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "}")
                          ])
                        ])
                      ])
                    ], -1)
                  ])]),
                  _: 1
                })
              ]),
              _: 1
            })
          ]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "Font Functions" }, {
          default: withCtx(() => [
            _cache[44] || (_cache[44] = createBaseVNode("p", null, [
              createTextVNode("Making a font available for use requires compiling it into your firmware. To do so, assuming you've created "),
              createBaseVNode("code", null, "my_font.qff.c"),
              createTextVNode(" and "),
              createBaseVNode("code", null, "my_font.qff.h"),
              createTextVNode(" as per the CLI examples above, you'd add the following to your "),
              createBaseVNode("code", null, "rules.mk"),
              createTextVNode(":")
            ], -1)),
            _cache[45] || (_cache[45] = createBaseVNode("div", { class: "language-make vp-adaptive-theme" }, [
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
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "SRC += noto11.qff.c")
                  ])
                ])
              ])
            ], -1)),
            _cache[46] || (_cache[46] = createBaseVNode("p", null, [
              createTextVNode("...and in your "),
              createBaseVNode("code", null, "keymap.c"),
              createTextVNode(", you'd add to the top of the file:")
            ], -1)),
            _cache[47] || (_cache[47] = createBaseVNode("div", { class: "language-c vp-adaptive-theme" }, [
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
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#include"),
                    createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, ' "noto11.qff.h"')
                  ])
                ])
              ])
            ], -1)),
            createVNode(_component_PluginTabs, null, {
              default: withCtx(() => [
                createVNode(_component_PluginTabsTab, { label: "Load Font" }, {
                  default: withCtx(() => [..._cache[40] || (_cache[40] = [
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
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_font_handle_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_load_font_mem"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "const"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " *"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, "buffer"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The "),
                      createBaseVNode("code", null, "qp_load_font_mem"),
                      createTextVNode(" function loads a QFF font from memory or flash.")
                    ], -1),
                    createBaseVNode("p", null, [
                      createBaseVNode("code", null, "qp_load_font_mem"),
                      createTextVNode(" returns a handle to the loaded font, which can then be measured using "),
                      createBaseVNode("code", null, "qp_textwidth"),
                      createTextVNode(", or drawn to the screen using "),
                      createBaseVNode("code", null, "qp_drawtext"),
                      createTextVNode(", or "),
                      createBaseVNode("code", null, "qp_drawtext_recolor"),
                      createTextVNode(". If a font is no longer required, it can be unloaded by calling "),
                      createBaseVNode("code", null, "qp_close_font"),
                      createTextVNode(" below.")
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("See the "),
                      createBaseVNode("a", { href: "./quantum_painter#quantum-painter-cli" }, "CLI Commands"),
                      createTextVNode(" for instructions on how to convert TTF fonts to "),
                      createBaseVNode("a", { href: "./quantum_painter_qff" }, "QFF"),
                      createTextVNode(".")
                    ], -1),
                    createBaseVNode("div", { class: "tip custom-block" }, [
                      createBaseVNode("p", { class: "custom-block-title" }, "TIP"),
                      createBaseVNode("p", null, [
                        createTextVNode("The total number of fonts available to load at any one time is controlled by the configurable option "),
                        createBaseVNode("code", null, "QUANTUM_PAINTER_NUM_FONTS"),
                        createTextVNode(" in the table above. If more fonts are required, the number should be increased in "),
                        createBaseVNode("code", null, "config.h"),
                        createTextVNode(".")
                      ])
                    ], -1),
                    createBaseVNode("p", null, "Font information is available through accessing the handle:", -1),
                    createBaseVNode("table", { tabindex: "0" }, [
                      createBaseVNode("thead", null, [
                        createBaseVNode("tr", null, [
                          createBaseVNode("th", null, "Property"),
                          createBaseVNode("th", null, "Accessor")
                        ])
                      ]),
                      createBaseVNode("tbody", null, [
                        createBaseVNode("tr", null, [
                          createBaseVNode("td", null, "Line Height"),
                          createBaseVNode("td", null, [
                            createBaseVNode("code", null, "image->line_height")
                          ])
                        ])
                      ])
                    ], -1)
                  ])]),
                  _: 1
                }),
                createVNode(_component_PluginTabsTab, { label: "Unload Font" }, {
                  default: withCtx(() => [..._cache[41] || (_cache[41] = [
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
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "bool"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_close_font"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_font_handle_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " font"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The "),
                      createBaseVNode("code", null, "qp_close_font"),
                      createTextVNode(" function releases resources related to the loading of the supplied font.")
                    ], -1)
                  ])]),
                  _: 1
                }),
                createVNode(_component_PluginTabsTab, { label: "Measure Text" }, {
                  default: withCtx(() => [..._cache[42] || (_cache[42] = [
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
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "int16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_textwidth"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_font_handle_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " font"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "const"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " char"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " *"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, "str"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The "),
                      createBaseVNode("code", null, "qp_textwidth"),
                      createTextVNode(" function allows measurement of how many pixels wide the supplied string would result in, for the given font.")
                    ], -1)
                  ])]),
                  _: 1
                }),
                createVNode(_component_PluginTabsTab, { label: "Draw Text" }, {
                  default: withCtx(() => [..._cache[43] || (_cache[43] = [
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
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "int16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_drawtext"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " x"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " y"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_font_handle_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " font"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "const"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " char"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " *"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, "str"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "int16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_drawtext_recolor"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " x"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " y"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_font_handle_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " font"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "const"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " char"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " *"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, "str"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " hue_fg"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " sat_fg"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " val_fg"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " hue_bg"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " sat_bg"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint8_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " val_bg"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The "),
                      createBaseVNode("code", null, "qp_drawtext"),
                      createTextVNode(" and "),
                      createBaseVNode("code", null, "qp_drawtext_recolor"),
                      createTextVNode(" functions draw the supplied string to the screen at the given location using the font supplied, with the latter function allowing for monochrome-based fonts to be recolored.")
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
                            createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "// Draw a text message on the bottom-right of the 240x320 display on initialisation")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "static"),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " painter_font_handle_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " my_font;")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " keyboard_post_init_kb"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") {")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    my_font "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_load_font_mem"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(font_noto11);")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "    if"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " (my_font "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "!="),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " NULL"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") {")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "        static"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " const"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " char"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " *"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "text "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                            createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, ' "Hello from QMK!"'),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ";")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "        int16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " width "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_textwidth"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(my_font, text);")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, "        qp_drawtext"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "(display, ("),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "240"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " -"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " width), ("),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "320"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " -"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " my_font->line_height), my_font, text);")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    }")
                          ]),
                          createTextVNode("\n"),
                          createBaseVNode("span", { class: "line" }, [
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "}")
                          ])
                        ])
                      ])
                    ], -1)
                  ])]),
                  _: 1
                })
              ]),
              _: 1
            })
          ]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "Advanced Functions" }, {
          default: withCtx(() => [
            createVNode(_component_PluginTabs, null, {
              default: withCtx(() => [
                createVNode(_component_PluginTabsTab, { label: "Getters" }, {
                  default: withCtx(() => [
                    _cache[54] || (_cache[54] = createBaseVNode("p", null, "These functions allow external code to retrieve the current width, height, rotation, and drawing offsets.", -1)),
                    createVNode(_component_PluginTabs, null, {
                      default: withCtx(() => [
                        createVNode(_component_PluginTabsTab, { label: "Width" }, {
                          default: withCtx(() => [..._cache[48] || (_cache[48] = [
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
                                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_get_width"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " device"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                                  ])
                                ])
                              ])
                            ], -1)
                          ])]),
                          _: 1
                        }),
                        createVNode(_component_PluginTabsTab, { label: "Height" }, {
                          default: withCtx(() => [..._cache[49] || (_cache[49] = [
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
                                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_get_height"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " device"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                                  ])
                                ])
                              ])
                            ], -1)
                          ])]),
                          _: 1
                        }),
                        createVNode(_component_PluginTabsTab, { label: "Rotation" }, {
                          default: withCtx(() => [..._cache[50] || (_cache[50] = [
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
                                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_rotation_t"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_get_rotation"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " device"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                                  ])
                                ])
                              ])
                            ], -1)
                          ])]),
                          _: 1
                        }),
                        createVNode(_component_PluginTabsTab, { label: "Offset X" }, {
                          default: withCtx(() => [..._cache[51] || (_cache[51] = [
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
                                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_get_offset_x"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " device"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                                  ])
                                ])
                              ])
                            ], -1)
                          ])]),
                          _: 1
                        }),
                        createVNode(_component_PluginTabsTab, { label: "Offset Y" }, {
                          default: withCtx(() => [..._cache[52] || (_cache[52] = [
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
                                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_get_offset_y"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " device"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                                  ])
                                ])
                              ])
                            ], -1)
                          ])]),
                          _: 1
                        }),
                        createVNode(_component_PluginTabsTab, { label: "Everything" }, {
                          default: withCtx(() => [..._cache[53] || (_cache[53] = [
                            createBaseVNode("p", null, [
                              createTextVNode("Convenience function to call all the previous ones at once. Note: You can pass "),
                              createBaseVNode("code", null, "NULL"),
                              createTextVNode(" for the values you are not interested in.")
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
                                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_get_geometry"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " device"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " *"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, "width"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " *"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, "height"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_rotation_t"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " *"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, "rotation"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " *"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, "offset_x"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " *"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, "offset_y"),
                                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                                  ])
                                ])
                              ])
                            ], -1)
                          ])]),
                          _: 1
                        })
                      ]),
                      _: 1
                    })
                  ]),
                  _: 1
                }),
                createVNode(_component_PluginTabsTab, { label: "Set Viewport Offsets" }, {
                  default: withCtx(() => [..._cache[55] || (_cache[55] = [
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
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_set_viewport_offsets"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " offset_x"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " offset_y"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The "),
                      createBaseVNode("code", null, "qp_set_viewport_offsets"),
                      createTextVNode(" function can be used to offset all subsequent drawing operations. For example, if a display controller is internally 240x320, but the display panel is 240x240 and has a Y offset of 80 pixels, you could invoke "),
                      createBaseVNode("code", null, "qp_set_viewport_offsets(display, 0, 80);"),
                      createTextVNode(" and the drawing positioning would be corrected.")
                    ], -1)
                  ])]),
                  _: 1
                }),
                createVNode(_component_PluginTabsTab, { label: "Set Viewport" }, {
                  default: withCtx(() => [..._cache[56] || (_cache[56] = [
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
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "bool"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_viewport"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " left"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " top"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " right"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint16_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " bottom"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The "),
                      createBaseVNode("code", null, "qp_viewport"),
                      createTextVNode(" function controls where raw pixel data is written to.")
                    ], -1)
                  ])]),
                  _: 1
                }),
                createVNode(_component_PluginTabsTab, { label: "Stream Pixel Data" }, {
                  default: withCtx(() => [..._cache[57] || (_cache[57] = [
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
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "bool"),
                            createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " qp_pixdata"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "("),
                            createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "painter_device_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " device"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "const"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " void"),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " *"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, "pixel_data"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                            createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "uint32_t"),
                            createBaseVNode("span", { style: { "--shiki-light": "#E36209", "--shiki-dark": "#FFAB70" } }, " native_pixel_count"),
                            createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ");")
                          ])
                        ])
                      ])
                    ], -1),
                    createBaseVNode("p", null, [
                      createTextVNode("The "),
                      createBaseVNode("code", null, "qp_pixdata"),
                      createTextVNode(" function allows raw pixel data to be streamed to the display. It requires a native pixel count rather than the number of bytes to transfer, to ensure display panel data alignment is respected. E.g. for display panels using RGB565 internal format, sending 10 pixels will result in 20 bytes of transfer.")
                    ], -1),
                    createBaseVNode("div", { class: "warning custom-block" }, [
                      createBaseVNode("p", { class: "custom-block-title" }, "WARNING"),
                      createBaseVNode("p", null, [
                        createTextVNode("Under normal circumstances, users will not need to manually call either "),
                        createBaseVNode("code", null, "qp_viewport"),
                        createTextVNode(" or "),
                        createBaseVNode("code", null, "qp_pixdata"),
                        createTextVNode(". These allow for writing of raw pixel information, in the display panel's native format, to the area defined by the viewport.")
                      ])
                    ], -1)
                  ])]),
                  _: 1
                })
              ]),
              _: 1
            })
          ]),
          _: 1
        })
      ]),
      _: 1
    })
  ]);
}
const quantum_painter = /* @__PURE__ */ _export_sfc(_sfc_main, [["render", _sfc_render]]);
export {
  __pageData,
  quantum_painter as default
};
