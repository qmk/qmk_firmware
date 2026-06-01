import { _ as _imports_0$1 } from "./chunks/color-wheel.DIUCmfNZ.js";
import { _ as _export_sfc, C as resolveComponent, o as openBlock, c as createElementBlock, al as createStaticVNode, E as createVNode, w as withCtx, j as createBaseVNode } from "./chunks/framework.8zKZLKO7.js";
const _imports_0 = "/assets/badge-community-light.Cciv47hr.svg";
const _imports_1 = "/assets/badge-community-dark.CirSPMz9.svg";
const __pageData = JSON.parse('{"title":"Documentation Capabilities","description":"","frontmatter":{},"headers":[],"relativePath":"__capabilities.md","filePath":"__capabilities.md","lastUpdated":null}');
const _sfc_main = { name: "__capabilities.md" };
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  const _component_PluginTabsTab = resolveComponent("PluginTabsTab");
  const _component_PluginTabs = resolveComponent("PluginTabs");
  return openBlock(), createElementBlock("div", null, [
    _cache[4] || (_cache[4] = createStaticVNode("", 82)),
    createVNode(_component_PluginTabs, null, {
      default: withCtx(() => [
        createVNode(_component_PluginTabsTab, { label: "tab a" }, {
          default: withCtx(() => [..._cache[0] || (_cache[0] = [
            createBaseVNode("p", null, "a content 2", -1)
          ])]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "tab b" }, {
          default: withCtx(() => [..._cache[1] || (_cache[1] = [
            createBaseVNode("p", null, "b content 2", -1)
          ])]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "tab c" }, {
          default: withCtx(() => [
            createVNode(_component_PluginTabs, null, {
              default: withCtx(() => [
                createVNode(_component_PluginTabsTab, { label: "nested tab a" }, {
                  default: withCtx(() => [..._cache[2] || (_cache[2] = [
                    createBaseVNode("p", null, "nested a content 2", -1)
                  ])]),
                  _: 1
                }),
                createVNode(_component_PluginTabsTab, { label: "nested tab b" }, {
                  default: withCtx(() => [..._cache[3] || (_cache[3] = [
                    createBaseVNode("p", null, "nested b content 2", -1)
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
    }),
    _cache[5] || (_cache[5] = createStaticVNode("", 6))
  ]);
}
const __capabilities = /* @__PURE__ */ _export_sfc(_sfc_main, [["render", _sfc_render]]);
export {
  __pageData,
  __capabilities as default
};
