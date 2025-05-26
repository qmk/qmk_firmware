import { _ as _export_sfc, c as createElementBlock, o as openBlock, a8 as createStaticVNode, l as createBaseVNode, a as createTextVNode } from "./chunks/framework.Cauyuiy8.js";
const __pageData = JSON.parse('{"title":"QMK CLI Development","description":"","frontmatter":{},"headers":[],"relativePath":"cli_development.md","filePath":"cli_development.md","lastUpdated":null}');
const _sfc_main = { name: "cli_development.md" };
const _hoisted_1 = /* @__PURE__ */ createStaticVNode("", 33);
const _hoisted_34 = /* @__PURE__ */ createBaseVNode("table", { fg_lightyellow_ex: "" }, [
  /* @__PURE__ */ createBaseVNode("thead", null, [
    /* @__PURE__ */ createBaseVNode("tr", null, [
      /* @__PURE__ */ createBaseVNode("th", null, "Color"),
      /* @__PURE__ */ createBaseVNode("th", null, "Background"),
      /* @__PURE__ */ createBaseVNode("th", null, "Extended Background"),
      /* @__PURE__ */ createBaseVNode("th", null, "Foreground"),
      /* @__PURE__ */ createBaseVNode("th", null, "Extended Foreground")
    ])
  ]),
  /* @__PURE__ */ createBaseVNode("tbody", null, [
    /* @__PURE__ */ createBaseVNode("tr", { fg_lightblack_ex: "" }, [
      /* @__PURE__ */ createBaseVNode("td", null, "Black"),
      /* @__PURE__ */ createBaseVNode("td", { bg_black: "" }),
      /* @__PURE__ */ createBaseVNode("td", { bg_lightblack_ex: "" }),
      /* @__PURE__ */ createBaseVNode("td", { fg_black: "" }),
      /* @__PURE__ */ createBaseVNode("td")
    ]),
    /* @__PURE__ */ createBaseVNode("tr", { fg_lightblue_ex: "" }, [
      /* @__PURE__ */ createBaseVNode("td", null, "Blue"),
      /* @__PURE__ */ createBaseVNode("td", { bg_blue: "" }),
      /* @__PURE__ */ createBaseVNode("td", { bg_lightblue_ex: "" }),
      /* @__PURE__ */ createBaseVNode("td", { fg_blue: "" }),
      /* @__PURE__ */ createBaseVNode("td")
    ]),
    /* @__PURE__ */ createBaseVNode("tr", { fg_lightcyan_ex: "" }, [
      /* @__PURE__ */ createBaseVNode("td", null, "Cyan"),
      /* @__PURE__ */ createBaseVNode("td", { bg_cyan: "" }),
      /* @__PURE__ */ createBaseVNode("td", { bg_lightcyan_ex: "" }),
      /* @__PURE__ */ createBaseVNode("td", { fg_cyan: "" }),
      /* @__PURE__ */ createBaseVNode("td")
    ]),
    /* @__PURE__ */ createBaseVNode("tr", { fg_lightgreen_ex: "" }, [
      /* @__PURE__ */ createBaseVNode("td", null, "Green"),
      /* @__PURE__ */ createBaseVNode("td", { bg_green: "" }),
      /* @__PURE__ */ createBaseVNode("td", { bg_lightgreen_ex: "" }),
      /* @__PURE__ */ createBaseVNode("td", { fg_green: "" }),
      /* @__PURE__ */ createBaseVNode("td")
    ]),
    /* @__PURE__ */ createBaseVNode("tr", { fg_lightmagenta_ex: "" }, [
      /* @__PURE__ */ createBaseVNode("td", null, "Magenta"),
      /* @__PURE__ */ createBaseVNode("td", { bg_magenta: "" }),
      /* @__PURE__ */ createBaseVNode("td", { bg_lightmagenta_ex: "" }),
      /* @__PURE__ */ createBaseVNode("td", { fg_magenta: "" }),
      /* @__PURE__ */ createBaseVNode("td")
    ]),
    /* @__PURE__ */ createBaseVNode("tr", { fg_lightred_ex: "" }, [
      /* @__PURE__ */ createBaseVNode("td", null, "Red"),
      /* @__PURE__ */ createBaseVNode("td", { bg_red: "" }),
      /* @__PURE__ */ createBaseVNode("td", { bg_lightred_ex: "" }),
      /* @__PURE__ */ createBaseVNode("td", { fg_red: "" }),
      /* @__PURE__ */ createBaseVNode("td")
    ]),
    /* @__PURE__ */ createBaseVNode("tr", { fg_lightwhite_ex: "" }, [
      /* @__PURE__ */ createBaseVNode("td", null, "White"),
      /* @__PURE__ */ createBaseVNode("td", { bg_white: "" }),
      /* @__PURE__ */ createBaseVNode("td", { bg_lightwhite_ex: "" }),
      /* @__PURE__ */ createBaseVNode("td", { fg_white: "" }),
      /* @__PURE__ */ createBaseVNode("td")
    ]),
    /* @__PURE__ */ createBaseVNode("tr", null, [
      /* @__PURE__ */ createBaseVNode("td", null, "Yellow"),
      /* @__PURE__ */ createBaseVNode("td", { bg_yellow: "" }),
      /* @__PURE__ */ createBaseVNode("td", { bg_lightyellow_ex: "" }),
      /* @__PURE__ */ createBaseVNode("td", { fg_yellow: "" }),
      /* @__PURE__ */ createBaseVNode("td")
    ])
  ])
], -1);
const _hoisted_35 = /* @__PURE__ */ createBaseVNode("p", null, "There are also control sequences that can be used to change the behavior of ANSI output:", -1);
const _hoisted_36 = /* @__PURE__ */ createBaseVNode("table", null, [
  /* @__PURE__ */ createBaseVNode("thead", null, [
    /* @__PURE__ */ createBaseVNode("tr", null, [
      /* @__PURE__ */ createBaseVNode("th", null, "Control Sequences"),
      /* @__PURE__ */ createBaseVNode("th", null, "Description")
    ])
  ]),
  /* @__PURE__ */ createBaseVNode("tbody", null, [
    /* @__PURE__ */ createBaseVNode("tr", null, [
      /* @__PURE__ */ createBaseVNode("td", { style_bright: "" }),
      /* @__PURE__ */ createBaseVNode("td", null, "Make the text brighter")
    ]),
    /* @__PURE__ */ createBaseVNode("tr", null, [
      /* @__PURE__ */ createBaseVNode("td", { style_dim: "" }),
      /* @__PURE__ */ createBaseVNode("td", null, "Make the text dimmer")
    ]),
    /* @__PURE__ */ createBaseVNode("tr", null, [
      /* @__PURE__ */ createBaseVNode("td", { style_normal: "" }),
      /* @__PURE__ */ createBaseVNode("td", null, [
        /* @__PURE__ */ createTextVNode("Make the text normal (neither "),
        /* @__PURE__ */ createBaseVNode("code", null, "{style_bright}"),
        /* @__PURE__ */ createTextVNode(" nor "),
        /* @__PURE__ */ createBaseVNode("code", null, "{style_dim}"),
        /* @__PURE__ */ createTextVNode(")")
      ])
    ]),
    /* @__PURE__ */ createBaseVNode("tr", null, [
      /* @__PURE__ */ createBaseVNode("td", { style_reset_all: "" }),
      /* @__PURE__ */ createBaseVNode("td", null, "Reset all text attributes to default. (This is automatically added to the end of every string.)")
    ]),
    /* @__PURE__ */ createBaseVNode("tr", null, [
      /* @__PURE__ */ createBaseVNode("td", { bg_reset: "" }),
      /* @__PURE__ */ createBaseVNode("td", null, "Reset the background color to the user's default")
    ]),
    /* @__PURE__ */ createBaseVNode("tr", null, [
      /* @__PURE__ */ createBaseVNode("td", { fg_reset: "" }),
      /* @__PURE__ */ createBaseVNode("td", null, "Reset the foreground color to the user's default")
    ])
  ])
], -1);
const _hoisted_37 = /* @__PURE__ */ createStaticVNode("", 44);
const _hoisted_81 = [
  _hoisted_1,
  _hoisted_34,
  _hoisted_35,
  _hoisted_36,
  _hoisted_37
];
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  return openBlock(), createElementBlock("div", null, _hoisted_81);
}
const cli_development = /* @__PURE__ */ _export_sfc(_sfc_main, [["render", _sfc_render]]);
export {
  __pageData,
  cli_development as default
};
