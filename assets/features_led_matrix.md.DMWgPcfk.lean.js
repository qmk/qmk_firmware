import { _ as _export_sfc, C as resolveComponent, o as openBlock, c as createElementBlock, al as createStaticVNode, E as createVNode, w as withCtx, j as createBaseVNode, a as createTextVNode } from "./chunks/framework.8zKZLKO7.js";
const __pageData = JSON.parse('{"title":"LED Matrix Lighting","description":"","frontmatter":{},"headers":[],"relativePath":"features/led_matrix.md","filePath":"features/led_matrix.md","lastUpdated":null}');
const _sfc_main = { name: "features/led_matrix.md" };
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  const _component_PluginTabsTab = resolveComponent("PluginTabsTab");
  const _component_PluginTabs = resolveComponent("PluginTabs");
  return openBlock(), createElementBlock("div", null, [
    _cache[8] || (_cache[8] = createStaticVNode("", 7)),
    createVNode(_component_PluginTabs, null, {
      default: withCtx(() => [
        createVNode(_component_PluginTabsTab, { label: "`JSON`" }, {
          default: withCtx(() => [..._cache[0] || (_cache[0] = [
            createBaseVNode("div", { class: "language-json vp-adaptive-theme" }, [
              createBaseVNode("button", {
                title: "Copy Code",
                class: "copy"
              }),
              createBaseVNode("span", { class: "lang" }, "json"),
              createBaseVNode("pre", {
                class: "shiki shiki-themes github-light github-dark vp-code",
                tabindex: "0"
              }, [
                createBaseVNode("code", null, [
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '    "led_matrix"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": {")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '      "driver"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '"is31fl3218"')
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    }")
                  ])
                ])
              ])
            ], -1)
          ])]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "`rules.mk`" }, {
          default: withCtx(() => [..._cache[1] || (_cache[1] = [
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
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "LED_MATRIX_DRIVER = is31fl3218")
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
    _cache[9] || (_cache[9] = createBaseVNode("h2", {
      id: "common-configuration",
      tabindex: "-1"
    }, [
      createTextVNode("Common Configuration "),
      createBaseVNode("a", {
        class: "header-anchor",
        href: "#common-configuration",
        "aria-label": 'Permalink to "Common Configuration {#common-configuration}"'
      }, "​")
    ], -1)),
    _cache[10] || (_cache[10] = createBaseVNode("p", null, [
      createTextVNode("From this point forward the configuration is the same for all the drivers. The "),
      createBaseVNode("code", null, "led_config_t"),
      createTextVNode(" struct provides a key electrical matrix to led index lookup table, what the physical position of each LED is on the board, and what type of key or usage the LED if the LED represents. Here is a brief example:")
    ], -1)),
    createVNode(_component_PluginTabs, null, {
      default: withCtx(() => [
        createVNode(_component_PluginTabsTab, { label: "`JSON`" }, {
          default: withCtx(() => [..._cache[2] || (_cache[2] = [
            createBaseVNode("div", { class: "language-json vp-adaptive-theme" }, [
              createBaseVNode("button", {
                title: "Copy Code",
                class: "copy"
              }),
              createBaseVNode("span", { class: "lang" }, "json"),
              createBaseVNode("pre", {
                class: "shiki shiki-themes github-light github-dark vp-code",
                tabindex: "0"
              }, [
                createBaseVNode("code", null, [
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '    "led_matrix"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": {")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '        "layout"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": [")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "            {"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '"matrix"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": ["),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "0"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "3"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "], "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '"x"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "188"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '"y"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "16"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '"flags"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "1"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "},")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "            {"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '"matrix"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": ["),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "1"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "3"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "], "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '"x"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "187"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '"y"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "48"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '"flags"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "4"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "},")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "            {"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '"matrix"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": ["),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "2"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "3"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "], "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '"x"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "147"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '"y"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "64"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '"flags"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "4"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "},")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "            {"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '"matrix"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": ["),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "2"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "0"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "], "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '"x"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "112"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '"y"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "64"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '"flags"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "4"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "},")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "            {"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '"matrix"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": ["),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "1"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "0"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "], "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '"x"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "37"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '"y"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "48"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '"flags"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "4"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "},")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "            {"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '"matrix"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": ["),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "0"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "0"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "], "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '"x"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "38"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '"y"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "16"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '"flags"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "1"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "}")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "        ]")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    }")
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("The first part, "),
              createBaseVNode("code", null, "matrix"),
              createTextVNode(", tells the system what key this LED represents using the key's electrical matrix row & col. This part is optional, if the LED doesn't correspond to a switch (such as underglow leds).")
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("The second and third parts represents the LED's physical "),
              createBaseVNode("code", null, "x, y"),
              createTextVNode(" position on the keyboard. The default expected range of values for "),
              createBaseVNode("code", null, "x"),
              createTextVNode(" is "),
              createBaseVNode("code", null, "0-224"),
              createTextVNode(", and the default expected range of values for "),
              createBaseVNode("code", null, "y"),
              createTextVNode(" is "),
              createBaseVNode("code", null, "0-64"),
              createTextVNode(". This default expected range is due to effects that calculate the center of the keyboard for their animations. The easiest way to calculate these positions is imagine your keyboard is a grid, and the top left of the keyboard represents "),
              createBaseVNode("code", null, "{ x, y }"),
              createTextVNode(" coordinate "),
              createBaseVNode("code", null, "{ 0, 0 }"),
              createTextVNode(" and the bottom right of your keyboard represents "),
              createBaseVNode("code", null, "{ 224, 64 }"),
              createTextVNode(". Using this as a basis, you can use the following formula to calculate the physical position:")
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
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "x "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 224"),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " /"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " (NUMBER_OF_COLS "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "-"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 1"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "*"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " COL_POSITION")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "y "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "  64"),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " /"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " (NUMBER_OF_ROWS "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "-"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 1"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "*"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " ROW_POSITION")
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("p", null, "Where NUMBER_OF_COLS, NUMBER_OF_ROWS, COL_POSITION, & ROW_POSITION are all based on the physical layout of your keyboard, not the electrical layout.", -1),
            createBaseVNode("p", null, [
              createTextVNode("As mentioned earlier, the center of the keyboard by default is expected to be "),
              createBaseVNode("code", null, "{ 112, 32 }"),
              createTextVNode(", but this can be changed if you want to more accurately calculate the LED's physical "),
              createBaseVNode("code", null, "{ x, y }"),
              createTextVNode(" positions. Keyboard designers can implement "),
              createBaseVNode("code", null, "led_matrix.center_point = [ 112, 32 ]"),
              createTextVNode(" in their json with the new center point of the keyboard, or where they want it to be allowing more possibilities for the "),
              createBaseVNode("code", null, "x, y"),
              createTextVNode(" values. Do note that the maximum value for x or y is 255, and the recommended maximum is 224 as this gives animations runoff room before they reset.")
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("The last value "),
              createBaseVNode("code", null, "flags"),
              createTextVNode(" is a bitmask, whether or not a certain LEDs is of a certain type. It is recommended that LEDs are set to only 1 type.")
            ], -1)
          ])]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "`<keyboard>.c`" }, {
          default: withCtx(() => [..._cache[3] || (_cache[3] = [
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
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "led_config_t"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " g_led_config "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " { {")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "  // Key Matrix to LED Index")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "  {   "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "5"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", NO_LED, NO_LED,   "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "0"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " },")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "  { NO_LED, NO_LED, NO_LED, NO_LED },")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "  {   "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "4"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", NO_LED, NO_LED,   "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "1"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " },")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "  {   "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "3"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", NO_LED, NO_LED,   "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "2"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " }")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "}, {")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "  // LED Index to Physical Position")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "  { "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "188"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",  "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "16"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " }, { "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "187"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",  "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "48"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " }, { "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "149"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",  "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "64"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " }, { "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "112"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",  "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "64"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " }, {  "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "37"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",  "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "48"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " }, {  "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "38"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",  "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "16"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " }")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "}, {")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "  // LED Index to Flag")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "  1"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "4"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "4"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "4"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "4"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "1")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "} };")
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("p", null, [
              createTextVNode("The first part, "),
              createBaseVNode("code", null, "// Key Matrix to LED Index"),
              createTextVNode(", tells the system what key this LED represents by using the key's electrical matrix row & col. The second part, "),
              createBaseVNode("code", null, "// LED Index to Physical Position"),
              createTextVNode(" represents the LED's physical "),
              createBaseVNode("code", null, "{ x, y }"),
              createTextVNode(" position on the keyboard. The default expected range of values for "),
              createBaseVNode("code", null, "{ x, y }"),
              createTextVNode(" is the inclusive range "),
              createBaseVNode("code", null, "{ 0..224, 0..64 }"),
              createTextVNode(". This default expected range is due to effects that calculate the center of the keyboard for their animations. The easiest way to calculate these positions is imagine your keyboard is a grid, and the top left of the keyboard represents "),
              createBaseVNode("code", null, "{ x, y }"),
              createTextVNode(" coordinate "),
              createBaseVNode("code", null, "{ 0, 0 }"),
              createTextVNode(" and the bottom right of your keyboard represents "),
              createBaseVNode("code", null, "{ 224, 64 }"),
              createTextVNode(". Using this as a basis, you can use the following formula to calculate the physical position:")
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
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "x "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 224"),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " /"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " (NUMBER_OF_COLS "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "-"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 1"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "*"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " COL_POSITION")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "y "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "="),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "  64"),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, " /"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " (NUMBER_OF_ROWS "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "-"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 1"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "*"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " ROW_POSITION")
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("p", null, "Where NUMBER_OF_COLS, NUMBER_OF_ROWS, COL_POSITION, & ROW_POSITION are all based on the physical layout of your keyboard, not the electrical layout.", -1),
            createBaseVNode("p", null, [
              createTextVNode("As mentioned earlier, the center of the keyboard by default is expected to be "),
              createBaseVNode("code", null, "{ 112, 32 }"),
              createTextVNode(", but this can be changed if you want to more accurately calculate the LED's physical "),
              createBaseVNode("code", null, "{ x, y }"),
              createTextVNode(" positions. Keyboard designers can implement "),
              createBaseVNode("code", null, "#define LED_MATRIX_CENTER { 112, 32 }"),
              createTextVNode(" in their config.h file with the new center point of the keyboard, or where they want it to be allowing more possibilities for the "),
              createBaseVNode("code", null, "{ x, y }"),
              createTextVNode(" values. Do note that the maximum value for x or y is 255, and the recommended maximum is 224 as this gives animations runoff room before they reset.")
            ], -1),
            createBaseVNode("p", null, [
              createBaseVNode("code", null, "// LED Index to Flag"),
              createTextVNode(" is a bitmask, whether or not a certain LEDs is of a certain type. It is recommended that LEDs are set to only 1 type.")
            ], -1)
          ])]),
          _: 1
        })
      ]),
      _: 1
    }),
    _cache[11] || (_cache[11] = createStaticVNode("", 7)),
    createVNode(_component_PluginTabs, null, {
      default: withCtx(() => [
        createVNode(_component_PluginTabsTab, { label: "`JSON`" }, {
          default: withCtx(() => [..._cache[4] || (_cache[4] = [
            createBaseVNode("p", null, [
              createTextVNode("You can enable a single effect by setting it true in the "),
              createBaseVNode("code", null, "led_matrix.animations"),
              createTextVNode(" section in your json:")
            ], -1),
            createBaseVNode("div", { class: "language-json vp-adaptive-theme" }, [
              createBaseVNode("button", {
                title: "Copy Code",
                class: "copy"
              }),
              createBaseVNode("span", { class: "lang" }, "json"),
              createBaseVNode("pre", {
                class: "shiki shiki-themes github-light github-dark vp-code",
                tabindex: "0"
              }, [
                createBaseVNode("code", null, [
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '    "led_matrix"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": {")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '        "animations"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": {")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "alphas_mods"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "breathing"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "band"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "band_pinwheel"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "band_spiral"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "cycle_left_right"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "cycle_up_down"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "cycle_out_in"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "dual_beacon"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",  ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "wave_left_right"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "wave_up_down"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",          ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "        }")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    },")
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("p", null, [
              createBaseVNode("strong", null, "Framebuffer effects")
            ], -1),
            createBaseVNode("div", { class: "language-json vp-adaptive-theme" }, [
              createBaseVNode("button", {
                title: "Copy Code",
                class: "copy"
              }),
              createBaseVNode("span", { class: "lang" }, "json"),
              createBaseVNode("pre", {
                class: "shiki shiki-themes github-light github-dark vp-code",
                tabindex: "0"
              }, [
                createBaseVNode("code", null, [
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '    "led_matrix"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": {")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '        "animations"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": {")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "typing_heatmap"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "        }")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    }")
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("div", { class: "tip custom-block" }, [
              createBaseVNode("p", { class: "custom-block-title" }, "TIP"),
              createBaseVNode("p", null, "These modes introduce additional logic that can increase firmware size.")
            ], -1),
            createBaseVNode("p", null, [
              createBaseVNode("strong", null, "Reactive effects")
            ], -1),
            createBaseVNode("div", { class: "language-json vp-adaptive-theme" }, [
              createBaseVNode("button", {
                title: "Copy Code",
                class: "copy"
              }),
              createBaseVNode("span", { class: "lang" }, "json"),
              createBaseVNode("pre", {
                class: "shiki shiki-themes github-light github-dark vp-code",
                tabindex: "0"
              }, [
                createBaseVNode("code", null, [
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '    "led_matrix"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": {")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '        "animations"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": {")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "solid_reactive_simple"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "solid_reactive"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "solid_reactive_wide"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "solid_reactive_multiwide"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "solid_reactive_cross"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "solid_reactive_multicross"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "solid_reactive_nexus"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "solid_reactive_multinexus"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "splash"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "multisplash"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "        }")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    }")
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("div", { class: "tip custom-block" }, [
              createBaseVNode("p", { class: "custom-block-title" }, "TIP"),
              createBaseVNode("p", null, "These modes introduce additional logic that can increase firmware size.")
            ], -1)
          ])]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "`config.h`" }, {
          default: withCtx(() => [..._cache[5] || (_cache[5] = [
            createBaseVNode("p", null, [
              createTextVNode("You can enable a single effect by defining "),
              createBaseVNode("code", null, "ENABLE_[EFFECT_NAME]"),
              createTextVNode(" in your "),
              createBaseVNode("code", null, "config.h"),
              createTextVNode(":")
            ], -1),
            createBaseVNode("table", { tabindex: "0" }, [
              createBaseVNode("thead", null, [
                createBaseVNode("tr", null, [
                  createBaseVNode("th", null, "Define"),
                  createBaseVNode("th", null, "Description")
                ])
              ]),
              createBaseVNode("tbody", null, [
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_LED_MATRIX_ALPHAS_MODS")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "LED_MATRIX_ALPHAS_MODS")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_LED_MATRIX_BREATHING")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "LED_MATRIX_BREATHING")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_LED_MATRIX_BAND")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "LED_MATRIX_BAND")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_LED_MATRIX_BAND_PINWHEEL")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "LED_MATRIX_BAND_PINWHEEL")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_LED_MATRIX_BAND_SPIRAL")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "LED_MATRIX_BAND_SPIRAL")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_LED_MATRIX_CYCLE_LEFT_RIGHT")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "LED_MATRIX_CYCLE_LEFT_RIGHT")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_LED_MATRIX_CYCLE_UP_DOWN")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "LED_MATRIX_CYCLE_UP_DOWN")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_LED_MATRIX_CYCLE_OUT_IN")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "LED_MATRIX_CYCLE_OUT_IN")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_LED_MATRIX_DUAL_BEACON")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "LED_MATRIX_DUAL_BEACON")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_LED_MATRIX_WAVE_LEFT_RIGHT")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "LED_MATRIX_WAVE_LEFT_RIGHT")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_LED_MATRIX_WAVE_UP_DOWN")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "LED_MATRIX_WAVE_UP_DOWN")
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("table", { tabindex: "0" }, [
              createBaseVNode("thead", null, [
                createBaseVNode("tr", null, [
                  createBaseVNode("th", null, "Framebuffer Defines"),
                  createBaseVNode("th", null, "Description")
                ])
              ]),
              createBaseVNode("tbody", null, [
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_LED_MATRIX_TYPING_HEATMAP")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "LED_MATRIX_TYPING_HEATMAP")
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("div", { class: "tip custom-block" }, [
              createBaseVNode("p", { class: "custom-block-title" }, "TIP"),
              createBaseVNode("p", null, "These modes introduce additional logic that can increase firmware size.")
            ], -1),
            createBaseVNode("table", { tabindex: "0" }, [
              createBaseVNode("thead", null, [
                createBaseVNode("tr", null, [
                  createBaseVNode("th", null, "Reactive Defines"),
                  createBaseVNode("th", null, "Description")
                ])
              ]),
              createBaseVNode("tbody", null, [
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_LED_MATRIX_SOLID_REACTIVE_SIMPLE")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "LED_MATRIX_SOLID_REACTIVE_SIMPLE")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_LED_MATRIX_SOLID_REACTIVE_WIDE")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "LED_MATRIX_SOLID_REACTIVE_WIDE")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTIWIDE")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "LED_MATRIX_SOLID_REACTIVE_MULTIWIDE")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_LED_MATRIX_SOLID_REACTIVE_CROSS")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "LED_MATRIX_SOLID_REACTIVE_CROSS")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTICROSS")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "LED_MATRIX_SOLID_REACTIVE_MULTICROSS")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_LED_MATRIX_SOLID_REACTIVE_NEXUS")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "LED_MATRIX_SOLID_REACTIVE_NEXUS")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTINEXUS")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "LED_MATRIX_SOLID_REACTIVE_MULTINEXUS")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_LED_MATRIX_SOLID_SPLASH")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "LED_MATRIX_SOLID_SPLASH")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_LED_MATRIX_SOLID_MULTISPLASH")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "LED_MATRIX_SOLID_MULTISPLASH")
                  ])
                ])
              ])
            ], -1),
            createBaseVNode("div", { class: "tip custom-block" }, [
              createBaseVNode("p", { class: "custom-block-title" }, "TIP"),
              createBaseVNode("p", null, "These modes introduce additional logic that can increase firmware size.")
            ], -1)
          ])]),
          _: 1
        })
      ]),
      _: 1
    }),
    _cache[12] || (_cache[12] = createStaticVNode("", 29)),
    createVNode(_component_PluginTabs, null, {
      default: withCtx(() => [
        createVNode(_component_PluginTabsTab, { label: "`JSON`" }, {
          default: withCtx(() => [..._cache[6] || (_cache[6] = [
            createBaseVNode("div", { class: "language-json vp-adaptive-theme" }, [
              createBaseVNode("button", {
                title: "Copy Code",
                class: "copy"
              }),
              createBaseVNode("span", { class: "lang" }, "json"),
              createBaseVNode("pre", {
                class: "shiki shiki-themes github-light github-dark vp-code",
                tabindex: "0"
              }, [
                createBaseVNode("code", null, [
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '    "led_matrix"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": {")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '        "default"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": {")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "            // Sets the default enabled state, if none has been set")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "on"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "            // Sets the default mode, if none has been set")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "animation"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '"solid"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "            // Sets the default brightness value, if none has been set")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "val"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "127"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "            // Sets the default speed, if none has been set")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "speed"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "127"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "            // Sets the default flag, if none has been set")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "flags"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "255"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "        },")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "        // Sets the flags which can be cycled through")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '        "flag_steps"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": [ ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "            // LED_FLAG_ALL, LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER, LED_FLAG_NONE")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "            255"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "5"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "0"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "  ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "        ],")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "        // limits max brightness of leds")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '        "max_brightness"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "255"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "        // number of milliseconds to wait until led automatically turns off")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '        "timeout"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "0"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "        // The value by which to increment the brightness per adjustment action")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '        "val_steps"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "16"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "        // The value by which to increment the animation speed per adjustment action")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '        "speed_steps"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "16"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "        // limits in milliseconds how frequently an animation will update the LEDs. ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "        // 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '        "led_flush_limit"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "16"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "        // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '        "led_process_limit"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "15"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "        // reactive effects respond to keyreleases (instead of keypresses)")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '        "react_on_keyup"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",  ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "        // turn off effects when suspended")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '        "sleep"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",  ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "        // (Optional) For split keyboards, the number of LEDs connected on each half. X = left, Y = Right.")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "        // If reactive effects are enabled, you also will want to enable split.transport.sync.matrix_state")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '        "split_count"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": ["),
                    createBaseVNode("span", { style: { "--shiki-light": "#B31D28", "--shiki-light-font-style": "italic", "--shiki-dark": "#FDAEB7", "--shiki-dark-font-style": "italic" } }, "X"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#B31D28", "--shiki-light-font-style": "italic", "--shiki-dark": "#FDAEB7", "--shiki-dark-font-style": "italic" } }, "Y"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "],  ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "    }")
                  ])
                ])
              ])
            ], -1)
          ])]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "`config.h`" }, {
          default: withCtx(() => [..._cache[7] || (_cache[7] = [
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
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " LED_MATRIX_KEYRELEASES"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // reactive effects respond to keyreleases (instead of keypresses)")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " LED_MATRIX_TIMEOUT"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 0"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // number of milliseconds to wait until led automatically turns off")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " LED_MATRIX_SLEEP"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // turn off effects when suspended")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " LED_MATRIX_LED_PROCESS_LIMIT"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " (LED_MATRIX_LED_COUNT "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "+"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 4"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ") "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "/"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 5"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " LED_MATRIX_LED_FLUSH_LIMIT"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 16"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " LED_MATRIX_MAXIMUM_BRIGHTNESS"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 255"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // limits maximum brightness of LEDs")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " LED_MATRIX_DEFAULT_ON"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // Sets the default enabled state, if none has been set")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " LED_MATRIX_DEFAULT_MODE"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " LED_MATRIX_SOLID"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // Sets the default mode, if none has been set")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " LED_MATRIX_DEFAULT_VAL"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " LED_MATRIX_MAXIMUM_BRIGHTNESS"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // Sets the default brightness value, if none has been set")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " LED_MATRIX_DEFAULT_SPD"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 127"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // Sets the default animation speed, if none has been set")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " LED_MATRIX_VAL_STEP"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 8"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // The value by which to increment the brightness per adjustment action")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " LED_MATRIX_SPD_STEP"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 16"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // The value by which to increment the animation speed per adjustment action")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " LED_MATRIX_DEFAULT_FLAGS"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " LED_FLAG_ALL"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // Sets the default LED flags, if none has been set")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " LED_MATRIX_SPLIT"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " { X, Y }"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "   // (Optional) For split keyboards, the number of LEDs connected on each half. X = left, Y = Right.")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "                                    // If reactive effects are enabled, you also will want to enable SPLIT_TRANSPORT_MIRROR")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " LED_MATRIX_FLAG_STEPS"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " { LED_FLAG_ALL, LED_FLAG_KEYLIGHT "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "|"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " LED_FLAG_MODIFIER, LED_FLAG_NONE }"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // Sets the flags which can be cycled through.")
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
    _cache[13] || (_cache[13] = createStaticVNode("", 173))
  ]);
}
const led_matrix = /* @__PURE__ */ _export_sfc(_sfc_main, [["render", _sfc_render]]);
export {
  __pageData,
  led_matrix as default
};
