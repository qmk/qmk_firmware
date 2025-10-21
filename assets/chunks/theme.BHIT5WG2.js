const __vite__mapDeps=(i,m=__vite__mapDeps,d=(m.f||(m.f=["assets/chunks/VPLocalSearchBox.DNY7ZZm3.js","assets/chunks/framework.Cauyuiy8.js"])))=>i.map(i=>d[i]);
import { d as defineComponent, o as openBlock, c as createElementBlock, r as renderSlot, n as normalizeClass, a as createTextVNode, t as toDisplayString, b as createBlock, w as withCtx, e as createCommentVNode, T as Transition, _ as _export_sfc, u as useData$1, i as isExternal, f as treatAsHtml, g as withBase, h as computed, j as ref, k as onMounted, l as createBaseVNode, m as unref, p as pushScopeId, q as popScopeId, s as isActive, v as useMediaQuery, x as watch, y as watchEffect, z as onUnmounted, A as watchPostEffect, B as onUpdated, C as getScrollOffset, D as resolveComponent, F as Fragment, E as renderList, G as shallowRef, H as onContentUpdated, I as createVNode, J as resolveDynamicComponent, K as EXTERNAL_URL_RE, L as useRoute, M as mergeProps, N as inject, O as useWindowSize, P as normalizeStyle, Q as onClickOutside, R as onKeyStroke, S as nextTick, U as useWindowScroll, V as inBrowser, W as readonly, X as defineAsyncComponent, Y as __vitePreload, Z as useScrollLock, $ as provide, a0 as toHandlers, a1 as withKeys, a2 as withModifiers, a3 as useSlots, a4 as reactive, a5 as toRef, a6 as useRouter, a7 as onBeforeMount } from "./framework.Cauyuiy8.js";
const _sfc_main$Z = /* @__PURE__ */ defineComponent({
  __name: "VPBadge",
  props: {
    text: {},
    type: { default: "tip" }
  },
  setup(__props) {
    return (_ctx, _cache) => {
      return openBlock(), createElementBlock("span", {
        class: normalizeClass(["VPBadge", _ctx.type])
      }, [
        renderSlot(_ctx.$slots, "default", {}, () => [
          createTextVNode(toDisplayString(_ctx.text), 1)
        ])
      ], 2);
    };
  }
});
const _hoisted_1$K = {
  key: 0,
  class: "VPBackdrop"
};
const _sfc_main$Y = /* @__PURE__ */ defineComponent({
  __name: "VPBackdrop",
  props: {
    show: { type: Boolean }
  },
  setup(__props) {
    return (_ctx, _cache) => {
      return openBlock(), createBlock(Transition, { name: "fade" }, {
        default: withCtx(() => [
          _ctx.show ? (openBlock(), createElementBlock("div", _hoisted_1$K)) : createCommentVNode("", true)
        ]),
        _: 1
      });
    };
  }
});
const VPBackdrop = /* @__PURE__ */ _export_sfc(_sfc_main$Y, [["__scopeId", "data-v-c79a1216"]]);
const useData = useData$1;
function throttleAndDebounce(fn, delay) {
  let timeoutId;
  let called = false;
  return () => {
    if (timeoutId)
      clearTimeout(timeoutId);
    if (!called) {
      fn();
      (called = true) && setTimeout(() => called = false, delay);
    } else
      timeoutId = setTimeout(fn, delay);
  };
}
function ensureStartingSlash(path) {
  return /^\//.test(path) ? path : `/${path}`;
}
function normalizeLink$1(url) {
  const { pathname, search, hash, protocol } = new URL(url, "http://a.com");
  if (isExternal(url) || url.startsWith("#") || !protocol.startsWith("http") || !treatAsHtml(pathname))
    return url;
  const { site } = useData();
  const normalizedPath = pathname.endsWith("/") || pathname.endsWith(".html") ? url : url.replace(/(?:(^\.+)\/)?.*$/, `$1${pathname.replace(/(\.md)?$/, site.value.cleanUrls ? "" : ".html")}${search}${hash}`);
  return withBase(normalizedPath);
}
function useLangs({ removeCurrent = true, correspondingLink = false } = {}) {
  const { site, localeIndex, page, theme: theme2, hash } = useData();
  const currentLang = computed(() => {
    var _a, _b;
    return {
      label: (_a = site.value.locales[localeIndex.value]) == null ? void 0 : _a.label,
      link: ((_b = site.value.locales[localeIndex.value]) == null ? void 0 : _b.link) || (localeIndex.value === "root" ? "/" : `/${localeIndex.value}/`)
    };
  });
  const localeLinks = computed(() => Object.entries(site.value.locales).flatMap(([key, value]) => removeCurrent && currentLang.value.label === value.label ? [] : {
    text: value.label,
    link: normalizeLink(value.link || (key === "root" ? "/" : `/${key}/`), theme2.value.i18nRouting !== false && correspondingLink, page.value.relativePath.slice(currentLang.value.link.length - 1), !site.value.cleanUrls) + hash.value
  }));
  return { localeLinks, currentLang };
}
function normalizeLink(link, addPath, path, addExt) {
  return addPath ? link.replace(/\/$/, "") + ensureStartingSlash(path.replace(/(^|\/)index\.md$/, "$1").replace(/\.md$/, addExt ? ".html" : "")) : link;
}
const _withScopeId$h = (n) => (pushScopeId("data-v-f87ff6e4"), n = n(), popScopeId(), n);
const _hoisted_1$J = { class: "NotFound" };
const _hoisted_2$v = { class: "code" };
const _hoisted_3$l = { class: "title" };
const _hoisted_4$d = /* @__PURE__ */ _withScopeId$h(() => /* @__PURE__ */ createBaseVNode("div", { class: "divider" }, null, -1));
const _hoisted_5$a = { class: "quote" };
const _hoisted_6$7 = { class: "action" };
const _hoisted_7$5 = ["href", "aria-label"];
const _sfc_main$X = /* @__PURE__ */ defineComponent({
  __name: "NotFound",
  setup(__props) {
    const { site, theme: theme2 } = useData();
    const { localeLinks } = useLangs({ removeCurrent: false });
    const root = ref("/");
    onMounted(() => {
      var _a;
      const path = window.location.pathname.replace(site.value.base, "").replace(/(^.*?\/).*$/, "/$1");
      if (localeLinks.value.length) {
        root.value = ((_a = localeLinks.value.find(({ link }) => link.startsWith(path))) == null ? void 0 : _a.link) || localeLinks.value[0].link;
      }
    });
    return (_ctx, _cache) => {
      var _a, _b, _c, _d, _e;
      return openBlock(), createElementBlock("div", _hoisted_1$J, [
        createBaseVNode("p", _hoisted_2$v, toDisplayString(((_a = unref(theme2).notFound) == null ? void 0 : _a.code) ?? "404"), 1),
        createBaseVNode("h1", _hoisted_3$l, toDisplayString(((_b = unref(theme2).notFound) == null ? void 0 : _b.title) ?? "PAGE NOT FOUND"), 1),
        _hoisted_4$d,
        createBaseVNode("blockquote", _hoisted_5$a, toDisplayString(((_c = unref(theme2).notFound) == null ? void 0 : _c.quote) ?? "But if you don't change your direction, and if you keep looking, you may end up where you are heading."), 1),
        createBaseVNode("div", _hoisted_6$7, [
          createBaseVNode("a", {
            class: "link",
            href: unref(withBase)(root.value),
            "aria-label": ((_d = unref(theme2).notFound) == null ? void 0 : _d.linkLabel) ?? "go to home"
          }, toDisplayString(((_e = unref(theme2).notFound) == null ? void 0 : _e.linkText) ?? "Take me home"), 9, _hoisted_7$5)
        ])
      ]);
    };
  }
});
const NotFound = /* @__PURE__ */ _export_sfc(_sfc_main$X, [["__scopeId", "data-v-f87ff6e4"]]);
function getSidebar(_sidebar, path) {
  if (Array.isArray(_sidebar))
    return addBase(_sidebar);
  if (_sidebar == null)
    return [];
  path = ensureStartingSlash(path);
  const dir = Object.keys(_sidebar).sort((a, b) => {
    return b.split("/").length - a.split("/").length;
  }).find((dir2) => {
    return path.startsWith(ensureStartingSlash(dir2));
  });
  const sidebar = dir ? _sidebar[dir] : [];
  return Array.isArray(sidebar) ? addBase(sidebar) : addBase(sidebar.items, sidebar.base);
}
function getSidebarGroups(sidebar) {
  const groups = [];
  let lastGroupIndex = 0;
  for (const index in sidebar) {
    const item = sidebar[index];
    if (item.items) {
      lastGroupIndex = groups.push(item);
      continue;
    }
    if (!groups[lastGroupIndex]) {
      groups.push({ items: [] });
    }
    groups[lastGroupIndex].items.push(item);
  }
  return groups;
}
function getFlatSideBarLinks(sidebar) {
  const links = [];
  function recursivelyExtractLinks(items) {
    for (const item of items) {
      if (item.text && item.link) {
        links.push({
          text: item.text,
          link: item.link,
          docFooterText: item.docFooterText
        });
      }
      if (item.items) {
        recursivelyExtractLinks(item.items);
      }
    }
  }
  recursivelyExtractLinks(sidebar);
  return links;
}
function hasActiveLink(path, items) {
  if (Array.isArray(items)) {
    return items.some((item) => hasActiveLink(path, item));
  }
  return isActive(path, items.link) ? true : items.items ? hasActiveLink(path, items.items) : false;
}
function addBase(items, _base) {
  return [...items].map((_item) => {
    const item = { ..._item };
    const base = item.base || _base;
    if (base && item.link)
      item.link = base + item.link;
    if (item.items)
      item.items = addBase(item.items, base);
    return item;
  });
}
function useSidebar() {
  const { frontmatter, page, theme: theme2 } = useData();
  const is960 = useMediaQuery("(min-width: 960px)");
  const isOpen = ref(false);
  const _sidebar = computed(() => {
    const sidebarConfig = theme2.value.sidebar;
    const relativePath = page.value.relativePath;
    return sidebarConfig ? getSidebar(sidebarConfig, relativePath) : [];
  });
  const sidebar = ref(_sidebar.value);
  watch(_sidebar, (next, prev) => {
    if (JSON.stringify(next) !== JSON.stringify(prev))
      sidebar.value = _sidebar.value;
  });
  const hasSidebar = computed(() => {
    return frontmatter.value.sidebar !== false && sidebar.value.length > 0 && frontmatter.value.layout !== "home";
  });
  const leftAside = computed(() => {
    if (hasAside)
      return frontmatter.value.aside == null ? theme2.value.aside === "left" : frontmatter.value.aside === "left";
    return false;
  });
  const hasAside = computed(() => {
    if (frontmatter.value.layout === "home")
      return false;
    if (frontmatter.value.aside != null)
      return !!frontmatter.value.aside;
    return theme2.value.aside !== false;
  });
  const isSidebarEnabled = computed(() => hasSidebar.value && is960.value);
  const sidebarGroups = computed(() => {
    return hasSidebar.value ? getSidebarGroups(sidebar.value) : [];
  });
  function open() {
    isOpen.value = true;
  }
  function close() {
    isOpen.value = false;
  }
  function toggle() {
    isOpen.value ? close() : open();
  }
  return {
    isOpen,
    sidebar,
    sidebarGroups,
    hasSidebar,
    hasAside,
    leftAside,
    isSidebarEnabled,
    open,
    close,
    toggle
  };
}
function useCloseSidebarOnEscape(isOpen, close) {
  let triggerElement;
  watchEffect(() => {
    triggerElement = isOpen.value ? document.activeElement : void 0;
  });
  onMounted(() => {
    window.addEventListener("keyup", onEscape);
  });
  onUnmounted(() => {
    window.removeEventListener("keyup", onEscape);
  });
  function onEscape(e) {
    if (e.key === "Escape" && isOpen.value) {
      close();
      triggerElement == null ? void 0 : triggerElement.focus();
    }
  }
}
function useSidebarControl(item) {
  const { page, hash } = useData();
  const collapsed = ref(false);
  const collapsible = computed(() => {
    return item.value.collapsed != null;
  });
  const isLink = computed(() => {
    return !!item.value.link;
  });
  const isActiveLink = ref(false);
  const updateIsActiveLink = () => {
    isActiveLink.value = isActive(page.value.relativePath, item.value.link);
  };
  watch([page, item, hash], updateIsActiveLink);
  onMounted(updateIsActiveLink);
  const hasActiveLink$1 = computed(() => {
    if (isActiveLink.value) {
      return true;
    }
    return item.value.items ? hasActiveLink(page.value.relativePath, item.value.items) : false;
  });
  const hasChildren = computed(() => {
    return !!(item.value.items && item.value.items.length);
  });
  watchEffect(() => {
    collapsed.value = !!(collapsible.value && item.value.collapsed);
  });
  watchPostEffect(() => {
    (isActiveLink.value || hasActiveLink$1.value) && (collapsed.value = false);
  });
  function toggle() {
    if (collapsible.value) {
      collapsed.value = !collapsed.value;
    }
  }
  return {
    collapsed,
    collapsible,
    isLink,
    isActiveLink,
    hasActiveLink: hasActiveLink$1,
    hasChildren,
    toggle
  };
}
function useAside() {
  const { hasSidebar } = useSidebar();
  const is960 = useMediaQuery("(min-width: 960px)");
  const is1280 = useMediaQuery("(min-width: 1280px)");
  const isAsideEnabled = computed(() => {
    if (!is1280.value && !is960.value) {
      return false;
    }
    return hasSidebar.value ? is1280.value : is960.value;
  });
  return {
    isAsideEnabled
  };
}
const resolvedHeaders = [];
function resolveTitle(theme2) {
  return typeof theme2.outline === "object" && !Array.isArray(theme2.outline) && theme2.outline.label || theme2.outlineTitle || "On this page";
}
function getHeaders(range) {
  const headers = [
    ...document.querySelectorAll(".VPDoc :where(h1,h2,h3,h4,h5,h6)")
  ].filter((el) => el.id && el.hasChildNodes()).map((el) => {
    const level = Number(el.tagName[1]);
    return {
      element: el,
      title: serializeHeader(el),
      link: "#" + el.id,
      level
    };
  });
  return resolveHeaders(headers, range);
}
function serializeHeader(h) {
  let ret = "";
  for (const node of h.childNodes) {
    if (node.nodeType === 1) {
      if (node.classList.contains("VPBadge") || node.classList.contains("header-anchor") || node.classList.contains("ignore-header")) {
        continue;
      }
      ret += node.textContent;
    } else if (node.nodeType === 3) {
      ret += node.textContent;
    }
  }
  return ret.trim();
}
function resolveHeaders(headers, range) {
  if (range === false) {
    return [];
  }
  const levelsRange = (typeof range === "object" && !Array.isArray(range) ? range.level : range) || 2;
  const [high, low] = typeof levelsRange === "number" ? [levelsRange, levelsRange] : levelsRange === "deep" ? [2, 6] : levelsRange;
  headers = headers.filter((h) => h.level >= high && h.level <= low);
  resolvedHeaders.length = 0;
  for (const { element, link } of headers) {
    resolvedHeaders.push({ element, link });
  }
  const ret = [];
  outer: for (let i = 0; i < headers.length; i++) {
    const cur = headers[i];
    if (i === 0) {
      ret.push(cur);
    } else {
      for (let j = i - 1; j >= 0; j--) {
        const prev = headers[j];
        if (prev.level < cur.level) {
          (prev.children || (prev.children = [])).push(cur);
          continue outer;
        }
      }
      ret.push(cur);
    }
  }
  return ret;
}
function useActiveAnchor(container, marker) {
  const { isAsideEnabled } = useAside();
  const onScroll = throttleAndDebounce(setActiveLink, 100);
  let prevActiveLink = null;
  onMounted(() => {
    requestAnimationFrame(setActiveLink);
    window.addEventListener("scroll", onScroll);
  });
  onUpdated(() => {
    activateLink(location.hash);
  });
  onUnmounted(() => {
    window.removeEventListener("scroll", onScroll);
  });
  function setActiveLink() {
    if (!isAsideEnabled.value) {
      return;
    }
    const scrollY = window.scrollY;
    const innerHeight = window.innerHeight;
    const offsetHeight = document.body.offsetHeight;
    const isBottom = Math.abs(scrollY + innerHeight - offsetHeight) < 1;
    const headers = resolvedHeaders.map(({ element, link }) => ({
      link,
      top: getAbsoluteTop(element)
    })).filter(({ top }) => !Number.isNaN(top)).sort((a, b) => a.top - b.top);
    if (!headers.length) {
      activateLink(null);
      return;
    }
    if (scrollY < 1) {
      activateLink(null);
      return;
    }
    if (isBottom) {
      activateLink(headers[headers.length - 1].link);
      return;
    }
    let activeLink = null;
    for (const { link, top } of headers) {
      if (top > scrollY + getScrollOffset() + 4) {
        break;
      }
      activeLink = link;
    }
    activateLink(activeLink);
  }
  function activateLink(hash) {
    if (prevActiveLink) {
      prevActiveLink.classList.remove("active");
    }
    if (hash == null) {
      prevActiveLink = null;
    } else {
      prevActiveLink = container.value.querySelector(`a[href="${decodeURIComponent(hash)}"]`);
    }
    const activeLink = prevActiveLink;
    if (activeLink) {
      activeLink.classList.add("active");
      marker.value.style.top = activeLink.offsetTop + 39 + "px";
      marker.value.style.opacity = "1";
    } else {
      marker.value.style.top = "33px";
      marker.value.style.opacity = "0";
    }
  }
}
function getAbsoluteTop(element) {
  let offsetTop = 0;
  while (element !== document.body) {
    if (element === null) {
      return NaN;
    }
    offsetTop += element.offsetTop;
    element = element.offsetParent;
  }
  return offsetTop;
}
const _hoisted_1$I = ["href", "title"];
const _sfc_main$W = /* @__PURE__ */ defineComponent({
  __name: "VPDocOutlineItem",
  props: {
    headers: {},
    root: { type: Boolean }
  },
  setup(__props) {
    function onClick({ target: el }) {
      const id2 = el.href.split("#")[1];
      const heading = document.getElementById(decodeURIComponent(id2));
      heading == null ? void 0 : heading.focus({ preventScroll: true });
    }
    return (_ctx, _cache) => {
      const _component_VPDocOutlineItem = resolveComponent("VPDocOutlineItem", true);
      return openBlock(), createElementBlock("ul", {
        class: normalizeClass(["VPDocOutlineItem", _ctx.root ? "root" : "nested"])
      }, [
        (openBlock(true), createElementBlock(Fragment, null, renderList(_ctx.headers, ({ children, link, title }) => {
          return openBlock(), createElementBlock("li", null, [
            createBaseVNode("a", {
              class: "outline-link",
              href: link,
              onClick,
              title
            }, toDisplayString(title), 9, _hoisted_1$I),
            (children == null ? void 0 : children.length) ? (openBlock(), createBlock(_component_VPDocOutlineItem, {
              key: 0,
              headers: children
            }, null, 8, ["headers"])) : createCommentVNode("", true)
          ]);
        }), 256))
      ], 2);
    };
  }
});
const VPDocOutlineItem = /* @__PURE__ */ _export_sfc(_sfc_main$W, [["__scopeId", "data-v-b933a997"]]);
const _withScopeId$g = (n) => (pushScopeId("data-v-935f8a84"), n = n(), popScopeId(), n);
const _hoisted_1$H = { class: "content" };
const _hoisted_2$u = {
  class: "outline-title",
  role: "heading",
  "aria-level": "2"
};
const _hoisted_3$k = { "aria-labelledby": "doc-outline-aria-label" };
const _hoisted_4$c = /* @__PURE__ */ _withScopeId$g(() => /* @__PURE__ */ createBaseVNode("span", {
  class: "visually-hidden",
  id: "doc-outline-aria-label"
}, " Table of Contents for current page ", -1));
const _sfc_main$V = /* @__PURE__ */ defineComponent({
  __name: "VPDocAsideOutline",
  setup(__props) {
    const { frontmatter, theme: theme2 } = useData();
    const headers = shallowRef([]);
    onContentUpdated(() => {
      headers.value = getHeaders(frontmatter.value.outline ?? theme2.value.outline);
    });
    const container = ref();
    const marker = ref();
    useActiveAnchor(container, marker);
    return (_ctx, _cache) => {
      return openBlock(), createElementBlock("div", {
        class: normalizeClass(["VPDocAsideOutline", { "has-outline": headers.value.length > 0 }]),
        ref_key: "container",
        ref: container,
        role: "navigation"
      }, [
        createBaseVNode("div", _hoisted_1$H, [
          createBaseVNode("div", {
            class: "outline-marker",
            ref_key: "marker",
            ref: marker
          }, null, 512),
          createBaseVNode("div", _hoisted_2$u, toDisplayString(unref(resolveTitle)(unref(theme2))), 1),
          createBaseVNode("nav", _hoisted_3$k, [
            _hoisted_4$c,
            createVNode(VPDocOutlineItem, {
              headers: headers.value,
              root: true
            }, null, 8, ["headers"])
          ])
        ])
      ], 2);
    };
  }
});
const VPDocAsideOutline = /* @__PURE__ */ _export_sfc(_sfc_main$V, [["__scopeId", "data-v-935f8a84"]]);
const _hoisted_1$G = { class: "VPDocAsideCarbonAds" };
const _sfc_main$U = /* @__PURE__ */ defineComponent({
  __name: "VPDocAsideCarbonAds",
  props: {
    carbonAds: {}
  },
  setup(__props) {
    const VPCarbonAds = () => null;
    return (_ctx, _cache) => {
      return openBlock(), createElementBlock("div", _hoisted_1$G, [
        createVNode(unref(VPCarbonAds), { "carbon-ads": _ctx.carbonAds }, null, 8, ["carbon-ads"])
      ]);
    };
  }
});
const _withScopeId$f = (n) => (pushScopeId("data-v-3f215769"), n = n(), popScopeId(), n);
const _hoisted_1$F = { class: "VPDocAside" };
const _hoisted_2$t = /* @__PURE__ */ _withScopeId$f(() => /* @__PURE__ */ createBaseVNode("div", { class: "spacer" }, null, -1));
const _sfc_main$T = /* @__PURE__ */ defineComponent({
  __name: "VPDocAside",
  setup(__props) {
    const { theme: theme2 } = useData();
    return (_ctx, _cache) => {
      return openBlock(), createElementBlock("div", _hoisted_1$F, [
        renderSlot(_ctx.$slots, "aside-top", {}, void 0, true),
        renderSlot(_ctx.$slots, "aside-outline-before", {}, void 0, true),
        createVNode(VPDocAsideOutline),
        renderSlot(_ctx.$slots, "aside-outline-after", {}, void 0, true),
        _hoisted_2$t,
        renderSlot(_ctx.$slots, "aside-ads-before", {}, void 0, true),
        unref(theme2).carbonAds ? (openBlock(), createBlock(_sfc_main$U, {
          key: 0,
          "carbon-ads": unref(theme2).carbonAds
        }, null, 8, ["carbon-ads"])) : createCommentVNode("", true),
        renderSlot(_ctx.$slots, "aside-ads-after", {}, void 0, true),
        renderSlot(_ctx.$slots, "aside-bottom", {}, void 0, true)
      ]);
    };
  }
});
const VPDocAside = /* @__PURE__ */ _export_sfc(_sfc_main$T, [["__scopeId", "data-v-3f215769"]]);
function useEditLink() {
  const { theme: theme2, page } = useData();
  return computed(() => {
    const { text = "Edit this page", pattern = "" } = theme2.value.editLink || {};
    let url;
    if (typeof pattern === "function") {
      url = pattern(page.value);
    } else {
      url = pattern.replace(/:path/g, page.value.filePath);
    }
    return { url, text };
  });
}
function usePrevNext() {
  const { page, theme: theme2, frontmatter } = useData();
  return computed(() => {
    var _a, _b, _c, _d, _e, _f, _g, _h;
    const sidebar = getSidebar(theme2.value.sidebar, page.value.relativePath);
    const links = getFlatSideBarLinks(sidebar);
    const candidates = uniqBy(links, (link) => link.link.replace(/[?#].*$/, ""));
    const index = candidates.findIndex((link) => {
      return isActive(page.value.relativePath, link.link);
    });
    const hidePrev = ((_a = theme2.value.docFooter) == null ? void 0 : _a.prev) === false && !frontmatter.value.prev || frontmatter.value.prev === false;
    const hideNext = ((_b = theme2.value.docFooter) == null ? void 0 : _b.next) === false && !frontmatter.value.next || frontmatter.value.next === false;
    return {
      prev: hidePrev ? void 0 : {
        text: (typeof frontmatter.value.prev === "string" ? frontmatter.value.prev : typeof frontmatter.value.prev === "object" ? frontmatter.value.prev.text : void 0) ?? ((_c = candidates[index - 1]) == null ? void 0 : _c.docFooterText) ?? ((_d = candidates[index - 1]) == null ? void 0 : _d.text),
        link: (typeof frontmatter.value.prev === "object" ? frontmatter.value.prev.link : void 0) ?? ((_e = candidates[index - 1]) == null ? void 0 : _e.link)
      },
      next: hideNext ? void 0 : {
        text: (typeof frontmatter.value.next === "string" ? frontmatter.value.next : typeof frontmatter.value.next === "object" ? frontmatter.value.next.text : void 0) ?? ((_f = candidates[index + 1]) == null ? void 0 : _f.docFooterText) ?? ((_g = candidates[index + 1]) == null ? void 0 : _g.text),
        link: (typeof frontmatter.value.next === "object" ? frontmatter.value.next.link : void 0) ?? ((_h = candidates[index + 1]) == null ? void 0 : _h.link)
      }
    };
  });
}
function uniqBy(array, keyFn) {
  const seen = /* @__PURE__ */ new Set();
  return array.filter((item) => {
    const k = keyFn(item);
    return seen.has(k) ? false : seen.add(k);
  });
}
const _sfc_main$S = /* @__PURE__ */ defineComponent({
  __name: "VPLink",
  props: {
    tag: {},
    href: {},
    noIcon: { type: Boolean },
    target: {},
    rel: {}
  },
  setup(__props) {
    const props = __props;
    const tag = computed(() => props.tag ?? (props.href ? "a" : "span"));
    const isExternal2 = computed(() => props.href && EXTERNAL_URL_RE.test(props.href));
    return (_ctx, _cache) => {
      return openBlock(), createBlock(resolveDynamicComponent(tag.value), {
        class: normalizeClass(["VPLink", {
          link: _ctx.href,
          "vp-external-link-icon": isExternal2.value,
          "no-icon": _ctx.noIcon
        }]),
        href: _ctx.href ? unref(normalizeLink$1)(_ctx.href) : void 0,
        target: _ctx.target ?? (isExternal2.value ? "_blank" : void 0),
        rel: _ctx.rel ?? (isExternal2.value ? "noreferrer" : void 0)
      }, {
        default: withCtx(() => [
          renderSlot(_ctx.$slots, "default")
        ]),
        _: 3
      }, 8, ["class", "href", "target", "rel"]);
    };
  }
});
const _hoisted_1$E = { class: "VPLastUpdated" };
const _hoisted_2$s = ["datetime"];
const _sfc_main$R = /* @__PURE__ */ defineComponent({
  __name: "VPDocFooterLastUpdated",
  setup(__props) {
    const { theme: theme2, page, frontmatter, lang } = useData();
    const date = computed(
      () => new Date(frontmatter.value.lastUpdated ?? page.value.lastUpdated)
    );
    const isoDatetime = computed(() => date.value.toISOString());
    const datetime = ref("");
    onMounted(() => {
      watchEffect(() => {
        var _a, _b, _c;
        datetime.value = new Intl.DateTimeFormat(
          ((_b = (_a = theme2.value.lastUpdated) == null ? void 0 : _a.formatOptions) == null ? void 0 : _b.forceLocale) ? lang.value : void 0,
          ((_c = theme2.value.lastUpdated) == null ? void 0 : _c.formatOptions) ?? {
            dateStyle: "short",
            timeStyle: "short"
          }
        ).format(date.value);
      });
    });
    return (_ctx, _cache) => {
      var _a;
      return openBlock(), createElementBlock("p", _hoisted_1$E, [
        createTextVNode(toDisplayString(((_a = unref(theme2).lastUpdated) == null ? void 0 : _a.text) || unref(theme2).lastUpdatedText || "Last updated") + ": ", 1),
        createBaseVNode("time", { datetime: isoDatetime.value }, toDisplayString(datetime.value), 9, _hoisted_2$s)
      ]);
    };
  }
});
const VPDocFooterLastUpdated = /* @__PURE__ */ _export_sfc(_sfc_main$R, [["__scopeId", "data-v-7e05ebdb"]]);
const _withScopeId$e = (n) => (pushScopeId("data-v-09de1c0f"), n = n(), popScopeId(), n);
const _hoisted_1$D = {
  key: 0,
  class: "VPDocFooter"
};
const _hoisted_2$r = {
  key: 0,
  class: "edit-info"
};
const _hoisted_3$j = {
  key: 0,
  class: "edit-link"
};
const _hoisted_4$b = /* @__PURE__ */ _withScopeId$e(() => /* @__PURE__ */ createBaseVNode("span", { class: "vpi-square-pen edit-link-icon" }, null, -1));
const _hoisted_5$9 = {
  key: 1,
  class: "last-updated"
};
const _hoisted_6$6 = {
  key: 1,
  class: "prev-next"
};
const _hoisted_7$4 = { class: "pager" };
const _hoisted_8$3 = ["innerHTML"];
const _hoisted_9$1 = ["innerHTML"];
const _hoisted_10$1 = { class: "pager" };
const _hoisted_11 = ["innerHTML"];
const _hoisted_12 = ["innerHTML"];
const _sfc_main$Q = /* @__PURE__ */ defineComponent({
  __name: "VPDocFooter",
  setup(__props) {
    const { theme: theme2, page, frontmatter } = useData();
    const editLink = useEditLink();
    const control = usePrevNext();
    const hasEditLink = computed(() => {
      return theme2.value.editLink && frontmatter.value.editLink !== false;
    });
    const hasLastUpdated = computed(() => {
      return page.value.lastUpdated && frontmatter.value.lastUpdated !== false;
    });
    const showFooter = computed(() => {
      return hasEditLink.value || hasLastUpdated.value || control.value.prev || control.value.next;
    });
    return (_ctx, _cache) => {
      var _a, _b, _c, _d;
      return showFooter.value ? (openBlock(), createElementBlock("footer", _hoisted_1$D, [
        renderSlot(_ctx.$slots, "doc-footer-before", {}, void 0, true),
        hasEditLink.value || hasLastUpdated.value ? (openBlock(), createElementBlock("div", _hoisted_2$r, [
          hasEditLink.value ? (openBlock(), createElementBlock("div", _hoisted_3$j, [
            createVNode(_sfc_main$S, {
              class: "edit-link-button",
              href: unref(editLink).url,
              "no-icon": true
            }, {
              default: withCtx(() => [
                _hoisted_4$b,
                createTextVNode(" " + toDisplayString(unref(editLink).text), 1)
              ]),
              _: 1
            }, 8, ["href"])
          ])) : createCommentVNode("", true),
          hasLastUpdated.value ? (openBlock(), createElementBlock("div", _hoisted_5$9, [
            createVNode(VPDocFooterLastUpdated)
          ])) : createCommentVNode("", true)
        ])) : createCommentVNode("", true),
        ((_a = unref(control).prev) == null ? void 0 : _a.link) || ((_b = unref(control).next) == null ? void 0 : _b.link) ? (openBlock(), createElementBlock("nav", _hoisted_6$6, [
          createBaseVNode("div", _hoisted_7$4, [
            ((_c = unref(control).prev) == null ? void 0 : _c.link) ? (openBlock(), createBlock(_sfc_main$S, {
              key: 0,
              class: "pager-link prev",
              href: unref(control).prev.link
            }, {
              default: withCtx(() => {
                var _a2;
                return [
                  createBaseVNode("span", {
                    class: "desc",
                    innerHTML: ((_a2 = unref(theme2).docFooter) == null ? void 0 : _a2.prev) || "Previous page"
                  }, null, 8, _hoisted_8$3),
                  createBaseVNode("span", {
                    class: "title",
                    innerHTML: unref(control).prev.text
                  }, null, 8, _hoisted_9$1)
                ];
              }),
              _: 1
            }, 8, ["href"])) : createCommentVNode("", true)
          ]),
          createBaseVNode("div", _hoisted_10$1, [
            ((_d = unref(control).next) == null ? void 0 : _d.link) ? (openBlock(), createBlock(_sfc_main$S, {
              key: 0,
              class: "pager-link next",
              href: unref(control).next.link
            }, {
              default: withCtx(() => {
                var _a2;
                return [
                  createBaseVNode("span", {
                    class: "desc",
                    innerHTML: ((_a2 = unref(theme2).docFooter) == null ? void 0 : _a2.next) || "Next page"
                  }, null, 8, _hoisted_11),
                  createBaseVNode("span", {
                    class: "title",
                    innerHTML: unref(control).next.text
                  }, null, 8, _hoisted_12)
                ];
              }),
              _: 1
            }, 8, ["href"])) : createCommentVNode("", true)
          ])
        ])) : createCommentVNode("", true)
      ])) : createCommentVNode("", true);
    };
  }
});
const VPDocFooter = /* @__PURE__ */ _export_sfc(_sfc_main$Q, [["__scopeId", "data-v-09de1c0f"]]);
const _withScopeId$d = (n) => (pushScopeId("data-v-39a288b8"), n = n(), popScopeId(), n);
const _hoisted_1$C = { class: "container" };
const _hoisted_2$q = /* @__PURE__ */ _withScopeId$d(() => /* @__PURE__ */ createBaseVNode("div", { class: "aside-curtain" }, null, -1));
const _hoisted_3$i = { class: "aside-container" };
const _hoisted_4$a = { class: "aside-content" };
const _hoisted_5$8 = { class: "content" };
const _hoisted_6$5 = { class: "content-container" };
const _hoisted_7$3 = { class: "main" };
const _sfc_main$P = /* @__PURE__ */ defineComponent({
  __name: "VPDoc",
  setup(__props) {
    const { theme: theme2 } = useData();
    const route = useRoute();
    const { hasSidebar, hasAside, leftAside } = useSidebar();
    const pageName = computed(
      () => route.path.replace(/[./]+/g, "_").replace(/_html$/, "")
    );
    return (_ctx, _cache) => {
      const _component_Content = resolveComponent("Content");
      return openBlock(), createElementBlock("div", {
        class: normalizeClass(["VPDoc", { "has-sidebar": unref(hasSidebar), "has-aside": unref(hasAside) }])
      }, [
        renderSlot(_ctx.$slots, "doc-top", {}, void 0, true),
        createBaseVNode("div", _hoisted_1$C, [
          unref(hasAside) ? (openBlock(), createElementBlock("div", {
            key: 0,
            class: normalizeClass(["aside", { "left-aside": unref(leftAside) }])
          }, [
            _hoisted_2$q,
            createBaseVNode("div", _hoisted_3$i, [
              createBaseVNode("div", _hoisted_4$a, [
                createVNode(VPDocAside, null, {
                  "aside-top": withCtx(() => [
                    renderSlot(_ctx.$slots, "aside-top", {}, void 0, true)
                  ]),
                  "aside-bottom": withCtx(() => [
                    renderSlot(_ctx.$slots, "aside-bottom", {}, void 0, true)
                  ]),
                  "aside-outline-before": withCtx(() => [
                    renderSlot(_ctx.$slots, "aside-outline-before", {}, void 0, true)
                  ]),
                  "aside-outline-after": withCtx(() => [
                    renderSlot(_ctx.$slots, "aside-outline-after", {}, void 0, true)
                  ]),
                  "aside-ads-before": withCtx(() => [
                    renderSlot(_ctx.$slots, "aside-ads-before", {}, void 0, true)
                  ]),
                  "aside-ads-after": withCtx(() => [
                    renderSlot(_ctx.$slots, "aside-ads-after", {}, void 0, true)
                  ]),
                  _: 3
                })
              ])
            ])
          ], 2)) : createCommentVNode("", true),
          createBaseVNode("div", _hoisted_5$8, [
            createBaseVNode("div", _hoisted_6$5, [
              renderSlot(_ctx.$slots, "doc-before", {}, void 0, true),
              createBaseVNode("main", _hoisted_7$3, [
                createVNode(_component_Content, {
                  class: normalizeClass(["vp-doc", [
                    pageName.value,
                    unref(theme2).externalLinkIcon && "external-link-icon-enabled"
                  ]])
                }, null, 8, ["class"])
              ]),
              createVNode(VPDocFooter, null, {
                "doc-footer-before": withCtx(() => [
                  renderSlot(_ctx.$slots, "doc-footer-before", {}, void 0, true)
                ]),
                _: 3
              }),
              renderSlot(_ctx.$slots, "doc-after", {}, void 0, true)
            ])
          ])
        ]),
        renderSlot(_ctx.$slots, "doc-bottom", {}, void 0, true)
      ], 2);
    };
  }
});
const VPDoc = /* @__PURE__ */ _export_sfc(_sfc_main$P, [["__scopeId", "data-v-39a288b8"]]);
const _sfc_main$O = /* @__PURE__ */ defineComponent({
  __name: "VPButton",
  props: {
    tag: {},
    size: { default: "medium" },
    theme: { default: "brand" },
    text: {},
    href: {},
    target: {},
    rel: {}
  },
  setup(__props) {
    const props = __props;
    const isExternal2 = computed(
      () => props.href && EXTERNAL_URL_RE.test(props.href)
    );
    const component = computed(() => {
      return props.tag || props.href ? "a" : "button";
    });
    return (_ctx, _cache) => {
      return openBlock(), createBlock(resolveDynamicComponent(component.value), {
        class: normalizeClass(["VPButton", [_ctx.size, _ctx.theme]]),
        href: _ctx.href ? unref(normalizeLink$1)(_ctx.href) : void 0,
        target: props.target ?? (isExternal2.value ? "_blank" : void 0),
        rel: props.rel ?? (isExternal2.value ? "noreferrer" : void 0)
      }, {
        default: withCtx(() => [
          createTextVNode(toDisplayString(_ctx.text), 1)
        ]),
        _: 1
      }, 8, ["class", "href", "target", "rel"]);
    };
  }
});
const VPButton = /* @__PURE__ */ _export_sfc(_sfc_main$O, [["__scopeId", "data-v-cad61b99"]]);
const _hoisted_1$B = ["src", "alt"];
const _sfc_main$N = /* @__PURE__ */ defineComponent({
  ...{ inheritAttrs: false },
  __name: "VPImage",
  props: {
    image: {},
    alt: {}
  },
  setup(__props) {
    return (_ctx, _cache) => {
      const _component_VPImage = resolveComponent("VPImage", true);
      return _ctx.image ? (openBlock(), createElementBlock(Fragment, { key: 0 }, [
        typeof _ctx.image === "string" || "src" in _ctx.image ? (openBlock(), createElementBlock("img", mergeProps({
          key: 0,
          class: "VPImage"
        }, typeof _ctx.image === "string" ? _ctx.$attrs : { ..._ctx.image, ..._ctx.$attrs }, {
          src: unref(withBase)(typeof _ctx.image === "string" ? _ctx.image : _ctx.image.src),
          alt: _ctx.alt ?? (typeof _ctx.image === "string" ? "" : _ctx.image.alt || "")
        }), null, 16, _hoisted_1$B)) : (openBlock(), createElementBlock(Fragment, { key: 1 }, [
          createVNode(_component_VPImage, mergeProps({
            class: "dark",
            image: _ctx.image.dark,
            alt: _ctx.image.alt
          }, _ctx.$attrs), null, 16, ["image", "alt"]),
          createVNode(_component_VPImage, mergeProps({
            class: "light",
            image: _ctx.image.light,
            alt: _ctx.image.alt
          }, _ctx.$attrs), null, 16, ["image", "alt"])
        ], 64))
      ], 64)) : createCommentVNode("", true);
    };
  }
});
const VPImage = /* @__PURE__ */ _export_sfc(_sfc_main$N, [["__scopeId", "data-v-8426fc1a"]]);
const _withScopeId$c = (n) => (pushScopeId("data-v-303bb580"), n = n(), popScopeId(), n);
const _hoisted_1$A = { class: "container" };
const _hoisted_2$p = { class: "main" };
const _hoisted_3$h = {
  key: 0,
  class: "name"
};
const _hoisted_4$9 = ["innerHTML"];
const _hoisted_5$7 = ["innerHTML"];
const _hoisted_6$4 = ["innerHTML"];
const _hoisted_7$2 = {
  key: 0,
  class: "actions"
};
const _hoisted_8$2 = {
  key: 0,
  class: "image"
};
const _hoisted_9 = { class: "image-container" };
const _hoisted_10 = /* @__PURE__ */ _withScopeId$c(() => /* @__PURE__ */ createBaseVNode("div", { class: "image-bg" }, null, -1));
const _sfc_main$M = /* @__PURE__ */ defineComponent({
  __name: "VPHero",
  props: {
    name: {},
    text: {},
    tagline: {},
    image: {},
    actions: {}
  },
  setup(__props) {
    const heroImageSlotExists = inject("hero-image-slot-exists");
    return (_ctx, _cache) => {
      return openBlock(), createElementBlock("div", {
        class: normalizeClass(["VPHero", { "has-image": _ctx.image || unref(heroImageSlotExists) }])
      }, [
        createBaseVNode("div", _hoisted_1$A, [
          createBaseVNode("div", _hoisted_2$p, [
            renderSlot(_ctx.$slots, "home-hero-info-before", {}, void 0, true),
            renderSlot(_ctx.$slots, "home-hero-info", {}, () => [
              _ctx.name ? (openBlock(), createElementBlock("h1", _hoisted_3$h, [
                createBaseVNode("span", {
                  innerHTML: _ctx.name,
                  class: "clip"
                }, null, 8, _hoisted_4$9)
              ])) : createCommentVNode("", true),
              _ctx.text ? (openBlock(), createElementBlock("p", {
                key: 1,
                innerHTML: _ctx.text,
                class: "text"
              }, null, 8, _hoisted_5$7)) : createCommentVNode("", true),
              _ctx.tagline ? (openBlock(), createElementBlock("p", {
                key: 2,
                innerHTML: _ctx.tagline,
                class: "tagline"
              }, null, 8, _hoisted_6$4)) : createCommentVNode("", true)
            ], true),
            renderSlot(_ctx.$slots, "home-hero-info-after", {}, void 0, true),
            _ctx.actions ? (openBlock(), createElementBlock("div", _hoisted_7$2, [
              (openBlock(true), createElementBlock(Fragment, null, renderList(_ctx.actions, (action) => {
                return openBlock(), createElementBlock("div", {
                  key: action.link,
                  class: "action"
                }, [
                  createVNode(VPButton, {
                    tag: "a",
                    size: "medium",
                    theme: action.theme,
                    text: action.text,
                    href: action.link,
                    target: action.target,
                    rel: action.rel
                  }, null, 8, ["theme", "text", "href", "target", "rel"])
                ]);
              }), 128))
            ])) : createCommentVNode("", true),
            renderSlot(_ctx.$slots, "home-hero-actions-after", {}, void 0, true)
          ]),
          _ctx.image || unref(heroImageSlotExists) ? (openBlock(), createElementBlock("div", _hoisted_8$2, [
            createBaseVNode("div", _hoisted_9, [
              _hoisted_10,
              renderSlot(_ctx.$slots, "home-hero-image", {}, () => [
                _ctx.image ? (openBlock(), createBlock(VPImage, {
                  key: 0,
                  class: "image-src",
                  image: _ctx.image
                }, null, 8, ["image"])) : createCommentVNode("", true)
              ], true)
            ])
          ])) : createCommentVNode("", true)
        ])
      ], 2);
    };
  }
});
const VPHero = /* @__PURE__ */ _export_sfc(_sfc_main$M, [["__scopeId", "data-v-303bb580"]]);
const _sfc_main$L = /* @__PURE__ */ defineComponent({
  __name: "VPHomeHero",
  setup(__props) {
    const { frontmatter: fm } = useData();
    return (_ctx, _cache) => {
      return unref(fm).hero ? (openBlock(), createBlock(VPHero, {
        key: 0,
        class: "VPHomeHero",
        name: unref(fm).hero.name,
        text: unref(fm).hero.text,
        tagline: unref(fm).hero.tagline,
        image: unref(fm).hero.image,
        actions: unref(fm).hero.actions
      }, {
        "home-hero-info-before": withCtx(() => [
          renderSlot(_ctx.$slots, "home-hero-info-before")
        ]),
        "home-hero-info": withCtx(() => [
          renderSlot(_ctx.$slots, "home-hero-info")
        ]),
        "home-hero-info-after": withCtx(() => [
          renderSlot(_ctx.$slots, "home-hero-info-after")
        ]),
        "home-hero-actions-after": withCtx(() => [
          renderSlot(_ctx.$slots, "home-hero-actions-after")
        ]),
        "home-hero-image": withCtx(() => [
          renderSlot(_ctx.$slots, "home-hero-image")
        ]),
        _: 3
      }, 8, ["name", "text", "tagline", "image", "actions"])) : createCommentVNode("", true);
    };
  }
});
const _withScopeId$b = (n) => (pushScopeId("data-v-a3976bdc"), n = n(), popScopeId(), n);
const _hoisted_1$z = { class: "box" };
const _hoisted_2$o = {
  key: 0,
  class: "icon"
};
const _hoisted_3$g = ["innerHTML"];
const _hoisted_4$8 = ["innerHTML"];
const _hoisted_5$6 = ["innerHTML"];
const _hoisted_6$3 = {
  key: 4,
  class: "link-text"
};
const _hoisted_7$1 = { class: "link-text-value" };
const _hoisted_8$1 = /* @__PURE__ */ _withScopeId$b(() => /* @__PURE__ */ createBaseVNode("span", { class: "vpi-arrow-right link-text-icon" }, null, -1));
const _sfc_main$K = /* @__PURE__ */ defineComponent({
  __name: "VPFeature",
  props: {
    icon: {},
    title: {},
    details: {},
    link: {},
    linkText: {},
    rel: {},
    target: {}
  },
  setup(__props) {
    return (_ctx, _cache) => {
      return openBlock(), createBlock(_sfc_main$S, {
        class: "VPFeature",
        href: _ctx.link,
        rel: _ctx.rel,
        target: _ctx.target,
        "no-icon": true,
        tag: _ctx.link ? "a" : "div"
      }, {
        default: withCtx(() => [
          createBaseVNode("article", _hoisted_1$z, [
            typeof _ctx.icon === "object" && _ctx.icon.wrap ? (openBlock(), createElementBlock("div", _hoisted_2$o, [
              createVNode(VPImage, {
                image: _ctx.icon,
                alt: _ctx.icon.alt,
                height: _ctx.icon.height || 48,
                width: _ctx.icon.width || 48
              }, null, 8, ["image", "alt", "height", "width"])
            ])) : typeof _ctx.icon === "object" ? (openBlock(), createBlock(VPImage, {
              key: 1,
              image: _ctx.icon,
              alt: _ctx.icon.alt,
              height: _ctx.icon.height || 48,
              width: _ctx.icon.width || 48
            }, null, 8, ["image", "alt", "height", "width"])) : _ctx.icon ? (openBlock(), createElementBlock("div", {
              key: 2,
              class: "icon",
              innerHTML: _ctx.icon
            }, null, 8, _hoisted_3$g)) : createCommentVNode("", true),
            createBaseVNode("h2", {
              class: "title",
              innerHTML: _ctx.title
            }, null, 8, _hoisted_4$8),
            _ctx.details ? (openBlock(), createElementBlock("p", {
              key: 3,
              class: "details",
              innerHTML: _ctx.details
            }, null, 8, _hoisted_5$6)) : createCommentVNode("", true),
            _ctx.linkText ? (openBlock(), createElementBlock("div", _hoisted_6$3, [
              createBaseVNode("p", _hoisted_7$1, [
                createTextVNode(toDisplayString(_ctx.linkText) + " ", 1),
                _hoisted_8$1
              ])
            ])) : createCommentVNode("", true)
          ])
        ]),
        _: 1
      }, 8, ["href", "rel", "target", "tag"]);
    };
  }
});
const VPFeature = /* @__PURE__ */ _export_sfc(_sfc_main$K, [["__scopeId", "data-v-a3976bdc"]]);
const _hoisted_1$y = {
  key: 0,
  class: "VPFeatures"
};
const _hoisted_2$n = { class: "container" };
const _hoisted_3$f = { class: "items" };
const _sfc_main$J = /* @__PURE__ */ defineComponent({
  __name: "VPFeatures",
  props: {
    features: {}
  },
  setup(__props) {
    const props = __props;
    const grid = computed(() => {
      const length = props.features.length;
      if (!length) {
        return;
      } else if (length === 2) {
        return "grid-2";
      } else if (length === 3) {
        return "grid-3";
      } else if (length % 3 === 0) {
        return "grid-6";
      } else if (length > 3) {
        return "grid-4";
      }
    });
    return (_ctx, _cache) => {
      return _ctx.features ? (openBlock(), createElementBlock("div", _hoisted_1$y, [
        createBaseVNode("div", _hoisted_2$n, [
          createBaseVNode("div", _hoisted_3$f, [
            (openBlock(true), createElementBlock(Fragment, null, renderList(_ctx.features, (feature) => {
              return openBlock(), createElementBlock("div", {
                key: feature.title,
                class: normalizeClass(["item", [grid.value]])
              }, [
                createVNode(VPFeature, {
                  icon: feature.icon,
                  title: feature.title,
                  details: feature.details,
                  link: feature.link,
                  "link-text": feature.linkText,
                  rel: feature.rel,
                  target: feature.target
                }, null, 8, ["icon", "title", "details", "link", "link-text", "rel", "target"])
              ], 2);
            }), 128))
          ])
        ])
      ])) : createCommentVNode("", true);
    };
  }
});
const VPFeatures = /* @__PURE__ */ _export_sfc(_sfc_main$J, [["__scopeId", "data-v-a6181336"]]);
const _sfc_main$I = /* @__PURE__ */ defineComponent({
  __name: "VPHomeFeatures",
  setup(__props) {
    const { frontmatter: fm } = useData();
    return (_ctx, _cache) => {
      return unref(fm).features ? (openBlock(), createBlock(VPFeatures, {
        key: 0,
        class: "VPHomeFeatures",
        features: unref(fm).features
      }, null, 8, ["features"])) : createCommentVNode("", true);
    };
  }
});
const _sfc_main$H = /* @__PURE__ */ defineComponent({
  __name: "VPHomeContent",
  setup(__props) {
    const { width: vw } = useWindowSize({ includeScrollbar: false });
    return (_ctx, _cache) => {
      return openBlock(), createElementBlock("div", {
        class: "vp-doc container",
        style: normalizeStyle(unref(vw) ? { "--vp-offset": `calc(50% - ${unref(vw) / 2}px)` } : {})
      }, [
        renderSlot(_ctx.$slots, "default", {}, void 0, true)
      ], 4);
    };
  }
});
const VPHomeContent = /* @__PURE__ */ _export_sfc(_sfc_main$H, [["__scopeId", "data-v-82d4af08"]]);
const _hoisted_1$x = { class: "VPHome" };
const _sfc_main$G = /* @__PURE__ */ defineComponent({
  __name: "VPHome",
  setup(__props) {
    const { frontmatter } = useData();
    return (_ctx, _cache) => {
      const _component_Content = resolveComponent("Content");
      return openBlock(), createElementBlock("div", _hoisted_1$x, [
        renderSlot(_ctx.$slots, "home-hero-before", {}, void 0, true),
        createVNode(_sfc_main$L, null, {
          "home-hero-info-before": withCtx(() => [
            renderSlot(_ctx.$slots, "home-hero-info-before", {}, void 0, true)
          ]),
          "home-hero-info": withCtx(() => [
            renderSlot(_ctx.$slots, "home-hero-info", {}, void 0, true)
          ]),
          "home-hero-info-after": withCtx(() => [
            renderSlot(_ctx.$slots, "home-hero-info-after", {}, void 0, true)
          ]),
          "home-hero-actions-after": withCtx(() => [
            renderSlot(_ctx.$slots, "home-hero-actions-after", {}, void 0, true)
          ]),
          "home-hero-image": withCtx(() => [
            renderSlot(_ctx.$slots, "home-hero-image", {}, void 0, true)
          ]),
          _: 3
        }),
        renderSlot(_ctx.$slots, "home-hero-after", {}, void 0, true),
        renderSlot(_ctx.$slots, "home-features-before", {}, void 0, true),
        createVNode(_sfc_main$I),
        renderSlot(_ctx.$slots, "home-features-after", {}, void 0, true),
        unref(frontmatter).markdownStyles !== false ? (openBlock(), createBlock(VPHomeContent, { key: 0 }, {
          default: withCtx(() => [
            createVNode(_component_Content)
          ]),
          _: 1
        })) : (openBlock(), createBlock(_component_Content, { key: 1 }))
      ]);
    };
  }
});
const VPHome = /* @__PURE__ */ _export_sfc(_sfc_main$G, [["__scopeId", "data-v-686f80a6"]]);
const _sfc_main$F = {};
const _hoisted_1$w = { class: "VPPage" };
function _sfc_render$1(_ctx, _cache) {
  const _component_Content = resolveComponent("Content");
  return openBlock(), createElementBlock("div", _hoisted_1$w, [
    renderSlot(_ctx.$slots, "page-top"),
    createVNode(_component_Content),
    renderSlot(_ctx.$slots, "page-bottom")
  ]);
}
const VPPage = /* @__PURE__ */ _export_sfc(_sfc_main$F, [["render", _sfc_render$1]]);
const _sfc_main$E = /* @__PURE__ */ defineComponent({
  __name: "VPContent",
  setup(__props) {
    const { page, frontmatter } = useData();
    const { hasSidebar } = useSidebar();
    return (_ctx, _cache) => {
      return openBlock(), createElementBlock("div", {
        class: normalizeClass(["VPContent", {
          "has-sidebar": unref(hasSidebar),
          "is-home": unref(frontmatter).layout === "home"
        }]),
        id: "VPContent"
      }, [
        unref(page).isNotFound ? renderSlot(_ctx.$slots, "not-found", { key: 0 }, () => [
          createVNode(NotFound)
        ], true) : unref(frontmatter).layout === "page" ? (openBlock(), createBlock(VPPage, { key: 1 }, {
          "page-top": withCtx(() => [
            renderSlot(_ctx.$slots, "page-top", {}, void 0, true)
          ]),
          "page-bottom": withCtx(() => [
            renderSlot(_ctx.$slots, "page-bottom", {}, void 0, true)
          ]),
          _: 3
        })) : unref(frontmatter).layout === "home" ? (openBlock(), createBlock(VPHome, { key: 2 }, {
          "home-hero-before": withCtx(() => [
            renderSlot(_ctx.$slots, "home-hero-before", {}, void 0, true)
          ]),
          "home-hero-info-before": withCtx(() => [
            renderSlot(_ctx.$slots, "home-hero-info-before", {}, void 0, true)
          ]),
          "home-hero-info": withCtx(() => [
            renderSlot(_ctx.$slots, "home-hero-info", {}, void 0, true)
          ]),
          "home-hero-info-after": withCtx(() => [
            renderSlot(_ctx.$slots, "home-hero-info-after", {}, void 0, true)
          ]),
          "home-hero-actions-after": withCtx(() => [
            renderSlot(_ctx.$slots, "home-hero-actions-after", {}, void 0, true)
          ]),
          "home-hero-image": withCtx(() => [
            renderSlot(_ctx.$slots, "home-hero-image", {}, void 0, true)
          ]),
          "home-hero-after": withCtx(() => [
            renderSlot(_ctx.$slots, "home-hero-after", {}, void 0, true)
          ]),
          "home-features-before": withCtx(() => [
            renderSlot(_ctx.$slots, "home-features-before", {}, void 0, true)
          ]),
          "home-features-after": withCtx(() => [
            renderSlot(_ctx.$slots, "home-features-after", {}, void 0, true)
          ]),
          _: 3
        })) : unref(frontmatter).layout && unref(frontmatter).layout !== "doc" ? (openBlock(), createBlock(resolveDynamicComponent(unref(frontmatter).layout), { key: 3 })) : (openBlock(), createBlock(VPDoc, { key: 4 }, {
          "doc-top": withCtx(() => [
            renderSlot(_ctx.$slots, "doc-top", {}, void 0, true)
          ]),
          "doc-bottom": withCtx(() => [
            renderSlot(_ctx.$slots, "doc-bottom", {}, void 0, true)
          ]),
          "doc-footer-before": withCtx(() => [
            renderSlot(_ctx.$slots, "doc-footer-before", {}, void 0, true)
          ]),
          "doc-before": withCtx(() => [
            renderSlot(_ctx.$slots, "doc-before", {}, void 0, true)
          ]),
          "doc-after": withCtx(() => [
            renderSlot(_ctx.$slots, "doc-after", {}, void 0, true)
          ]),
          "aside-top": withCtx(() => [
            renderSlot(_ctx.$slots, "aside-top", {}, void 0, true)
          ]),
          "aside-outline-before": withCtx(() => [
            renderSlot(_ctx.$slots, "aside-outline-before", {}, void 0, true)
          ]),
          "aside-outline-after": withCtx(() => [
            renderSlot(_ctx.$slots, "aside-outline-after", {}, void 0, true)
          ]),
          "aside-ads-before": withCtx(() => [
            renderSlot(_ctx.$slots, "aside-ads-before", {}, void 0, true)
          ]),
          "aside-ads-after": withCtx(() => [
            renderSlot(_ctx.$slots, "aside-ads-after", {}, void 0, true)
          ]),
          "aside-bottom": withCtx(() => [
            renderSlot(_ctx.$slots, "aside-bottom", {}, void 0, true)
          ]),
          _: 3
        }))
      ], 2);
    };
  }
});
const VPContent = /* @__PURE__ */ _export_sfc(_sfc_main$E, [["__scopeId", "data-v-1428d186"]]);
const _hoisted_1$v = { class: "container" };
const _hoisted_2$m = ["innerHTML"];
const _hoisted_3$e = ["innerHTML"];
const _sfc_main$D = /* @__PURE__ */ defineComponent({
  __name: "VPFooter",
  setup(__props) {
    const { theme: theme2, frontmatter } = useData();
    const { hasSidebar } = useSidebar();
    return (_ctx, _cache) => {
      return unref(theme2).footer && unref(frontmatter).footer !== false ? (openBlock(), createElementBlock("footer", {
        key: 0,
        class: normalizeClass(["VPFooter", { "has-sidebar": unref(hasSidebar) }])
      }, [
        createBaseVNode("div", _hoisted_1$v, [
          unref(theme2).footer.message ? (openBlock(), createElementBlock("p", {
            key: 0,
            class: "message",
            innerHTML: unref(theme2).footer.message
          }, null, 8, _hoisted_2$m)) : createCommentVNode("", true),
          unref(theme2).footer.copyright ? (openBlock(), createElementBlock("p", {
            key: 1,
            class: "copyright",
            innerHTML: unref(theme2).footer.copyright
          }, null, 8, _hoisted_3$e)) : createCommentVNode("", true)
        ])
      ], 2)) : createCommentVNode("", true);
    };
  }
});
const VPFooter = /* @__PURE__ */ _export_sfc(_sfc_main$D, [["__scopeId", "data-v-e315a0ad"]]);
function useLocalNav() {
  const { theme: theme2, frontmatter } = useData();
  const headers = shallowRef([]);
  const hasLocalNav = computed(() => {
    return headers.value.length > 0;
  });
  onContentUpdated(() => {
    headers.value = getHeaders(frontmatter.value.outline ?? theme2.value.outline);
  });
  return {
    headers,
    hasLocalNav
  };
}
const _withScopeId$a = (n) => (pushScopeId("data-v-267dd0ed"), n = n(), popScopeId(), n);
const _hoisted_1$u = { class: "menu-text" };
const _hoisted_2$l = /* @__PURE__ */ _withScopeId$a(() => /* @__PURE__ */ createBaseVNode("span", { class: "vpi-chevron-right icon" }, null, -1));
const _hoisted_3$d = { class: "header" };
const _hoisted_4$7 = { class: "outline" };
const _sfc_main$C = /* @__PURE__ */ defineComponent({
  __name: "VPLocalNavOutlineDropdown",
  props: {
    headers: {},
    navHeight: {}
  },
  setup(__props) {
    const props = __props;
    const { theme: theme2 } = useData();
    const open = ref(false);
    const vh = ref(0);
    const main = ref();
    const items = ref();
    onClickOutside(main, () => {
      open.value = false;
    });
    onKeyStroke("Escape", () => {
      open.value = false;
    });
    onContentUpdated(() => {
      open.value = false;
    });
    function toggle() {
      open.value = !open.value;
      vh.value = window.innerHeight + Math.min(window.scrollY - props.navHeight, 0);
    }
    function onItemClick(e) {
      if (e.target.classList.contains("outline-link")) {
        if (items.value) {
          items.value.style.transition = "none";
        }
        nextTick(() => {
          open.value = false;
        });
      }
    }
    function scrollToTop() {
      open.value = false;
      window.scrollTo({ top: 0, left: 0, behavior: "smooth" });
    }
    return (_ctx, _cache) => {
      return openBlock(), createElementBlock("div", {
        class: "VPLocalNavOutlineDropdown",
        style: normalizeStyle({ "--vp-vh": vh.value + "px" }),
        ref_key: "main",
        ref: main
      }, [
        _ctx.headers.length > 0 ? (openBlock(), createElementBlock("button", {
          key: 0,
          onClick: toggle,
          class: normalizeClass({ open: open.value })
        }, [
          createBaseVNode("span", _hoisted_1$u, toDisplayString(unref(resolveTitle)(unref(theme2))), 1),
          _hoisted_2$l
        ], 2)) : (openBlock(), createElementBlock("button", {
          key: 1,
          onClick: scrollToTop
        }, toDisplayString(unref(theme2).returnToTopLabel || "Return to top"), 1)),
        createVNode(Transition, { name: "flyout" }, {
          default: withCtx(() => [
            open.value ? (openBlock(), createElementBlock("div", {
              key: 0,
              ref_key: "items",
              ref: items,
              class: "items",
              onClick: onItemClick
            }, [
              createBaseVNode("div", _hoisted_3$d, [
                createBaseVNode("a", {
                  class: "top-link",
                  href: "#",
                  onClick: scrollToTop
                }, toDisplayString(unref(theme2).returnToTopLabel || "Return to top"), 1)
              ]),
              createBaseVNode("div", _hoisted_4$7, [
                createVNode(VPDocOutlineItem, { headers: _ctx.headers }, null, 8, ["headers"])
              ])
            ], 512)) : createCommentVNode("", true)
          ]),
          _: 1
        })
      ], 4);
    };
  }
});
const VPLocalNavOutlineDropdown = /* @__PURE__ */ _export_sfc(_sfc_main$C, [["__scopeId", "data-v-267dd0ed"]]);
const _withScopeId$9 = (n) => (pushScopeId("data-v-a6f0e41e"), n = n(), popScopeId(), n);
const _hoisted_1$t = { class: "container" };
const _hoisted_2$k = ["aria-expanded"];
const _hoisted_3$c = /* @__PURE__ */ _withScopeId$9(() => /* @__PURE__ */ createBaseVNode("span", { class: "vpi-align-left menu-icon" }, null, -1));
const _hoisted_4$6 = { class: "menu-text" };
const _sfc_main$B = /* @__PURE__ */ defineComponent({
  __name: "VPLocalNav",
  props: {
    open: { type: Boolean }
  },
  emits: ["open-menu"],
  setup(__props) {
    const { theme: theme2, frontmatter } = useData();
    const { hasSidebar } = useSidebar();
    const { headers } = useLocalNav();
    const { y } = useWindowScroll();
    const navHeight = ref(0);
    onMounted(() => {
      navHeight.value = parseInt(
        getComputedStyle(document.documentElement).getPropertyValue(
          "--vp-nav-height"
        )
      );
    });
    onContentUpdated(() => {
      headers.value = getHeaders(frontmatter.value.outline ?? theme2.value.outline);
    });
    const empty = computed(() => {
      return headers.value.length === 0;
    });
    const emptyAndNoSidebar = computed(() => {
      return empty.value && !hasSidebar.value;
    });
    const classes = computed(() => {
      return {
        VPLocalNav: true,
        "has-sidebar": hasSidebar.value,
        empty: empty.value,
        fixed: emptyAndNoSidebar.value
      };
    });
    return (_ctx, _cache) => {
      return unref(frontmatter).layout !== "home" && (!emptyAndNoSidebar.value || unref(y) >= navHeight.value) ? (openBlock(), createElementBlock("div", {
        key: 0,
        class: normalizeClass(classes.value)
      }, [
        createBaseVNode("div", _hoisted_1$t, [
          unref(hasSidebar) ? (openBlock(), createElementBlock("button", {
            key: 0,
            class: "menu",
            "aria-expanded": _ctx.open,
            "aria-controls": "VPSidebarNav",
            onClick: _cache[0] || (_cache[0] = ($event) => _ctx.$emit("open-menu"))
          }, [
            _hoisted_3$c,
            createBaseVNode("span", _hoisted_4$6, toDisplayString(unref(theme2).sidebarMenuLabel || "Menu"), 1)
          ], 8, _hoisted_2$k)) : createCommentVNode("", true),
          createVNode(VPLocalNavOutlineDropdown, {
            headers: unref(headers),
            navHeight: navHeight.value
          }, null, 8, ["headers", "navHeight"])
        ])
      ], 2)) : createCommentVNode("", true);
    };
  }
});
const VPLocalNav = /* @__PURE__ */ _export_sfc(_sfc_main$B, [["__scopeId", "data-v-a6f0e41e"]]);
function useNav() {
  const isScreenOpen = ref(false);
  function openScreen() {
    isScreenOpen.value = true;
    window.addEventListener("resize", closeScreenOnTabletWindow);
  }
  function closeScreen() {
    isScreenOpen.value = false;
    window.removeEventListener("resize", closeScreenOnTabletWindow);
  }
  function toggleScreen() {
    isScreenOpen.value ? closeScreen() : openScreen();
  }
  function closeScreenOnTabletWindow() {
    window.outerWidth >= 768 && closeScreen();
  }
  const route = useRoute();
  watch(() => route.path, closeScreen);
  return {
    isScreenOpen,
    openScreen,
    closeScreen,
    toggleScreen
  };
}
const _sfc_main$A = {};
const _hoisted_1$s = {
  class: "VPSwitch",
  type: "button",
  role: "switch"
};
const _hoisted_2$j = { class: "check" };
const _hoisted_3$b = {
  key: 0,
  class: "icon"
};
function _sfc_render(_ctx, _cache) {
  return openBlock(), createElementBlock("button", _hoisted_1$s, [
    createBaseVNode("span", _hoisted_2$j, [
      _ctx.$slots.default ? (openBlock(), createElementBlock("span", _hoisted_3$b, [
        renderSlot(_ctx.$slots, "default", {}, void 0, true)
      ])) : createCommentVNode("", true)
    ])
  ]);
}
const VPSwitch = /* @__PURE__ */ _export_sfc(_sfc_main$A, [["render", _sfc_render], ["__scopeId", "data-v-1d5665e3"]]);
const _withScopeId$8 = (n) => (pushScopeId("data-v-d1f28634"), n = n(), popScopeId(), n);
const _hoisted_1$r = /* @__PURE__ */ _withScopeId$8(() => /* @__PURE__ */ createBaseVNode("span", { class: "vpi-sun sun" }, null, -1));
const _hoisted_2$i = /* @__PURE__ */ _withScopeId$8(() => /* @__PURE__ */ createBaseVNode("span", { class: "vpi-moon moon" }, null, -1));
const _sfc_main$z = /* @__PURE__ */ defineComponent({
  __name: "VPSwitchAppearance",
  setup(__props) {
    const { isDark, theme: theme2 } = useData();
    const toggleAppearance = inject("toggle-appearance", () => {
      isDark.value = !isDark.value;
    });
    const switchTitle = computed(() => {
      return isDark.value ? theme2.value.lightModeSwitchTitle || "Switch to light theme" : theme2.value.darkModeSwitchTitle || "Switch to dark theme";
    });
    return (_ctx, _cache) => {
      return openBlock(), createBlock(VPSwitch, {
        title: switchTitle.value,
        class: "VPSwitchAppearance",
        "aria-checked": unref(isDark),
        onClick: unref(toggleAppearance)
      }, {
        default: withCtx(() => [
          _hoisted_1$r,
          _hoisted_2$i
        ]),
        _: 1
      }, 8, ["title", "aria-checked", "onClick"]);
    };
  }
});
const VPSwitchAppearance = /* @__PURE__ */ _export_sfc(_sfc_main$z, [["__scopeId", "data-v-d1f28634"]]);
const _hoisted_1$q = {
  key: 0,
  class: "VPNavBarAppearance"
};
const _sfc_main$y = /* @__PURE__ */ defineComponent({
  __name: "VPNavBarAppearance",
  setup(__props) {
    const { site } = useData();
    return (_ctx, _cache) => {
      return unref(site).appearance && unref(site).appearance !== "force-dark" ? (openBlock(), createElementBlock("div", _hoisted_1$q, [
        createVNode(VPSwitchAppearance)
      ])) : createCommentVNode("", true);
    };
  }
});
const VPNavBarAppearance = /* @__PURE__ */ _export_sfc(_sfc_main$y, [["__scopeId", "data-v-e6aabb21"]]);
const focusedElement = ref();
let active = false;
let listeners = 0;
function useFlyout(options) {
  const focus = ref(false);
  if (inBrowser) {
    !active && activateFocusTracking();
    listeners++;
    const unwatch = watch(focusedElement, (el) => {
      var _a, _b, _c;
      if (el === options.el.value || ((_a = options.el.value) == null ? void 0 : _a.contains(el))) {
        focus.value = true;
        (_b = options.onFocus) == null ? void 0 : _b.call(options);
      } else {
        focus.value = false;
        (_c = options.onBlur) == null ? void 0 : _c.call(options);
      }
    });
    onUnmounted(() => {
      unwatch();
      listeners--;
      if (!listeners) {
        deactivateFocusTracking();
      }
    });
  }
  return readonly(focus);
}
function activateFocusTracking() {
  document.addEventListener("focusin", handleFocusIn);
  active = true;
  focusedElement.value = document.activeElement;
}
function deactivateFocusTracking() {
  document.removeEventListener("focusin", handleFocusIn);
}
function handleFocusIn() {
  focusedElement.value = document.activeElement;
}
const _hoisted_1$p = { class: "VPMenuLink" };
const _sfc_main$x = /* @__PURE__ */ defineComponent({
  __name: "VPMenuLink",
  props: {
    item: {}
  },
  setup(__props) {
    const { page } = useData();
    return (_ctx, _cache) => {
      return openBlock(), createElementBlock("div", _hoisted_1$p, [
        createVNode(_sfc_main$S, {
          class: normalizeClass({ active: unref(isActive)(unref(page).relativePath, _ctx.item.activeMatch || _ctx.item.link, !!_ctx.item.activeMatch) }),
          href: _ctx.item.link,
          target: _ctx.item.target,
          rel: _ctx.item.rel
        }, {
          default: withCtx(() => [
            createTextVNode(toDisplayString(_ctx.item.text), 1)
          ]),
          _: 1
        }, 8, ["class", "href", "target", "rel"])
      ]);
    };
  }
});
const VPMenuLink = /* @__PURE__ */ _export_sfc(_sfc_main$x, [["__scopeId", "data-v-43f1e123"]]);
const _hoisted_1$o = { class: "VPMenuGroup" };
const _hoisted_2$h = {
  key: 0,
  class: "title"
};
const _sfc_main$w = /* @__PURE__ */ defineComponent({
  __name: "VPMenuGroup",
  props: {
    text: {},
    items: {}
  },
  setup(__props) {
    return (_ctx, _cache) => {
      return openBlock(), createElementBlock("div", _hoisted_1$o, [
        _ctx.text ? (openBlock(), createElementBlock("p", _hoisted_2$h, toDisplayString(_ctx.text), 1)) : createCommentVNode("", true),
        (openBlock(true), createElementBlock(Fragment, null, renderList(_ctx.items, (item) => {
          return openBlock(), createElementBlock(Fragment, null, [
            "link" in item ? (openBlock(), createBlock(VPMenuLink, {
              key: 0,
              item
            }, null, 8, ["item"])) : createCommentVNode("", true)
          ], 64);
        }), 256))
      ]);
    };
  }
});
const VPMenuGroup = /* @__PURE__ */ _export_sfc(_sfc_main$w, [["__scopeId", "data-v-69e747b5"]]);
const _hoisted_1$n = { class: "VPMenu" };
const _hoisted_2$g = {
  key: 0,
  class: "items"
};
const _sfc_main$v = /* @__PURE__ */ defineComponent({
  __name: "VPMenu",
  props: {
    items: {}
  },
  setup(__props) {
    return (_ctx, _cache) => {
      return openBlock(), createElementBlock("div", _hoisted_1$n, [
        _ctx.items ? (openBlock(), createElementBlock("div", _hoisted_2$g, [
          (openBlock(true), createElementBlock(Fragment, null, renderList(_ctx.items, (item) => {
            return openBlock(), createElementBlock(Fragment, {
              key: item.text
            }, [
              "link" in item ? (openBlock(), createBlock(VPMenuLink, {
                key: 0,
                item
              }, null, 8, ["item"])) : (openBlock(), createBlock(VPMenuGroup, {
                key: 1,
                text: item.text,
                items: item.items
              }, null, 8, ["text", "items"]))
            ], 64);
          }), 128))
        ])) : createCommentVNode("", true),
        renderSlot(_ctx.$slots, "default", {}, void 0, true)
      ]);
    };
  }
});
const VPMenu = /* @__PURE__ */ _export_sfc(_sfc_main$v, [["__scopeId", "data-v-e7ea1737"]]);
const _withScopeId$7 = (n) => (pushScopeId("data-v-b6c34ac9"), n = n(), popScopeId(), n);
const _hoisted_1$m = ["aria-expanded", "aria-label"];
const _hoisted_2$f = {
  key: 0,
  class: "text"
};
const _hoisted_3$a = ["innerHTML"];
const _hoisted_4$5 = /* @__PURE__ */ _withScopeId$7(() => /* @__PURE__ */ createBaseVNode("span", { class: "vpi-chevron-down text-icon" }, null, -1));
const _hoisted_5$5 = {
  key: 1,
  class: "vpi-more-horizontal icon"
};
const _hoisted_6$2 = { class: "menu" };
const _sfc_main$u = /* @__PURE__ */ defineComponent({
  __name: "VPFlyout",
  props: {
    icon: {},
    button: {},
    label: {},
    items: {}
  },
  setup(__props) {
    const open = ref(false);
    const el = ref();
    useFlyout({ el, onBlur });
    function onBlur() {
      open.value = false;
    }
    return (_ctx, _cache) => {
      return openBlock(), createElementBlock("div", {
        class: "VPFlyout",
        ref_key: "el",
        ref: el,
        onMouseenter: _cache[1] || (_cache[1] = ($event) => open.value = true),
        onMouseleave: _cache[2] || (_cache[2] = ($event) => open.value = false)
      }, [
        createBaseVNode("button", {
          type: "button",
          class: "button",
          "aria-haspopup": "true",
          "aria-expanded": open.value,
          "aria-label": _ctx.label,
          onClick: _cache[0] || (_cache[0] = ($event) => open.value = !open.value)
        }, [
          _ctx.button || _ctx.icon ? (openBlock(), createElementBlock("span", _hoisted_2$f, [
            _ctx.icon ? (openBlock(), createElementBlock("span", {
              key: 0,
              class: normalizeClass([_ctx.icon, "option-icon"])
            }, null, 2)) : createCommentVNode("", true),
            _ctx.button ? (openBlock(), createElementBlock("span", {
              key: 1,
              innerHTML: _ctx.button
            }, null, 8, _hoisted_3$a)) : createCommentVNode("", true),
            _hoisted_4$5
          ])) : (openBlock(), createElementBlock("span", _hoisted_5$5))
        ], 8, _hoisted_1$m),
        createBaseVNode("div", _hoisted_6$2, [
          createVNode(VPMenu, { items: _ctx.items }, {
            default: withCtx(() => [
              renderSlot(_ctx.$slots, "default", {}, void 0, true)
            ]),
            _: 3
          }, 8, ["items"])
        ])
      ], 544);
    };
  }
});
const VPFlyout = /* @__PURE__ */ _export_sfc(_sfc_main$u, [["__scopeId", "data-v-b6c34ac9"]]);
const _hoisted_1$l = ["href", "aria-label", "innerHTML"];
const _sfc_main$t = /* @__PURE__ */ defineComponent({
  __name: "VPSocialLink",
  props: {
    icon: {},
    link: {},
    ariaLabel: {}
  },
  setup(__props) {
    const props = __props;
    const svg = computed(() => {
      if (typeof props.icon === "object") return props.icon.svg;
      return `<span class="vpi-social-${props.icon}" />`;
    });
    return (_ctx, _cache) => {
      return openBlock(), createElementBlock("a", {
        class: "VPSocialLink no-icon",
        href: _ctx.link,
        "aria-label": _ctx.ariaLabel ?? (typeof _ctx.icon === "string" ? _ctx.icon : ""),
        target: "_blank",
        rel: "noopener",
        innerHTML: svg.value
      }, null, 8, _hoisted_1$l);
    };
  }
});
const VPSocialLink = /* @__PURE__ */ _export_sfc(_sfc_main$t, [["__scopeId", "data-v-eee4e7cb"]]);
const _hoisted_1$k = { class: "VPSocialLinks" };
const _sfc_main$s = /* @__PURE__ */ defineComponent({
  __name: "VPSocialLinks",
  props: {
    links: {}
  },
  setup(__props) {
    return (_ctx, _cache) => {
      return openBlock(), createElementBlock("div", _hoisted_1$k, [
        (openBlock(true), createElementBlock(Fragment, null, renderList(_ctx.links, ({ link, icon, ariaLabel }) => {
          return openBlock(), createBlock(VPSocialLink, {
            key: link,
            icon,
            link,
            ariaLabel
          }, null, 8, ["icon", "link", "ariaLabel"]);
        }), 128))
      ]);
    };
  }
});
const VPSocialLinks = /* @__PURE__ */ _export_sfc(_sfc_main$s, [["__scopeId", "data-v-7bc22406"]]);
const _hoisted_1$j = {
  key: 0,
  class: "group translations"
};
const _hoisted_2$e = { class: "trans-title" };
const _hoisted_3$9 = {
  key: 1,
  class: "group"
};
const _hoisted_4$4 = { class: "item appearance" };
const _hoisted_5$4 = { class: "label" };
const _hoisted_6$1 = { class: "appearance-action" };
const _hoisted_7 = {
  key: 2,
  class: "group"
};
const _hoisted_8 = { class: "item social-links" };
const _sfc_main$r = /* @__PURE__ */ defineComponent({
  __name: "VPNavBarExtra",
  setup(__props) {
    const { site, theme: theme2 } = useData();
    const { localeLinks, currentLang } = useLangs({ correspondingLink: true });
    const hasExtraContent = computed(
      () => localeLinks.value.length && currentLang.value.label || site.value.appearance || theme2.value.socialLinks
    );
    return (_ctx, _cache) => {
      return hasExtraContent.value ? (openBlock(), createBlock(VPFlyout, {
        key: 0,
        class: "VPNavBarExtra",
        label: "extra navigation"
      }, {
        default: withCtx(() => [
          unref(localeLinks).length && unref(currentLang).label ? (openBlock(), createElementBlock("div", _hoisted_1$j, [
            createBaseVNode("p", _hoisted_2$e, toDisplayString(unref(currentLang).label), 1),
            (openBlock(true), createElementBlock(Fragment, null, renderList(unref(localeLinks), (locale) => {
              return openBlock(), createBlock(VPMenuLink, {
                key: locale.link,
                item: locale
              }, null, 8, ["item"]);
            }), 128))
          ])) : createCommentVNode("", true),
          unref(site).appearance && unref(site).appearance !== "force-dark" ? (openBlock(), createElementBlock("div", _hoisted_3$9, [
            createBaseVNode("div", _hoisted_4$4, [
              createBaseVNode("p", _hoisted_5$4, toDisplayString(unref(theme2).darkModeSwitchLabel || "Appearance"), 1),
              createBaseVNode("div", _hoisted_6$1, [
                createVNode(VPSwitchAppearance)
              ])
            ])
          ])) : createCommentVNode("", true),
          unref(theme2).socialLinks ? (openBlock(), createElementBlock("div", _hoisted_7, [
            createBaseVNode("div", _hoisted_8, [
              createVNode(VPSocialLinks, {
                class: "social-links-list",
                links: unref(theme2).socialLinks
              }, null, 8, ["links"])
            ])
          ])) : createCommentVNode("", true)
        ]),
        _: 1
      })) : createCommentVNode("", true);
    };
  }
});
const VPNavBarExtra = /* @__PURE__ */ _export_sfc(_sfc_main$r, [["__scopeId", "data-v-d0bd9dde"]]);
const _withScopeId$6 = (n) => (pushScopeId("data-v-e5dd9c1c"), n = n(), popScopeId(), n);
const _hoisted_1$i = ["aria-expanded"];
const _hoisted_2$d = /* @__PURE__ */ _withScopeId$6(() => /* @__PURE__ */ createBaseVNode("span", { class: "container" }, [
  /* @__PURE__ */ createBaseVNode("span", { class: "top" }),
  /* @__PURE__ */ createBaseVNode("span", { class: "middle" }),
  /* @__PURE__ */ createBaseVNode("span", { class: "bottom" })
], -1));
const _hoisted_3$8 = [
  _hoisted_2$d
];
const _sfc_main$q = /* @__PURE__ */ defineComponent({
  __name: "VPNavBarHamburger",
  props: {
    active: { type: Boolean }
  },
  emits: ["click"],
  setup(__props) {
    return (_ctx, _cache) => {
      return openBlock(), createElementBlock("button", {
        type: "button",
        class: normalizeClass(["VPNavBarHamburger", { active: _ctx.active }]),
        "aria-label": "mobile navigation",
        "aria-expanded": _ctx.active,
        "aria-controls": "VPNavScreen",
        onClick: _cache[0] || (_cache[0] = ($event) => _ctx.$emit("click"))
      }, _hoisted_3$8, 10, _hoisted_1$i);
    };
  }
});
const VPNavBarHamburger = /* @__PURE__ */ _export_sfc(_sfc_main$q, [["__scopeId", "data-v-e5dd9c1c"]]);
const _hoisted_1$h = ["innerHTML"];
const _sfc_main$p = /* @__PURE__ */ defineComponent({
  __name: "VPNavBarMenuLink",
  props: {
    item: {}
  },
  setup(__props) {
    const { page } = useData();
    return (_ctx, _cache) => {
      return openBlock(), createBlock(_sfc_main$S, {
        class: normalizeClass({
          VPNavBarMenuLink: true,
          active: unref(isActive)(
            unref(page).relativePath,
            _ctx.item.activeMatch || _ctx.item.link,
            !!_ctx.item.activeMatch
          )
        }),
        href: _ctx.item.link,
        noIcon: _ctx.item.noIcon,
        target: _ctx.item.target,
        rel: _ctx.item.rel,
        tabindex: "0"
      }, {
        default: withCtx(() => [
          createBaseVNode("span", {
            innerHTML: _ctx.item.text
          }, null, 8, _hoisted_1$h)
        ]),
        _: 1
      }, 8, ["class", "href", "noIcon", "target", "rel"]);
    };
  }
});
const VPNavBarMenuLink = /* @__PURE__ */ _export_sfc(_sfc_main$p, [["__scopeId", "data-v-9c663999"]]);
const _sfc_main$o = /* @__PURE__ */ defineComponent({
  __name: "VPNavBarMenuGroup",
  props: {
    item: {}
  },
  setup(__props) {
    const props = __props;
    const { page } = useData();
    const isChildActive = (navItem) => {
      if ("link" in navItem) {
        return isActive(
          page.value.relativePath,
          navItem.link,
          !!props.item.activeMatch
        );
      } else {
        return navItem.items.some(isChildActive);
      }
    };
    const childrenActive = computed(() => isChildActive(props.item));
    return (_ctx, _cache) => {
      return openBlock(), createBlock(VPFlyout, {
        class: normalizeClass({
          VPNavBarMenuGroup: true,
          active: unref(isActive)(
            unref(page).relativePath,
            _ctx.item.activeMatch,
            !!_ctx.item.activeMatch
          ) || childrenActive.value
        }),
        button: _ctx.item.text,
        items: _ctx.item.items
      }, null, 8, ["class", "button", "items"]);
    };
  }
});
const _withScopeId$5 = (n) => (pushScopeId("data-v-7f418b0f"), n = n(), popScopeId(), n);
const _hoisted_1$g = {
  key: 0,
  "aria-labelledby": "main-nav-aria-label",
  class: "VPNavBarMenu"
};
const _hoisted_2$c = /* @__PURE__ */ _withScopeId$5(() => /* @__PURE__ */ createBaseVNode("span", {
  id: "main-nav-aria-label",
  class: "visually-hidden"
}, "Main Navigation", -1));
const _sfc_main$n = /* @__PURE__ */ defineComponent({
  __name: "VPNavBarMenu",
  setup(__props) {
    const { theme: theme2 } = useData();
    return (_ctx, _cache) => {
      return unref(theme2).nav ? (openBlock(), createElementBlock("nav", _hoisted_1$g, [
        _hoisted_2$c,
        (openBlock(true), createElementBlock(Fragment, null, renderList(unref(theme2).nav, (item) => {
          return openBlock(), createElementBlock(Fragment, {
            key: item.text
          }, [
            "link" in item ? (openBlock(), createBlock(VPNavBarMenuLink, {
              key: 0,
              item
            }, null, 8, ["item"])) : (openBlock(), createBlock(_sfc_main$o, {
              key: 1,
              item
            }, null, 8, ["item"]))
          ], 64);
        }), 128))
      ])) : createCommentVNode("", true);
    };
  }
});
const VPNavBarMenu = /* @__PURE__ */ _export_sfc(_sfc_main$n, [["__scopeId", "data-v-7f418b0f"]]);
function createSearchTranslate(defaultTranslations) {
  const { localeIndex, theme: theme2 } = useData();
  function translate(key) {
    var _a, _b, _c;
    const keyPath = key.split(".");
    const themeObject = (_a = theme2.value.search) == null ? void 0 : _a.options;
    const isObject = themeObject && typeof themeObject === "object";
    const locales = isObject && ((_c = (_b = themeObject.locales) == null ? void 0 : _b[localeIndex.value]) == null ? void 0 : _c.translations) || null;
    const translations = isObject && themeObject.translations || null;
    let localeResult = locales;
    let translationResult = translations;
    let defaultResult = defaultTranslations;
    const lastKey = keyPath.pop();
    for (const k of keyPath) {
      let fallbackResult = null;
      const foundInFallback = defaultResult == null ? void 0 : defaultResult[k];
      if (foundInFallback) {
        fallbackResult = defaultResult = foundInFallback;
      }
      const foundInTranslation = translationResult == null ? void 0 : translationResult[k];
      if (foundInTranslation) {
        fallbackResult = translationResult = foundInTranslation;
      }
      const foundInLocale = localeResult == null ? void 0 : localeResult[k];
      if (foundInLocale) {
        fallbackResult = localeResult = foundInLocale;
      }
      if (!foundInFallback) {
        defaultResult = fallbackResult;
      }
      if (!foundInTranslation) {
        translationResult = fallbackResult;
      }
      if (!foundInLocale) {
        localeResult = fallbackResult;
      }
    }
    return (localeResult == null ? void 0 : localeResult[lastKey]) ?? (translationResult == null ? void 0 : translationResult[lastKey]) ?? (defaultResult == null ? void 0 : defaultResult[lastKey]) ?? "";
  }
  return translate;
}
const _hoisted_1$f = ["aria-label"];
const _hoisted_2$b = { class: "DocSearch-Button-Container" };
const _hoisted_3$7 = /* @__PURE__ */ createBaseVNode("span", { class: "vp-icon DocSearch-Search-Icon" }, null, -1);
const _hoisted_4$3 = { class: "DocSearch-Button-Placeholder" };
const _hoisted_5$3 = /* @__PURE__ */ createBaseVNode("span", { class: "DocSearch-Button-Keys" }, [
  /* @__PURE__ */ createBaseVNode("kbd", { class: "DocSearch-Button-Key" }),
  /* @__PURE__ */ createBaseVNode("kbd", { class: "DocSearch-Button-Key" }, "K")
], -1);
const _sfc_main$m = /* @__PURE__ */ defineComponent({
  __name: "VPNavBarSearchButton",
  setup(__props) {
    const defaultTranslations = {
      button: {
        buttonText: "Search",
        buttonAriaLabel: "Search"
      }
    };
    const translate = createSearchTranslate(defaultTranslations);
    return (_ctx, _cache) => {
      return openBlock(), createElementBlock("button", {
        type: "button",
        class: "DocSearch DocSearch-Button",
        "aria-label": unref(translate)("button.buttonAriaLabel")
      }, [
        createBaseVNode("span", _hoisted_2$b, [
          _hoisted_3$7,
          createBaseVNode("span", _hoisted_4$3, toDisplayString(unref(translate)("button.buttonText")), 1)
        ]),
        _hoisted_5$3
      ], 8, _hoisted_1$f);
    };
  }
});
const _hoisted_1$e = { class: "VPNavBarSearch" };
const _hoisted_2$a = { id: "local-search" };
const _hoisted_3$6 = {
  key: 1,
  id: "docsearch"
};
const _sfc_main$l = /* @__PURE__ */ defineComponent({
  __name: "VPNavBarSearch",
  setup(__props) {
    const VPLocalSearchBox = defineAsyncComponent(() => __vitePreload(() => import("./VPLocalSearchBox.DNY7ZZm3.js"), true ? __vite__mapDeps([0,1]) : void 0));
    const VPAlgoliaSearchBox = () => null;
    const { theme: theme2 } = useData();
    const loaded = ref(false);
    const actuallyLoaded = ref(false);
    onMounted(() => {
      {
        return;
      }
    });
    function load() {
      if (!loaded.value) {
        loaded.value = true;
        setTimeout(poll, 16);
      }
    }
    function poll() {
      const e = new Event("keydown");
      e.key = "k";
      e.metaKey = true;
      window.dispatchEvent(e);
      setTimeout(() => {
        if (!document.querySelector(".DocSearch-Modal")) {
          poll();
        }
      }, 16);
    }
    function isEditingContent(event) {
      const element = event.target;
      const tagName = element.tagName;
      return element.isContentEditable || tagName === "INPUT" || tagName === "SELECT" || tagName === "TEXTAREA";
    }
    const showSearch = ref(false);
    {
      onKeyStroke("k", (event) => {
        if (event.ctrlKey || event.metaKey) {
          event.preventDefault();
          showSearch.value = true;
        }
      });
      onKeyStroke("/", (event) => {
        if (!isEditingContent(event)) {
          event.preventDefault();
          showSearch.value = true;
        }
      });
    }
    const provider = "local";
    return (_ctx, _cache) => {
      var _a;
      return openBlock(), createElementBlock("div", _hoisted_1$e, [
        unref(provider) === "local" ? (openBlock(), createElementBlock(Fragment, { key: 0 }, [
          showSearch.value ? (openBlock(), createBlock(unref(VPLocalSearchBox), {
            key: 0,
            onClose: _cache[0] || (_cache[0] = ($event) => showSearch.value = false)
          })) : createCommentVNode("", true),
          createBaseVNode("div", _hoisted_2$a, [
            createVNode(_sfc_main$m, {
              onClick: _cache[1] || (_cache[1] = ($event) => showSearch.value = true)
            })
          ])
        ], 64)) : unref(provider) === "algolia" ? (openBlock(), createElementBlock(Fragment, { key: 1 }, [
          loaded.value ? (openBlock(), createBlock(unref(VPAlgoliaSearchBox), {
            key: 0,
            algolia: ((_a = unref(theme2).search) == null ? void 0 : _a.options) ?? unref(theme2).algolia,
            onVnodeBeforeMount: _cache[2] || (_cache[2] = ($event) => actuallyLoaded.value = true)
          }, null, 8, ["algolia"])) : createCommentVNode("", true),
          !actuallyLoaded.value ? (openBlock(), createElementBlock("div", _hoisted_3$6, [
            createVNode(_sfc_main$m, { onClick: load })
          ])) : createCommentVNode("", true)
        ], 64)) : createCommentVNode("", true)
      ]);
    };
  }
});
const _sfc_main$k = /* @__PURE__ */ defineComponent({
  __name: "VPNavBarSocialLinks",
  setup(__props) {
    const { theme: theme2 } = useData();
    return (_ctx, _cache) => {
      return unref(theme2).socialLinks ? (openBlock(), createBlock(VPSocialLinks, {
        key: 0,
        class: "VPNavBarSocialLinks",
        links: unref(theme2).socialLinks
      }, null, 8, ["links"])) : createCommentVNode("", true);
    };
  }
});
const VPNavBarSocialLinks = /* @__PURE__ */ _export_sfc(_sfc_main$k, [["__scopeId", "data-v-0394ad82"]]);
const _hoisted_1$d = ["href", "rel", "target"];
const _hoisted_2$9 = { key: 1 };
const _hoisted_3$5 = { key: 2 };
const _sfc_main$j = /* @__PURE__ */ defineComponent({
  __name: "VPNavBarTitle",
  setup(__props) {
    const { site, theme: theme2 } = useData();
    const { hasSidebar } = useSidebar();
    const { currentLang } = useLangs();
    const link = computed(
      () => {
        var _a;
        return typeof theme2.value.logoLink === "string" ? theme2.value.logoLink : (_a = theme2.value.logoLink) == null ? void 0 : _a.link;
      }
    );
    const rel = computed(
      () => {
        var _a;
        return typeof theme2.value.logoLink === "string" ? void 0 : (_a = theme2.value.logoLink) == null ? void 0 : _a.rel;
      }
    );
    const target = computed(
      () => {
        var _a;
        return typeof theme2.value.logoLink === "string" ? void 0 : (_a = theme2.value.logoLink) == null ? void 0 : _a.target;
      }
    );
    return (_ctx, _cache) => {
      return openBlock(), createElementBlock("div", {
        class: normalizeClass(["VPNavBarTitle", { "has-sidebar": unref(hasSidebar) }])
      }, [
        createBaseVNode("a", {
          class: "title",
          href: link.value ?? unref(normalizeLink$1)(unref(currentLang).link),
          rel: rel.value,
          target: target.value
        }, [
          renderSlot(_ctx.$slots, "nav-bar-title-before", {}, void 0, true),
          unref(theme2).logo ? (openBlock(), createBlock(VPImage, {
            key: 0,
            class: "logo",
            image: unref(theme2).logo
          }, null, 8, ["image"])) : createCommentVNode("", true),
          unref(theme2).siteTitle ? (openBlock(), createElementBlock("span", _hoisted_2$9, toDisplayString(unref(theme2).siteTitle), 1)) : unref(theme2).siteTitle === void 0 ? (openBlock(), createElementBlock("span", _hoisted_3$5, toDisplayString(unref(site).title), 1)) : createCommentVNode("", true),
          renderSlot(_ctx.$slots, "nav-bar-title-after", {}, void 0, true)
        ], 8, _hoisted_1$d)
      ], 2);
    };
  }
});
const VPNavBarTitle = /* @__PURE__ */ _export_sfc(_sfc_main$j, [["__scopeId", "data-v-ab179fa1"]]);
const _hoisted_1$c = { class: "items" };
const _hoisted_2$8 = { class: "title" };
const _sfc_main$i = /* @__PURE__ */ defineComponent({
  __name: "VPNavBarTranslations",
  setup(__props) {
    const { theme: theme2 } = useData();
    const { localeLinks, currentLang } = useLangs({ correspondingLink: true });
    return (_ctx, _cache) => {
      return unref(localeLinks).length && unref(currentLang).label ? (openBlock(), createBlock(VPFlyout, {
        key: 0,
        class: "VPNavBarTranslations",
        icon: "vpi-languages",
        label: unref(theme2).langMenuLabel || "Change language"
      }, {
        default: withCtx(() => [
          createBaseVNode("div", _hoisted_1$c, [
            createBaseVNode("p", _hoisted_2$8, toDisplayString(unref(currentLang).label), 1),
            (openBlock(true), createElementBlock(Fragment, null, renderList(unref(localeLinks), (locale) => {
              return openBlock(), createBlock(VPMenuLink, {
                key: locale.link,
                item: locale
              }, null, 8, ["item"]);
            }), 128))
          ])
        ]),
        _: 1
      }, 8, ["label"])) : createCommentVNode("", true);
    };
  }
});
const VPNavBarTranslations = /* @__PURE__ */ _export_sfc(_sfc_main$i, [["__scopeId", "data-v-88af2de4"]]);
const _withScopeId$4 = (n) => (pushScopeId("data-v-ccf7ddec"), n = n(), popScopeId(), n);
const _hoisted_1$b = { class: "wrapper" };
const _hoisted_2$7 = { class: "container" };
const _hoisted_3$4 = { class: "title" };
const _hoisted_4$2 = { class: "content" };
const _hoisted_5$2 = { class: "content-body" };
const _hoisted_6 = /* @__PURE__ */ _withScopeId$4(() => /* @__PURE__ */ createBaseVNode("div", { class: "divider" }, [
  /* @__PURE__ */ createBaseVNode("div", { class: "divider-line" })
], -1));
const _sfc_main$h = /* @__PURE__ */ defineComponent({
  __name: "VPNavBar",
  props: {
    isScreenOpen: { type: Boolean }
  },
  emits: ["toggle-screen"],
  setup(__props) {
    const { y } = useWindowScroll();
    const { hasSidebar } = useSidebar();
    const { frontmatter } = useData();
    const classes = ref({});
    watchPostEffect(() => {
      classes.value = {
        "has-sidebar": hasSidebar.value,
        "home": frontmatter.value.layout === "home",
        "top": y.value === 0
      };
    });
    return (_ctx, _cache) => {
      return openBlock(), createElementBlock("div", {
        class: normalizeClass(["VPNavBar", classes.value])
      }, [
        createBaseVNode("div", _hoisted_1$b, [
          createBaseVNode("div", _hoisted_2$7, [
            createBaseVNode("div", _hoisted_3$4, [
              createVNode(VPNavBarTitle, null, {
                "nav-bar-title-before": withCtx(() => [
                  renderSlot(_ctx.$slots, "nav-bar-title-before", {}, void 0, true)
                ]),
                "nav-bar-title-after": withCtx(() => [
                  renderSlot(_ctx.$slots, "nav-bar-title-after", {}, void 0, true)
                ]),
                _: 3
              })
            ]),
            createBaseVNode("div", _hoisted_4$2, [
              createBaseVNode("div", _hoisted_5$2, [
                renderSlot(_ctx.$slots, "nav-bar-content-before", {}, void 0, true),
                createVNode(_sfc_main$l, { class: "search" }),
                createVNode(VPNavBarMenu, { class: "menu" }),
                createVNode(VPNavBarTranslations, { class: "translations" }),
                createVNode(VPNavBarAppearance, { class: "appearance" }),
                createVNode(VPNavBarSocialLinks, { class: "social-links" }),
                createVNode(VPNavBarExtra, { class: "extra" }),
                renderSlot(_ctx.$slots, "nav-bar-content-after", {}, void 0, true),
                createVNode(VPNavBarHamburger, {
                  class: "hamburger",
                  active: _ctx.isScreenOpen,
                  onClick: _cache[0] || (_cache[0] = ($event) => _ctx.$emit("toggle-screen"))
                }, null, 8, ["active"])
              ])
            ])
          ])
        ]),
        _hoisted_6
      ], 2);
    };
  }
});
const VPNavBar = /* @__PURE__ */ _export_sfc(_sfc_main$h, [["__scopeId", "data-v-ccf7ddec"]]);
const _hoisted_1$a = {
  key: 0,
  class: "VPNavScreenAppearance"
};
const _hoisted_2$6 = { class: "text" };
const _sfc_main$g = /* @__PURE__ */ defineComponent({
  __name: "VPNavScreenAppearance",
  setup(__props) {
    const { site, theme: theme2 } = useData();
    return (_ctx, _cache) => {
      return unref(site).appearance && unref(site).appearance !== "force-dark" ? (openBlock(), createElementBlock("div", _hoisted_1$a, [
        createBaseVNode("p", _hoisted_2$6, toDisplayString(unref(theme2).darkModeSwitchLabel || "Appearance"), 1),
        createVNode(VPSwitchAppearance)
      ])) : createCommentVNode("", true);
    };
  }
});
const VPNavScreenAppearance = /* @__PURE__ */ _export_sfc(_sfc_main$g, [["__scopeId", "data-v-2d7af913"]]);
const _sfc_main$f = /* @__PURE__ */ defineComponent({
  __name: "VPNavScreenMenuLink",
  props: {
    item: {}
  },
  setup(__props) {
    const closeScreen = inject("close-screen");
    return (_ctx, _cache) => {
      return openBlock(), createBlock(_sfc_main$S, {
        class: "VPNavScreenMenuLink",
        href: _ctx.item.link,
        target: _ctx.item.target,
        rel: _ctx.item.rel,
        onClick: unref(closeScreen),
        innerHTML: _ctx.item.text
      }, null, 8, ["href", "target", "rel", "onClick", "innerHTML"]);
    };
  }
});
const VPNavScreenMenuLink = /* @__PURE__ */ _export_sfc(_sfc_main$f, [["__scopeId", "data-v-7f31e1f6"]]);
const _sfc_main$e = /* @__PURE__ */ defineComponent({
  __name: "VPNavScreenMenuGroupLink",
  props: {
    item: {}
  },
  setup(__props) {
    const closeScreen = inject("close-screen");
    return (_ctx, _cache) => {
      return openBlock(), createBlock(_sfc_main$S, {
        class: "VPNavScreenMenuGroupLink",
        href: _ctx.item.link,
        target: _ctx.item.target,
        rel: _ctx.item.rel,
        onClick: unref(closeScreen)
      }, {
        default: withCtx(() => [
          createTextVNode(toDisplayString(_ctx.item.text), 1)
        ]),
        _: 1
      }, 8, ["href", "target", "rel", "onClick"]);
    };
  }
});
const VPNavScreenMenuGroupLink = /* @__PURE__ */ _export_sfc(_sfc_main$e, [["__scopeId", "data-v-19976ae1"]]);
const _hoisted_1$9 = { class: "VPNavScreenMenuGroupSection" };
const _hoisted_2$5 = {
  key: 0,
  class: "title"
};
const _sfc_main$d = /* @__PURE__ */ defineComponent({
  __name: "VPNavScreenMenuGroupSection",
  props: {
    text: {},
    items: {}
  },
  setup(__props) {
    return (_ctx, _cache) => {
      return openBlock(), createElementBlock("div", _hoisted_1$9, [
        _ctx.text ? (openBlock(), createElementBlock("p", _hoisted_2$5, toDisplayString(_ctx.text), 1)) : createCommentVNode("", true),
        (openBlock(true), createElementBlock(Fragment, null, renderList(_ctx.items, (item) => {
          return openBlock(), createBlock(VPNavScreenMenuGroupLink, {
            key: item.text,
            item
          }, null, 8, ["item"]);
        }), 128))
      ]);
    };
  }
});
const VPNavScreenMenuGroupSection = /* @__PURE__ */ _export_sfc(_sfc_main$d, [["__scopeId", "data-v-8133b170"]]);
const _withScopeId$3 = (n) => (pushScopeId("data-v-ff6087d4"), n = n(), popScopeId(), n);
const _hoisted_1$8 = ["aria-controls", "aria-expanded"];
const _hoisted_2$4 = ["innerHTML"];
const _hoisted_3$3 = /* @__PURE__ */ _withScopeId$3(() => /* @__PURE__ */ createBaseVNode("span", { class: "vpi-plus button-icon" }, null, -1));
const _hoisted_4$1 = ["id"];
const _hoisted_5$1 = {
  key: 1,
  class: "group"
};
const _sfc_main$c = /* @__PURE__ */ defineComponent({
  __name: "VPNavScreenMenuGroup",
  props: {
    text: {},
    items: {}
  },
  setup(__props) {
    const props = __props;
    const isOpen = ref(false);
    const groupId = computed(
      () => `NavScreenGroup-${props.text.replace(" ", "-").toLowerCase()}`
    );
    function toggle() {
      isOpen.value = !isOpen.value;
    }
    return (_ctx, _cache) => {
      return openBlock(), createElementBlock("div", {
        class: normalizeClass(["VPNavScreenMenuGroup", { open: isOpen.value }])
      }, [
        createBaseVNode("button", {
          class: "button",
          "aria-controls": groupId.value,
          "aria-expanded": isOpen.value,
          onClick: toggle
        }, [
          createBaseVNode("span", {
            class: "button-text",
            innerHTML: _ctx.text
          }, null, 8, _hoisted_2$4),
          _hoisted_3$3
        ], 8, _hoisted_1$8),
        createBaseVNode("div", {
          id: groupId.value,
          class: "items"
        }, [
          (openBlock(true), createElementBlock(Fragment, null, renderList(_ctx.items, (item) => {
            return openBlock(), createElementBlock(Fragment, {
              key: item.text
            }, [
              "link" in item ? (openBlock(), createElementBlock("div", {
                key: item.text,
                class: "item"
              }, [
                createVNode(VPNavScreenMenuGroupLink, { item }, null, 8, ["item"])
              ])) : (openBlock(), createElementBlock("div", _hoisted_5$1, [
                createVNode(VPNavScreenMenuGroupSection, {
                  text: item.text,
                  items: item.items
                }, null, 8, ["text", "items"])
              ]))
            ], 64);
          }), 128))
        ], 8, _hoisted_4$1)
      ], 2);
    };
  }
});
const VPNavScreenMenuGroup = /* @__PURE__ */ _export_sfc(_sfc_main$c, [["__scopeId", "data-v-ff6087d4"]]);
const _hoisted_1$7 = {
  key: 0,
  class: "VPNavScreenMenu"
};
const _sfc_main$b = /* @__PURE__ */ defineComponent({
  __name: "VPNavScreenMenu",
  setup(__props) {
    const { theme: theme2 } = useData();
    return (_ctx, _cache) => {
      return unref(theme2).nav ? (openBlock(), createElementBlock("nav", _hoisted_1$7, [
        (openBlock(true), createElementBlock(Fragment, null, renderList(unref(theme2).nav, (item) => {
          return openBlock(), createElementBlock(Fragment, {
            key: item.text
          }, [
            "link" in item ? (openBlock(), createBlock(VPNavScreenMenuLink, {
              key: 0,
              item
            }, null, 8, ["item"])) : (openBlock(), createBlock(VPNavScreenMenuGroup, {
              key: 1,
              text: item.text || "",
              items: item.items
            }, null, 8, ["text", "items"]))
          ], 64);
        }), 128))
      ])) : createCommentVNode("", true);
    };
  }
});
const _sfc_main$a = /* @__PURE__ */ defineComponent({
  __name: "VPNavScreenSocialLinks",
  setup(__props) {
    const { theme: theme2 } = useData();
    return (_ctx, _cache) => {
      return unref(theme2).socialLinks ? (openBlock(), createBlock(VPSocialLinks, {
        key: 0,
        class: "VPNavScreenSocialLinks",
        links: unref(theme2).socialLinks
      }, null, 8, ["links"])) : createCommentVNode("", true);
    };
  }
});
const _withScopeId$2 = (n) => (pushScopeId("data-v-858fe1a4"), n = n(), popScopeId(), n);
const _hoisted_1$6 = /* @__PURE__ */ _withScopeId$2(() => /* @__PURE__ */ createBaseVNode("span", { class: "vpi-languages icon lang" }, null, -1));
const _hoisted_2$3 = /* @__PURE__ */ _withScopeId$2(() => /* @__PURE__ */ createBaseVNode("span", { class: "vpi-chevron-down icon chevron" }, null, -1));
const _hoisted_3$2 = { class: "list" };
const _sfc_main$9 = /* @__PURE__ */ defineComponent({
  __name: "VPNavScreenTranslations",
  setup(__props) {
    const { localeLinks, currentLang } = useLangs({ correspondingLink: true });
    const isOpen = ref(false);
    function toggle() {
      isOpen.value = !isOpen.value;
    }
    return (_ctx, _cache) => {
      return unref(localeLinks).length && unref(currentLang).label ? (openBlock(), createElementBlock("div", {
        key: 0,
        class: normalizeClass(["VPNavScreenTranslations", { open: isOpen.value }])
      }, [
        createBaseVNode("button", {
          class: "title",
          onClick: toggle
        }, [
          _hoisted_1$6,
          createTextVNode(" " + toDisplayString(unref(currentLang).label) + " ", 1),
          _hoisted_2$3
        ]),
        createBaseVNode("ul", _hoisted_3$2, [
          (openBlock(true), createElementBlock(Fragment, null, renderList(unref(localeLinks), (locale) => {
            return openBlock(), createElementBlock("li", {
              key: locale.link,
              class: "item"
            }, [
              createVNode(_sfc_main$S, {
                class: "link",
                href: locale.link
              }, {
                default: withCtx(() => [
                  createTextVNode(toDisplayString(locale.text), 1)
                ]),
                _: 2
              }, 1032, ["href"])
            ]);
          }), 128))
        ])
      ], 2)) : createCommentVNode("", true);
    };
  }
});
const VPNavScreenTranslations = /* @__PURE__ */ _export_sfc(_sfc_main$9, [["__scopeId", "data-v-858fe1a4"]]);
const _hoisted_1$5 = { class: "container" };
const _sfc_main$8 = /* @__PURE__ */ defineComponent({
  __name: "VPNavScreen",
  props: {
    open: { type: Boolean }
  },
  setup(__props) {
    const screen = ref(null);
    const isLocked = useScrollLock(inBrowser ? document.body : null);
    return (_ctx, _cache) => {
      return openBlock(), createBlock(Transition, {
        name: "fade",
        onEnter: _cache[0] || (_cache[0] = ($event) => isLocked.value = true),
        onAfterLeave: _cache[1] || (_cache[1] = ($event) => isLocked.value = false)
      }, {
        default: withCtx(() => [
          _ctx.open ? (openBlock(), createElementBlock("div", {
            key: 0,
            class: "VPNavScreen",
            ref_key: "screen",
            ref: screen,
            id: "VPNavScreen"
          }, [
            createBaseVNode("div", _hoisted_1$5, [
              renderSlot(_ctx.$slots, "nav-screen-content-before", {}, void 0, true),
              createVNode(_sfc_main$b, { class: "menu" }),
              createVNode(VPNavScreenTranslations, { class: "translations" }),
              createVNode(VPNavScreenAppearance, { class: "appearance" }),
              createVNode(_sfc_main$a, { class: "social-links" }),
              renderSlot(_ctx.$slots, "nav-screen-content-after", {}, void 0, true)
            ])
          ], 512)) : createCommentVNode("", true)
        ]),
        _: 3
      });
    };
  }
});
const VPNavScreen = /* @__PURE__ */ _export_sfc(_sfc_main$8, [["__scopeId", "data-v-cc5739dd"]]);
const _hoisted_1$4 = {
  key: 0,
  class: "VPNav"
};
const _sfc_main$7 = /* @__PURE__ */ defineComponent({
  __name: "VPNav",
  setup(__props) {
    const { isScreenOpen, closeScreen, toggleScreen } = useNav();
    const { frontmatter } = useData();
    const hasNavbar = computed(() => {
      return frontmatter.value.navbar !== false;
    });
    provide("close-screen", closeScreen);
    watchEffect(() => {
      if (inBrowser) {
        document.documentElement.classList.toggle("hide-nav", !hasNavbar.value);
      }
    });
    return (_ctx, _cache) => {
      return hasNavbar.value ? (openBlock(), createElementBlock("header", _hoisted_1$4, [
        createVNode(VPNavBar, {
          "is-screen-open": unref(isScreenOpen),
          onToggleScreen: unref(toggleScreen)
        }, {
          "nav-bar-title-before": withCtx(() => [
            renderSlot(_ctx.$slots, "nav-bar-title-before", {}, void 0, true)
          ]),
          "nav-bar-title-after": withCtx(() => [
            renderSlot(_ctx.$slots, "nav-bar-title-after", {}, void 0, true)
          ]),
          "nav-bar-content-before": withCtx(() => [
            renderSlot(_ctx.$slots, "nav-bar-content-before", {}, void 0, true)
          ]),
          "nav-bar-content-after": withCtx(() => [
            renderSlot(_ctx.$slots, "nav-bar-content-after", {}, void 0, true)
          ]),
          _: 3
        }, 8, ["is-screen-open", "onToggleScreen"]),
        createVNode(VPNavScreen, { open: unref(isScreenOpen) }, {
          "nav-screen-content-before": withCtx(() => [
            renderSlot(_ctx.$slots, "nav-screen-content-before", {}, void 0, true)
          ]),
          "nav-screen-content-after": withCtx(() => [
            renderSlot(_ctx.$slots, "nav-screen-content-after", {}, void 0, true)
          ]),
          _: 3
        }, 8, ["open"])
      ])) : createCommentVNode("", true);
    };
  }
});
const VPNav = /* @__PURE__ */ _export_sfc(_sfc_main$7, [["__scopeId", "data-v-ae24b3ad"]]);
const _withScopeId$1 = (n) => (pushScopeId("data-v-b8d55f3b"), n = n(), popScopeId(), n);
const _hoisted_1$3 = ["role", "tabindex"];
const _hoisted_2$2 = /* @__PURE__ */ _withScopeId$1(() => /* @__PURE__ */ createBaseVNode("div", { class: "indicator" }, null, -1));
const _hoisted_3$1 = /* @__PURE__ */ _withScopeId$1(() => /* @__PURE__ */ createBaseVNode("span", { class: "vpi-chevron-right caret-icon" }, null, -1));
const _hoisted_4 = [
  _hoisted_3$1
];
const _hoisted_5 = {
  key: 1,
  class: "items"
};
const _sfc_main$6 = /* @__PURE__ */ defineComponent({
  __name: "VPSidebarItem",
  props: {
    item: {},
    depth: {}
  },
  setup(__props) {
    const props = __props;
    const {
      collapsed,
      collapsible,
      isLink,
      isActiveLink,
      hasActiveLink: hasActiveLink2,
      hasChildren,
      toggle
    } = useSidebarControl(computed(() => props.item));
    const sectionTag = computed(() => hasChildren.value ? "section" : `div`);
    const linkTag = computed(() => isLink.value ? "a" : "div");
    const textTag = computed(() => {
      return !hasChildren.value ? "p" : props.depth + 2 === 7 ? "p" : `h${props.depth + 2}`;
    });
    const itemRole = computed(() => isLink.value ? void 0 : "button");
    const classes = computed(() => [
      [`level-${props.depth}`],
      { collapsible: collapsible.value },
      { collapsed: collapsed.value },
      { "is-link": isLink.value },
      { "is-active": isActiveLink.value },
      { "has-active": hasActiveLink2.value }
    ]);
    function onItemInteraction(e) {
      if ("key" in e && e.key !== "Enter") {
        return;
      }
      !props.item.link && toggle();
    }
    function onCaretClick() {
      props.item.link && toggle();
    }
    return (_ctx, _cache) => {
      const _component_VPSidebarItem = resolveComponent("VPSidebarItem", true);
      return openBlock(), createBlock(resolveDynamicComponent(sectionTag.value), {
        class: normalizeClass(["VPSidebarItem", classes.value])
      }, {
        default: withCtx(() => [
          _ctx.item.text ? (openBlock(), createElementBlock("div", mergeProps({
            key: 0,
            class: "item",
            role: itemRole.value
          }, toHandlers(
            _ctx.item.items ? { click: onItemInteraction, keydown: onItemInteraction } : {},
            true
          ), {
            tabindex: _ctx.item.items && 0
          }), [
            _hoisted_2$2,
            _ctx.item.link ? (openBlock(), createBlock(_sfc_main$S, {
              key: 0,
              tag: linkTag.value,
              class: "link",
              href: _ctx.item.link,
              rel: _ctx.item.rel,
              target: _ctx.item.target
            }, {
              default: withCtx(() => [
                (openBlock(), createBlock(resolveDynamicComponent(textTag.value), {
                  class: "text",
                  innerHTML: _ctx.item.text
                }, null, 8, ["innerHTML"]))
              ]),
              _: 1
            }, 8, ["tag", "href", "rel", "target"])) : (openBlock(), createBlock(resolveDynamicComponent(textTag.value), {
              key: 1,
              class: "text",
              innerHTML: _ctx.item.text
            }, null, 8, ["innerHTML"])),
            _ctx.item.collapsed != null && _ctx.item.items && _ctx.item.items.length ? (openBlock(), createElementBlock("div", {
              key: 2,
              class: "caret",
              role: "button",
              "aria-label": "toggle section",
              onClick: onCaretClick,
              onKeydown: withKeys(onCaretClick, ["enter"]),
              tabindex: "0"
            }, _hoisted_4, 32)) : createCommentVNode("", true)
          ], 16, _hoisted_1$3)) : createCommentVNode("", true),
          _ctx.item.items && _ctx.item.items.length ? (openBlock(), createElementBlock("div", _hoisted_5, [
            _ctx.depth < 5 ? (openBlock(true), createElementBlock(Fragment, { key: 0 }, renderList(_ctx.item.items, (i) => {
              return openBlock(), createBlock(_component_VPSidebarItem, {
                key: i.text,
                item: i,
                depth: _ctx.depth + 1
              }, null, 8, ["item", "depth"]);
            }), 128)) : createCommentVNode("", true)
          ])) : createCommentVNode("", true)
        ]),
        _: 1
      }, 8, ["class"]);
    };
  }
});
const VPSidebarItem = /* @__PURE__ */ _export_sfc(_sfc_main$6, [["__scopeId", "data-v-b8d55f3b"]]);
const _withScopeId = (n) => (pushScopeId("data-v-575e6a36"), n = n(), popScopeId(), n);
const _hoisted_1$2 = /* @__PURE__ */ _withScopeId(() => /* @__PURE__ */ createBaseVNode("div", { class: "curtain" }, null, -1));
const _hoisted_2$1 = {
  class: "nav",
  id: "VPSidebarNav",
  "aria-labelledby": "sidebar-aria-label",
  tabindex: "-1"
};
const _hoisted_3 = /* @__PURE__ */ _withScopeId(() => /* @__PURE__ */ createBaseVNode("span", {
  class: "visually-hidden",
  id: "sidebar-aria-label"
}, " Sidebar Navigation ", -1));
const _sfc_main$5 = /* @__PURE__ */ defineComponent({
  __name: "VPSidebar",
  props: {
    open: { type: Boolean }
  },
  setup(__props) {
    const { sidebarGroups, hasSidebar } = useSidebar();
    const props = __props;
    const navEl = ref(null);
    const isLocked = useScrollLock(inBrowser ? document.body : null);
    watch(
      [props, navEl],
      () => {
        var _a;
        if (props.open) {
          isLocked.value = true;
          (_a = navEl.value) == null ? void 0 : _a.focus();
        } else isLocked.value = false;
      },
      { immediate: true, flush: "post" }
    );
    return (_ctx, _cache) => {
      return unref(hasSidebar) ? (openBlock(), createElementBlock("aside", {
        key: 0,
        class: normalizeClass(["VPSidebar", { open: _ctx.open }]),
        ref_key: "navEl",
        ref: navEl,
        onClick: _cache[0] || (_cache[0] = withModifiers(() => {
        }, ["stop"]))
      }, [
        _hoisted_1$2,
        createBaseVNode("nav", _hoisted_2$1, [
          _hoisted_3,
          renderSlot(_ctx.$slots, "sidebar-nav-before", {}, void 0, true),
          (openBlock(true), createElementBlock(Fragment, null, renderList(unref(sidebarGroups), (item) => {
            return openBlock(), createElementBlock("div", {
              key: item.text,
              class: "group"
            }, [
              createVNode(VPSidebarItem, {
                item,
                depth: 0
              }, null, 8, ["item"])
            ]);
          }), 128)),
          renderSlot(_ctx.$slots, "sidebar-nav-after", {}, void 0, true)
        ])
      ], 2)) : createCommentVNode("", true);
    };
  }
});
const VPSidebar = /* @__PURE__ */ _export_sfc(_sfc_main$5, [["__scopeId", "data-v-575e6a36"]]);
const _sfc_main$4 = /* @__PURE__ */ defineComponent({
  __name: "VPSkipLink",
  setup(__props) {
    const route = useRoute();
    const backToTop = ref();
    watch(() => route.path, () => backToTop.value.focus());
    function focusOnTargetAnchor({ target }) {
      const el = document.getElementById(
        decodeURIComponent(target.hash).slice(1)
      );
      if (el) {
        const removeTabIndex = () => {
          el.removeAttribute("tabindex");
          el.removeEventListener("blur", removeTabIndex);
        };
        el.setAttribute("tabindex", "-1");
        el.addEventListener("blur", removeTabIndex);
        el.focus();
        window.scrollTo(0, 0);
      }
    }
    return (_ctx, _cache) => {
      return openBlock(), createElementBlock(Fragment, null, [
        createBaseVNode("span", {
          ref_key: "backToTop",
          ref: backToTop,
          tabindex: "-1"
        }, null, 512),
        createBaseVNode("a", {
          href: "#VPContent",
          class: "VPSkipLink visually-hidden",
          onClick: focusOnTargetAnchor
        }, " Skip to content ")
      ], 64);
    };
  }
});
const VPSkipLink = /* @__PURE__ */ _export_sfc(_sfc_main$4, [["__scopeId", "data-v-0f60ec36"]]);
const _sfc_main$3 = /* @__PURE__ */ defineComponent({
  __name: "Layout",
  setup(__props) {
    const {
      isOpen: isSidebarOpen,
      open: openSidebar,
      close: closeSidebar
    } = useSidebar();
    const route = useRoute();
    watch(() => route.path, closeSidebar);
    useCloseSidebarOnEscape(isSidebarOpen, closeSidebar);
    const { frontmatter } = useData();
    const slots = useSlots();
    const heroImageSlotExists = computed(() => !!slots["home-hero-image"]);
    provide("hero-image-slot-exists", heroImageSlotExists);
    return (_ctx, _cache) => {
      const _component_Content = resolveComponent("Content");
      return unref(frontmatter).layout !== false ? (openBlock(), createElementBlock("div", {
        key: 0,
        class: normalizeClass(["Layout", unref(frontmatter).pageClass])
      }, [
        renderSlot(_ctx.$slots, "layout-top", {}, void 0, true),
        createVNode(VPSkipLink),
        createVNode(VPBackdrop, {
          class: "backdrop",
          show: unref(isSidebarOpen),
          onClick: unref(closeSidebar)
        }, null, 8, ["show", "onClick"]),
        createVNode(VPNav, null, {
          "nav-bar-title-before": withCtx(() => [
            renderSlot(_ctx.$slots, "nav-bar-title-before", {}, void 0, true)
          ]),
          "nav-bar-title-after": withCtx(() => [
            renderSlot(_ctx.$slots, "nav-bar-title-after", {}, void 0, true)
          ]),
          "nav-bar-content-before": withCtx(() => [
            renderSlot(_ctx.$slots, "nav-bar-content-before", {}, void 0, true)
          ]),
          "nav-bar-content-after": withCtx(() => [
            renderSlot(_ctx.$slots, "nav-bar-content-after", {}, void 0, true)
          ]),
          "nav-screen-content-before": withCtx(() => [
            renderSlot(_ctx.$slots, "nav-screen-content-before", {}, void 0, true)
          ]),
          "nav-screen-content-after": withCtx(() => [
            renderSlot(_ctx.$slots, "nav-screen-content-after", {}, void 0, true)
          ]),
          _: 3
        }),
        createVNode(VPLocalNav, {
          open: unref(isSidebarOpen),
          onOpenMenu: unref(openSidebar)
        }, null, 8, ["open", "onOpenMenu"]),
        createVNode(VPSidebar, { open: unref(isSidebarOpen) }, {
          "sidebar-nav-before": withCtx(() => [
            renderSlot(_ctx.$slots, "sidebar-nav-before", {}, void 0, true)
          ]),
          "sidebar-nav-after": withCtx(() => [
            renderSlot(_ctx.$slots, "sidebar-nav-after", {}, void 0, true)
          ]),
          _: 3
        }, 8, ["open"]),
        createVNode(VPContent, null, {
          "page-top": withCtx(() => [
            renderSlot(_ctx.$slots, "page-top", {}, void 0, true)
          ]),
          "page-bottom": withCtx(() => [
            renderSlot(_ctx.$slots, "page-bottom", {}, void 0, true)
          ]),
          "not-found": withCtx(() => [
            renderSlot(_ctx.$slots, "not-found", {}, void 0, true)
          ]),
          "home-hero-before": withCtx(() => [
            renderSlot(_ctx.$slots, "home-hero-before", {}, void 0, true)
          ]),
          "home-hero-info-before": withCtx(() => [
            renderSlot(_ctx.$slots, "home-hero-info-before", {}, void 0, true)
          ]),
          "home-hero-info": withCtx(() => [
            renderSlot(_ctx.$slots, "home-hero-info", {}, void 0, true)
          ]),
          "home-hero-info-after": withCtx(() => [
            renderSlot(_ctx.$slots, "home-hero-info-after", {}, void 0, true)
          ]),
          "home-hero-actions-after": withCtx(() => [
            renderSlot(_ctx.$slots, "home-hero-actions-after", {}, void 0, true)
          ]),
          "home-hero-image": withCtx(() => [
            renderSlot(_ctx.$slots, "home-hero-image", {}, void 0, true)
          ]),
          "home-hero-after": withCtx(() => [
            renderSlot(_ctx.$slots, "home-hero-after", {}, void 0, true)
          ]),
          "home-features-before": withCtx(() => [
            renderSlot(_ctx.$slots, "home-features-before", {}, void 0, true)
          ]),
          "home-features-after": withCtx(() => [
            renderSlot(_ctx.$slots, "home-features-after", {}, void 0, true)
          ]),
          "doc-footer-before": withCtx(() => [
            renderSlot(_ctx.$slots, "doc-footer-before", {}, void 0, true)
          ]),
          "doc-before": withCtx(() => [
            renderSlot(_ctx.$slots, "doc-before", {}, void 0, true)
          ]),
          "doc-after": withCtx(() => [
            renderSlot(_ctx.$slots, "doc-after", {}, void 0, true)
          ]),
          "doc-top": withCtx(() => [
            renderSlot(_ctx.$slots, "doc-top", {}, void 0, true)
          ]),
          "doc-bottom": withCtx(() => [
            renderSlot(_ctx.$slots, "doc-bottom", {}, void 0, true)
          ]),
          "aside-top": withCtx(() => [
            renderSlot(_ctx.$slots, "aside-top", {}, void 0, true)
          ]),
          "aside-bottom": withCtx(() => [
            renderSlot(_ctx.$slots, "aside-bottom", {}, void 0, true)
          ]),
          "aside-outline-before": withCtx(() => [
            renderSlot(_ctx.$slots, "aside-outline-before", {}, void 0, true)
          ]),
          "aside-outline-after": withCtx(() => [
            renderSlot(_ctx.$slots, "aside-outline-after", {}, void 0, true)
          ]),
          "aside-ads-before": withCtx(() => [
            renderSlot(_ctx.$slots, "aside-ads-before", {}, void 0, true)
          ]),
          "aside-ads-after": withCtx(() => [
            renderSlot(_ctx.$slots, "aside-ads-after", {}, void 0, true)
          ]),
          _: 3
        }),
        createVNode(VPFooter),
        renderSlot(_ctx.$slots, "layout-bottom", {}, void 0, true)
      ], 2)) : (openBlock(), createBlock(_component_Content, { key: 1 }));
    };
  }
});
const Layout = /* @__PURE__ */ _export_sfc(_sfc_main$3, [["__scopeId", "data-v-5d98c3a5"]]);
const theme = {
  Layout,
  enhanceApp: ({ app }) => {
    app.component("Badge", _sfc_main$Z);
  }
};
const useStabilizeScrollPosition = (targetEle) => {
  if (typeof document === "undefined") {
    const mock = (f) => async (...args) => f(...args);
    return { stabilizeScrollPosition: mock };
  }
  const scrollableEleVal = document.documentElement;
  const stabilizeScrollPosition = (func) => async (...args) => {
    const result = func(...args);
    const eleVal = targetEle.value;
    if (!eleVal) return result;
    const offset = eleVal.offsetTop - scrollableEleVal.scrollTop;
    await nextTick();
    scrollableEleVal.scrollTop = eleVal.offsetTop - offset;
    return result;
  };
  return { stabilizeScrollPosition };
};
const injectionKey$1 = "vitepress:tabSharedState";
const ls = typeof localStorage !== "undefined" ? localStorage : null;
const localStorageKey = "vitepress:tabsSharedState";
const getLocalStorageValue = () => {
  const rawValue = ls == null ? void 0 : ls.getItem(localStorageKey);
  if (rawValue) {
    try {
      return JSON.parse(rawValue);
    } catch {
    }
  }
  return {};
};
const setLocalStorageValue = (v) => {
  if (!ls) return;
  ls.setItem(localStorageKey, JSON.stringify(v));
};
const provideTabsSharedState = (app) => {
  const state = reactive({});
  watch(
    () => state.content,
    (newStateContent, oldStateContent) => {
      if (newStateContent && oldStateContent) {
        setLocalStorageValue(newStateContent);
      }
    },
    { deep: true }
  );
  app.provide(injectionKey$1, state);
};
const useTabsSelectedState = (acceptValues, sharedStateKey) => {
  const sharedState = inject(injectionKey$1);
  if (!sharedState) {
    throw new Error(
      "[vitepress-plugin-tabs] TabsSharedState should be injected"
    );
  }
  onMounted(() => {
    if (!sharedState.content) {
      sharedState.content = getLocalStorageValue();
    }
  });
  const nonSharedState = ref();
  const selected = computed({
    get() {
      var _a;
      const key = sharedStateKey.value;
      const acceptVals = acceptValues.value;
      if (key) {
        const value = (_a = sharedState.content) == null ? void 0 : _a[key];
        if (value && acceptVals.includes(value)) {
          return value;
        }
      } else {
        const nonSharedStateVal = nonSharedState.value;
        if (nonSharedStateVal) {
          return nonSharedStateVal;
        }
      }
      return acceptVals[0];
    },
    set(v) {
      const key = sharedStateKey.value;
      if (key) {
        if (sharedState.content) {
          sharedState.content[key] = v;
        }
      } else {
        nonSharedState.value = v;
      }
    }
  });
  const select = (newValue) => {
    selected.value = newValue;
  };
  return { selected, select };
};
let id = 0;
const useUid = () => {
  id++;
  return "" + id;
};
function useTabLabels() {
  const slots = useSlots();
  const tabLabels = computed(() => {
    var _a;
    const defaultSlot = (_a = slots.default) == null ? void 0 : _a.call(slots);
    if (!defaultSlot) {
      return [];
    }
    return defaultSlot.filter(
      (vnode) => typeof vnode.type === "object" && "__name" in vnode.type && vnode.type.__name === "PluginTabsTab" && vnode.props
    ).map((vnode) => {
      var _a2;
      return (_a2 = vnode.props) == null ? void 0 : _a2.label;
    });
  });
  return tabLabels;
}
const injectionKey = "vitepress:tabSingleState";
const provideTabsSingleState = (state) => {
  provide(injectionKey, state);
};
const useTabsSingleState = () => {
  const singleState = inject(injectionKey);
  if (!singleState) {
    throw new Error(
      "[vitepress-plugin-tabs] TabsSingleState should be injected"
    );
  }
  return singleState;
};
const _hoisted_1$1 = { class: "plugin-tabs" };
const _hoisted_2 = ["id", "aria-selected", "aria-controls", "tabindex", "onClick"];
const _sfc_main$2 = /* @__PURE__ */ defineComponent({
  __name: "PluginTabs",
  props: {
    sharedStateKey: {}
  },
  setup(__props) {
    const props = __props;
    const tabLabels = useTabLabels();
    const { selected, select } = useTabsSelectedState(
      tabLabels,
      toRef(props, "sharedStateKey")
    );
    const tablist = ref();
    const { stabilizeScrollPosition } = useStabilizeScrollPosition(tablist);
    const selectStable = stabilizeScrollPosition(select);
    const buttonRefs = ref([]);
    const onKeydown = (e) => {
      var _a;
      const currentIndex = tabLabels.value.indexOf(selected.value);
      let selectIndex;
      if (e.key === "ArrowLeft") {
        selectIndex = currentIndex >= 1 ? currentIndex - 1 : tabLabels.value.length - 1;
      } else if (e.key === "ArrowRight") {
        selectIndex = currentIndex < tabLabels.value.length - 1 ? currentIndex + 1 : 0;
      }
      if (selectIndex !== void 0) {
        selectStable(tabLabels.value[selectIndex]);
        (_a = buttonRefs.value[selectIndex]) == null ? void 0 : _a.focus();
      }
    };
    const uid = useUid();
    provideTabsSingleState({ uid, selected });
    return (_ctx, _cache) => {
      return openBlock(), createElementBlock("div", _hoisted_1$1, [
        createBaseVNode("div", {
          ref_key: "tablist",
          ref: tablist,
          class: "plugin-tabs--tab-list",
          role: "tablist",
          onKeydown
        }, [
          (openBlock(true), createElementBlock(Fragment, null, renderList(unref(tabLabels), (tabLabel) => {
            return openBlock(), createElementBlock("button", {
              id: `tab-${tabLabel}-${unref(uid)}`,
              ref_for: true,
              ref_key: "buttonRefs",
              ref: buttonRefs,
              key: tabLabel,
              role: "tab",
              class: "plugin-tabs--tab",
              "aria-selected": tabLabel === unref(selected),
              "aria-controls": `panel-${tabLabel}-${unref(uid)}`,
              tabindex: tabLabel === unref(selected) ? 0 : -1,
              onClick: () => unref(selectStable)(tabLabel)
            }, toDisplayString(tabLabel), 9, _hoisted_2);
          }), 128))
        ], 544),
        renderSlot(_ctx.$slots, "default")
      ]);
    };
  }
});
const _hoisted_1 = ["id", "aria-labelledby"];
const _sfc_main$1 = /* @__PURE__ */ defineComponent({
  __name: "PluginTabsTab",
  props: {
    label: {}
  },
  setup(__props) {
    const { uid, selected } = useTabsSingleState();
    return (_ctx, _cache) => {
      return unref(selected) === _ctx.label ? (openBlock(), createElementBlock("div", {
        key: 0,
        id: `panel-${_ctx.label}-${unref(uid)}`,
        class: "plugin-tabs--content",
        role: "tabpanel",
        tabindex: "0",
        "aria-labelledby": `tab-${_ctx.label}-${unref(uid)}`
      }, [
        renderSlot(_ctx.$slots, "default", {}, void 0, true)
      ], 8, _hoisted_1)) : createCommentVNode("", true);
    };
  }
});
const PluginTabsTab = /* @__PURE__ */ _export_sfc(_sfc_main$1, [["__scopeId", "data-v-b2b19630"]]);
const enhanceAppWithTabs = (app) => {
  provideTabsSharedState(app);
  app.component("PluginTabs", _sfc_main$2);
  app.component("PluginTabsTab", PluginTabsTab);
};
const aliases = {
  "/adding_a_keyboard_to_qmk": "/hardware_keyboard_guidelines",
  "/build_environment_setup": "/newbs_getting_started",
  "/cli_dev_configuration": "/cli_configuration",
  "/dynamic_macros": "/feature_dynamic_macros",
  "/feature_common_shortcuts": "/feature_advanced_keycodes",
  "/flashing_bootloadhid": "/flashing",
  "/getting_started_build_tools": "/newbs_getting_started",
  "/getting_started_getting_help": "/support",
  "/glossary": "/reference_glossary",
  "/key_lock": "/feature_key_lock",
  "/make_instructions": "/getting_started_make_guide",
  "/python_development": "/cli_development",
  "/space_cadet_shift": "/feature_space_cadet_shift",
  "/tap_dance": "/feature_tap_dance",
  "/tutorial": "/newbs",
  "/unicode": "/feature_unicode",
  "/features/bluetooth": "/features/wireless",
  "/adc_driver": "/drivers/adc",
  "/apa102_driver": "/drivers/apa102",
  "/audio_driver": "/drivers/audio",
  "/eeprom_driver": "/drivers/eeprom",
  "/feature_audio": "/features/audio",
  "/feature_auto_shift": "/features/auto_shift",
  "/feature_autocorrect": "/features/autocorrect",
  "/feature_backlight": "/features/backlight",
  "/feature_bluetooth": "/features/wireless",
  "/feature_bootmagic": "/features/bootmagic",
  "/feature_caps_word": "/features/caps_word",
  "/feature_combo": "/features/combo",
  "/feature_command": "/features/command",
  "/feature_digitizer": "/features/digitizer",
  "/feature_dip_switch": "/features/dip_switch",
  "/feature_dynamic_macros": "/features/dynamic_macros",
  "/feature_encoders": "/features/encoders",
  "/feature_grave_esc": "/features/grave_esc",
  "/feature_haptic_feedback": "/features/haptic_feedback",
  "/feature_hd44780": "/features/hd44780",
  "/feature_joystick": "/features/joystick",
  "/feature_key_lock": "/features/key_lock",
  "/feature_key_overrides": "/features/key_overrides",
  "/feature_leader_key": "/features/leader_key",
  "/feature_led_indicators": "/features/led_indicators",
  "/feature_led_matrix": "/features/led_matrix",
  "/feature_midi": "/features/midi",
  "/feature_mouse_keys": "/features/mouse_keys",
  "/feature_oled_driver": "/features/oled_driver",
  "/feature_os_detection": "/features/os_detection",
  "/feature_pointing_device": "/features/pointing_device",
  "/feature_programmable_button": "/features/programmable_button",
  "/feature_ps2_mouse": "/features/ps2_mouse",
  "/feature_rawhid": "/features/rawhid",
  "/feature_repeat_key": "/features/repeat_key",
  "/feature_rgb_matrix": "/features/rgb_matrix",
  "/feature_rgblight": "/features/rgblight",
  "/feature_secure": "/features/secure",
  "/feature_send_string": "/features/send_string",
  "/feature_sequencer": "/features/sequencer",
  "/feature_space_cadet": "/features/space_cadet",
  "/feature_split_keyboard": "/features/split_keyboard",
  "/feature_st7565": "/features/st7565",
  "/feature_stenography": "/features/stenography",
  "/feature_swap_hands": "/features/swap_hands",
  "/feature_tap_dance": "/features/tap_dance",
  "/feature_tri_layer": "/features/tri_layer",
  "/feature_unicode": "/features/unicode",
  "/feature_wpm": "/features/wpm",
  "/flash_driver": "/drivers/flash",
  "/gpio_control": "/drivers/gpio",
  "/i2c_driver": "/drivers/i2c",
  "/serial_driver": "/drivers/serial",
  "/spi_driver": "/drivers/spi",
  "/uart_driver": "/drivers/uart",
  "/ws2812_driver": "/drivers/ws2812"
};
const _sfc_main = {
  __name: "QMKLayout",
  setup(__props) {
    const router = useRouter();
    onBeforeMount(async () => {
      let newUrl = window.location.href.replace(/\/#\//, "/").replace(/\?id=/, "#");
      let testUrl = new URL(newUrl);
      while (testUrl.pathname in aliases) {
        testUrl.pathname = aliases[testUrl.pathname];
      }
      newUrl = testUrl.toString();
      if (newUrl != window.location.href) {
        window.history.replaceState({}, "", newUrl);
        await router.go(newUrl);
      }
    });
    return (_ctx, _cache) => {
      return openBlock(), createBlock(unref(theme).Layout);
    };
  }
};
const RawTheme = {
  extends: theme,
  Layout: _sfc_main,
  enhanceApp({ app }) {
    enhanceAppWithTabs(app);
  }
};
export {
  RawTheme as R,
  createSearchTranslate as c,
  useData as u
};
