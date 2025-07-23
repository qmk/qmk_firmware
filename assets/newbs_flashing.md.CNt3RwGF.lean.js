import { _ as _export_sfc, c as createElementBlock, I as createVNode, w as withCtx, a8 as createStaticVNode, D as resolveComponent, o as openBlock, l as createBaseVNode } from "./chunks/framework.Cauyuiy8.js";
const __pageData = JSON.parse('{"title":"Flashing Your Keyboard","description":"","frontmatter":{},"headers":[],"relativePath":"newbs_flashing.md","filePath":"newbs_flashing.md","lastUpdated":null}');
const _sfc_main = { name: "newbs_flashing.md" };
const _hoisted_1 = /* @__PURE__ */ createStaticVNode("", 17);
const _hoisted_18 = /* @__PURE__ */ createBaseVNode("div", { class: "language- vp-adaptive-theme" }, [
  /* @__PURE__ */ createBaseVNode("button", {
    title: "Copy Code",
    class: "copy"
  }),
  /* @__PURE__ */ createBaseVNode("span", { class: "lang" }),
  /* @__PURE__ */ createBaseVNode("pre", { class: "shiki shiki-themes github-light github-dark vp-code" }, [
    /* @__PURE__ */ createBaseVNode("code", null, [
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", null, "start .")
      ])
    ])
  ])
], -1);
const _hoisted_19 = /* @__PURE__ */ createBaseVNode("div", { class: "language- vp-adaptive-theme" }, [
  /* @__PURE__ */ createBaseVNode("button", {
    title: "Copy Code",
    class: "copy"
  }),
  /* @__PURE__ */ createBaseVNode("span", { class: "lang" }),
  /* @__PURE__ */ createBaseVNode("pre", { class: "shiki shiki-themes github-light github-dark vp-code" }, [
    /* @__PURE__ */ createBaseVNode("code", null, [
      /* @__PURE__ */ createBaseVNode("span", { class: "line" }, [
        /* @__PURE__ */ createBaseVNode("span", null, "open .")
      ])
    ])
  ])
], -1);
const _hoisted_20 = /* @__PURE__ */ createStaticVNode("", 22);
function _sfc_render(_ctx, _cache, $props, $setup, $data, $options) {
  const _component_PluginTabsTab = resolveComponent("PluginTabsTab");
  const _component_PluginTabs = resolveComponent("PluginTabs");
  return openBlock(), createElementBlock("div", null, [
    _hoisted_1,
    createVNode(_component_PluginTabs, null, {
      default: withCtx(() => [
        createVNode(_component_PluginTabsTab, { label: "Windows" }, {
          default: withCtx(() => [
            _hoisted_18
          ]),
          _: 1
        }),
        createVNode(_component_PluginTabsTab, { label: "macOS" }, {
          default: withCtx(() => [
            _hoisted_19
          ]),
          _: 1
        })
      ]),
      _: 1
    }),
    _hoisted_20
  ]);
}
const newbs_flashing = /* @__PURE__ */ _export_sfc(_sfc_main, [["render", _sfc_render]]);
export {
  __pageData,
  newbs_flashing as default
};
