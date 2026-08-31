import { _ as _export_sfc, C as resolveComponent, o as openBlock, c as createElementBlock, al as createStaticVNode, E as createVNode, w as withCtx, j as createBaseVNode, a as createTextVNode } from "./chunks/framework.8zKZLKO7.js";
const __pageData = JSON.parse('{"title":"RGB Matrix Lighting","description":"","frontmatter":{},"headers":[],"relativePath":"features/rgb_matrix.md","filePath":"features/rgb_matrix.md","lastUpdated":null}');
const _sfc_main = { name: "features/rgb_matrix.md" };
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  const _component_PluginTabsTab = resolveComponent("PluginTabsTab");
  const _component_PluginTabs = resolveComponent("PluginTabs");
  return openBlock(), createElementBlock("div", null, [
    _cache[8] || (_cache[8] = createStaticVNode('<h1 id="rgb-matrix-lighting" tabindex="-1">RGB Matrix Lighting <a class="header-anchor" href="#rgb-matrix-lighting" aria-label="Permalink to &quot;RGB Matrix Lighting {#rgb-matrix-lighting}&quot;">​</a></h1><p>This feature allows you to use RGB LED matrices driven by external drivers. It hooks into the RGBLIGHT system so you can use the same keycodes as RGBLIGHT to control it.</p><p>If you want to use single color LED&#39;s you should use the <a href="./led_matrix">LED Matrix Subsystem</a> instead.</p><h2 id="driver-configuration" tabindex="-1">Driver Configuration <a class="header-anchor" href="#driver-configuration" aria-label="Permalink to &quot;Driver Configuration {#driver-configuration}&quot;">​</a></h2><p>RGB Matrix is an abstraction layer on top of an underlying LED driver API. The list of supported LED drivers is below; see the respective documentation for information on how to configure the driver.</p><table tabindex="0"><thead><tr><th>Driver</th><th>Max LEDs</th></tr></thead><tbody><tr><td><a href="./../drivers/apa102">APA102</a></td><td>?</td></tr><tr><td><a href="./../drivers/aw20216s">AW20216S</a></td><td>72</td></tr><tr><td><a href="./../drivers/is31fl3218">IS31FL3218</a></td><td>6</td></tr><tr><td><a href="./../drivers/is31fl3236">IS31FL3236</a></td><td>12</td></tr><tr><td><a href="./../drivers/is31fl3729">IS31FL3729</a></td><td>45</td></tr><tr><td><a href="./../drivers/is31fl3731">IS31FL3731</a></td><td>48</td></tr><tr><td><a href="./../drivers/is31fl3733">IS31FL3733</a></td><td>64</td></tr><tr><td><a href="./../drivers/is31fl3736">IS31FL3736</a></td><td>32</td></tr><tr><td><a href="./../drivers/is31fl3737">IS31FL3737</a></td><td>48</td></tr><tr><td><a href="./../drivers/is31fl3741">IS31FL3741</a></td><td>117</td></tr><tr><td><a href="./../drivers/is31fl3742a">IS31FL3742A</a></td><td>60</td></tr><tr><td><a href="./../drivers/is31fl3743a">IS31FL3743A</a></td><td>66</td></tr><tr><td><a href="./../drivers/is31fl3745">IS31FL3745</a></td><td>48</td></tr><tr><td><a href="./../drivers/is31fl3746a">IS31FL3746A</a></td><td>24</td></tr><tr><td><a href="./../drivers/snled27351">SNLED27351</a></td><td>64</td></tr><tr><td><a href="./../drivers/ws2812">WS2812</a></td><td>?</td></tr></tbody></table><p>To assign the RGB Matrix driver, add the following to your keyboard config, for example:</p>', 7)),
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
                    createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '    "rgb_matrix"'),
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
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "RGB_MATRIX_DRIVER = is31fl3218")
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
                    createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '    "rgb_matrix"'),
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
              createBaseVNode("code", null, "rgb_matrix.center_point = [ 112, 32 ]"),
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
              createBaseVNode("code", null, "rgb_matrix.center_point = [ 112, 32]"),
              createTextVNode(" in their json (or "),
              createBaseVNode("code", null, "#define RGB_MATRIX_CENTER {112, 32}"),
              createTextVNode(" in their config.h file) with the new center point of the keyboard, or where they want it to be allowing more possibilities for the "),
              createBaseVNode("code", null, "x, y"),
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
    _cache[11] || (_cache[11] = createStaticVNode('<h2 id="flags" tabindex="-1">Flags <a class="header-anchor" href="#flags" aria-label="Permalink to &quot;Flags {#flags}&quot;">​</a></h2><table tabindex="0"><thead><tr><th>Define</th><th>Value</th><th>Description</th></tr></thead><tbody><tr><td><code>HAS_FLAGS(bits, flags)</code></td><td><em>n/a</em></td><td>Evaluates to <code>true</code> if <code>bits</code> has all <code>flags</code> set</td></tr><tr><td><code>HAS_ANY_FLAGS(bits, flags)</code></td><td><em>n/a</em></td><td>Evaluates to <code>true</code> if <code>bits</code> has any <code>flags</code> set</td></tr><tr><td><code>LED_FLAG_NONE</code></td><td><code>0x00</code></td><td>If this LED has no flags</td></tr><tr><td><code>LED_FLAG_ALL</code></td><td><code>0xFF</code></td><td>If this LED has all flags</td></tr><tr><td><code>LED_FLAG_MODIFIER</code></td><td><code>0x01</code></td><td>If the LED is on a modifier key</td></tr><tr><td><code>LED_FLAG_UNDERGLOW</code></td><td><code>0x02</code></td><td>If the LED is for underglow</td></tr><tr><td><code>LED_FLAG_KEYLIGHT</code></td><td><code>0x04</code></td><td>If the LED is for key backlight</td></tr><tr><td><code>LED_FLAG_INDICATOR</code></td><td><code>0x08</code></td><td>If the LED is for keyboard state indication</td></tr></tbody></table><h2 id="keycodes" tabindex="-1">Keycodes <a class="header-anchor" href="#keycodes" aria-label="Permalink to &quot;Keycodes {#keycodes}&quot;">​</a></h2><table tabindex="0"><thead><tr><th>Key</th><th>Aliases</th><th>Description</th></tr></thead><tbody><tr><td><code>QK_RGB_MATRIX_ON</code></td><td><code>RM_ON</code></td><td>Turn on RGB Matrix</td></tr><tr><td><code>QK_RGB_MATRIX_OFF</code></td><td><code>RM_OFF</code></td><td>Turn off RGB Matrix</td></tr><tr><td><code>QK_RGB_MATRIX_TOGGLE</code></td><td><code>RM_TOGG</code></td><td>Toggle RGB Matrix on or off</td></tr><tr><td><code>QK_RGB_MATRIX_MODE_NEXT</code></td><td><code>RM_NEXT</code></td><td>Cycle through animations</td></tr><tr><td><code>QK_RGB_MATRIX_MODE_PREVIOUS</code></td><td><code>RM_PREV</code></td><td>Cycle through animations in reverse</td></tr><tr><td><code>QK_RGB_MATRIX_HUE_UP</code></td><td><code>RM_HUEU</code></td><td>Cycle through hue</td></tr><tr><td><code>QK_RGB_MATRIX_HUE_DOWN</code></td><td><code>RM_HUED</code></td><td>Cycle through hue in reverse</td></tr><tr><td><code>QK_RGB_MATRIX_SATURATION_UP</code></td><td><code>RM_SATU</code></td><td>Increase the saturation</td></tr><tr><td><code>QK_RGB_MATRIX_SATURATION_DOWN</code></td><td><code>RM_SATD</code></td><td>Decrease the saturation</td></tr><tr><td><code>QK_RGB_MATRIX_VALUE_UP</code></td><td><code>RM_VALU</code></td><td>Increase the brightness level</td></tr><tr><td><code>QK_RGB_MATRIX_VALUE_DOWN</code></td><td><code>RM_VALD</code></td><td>Decrease the brightness level</td></tr><tr><td><code>QK_RGB_MATRIX_SPEED_UP</code></td><td><code>RM_SPDU</code></td><td>Increase the animation speed</td></tr><tr><td><code>QK_RGB_MATRIX_SPEED_DOWN</code></td><td><code>RM_SPDD</code></td><td>Decrease the animation speed</td></tr><tr><td><code>QK_RGB_MATRIX_FLAG_NEXT</code></td><td><code>RM_FLGN</code></td><td>Cycle through flags</td></tr><tr><td><code>QK_RGB_MATRIX_FLAG_PREVIOUS</code></td><td><code>RM_FLGP</code></td><td>Cycle through flags in reverse</td></tr></tbody></table><h2 id="rgb-matrix-effects" tabindex="-1">RGB Matrix Effects <a class="header-anchor" href="#rgb-matrix-effects" aria-label="Permalink to &quot;RGB Matrix Effects {#rgb-matrix-effects}&quot;">​</a></h2><p>All effects have been configured to support current configuration values (Hue, Saturation, Value, &amp; Speed) unless otherwise noted below. These are the effects that are currently available:</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">enum</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> rgb_matrix_effects {</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_NONE </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">=</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> 0</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">,</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_SOLID_COLOR </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">=</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> 1</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">     // Static single hue, no speed support</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_ALPHAS_MODS,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">         // Static dual hue, speed is hue for secondary hue</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_GRADIENT_UP_DOWN,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">    // Static gradient top to bottom, speed controls how much gradient changes</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_GRADIENT_LEFT_RIGHT,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">    // Static gradient left to right, speed controls how much gradient changes</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_BREATHING,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">           // Single hue brightness cycling animation</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_BAND_SAT,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">        // Single hue band fading saturation scrolling left to right</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_BAND_VAL,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">        // Single hue band fading brightness scrolling left to right</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_BAND_PINWHEEL_SAT,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">   // Single hue 3 blade spinning pinwheel fades saturation</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_BAND_PINWHEEL_VAL,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">   // Single hue 3 blade spinning pinwheel fades brightness</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_BAND_SPIRAL_SAT,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">     // Single hue spinning spiral fades saturation</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_BAND_SPIRAL_VAL,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">     // Single hue spinning spiral fades brightness</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_CYCLE_ALL,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">           // Full keyboard solid hue cycling through full gradient</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_CYCLE_LEFT_RIGHT,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">    // Full gradient scrolling left to right</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_CYCLE_UP_DOWN,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">       // Full gradient scrolling top to bottom</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_CYCLE_OUT_IN,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">        // Full gradient scrolling out to in</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_CYCLE_OUT_IN_DUAL,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">   // Full dual gradients scrolling out to in</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_RAINBOW_MOVING_CHEVRON,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">  // Full gradient Chevron shapped scrolling left to right</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_CYCLE_PINWHEEL,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">      // Full gradient spinning pinwheel around center of keyboard</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_CYCLE_SPIRAL,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">        // Full gradient spinning spiral around center of keyboard</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_DUAL_BEACON,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">         // Full gradient spinning around center of keyboard</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_RAINBOW_BEACON,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">      // Full tighter gradient spinning around center of keyboard</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_RAINBOW_PINWHEELS,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">   // Full dual gradients spinning two halves of keyboard</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_FLOWER_BLOOMING,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">     // Full tighter gradient of first half scrolling left to right and second half scrolling right to left</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_RAINDROPS,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">           // Randomly changes a single key&#39;s hue</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_JELLYBEAN_RAINDROPS,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;"> // Randomly changes a single key&#39;s hue and saturation</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_HUE_BREATHING,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">       // Hue shifts up a slight amount at the same time, then shifts back</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_HUE_PENDULUM,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">        // Hue shifts up a slight amount in a wave to the right, then back to the left</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_HUE_WAVE,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">            // Hue shifts up a slight amount and then back down in a wave to the right</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_PIXEL_FRACTAL,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">       // Single hue fractal filled keys pulsing horizontally out to edges</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_PIXEL_FLOW,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">          // Pulsing RGB flow along LED wiring with random hues</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_PIXEL_RAIN,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">          // Randomly light keys with random hues</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_TYPING_HEATMAP,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">      // How hot is your WPM!</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_DIGITAL_RAIN,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">        // That famous computer simulation</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_SOLID_REACTIVE_SIMPLE,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">   // Pulses keys hit to hue &amp; value then fades value out</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_SOLID_REACTIVE,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">      // Static single hue, pulses keys hit to shifted hue then fades to current hue</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_SOLID_REACTIVE_WIDE,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">       // Hue &amp; value pulse near a single key hit then fades value out</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">  // Hue &amp; value pulse near multiple key hits then fades value out</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_SOLID_REACTIVE_CROSS,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">      // Hue &amp; value pulse the same column and row of a single key hit then fades value out</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_SOLID_REACTIVE_MULTICROSS,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;"> // Hue &amp; value pulse the same column and row of multiple key hits then fades value out</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_SOLID_REACTIVE_NEXUS,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">      // Hue &amp; value pulse away on the same column and row of a single key hit then fades value out</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;"> // Hue &amp; value pulse away on the same column and row of multiple key hits then fades value out</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_SPLASH,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">              // Full gradient &amp; value pulse away from a single key hit then fades value out</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_MULTISPLASH,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">         // Full gradient &amp; value pulse away from multiple key hits then fades value out</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_SOLID_SPLASH,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">        // Hue &amp; value pulse away from a single key hit then fades value out</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_SOLID_MULTISPLASH,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">   // Hue &amp; value pulse away from multiple key hits then fades value out</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_STARLIGHT,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">           // LEDs turn on and off at random at varying brightness, maintaining user set color</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_STARLIGHT_SMOOTH,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">    // LEDs slowly increase and decrease in brightness randomly</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_STARLIGHT_DUAL_HUE,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">  // LEDs turn on and off at random at varying brightness, modifies user set hue by +- 30</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_STARLIGHT_DUAL_SAT,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">  // LEDs turn on and off at random at varying brightness, modifies user set saturation by +- 30</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_RIVERFLOW,</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">           // Modification to breathing animation, offset&#39;s animation depending on key location to simulate a river flowing</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    RGB_MATRIX_EFFECT_MAX</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">};</span></span></code></pre></div>', 7)),
    createVNode(_component_PluginTabs, null, {
      default: withCtx(() => [
        createVNode(_component_PluginTabsTab, { label: "`JSON`" }, {
          default: withCtx(() => [..._cache[4] || (_cache[4] = [
            createBaseVNode("p", null, [
              createTextVNode("You can enable a single effect by setting it true in the "),
              createBaseVNode("code", null, "rgb_matrix.animations"),
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
                    createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '    "rgb_matrix"'),
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
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "gradient_up_down"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "gradient_left_right"'),
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
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "band_sat"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "band_val"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "band_pinwheel_sat"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "band_pinwheel_val"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "band_spiral_sat"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "band_spiral_val"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "cycle_all"'),
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
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "rainbow_moving_chevron"'),
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
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "cycle_out_in_dual"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "cycle_pinwheel"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "cycle_spiral"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "dual_beacon"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "rainbow_beacon"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "rainbow_pinwheels"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "raindrops"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "jellybean_raindrops"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "hue_breathing"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "hue_pendulum"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "hue_wave"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "pixel_rain"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "pixel_flow"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "pixel_fractal"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
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
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "digital_rain"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
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
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "multispash"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "solid_splash"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "solid_multisplash"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "starlight"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "starlight_smooth"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "starlight_dual_hue"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "starlight_dual_sat"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "riverflow"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, "            ")
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
                    createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '    "rgb_matrix"'),
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
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "digital_rain"'),
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
                    createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '    "rgb_matrix"'),
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
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "solid_splash"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ",")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "solid_multisplash"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "true")
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
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_ALPHAS_MODS")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_ALPHAS_MODS")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_GRADIENT_UP_DOWN")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_GRADIENT_LEFT_RIGHT")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_BREATHING")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_BREATHING")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_BAND_SAT")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_BAND_SAT")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_BAND_VAL")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_BAND_VAL")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_BAND_PINWHEEL_SAT")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_BAND_PINWHEEL_VAL")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_BAND_SPIRAL_SAT")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_BAND_SPIRAL_VAL")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_CYCLE_ALL")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_CYCLE_ALL")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_CYCLE_LEFT_RIGHT")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_CYCLE_UP_DOWN")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_RAINBOW_MOVING_CHEVRON")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_CYCLE_OUT_IN")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_CYCLE_OUT_IN_DUAL")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_CYCLE_PINWHEEL")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_CYCLE_SPIRAL")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_DUAL_BEACON")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_DUAL_BEACON")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_RAINBOW_BEACON")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_RAINBOW_BEACON")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_RAINBOW_PINWHEELS")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_FLOWER_BLOOMING")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_FLOWER_BLOOMING")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_RAINDROPS")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_RAINDROPS")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_JELLYBEAN_RAINDROPS")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_HUE_BREATHING")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_HUE_BREATHING")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_HUE_PENDULUM")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_HUE_PENDULUM")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_HUE_WAVE")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_HUE_WAVE ")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_PIXEL_FRACTAL")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_PIXEL_FRACTAL")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_PIXEL_FLOW")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_PIXEL_FLOW")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_PIXEL_RAIN")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_PIXEL_RAIN")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_STARLIGHT")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_STARLIGHT")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_STARLIGHT_SMOOTH")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_STARLIGHT_SMOOTH")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_STARLIGHT_DUAL_HUE")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_STARLIGHT_DUAL_HUE")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_STARLIGHT_DUAL_SAT")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_STARLIGHT_DUAL_SAT")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_RIVERFLOW")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_RIVERFLOW")
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
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_TYPING_HEATMAP")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_TYPING_HEATMAP")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_DIGITAL_RAIN")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_DIGITAL_RAIN")
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
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_SOLID_REACTIVE_SIMPLE")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_SOLID_REACTIVE")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_SOLID_REACTIVE")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_SOLID_REACTIVE_WIDE")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_SOLID_REACTIVE_CROSS")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_SOLID_REACTIVE_MULTICROSS")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_SOLID_REACTIVE_NEXUS")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_SPLASH")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_SPLASH")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_MULTISPLASH")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_MULTISPLASH")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_SOLID_SPLASH")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_SOLID_SPLASH")
                  ])
                ]),
                createBaseVNode("tr", null, [
                  createBaseVNode("td", null, [
                    createBaseVNode("code", null, "#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH")
                  ]),
                  createBaseVNode("td", null, [
                    createTextVNode("Enables "),
                    createBaseVNode("code", null, "RGB_MATRIX_SOLID_MULTISPLASH")
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
    _cache[12] || (_cache[12] = createStaticVNode('<h3 id="rgb-matrix-effect-typing-heatmap" tabindex="-1">RGB Matrix Effect Typing Heatmap <a class="header-anchor" href="#rgb-matrix-effect-typing-heatmap" aria-label="Permalink to &quot;RGB Matrix Effect Typing Heatmap {#rgb-matrix-effect-typing-heatmap}&quot;">​</a></h3><p>This effect will color the RGB matrix according to a heatmap of recently pressed keys. Whenever a key is pressed its &quot;temperature&quot; increases as well as that of its neighboring keys. The temperature of each key is then decreased automatically every 25 milliseconds by default.</p><p>In order to change the delay of temperature decrease define <code>RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS</code>:</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#define</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> 50</span></span></code></pre></div><p>As heatmap uses the physical position of the leds set in the g_led_config, you may need to tweak the following options to get the best effect for your keyboard. Note the size of this grid is <code>224x64</code>.</p><p>Limit the distance the effect spreads to surrounding keys.</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#define</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> RGB_MATRIX_TYPING_HEATMAP_SPREAD</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> 40</span></span></code></pre></div><p>Limit how hot surrounding keys get from each press.</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#define</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> RGB_MATRIX_TYPING_HEATMAP_AREA_LIMIT</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> 16</span></span></code></pre></div><p>Remove the spread effect entirely.</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#define</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> RGB_MATRIX_TYPING_HEATMAP_SLIM</span></span></code></pre></div><p>It&#39;s also possible to adjust the tempo of <em>heating up</em>. It&#39;s defined as the number of shades that are increased on the <a href="https://en.wikipedia.org/wiki/HSL_and_HSV" target="_blank" rel="noreferrer">HSV scale</a>. Decreasing this value increases the number of keystrokes needed to fully heat up the key.</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#define</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> RGB_MATRIX_TYPING_HEATMAP_INCREASE_STEP</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> 32</span></span></code></pre></div><h3 id="rgb-matrix-effect-solid-reactive" tabindex="-1">RGB Matrix Effect Solid Reactive <a class="header-anchor" href="#rgb-matrix-effect-solid-reactive" aria-label="Permalink to &quot;RGB Matrix Effect Solid Reactive {#rgb-matrix-effect-solid-reactive}&quot;">​</a></h3><p>Solid reactive effects will pulse RGB light on key presses with user configurable hues. To enable gradient mode that will automatically change reactive color, add the following define:</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#define</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> RGB_MATRIX_SOLID_REACTIVE_GRADIENT_MODE</span></span></code></pre></div><p>Gradient mode will loop through the color wheel hues over time and its duration can be controlled with the effect speed keycodes (<code>RM_SPDU</code>/<code>RM_SPDD</code>).</p><h2 id="custom-rgb-matrix-effects" tabindex="-1">Custom RGB Matrix Effects <a class="header-anchor" href="#custom-rgb-matrix-effects" aria-label="Permalink to &quot;Custom RGB Matrix Effects {#custom-rgb-matrix-effects}&quot;">​</a></h2><p>By setting <code>RGB_MATRIX_CUSTOM_USER = yes</code> in <code>rules.mk</code>, new effects can be defined directly from your keymap or userspace, without having to edit any QMK core files. To declare new effects, create a <code>rgb_matrix_user.inc</code> file in the user keymap directory or userspace folder.</p><div class="tip custom-block"><p class="custom-block-title">TIP</p><p>Hardware maintainers who want to limit custom effects to a specific keyboard can create a <code>rgb_matrix_kb.inc</code> file in the root of the keyboard directory, and add <code>RGB_MATRIX_CUSTOM_KB = yes</code> to the keyboard level <code>rules.mk</code>.</p></div><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">// !!! DO NOT ADD #pragma once !!!</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;"> //</span></span>\n<span class="line"></span>\n<span class="line"><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">// Step 1.</span></span>\n<span class="line"><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">// Declare custom effects using the RGB_MATRIX_EFFECT macro</span></span>\n<span class="line"><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">// (note the lack of semicolon after the macro!)</span></span>\n<span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">RGB_MATRIX_EFFECT</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(my_cool_effect)</span></span>\n<span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">RGB_MATRIX_EFFECT</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(my_cool_effect2)</span></span>\n<span class="line"></span>\n<span class="line"><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">// Step 2.</span></span>\n<span class="line"><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#ifdef</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> RGB_MATRIX_CUSTOM_EFFECT_IMPLS</span></span>\n<span class="line"></span>\n<span class="line"><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">// e.g: A simple effect, self-contained within a single method</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">static</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;"> bool</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> my_cool_effect</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">effect_params_t</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">*</span><span style="--shiki-light:#E36209;--shiki-dark:#FFAB70;"> params</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) {</span></span>\n<span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">  RGB_MATRIX_USE_LIMITS</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(led_min, led_max);</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">  for</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> (</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">uint8_t</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> i </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">=</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> led_min; i </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">&lt;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> led_max; i</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">++</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) {</span></span>\n<span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">    rgb_matrix_set_color</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(i, </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">0x</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">ff</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">0x</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">ff</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">0x</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">00</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">);</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">  }</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">  return</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> rgb_matrix_check_finished_leds</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(led_max);</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">}</span></span>\n<span class="line"></span>\n<span class="line"><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">// e.g: A more complex effect, relying on external methods and state, with</span></span>\n<span class="line"><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">// dedicated init and run methods</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">static</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;"> uint8_t</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> some_global_state;</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">static</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;"> void</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> my_cool_effect2_complex_init</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">effect_params_t</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">*</span><span style="--shiki-light:#E36209;--shiki-dark:#FFAB70;"> params</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) {</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">  some_global_state </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">=</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> 1</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">;</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">}</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">static</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;"> bool</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> my_cool_effect2_complex_run</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">effect_params_t</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">*</span><span style="--shiki-light:#E36209;--shiki-dark:#FFAB70;"> params</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) {</span></span>\n<span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">  RGB_MATRIX_USE_LIMITS</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(led_min, led_max);</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">  for</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> (</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">uint8_t</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> i </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">=</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> led_min; i </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">&lt;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> led_max; i</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">++</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) {</span></span>\n<span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">    rgb_matrix_set_color</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(i, </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">0x</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">ff</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, some_global_state</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">++</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">0x</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">ff</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">);</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">  }</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">  return</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> rgb_matrix_check_finished_leds</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(led_max);</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">}</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">static</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;"> bool</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> my_cool_effect2</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">effect_params_t</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">*</span><span style="--shiki-light:#E36209;--shiki-dark:#FFAB70;"> params</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) {</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">  if</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> (params-&gt;init) </span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">my_cool_effect2_complex_init</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(params);</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">  return</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> my_cool_effect2_complex_run</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(params);</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">}</span></span>\n<span class="line"></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#endif</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;"> // RGB_MATRIX_CUSTOM_EFFECT_IMPLS</span></span></code></pre></div><p>To switch to your custom effect programmatically, simply call <code>rgb_matrix_mode()</code> and prepend <code>RGB_MATRIX_CUSTOM_</code> to the effect name you specified in <code>RGB_MATRIX_EFFECT()</code>. For example, an effect declared as <code>RGB_MATRIX_EFFECT(my_cool_effect)</code> would be referenced with:</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">rgb_matrix_mode</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(RGB_MATRIX_CUSTOM_my_cool_effect);</span></span></code></pre></div><p>For inspiration and examples, check out the built-in effects under <code>quantum/rgb_matrix/animations/</code>.</p><h2 id="colors" tabindex="-1">Colors <a class="header-anchor" href="#colors" aria-label="Permalink to &quot;Colors {#colors}&quot;">​</a></h2><p>These are shorthands to popular colors. The <code>RGB</code> ones can be passed to the <code>setrgb</code> functions, while the <code>HSV</code> ones to the <code>sethsv</code> functions.</p><table tabindex="0"><thead><tr><th>RGB</th><th>HSV</th></tr></thead><tbody><tr><td><code>RGB_AZURE</code></td><td><code>HSV_AZURE</code></td></tr><tr><td><code>RGB_BLACK</code>/<code>RGB_OFF</code></td><td><code>HSV_BLACK</code>/<code>HSV_OFF</code></td></tr><tr><td><code>RGB_BLUE</code></td><td><code>HSV_BLUE</code></td></tr><tr><td><code>RGB_CHARTREUSE</code></td><td><code>HSV_CHARTREUSE</code></td></tr><tr><td><code>RGB_CORAL</code></td><td><code>HSV_CORAL</code></td></tr><tr><td><code>RGB_CYAN</code></td><td><code>HSV_CYAN</code></td></tr><tr><td><code>RGB_GOLD</code></td><td><code>HSV_GOLD</code></td></tr><tr><td><code>RGB_GOLDENROD</code></td><td><code>HSV_GOLDENROD</code></td></tr><tr><td><code>RGB_GREEN</code></td><td><code>HSV_GREEN</code></td></tr><tr><td><code>RGB_MAGENTA</code></td><td><code>HSV_MAGENTA</code></td></tr><tr><td><code>RGB_ORANGE</code></td><td><code>HSV_ORANGE</code></td></tr><tr><td><code>RGB_PINK</code></td><td><code>HSV_PINK</code></td></tr><tr><td><code>RGB_PURPLE</code></td><td><code>HSV_PURPLE</code></td></tr><tr><td><code>RGB_RED</code></td><td><code>HSV_RED</code></td></tr><tr><td><code>RGB_SPRINGGREEN</code></td><td><code>HSV_SPRINGGREEN</code></td></tr><tr><td><code>RGB_TEAL</code></td><td><code>HSV_TEAL</code></td></tr><tr><td><code>RGB_TURQUOISE</code></td><td><code>HSV_TURQUOISE</code></td></tr><tr><td><code>RGB_WHITE</code></td><td><code>HSV_WHITE</code></td></tr><tr><td><code>RGB_YELLOW</code></td><td><code>HSV_YELLOW</code></td></tr></tbody></table><p>These are defined in <a href="https://github.com/qmk/qmk_firmware/blob/master/quantum/color.h" target="_blank" rel="noreferrer"><code>color.h</code></a>. Feel free to add to this list!</p><h2 id="naming" tabindex="-1">Naming <a class="header-anchor" href="#naming" aria-label="Permalink to &quot;Naming&quot;">​</a></h2><p>If you wish to be able to use the name of an effect in your code -- say for a display indicator -- then you can enable the function <code>rgb_matrix_get_mode_name</code> in the following manner:</p><p>In your keymap&#39;s <code>config.h</code>:</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#define</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> RGB_MATRIX_MODE_NAME_ENABLE</span></span></code></pre></div><p>In your <code>keymap.c</code></p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">const</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;"> char*</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> effect_name </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">=</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> rgb_matrix_get_mode_name</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">rgb_matrix_get_mode</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">());</span></span>\n<span class="line"><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;">// do something with `effect_name`, like `oled_write_ln(effect_name, false);`</span></span></code></pre></div><div class="info custom-block"><p class="custom-block-title">INFO</p><p><code>rgb_matrix_get_mode_name()</code> is not enabled by default as it increases the amount of flash memory used by the firmware based on the number of effects enabled.</p></div><h2 id="additional-configh-options" tabindex="-1">Additional Configuration Options <a class="header-anchor" href="#additional-configh-options" aria-label="Permalink to &quot;Additional Configuration Options {#additional-configh-options}&quot;">​</a></h2><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">#define</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> RGB_MATRIX_MODE_NAME_ENABLE</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;"> // enables rgb_matrix_get_mode_name()</span></span></code></pre></div>', 37)),
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
                    createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '    "rgb_matrix"'),
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
                    createBaseVNode("span", { style: { "--shiki-light": "#032F62", "--shiki-dark": "#9ECBFF" } }, '"cycle_left_right"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "            // Sets the default hue value, if none has been set")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "hue"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "0"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "            // Sets the default saturation value, if none has been set")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '            "sat"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "255"),
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
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "            // LED_FLAG_ALL, LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER, LED_FLAG_UNDERGLOW, LED_FLAG_NONE")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "            255"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "5"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "2"),
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
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "        // number of milliseconds to wait until rgb automatically turns off")
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
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "        // The value by which to increment the hue per adjustment action")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '        "hue_steps"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "8"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ", ")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "        // The value by which to increment the saturation per adjustment action")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, '        "sat_steps"'),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, ": "),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, "16"),
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
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " RGB_MATRIX_KEYRELEASES"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // reactive effects respond to keyreleases (instead of keypresses)")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " RGB_MATRIX_TIMEOUT"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 0"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // number of milliseconds to wait until rgb automatically turns off")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " RGB_MATRIX_SLEEP"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // turn off effects when suspended")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " RGB_MATRIX_LED_PROCESS_LIMIT"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " (RGB_MATRIX_LED_COUNT "),
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
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " RGB_MATRIX_LED_FLUSH_LIMIT"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 16"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " RGB_MATRIX_MAXIMUM_BRIGHTNESS"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 200"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " RGB_MATRIX_DEFAULT_ON"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " true"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // Sets the default enabled state, if none has been set")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " RGB_MATRIX_DEFAULT_MODE"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " RGB_MATRIX_CYCLE_LEFT_RIGHT"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // Sets the default mode, if none has been set")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " RGB_MATRIX_DEFAULT_HUE"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 0"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // Sets the default hue value, if none has been set")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " RGB_MATRIX_DEFAULT_SAT"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 255"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // Sets the default saturation value, if none has been set")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " RGB_MATRIX_DEFAULT_VAL"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " RGB_MATRIX_MAXIMUM_BRIGHTNESS"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // Sets the default brightness value, if none has been set")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " RGB_MATRIX_DEFAULT_SPD"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 127"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // Sets the default animation speed, if none has been set")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " RGB_MATRIX_HUE_STEP"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 8"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // The value by which to increment the hue per adjustment action")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " RGB_MATRIX_SAT_STEP"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 16"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // The value by which to increment the saturation per adjustment action")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " RGB_MATRIX_VAL_STEP"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 16"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // The value by which to increment the brightness per adjustment action")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " RGB_MATRIX_SPD_STEP"),
                    createBaseVNode("span", { style: { "--shiki-light": "#005CC5", "--shiki-dark": "#79B8FF" } }, " 16"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // The value by which to increment the animation speed per adjustment action")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " RGB_MATRIX_DEFAULT_FLAGS"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " LED_FLAG_ALL"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // Sets the default LED flags, if none has been set")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " RGB_MATRIX_SPLIT"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " { X, Y }"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, " // (Optional) For split keyboards, the number of LEDs connected on each half. X = left, Y = Right.")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "                                  // If reactive effects are enabled, you also will want to enable SPLIT_TRANSPORT_MIRROR")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " RGB_TRIGGER_ON_KEYDOWN"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6A737D", "--shiki-dark": "#6A737D" } }, "      // Triggers RGB keypress events on key down. This makes RGB control feel more responsive. This may cause RGB to not function properly on some boards")
                  ]),
                  createTextVNode("\n"),
                  createBaseVNode("span", { class: "line" }, [
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "#define"),
                    createBaseVNode("span", { style: { "--shiki-light": "#6F42C1", "--shiki-dark": "#B392F0" } }, " RGB_MATRIX_FLAG_STEPS"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " { LED_FLAG_ALL, LED_FLAG_KEYLIGHT "),
                    createBaseVNode("span", { style: { "--shiki-light": "#D73A49", "--shiki-dark": "#F97583" } }, "|"),
                    createBaseVNode("span", { style: { "--shiki-light": "#24292E", "--shiki-dark": "#E1E4E8" } }, " LED_FLAG_MODIFIER, LED_FLAG_UNDERGLOW, LED_FLAG_NONE }"),
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
    _cache[13] || (_cache[13] = createStaticVNode('<h2 id="eeprom-storage" tabindex="-1">EEPROM storage <a class="header-anchor" href="#eeprom-storage" aria-label="Permalink to &quot;EEPROM storage {#eeprom-storage}&quot;">​</a></h2><p>The EEPROM for it is currently shared with the LED Matrix system (it&#39;s generally assumed only one feature would be used at a time).</p><h2 id="callbacks" tabindex="-1">Callbacks <a class="header-anchor" href="#callbacks" aria-label="Permalink to &quot;Callbacks {#callbacks}&quot;">​</a></h2><h3 id="indicators" tabindex="-1">Indicators <a class="header-anchor" href="#indicators" aria-label="Permalink to &quot;Indicators {#indicators}&quot;">​</a></h3><p>If you want to set custom indicators, such as an LED for Caps Lock, or layer indication, then you can use the <code>rgb_matrix_indicators_kb</code> function on the keyboard level source file, or <code>rgb_matrix_indicators_user</code> function in the user <code>keymap.c</code>.</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">bool</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> rgb_matrix_indicators_kb</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">void</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) {</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">    if</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> (</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">!</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">rgb_matrix_indicators_user</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">()) {</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">        return</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> false</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">;</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    }</span></span>\n<span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">    rgb_matrix_set_color</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(index, red, green, blue);</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">    return</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> true</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">;</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">}</span></span></code></pre></div><p>In addition, there are the advanced indicator functions. These are aimed at those with heavily customized displays, where rendering every LED per cycle is expensive. Such as some of the &quot;drashna&quot; layouts. This includes a special macro to help make this easier to use: <code>RGB_MATRIX_INDICATOR_SET_COLOR(i, r, g, b)</code>.</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">bool</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> rgb_matrix_indicators_advanced_user</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">uint8_t</span><span style="--shiki-light:#E36209;--shiki-dark:#FFAB70;"> led_min</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">uint8_t</span><span style="--shiki-light:#E36209;--shiki-dark:#FFAB70;"> led_max</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) {</span></span>\n<span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">    RGB_MATRIX_INDICATOR_SET_COLOR</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(index, red, green, blue);</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">    return</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> false</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">;</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">}</span></span></code></pre></div><h3 id="indicator-examples" tabindex="-1">Indicator Examples <a class="header-anchor" href="#indicator-examples" aria-label="Permalink to &quot;Indicator Examples {#indicator-examples}&quot;">​</a></h3><p>Caps Lock indicator on alphanumeric flagged keys:</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">bool</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> rgb_matrix_indicators_advanced_user</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">uint8_t</span><span style="--shiki-light:#E36209;--shiki-dark:#FFAB70;"> led_min</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">uint8_t</span><span style="--shiki-light:#E36209;--shiki-dark:#FFAB70;"> led_max</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) {</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">    if</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> (</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">host_keyboard_led_state</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">().caps_lock) {</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">        for</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> (</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">uint8_t</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> i </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">=</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> led_min; i </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">&lt;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> led_max; i</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">++</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) {</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">            if</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> (g_led_config.flags[i] </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">&amp;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> LED_FLAG_KEYLIGHT) {</span></span>\n<span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">                rgb_matrix_set_color</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(i, RGB_RED);</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">            }</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">        }</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    }</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">    return</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> false</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">;</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">}</span></span></code></pre></div><p>Layer indicator on all keys:</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">bool</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> rgb_matrix_indicators_advanced_user</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">uint8_t</span><span style="--shiki-light:#E36209;--shiki-dark:#FFAB70;"> led_min</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">uint8_t</span><span style="--shiki-light:#E36209;--shiki-dark:#FFAB70;"> led_max</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) {</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">    for</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> (</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">uint8_t</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> i </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">=</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> led_min; i </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">&lt;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> led_max; i</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">++</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) {</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">        switch</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">get_highest_layer</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(layer_state</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">|</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">default_layer_state)) {</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">            case</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> 2</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">:</span></span>\n<span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">                rgb_matrix_set_color</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(i, RGB_BLUE);</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">                break</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">;</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">            case</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> 1</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">:</span></span>\n<span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">                rgb_matrix_set_color</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(i, RGB_YELLOW);</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">                break</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">;</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">            default</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">:</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">                break</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">;</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">        }</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    }</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">    return</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> false</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">;</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">}</span></span></code></pre></div><p>Layer indicator only on keys with configured keycodes:</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">bool</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> rgb_matrix_indicators_advanced_user</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">uint8_t</span><span style="--shiki-light:#E36209;--shiki-dark:#FFAB70;"> led_min</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">uint8_t</span><span style="--shiki-light:#E36209;--shiki-dark:#FFAB70;"> led_max</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) {</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">    if</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> (</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">get_highest_layer</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(layer_state) </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">&gt;</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> 0</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) {</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">        uint8_t</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> layer </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">=</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> get_highest_layer</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(layer_state);</span></span>\n<span class="line"></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">        for</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> (</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">uint8_t</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> row </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">=</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> 0</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">; row </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">&lt;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> MATRIX_ROWS; </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">++</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">row) {</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">            for</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> (</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">uint8_t</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> col </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">=</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> 0</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">; col </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">&lt;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> MATRIX_COLS; </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">++</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">col) {</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">                uint8_t</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> index </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">=</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> g_led_config.matrix_co[row][col];</span></span>\n<span class="line"></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">                if</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> (index </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">&gt;=</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> led_min </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">&amp;&amp;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> index </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">&lt;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> led_max </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">&amp;&amp;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> index </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">!=</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> NO_LED </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">&amp;&amp;</span></span>\n<span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">                keymap_key_to_keycode</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(layer, (</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">keypos_t</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">){col,row}) </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">&gt;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> KC_TRNS) {</span></span>\n<span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">                    rgb_matrix_set_color</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(index, RGB_GREEN);</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">                }</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">            }</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">        }</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    }</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">    return</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> false</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">;</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">}</span></span></code></pre></div><div class="tip custom-block"><p class="custom-block-title">TIP</p><p>Split keyboards will require layer state data syncing with <code>#define SPLIT_LAYER_STATE_ENABLE</code>. See <a href="./split_keyboard#data-sync-options">Data Sync Options</a> for more details.</p></div><h4 id="indicator-examples-2" tabindex="-1">Examples <a class="header-anchor" href="#indicator-examples-2" aria-label="Permalink to &quot;Examples {#indicator-examples-2}&quot;">​</a></h4><p>This example sets the modifiers to be a specific color based on the layer state. You can use a switch case here, instead, if you would like. This uses HSV and then converts to RGB, because this allows the brightness to be limited (important when using the WS2812 driver).</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">bool</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> rgb_matrix_indicators_advanced_user</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">uint8_t</span><span style="--shiki-light:#E36209;--shiki-dark:#FFAB70;"> led_min</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">uint8_t</span><span style="--shiki-light:#E36209;--shiki-dark:#FFAB70;"> led_max</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) {</span></span>\n<span class="line"><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">    hsv_t</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> hsv </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">=</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> {</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">0</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">255</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">255</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">};</span></span>\n<span class="line"></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">    if</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> (</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">get_highest_layer</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(layer_state</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">|</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">default_layer_state) </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">==</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> 2</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) {</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">        hsv </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">=</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> (</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">hsv_t</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">){</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">130</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">255</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">255</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">};</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    } </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">else</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> {</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">        hsv </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">=</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> (</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">hsv_t</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">){</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">30</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">255</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">255</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">};</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    }</span></span>\n<span class="line"></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">    if</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> (hsv.v </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">&gt;</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> rgb_matrix_get_val</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">()) {</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">        hsv.v </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">=</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> rgb_matrix_get_val</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">();</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    }</span></span>\n<span class="line"><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">    rgb_t</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> rgb </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">=</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> hsv_to_rgb</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(hsv);</span></span>\n<span class="line"></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">    for</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> (</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">uint8_t</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> i </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">=</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> led_min; i </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">&lt;</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> led_max; i</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">++</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) {</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">        if</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> (</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">HAS_FLAGS</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(g_led_config.flags[i], </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">0x</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">01</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">)) {</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;"> // 0x01 == LED_FLAG_MODIFIER</span></span>\n<span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">            rgb_matrix_set_color</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(i, rgb.r, rgb.g, rgb.b);</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">        }</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    }</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">    return</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> false</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">;</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">}</span></span></code></pre></div><p>If you want to indicate a Host LED status (caps lock, num lock, etc), you can use something like this to light up the caps lock key:</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">bool</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> rgb_matrix_indicators_advanced_user</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">uint8_t</span><span style="--shiki-light:#E36209;--shiki-dark:#FFAB70;"> led_min</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">uint8_t</span><span style="--shiki-light:#E36209;--shiki-dark:#FFAB70;"> led_max</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) {</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">    if</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> (</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">host_keyboard_led_state</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">().caps_lock) {</span></span>\n<span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">        RGB_MATRIX_INDICATOR_SET_COLOR</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">5</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">255</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">255</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">255</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">);</span><span style="--shiki-light:#6A737D;--shiki-dark:#6A737D;"> // assuming caps lock is at led #5</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    } </span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">else</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;"> {</span></span>\n<span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">        RGB_MATRIX_INDICATOR_SET_COLOR</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">5</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">0</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">0</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">, </span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;">0</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">);</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">    }</span></span>\n<span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">    return</span><span style="--shiki-light:#005CC5;--shiki-dark:#79B8FF;"> false</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">;</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">}</span></span></code></pre></div><div class="tip custom-block"><p class="custom-block-title">TIP</p><p>RGB indicators on split keyboards will require state information synced to the slave half (e.g. <code>#define SPLIT_LAYER_STATE_ENABLE</code>). See <a href="./split_keyboard#data-sync-options">data sync options</a> for more details.</p></div><h4 id="indicators-without-rgb-matrix-effect" tabindex="-1">Indicators without RGB Matrix Effect <a class="header-anchor" href="#indicators-without-rgb-matrix-effect" aria-label="Permalink to &quot;Indicators without RGB Matrix Effect&quot;">​</a></h4><p>If you want to just use RGB indicators without RGB matrix effect, it is not possible to disable the latter because toggling RGB off will disable everything. You can workaround it with solid effect and colors off using this init function:</p><div class="language-c vp-adaptive-theme"><button title="Copy Code" class="copy"></button><span class="lang">c</span><pre class="shiki shiki-themes github-light github-dark vp-code" tabindex="0"><code><span class="line"><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">void</span><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;"> keyboard_post_init_user</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(</span><span style="--shiki-light:#D73A49;--shiki-dark:#F97583;">void</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">) {</span></span>\n<span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">    rgb_matrix_mode_noeeprom</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(RGB_MATRIX_SOLID_COLOR);</span></span>\n<span class="line"><span style="--shiki-light:#6F42C1;--shiki-dark:#B392F0;">    rgb_matrix_sethsv_noeeprom</span><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">(HSV_OFF);</span></span>\n<span class="line"><span style="--shiki-light:#24292E;--shiki-dark:#E1E4E8;">}</span></span></code></pre></div><h2 id="api" tabindex="-1">API <a class="header-anchor" href="#api" aria-label="Permalink to &quot;API {#api}&quot;">​</a></h2><h3 id="api-rgb-matrix-toggle" tabindex="-1"><code>void rgb_matrix_toggle(void)</code> <a class="header-anchor" href="#api-rgb-matrix-toggle" aria-label="Permalink to &quot;`void rgb_matrix_toggle(void)` {#api-rgb-matrix-toggle}&quot;">​</a></h3><p>Toggle RGB Matrix on or off.</p><hr><h3 id="api-rgb-matrix-toggle-noeeprom" tabindex="-1"><code>void rgb_matrix_toggle_noeeprom(void)</code> <a class="header-anchor" href="#api-rgb-matrix-toggle-noeeprom" aria-label="Permalink to &quot;`void rgb_matrix_toggle_noeeprom(void)` {#api-rgb-matrix-toggle-noeeprom}&quot;">​</a></h3><p>Toggle RGB Matrix on or off. New state is not written to EEPROM.</p><hr><h3 id="api-rgb-matrix-enable" tabindex="-1"><code>void rgb_matrix_enable(void)</code> <a class="header-anchor" href="#api-rgb-matrix-enable" aria-label="Permalink to &quot;`void rgb_matrix_enable(void)` {#api-rgb-matrix-enable}&quot;">​</a></h3><p>Turn RGB Matrix on.</p><hr><h3 id="api-rgb-matrix-enable-noeeprom" tabindex="-1"><code>void rgb_matrix_enable_noeeprom(void)</code> <a class="header-anchor" href="#api-rgb-matrix-enable-noeeprom" aria-label="Permalink to &quot;`void rgb_matrix_enable_noeeprom(void)` {#api-rgb-matrix-enable-noeeprom}&quot;">​</a></h3><p>Turn RGB Matrix on. New state is not written to EEPROM.</p><hr><h3 id="api-rgb-matrix-disable" tabindex="-1"><code>void rgb_matrix_disable(void)</code> <a class="header-anchor" href="#api-rgb-matrix-disable" aria-label="Permalink to &quot;`void rgb_matrix_disable(void)` {#api-rgb-matrix-disable}&quot;">​</a></h3><p>Turn RGB Matrix off.</p><hr><h3 id="api-rgb-matrix-disable-noeeprom" tabindex="-1"><code>void rgb_matrix_disable_noeeprom(void)</code> <a class="header-anchor" href="#api-rgb-matrix-disable-noeeprom" aria-label="Permalink to &quot;`void rgb_matrix_disable_noeeprom(void)` {#api-rgb-matrix-disable-noeeprom}&quot;">​</a></h3><p>Turn RGB Matrix off. New state is not written to EEPROM.</p><hr><h3 id="api-rgb-matrix-is-enabled" tabindex="-1"><code>bool rgb_matrix_is_enabled(void)</code> <a class="header-anchor" href="#api-rgb-matrix-is-enabled" aria-label="Permalink to &quot;`bool rgb_matrix_is_enabled(void)` {#api-rgb-matrix-is-enabled}&quot;">​</a></h3><p>Get the current enabled state of RGB Matrix.</p><h4 id="api-rgb-matrix-is-enabled-return" tabindex="-1">Return Value <a class="header-anchor" href="#api-rgb-matrix-is-enabled-return" aria-label="Permalink to &quot;Return Value {#api-rgb-matrix-is-enabled-return}&quot;">​</a></h4><p><code>true</code> if RGB Matrix is enabled.</p><hr><h3 id="api-rgb-matrix-set-color" tabindex="-1"><code>void rgb_matrix_set_color(uint8_t index, uint8_t r, uint8_t g, uint8_t b)</code> <a class="header-anchor" href="#api-rgb-matrix-set-color" aria-label="Permalink to &quot;`void rgb_matrix_set_color(uint8_t index, uint8_t r, uint8_t g, uint8_t b)` {#api-rgb-matrix-set-color}&quot;">​</a></h3><p>Set the color of a single LED.</p><p>This function can only be run from within an effect or indicator callback, otherwise the currently running animation will simply overwrite it on the next frame.</p><h4 id="api-rgb-matrix-set-color-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-rgb-matrix-set-color-arguments" aria-label="Permalink to &quot;Arguments {#api-rgb-matrix-set-color-arguments}&quot;">​</a></h4><ul><li><code>uint8_t index</code><br> The LED index, from 0 to <code>RGB_MATRIX_LED_COUNT - 1</code>.</li><li><code>uint8_t r</code><br> The red value to set.</li><li><code>uint8_t g</code><br> The green value to set.</li><li><code>uint8_t b</code><br> The blue value to set.</li></ul><hr><h3 id="api-rgb-matrix-set-color-all" tabindex="-1"><code>void rgb_matrix_set_color_all(uint8_t r, uint8_t g, uint8_t b)</code> <a class="header-anchor" href="#api-rgb-matrix-set-color-all" aria-label="Permalink to &quot;`void rgb_matrix_set_color_all(uint8_t r, uint8_t g, uint8_t b)` {#api-rgb-matrix-set-color-all}&quot;">​</a></h3><p>Set the color of all LEDs.</p><p>This function can only be run from within an effect or indicator callback, otherwise the currently running animation will simply overwrite it on the next frame.</p><h4 id="api-rgb-matrix-set-color-all-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-rgb-matrix-set-color-all-arguments" aria-label="Permalink to &quot;Arguments {#api-rgb-matrix-set-color-all-arguments}&quot;">​</a></h4><ul><li><code>uint8_t r</code><br> The red value to set.</li><li><code>uint8_t g</code><br> The green value to set.</li><li><code>uint8_t b</code><br> The blue value to set.</li></ul><hr><h3 id="api-rgb-matrix-mode" tabindex="-1"><code>void rgb_matrix_mode(uint8_t mode)</code> <a class="header-anchor" href="#api-rgb-matrix-mode" aria-label="Permalink to &quot;`void rgb_matrix_mode(uint8_t mode)` {#api-rgb-matrix-mode}&quot;">​</a></h3><p>Set the currently running effect.</p><h4 id="api-rgb-matrix-mode-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-rgb-matrix-mode-arguments" aria-label="Permalink to &quot;Arguments {#api-rgb-matrix-mode-arguments}&quot;">​</a></h4><ul><li><code>uint8_t mode</code><br> The effect to switch to.</li></ul><hr><h3 id="api-rgb-matrix-mode-noeeprom" tabindex="-1"><code>void rgb_matrix_mode_noeeprom(uint8_t mode)</code> <a class="header-anchor" href="#api-rgb-matrix-mode-noeeprom" aria-label="Permalink to &quot;`void rgb_matrix_mode_noeeprom(uint8_t mode)` {#api-rgb-matrix-mode-noeeprom}&quot;">​</a></h3><p>Set the currently running effect. New state is not written to EEPROM.</p><h4 id="api-rgb-matrix-mode-noeeprom-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-rgb-matrix-mode-noeeprom-arguments" aria-label="Permalink to &quot;Arguments {#api-rgb-matrix-mode-noeeprom-arguments}&quot;">​</a></h4><ul><li><code>uint8_t mode</code><br> The effect to switch to.</li></ul><hr><h3 id="api-rgb-matrix-step" tabindex="-1"><code>void rgb_matrix_step(void)</code> <a class="header-anchor" href="#api-rgb-matrix-step" aria-label="Permalink to &quot;`void rgb_matrix_step(void)` {#api-rgb-matrix-step}&quot;">​</a></h3><p>Move to the next enabled effect.</p><hr><h3 id="api-rgb-matrix-step-noeeprom" tabindex="-1"><code>void rgb_matrix_step_noeeprom(void)</code> <a class="header-anchor" href="#api-rgb-matrix-step-noeeprom" aria-label="Permalink to &quot;`void rgb_matrix_step_noeeprom(void)` {#api-rgb-matrix-step-noeeprom}&quot;">​</a></h3><p>Move to the next enabled effect. New state is not written to EEPROM.</p><hr><h3 id="api-rgb-matrix-step-reverse" tabindex="-1"><code>void rgb_matrix_step_reverse(void)</code> <a class="header-anchor" href="#api-rgb-matrix-step-reverse" aria-label="Permalink to &quot;`void rgb_matrix_step_reverse(void)` {#api-rgb-matrix-step-reverse}&quot;">​</a></h3><p>Move to the previous enabled effect.</p><hr><h3 id="api-rgb-matrix-step-reverse-noeeprom" tabindex="-1"><code>void rgb_matrix_step_reverse_noeeprom(void)</code> <a class="header-anchor" href="#api-rgb-matrix-step-reverse-noeeprom" aria-label="Permalink to &quot;`void rgb_matrix_step_reverse_noeeprom(void)` {#api-rgb-matrix-step-reverse-noeeprom}&quot;">​</a></h3><p>Move to the previous enabled effect. New state is not written to EEPROM.</p><hr><h3 id="api-rgb-matrix-get-mode" tabindex="-1"><code>uint8_t rgb_matrix_get_mode(void)</code> <a class="header-anchor" href="#api-rgb-matrix-get-mode" aria-label="Permalink to &quot;`uint8_t rgb_matrix_get_mode(void)` {#api-rgb-matrix-get-mode}&quot;">​</a></h3><p>Get the currently running effect.</p><h4 id="api-rgb-matrix-get-mode-return" tabindex="-1">Return Value <a class="header-anchor" href="#api-rgb-matrix-get-mode-return" aria-label="Permalink to &quot;Return Value {#api-rgb-matrix-get-mode-return}&quot;">​</a></h4><p>The index of the currently running effect.</p><hr><h3 id="api-rgb-matrix-increase-hue" tabindex="-1"><code>void rgb_matrix_increase_hue(void)</code> <a class="header-anchor" href="#api-rgb-matrix-increase-hue" aria-label="Permalink to &quot;`void rgb_matrix_increase_hue(void)` {#api-rgb-matrix-increase-hue}&quot;">​</a></h3><p>Increase the global effect hue.</p><hr><h3 id="api-rgb-matrix-increase-hue-noeeprom" tabindex="-1"><code>void rgb_matrix_increase_hue_noeeprom(void)</code> <a class="header-anchor" href="#api-rgb-matrix-increase-hue-noeeprom" aria-label="Permalink to &quot;`void rgb_matrix_increase_hue_noeeprom(void)` {#api-rgb-matrix-increase-hue-noeeprom}&quot;">​</a></h3><p>Increase the global effect hue. New state is not written to EEPROM.</p><hr><h3 id="api-rgb-matrix-decrease-hue" tabindex="-1"><code>void rgb_matrix_decrease_hue(void)</code> <a class="header-anchor" href="#api-rgb-matrix-decrease-hue" aria-label="Permalink to &quot;`void rgb_matrix_decrease_hue(void)` {#api-rgb-matrix-decrease-hue}&quot;">​</a></h3><p>Decrease the global effect hue.</p><hr><h3 id="api-rgb-matrix-decrease-hue-noeeprom" tabindex="-1"><code>void rgb_matrix_decrease_hue_noeeprom(void)</code> <a class="header-anchor" href="#api-rgb-matrix-decrease-hue-noeeprom" aria-label="Permalink to &quot;`void rgb_matrix_decrease_hue_noeeprom(void)` {#api-rgb-matrix-decrease-hue-noeeprom}&quot;">​</a></h3><p>Decrease the global effect hue. New state is not written to EEPROM.</p><hr><h3 id="api-rgb-matrix-get-hue" tabindex="-1"><code>uint8_t rgb_matrix_get_hue(void)</code> <a class="header-anchor" href="#api-rgb-matrix-get-hue" aria-label="Permalink to &quot;`uint8_t rgb_matrix_get_hue(void)` {#api-rgb-matrix-get-hue}&quot;">​</a></h3><p>Get the current global effect hue.</p><h4 id="api-rgb-matrix-get-hue-return" tabindex="-1">Return Value <a class="header-anchor" href="#api-rgb-matrix-get-hue-return" aria-label="Permalink to &quot;Return Value {#api-rgb-matrix-get-hue-return}&quot;">​</a></h4><p>The current hue value, from 0 to 255.</p><hr><h3 id="api-rgb-matrix-increase-sat" tabindex="-1"><code>void rgb_matrix_increase_sat(void)</code> <a class="header-anchor" href="#api-rgb-matrix-increase-sat" aria-label="Permalink to &quot;`void rgb_matrix_increase_sat(void)` {#api-rgb-matrix-increase-sat}&quot;">​</a></h3><p>Increase the global effect saturation.</p><hr><h3 id="api-rgb-matrix-increase-sat-noeeprom" tabindex="-1"><code>void rgb_matrix_increase_sat_noeeprom(void)</code> <a class="header-anchor" href="#api-rgb-matrix-increase-sat-noeeprom" aria-label="Permalink to &quot;`void rgb_matrix_increase_sat_noeeprom(void)` {#api-rgb-matrix-increase-sat-noeeprom}&quot;">​</a></h3><p>Increase the global effect saturation. New state is not written to EEPROM.</p><hr><h3 id="api-rgb-matrix-decrease-sat" tabindex="-1"><code>void rgb_matrix_decrease_sat(void)</code> <a class="header-anchor" href="#api-rgb-matrix-decrease-sat" aria-label="Permalink to &quot;`void rgb_matrix_decrease_sat(void)` {#api-rgb-matrix-decrease-sat}&quot;">​</a></h3><p>Decrease the global effect saturation.</p><hr><h3 id="api-rgb-matrix-decrease-sat-noeeprom" tabindex="-1"><code>void rgb_matrix_decrease_sat_noeeprom(void)</code> <a class="header-anchor" href="#api-rgb-matrix-decrease-sat-noeeprom" aria-label="Permalink to &quot;`void rgb_matrix_decrease_sat_noeeprom(void)` {#api-rgb-matrix-decrease-sat-noeeprom}&quot;">​</a></h3><p>Decrease the global effect saturation. New state is not written to EEPROM.</p><hr><h3 id="api-rgb-matrix-get-sat" tabindex="-1"><code>uint8_t rgb_matrix_get_sat(void)</code> <a class="header-anchor" href="#api-rgb-matrix-get-sat" aria-label="Permalink to &quot;`uint8_t rgb_matrix_get_sat(void)` {#api-rgb-matrix-get-sat}&quot;">​</a></h3><p>Get the current global effect saturation.</p><h4 id="api-rgb-matrix-get-sat-return" tabindex="-1">Return Value <a class="header-anchor" href="#api-rgb-matrix-get-sat-return" aria-label="Permalink to &quot;Return Value {#api-rgb-matrix-get-sat-return}&quot;">​</a></h4><p>The current saturation value, from 0 to 255.</p><hr><h3 id="api-rgb-matrix-increase-val" tabindex="-1"><code>void rgb_matrix_increase_val(void)</code> <a class="header-anchor" href="#api-rgb-matrix-increase-val" aria-label="Permalink to &quot;`void rgb_matrix_increase_val(void)` {#api-rgb-matrix-increase-val}&quot;">​</a></h3><p>Increase the global effect value (brightness).</p><hr><h3 id="api-rgb-matrix-increase-val-noeeprom" tabindex="-1"><code>void rgb_matrix_increase_val_noeeprom(void)</code> <a class="header-anchor" href="#api-rgb-matrix-increase-val-noeeprom" aria-label="Permalink to &quot;`void rgb_matrix_increase_val_noeeprom(void)` {#api-rgb-matrix-increase-val-noeeprom}&quot;">​</a></h3><p>Increase the global effect value (brightness). New state is not written to EEPROM.</p><hr><h3 id="api-rgb-matrix-decrease-val" tabindex="-1"><code>void rgb_matrix_decrease_val(void)</code> <a class="header-anchor" href="#api-rgb-matrix-decrease-val" aria-label="Permalink to &quot;`void rgb_matrix_decrease_val(void)` {#api-rgb-matrix-decrease-val}&quot;">​</a></h3><p>Decrease the global effect value (brightness).</p><hr><h3 id="api-rgb-matrix-decrease-val-noeeprom" tabindex="-1"><code>void rgb_matrix_decrease_val_noeeprom(void)</code> <a class="header-anchor" href="#api-rgb-matrix-decrease-val-noeeprom" aria-label="Permalink to &quot;`void rgb_matrix_decrease_val_noeeprom(void)` {#api-rgb-matrix-decrease-val-noeeprom}&quot;">​</a></h3><p>Decrease the global effect value (brightness). New state is not written to EEPROM.</p><hr><h3 id="api-rgb-matrix-get-val" tabindex="-1"><code>uint8_t rgb_matrix_get_val(void)</code> <a class="header-anchor" href="#api-rgb-matrix-get-val" aria-label="Permalink to &quot;`uint8_t rgb_matrix_get_val(void)` {#api-rgb-matrix-get-val}&quot;">​</a></h3><p>Get the current global effect value (brightness).</p><h4 id="api-rgb-matrix-get-val-return" tabindex="-1">Return Value <a class="header-anchor" href="#api-rgb-matrix-get-val-return" aria-label="Permalink to &quot;Return Value {#api-rgb-matrix-get-val-return}&quot;">​</a></h4><p>The current brightness value, from 0 to 255.</p><hr><h3 id="api-rgb-matrix-increase-speed" tabindex="-1"><code>void rgb_matrix_increase_speed(void)</code> <a class="header-anchor" href="#api-rgb-matrix-increase-speed" aria-label="Permalink to &quot;`void rgb_matrix_increase_speed(void)` {#api-rgb-matrix-increase-speed}&quot;">​</a></h3><p>Increase the effect speed.</p><hr><h3 id="api-rgb-matrix-increase-speed-noeeprom" tabindex="-1"><code>void rgb_matrix_increase_speed_noeeprom(void)</code> <a class="header-anchor" href="#api-rgb-matrix-increase-speed-noeeprom" aria-label="Permalink to &quot;`void rgb_matrix_increase_speed_noeeprom(void)` {#api-rgb-matrix-increase-speed-noeeprom}&quot;">​</a></h3><p>Increase the effect speed. New state is not written to EEPROM.</p><hr><h3 id="api-rgb-matrix-decrease-speed" tabindex="-1"><code>void rgb_matrix_decrease_speed(void)</code> <a class="header-anchor" href="#api-rgb-matrix-decrease-speed" aria-label="Permalink to &quot;`void rgb_matrix_decrease_speed(void)` {#api-rgb-matrix-decrease-speed}&quot;">​</a></h3><p>Decrease the effect speed.</p><hr><h3 id="api-rgb-matrix-decrease-speed-noeeprom" tabindex="-1"><code>void rgb_matrix_decrease_speed_noeeprom(void)</code> <a class="header-anchor" href="#api-rgb-matrix-decrease-speed-noeeprom" aria-label="Permalink to &quot;`void rgb_matrix_decrease_speed_noeeprom(void)` {#api-rgb-matrix-decrease-speed-noeeprom}&quot;">​</a></h3><p>Decrease the effect speed. New state is not written to EEPROM.</p><hr><h3 id="api-rgb-matrix-set-speed" tabindex="-1"><code>void rgb_matrix_set_speed(uint8_t speed)</code> <a class="header-anchor" href="#api-rgb-matrix-set-speed" aria-label="Permalink to &quot;`void rgb_matrix_set_speed(uint8_t speed)` {#api-rgb-matrix-set-speed}&quot;">​</a></h3><p>Set the effect speed.</p><h4 id="api-rgb-matrix-set-speed-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-rgb-matrix-set-speed-arguments" aria-label="Permalink to &quot;Arguments {#api-rgb-matrix-set-speed-arguments}&quot;">​</a></h4><ul><li><code>uint8_t speed</code><br> The new speed to set, from 0 to 255.</li></ul><hr><h3 id="api-rgb-matrix-set-speed-noeeprom" tabindex="-1"><code>void rgb_matrix_set_speed_noeeprom(uint8_t speed)</code> <a class="header-anchor" href="#api-rgb-matrix-set-speed-noeeprom" aria-label="Permalink to &quot;`void rgb_matrix_set_speed_noeeprom(uint8_t speed)` {#api-rgb-matrix-set-speed-noeeprom}&quot;">​</a></h3><p>Set the effect speed. New state is not written to EEPROM.</p><h4 id="api-rgb-matrix-set-speed-noeeprom-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-rgb-matrix-set-speed-noeeprom-arguments" aria-label="Permalink to &quot;Arguments {#api-rgb-matrix-set-speed-noeeprom-arguments}&quot;">​</a></h4><ul><li><code>uint8_t speed</code><br> The new speed to set, from 0 to 255.</li></ul><hr><h3 id="api-rgb-matrix-get-speed" tabindex="-1"><code>uint8_t rgb_matrix_get_speed(void)</code> <a class="header-anchor" href="#api-rgb-matrix-get-speed" aria-label="Permalink to &quot;`uint8_t rgb_matrix_get_speed(void)` {#api-rgb-matrix-get-speed}&quot;">​</a></h3><p>Get the current effect speed.</p><h4 id="api-rgb-matrix-get-speed-return" tabindex="-1">Return Value <a class="header-anchor" href="#api-rgb-matrix-get-speed-return" aria-label="Permalink to &quot;Return Value {#api-rgb-matrix-get-speed-return}&quot;">​</a></h4><p>The current effect speed, from 0 to 255.</p><hr><h3 id="api-rgb-matrix-set-flags" tabindex="-1"><code>void rgb_matrix_set_flags(led_flags_t flags)</code> <a class="header-anchor" href="#api-rgb-matrix-set-flags" aria-label="Permalink to &quot;`void rgb_matrix_set_flags(led_flags_t flags)` {#api-rgb-matrix-set-flags}&quot;">​</a></h3><p>Set the global effect flags.</p><h4 id="api-rgb-matrix-set-flags-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-rgb-matrix-set-flags-arguments" aria-label="Permalink to &quot;Arguments {#api-rgb-matrix-set-flags-arguments}&quot;">​</a></h4><ul><li><code>led_flags_t flags</code><br> The <a href="#flags">flags</a> value to set.</li></ul><hr><h3 id="api-rgb-matrix-set-flags-noeeprom" tabindex="-1"><code>void rgb_matrix_set_flags_noeeprom(led_flags_t flags)</code> <a class="header-anchor" href="#api-rgb-matrix-set-flags-noeeprom" aria-label="Permalink to &quot;`void rgb_matrix_set_flags_noeeprom(led_flags_t flags)` {#api-rgb-matrix-set-flags-noeeprom}&quot;">​</a></h3><p>Set the global effect flags. New state is not written to EEPROM.</p><h4 id="api-rgb-matrix-set-flags-noeeprom-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-rgb-matrix-set-flags-noeeprom-arguments" aria-label="Permalink to &quot;Arguments {#api-rgb-matrix-set-flags-noeeprom-arguments}&quot;">​</a></h4><ul><li><code>led_flags_t flags</code><br> The <a href="#flags">flags</a> value to set.</li></ul><hr><h3 id="api-rgb-matrix-flags-step" tabindex="-1"><code>void rgb_matrix_flags_step(void)</code> <a class="header-anchor" href="#api-rgb-matrix-flags-step" aria-label="Permalink to &quot;`void rgb_matrix_flags_step(void)` {#api-rgb-matrix-flags-step}&quot;">​</a></h3><p>Move to the next flag combination.</p><hr><h3 id="api-rgb-matrix-flags-step-noeeprom" tabindex="-1"><code>void rgb_matrix_flags_step_noeeprom(void)</code> <a class="header-anchor" href="#api-rgb-matrix-flags-step-noeeprom" aria-label="Permalink to &quot;`void rgb_matrix_flags_step_noeeprom(void)` {#api-rgb-matrix-flags-step-noeeprom}&quot;">​</a></h3><p>Move to the next flag combination. New state is not written to EEPROM.</p><hr><h3 id="api-rgb-matrix-flags-step-reverse" tabindex="-1"><code>void rgb_matrix_flags_step_reverse(void)</code> <a class="header-anchor" href="#api-rgb-matrix-flags-step-reverse" aria-label="Permalink to &quot;`void rgb_matrix_flags_step_reverse(void)` {#api-rgb-matrix-flags-step-reverse}&quot;">​</a></h3><p>Move to the previous flag combination.</p><hr><h3 id="api-rgb-matrix-flags-step-reverse-noeeprom" tabindex="-1"><code>void rgb_matrix_flags_step_reverse_noeeprom(void)</code> <a class="header-anchor" href="#api-rgb-matrix-flags-step-reverse-noeeprom" aria-label="Permalink to &quot;`void rgb_matrix_flags_step_reverse_noeeprom(void)` {#api-rgb-matrix-flags-step-reverse-noeeprom}&quot;">​</a></h3><p>Move to the previous flag combination. New state is not written to EEPROM.</p><hr><h3 id="api-rgb-matrix-get-flags" tabindex="-1"><code>uint8_t rgb_matrix_get_flags(void)</code> <a class="header-anchor" href="#api-rgb-matrix-get-flags" aria-label="Permalink to &quot;`uint8_t rgb_matrix_get_flags(void)` {#api-rgb-matrix-get-flags}&quot;">​</a></h3><p>Get the current global effect flags.</p><h4 id="api-rgb-matrix-get-flags-return" tabindex="-1">Return Value <a class="header-anchor" href="#api-rgb-matrix-get-flags-return" aria-label="Permalink to &quot;Return Value {#api-rgb-matrix-get-flags-return}&quot;">​</a></h4><p>The current effect <a href="#flags">flags</a>.</p><hr><h3 id="api-rgb-matrix-sethsv" tabindex="-1"><code>void rgb_matrix_sethsv(uint8_t h, uint8_t s, uint8_t v)</code> <a class="header-anchor" href="#api-rgb-matrix-sethsv" aria-label="Permalink to &quot;`void rgb_matrix_sethsv(uint8_t h, uint8_t s, uint8_t v)` {#api-rgb-matrix-sethsv}&quot;">​</a></h3><p>Set the global effect hue, saturation, and value (brightness).</p><h3 id="api-rgb-matrix-sethsv-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-rgb-matrix-sethsv-arguments" aria-label="Permalink to &quot;Arguments {#api-rgb-matrix-sethsv-arguments}&quot;">​</a></h3><ul><li><code>uint8_t h</code><br> The hue to set, from 0 to 255.</li><li><code>uint8_t s</code><br> The saturation to set, from 0 to 255.</li><li><code>uint8_t v</code><br> The value (brightness) to set, from 0 to 255.</li></ul><hr><h3 id="api-rgb-matrix-sethsv-noeeprom" tabindex="-1"><code>void rgb_matrix_sethsv_noeeprom(uint8_t h, uint8_t s, uint8_t v)</code> <a class="header-anchor" href="#api-rgb-matrix-sethsv-noeeprom" aria-label="Permalink to &quot;`void rgb_matrix_sethsv_noeeprom(uint8_t h, uint8_t s, uint8_t v)` {#api-rgb-matrix-sethsv-noeeprom}&quot;">​</a></h3><p>Set the global effect hue, saturation, and value (brightness). New state is not written to EEPROM.</p><h4 id="api-rgb-matrix-sethsv-noeeprom-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-rgb-matrix-sethsv-noeeprom-arguments" aria-label="Permalink to &quot;Arguments {#api-rgb-matrix-sethsv-noeeprom-arguments}&quot;">​</a></h4><ul><li><code>uint8_t h</code><br> The hue to set, from 0 to 255.</li><li><code>uint8_t s</code><br> The saturation to set, from 0 to 255.</li><li><code>uint8_t v</code><br> The value (brightness) to set, from 0 to 255.</li></ul><hr><h3 id="api-rgb-matrix-get-hsv" tabindex="-1"><code>hsv_t rgb_matrix_get_hsv(void)</code> <a class="header-anchor" href="#api-rgb-matrix-get-hsv" aria-label="Permalink to &quot;`hsv_t rgb_matrix_get_hsv(void)` {#api-rgb-matrix-get-hsv}&quot;">​</a></h3><p>Get the current global effect hue, saturation, and value (brightness).</p><h4 id="api-rgb-matrix-get-hsv-return" tabindex="-1">Return Value <a class="header-anchor" href="#api-rgb-matrix-get-hsv-return" aria-label="Permalink to &quot;Return Value {#api-rgb-matrix-get-hsv-return}&quot;">​</a></h4><p>The current effect HSV as an <code>hsv_t</code> struct.</p><hr><h3 id="api-rgb-matrix-reload-from-eeprom" tabindex="-1"><code>void rgb_matrix_reload_from_eeprom(void)</code> <a class="header-anchor" href="#api-rgb-matrix-reload-from-eeprom" aria-label="Permalink to &quot;`void rgb_matrix_reload_from_eeprom(void)` {#api-rgb-matrix-reload-from-eeprom}&quot;">​</a></h3><p>Reload the effect configuration (enabled, mode and color) from EEPROM.</p><hr><h3 id="api-rgb-matrix-get-suspend-state" tabindex="-1"><code>bool rgb_matrix_get_suspend_state(void)</code> <a class="header-anchor" href="#api-rgb-matrix-get-suspend-state" aria-label="Permalink to &quot;`bool rgb_matrix_get_suspend_state(void)` {#api-rgb-matrix-get-suspend-state}&quot;">​</a></h3><p>Get the current suspend state of RGB Matrix.</p><h4 id="api-rgb-matrix-get-suspend-state-return" tabindex="-1">Return Value <a class="header-anchor" href="#api-rgb-matrix-get-suspend-state-return" aria-label="Permalink to &quot;Return Value {#api-rgb-matrix-get-suspend-state-return}&quot;">​</a></h4><p><code>true</code> if RGB Matrix is currently in the suspended state.</p><hr><h3 id="api-rgb-matrix-indicators-kb" tabindex="-1"><code>bool rgb_matrix_indicators_kb(void)</code> <a class="header-anchor" href="#api-rgb-matrix-indicators-kb" aria-label="Permalink to &quot;`bool rgb_matrix_indicators_kb(void)` {#api-rgb-matrix-indicators-kb}&quot;">​</a></h3><p>Keyboard-level callback, invoked after current animation frame is rendered but before it is flushed to the LEDs.</p><h4 id="api-rgb-matrix-indicators-kb-return" tabindex="-1">Return Value <a class="header-anchor" href="#api-rgb-matrix-indicators-kb-return" aria-label="Permalink to &quot;Return Value {#api-rgb-matrix-indicators-kb-return}&quot;">​</a></h4><p>Currently unused.</p><hr><h3 id="api-rgb-matrix-indicators-user" tabindex="-1"><code>bool rgb_matrix_indicators_user(void)</code> <a class="header-anchor" href="#api-rgb-matrix-indicators-user" aria-label="Permalink to &quot;`bool rgb_matrix_indicators_user(void)` {#api-rgb-matrix-indicators-user}&quot;">​</a></h3><p>Keymap-level callback, invoked after current animation frame is rendered but before it is flushed to the LEDs.</p><h4 id="api-rgb-matrix-indicators-user-return" tabindex="-1">Return Value <a class="header-anchor" href="#api-rgb-matrix-indicators-user-return" aria-label="Permalink to &quot;Return Value {#api-rgb-matrix-indicators-user-return}&quot;">​</a></h4><p><code>true</code> to continue running the keyboard-level callback.</p><hr><h3 id="api-rgb-matrix-indicators-advanced-kb" tabindex="-1"><code>bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max)</code> <a class="header-anchor" href="#api-rgb-matrix-indicators-advanced-kb" aria-label="Permalink to &quot;`bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max)` {#api-rgb-matrix-indicators-advanced-kb}&quot;">​</a></h3><p>Keyboard-level callback, invoked after current animation frame is rendered but before it is flushed to the LEDs.</p><h3 id="api-rgb-matrix-indicators-advanced-kb-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-rgb-matrix-indicators-advanced-kb-arguments" aria-label="Permalink to &quot;Arguments {#api-rgb-matrix-indicators-advanced-kb-arguments}&quot;">​</a></h3><ul><li><code>uint8_t led_min</code><br> The index of the first LED in this batch.</li><li><code>uint8_t led_max</code><br> The index of the last LED in this batch.</li></ul><h4 id="api-rgb-matrix-indicators-advanced-kb-return" tabindex="-1">Return Value <a class="header-anchor" href="#api-rgb-matrix-indicators-advanced-kb-return" aria-label="Permalink to &quot;Return Value {#api-rgb-matrix-indicators-advanced-kb-return}&quot;">​</a></h4><p>Currently unused.</p><hr><h3 id="api-rgb-matrix-indicators-advanced-user" tabindex="-1"><code>bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max)</code> <a class="header-anchor" href="#api-rgb-matrix-indicators-advanced-user" aria-label="Permalink to &quot;`bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max)` {#api-rgb-matrix-indicators-advanced-user}&quot;">​</a></h3><p>Keymap-level callback, invoked after current animation frame is rendered but before it is flushed to the LEDs.</p><h3 id="api-rgb-matrix-indicators-advanced-user-arguments" tabindex="-1">Arguments <a class="header-anchor" href="#api-rgb-matrix-indicators-advanced-user-arguments" aria-label="Permalink to &quot;Arguments {#api-rgb-matrix-indicators-advanced-user-arguments}&quot;">​</a></h3><ul><li><code>uint8_t led_min</code><br> The index of the first LED in this batch.</li><li><code>uint8_t led_max</code><br> The index of the last LED in this batch.</li></ul><h4 id="api-rgb-matrix-indicators-advanced-user-return" tabindex="-1">Return Value <a class="header-anchor" href="#api-rgb-matrix-indicators-advanced-user-return" aria-label="Permalink to &quot;Return Value {#api-rgb-matrix-indicators-advanced-user-return}&quot;">​</a></h4><p><code>true</code> to continue running the keyboard-level callback.</p>', 239))
  ]);
}
const rgb_matrix = /* @__PURE__ */ _export_sfc(_sfc_main, [["render", _sfc_render]]);
export {
  __pageData,
  rgb_matrix as default
};
