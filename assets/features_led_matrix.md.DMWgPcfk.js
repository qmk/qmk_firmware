import { _ as _export_sfc, C as resolveComponent, o as openBlock, c as createElementBlock, al as createStaticVNode, E as createVNode, w as withCtx, j as createBaseVNode, a as createTextVNode } from "./chunks/framework.8zKZLKO7.js";
const __pageData = JSON.parse('{"title":"LED Matrix Lighting","description":"","frontmatter":{},"headers":[],"relativePath":"features/led_matrix.md","filePath":"features/led_matrix.md","lastUpdated":null}');
const _sfc_main = { name: "features/led_matrix.md" };
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  const _component_PluginTabsTab = resolveComponent("PluginTabsTab");
  const _component_PluginTabs = resolveComponent("PluginTabs");
  return openBlock(), createElementBlock("div", null, [
    _cache[8] || (_cache[8] = createStaticVNode('<h1 id="led-matrix-lighting" tabindex="-1">LED Matrix Lighting <a class="header-anchor" href="#led-matrix-lighting" aria-label="Permalink to &quot;LED Matrix Lighting {#led-matrix-lighting}&quot;">​</a></h1><p>This feature allows you to use LED matrices driven by external drivers. It hooks into the backlight system so you can use the same keycodes as backlighting to control it.</p><p>If you want to use RGB LED&#39;s you should use the <a href="./rgb_matrix">RGB Matrix Subsystem</a> instead.</p><h2 id="driver-configuration" tabindex="-1">Driver Configuration <a class="header-anchor" href="#driver-configuration" aria-label="Permalink to &quot;Driver Configuration {#driver-configuration}&quot;">​</a></h2><p>LED Matrix is an abstraction layer on top of an underlying LED driver API. The list of supported LED drivers is below; see the respective documentation for information on how to configure the driver.</p><table tabindex="0"><thead><tr><th>Driver</th><th>Max LEDs</th></tr></thead><tbody><tr><td><a href="./../drivers/is31fl3218">IS31FL3218</a></td><td>18</td></tr><tr><td><a href="./../drivers/is31fl3236">IS31FL3236</a></td><td>36</td></tr><tr><td><a href="./../drivers/is31fl3729">IS31FL3729</a></td><td>135</td></tr><tr><td><a href="./../drivers/is31fl3731">IS31FL3731</a></td><td>144</td></tr><tr><td><a href="./../drivers/is31fl3733">IS31FL3733</a></td><td>192</td></tr><tr><td><a href="./../drivers/is31fl3736">IS31FL3736</a></td><td>96</td></tr><tr><td><a href="./../drivers/is31fl3737">IS31FL3737</a></td><td>144</td></tr><tr><td><a href="./../drivers/is31fl3741">IS31FL3741</a></td><td>351</td></tr><tr><td><a href="./../drivers/is31fl3742a">IS31FL3742A</a></td><td>180</td></tr><tr><td><a href="./../drivers/is31fl3743a">IS31FL3743A</a></td><td>198</td></tr><tr><td><a href="./../drivers/is31fl3745">IS31FL3745</a></td><td>144</td></tr><tr><td><a href="./../drivers/is31fl3746a">IS31FL3746A</a></td><td>72</td></tr><tr><td><a href="./../drivers/snled27351">SNLED27351</a></td><td>192</td></tr></tbody></table><p>To assign the LED Matrix driver, add the following to your keyboard config, for example:</p>', 7)),
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
    _cache[11] || (_cache[11] = createStaticVNode('<h2 id="flags" tabindex="-1">Flags <a class="header-anchor" href="#flags" aria-label="Permalink to &quot;Flags {#flags}&quot;">​</a></h2><table tabindex="0"><thead><tr><th>Define</th><th>Value</th><th>Description</th></tr></thead><tbody><tr><td><code>HAS_FLAGS(bits, flags)</code></td><td><em>n/a</em></td><td>Evaluates to <code>true</code> if <code>bits</code> has all <code>flags</code> set</td></tr><tr><td><code>HAS_ANY_FLAGS(bits, flags)</code></td><td><em>n/a</em></td><td>Evaluates to <code>true</code> if <code>bits</code> has any <code>flags</code> set</td></tr><tr><td><code>LED_FLAG_NONE</code></td><td><code>0x00</code></td><td>If this LED has no flags</td></tr><tr><td><code>LED_FLAG_ALL</code></td><td><code>0xFF</code></td><td>If this LED has all flags</td></tr><tr><td><code>LED_FLAG_MODIFIER</code></td><td><code>0x01</code></td><td>If the LED is on a modifier key</td></tr><tr><td><code>LED_FLAG_KEYLIGHT</code></td><td><code>0x04</code></td><td>If the LED is for key backlight</td></tr><tr><td><code>LED_FLAG_INDICATOR</code></td><td><code>0x08</code></td><td>If the LED is for keyboard state indication</td></tr></tbody></table><h2 id="keycodes" tabindex="-1">Keycodes <a class="header-anchor" href="#keycodes" aria-label="Permalink to &quot;Keycodes {#keycodes}&quot;">​</a></h2><table tabindex="0"><thead><tr><th>Key</th><th>Aliases</th><th>Description</th></tr></thead><tbody><tr><td><code>QK_LED_MATRIX_ON</code></td><td><code>LM_ON</code></td><td>Turn on LED Matrix</td></tr><tr><td><code>QK_LED_MATRIX_OFF</code></td><td><code>LM_OFF</code></td><td>Turn off LED Matrix</td></tr><tr><td><code>QK_LED_MATRIX_TOGGLE</code></td><td><code>LM_TOGG</code></td><td>Toggle LED Matrix on or off</td></tr><tr><td><code>QK_LED_MATRIX_MODE_NEXT</code></td><td><code>LM_NEXT</code></td><td>Cycle through animations</td></tr><tr><td><code>QK_LED_MATRIX_MODE_PREVIOUS</code></td><td><code>LM_PREV</code></td><td>Cycle through animations in reverse</td></tr><tr><td><code>QK_LED_MATRIX_BRIGHTNESS_UP</code></td><td><code>LM_BRIU</code></td><td>Increase the brightness level</td></tr><tr><td><code>QK_LED_MATRIX_BRIGHTNESS_DOWN</code></td><td><code>LM_BRID</code></td><td>Decrease the brightness level</td></tr><tr><td><code>QK_LED_MATRIX_SPEED_UP</code></td><td><code>LM_SPDU</code></td><td>Increase the animation speed</td></tr><tr><td><code>QK_LED_MATRIX_SPEED_DOWN</code></td><td><code>LM_SPDD</code></td><td>Decrease the animation speed</td></tr><tr><td><code>QK_LED_MATRIX_FLAG_NEXT</code></td><td><code>LM_FLGN</code></td><td>Cycle through flags</td></tr><tr><td><code>QK_LED_MATRIX_FLAG_PREVIOUS</code></td><td><code>LM_FLGP</code></td><td>Cycle through flags in reverse</td></tr></tbody></table><h2 id="led-matrix-effects" tabindex="-1">LED Matrix Effects <a class="header-anchor" href="#led-matrix-effects" aria-label="Permalink to &quot;LED Matrix Effects {#led-matrix-effects}&quot;">​</a></h2><p>These are the effects that are currently available:</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">enum</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> led_matrix_effects {</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    LED_MATRIX_NONE </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">=</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> 0</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">,</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    LED_MATRIX_SOLID </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">=</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> 1</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">           // Static single val, no speed support</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    LED_MATRIX_ALPHAS_MODS,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">         // Static dual val, speed is val for LEDs marked as modifiers</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    LED_MATRIX_BREATHING,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">           // Cycling brightness animation</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    LED_MATRIX_BAND,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">                // Band fading brightness scrolling left to right</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    LED_MATRIX_BAND_PINWHEEL,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">       // 3 blade spinning pinwheel fades brightness</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    LED_MATRIX_BAND_SPIRAL,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">         // Spinning spiral fades brightness</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    LED_MATRIX_CYCLE_LEFT_RIGHT,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">    // Full gradient scrolling left to right</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    LED_MATRIX_CYCLE_UP_DOWN,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">       // Full gradient scrolling top to bottom</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    LED_MATRIX_CYCLE_OUT_IN,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">        // Full gradient scrolling out to in</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    LED_MATRIX_DUAL_BEACON,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">         // Full gradient spinning around center of keyboard</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    LED_MATRIX_SOLID_REACTIVE_SIMPLE,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">   // Pulses keys hit then fades out</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    LED_MATRIX_SOLID_REACTIVE_WIDE,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">       // Value pulses near a single key hit then fades out</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    LED_MATRIX_SOLID_REACTIVE_MULTIWIDE,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">  // Value pulses near multiple key hits then fades out</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    LED_MATRIX_SOLID_REACTIVE_CROSS,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">      // Value pulses the same column and row of a single key hit then fades out</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    LED_MATRIX_SOLID_REACTIVE_MULTICROSS,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;"> // Value pulses the same column and row of multiple key hits then fades out</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    LED_MATRIX_SOLID_REACTIVE_NEXUS,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">      // Value pulses away on the same column and row of a single key hit then fades out</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    LED_MATRIX_SOLID_REACTIVE_MULTINEXUS,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;"> // Value pulses away on the same column and row of multiple key hits then fades out</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    LED_MATRIX_SOLID_SPLASH,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">             // Value pulses away from a single key hit then fades out</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    LED_MATRIX_SOLID_MULTISPLASH,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">        // Value pulses away from multiple key hits then fades out</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    LED_MATRIX_WAVE_LEFT_RIGHT,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">           // Sine wave scrolling from left to right</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    LED_MATRIX_WAVE_UP_DOWN,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">              // Sine wave scrolling from up to down</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    LED_MATRIX_TYPING_HEATMAP,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">            // How hot is your WPM!</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    LED_MATRIX_EFFECT_MAX</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">};</span></span></code></pre></div>', 7)),
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
    _cache[12] || (_cache[12] = createStaticVNode('<h3 id="led-matrix-effect-typing-heatmap" tabindex="-1">LED Matrix Effect Typing Heatmap <a class="header-anchor" href="#led-matrix-effect-typing-heatmap" aria-label="Permalink to &quot;LED Matrix Effect Typing Heatmap {#led-matrix-effect-typing-heatmap}&quot;">​</a></h3><p>This effect will scale the LED matrix brightness according to a heatmap of recently pressed keys. Whenever a key is pressed its &quot;temperature&quot; increases as well as that of its neighboring keys. The temperature of each key is then decreased automatically every 25 milliseconds by default.</p><p>In order to change the delay of temperature decrease define <code>LED_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS</code>:</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#define</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> LED_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> 50</span></span></code></pre></div><p>As heatmap uses the physical position of the leds set in the g_led_config, you may need to tweak the following options to get the best effect for your keyboard. Note the size of this grid is <code>224x64</code>.</p><p>Limit the distance the effect spreads to surrounding keys.</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#define</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> LED_MATRIX_TYPING_HEATMAP_SPREAD</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> 40</span></span></code></pre></div><p>Limit how hot surrounding keys get from each press.</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#define</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> LED_MATRIX_TYPING_HEATMAP_AREA_LIMIT</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> 16</span></span></code></pre></div><p>Remove the spread effect entirely.</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#define</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> LED_MATRIX_TYPING_HEATMAP_SLIM</span></span></code></pre></div><p>It&#39;s also possible to adjust the tempo of <em>heating up</em>. It&#39;s defined as the number of steps by which to increment the brightness. Decreasing this value increases the number of keystrokes needed to fully heat up the key.</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#define</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> LED_MATRIX_TYPING_HEATMAP_INCREASE_STEP</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> 32</span></span></code></pre></div><h2 id="custom-led-matrix-effects" tabindex="-1">Custom LED Matrix Effects <a class="header-anchor" href="#custom-led-matrix-effects" aria-label="Permalink to &quot;Custom LED Matrix Effects {#custom-led-matrix-effects}&quot;">​</a></h2><p>By setting <code>LED_MATRIX_CUSTOM_USER = yes</code> in <code>rules.mk</code>, new effects can be defined directly from your keymap or userspace, without having to edit any QMK core files. To declare new effects, create a <code>led_matrix_user.inc</code> file in the user keymap directory or userspace folder.</p><div class="tip custom-block"><p class="custom-block-title">TIP</p><p>Hardware maintainers who want to limit custom effects to a specific keyboard can create a <code>led_matrix_kb.inc</code> file in the root of the keyboard directory, and add <code>LED_MATRIX_CUSTOM_KB = yes</code> to the keyboard level <code>rules.mk</code>.</p></div><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">// !!! DO NOT ADD #pragma once !!!</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;"> //</span></span>\n<span class="line"></span>\n<span class="line"><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">// Step 1.</span></span>\n<span class="line"><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">// Declare custom effects using the LED_MATRIX_EFFECT macro</span></span>\n<span class="line"><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">// (note the lack of semicolon after the macro!)</span></span>\n<span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">LED_MATRIX_EFFECT</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(my_cool_effect)</span></span>\n<span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">LED_MATRIX_EFFECT</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(my_cool_effect2)</span></span>\n<span class="line"></span>\n<span class="line"><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">// Step 2.</span></span>\n<span class="line"><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">// Define effects inside the `LED_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#ifdef</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> LED_MATRIX_CUSTOM_EFFECT_IMPLS</span></span>\n<span class="line"></span>\n<span class="line"><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">// e.g: A simple effect, self-contained within a single method</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">static</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;"> bool</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> my_cool_effect</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">effect_params_t</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">*</span><span style="--shiki-light:#E36209;--shiki-dark:#FFAB70;"> params</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) {</span></span>\n<span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">  LED_MATRIX_USE_LIMITS</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(led_min, led_max);</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">  for</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> (</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">uint8_t</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> i </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">=</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> led_min; i </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">&lt;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> led_max; i</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">++</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) {</span></span>\n<span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">    led_matrix_set_value</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(i, </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">0x</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">FF</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">);</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">  }</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">  return</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> led_matrix_check_finished_leds</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(led_max);</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">}</span></span>\n<span class="line"></span>\n<span class="line"><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">// e.g: A more complex effect, relying on external methods and state, with</span></span>\n<span class="line"><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">// dedicated init and run methods</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">static</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;"> uint8_t</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> some_global_state;</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">static</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;"> void</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> my_cool_effect2_complex_init</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">effect_params_t</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">*</span><span style="--shiki-light:#E36209;--shiki-dark:#FFAB70;"> params</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) {</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">  some_global_state </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">=</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> 1</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">;</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">}</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">static</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;"> bool</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> my_cool_effect2_complex_run</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">effect_params_t</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">*</span><span style="--shiki-light:#E36209;--shiki-dark:#FFAB70;"> params</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) {</span></span>\n<span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">  LED_MATRIX_USE_LIMITS</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(led_min, led_max);</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">  for</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> (</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">uint8_t</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> i </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">=</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> led_min; i </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">&lt;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> led_max; i</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">++</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) {</span></span>\n<span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">    led_matrix_set_value</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(i, some_global_state</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">++</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">);</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">  }</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">  return</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> led_matrix_check_finished_leds</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(led_max);</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">}</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">static</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;"> bool</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> my_cool_effect2</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">effect_params_t</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">*</span><span style="--shiki-light:#E36209;--shiki-dark:#FFAB70;"> params</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) {</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">  if</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> (params-&gt;init) </span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">my_cool_effect2_complex_init</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(params);</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">  return</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> my_cool_effect2_complex_run</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(params);</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">}</span></span>\n<span class="line"></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#endif</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;"> // LED_MATRIX_CUSTOM_EFFECT_IMPLS</span></span></code></pre></div><p>To switch to your custom effect programmatically, simply call <code>led_matrix_mode()</code> and prepend <code>LED_MATRIX_CUSTOM_</code> to the effect name your specified in <code>LED_MATRIX_EFFECT()</code>. For example, an effect declared as <code>LED_MATRIX_EFFECT(my_cool_effect)</code> would be referenced with:</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">led_matrix_mode</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(LED_MATRIX_CUSTOM_my_cool_effect);</span></span></code></pre></div><p>For inspiration and examples, check out the built-in effects under <code>quantum/led_matrix/animations/</code>.</p><h2 id="naming" tabindex="-1">Naming <a class="header-anchor" href="#naming" aria-label="Permalink to &quot;Naming&quot;">​</a></h2><p>If you wish to be able to use the name of an effect in your code -- say for a display indicator -- then you can enable the function <code>led_matrix_get_mode_name</code> in the following manner:</p><p>In your keymap&#39;s <code>config.h</code>:</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#define</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> LED_MATRIX_MODE_NAME_ENABLE</span></span></code></pre></div><p>In your <code>keymap.c</code></p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">const</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;"> char*</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> effect_name </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">=</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> led_matrix_get_mode_name</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">led_matrix_get_mode</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">());</span></span>\n<span class="line"><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">// do something with `effect_name`, like `oled_write_ln(effect_name, false);`</span></span></code></pre></div><div class="info custom-block"><p class="custom-block-title">INFO</p><p><code>led_matrix_get_mode_name()</code> is not enabled by default as it increases the amount of flash memory used by the firmware based on the number of effects enabled.</p></div><h2 id="additional-configh-options" tabindex="-1">Additional Configuration Options <a class="header-anchor" href="#additional-configh-options" aria-label="Permalink to &quot;Additional Configuration Options {#additional-configh-options}&quot;">​</a></h2><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#define</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> LED_MATRIX_MODE_NAME_ENABLE</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;"> // enables led_matrix_get_mode_name()</span></span></code></pre></div>', 29)),
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
    _cache[13] || (_cache[13] = createStaticVNode('<h2 id="eeprom-storage" tabindex="-1">EEPROM storage <a class="header-anchor" href="#eeprom-storage" aria-label="Permalink to &quot;EEPROM storage {#eeprom-storage}&quot;">​</a></h2><p>The EEPROM for it is currently shared with the RGB Matrix system (it&#39;s generally assumed only one feature would be used at a time).</p><h2 id="callbacks" tabindex="-1">Callbacks <a class="header-anchor" href="#callbacks" aria-label="Permalink to &quot;Callbacks {#callbacks}&quot;">​</a></h2><h3 id="indicators" tabindex="-1">Indicators <a class="header-anchor" href="#indicators" aria-label="Permalink to &quot;Indicators {#indicators}&quot;">​</a></h3><p>If you want to set custom indicators, such as an LED for Caps Lock, or layer indication, then you can use the <code>led_matrix_indicators_kb</code> function on the keyboard level source file, or <code>led_matrix_indicators_user</code> function in the user <code>keymap.c</code>.</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">bool</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> led_matrix_indicators_kb</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">void</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) {</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">    if</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> (</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">!</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">led_matrix_indicators_user</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">()) {</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">        return</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> false</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">;</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    }</span></span>\n<span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">    led_matrix_set_value</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(index, value);</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">    return</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> true</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">;</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">}</span></span></code></pre></div><p>In addition, there are the advanced indicator functions. These are aimed at those with heavily customized displays, where rendering every LED per cycle is expensive. This includes a special macro to help make this easier to use: <code>LED_MATRIX_INDICATOR_SET_VALUE(i, v)</code>.</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">void</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> led_matrix_indicators_advanced_user</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">uint8_t</span><span style="--shiki-light:#E36209;--shiki-dark:#FFAB70;"> led_min</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">uint8_t</span><span style="--shiki-light:#E36209;--shiki-dark:#FFAB70;"> led_max</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) {</span></span>\n<span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">    LED_MATRIX_INDICATOR_SET_VALUE</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(index, value);</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">    return</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> false</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">;</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">}</span></span></code></pre></div><h2 id="api" tabindex="-1">API <a class="header-anchor" href="#api" aria-label="Permalink to &quot;API {#api}&quot;">​</a></h2><h3 id="api-led-matrix-toggle" tabindex="-1"><code>void led_matrix_toggle(void)</code> <a class="header-anchor" href="#api-led-matrix-toggle" aria-label="Permalink to &quot;`void led_matrix_toggle(void)` {#api-led-matrix-toggle}&quot;">​</a></h3><p>Toggle LED Matrix on or off.</p><hr><h3 id="api-led-matrix-toggle-noeeprom" tabindex="-1"><code>void led_matrix_toggle_noeeprom(void)</code> <a class="header-anchor" href="#api-led-matrix-toggle-noeeprom" aria-label="Permalink to &quot;`void led_matrix_toggle_noeeprom(void)` {#api-led-matrix-toggle-noeeprom}&quot;">​</a></h3><p>Toggle LED Matrix on or off. New state is not written to EEPROM.</p><hr><h3 id="api-led-matrix-enable" tabindex="-1"><code>void led_matrix_enable(void)</code> <a class="header-anchor" href="#api-led-matrix-enable" aria-label="Permalink to &quot;`void led_matrix_enable(void)` {#api-led-matrix-enable}&quot;">​</a></h3><p>Turn LED Matrix on.</p><hr><h3 id="api-led-matrix-enable-noeeprom" tabindex="-1"><code>void led_matrix_enable_noeeprom(void)</code> <a class="header-anchor" href="#api-led-matrix-enable-noeeprom" aria-label="Permalink to &quot;`void led_matrix_enable_noeeprom(void)` {#api-led-matrix-enable-noeeprom}&quot;">​</a></h3><p>Turn LED Matrix on. New state is not written to EEPROM.</p><hr><h3 id="api-led-matrix-disable" tabindex="-1"><code>void led_matrix_disable(void)</code> <a class="header-anchor" href="#api-led-matrix-disable" aria-label="Permalink to &quot;`void led_matrix_disable(void)` {#api-led-matrix-disable}&quot;">​</a></h3><p>Turn LED Matrix off.</p><hr><h3 id="api-led-matrix-disable-noeeprom" tabindex="-1"><code>void led_matrix_disable_noeeprom(void)</code> <a class="header-anchor" href="#api-led-matrix-disable-noeeprom" aria-label="Permalink to &quot;`void led_matrix_disable_noeeprom(void)` {#api-led-matrix-disable-noeeprom}&quot;">​</a></h3><p>Turn LED Matrix off. New state is not written to EEPROM.</p><hr><h3 id="api-led-matrix-is-enabled" tabindex="-1"><code>bool led_matrix_is_enabled(void)</code> <a class="header-anchor" href="#api-led-matrix-is-enabled" aria-label="Permalink to &quot;`bool led_matrix_is_enabled(void)` {#api-led-matrix-is-enabled}&quot;">​</a></h3><p>Get the current enabled state of LED Matrix.</p><h4 id="api-led-matrix-is-enabled-return" tabindex="-1">Return Value <a class="header-anchor" href="#api-led-matrix-is-enabled-return" aria-label="Permalink to &quot;Return Value {#api-led-matrix-is-enabled-return}&quot;">​</a></h4><p><code>true</code> if LED Matrix is enabled.</p><hr><h3 id="led-matrix-set-value" tabindex="-1"><code>void led_matrix_set_value(uint8_t index, uint8_t v)</code> <a class="header-anchor" href="#led-matrix-set-value" aria-label="Permalink to &quot;`void led_matrix_set_value(uint8_t index, uint8_t v)` {#led-matrix-set-value}&quot;">​</a></h3><p>Set the brightness of a single LED.</p><p>This function can only be run from within an effect or indicator callback, otherwise the currently running animation will simply overwrite it on the next frame.</p><h4 id="api-led-matrix-set-value-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-led-matrix-set-value-arguments" aria-label="Permalink to &quot;Arguments {#api-led-matrix-set-value-arguments}&quot;">​</a></h4><ul><li><code>uint8_t index</code><br> The LED index, from 0 to <code>LED_MATRIX_LED_COUNT - 1</code>.</li><li><code>uint8_t v</code><br> The brightness value to set.</li></ul><hr><h3 id="api-led-matrix-set-value-all" tabindex="-1"><code>void led_matrix_set_value_all(uint8_t v)</code> <a class="header-anchor" href="#api-led-matrix-set-value-all" aria-label="Permalink to &quot;`void led_matrix_set_value_all(uint8_t v)` {#api-led-matrix-set-value-all}&quot;">​</a></h3><p>Set the brightness of all LEDs.</p><p>This function can only be run from within an effect or indicator callback, otherwise the currently running animation will simply overwrite it on the next frame.</p><h4 id="api-led-matrix-set-value-all-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-led-matrix-set-value-all-arguments" aria-label="Permalink to &quot;Arguments {#api-led-matrix-set-value-all-arguments}&quot;">​</a></h4><ul><li><code>uint8_t v</code><br> The brightness value to set.</li></ul><hr><h3 id="api-led-matrix-mode" tabindex="-1"><code>void led_matrix_mode(uint8_t mode)</code> <a class="header-anchor" href="#api-led-matrix-mode" aria-label="Permalink to &quot;`void led_matrix_mode(uint8_t mode)` {#api-led-matrix-mode}&quot;">​</a></h3><p>Set the currently running effect.</p><h4 id="api-led-matrix-mode-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-led-matrix-mode-arguments" aria-label="Permalink to &quot;Arguments {#api-led-matrix-mode-arguments}&quot;">​</a></h4><ul><li><code>uint8_t mode</code><br> The effect to switch to.</li></ul><hr><h3 id="api-led-matrix-mode-noeeprom" tabindex="-1"><code>void led_matrix_mode_noeeprom(uint8_t mode)</code> <a class="header-anchor" href="#api-led-matrix-mode-noeeprom" aria-label="Permalink to &quot;`void led_matrix_mode_noeeprom(uint8_t mode)` {#api-led-matrix-mode-noeeprom}&quot;">​</a></h3><p>Set the currently running effect. New state is not written to EEPROM.</p><h4 id="api-led-matrix-mode-noeeprom-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-led-matrix-mode-noeeprom-arguments" aria-label="Permalink to &quot;Arguments {#api-led-matrix-mode-noeeprom-arguments}&quot;">​</a></h4><ul><li><code>uint8_t mode</code><br> The effect to switch to.</li></ul><hr><h3 id="api-led-matrix-step" tabindex="-1"><code>void led_matrix_step(void)</code> <a class="header-anchor" href="#api-led-matrix-step" aria-label="Permalink to &quot;`void led_matrix_step(void)` {#api-led-matrix-step}&quot;">​</a></h3><p>Move to the next enabled effect.</p><hr><h3 id="api-led-matrix-step-noeeprom" tabindex="-1"><code>void led_matrix_step_noeeprom(void)</code> <a class="header-anchor" href="#api-led-matrix-step-noeeprom" aria-label="Permalink to &quot;`void led_matrix_step_noeeprom(void)` {#api-led-matrix-step-noeeprom}&quot;">​</a></h3><p>Move to the next enabled effect. New state is not written to EEPROM.</p><hr><h3 id="api-led-matrix-step-reverse" tabindex="-1"><code>void led_matrix_step_reverse(void)</code> <a class="header-anchor" href="#api-led-matrix-step-reverse" aria-label="Permalink to &quot;`void led_matrix_step_reverse(void)` {#api-led-matrix-step-reverse}&quot;">​</a></h3><p>Move to the previous enabled effect.</p><hr><h3 id="api-led-matrix-step-reverse-noeeprom" tabindex="-1"><code>void led_matrix_step_reverse_noeeprom(void)</code> <a class="header-anchor" href="#api-led-matrix-step-reverse-noeeprom" aria-label="Permalink to &quot;`void led_matrix_step_reverse_noeeprom(void)` {#api-led-matrix-step-reverse-noeeprom}&quot;">​</a></h3><p>Move to the previous enabled effect. New state is not written to EEPROM.</p><hr><h3 id="api-led-matrix-get-mode" tabindex="-1"><code>uint8_t led_matrix_get_mode(void)</code> <a class="header-anchor" href="#api-led-matrix-get-mode" aria-label="Permalink to &quot;`uint8_t led_matrix_get_mode(void)` {#api-led-matrix-get-mode}&quot;">​</a></h3><p>Get the currently running effect.</p><h4 id="api-led-matrix-get-mode-return" tabindex="-1">Return Value <a class="header-anchor" href="#api-led-matrix-get-mode-return" aria-label="Permalink to &quot;Return Value {#api-led-matrix-get-mode-return}&quot;">​</a></h4><p>The index of the currently running effect.</p><hr><h3 id="api-led-matrix-increase-val" tabindex="-1"><code>void val_matrix_increase_val(void)</code> <a class="header-anchor" href="#api-led-matrix-increase-val" aria-label="Permalink to &quot;`void val_matrix_increase_val(void)` {#api-led-matrix-increase-val}&quot;">​</a></h3><p>Increase the global effect brightness.</p><hr><h3 id="api-led-matrix-increase-val-noeeprom" tabindex="-1"><code>void led_matrix_increase_val_noeeprom(void)</code> <a class="header-anchor" href="#api-led-matrix-increase-val-noeeprom" aria-label="Permalink to &quot;`void led_matrix_increase_val_noeeprom(void)` {#api-led-matrix-increase-val-noeeprom}&quot;">​</a></h3><p>Increase the global effect brightness. New state is not written to EEPROM.</p><hr><h3 id="api-led-matrix-decrease-val" tabindex="-1"><code>void led_matrix_decrease_val(void)</code> <a class="header-anchor" href="#api-led-matrix-decrease-val" aria-label="Permalink to &quot;`void led_matrix_decrease_val(void)` {#api-led-matrix-decrease-val}&quot;">​</a></h3><p>Decrease the global effect brightness.</p><hr><h3 id="api-led-matrix-decrease-val-noeeprom" tabindex="-1"><code>void led_matrix_decrease_val_noeeprom(void)</code> <a class="header-anchor" href="#api-led-matrix-decrease-val-noeeprom" aria-label="Permalink to &quot;`void led_matrix_decrease_val_noeeprom(void)` {#api-led-matrix-decrease-val-noeeprom}&quot;">​</a></h3><p>Decrease the global effect brightness. New state is not written to EEPROM.</p><hr><h3 id="api-led-matrix-get-val" tabindex="-1"><code>uint8_t led_matrix_get_val(void)</code> <a class="header-anchor" href="#api-led-matrix-get-val" aria-label="Permalink to &quot;`uint8_t led_matrix_get_val(void)` {#api-led-matrix-get-val}&quot;">​</a></h3><p>Get the current global effect brightness.</p><h4 id="api-led-matrix-get-val-return" tabindex="-1">Return Value <a class="header-anchor" href="#api-led-matrix-get-val-return" aria-label="Permalink to &quot;Return Value {#api-led-matrix-get-val-return}&quot;">​</a></h4><p>The current brightness value, from 0 to 255.</p><hr><h3 id="api-led-matrix-increase-speed" tabindex="-1"><code>void led_matrix_increase_speed(void)</code> <a class="header-anchor" href="#api-led-matrix-increase-speed" aria-label="Permalink to &quot;`void led_matrix_increase_speed(void)` {#api-led-matrix-increase-speed}&quot;">​</a></h3><p>Increase the effect speed.</p><hr><h3 id="api-led-matrix-increase-speed-noeeprom" tabindex="-1"><code>void led_matrix_increase_speed_noeeprom(void)</code> <a class="header-anchor" href="#api-led-matrix-increase-speed-noeeprom" aria-label="Permalink to &quot;`void led_matrix_increase_speed_noeeprom(void)` {#api-led-matrix-increase-speed-noeeprom}&quot;">​</a></h3><p>Increase the effect speed. New state is not written to EEPROM.</p><hr><h3 id="api-led-matrix-decrease-speed" tabindex="-1"><code>void led_matrix_decrease_speed(void)</code> <a class="header-anchor" href="#api-led-matrix-decrease-speed" aria-label="Permalink to &quot;`void led_matrix_decrease_speed(void)` {#api-led-matrix-decrease-speed}&quot;">​</a></h3><p>Decrease the effect speed.</p><hr><h3 id="api-led-matrix-decrease-speed-noeeprom" tabindex="-1"><code>void led_matrix_decrease_speed_noeeprom(void)</code> <a class="header-anchor" href="#api-led-matrix-decrease-speed-noeeprom" aria-label="Permalink to &quot;`void led_matrix_decrease_speed_noeeprom(void)` {#api-led-matrix-decrease-speed-noeeprom}&quot;">​</a></h3><p>Decrease the effect speed. New state is not written to EEPROM.</p><hr><h3 id="api-led-matrix-set-speed" tabindex="-1"><code>void led_matrix_set_speed(uint8_t speed)</code> <a class="header-anchor" href="#api-led-matrix-set-speed" aria-label="Permalink to &quot;`void led_matrix_set_speed(uint8_t speed)` {#api-led-matrix-set-speed}&quot;">​</a></h3><p>Set the effect speed.</p><h4 id="api-led-matrix-set-speed-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-led-matrix-set-speed-arguments" aria-label="Permalink to &quot;Arguments {#api-led-matrix-set-speed-arguments}&quot;">​</a></h4><ul><li><code>uint8_t speed</code><br> The new speed to set, from 0 to 255.</li></ul><hr><h3 id="api-led-matrix-set-speed-noeeprom" tabindex="-1"><code>void led_matrix_set_speed_noeeprom(uint8_t speed)</code> <a class="header-anchor" href="#api-led-matrix-set-speed-noeeprom" aria-label="Permalink to &quot;`void led_matrix_set_speed_noeeprom(uint8_t speed)` {#api-led-matrix-set-speed-noeeprom}&quot;">​</a></h3><p>Set the effect speed. New state is not written to EEPROM.</p><h4 id="api-led-matrix-set-speed-noeeprom-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-led-matrix-set-speed-noeeprom-arguments" aria-label="Permalink to &quot;Arguments {#api-led-matrix-set-speed-noeeprom-arguments}&quot;">​</a></h4><ul><li><code>uint8_t speed</code><br> The new speed to set, from 0 to 255.</li></ul><hr><h3 id="api-led-matrix-get-speed" tabindex="-1"><code>uint8_t led_matrix_get_speed(void)</code> <a class="header-anchor" href="#api-led-matrix-get-speed" aria-label="Permalink to &quot;`uint8_t led_matrix_get_speed(void)` {#api-led-matrix-get-speed}&quot;">​</a></h3><p>Get the current effect speed.</p><h4 id="api-led-matrix-get-speed-return" tabindex="-1">Return Value <a class="header-anchor" href="#api-led-matrix-get-speed-return" aria-label="Permalink to &quot;Return Value {#api-led-matrix-get-speed-return}&quot;">​</a></h4><p>The current effect speed, from 0 to 255.</p><hr><h3 id="api-led-matrix-set-flags" tabindex="-1"><code>void led_matrix_set_flags(led_flags_t flags)</code> <a class="header-anchor" href="#api-led-matrix-set-flags" aria-label="Permalink to &quot;`void led_matrix_set_flags(led_flags_t flags)` {#api-led-matrix-set-flags}&quot;">​</a></h3><p>Set the global effect flags.</p><h4 id="api-led-matrix-set-flags-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-led-matrix-set-flags-arguments" aria-label="Permalink to &quot;Arguments {#api-led-matrix-set-flags-arguments}&quot;">​</a></h4><ul><li><code>led_flags_t flags</code><br> The <a href="#flags">flags</a> value to set.</li></ul><hr><h3 id="api-led-matrix-set-flags-noeeprom" tabindex="-1"><code>void led_matrix_set_flags_noeeprom(led_flags_t flags)</code> <a class="header-anchor" href="#api-led-matrix-set-flags-noeeprom" aria-label="Permalink to &quot;`void led_matrix_set_flags_noeeprom(led_flags_t flags)` {#api-led-matrix-set-flags-noeeprom}&quot;">​</a></h3><p>Set the global effect flags. New state is not written to EEPROM.</p><h4 id="api-led-matrix-set-flags-noeeprom-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-led-matrix-set-flags-noeeprom-arguments" aria-label="Permalink to &quot;Arguments {#api-led-matrix-set-flags-noeeprom-arguments}&quot;">​</a></h4><ul><li><code>led_flags_t flags</code><br> The <a href="#flags">flags</a> value to set.</li></ul><hr><h3 id="api-led-matrix-flags-step" tabindex="-1"><code>void led_matrix_flags_step(void)</code> <a class="header-anchor" href="#api-led-matrix-flags-step" aria-label="Permalink to &quot;`void led_matrix_flags_step(void)` {#api-led-matrix-flags-step}&quot;">​</a></h3><p>Move to the next flag combination.</p><hr><h3 id="api-led-matrix-flags-step-noeeprom" tabindex="-1"><code>void led_matrix_flags_step_noeeprom(void)</code> <a class="header-anchor" href="#api-led-matrix-flags-step-noeeprom" aria-label="Permalink to &quot;`void led_matrix_flags_step_noeeprom(void)` {#api-led-matrix-flags-step-noeeprom}&quot;">​</a></h3><p>Move to the next flag combination. New state is not written to EEPROM.</p><hr><h3 id="api-led-matrix-flags-step-reverse" tabindex="-1"><code>void led_matrix_flags_step_reverse(void)</code> <a class="header-anchor" href="#api-led-matrix-flags-step-reverse" aria-label="Permalink to &quot;`void led_matrix_flags_step_reverse(void)` {#api-led-matrix-flags-step-reverse}&quot;">​</a></h3><p>Move to the previous flag combination.</p><hr><h3 id="api-led-matrix-flags-step-reverse-noeeprom" tabindex="-1"><code>void led_matrix_flags_step_reverse_noeeprom(void)</code> <a class="header-anchor" href="#api-led-matrix-flags-step-reverse-noeeprom" aria-label="Permalink to &quot;`void led_matrix_flags_step_reverse_noeeprom(void)` {#api-led-matrix-flags-step-reverse-noeeprom}&quot;">​</a></h3><p>Move to the previous flag combination. New state is not written to EEPROM.</p><hr><h3 id="api-led-matrix-get-flags" tabindex="-1"><code>uint8_t led_matrix_get_flags(void)</code> <a class="header-anchor" href="#api-led-matrix-get-flags" aria-label="Permalink to &quot;`uint8_t led_matrix_get_flags(void)` {#api-led-matrix-get-flags}&quot;">​</a></h3><p>Get the current global effect flags.</p><h4 id="api-led-matrix-get-flags-return" tabindex="-1">Return Value <a class="header-anchor" href="#api-led-matrix-get-flags-return" aria-label="Permalink to &quot;Return Value {#api-led-matrix-get-flags-return}&quot;">​</a></h4><p>The current effect <a href="#flags">flags</a>.</p><hr><h3 id="api-led-matrix-reload-from-eeprom" tabindex="-1"><code>void led_matrix_reload_from_eeprom(void)</code> <a class="header-anchor" href="#api-led-matrix-reload-from-eeprom" aria-label="Permalink to &quot;`void led_matrix_reload_from_eeprom(void)` {#api-led-matrix-reload-from-eeprom}&quot;">​</a></h3><p>Reload the effect configuration (enabled, mode and brightness) from EEPROM.</p><hr><h3 id="api-led-matrix-get-suspend-state" tabindex="-1"><code>bool led_matrix_get_suspend_state(void)</code> <a class="header-anchor" href="#api-led-matrix-get-suspend-state" aria-label="Permalink to &quot;`bool led_matrix_get_suspend_state(void)` {#api-led-matrix-get-suspend-state}&quot;">​</a></h3><p>Get the current suspend state of LED Matrix.</p><h4 id="api-led-matrix-get-suspend-state-return" tabindex="-1">Return Value <a class="header-anchor" href="#api-led-matrix-get-suspend-state-return" aria-label="Permalink to &quot;Return Value {#api-led-matrix-get-suspend-state-return}&quot;">​</a></h4><p><code>true</code> if LED Matrix is currently in the suspended state.</p><hr><h3 id="api-led-matrix-indicators-kb" tabindex="-1"><code>bool led_matrix_indicators_kb(void)</code> <a class="header-anchor" href="#api-led-matrix-indicators-kb" aria-label="Permalink to &quot;`bool led_matrix_indicators_kb(void)` {#api-led-matrix-indicators-kb}&quot;">​</a></h3><p>Keyboard-level callback, invoked after current animation frame is rendered but before it is flushed to the LEDs.</p><h4 id="api-led-matrix-indicators-kb-return" tabindex="-1">Return Value <a class="header-anchor" href="#api-led-matrix-indicators-kb-return" aria-label="Permalink to &quot;Return Value {#api-led-matrix-indicators-kb-return}&quot;">​</a></h4><p>Currently unused.</p><hr><h3 id="api-led-matrix-indicators-user" tabindex="-1"><code>bool led_matrix_indicators_user(void)</code> <a class="header-anchor" href="#api-led-matrix-indicators-user" aria-label="Permalink to &quot;`bool led_matrix_indicators_user(void)` {#api-led-matrix-indicators-user}&quot;">​</a></h3><p>Keymap-level callback, invoked after current animation frame is rendered but before it is flushed to the LEDs.</p><h4 id="api-led-matrix-indicators-user-return" tabindex="-1">Return Value <a class="header-anchor" href="#api-led-matrix-indicators-user-return" aria-label="Permalink to &quot;Return Value {#api-led-matrix-indicators-user-return}&quot;">​</a></h4><p><code>true</code> to continue running the keyboard-level callback.</p><hr><h3 id="api-led-matrix-indicators-advanced-kb" tabindex="-1"><code>bool led_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max)</code> <a class="header-anchor" href="#api-led-matrix-indicators-advanced-kb" aria-label="Permalink to &quot;`bool led_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max)` {#api-led-matrix-indicators-advanced-kb}&quot;">​</a></h3><p>Keyboard-level callback, invoked after current animation frame is rendered but before it is flushed to the LEDs.</p><h3 id="api-led-matrix-indicators-advanced-kb-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-led-matrix-indicators-advanced-kb-arguments" aria-label="Permalink to &quot;Arguments {#api-led-matrix-indicators-advanced-kb-arguments}&quot;">​</a></h3><ul><li><code>uint8_t led_min</code><br> The index of the first LED in this batch.</li><li><code>uint8_t led_max</code><br> The index of the last LED in this batch.</li></ul><h4 id="api-led-matrix-indicators-advanced-kb-return" tabindex="-1">Return Value <a class="header-anchor" href="#api-led-matrix-indicators-advanced-kb-return" aria-label="Permalink to &quot;Return Value {#api-led-matrix-indicators-advanced-kb-return}&quot;">​</a></h4><p>Currently unused.</p><hr><h3 id="api-led-matrix-indicators-advanced-user" tabindex="-1"><code>bool led_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max)</code> <a class="header-anchor" href="#api-led-matrix-indicators-advanced-user" aria-label="Permalink to &quot;`bool led_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max)` {#api-led-matrix-indicators-advanced-user}&quot;">​</a></h3><p>Keymap-level callback, invoked after current animation frame is rendered but before it is flushed to the LEDs.</p><h3 id="api-led-matrix-indicators-advanced-user-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-led-matrix-indicators-advanced-user-arguments" aria-label="Permalink to &quot;Arguments {#api-led-matrix-indicators-advanced-user-arguments}&quot;">​</a></h3><ul><li><code>uint8_t led_min</code><br> The index of the first LED in this batch.</li><li><code>uint8_t led_max</code><br> The index of the last LED in this batch.</li></ul><h4 id="api-led-matrix-indicators-advanced-user-return" tabindex="-1">Return Value <a class="header-anchor" href="#api-led-matrix-indicators-advanced-user-return" aria-label="Permalink to &quot;Return Value {#api-led-matrix-indicators-advanced-user-return}&quot;">​</a></h4><p><code>true</code> to continue running the keyboard-level callback.</p>', 173))
  ]);
}
const led_matrix = /* @__PURE__ */ _export_sfc(_sfc_main, [["render", _sfc_render]]);
export {
  __pageData,
  led_matrix as default
};
