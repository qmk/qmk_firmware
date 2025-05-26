import { _ as _imports_0$1 } from "./chunks/color-wheel.DIUCmfNZ.js";
import { _ as _export_sfc, c as createElementBlock, I as createVNode, w as withCtx, a8 as createStaticVNode, D as resolveComponent, o as openBlock, l as createBaseVNode } from "./chunks/framework.Cauyuiy8.js";
const _imports_0 = "/assets/badge-community-light.Cciv47hr.svg";
const _imports_1 = "/assets/badge-community-dark.CirSPMz9.svg";
const __pageData = JSON.parse('{"title":"Documentation Capabilities","description":"","frontmatter":{},"headers":[],"relativePath":"__capabilities.md","filePath":"__capabilities.md","lastUpdated":null}');
const _sfc_main = { name: "__capabilities.md" };
const _hoisted_1 = /* @__PURE__ */ createStaticVNode("", 82);
const _hoisted_83 = /* @__PURE__ */ createBaseVNode("p", null, "a content 2", -1);
const _hoisted_84 = /* @__PURE__ */ createBaseVNode("p", null, "b content 2", -1);
const _hoisted_85 = /* @__PURE__ */ createBaseVNode("p", null, "nested a content 2", -1);
const _hoisted_86 = /* @__PURE__ */ createBaseVNode("p", null, "nested b content 2", -1);
const _hoisted_87 = /* @__PURE__ */ createStaticVNode("", 6);
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  const _component_PluginTabsTab = resolveComponent("PluginTabsTab");
  const _component_PluginTabs = resolveComponent("PluginTabs");
  return openBlock(), createElementBlock("div", null, [
    _hoisted_1,
    createVNode(_component_PluginTabs, null, {
      default: withCtx(() => [
        createVNode(_component_PluginTabsTab, { label: "tab a" }, {
          default: withCtx(() => [
            _hoisted_83
          ]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "tab b" }, {
          default: withCtx(() => [
            _hoisted_84
          ]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "tab c" }, {
          default: withCtx(() => [
            createVNode(_component_PluginTabs, null, {
              default: withCtx(() => [
                createVNode(_component_PluginTabsTab, { label: "nested tab a" }, {
                  default: withCtx(() => [
                    _hoisted_85
                  ]),
                  _: 1
                }),
                createVNode(_component_PluginTabsTab, { label: "nested tab b" }, {
                  default: withCtx(() => [
                    _hoisted_86
                  ]),
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
    }),
    _hoisted_87
  ]);
}
const __capabilities = /* @__PURE__ */ _export_sfc(_sfc_main, [["render", _sfc_render]]);
export {
  __pageData,
  __capabilities as default
};
