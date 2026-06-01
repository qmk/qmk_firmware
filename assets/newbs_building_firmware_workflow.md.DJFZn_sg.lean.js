import { _ as _export_sfc, C as resolveComponent, o as openBlock, c as createElementBlock, al as createStaticVNode, E as createVNode, w as withCtx, j as createBaseVNode, a as createTextVNode } from "./chunks/framework.8zKZLKO7.js";
const __pageData = JSON.parse('{"title":"Building QMK with GitHub Userspace","description":"","frontmatter":{},"headers":[],"relativePath":"newbs_building_firmware_workflow.md","filePath":"newbs_building_firmware_workflow.md","lastUpdated":null}');
const _sfc_main = { name: "newbs_building_firmware_workflow.md" };
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  const _component_PluginTabsTab = resolveComponent("PluginTabsTab");
  const _component_PluginTabs = resolveComponent("PluginTabs");
  return openBlock(), createElementBlock("div", null, [
    _cache[3] || (_cache[3] = createStaticVNode("", 10)),
    createVNode(_component_PluginTabs, null, {
      default: withCtx(() => [
        createVNode(_component_PluginTabsTab, { label: "Windows" }, {
          default: withCtx(() => [..._cache[0] || (_cache[0] = [
            createBaseVNode("p", null, [
              createTextVNode("QMK maintains a bundle of MSYS2, the CLI and all necessary dependencies including Git. Install "),
              createBaseVNode("a", {
                href: "https://msys.qmk.fm/",
                target: "_blank",
                rel: "noreferrer"
              }, "QMK MSYS"),
              createTextVNode(" with the latest release "),
              createBaseVNode("a", {
                href: "https://github.com/qmk/qmk_distro_msys/releases/latest",
                target: "_blank",
                rel: "noreferrer"
              }, "here"),
              createTextVNode(". Git will be part of the bundle.")
            ], -1)
          ])]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "macOS" }, {
          default: withCtx(() => [..._cache[1] || (_cache[1] = [
            createBaseVNode("p", null, [
              createTextVNode("Install Homebrew following the instructions on "),
              createBaseVNode("a", {
                href: "https://brew.sh",
                target: "_blank",
                rel: "noreferrer"
              }, "https://brew.sh"),
              createTextVNode(". Git will be part of the bundle.")
            ], -1)
          ])]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "Linux/WSL" }, {
          default: withCtx(() => [..._cache[2] || (_cache[2] = [
            createBaseVNode("p", null, "It's very likely that you already have Git installed. If not, use one of the following commands:", -1),
            createBaseVNode("ul", null, [
              createBaseVNode("li", null, [
                createTextVNode("Debian / Ubuntu / Devuan: "),
                createBaseVNode("code", null, "sudo apt install -y git")
              ]),
              createBaseVNode("li", null, [
                createTextVNode("Fedora / Red Hat / CentOS: "),
                createBaseVNode("code", null, "sudo yum -y install git")
              ]),
              createBaseVNode("li", null, [
                createTextVNode("Arch / Manjaro: "),
                createBaseVNode("code", null, "sudo pacman --needed --noconfirm -S git")
              ]),
              createBaseVNode("li", null, [
                createTextVNode("Void: "),
                createBaseVNode("code", null, "sudo xbps-install -y git")
              ]),
              createBaseVNode("li", null, [
                createTextVNode("Solus: "),
                createBaseVNode("code", null, "sudo eopkg -y install git")
              ]),
              createBaseVNode("li", null, [
                createTextVNode("Sabayon: "),
                createBaseVNode("code", null, "sudo equo install dev-vcs/git")
              ]),
              createBaseVNode("li", null, [
                createTextVNode("Gentoo: "),
                createBaseVNode("code", null, "sudo emerge dev-vcs/git")
              ])
            ], -1)
          ])]),
          _: 1
        })
      ]),
      _: 1
    }),
    _cache[4] || (_cache[4] = createStaticVNode("", 35))
  ]);
}
const newbs_building_firmware_workflow = /* @__PURE__ */ _export_sfc(_sfc_main, [["render", _sfc_render]]);
export {
  __pageData,
  newbs_building_firmware_workflow as default
};
