import { _ as _export_sfc, o as openBlock, c as createElementBlock, al as createStaticVNode, j as createBaseVNode, a as createTextVNode } from "./chunks/framework.8zKZLKO7.js";
const __pageData = JSON.parse('{"title":"QMK CLI Development","description":"","frontmatter":{},"headers":[],"relativePath":"cli_development.md","filePath":"cli_development.md","lastUpdated":null}');
const _sfc_main = { name: "cli_development.md" };
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  return openBlock(), createElementBlock("div", null, [..._cache[0] || (_cache[0] = [
    createStaticVNode("", 33),
    createBaseVNode("table", { tabindex: "0" }, [
      createBaseVNode("thead", null, [
        createBaseVNode("tr", null, [
          createBaseVNode("th", null, "Color"),
          createBaseVNode("th", null, "Background"),
          createBaseVNode("th", null, "Extended Background"),
          createBaseVNode("th", null, "Foreground"),
          createBaseVNode("th", null, "Extended Foreground")
        ])
      ]),
      createBaseVNode("tbody", null, [
        createBaseVNode("tr", null, [
          createBaseVNode("td", null, "Black"),
          createBaseVNode("td", { bg_black: "" }),
          createBaseVNode("td", { bg_lightblack_ex: "" }),
          createBaseVNode("td", { fg_black: "" }),
          createBaseVNode("td", { fg_lightblack_ex: "" })
        ]),
        createBaseVNode("tr", null, [
          createBaseVNode("td", null, "Blue"),
          createBaseVNode("td", { bg_blue: "" }),
          createBaseVNode("td", { bg_lightblue_ex: "" }),
          createBaseVNode("td", { fg_blue: "" }),
          createBaseVNode("td", { fg_lightblue_ex: "" })
        ]),
        createBaseVNode("tr", null, [
          createBaseVNode("td", null, "Cyan"),
          createBaseVNode("td", { bg_cyan: "" }),
          createBaseVNode("td", { bg_lightcyan_ex: "" }),
          createBaseVNode("td", { fg_cyan: "" }),
          createBaseVNode("td", { fg_lightcyan_ex: "" })
        ]),
        createBaseVNode("tr", null, [
          createBaseVNode("td", null, "Green"),
          createBaseVNode("td", { bg_green: "" }),
          createBaseVNode("td", { bg_lightgreen_ex: "" }),
          createBaseVNode("td", { fg_green: "" }),
          createBaseVNode("td", { fg_lightgreen_ex: "" })
        ]),
        createBaseVNode("tr", null, [
          createBaseVNode("td", null, "Magenta"),
          createBaseVNode("td", { bg_magenta: "" }),
          createBaseVNode("td", { bg_lightmagenta_ex: "" }),
          createBaseVNode("td", { fg_magenta: "" }),
          createBaseVNode("td", { fg_lightmagenta_ex: "" })
        ]),
        createBaseVNode("tr", null, [
          createBaseVNode("td", null, "Red"),
          createBaseVNode("td", { bg_red: "" }),
          createBaseVNode("td", { bg_lightred_ex: "" }),
          createBaseVNode("td", { fg_red: "" }),
          createBaseVNode("td", { fg_lightred_ex: "" })
        ]),
        createBaseVNode("tr", null, [
          createBaseVNode("td", null, "White"),
          createBaseVNode("td", { bg_white: "" }),
          createBaseVNode("td", { bg_lightwhite_ex: "" }),
          createBaseVNode("td", { fg_white: "" }),
          createBaseVNode("td", { fg_lightwhite_ex: "" })
        ]),
        createBaseVNode("tr", null, [
          createBaseVNode("td", null, "Yellow"),
          createBaseVNode("td", { bg_yellow: "" }),
          createBaseVNode("td", { bg_lightyellow_ex: "" }),
          createBaseVNode("td", { fg_yellow: "" }),
          createBaseVNode("td", { fg_lightyellow_ex: "" })
        ])
      ])
    ], -1),
    createBaseVNode("p", null, "There are also control sequences that can be used to change the behavior of ANSI output:", -1),
    createBaseVNode("table", { tabindex: "0" }, [
      createBaseVNode("thead", null, [
        createBaseVNode("tr", null, [
          createBaseVNode("th", null, "Control Sequences"),
          createBaseVNode("th", null, "Description")
        ])
      ]),
      createBaseVNode("tbody", null, [
        createBaseVNode("tr", null, [
          createBaseVNode("td", { style_bright: "" }),
          createBaseVNode("td", null, "Make the text brighter")
        ]),
        createBaseVNode("tr", null, [
          createBaseVNode("td", { style_dim: "" }),
          createBaseVNode("td", null, "Make the text dimmer")
        ]),
        createBaseVNode("tr", null, [
          createBaseVNode("td", { style_normal: "" }),
          createBaseVNode("td", null, [
            createTextVNode("Make the text normal (neither "),
            createBaseVNode("code", null, "{style_bright}"),
            createTextVNode(" nor "),
            createBaseVNode("code", null, "{style_dim}"),
            createTextVNode(")")
          ])
        ]),
        createBaseVNode("tr", null, [
          createBaseVNode("td", { style_reset_all: "" }),
          createBaseVNode("td", null, "Reset all text attributes to default. (This is automatically added to the end of every string.)")
        ]),
        createBaseVNode("tr", null, [
          createBaseVNode("td", { bg_reset: "" }),
          createBaseVNode("td", null, "Reset the background color to the user's default")
        ]),
        createBaseVNode("tr", null, [
          createBaseVNode("td", { fg_reset: "" }),
          createBaseVNode("td", null, "Reset the foreground color to the user's default")
        ])
      ])
    ], -1),
    createStaticVNode("", 44)
  ])]);
}
const cli_development = /* @__PURE__ */ _export_sfc(_sfc_main, [["render", _sfc_render]]);
export {
  __pageData,
  cli_development as default
};
