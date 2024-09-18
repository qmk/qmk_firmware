import { _ as _export_sfc, D as resolveComponent, c as createElementBlock, I as createVNode, w as withCtx, a8 as createStaticVNode, o as openBlock, l as createBaseVNode, a as createTextVNode } from "./chunks/framework.Clpp4x2N.js";
const __pageData = JSON.parse('{"title":"Building QMK with GitHub Userspace","description":"","frontmatter":{},"headers":[],"relativePath":"newbs_building_firmware_workflow.md","filePath":"newbs_building_firmware_workflow.md"}');
const _sfc_main = { name: "newbs_building_firmware_workflow.md" };
const _hoisted_1 = /* @__PURE__ */ createStaticVNode("", 10);
const _hoisted_11 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("QMK maintains a bundle of MSYS2, the CLI and all necessary dependencies including Git. Install "),
  /* @__PURE__ */ createBaseVNode("a", {
    href: "https://msys.qmk.fm/",
    target: "_blank",
    rel: "noreferrer"
  }, "QMK MSYS"),
  /* @__PURE__ */ createTextVNode(" with the latest release "),
  /* @__PURE__ */ createBaseVNode("a", {
    href: "https://github.com/qmk/qmk_distro_msys/releases/latest",
    target: "_blank",
    rel: "noreferrer"
  }, "here"),
  /* @__PURE__ */ createTextVNode(". Git will be part of the bundle.")
], -1);
const _hoisted_12 = /* @__PURE__ */ createBaseVNode("p", null, [
  /* @__PURE__ */ createTextVNode("Install Homebrew following the instructions on "),
  /* @__PURE__ */ createBaseVNode("a", {
    href: "https://brew.sh",
    target: "_blank",
    rel: "noreferrer"
  }, "https://brew.sh"),
  /* @__PURE__ */ createTextVNode(". Git will be part of the bundle.")
], -1);
const _hoisted_13 = /* @__PURE__ */ createBaseVNode("p", null, "It's very likely that you already have Git installed. If not, use one of the following commands:", -1);
const _hoisted_14 = /* @__PURE__ */ createBaseVNode("ul", null, [
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Debian / Ubuntu / Devuan: "),
    /* @__PURE__ */ createBaseVNode("code", null, "sudo apt install -y git")
  ]),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Fedora / Red Hat / CentOS: "),
    /* @__PURE__ */ createBaseVNode("code", null, "sudo yum -y install git")
  ]),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Arch / Manjaro: "),
    /* @__PURE__ */ createBaseVNode("code", null, "sudo pacman --needed --noconfirm -S git")
  ]),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Void: "),
    /* @__PURE__ */ createBaseVNode("code", null, "sudo xbps-install -y git")
  ]),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Solus: "),
    /* @__PURE__ */ createBaseVNode("code", null, "sudo eopkg -y install git")
  ]),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Sabayon: "),
    /* @__PURE__ */ createBaseVNode("code", null, "sudo equo install dev-vcs/git")
  ]),
  /* @__PURE__ */ createBaseVNode("li", null, [
    /* @__PURE__ */ createTextVNode("Gentoo: "),
    /* @__PURE__ */ createBaseVNode("code", null, "sudo emerge dev-vcs/git")
  ])
], -1);
const _hoisted_15 = /* @__PURE__ */ createStaticVNode("", 35);
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  const _component_PluginTabsTab = resolveComponent("PluginTabsTab");
  const _component_PluginTabs = resolveComponent("PluginTabs");
  return openBlock(), createElementBlock("div", null, [
    _hoisted_1,
    createVNode(_component_PluginTabs, null, {
      default: withCtx(() => [
        createVNode(_component_PluginTabsTab, { label: "Windows" }, {
          default: withCtx(() => [
            _hoisted_11
          ]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "macOS" }, {
          default: withCtx(() => [
            _hoisted_12
          ]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "Linux/WSL" }, {
          default: withCtx(() => [
            _hoisted_13,
            _hoisted_14
          ]),
          _: 1
        })
      ]),
      _: 1
    }),
    _hoisted_15
  ]);
}
const newbs_building_firmware_workflow = /* @__PURE__ */ _export_sfc(_sfc_main, [["render", _sfc_render]]);
export {
  __pageData,
  newbs_building_firmware_workflow as default
};
