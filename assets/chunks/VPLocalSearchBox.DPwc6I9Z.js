var __defProp = Object.defineProperty;
var __defNormalProp = (obj, key, value) => key in obj ? __defProp(obj, key, { enumerable: true, configurable: true, writable: true, value }) : obj[key] = value;
var __publicField = (obj, key, value) => __defNormalProp(obj, typeof key !== "symbol" ? key + "" : key, value);
import { Y as __vitePreload, j as ref, x as watch, an as unrefElement, ao as tryOnScopeDispose, d as defineComponent, G as shallowRef, ap as computedAsync, h as computed, aq as useSessionStorage, ar as useLocalStorage, y as watchEffect, as as watchDebounced, k as onMounted, S as nextTick, R as onKeyStroke, a6 as useRouter, at as useEventListener, Z as useScrollLock, V as inBrowser, au as onBeforeUnmount, o as openBlock, b as createBlock, l as createBaseVNode, a2 as withModifiers, m as unref, av as withDirectives, aw as vModelText, ax as isRef, c as createElementBlock, n as normalizeClass, e as createCommentVNode, E as renderList, F as Fragment, a as createTextVNode, t as toDisplayString, ay as Teleport, p as pushScopeId, q as popScopeId, az as markRaw, aA as createApp, ac as dataSymbol, ai as pathToFile, aB as escapeRegExp, _ as _export_sfc } from "./framework.Cauyuiy8.js";
import { u as useData, c as createSearchTranslate } from "./theme.DnVB8IHM.js";
const localSearchIndex = { "root": () => __vitePreload(() => import("./@localSearchIndexroot.BVETFjrV.js"), true ? [] : void 0) };
/*!
* tabbable 6.2.0
* @license MIT, https://github.com/focus-trap/tabbable/blob/master/LICENSE
*/
var candidateSelectors = ["input:not([inert])", "select:not([inert])", "textarea:not([inert])", "a[href]:not([inert])", "button:not([inert])", "[tabindex]:not(slot):not([inert])", "audio[controls]:not([inert])", "video[controls]:not([inert])", '[contenteditable]:not([contenteditable="false"]):not([inert])', "details>summary:first-of-type:not([inert])", "details:not([inert])"];
var candidateSelector = /* @__PURE__ */ candidateSelectors.join(",");
var NoElement = typeof Element === "undefined";
var matches = NoElement ? function() {
} : Element.prototype.matches || Element.prototype.msMatchesSelector || Element.prototype.webkitMatchesSelector;
var getRootNode = !NoElement && Element.prototype.getRootNode ? function(element) {
  var _element$getRootNode;
  return element === null || element === void 0 ? void 0 : (_element$getRootNode = element.getRootNode) === null || _element$getRootNode === void 0 ? void 0 : _element$getRootNode.call(element);
} : function(element) {
  return element === null || element === void 0 ? void 0 : element.ownerDocument;
};
var isInert = function isInert2(node, lookUp) {
  var _node$getAttribute;
  if (lookUp === void 0) {
    lookUp = true;
  }
  var inertAtt = node === null || node === void 0 ? void 0 : (_node$getAttribute = node.getAttribute) === null || _node$getAttribute === void 0 ? void 0 : _node$getAttribute.call(node, "inert");
  var inert = inertAtt === "" || inertAtt === "true";
  var result = inert || lookUp && node && isInert2(node.parentNode);
  return result;
};
var isContentEditable = function isContentEditable2(node) {
  var _node$getAttribute2;
  var attValue = node === null || node === void 0 ? void 0 : (_node$getAttribute2 = node.getAttribute) === null || _node$getAttribute2 === void 0 ? void 0 : _node$getAttribute2.call(node, "contenteditable");
  return attValue === "" || attValue === "true";
};
var getCandidates = function getCandidates2(el, includeContainer, filter) {
  if (isInert(el)) {
    return [];
  }
  var candidates = Array.prototype.slice.apply(el.querySelectorAll(candidateSelector));
  if (includeContainer && matches.call(el, candidateSelector)) {
    candidates.unshift(el);
  }
  candidates = candidates.filter(filter);
  return candidates;
};
var getCandidatesIteratively = function getCandidatesIteratively2(elements, includeContainer, options) {
  var candidates = [];
  var elementsToCheck = Array.from(elements);
  while (elementsToCheck.length) {
    var element = elementsToCheck.shift();
    if (isInert(element, false)) {
      continue;
    }
    if (element.tagName === "SLOT") {
      var assigned = element.assignedElements();
      var content = assigned.length ? assigned : element.children;
      var nestedCandidates = getCandidatesIteratively2(content, true, options);
      if (options.flatten) {
        candidates.push.apply(candidates, nestedCandidates);
      } else {
        candidates.push({
          scopeParent: element,
          candidates: nestedCandidates
        });
      }
    } else {
      var validCandidate = matches.call(element, candidateSelector);
      if (validCandidate && options.filter(element) && (includeContainer || !elements.includes(element))) {
        candidates.push(element);
      }
      var shadowRoot = element.shadowRoot || // check for an undisclosed shadow
      typeof options.getShadowRoot === "function" && options.getShadowRoot(element);
      var validShadowRoot = !isInert(shadowRoot, false) && (!options.shadowRootFilter || options.shadowRootFilter(element));
      if (shadowRoot && validShadowRoot) {
        var _nestedCandidates = getCandidatesIteratively2(shadowRoot === true ? element.children : shadowRoot.children, true, options);
        if (options.flatten) {
          candidates.push.apply(candidates, _nestedCandidates);
        } else {
          candidates.push({
            scopeParent: element,
            candidates: _nestedCandidates
          });
        }
      } else {
        elementsToCheck.unshift.apply(elementsToCheck, element.children);
      }
    }
  }
  return candidates;
};
var hasTabIndex = function hasTabIndex2(node) {
  return !isNaN(parseInt(node.getAttribute("tabindex"), 10));
};
var getTabIndex = function getTabIndex2(node) {
  if (!node) {
    throw new Error("No node provided");
  }
  if (node.tabIndex < 0) {
    if ((/^(AUDIO|VIDEO|DETAILS)$/.test(node.tagName) || isContentEditable(node)) && !hasTabIndex(node)) {
      return 0;
    }
  }
  return node.tabIndex;
};
var getSortOrderTabIndex = function getSortOrderTabIndex2(node, isScope) {
  var tabIndex = getTabIndex(node);
  if (tabIndex < 0 && isScope && !hasTabIndex(node)) {
    return 0;
  }
  return tabIndex;
};
var sortOrderedTabbables = function sortOrderedTabbables2(a, b) {
  return a.tabIndex === b.tabIndex ? a.documentOrder - b.documentOrder : a.tabIndex - b.tabIndex;
};
var isInput = function isInput2(node) {
  return node.tagName === "INPUT";
};
var isHiddenInput = function isHiddenInput2(node) {
  return isInput(node) && node.type === "hidden";
};
var isDetailsWithSummary = function isDetailsWithSummary2(node) {
  var r = node.tagName === "DETAILS" && Array.prototype.slice.apply(node.children).some(function(child) {
    return child.tagName === "SUMMARY";
  });
  return r;
};
var getCheckedRadio = function getCheckedRadio2(nodes, form) {
  for (var i = 0; i < nodes.length; i++) {
    if (nodes[i].checked && nodes[i].form === form) {
      return nodes[i];
    }
  }
};
var isTabbableRadio = function isTabbableRadio2(node) {
  if (!node.name) {
    return true;
  }
  var radioScope = node.form || getRootNode(node);
  var queryRadios = function queryRadios2(name) {
    return radioScope.querySelectorAll('input[type="radio"][name="' + name + '"]');
  };
  var radioSet;
  if (typeof window !== "undefined" && typeof window.CSS !== "undefined" && typeof window.CSS.escape === "function") {
    radioSet = queryRadios(window.CSS.escape(node.name));
  } else {
    try {
      radioSet = queryRadios(node.name);
    } catch (err) {
      console.error("Looks like you have a radio button with a name attribute containing invalid CSS selector characters and need the CSS.escape polyfill: %s", err.message);
      return false;
    }
  }
  var checked = getCheckedRadio(radioSet, node.form);
  return !checked || checked === node;
};
var isRadio = function isRadio2(node) {
  return isInput(node) && node.type === "radio";
};
var isNonTabbableRadio = function isNonTabbableRadio2(node) {
  return isRadio(node) && !isTabbableRadio(node);
};
var isNodeAttached = function isNodeAttached2(node) {
  var _nodeRoot;
  var nodeRoot = node && getRootNode(node);
  var nodeRootHost = (_nodeRoot = nodeRoot) === null || _nodeRoot === void 0 ? void 0 : _nodeRoot.host;
  var attached = false;
  if (nodeRoot && nodeRoot !== node) {
    var _nodeRootHost, _nodeRootHost$ownerDo, _node$ownerDocument;
    attached = !!((_nodeRootHost = nodeRootHost) !== null && _nodeRootHost !== void 0 && (_nodeRootHost$ownerDo = _nodeRootHost.ownerDocument) !== null && _nodeRootHost$ownerDo !== void 0 && _nodeRootHost$ownerDo.contains(nodeRootHost) || node !== null && node !== void 0 && (_node$ownerDocument = node.ownerDocument) !== null && _node$ownerDocument !== void 0 && _node$ownerDocument.contains(node));
    while (!attached && nodeRootHost) {
      var _nodeRoot2, _nodeRootHost2, _nodeRootHost2$ownerD;
      nodeRoot = getRootNode(nodeRootHost);
      nodeRootHost = (_nodeRoot2 = nodeRoot) === null || _nodeRoot2 === void 0 ? void 0 : _nodeRoot2.host;
      attached = !!((_nodeRootHost2 = nodeRootHost) !== null && _nodeRootHost2 !== void 0 && (_nodeRootHost2$ownerD = _nodeRootHost2.ownerDocument) !== null && _nodeRootHost2$ownerD !== void 0 && _nodeRootHost2$ownerD.contains(nodeRootHost));
    }
  }
  return attached;
};
var isZeroArea = function isZeroArea2(node) {
  var _node$getBoundingClie = node.getBoundingClientRect(), width = _node$getBoundingClie.width, height = _node$getBoundingClie.height;
  return width === 0 && height === 0;
};
var isHidden = function isHidden2(node, _ref) {
  var displayCheck = _ref.displayCheck, getShadowRoot = _ref.getShadowRoot;
  if (getComputedStyle(node).visibility === "hidden") {
    return true;
  }
  var isDirectSummary = matches.call(node, "details>summary:first-of-type");
  var nodeUnderDetails = isDirectSummary ? node.parentElement : node;
  if (matches.call(nodeUnderDetails, "details:not([open]) *")) {
    return true;
  }
  if (!displayCheck || displayCheck === "full" || displayCheck === "legacy-full") {
    if (typeof getShadowRoot === "function") {
      var originalNode = node;
      while (node) {
        var parentElement = node.parentElement;
        var rootNode = getRootNode(node);
        if (parentElement && !parentElement.shadowRoot && getShadowRoot(parentElement) === true) {
          return isZeroArea(node);
        } else if (node.assignedSlot) {
          node = node.assignedSlot;
        } else if (!parentElement && rootNode !== node.ownerDocument) {
          node = rootNode.host;
        } else {
          node = parentElement;
        }
      }
      node = originalNode;
    }
    if (isNodeAttached(node)) {
      return !node.getClientRects().length;
    }
    if (displayCheck !== "legacy-full") {
      return true;
    }
  } else if (displayCheck === "non-zero-area") {
    return isZeroArea(node);
  }
  return false;
};
var isDisabledFromFieldset = function isDisabledFromFieldset2(node) {
  if (/^(INPUT|BUTTON|SELECT|TEXTAREA)$/.test(node.tagName)) {
    var parentNode = node.parentElement;
    while (parentNode) {
      if (parentNode.tagName === "FIELDSET" && parentNode.disabled) {
        for (var i = 0; i < parentNode.children.length; i++) {
          var child = parentNode.children.item(i);
          if (child.tagName === "LEGEND") {
            return matches.call(parentNode, "fieldset[disabled] *") ? true : !child.contains(node);
          }
        }
        return true;
      }
      parentNode = parentNode.parentElement;
    }
  }
  return false;
};
var isNodeMatchingSelectorFocusable = function isNodeMatchingSelectorFocusable2(options, node) {
  if (node.disabled || // we must do an inert look up to filter out any elements inside an inert ancestor
  //  because we're limited in the type of selectors we can use in JSDom (see related
  //  note related to `candidateSelectors`)
  isInert(node) || isHiddenInput(node) || isHidden(node, options) || // For a details element with a summary, the summary element gets the focus
  isDetailsWithSummary(node) || isDisabledFromFieldset(node)) {
    return false;
  }
  return true;
};
var isNodeMatchingSelectorTabbable = function isNodeMatchingSelectorTabbable2(options, node) {
  if (isNonTabbableRadio(node) || getTabIndex(node) < 0 || !isNodeMatchingSelectorFocusable(options, node)) {
    return false;
  }
  return true;
};
var isValidShadowRootTabbable = function isValidShadowRootTabbable2(shadowHostNode) {
  var tabIndex = parseInt(shadowHostNode.getAttribute("tabindex"), 10);
  if (isNaN(tabIndex) || tabIndex >= 0) {
    return true;
  }
  return false;
};
var sortByOrder = function sortByOrder2(candidates) {
  var regularTabbables = [];
  var orderedTabbables = [];
  candidates.forEach(function(item, i) {
    var isScope = !!item.scopeParent;
    var element = isScope ? item.scopeParent : item;
    var candidateTabindex = getSortOrderTabIndex(element, isScope);
    var elements = isScope ? sortByOrder2(item.candidates) : element;
    if (candidateTabindex === 0) {
      isScope ? regularTabbables.push.apply(regularTabbables, elements) : regularTabbables.push(element);
    } else {
      orderedTabbables.push({
        documentOrder: i,
        tabIndex: candidateTabindex,
        item,
        isScope,
        content: elements
      });
    }
  });
  return orderedTabbables.sort(sortOrderedTabbables).reduce(function(acc, sortable) {
    sortable.isScope ? acc.push.apply(acc, sortable.content) : acc.push(sortable.content);
    return acc;
  }, []).concat(regularTabbables);
};
var tabbable = function tabbable2(container, options) {
  options = options || {};
  var candidates;
  if (options.getShadowRoot) {
    candidates = getCandidatesIteratively([container], options.includeContainer, {
      filter: isNodeMatchingSelectorTabbable.bind(null, options),
      flatten: false,
      getShadowRoot: options.getShadowRoot,
      shadowRootFilter: isValidShadowRootTabbable
    });
  } else {
    candidates = getCandidates(container, options.includeContainer, isNodeMatchingSelectorTabbable.bind(null, options));
  }
  return sortByOrder(candidates);
};
var focusable = function focusable2(container, options) {
  options = options || {};
  var candidates;
  if (options.getShadowRoot) {
    candidates = getCandidatesIteratively([container], options.includeContainer, {
      filter: isNodeMatchingSelectorFocusable.bind(null, options),
      flatten: true,
      getShadowRoot: options.getShadowRoot
    });
  } else {
    candidates = getCandidates(container, options.includeContainer, isNodeMatchingSelectorFocusable.bind(null, options));
  }
  return candidates;
};
var isTabbable = function isTabbable2(node, options) {
  options = options || {};
  if (!node) {
    throw new Error("No node provided");
  }
  if (matches.call(node, candidateSelector) === false) {
    return false;
  }
  return isNodeMatchingSelectorTabbable(options, node);
};
var focusableCandidateSelector = /* @__PURE__ */ candidateSelectors.concat("iframe").join(",");
var isFocusable = function isFocusable2(node, options) {
  options = options || {};
  if (!node) {
    throw new Error("No node provided");
  }
  if (matches.call(node, focusableCandidateSelector) === false) {
    return false;
  }
  return isNodeMatchingSelectorFocusable(options, node);
};
/*!
* focus-trap 7.5.4
* @license MIT, https://github.com/focus-trap/focus-trap/blob/master/LICENSE
*/
function ownKeys(e, r) {
  var t = Object.keys(e);
  if (Object.getOwnPropertySymbols) {
    var o = Object.getOwnPropertySymbols(e);
    r && (o = o.filter(function(r2) {
      return Object.getOwnPropertyDescriptor(e, r2).enumerable;
    })), t.push.apply(t, o);
  }
  return t;
}
function _objectSpread2(e) {
  for (var r = 1; r < arguments.length; r++) {
    var t = null != arguments[r] ? arguments[r] : {};
    r % 2 ? ownKeys(Object(t), true).forEach(function(r2) {
      _defineProperty(e, r2, t[r2]);
    }) : Object.getOwnPropertyDescriptors ? Object.defineProperties(e, Object.getOwnPropertyDescriptors(t)) : ownKeys(Object(t)).forEach(function(r2) {
      Object.defineProperty(e, r2, Object.getOwnPropertyDescriptor(t, r2));
    });
  }
  return e;
}
function _defineProperty(obj, key, value) {
  key = _toPropertyKey(key);
  if (key in obj) {
    Object.defineProperty(obj, key, {
      value,
      enumerable: true,
      configurable: true,
      writable: true
    });
  } else {
    obj[key] = value;
  }
  return obj;
}
function _toPrimitive(input, hint) {
  if (typeof input !== "object" || input === null) return input;
  var prim = input[Symbol.toPrimitive];
  if (prim !== void 0) {
    var res = prim.call(input, hint || "default");
    if (typeof res !== "object") return res;
    throw new TypeError("@@toPrimitive must return a primitive value.");
  }
  return (hint === "string" ? String : Number)(input);
}
function _toPropertyKey(arg) {
  var key = _toPrimitive(arg, "string");
  return typeof key === "symbol" ? key : String(key);
}
var activeFocusTraps = {
  activateTrap: function activateTrap(trapStack, trap) {
    if (trapStack.length > 0) {
      var activeTrap = trapStack[trapStack.length - 1];
      if (activeTrap !== trap) {
        activeTrap.pause();
      }
    }
    var trapIndex = trapStack.indexOf(trap);
    if (trapIndex === -1) {
      trapStack.push(trap);
    } else {
      trapStack.splice(trapIndex, 1);
      trapStack.push(trap);
    }
  },
  deactivateTrap: function deactivateTrap(trapStack, trap) {
    var trapIndex = trapStack.indexOf(trap);
    if (trapIndex !== -1) {
      trapStack.splice(trapIndex, 1);
    }
    if (trapStack.length > 0) {
      trapStack[trapStack.length - 1].unpause();
    }
  }
};
var isSelectableInput = function isSelectableInput2(node) {
  return node.tagName && node.tagName.toLowerCase() === "input" && typeof node.select === "function";
};
var isEscapeEvent = function isEscapeEvent2(e) {
  return (e === null || e === void 0 ? void 0 : e.key) === "Escape" || (e === null || e === void 0 ? void 0 : e.key) === "Esc" || (e === null || e === void 0 ? void 0 : e.keyCode) === 27;
};
var isTabEvent = function isTabEvent2(e) {
  return (e === null || e === void 0 ? void 0 : e.key) === "Tab" || (e === null || e === void 0 ? void 0 : e.keyCode) === 9;
};
var isKeyForward = function isKeyForward2(e) {
  return isTabEvent(e) && !e.shiftKey;
};
var isKeyBackward = function isKeyBackward2(e) {
  return isTabEvent(e) && e.shiftKey;
};
var delay = function delay2(fn) {
  return setTimeout(fn, 0);
};
var findIndex = function findIndex2(arr, fn) {
  var idx = -1;
  arr.every(function(value, i) {
    if (fn(value)) {
      idx = i;
      return false;
    }
    return true;
  });
  return idx;
};
var valueOrHandler = function valueOrHandler2(value) {
  for (var _len = arguments.length, params = new Array(_len > 1 ? _len - 1 : 0), _key = 1; _key < _len; _key++) {
    params[_key - 1] = arguments[_key];
  }
  return typeof value === "function" ? value.apply(void 0, params) : value;
};
var getActualTarget = function getActualTarget2(event) {
  return event.target.shadowRoot && typeof event.composedPath === "function" ? event.composedPath()[0] : event.target;
};
var internalTrapStack = [];
var createFocusTrap = function createFocusTrap2(elements, userOptions) {
  var doc = (userOptions === null || userOptions === void 0 ? void 0 : userOptions.document) || document;
  var trapStack = (userOptions === null || userOptions === void 0 ? void 0 : userOptions.trapStack) || internalTrapStack;
  var config = _objectSpread2({
    returnFocusOnDeactivate: true,
    escapeDeactivates: true,
    delayInitialFocus: true,
    isKeyForward,
    isKeyBackward
  }, userOptions);
  var state = {
    // containers given to createFocusTrap()
    // @type {Array<HTMLElement>}
    containers: [],
    // list of objects identifying tabbable nodes in `containers` in the trap
    // NOTE: it's possible that a group has no tabbable nodes if nodes get removed while the trap
    //  is active, but the trap should never get to a state where there isn't at least one group
    //  with at least one tabbable node in it (that would lead to an error condition that would
    //  result in an error being thrown)
    // @type {Array<{
    //   container: HTMLElement,
    //   tabbableNodes: Array<HTMLElement>, // empty if none
    //   focusableNodes: Array<HTMLElement>, // empty if none
    //   posTabIndexesFound: boolean,
    //   firstTabbableNode: HTMLElement|undefined,
    //   lastTabbableNode: HTMLElement|undefined,
    //   firstDomTabbableNode: HTMLElement|undefined,
    //   lastDomTabbableNode: HTMLElement|undefined,
    //   nextTabbableNode: (node: HTMLElement, forward: boolean) => HTMLElement|undefined
    // }>}
    containerGroups: [],
    // same order/length as `containers` list
    // references to objects in `containerGroups`, but only those that actually have
    //  tabbable nodes in them
    // NOTE: same order as `containers` and `containerGroups`, but __not necessarily__
    //  the same length
    tabbableGroups: [],
    nodeFocusedBeforeActivation: null,
    mostRecentlyFocusedNode: null,
    active: false,
    paused: false,
    // timer ID for when delayInitialFocus is true and initial focus in this trap
    //  has been delayed during activation
    delayInitialFocusTimer: void 0,
    // the most recent KeyboardEvent for the configured nav key (typically [SHIFT+]TAB), if any
    recentNavEvent: void 0
  };
  var trap;
  var getOption = function getOption2(configOverrideOptions, optionName, configOptionName) {
    return configOverrideOptions && configOverrideOptions[optionName] !== void 0 ? configOverrideOptions[optionName] : config[configOptionName || optionName];
  };
  var findContainerIndex = function findContainerIndex2(element, event) {
    var composedPath = typeof (event === null || event === void 0 ? void 0 : event.composedPath) === "function" ? event.composedPath() : void 0;
    return state.containerGroups.findIndex(function(_ref) {
      var container = _ref.container, tabbableNodes = _ref.tabbableNodes;
      return container.contains(element) || // fall back to explicit tabbable search which will take into consideration any
      //  web components if the `tabbableOptions.getShadowRoot` option was used for
      //  the trap, enabling shadow DOM support in tabbable (`Node.contains()` doesn't
      //  look inside web components even if open)
      (composedPath === null || composedPath === void 0 ? void 0 : composedPath.includes(container)) || tabbableNodes.find(function(node) {
        return node === element;
      });
    });
  };
  var getNodeForOption = function getNodeForOption2(optionName) {
    var optionValue = config[optionName];
    if (typeof optionValue === "function") {
      for (var _len2 = arguments.length, params = new Array(_len2 > 1 ? _len2 - 1 : 0), _key2 = 1; _key2 < _len2; _key2++) {
        params[_key2 - 1] = arguments[_key2];
      }
      optionValue = optionValue.apply(void 0, params);
    }
    if (optionValue === true) {
      optionValue = void 0;
    }
    if (!optionValue) {
      if (optionValue === void 0 || optionValue === false) {
        return optionValue;
      }
      throw new Error("`".concat(optionName, "` was specified but was not a node, or did not return a node"));
    }
    var node = optionValue;
    if (typeof optionValue === "string") {
      node = doc.querySelector(optionValue);
      if (!node) {
        throw new Error("`".concat(optionName, "` as selector refers to no known node"));
      }
    }
    return node;
  };
  var getInitialFocusNode = function getInitialFocusNode2() {
    var node = getNodeForOption("initialFocus");
    if (node === false) {
      return false;
    }
    if (node === void 0 || !isFocusable(node, config.tabbableOptions)) {
      if (findContainerIndex(doc.activeElement) >= 0) {
        node = doc.activeElement;
      } else {
        var firstTabbableGroup = state.tabbableGroups[0];
        var firstTabbableNode = firstTabbableGroup && firstTabbableGroup.firstTabbableNode;
        node = firstTabbableNode || getNodeForOption("fallbackFocus");
      }
    }
    if (!node) {
      throw new Error("Your focus-trap needs to have at least one focusable element");
    }
    return node;
  };
  var updateTabbableNodes = function updateTabbableNodes2() {
    state.containerGroups = state.containers.map(function(container) {
      var tabbableNodes = tabbable(container, config.tabbableOptions);
      var focusableNodes = focusable(container, config.tabbableOptions);
      var firstTabbableNode = tabbableNodes.length > 0 ? tabbableNodes[0] : void 0;
      var lastTabbableNode = tabbableNodes.length > 0 ? tabbableNodes[tabbableNodes.length - 1] : void 0;
      var firstDomTabbableNode = focusableNodes.find(function(node) {
        return isTabbable(node);
      });
      var lastDomTabbableNode = focusableNodes.slice().reverse().find(function(node) {
        return isTabbable(node);
      });
      var posTabIndexesFound = !!tabbableNodes.find(function(node) {
        return getTabIndex(node) > 0;
      });
      return {
        container,
        tabbableNodes,
        focusableNodes,
        /** True if at least one node with positive `tabindex` was found in this container. */
        posTabIndexesFound,
        /** First tabbable node in container, __tabindex__ order; `undefined` if none. */
        firstTabbableNode,
        /** Last tabbable node in container, __tabindex__ order; `undefined` if none. */
        lastTabbableNode,
        // NOTE: DOM order is NOT NECESSARILY "document position" order, but figuring that out
        //  would require more than just https://developer.mozilla.org/en-US/docs/Web/API/Node/compareDocumentPosition
        //  because that API doesn't work with Shadow DOM as well as it should (@see
        //  https://github.com/whatwg/dom/issues/320) and since this first/last is only needed, so far,
        //  to address an edge case related to positive tabindex support, this seems like a much easier,
        //  "close enough most of the time" alternative for positive tabindexes which should generally
        //  be avoided anyway...
        /** First tabbable node in container, __DOM__ order; `undefined` if none. */
        firstDomTabbableNode,
        /** Last tabbable node in container, __DOM__ order; `undefined` if none. */
        lastDomTabbableNode,
        /**
         * Finds the __tabbable__ node that follows the given node in the specified direction,
         *  in this container, if any.
         * @param {HTMLElement} node
         * @param {boolean} [forward] True if going in forward tab order; false if going
         *  in reverse.
         * @returns {HTMLElement|undefined} The next tabbable node, if any.
         */
        nextTabbableNode: function nextTabbableNode(node) {
          var forward = arguments.length > 1 && arguments[1] !== void 0 ? arguments[1] : true;
          var nodeIdx = tabbableNodes.indexOf(node);
          if (nodeIdx < 0) {
            if (forward) {
              return focusableNodes.slice(focusableNodes.indexOf(node) + 1).find(function(el) {
                return isTabbable(el);
              });
            }
            return focusableNodes.slice(0, focusableNodes.indexOf(node)).reverse().find(function(el) {
              return isTabbable(el);
            });
          }
          return tabbableNodes[nodeIdx + (forward ? 1 : -1)];
        }
      };
    });
    state.tabbableGroups = state.containerGroups.filter(function(group) {
      return group.tabbableNodes.length > 0;
    });
    if (state.tabbableGroups.length <= 0 && !getNodeForOption("fallbackFocus")) {
      throw new Error("Your focus-trap must have at least one container with at least one tabbable node in it at all times");
    }
    if (state.containerGroups.find(function(g) {
      return g.posTabIndexesFound;
    }) && state.containerGroups.length > 1) {
      throw new Error("At least one node with a positive tabindex was found in one of your focus-trap's multiple containers. Positive tabindexes are only supported in single-container focus-traps.");
    }
  };
  var getActiveElement = function getActiveElement2(el) {
    var activeElement = el.activeElement;
    if (!activeElement) {
      return;
    }
    if (activeElement.shadowRoot && activeElement.shadowRoot.activeElement !== null) {
      return getActiveElement2(activeElement.shadowRoot);
    }
    return activeElement;
  };
  var tryFocus = function tryFocus2(node) {
    if (node === false) {
      return;
    }
    if (node === getActiveElement(document)) {
      return;
    }
    if (!node || !node.focus) {
      tryFocus2(getInitialFocusNode());
      return;
    }
    node.focus({
      preventScroll: !!config.preventScroll
    });
    state.mostRecentlyFocusedNode = node;
    if (isSelectableInput(node)) {
      node.select();
    }
  };
  var getReturnFocusNode = function getReturnFocusNode2(previousActiveElement) {
    var node = getNodeForOption("setReturnFocus", previousActiveElement);
    return node ? node : node === false ? false : previousActiveElement;
  };
  var findNextNavNode = function findNextNavNode2(_ref2) {
    var target = _ref2.target, event = _ref2.event, _ref2$isBackward = _ref2.isBackward, isBackward = _ref2$isBackward === void 0 ? false : _ref2$isBackward;
    target = target || getActualTarget(event);
    updateTabbableNodes();
    var destinationNode = null;
    if (state.tabbableGroups.length > 0) {
      var containerIndex = findContainerIndex(target, event);
      var containerGroup = containerIndex >= 0 ? state.containerGroups[containerIndex] : void 0;
      if (containerIndex < 0) {
        if (isBackward) {
          destinationNode = state.tabbableGroups[state.tabbableGroups.length - 1].lastTabbableNode;
        } else {
          destinationNode = state.tabbableGroups[0].firstTabbableNode;
        }
      } else if (isBackward) {
        var startOfGroupIndex = findIndex(state.tabbableGroups, function(_ref3) {
          var firstTabbableNode = _ref3.firstTabbableNode;
          return target === firstTabbableNode;
        });
        if (startOfGroupIndex < 0 && (containerGroup.container === target || isFocusable(target, config.tabbableOptions) && !isTabbable(target, config.tabbableOptions) && !containerGroup.nextTabbableNode(target, false))) {
          startOfGroupIndex = containerIndex;
        }
        if (startOfGroupIndex >= 0) {
          var destinationGroupIndex = startOfGroupIndex === 0 ? state.tabbableGroups.length - 1 : startOfGroupIndex - 1;
          var destinationGroup = state.tabbableGroups[destinationGroupIndex];
          destinationNode = getTabIndex(target) >= 0 ? destinationGroup.lastTabbableNode : destinationGroup.lastDomTabbableNode;
        } else if (!isTabEvent(event)) {
          destinationNode = containerGroup.nextTabbableNode(target, false);
        }
      } else {
        var lastOfGroupIndex = findIndex(state.tabbableGroups, function(_ref4) {
          var lastTabbableNode = _ref4.lastTabbableNode;
          return target === lastTabbableNode;
        });
        if (lastOfGroupIndex < 0 && (containerGroup.container === target || isFocusable(target, config.tabbableOptions) && !isTabbable(target, config.tabbableOptions) && !containerGroup.nextTabbableNode(target))) {
          lastOfGroupIndex = containerIndex;
        }
        if (lastOfGroupIndex >= 0) {
          var _destinationGroupIndex = lastOfGroupIndex === state.tabbableGroups.length - 1 ? 0 : lastOfGroupIndex + 1;
          var _destinationGroup = state.tabbableGroups[_destinationGroupIndex];
          destinationNode = getTabIndex(target) >= 0 ? _destinationGroup.firstTabbableNode : _destinationGroup.firstDomTabbableNode;
        } else if (!isTabEvent(event)) {
          destinationNode = containerGroup.nextTabbableNode(target);
        }
      }
    } else {
      destinationNode = getNodeForOption("fallbackFocus");
    }
    return destinationNode;
  };
  var checkPointerDown = function checkPointerDown2(e) {
    var target = getActualTarget(e);
    if (findContainerIndex(target, e) >= 0) {
      return;
    }
    if (valueOrHandler(config.clickOutsideDeactivates, e)) {
      trap.deactivate({
        // NOTE: by setting `returnFocus: false`, deactivate() will do nothing,
        //  which will result in the outside click setting focus to the node
        //  that was clicked (and if not focusable, to "nothing"); by setting
        //  `returnFocus: true`, we'll attempt to re-focus the node originally-focused
        //  on activation (or the configured `setReturnFocus` node), whether the
        //  outside click was on a focusable node or not
        returnFocus: config.returnFocusOnDeactivate
      });
      return;
    }
    if (valueOrHandler(config.allowOutsideClick, e)) {
      return;
    }
    e.preventDefault();
  };
  var checkFocusIn = function checkFocusIn2(event) {
    var target = getActualTarget(event);
    var targetContained = findContainerIndex(target, event) >= 0;
    if (targetContained || target instanceof Document) {
      if (targetContained) {
        state.mostRecentlyFocusedNode = target;
      }
    } else {
      event.stopImmediatePropagation();
      var nextNode;
      var navAcrossContainers = true;
      if (state.mostRecentlyFocusedNode) {
        if (getTabIndex(state.mostRecentlyFocusedNode) > 0) {
          var mruContainerIdx = findContainerIndex(state.mostRecentlyFocusedNode);
          var tabbableNodes = state.containerGroups[mruContainerIdx].tabbableNodes;
          if (tabbableNodes.length > 0) {
            var mruTabIdx = tabbableNodes.findIndex(function(node) {
              return node === state.mostRecentlyFocusedNode;
            });
            if (mruTabIdx >= 0) {
              if (config.isKeyForward(state.recentNavEvent)) {
                if (mruTabIdx + 1 < tabbableNodes.length) {
                  nextNode = tabbableNodes[mruTabIdx + 1];
                  navAcrossContainers = false;
                }
              } else {
                if (mruTabIdx - 1 >= 0) {
                  nextNode = tabbableNodes[mruTabIdx - 1];
                  navAcrossContainers = false;
                }
              }
            }
          }
        } else {
          if (!state.containerGroups.some(function(g) {
            return g.tabbableNodes.some(function(n) {
              return getTabIndex(n) > 0;
            });
          })) {
            navAcrossContainers = false;
          }
        }
      } else {
        navAcrossContainers = false;
      }
      if (navAcrossContainers) {
        nextNode = findNextNavNode({
          // move FROM the MRU node, not event-related node (which will be the node that is
          //  outside the trap causing the focus escape we're trying to fix)
          target: state.mostRecentlyFocusedNode,
          isBackward: config.isKeyBackward(state.recentNavEvent)
        });
      }
      if (nextNode) {
        tryFocus(nextNode);
      } else {
        tryFocus(state.mostRecentlyFocusedNode || getInitialFocusNode());
      }
    }
    state.recentNavEvent = void 0;
  };
  var checkKeyNav = function checkKeyNav2(event) {
    var isBackward = arguments.length > 1 && arguments[1] !== void 0 ? arguments[1] : false;
    state.recentNavEvent = event;
    var destinationNode = findNextNavNode({
      event,
      isBackward
    });
    if (destinationNode) {
      if (isTabEvent(event)) {
        event.preventDefault();
      }
      tryFocus(destinationNode);
    }
  };
  var checkKey = function checkKey2(event) {
    if (isEscapeEvent(event) && valueOrHandler(config.escapeDeactivates, event) !== false) {
      event.preventDefault();
      trap.deactivate();
      return;
    }
    if (config.isKeyForward(event) || config.isKeyBackward(event)) {
      checkKeyNav(event, config.isKeyBackward(event));
    }
  };
  var checkClick = function checkClick2(e) {
    var target = getActualTarget(e);
    if (findContainerIndex(target, e) >= 0) {
      return;
    }
    if (valueOrHandler(config.clickOutsideDeactivates, e)) {
      return;
    }
    if (valueOrHandler(config.allowOutsideClick, e)) {
      return;
    }
    e.preventDefault();
    e.stopImmediatePropagation();
  };
  var addListeners = function addListeners2() {
    if (!state.active) {
      return;
    }
    activeFocusTraps.activateTrap(trapStack, trap);
    state.delayInitialFocusTimer = config.delayInitialFocus ? delay(function() {
      tryFocus(getInitialFocusNode());
    }) : tryFocus(getInitialFocusNode());
    doc.addEventListener("focusin", checkFocusIn, true);
    doc.addEventListener("mousedown", checkPointerDown, {
      capture: true,
      passive: false
    });
    doc.addEventListener("touchstart", checkPointerDown, {
      capture: true,
      passive: false
    });
    doc.addEventListener("click", checkClick, {
      capture: true,
      passive: false
    });
    doc.addEventListener("keydown", checkKey, {
      capture: true,
      passive: false
    });
    return trap;
  };
  var removeListeners = function removeListeners2() {
    if (!state.active) {
      return;
    }
    doc.removeEventListener("focusin", checkFocusIn, true);
    doc.removeEventListener("mousedown", checkPointerDown, true);
    doc.removeEventListener("touchstart", checkPointerDown, true);
    doc.removeEventListener("click", checkClick, true);
    doc.removeEventListener("keydown", checkKey, true);
    return trap;
  };
  var checkDomRemoval = function checkDomRemoval2(mutations) {
    var isFocusedNodeRemoved = mutations.some(function(mutation) {
      var removedNodes = Array.from(mutation.removedNodes);
      return removedNodes.some(function(node) {
        return node === state.mostRecentlyFocusedNode;
      });
    });
    if (isFocusedNodeRemoved) {
      tryFocus(getInitialFocusNode());
    }
  };
  var mutationObserver = typeof window !== "undefined" && "MutationObserver" in window ? new MutationObserver(checkDomRemoval) : void 0;
  var updateObservedNodes = function updateObservedNodes2() {
    if (!mutationObserver) {
      return;
    }
    mutationObserver.disconnect();
    if (state.active && !state.paused) {
      state.containers.map(function(container) {
        mutationObserver.observe(container, {
          subtree: true,
          childList: true
        });
      });
    }
  };
  trap = {
    get active() {
      return state.active;
    },
    get paused() {
      return state.paused;
    },
    activate: function activate(activateOptions) {
      if (state.active) {
        return this;
      }
      var onActivate = getOption(activateOptions, "onActivate");
      var onPostActivate = getOption(activateOptions, "onPostActivate");
      var checkCanFocusTrap = getOption(activateOptions, "checkCanFocusTrap");
      if (!checkCanFocusTrap) {
        updateTabbableNodes();
      }
      state.active = true;
      state.paused = false;
      state.nodeFocusedBeforeActivation = doc.activeElement;
      onActivate === null || onActivate === void 0 || onActivate();
      var finishActivation = function finishActivation2() {
        if (checkCanFocusTrap) {
          updateTabbableNodes();
        }
        addListeners();
        updateObservedNodes();
        onPostActivate === null || onPostActivate === void 0 || onPostActivate();
      };
      if (checkCanFocusTrap) {
        checkCanFocusTrap(state.containers.concat()).then(finishActivation, finishActivation);
        return this;
      }
      finishActivation();
      return this;
    },
    deactivate: function deactivate(deactivateOptions) {
      if (!state.active) {
        return this;
      }
      var options = _objectSpread2({
        onDeactivate: config.onDeactivate,
        onPostDeactivate: config.onPostDeactivate,
        checkCanReturnFocus: config.checkCanReturnFocus
      }, deactivateOptions);
      clearTimeout(state.delayInitialFocusTimer);
      state.delayInitialFocusTimer = void 0;
      removeListeners();
      state.active = false;
      state.paused = false;
      updateObservedNodes();
      activeFocusTraps.deactivateTrap(trapStack, trap);
      var onDeactivate = getOption(options, "onDeactivate");
      var onPostDeactivate = getOption(options, "onPostDeactivate");
      var checkCanReturnFocus = getOption(options, "checkCanReturnFocus");
      var returnFocus = getOption(options, "returnFocus", "returnFocusOnDeactivate");
      onDeactivate === null || onDeactivate === void 0 || onDeactivate();
      var finishDeactivation = function finishDeactivation2() {
        delay(function() {
          if (returnFocus) {
            tryFocus(getReturnFocusNode(state.nodeFocusedBeforeActivation));
          }
          onPostDeactivate === null || onPostDeactivate === void 0 || onPostDeactivate();
        });
      };
      if (returnFocus && checkCanReturnFocus) {
        checkCanReturnFocus(getReturnFocusNode(state.nodeFocusedBeforeActivation)).then(finishDeactivation, finishDeactivation);
        return this;
      }
      finishDeactivation();
      return this;
    },
    pause: function pause(pauseOptions) {
      if (state.paused || !state.active) {
        return this;
      }
      var onPause = getOption(pauseOptions, "onPause");
      var onPostPause = getOption(pauseOptions, "onPostPause");
      state.paused = true;
      onPause === null || onPause === void 0 || onPause();
      removeListeners();
      updateObservedNodes();
      onPostPause === null || onPostPause === void 0 || onPostPause();
      return this;
    },
    unpause: function unpause(unpauseOptions) {
      if (!state.paused || !state.active) {
        return this;
      }
      var onUnpause = getOption(unpauseOptions, "onUnpause");
      var onPostUnpause = getOption(unpauseOptions, "onPostUnpause");
      state.paused = false;
      onUnpause === null || onUnpause === void 0 || onUnpause();
      updateTabbableNodes();
      addListeners();
      updateObservedNodes();
      onPostUnpause === null || onPostUnpause === void 0 || onPostUnpause();
      return this;
    },
    updateContainerElements: function updateContainerElements(containerElements) {
      var elementsAsArray = [].concat(containerElements).filter(Boolean);
      state.containers = elementsAsArray.map(function(element) {
        return typeof element === "string" ? doc.querySelector(element) : element;
      });
      if (state.active) {
        updateTabbableNodes();
      }
      updateObservedNodes();
      return this;
    }
  };
  trap.updateContainerElements(elements);
  return trap;
};
function useFocusTrap(target, options = {}) {
  let trap;
  const { immediate, ...focusTrapOptions } = options;
  const hasFocus = ref(false);
  const isPaused = ref(false);
  const activate = (opts) => trap && trap.activate(opts);
  const deactivate = (opts) => trap && trap.deactivate(opts);
  const pause = () => {
    if (trap) {
      trap.pause();
      isPaused.value = true;
    }
  };
  const unpause = () => {
    if (trap) {
      trap.unpause();
      isPaused.value = false;
    }
  };
  watch(
    () => unrefElement(target),
    (el) => {
      if (!el)
        return;
      trap = createFocusTrap(el, {
        ...focusTrapOptions,
        onActivate() {
          hasFocus.value = true;
          if (options.onActivate)
            options.onActivate();
        },
        onDeactivate() {
          hasFocus.value = false;
          if (options.onDeactivate)
            options.onDeactivate();
        }
      });
      if (immediate)
        activate();
    },
    { flush: "post" }
  );
  tryOnScopeDispose(() => deactivate());
  return {
    hasFocus,
    isPaused,
    activate,
    deactivate,
    pause,
    unpause
  };
}
class DOMIterator {
  /**
   * @param {HTMLElement|HTMLElement[]|NodeList|string} ctx - The context DOM
   * element, an array of DOM elements, a NodeList or a selector
   * @param {boolean} [iframes=true] - A boolean indicating if iframes should
   * be handled
   * @param {string[]} [exclude=[]] - An array containing exclusion selectors
   * for iframes
   * @param {number} [iframesTimeout=5000] - A number indicating the ms to
   * wait before an iframe should be skipped, in case the load event isn't
   * fired. This also applies if the user is offline and the resource of the
   * iframe is online (either by the browsers "offline" mode or because
   * there's no internet connection)
   */
  constructor(ctx, iframes = true, exclude = [], iframesTimeout = 5e3) {
    this.ctx = ctx;
    this.iframes = iframes;
    this.exclude = exclude;
    this.iframesTimeout = iframesTimeout;
  }
  /**
   * Checks if the specified DOM element matches the selector
   * @param  {HTMLElement} element - The DOM element
   * @param  {string|string[]} selector - The selector or an array with
   * selectors
   * @return {boolean}
   * @access public
   */
  static matches(element, selector) {
    const selectors = typeof selector === "string" ? [selector] : selector, fn = element.matches || element.matchesSelector || element.msMatchesSelector || element.mozMatchesSelector || element.oMatchesSelector || element.webkitMatchesSelector;
    if (fn) {
      let match = false;
      selectors.every((sel) => {
        if (fn.call(element, sel)) {
          match = true;
          return false;
        }
        return true;
      });
      return match;
    } else {
      return false;
    }
  }
  /**
   * Returns all contexts filtered by duplicates (even nested)
   * @return {HTMLElement[]} - An array containing DOM contexts
   * @access protected
   */
  getContexts() {
    let ctx, filteredCtx = [];
    if (typeof this.ctx === "undefined" || !this.ctx) {
      ctx = [];
    } else if (NodeList.prototype.isPrototypeOf(this.ctx)) {
      ctx = Array.prototype.slice.call(this.ctx);
    } else if (Array.isArray(this.ctx)) {
      ctx = this.ctx;
    } else if (typeof this.ctx === "string") {
      ctx = Array.prototype.slice.call(
        document.querySelectorAll(this.ctx)
      );
    } else {
      ctx = [this.ctx];
    }
    ctx.forEach((ctx2) => {
      const isDescendant = filteredCtx.filter((contexts) => {
        return contexts.contains(ctx2);
      }).length > 0;
      if (filteredCtx.indexOf(ctx2) === -1 && !isDescendant) {
        filteredCtx.push(ctx2);
      }
    });
    return filteredCtx;
  }
  /**
   * @callback DOMIterator~getIframeContentsSuccessCallback
   * @param {HTMLDocument} contents - The contentDocument of the iframe
   */
  /**
   * Calls the success callback function with the iframe document. If it can't
   * be accessed it calls the error callback function
   * @param {HTMLElement} ifr - The iframe DOM element
   * @param {DOMIterator~getIframeContentsSuccessCallback} successFn
   * @param {function} [errorFn]
   * @access protected
   */
  getIframeContents(ifr, successFn, errorFn = () => {
  }) {
    let doc;
    try {
      const ifrWin = ifr.contentWindow;
      doc = ifrWin.document;
      if (!ifrWin || !doc) {
        throw new Error("iframe inaccessible");
      }
    } catch (e) {
      errorFn();
    }
    if (doc) {
      successFn(doc);
    }
  }
  /**
   * Checks if an iframe is empty (if about:blank is the shown page)
   * @param {HTMLElement} ifr - The iframe DOM element
   * @return {boolean}
   * @access protected
   */
  isIframeBlank(ifr) {
    const bl = "about:blank", src = ifr.getAttribute("src").trim(), href = ifr.contentWindow.location.href;
    return href === bl && src !== bl && src;
  }
  /**
   * Observes the onload event of an iframe and calls the success callback or
   * the error callback if the iframe is inaccessible. If the event isn't
   * fired within the specified {@link DOMIterator#iframesTimeout}, then it'll
   * call the error callback too
   * @param {HTMLElement} ifr - The iframe DOM element
   * @param {DOMIterator~getIframeContentsSuccessCallback} successFn
   * @param {function} errorFn
   * @access protected
   */
  observeIframeLoad(ifr, successFn, errorFn) {
    let called = false, tout = null;
    const listener = () => {
      if (called) {
        return;
      }
      called = true;
      clearTimeout(tout);
      try {
        if (!this.isIframeBlank(ifr)) {
          ifr.removeEventListener("load", listener);
          this.getIframeContents(ifr, successFn, errorFn);
        }
      } catch (e) {
        errorFn();
      }
    };
    ifr.addEventListener("load", listener);
    tout = setTimeout(listener, this.iframesTimeout);
  }
  /**
   * Callback when the iframe is ready
   * @callback DOMIterator~onIframeReadySuccessCallback
   * @param {HTMLDocument} contents - The contentDocument of the iframe
   */
  /**
   * Callback if the iframe can't be accessed
   * @callback DOMIterator~onIframeReadyErrorCallback
   */
  /**
   * Calls the callback if the specified iframe is ready for DOM access
   * @param  {HTMLElement} ifr - The iframe DOM element
   * @param  {DOMIterator~onIframeReadySuccessCallback} successFn - Success
   * callback
   * @param {DOMIterator~onIframeReadyErrorCallback} errorFn - Error callback
   * @see {@link http://stackoverflow.com/a/36155560/3894981} for
   * background information
   * @access protected
   */
  onIframeReady(ifr, successFn, errorFn) {
    try {
      if (ifr.contentWindow.document.readyState === "complete") {
        if (this.isIframeBlank(ifr)) {
          this.observeIframeLoad(ifr, successFn, errorFn);
        } else {
          this.getIframeContents(ifr, successFn, errorFn);
        }
      } else {
        this.observeIframeLoad(ifr, successFn, errorFn);
      }
    } catch (e) {
      errorFn();
    }
  }
  /**
   * Callback when all iframes are ready for DOM access
   * @callback DOMIterator~waitForIframesDoneCallback
   */
  /**
   * Iterates over all iframes and calls the done callback when all of them
   * are ready for DOM access (including nested ones)
   * @param {HTMLElement} ctx - The context DOM element
   * @param {DOMIterator~waitForIframesDoneCallback} done - Done callback
   */
  waitForIframes(ctx, done) {
    let eachCalled = 0;
    this.forEachIframe(ctx, () => true, (ifr) => {
      eachCalled++;
      this.waitForIframes(ifr.querySelector("html"), () => {
        if (!--eachCalled) {
          done();
        }
      });
    }, (handled) => {
      if (!handled) {
        done();
      }
    });
  }
  /**
   * Callback allowing to filter an iframe. Must return true when the element
   * should remain, otherwise false
   * @callback DOMIterator~forEachIframeFilterCallback
   * @param {HTMLElement} iframe - The iframe DOM element
   */
  /**
   * Callback for each iframe content
   * @callback DOMIterator~forEachIframeEachCallback
   * @param {HTMLElement} content - The iframe document
   */
  /**
   * Callback if all iframes inside the context were handled
   * @callback DOMIterator~forEachIframeEndCallback
   * @param {number} handled - The number of handled iframes (those who
   * wheren't filtered)
   */
  /**
   * Iterates over all iframes inside the specified context and calls the
   * callbacks when they're ready. Filters iframes based on the instance
   * exclusion selectors
   * @param {HTMLElement} ctx - The context DOM element
   * @param {DOMIterator~forEachIframeFilterCallback} filter - Filter callback
   * @param {DOMIterator~forEachIframeEachCallback} each - Each callback
   * @param {DOMIterator~forEachIframeEndCallback} [end] - End callback
   * @access protected
   */
  forEachIframe(ctx, filter, each, end = () => {
  }) {
    let ifr = ctx.querySelectorAll("iframe"), open = ifr.length, handled = 0;
    ifr = Array.prototype.slice.call(ifr);
    const checkEnd = () => {
      if (--open <= 0) {
        end(handled);
      }
    };
    if (!open) {
      checkEnd();
    }
    ifr.forEach((ifr2) => {
      if (DOMIterator.matches(ifr2, this.exclude)) {
        checkEnd();
      } else {
        this.onIframeReady(ifr2, (con) => {
          if (filter(ifr2)) {
            handled++;
            each(con);
          }
          checkEnd();
        }, checkEnd);
      }
    });
  }
  /**
   * Creates a NodeIterator on the specified context
   * @see {@link https://developer.mozilla.org/en/docs/Web/API/NodeIterator}
   * @param {HTMLElement} ctx - The context DOM element
   * @param {DOMIterator~whatToShow} whatToShow
   * @param {DOMIterator~filterCb} filter
   * @return {NodeIterator}
   * @access protected
   */
  createIterator(ctx, whatToShow, filter) {
    return document.createNodeIterator(ctx, whatToShow, filter, false);
  }
  /**
   * Creates an instance of DOMIterator in an iframe
   * @param {HTMLDocument} contents - Iframe document
   * @return {DOMIterator}
   * @access protected
   */
  createInstanceOnIframe(contents) {
    return new DOMIterator(contents.querySelector("html"), this.iframes);
  }
  /**
   * Checks if an iframe occurs between two nodes, more specifically if an
   * iframe occurs before the specified node and after the specified prevNode
   * @param {HTMLElement} node - The node that should occur after the iframe
   * @param {HTMLElement} prevNode - The node that should occur before the
   * iframe
   * @param {HTMLElement} ifr - The iframe to check against
   * @return {boolean}
   * @access protected
   */
  compareNodeIframe(node, prevNode, ifr) {
    const compCurr = node.compareDocumentPosition(ifr), prev = Node.DOCUMENT_POSITION_PRECEDING;
    if (compCurr & prev) {
      if (prevNode !== null) {
        const compPrev = prevNode.compareDocumentPosition(ifr), after = Node.DOCUMENT_POSITION_FOLLOWING;
        if (compPrev & after) {
          return true;
        }
      } else {
        return true;
      }
    }
    return false;
  }
  /**
   * @typedef {DOMIterator~getIteratorNodeReturn}
   * @type {object.<string>}
   * @property {HTMLElement} prevNode - The previous node or null if there is
   * no
   * @property {HTMLElement} node - The current node
   */
  /**
   * Returns the previous and current node of the specified iterator
   * @param {NodeIterator} itr - The iterator
   * @return {DOMIterator~getIteratorNodeReturn}
   * @access protected
   */
  getIteratorNode(itr) {
    const prevNode = itr.previousNode();
    let node;
    if (prevNode === null) {
      node = itr.nextNode();
    } else {
      node = itr.nextNode() && itr.nextNode();
    }
    return {
      prevNode,
      node
    };
  }
  /**
   * An array containing objects. The object key "val" contains an iframe
   * DOM element. The object key "handled" contains a boolean indicating if
   * the iframe was handled already.
   * It wouldn't be enough to save all open or all already handled iframes.
   * The information of open iframes is necessary because they may occur after
   * all other text nodes (and compareNodeIframe would never be true). The
   * information of already handled iframes is necessary as otherwise they may
   * be handled multiple times
   * @typedef DOMIterator~checkIframeFilterIfr
   * @type {object[]}
   */
  /**
   * Checks if an iframe wasn't handled already and if so, calls
   * {@link DOMIterator#compareNodeIframe} to check if it should be handled.
   * Information wheter an iframe was or wasn't handled is given within the
   * <code>ifr</code> dictionary
   * @param {HTMLElement} node - The node that should occur after the iframe
   * @param {HTMLElement} prevNode - The node that should occur before the
   * iframe
   * @param {HTMLElement} currIfr - The iframe to check
   * @param {DOMIterator~checkIframeFilterIfr} ifr - The iframe dictionary.
   * Will be manipulated (by reference)
   * @return {boolean} Returns true when it should be handled, otherwise false
   * @access protected
   */
  checkIframeFilter(node, prevNode, currIfr, ifr) {
    let key = false, handled = false;
    ifr.forEach((ifrDict, i) => {
      if (ifrDict.val === currIfr) {
        key = i;
        handled = ifrDict.handled;
      }
    });
    if (this.compareNodeIframe(node, prevNode, currIfr)) {
      if (key === false && !handled) {
        ifr.push({
          val: currIfr,
          handled: true
        });
      } else if (key !== false && !handled) {
        ifr[key].handled = true;
      }
      return true;
    }
    if (key === false) {
      ifr.push({
        val: currIfr,
        handled: false
      });
    }
    return false;
  }
  /**
   * Creates an iterator on all open iframes in the specified array and calls
   * the end callback when finished
   * @param {DOMIterator~checkIframeFilterIfr} ifr
   * @param {DOMIterator~whatToShow} whatToShow
   * @param  {DOMIterator~forEachNodeCallback} eCb - Each callback
   * @param {DOMIterator~filterCb} fCb
   * @access protected
   */
  handleOpenIframes(ifr, whatToShow, eCb, fCb) {
    ifr.forEach((ifrDict) => {
      if (!ifrDict.handled) {
        this.getIframeContents(ifrDict.val, (con) => {
          this.createInstanceOnIframe(con).forEachNode(
            whatToShow,
            eCb,
            fCb
          );
        });
      }
    });
  }
  /**
   * Iterates through all nodes in the specified context and handles iframe
   * nodes at the correct position
   * @param {DOMIterator~whatToShow} whatToShow
   * @param {HTMLElement} ctx - The context
   * @param  {DOMIterator~forEachNodeCallback} eachCb - Each callback
   * @param {DOMIterator~filterCb} filterCb - Filter callback
   * @param {DOMIterator~forEachNodeEndCallback} doneCb - End callback
   * @access protected
   */
  iterateThroughNodes(whatToShow, ctx, eachCb, filterCb, doneCb) {
    const itr = this.createIterator(ctx, whatToShow, filterCb);
    let ifr = [], elements = [], node, prevNode, retrieveNodes = () => {
      ({
        prevNode,
        node
      } = this.getIteratorNode(itr));
      return node;
    };
    while (retrieveNodes()) {
      if (this.iframes) {
        this.forEachIframe(ctx, (currIfr) => {
          return this.checkIframeFilter(node, prevNode, currIfr, ifr);
        }, (con) => {
          this.createInstanceOnIframe(con).forEachNode(
            whatToShow,
            (ifrNode) => elements.push(ifrNode),
            filterCb
          );
        });
      }
      elements.push(node);
    }
    elements.forEach((node2) => {
      eachCb(node2);
    });
    if (this.iframes) {
      this.handleOpenIframes(ifr, whatToShow, eachCb, filterCb);
    }
    doneCb();
  }
  /**
   * Callback for each node
   * @callback DOMIterator~forEachNodeCallback
   * @param {HTMLElement} node - The DOM text node element
   */
  /**
   * Callback if all contexts were handled
   * @callback DOMIterator~forEachNodeEndCallback
   */
  /**
   * Iterates over all contexts and initializes
   * {@link DOMIterator#iterateThroughNodes iterateThroughNodes} on them
   * @param {DOMIterator~whatToShow} whatToShow
   * @param  {DOMIterator~forEachNodeCallback} each - Each callback
   * @param {DOMIterator~filterCb} filter - Filter callback
   * @param {DOMIterator~forEachNodeEndCallback} done - End callback
   * @access public
   */
  forEachNode(whatToShow, each, filter, done = () => {
  }) {
    const contexts = this.getContexts();
    let open = contexts.length;
    if (!open) {
      done();
    }
    contexts.forEach((ctx) => {
      const ready = () => {
        this.iterateThroughNodes(whatToShow, ctx, each, filter, () => {
          if (--open <= 0) {
            done();
          }
        });
      };
      if (this.iframes) {
        this.waitForIframes(ctx, ready);
      } else {
        ready();
      }
    });
  }
  /**
   * Callback to filter nodes. Can return e.g. NodeFilter.FILTER_ACCEPT or
   * NodeFilter.FILTER_REJECT
   * @see {@link http://tinyurl.com/zdczmm2}
   * @callback DOMIterator~filterCb
   * @param {HTMLElement} node - The node to filter
   */
  /**
   * @typedef DOMIterator~whatToShow
   * @see {@link http://tinyurl.com/zfqqkx2}
   * @type {number}
   */
}
let Mark$1 = class Mark {
  // eslint-disable-line no-unused-vars
  /**
   * @param {HTMLElement|HTMLElement[]|NodeList|string} ctx - The context DOM
   * element, an array of DOM elements, a NodeList or a selector
   */
  constructor(ctx) {
    this.ctx = ctx;
    this.ie = false;
    const ua = window.navigator.userAgent;
    if (ua.indexOf("MSIE") > -1 || ua.indexOf("Trident") > -1) {
      this.ie = true;
    }
  }
  /**
   * Options defined by the user. They will be initialized from one of the
   * public methods. See {@link Mark#mark}, {@link Mark#markRegExp},
   * {@link Mark#markRanges} and {@link Mark#unmark} for option properties.
   * @type {object}
   * @param {object} [val] - An object that will be merged with defaults
   * @access protected
   */
  set opt(val) {
    this._opt = Object.assign({}, {
      "element": "",
      "className": "",
      "exclude": [],
      "iframes": false,
      "iframesTimeout": 5e3,
      "separateWordSearch": true,
      "diacritics": true,
      "synonyms": {},
      "accuracy": "partially",
      "acrossElements": false,
      "caseSensitive": false,
      "ignoreJoiners": false,
      "ignoreGroups": 0,
      "ignorePunctuation": [],
      "wildcards": "disabled",
      "each": () => {
      },
      "noMatch": () => {
      },
      "filter": () => true,
      "done": () => {
      },
      "debug": false,
      "log": window.console
    }, val);
  }
  get opt() {
    return this._opt;
  }
  /**
   * An instance of DOMIterator
   * @type {DOMIterator}
   * @access protected
   */
  get iterator() {
    return new DOMIterator(
      this.ctx,
      this.opt.iframes,
      this.opt.exclude,
      this.opt.iframesTimeout
    );
  }
  /**
   * Logs a message if log is enabled
   * @param {string} msg - The message to log
   * @param {string} [level="debug"] - The log level, e.g. <code>warn</code>
   * <code>error</code>, <code>debug</code>
   * @access protected
   */
  log(msg, level = "debug") {
    const log = this.opt.log;
    if (!this.opt.debug) {
      return;
    }
    if (typeof log === "object" && typeof log[level] === "function") {
      log[level](`mark.js: ${msg}`);
    }
  }
  /**
   * Escapes a string for usage within a regular expression
   * @param {string} str - The string to escape
   * @return {string}
   * @access protected
   */
  escapeStr(str) {
    return str.replace(/[\-\[\]\/\{\}\(\)\*\+\?\.\\\^\$\|]/g, "\\$&");
  }
  /**
   * Creates a regular expression string to match the specified search
   * term including synonyms, diacritics and accuracy if defined
   * @param  {string} str - The search term to be used
   * @return {string}
   * @access protected
   */
  createRegExp(str) {
    if (this.opt.wildcards !== "disabled") {
      str = this.setupWildcardsRegExp(str);
    }
    str = this.escapeStr(str);
    if (Object.keys(this.opt.synonyms).length) {
      str = this.createSynonymsRegExp(str);
    }
    if (this.opt.ignoreJoiners || this.opt.ignorePunctuation.length) {
      str = this.setupIgnoreJoinersRegExp(str);
    }
    if (this.opt.diacritics) {
      str = this.createDiacriticsRegExp(str);
    }
    str = this.createMergedBlanksRegExp(str);
    if (this.opt.ignoreJoiners || this.opt.ignorePunctuation.length) {
      str = this.createJoinersRegExp(str);
    }
    if (this.opt.wildcards !== "disabled") {
      str = this.createWildcardsRegExp(str);
    }
    str = this.createAccuracyRegExp(str);
    return str;
  }
  /**
   * Creates a regular expression string to match the defined synonyms
   * @param  {string} str - The search term to be used
   * @return {string}
   * @access protected
   */
  createSynonymsRegExp(str) {
    const syn = this.opt.synonyms, sens = this.opt.caseSensitive ? "" : "i", joinerPlaceholder = this.opt.ignoreJoiners || this.opt.ignorePunctuation.length ? "\0" : "";
    for (let index in syn) {
      if (syn.hasOwnProperty(index)) {
        const value = syn[index], k1 = this.opt.wildcards !== "disabled" ? this.setupWildcardsRegExp(index) : this.escapeStr(index), k2 = this.opt.wildcards !== "disabled" ? this.setupWildcardsRegExp(value) : this.escapeStr(value);
        if (k1 !== "" && k2 !== "") {
          str = str.replace(
            new RegExp(
              `(${this.escapeStr(k1)}|${this.escapeStr(k2)})`,
              `gm${sens}`
            ),
            joinerPlaceholder + `(${this.processSynomyms(k1)}|${this.processSynomyms(k2)})` + joinerPlaceholder
          );
        }
      }
    }
    return str;
  }
  /**
   * Setup synonyms to work with ignoreJoiners and or ignorePunctuation
   * @param {string} str - synonym key or value to process
   * @return {string} - processed synonym string
   */
  processSynomyms(str) {
    if (this.opt.ignoreJoiners || this.opt.ignorePunctuation.length) {
      str = this.setupIgnoreJoinersRegExp(str);
    }
    return str;
  }
  /**
   * Sets up the regular expression string to allow later insertion of
   * wildcard regular expression matches
   * @param  {string} str - The search term to be used
   * @return {string}
   * @access protected
   */
  setupWildcardsRegExp(str) {
    str = str.replace(/(?:\\)*\?/g, (val) => {
      return val.charAt(0) === "\\" ? "?" : "";
    });
    return str.replace(/(?:\\)*\*/g, (val) => {
      return val.charAt(0) === "\\" ? "*" : "";
    });
  }
  /**
   * Sets up the regular expression string to allow later insertion of
   * wildcard regular expression matches
   * @param  {string} str - The search term to be used
   * @return {string}
   * @access protected
   */
  createWildcardsRegExp(str) {
    let spaces = this.opt.wildcards === "withSpaces";
    return str.replace(/\u0001/g, spaces ? "[\\S\\s]?" : "\\S?").replace(/\u0002/g, spaces ? "[\\S\\s]*?" : "\\S*");
  }
  /**
   * Sets up the regular expression string to allow later insertion of
   * designated characters (soft hyphens & zero width characters)
   * @param  {string} str - The search term to be used
   * @return {string}
   * @access protected
   */
  setupIgnoreJoinersRegExp(str) {
    return str.replace(/[^(|)\\]/g, (val, indx, original) => {
      let nextChar = original.charAt(indx + 1);
      if (/[(|)\\]/.test(nextChar) || nextChar === "") {
        return val;
      } else {
        return val + "\0";
      }
    });
  }
  /**
   * Creates a regular expression string to allow ignoring of designated
   * characters (soft hyphens, zero width characters & punctuation) based on
   * the specified option values of <code>ignorePunctuation</code> and
   * <code>ignoreJoiners</code>
   * @param  {string} str - The search term to be used
   * @return {string}
   * @access protected
   */
  createJoinersRegExp(str) {
    let joiner = [];
    const ignorePunctuation = this.opt.ignorePunctuation;
    if (Array.isArray(ignorePunctuation) && ignorePunctuation.length) {
      joiner.push(this.escapeStr(ignorePunctuation.join("")));
    }
    if (this.opt.ignoreJoiners) {
      joiner.push("\\u00ad\\u200b\\u200c\\u200d");
    }
    return joiner.length ? str.split(/\u0000+/).join(`[${joiner.join("")}]*`) : str;
  }
  /**
   * Creates a regular expression string to match diacritics
   * @param  {string} str - The search term to be used
   * @return {string}
   * @access protected
   */
  createDiacriticsRegExp(str) {
    const sens = this.opt.caseSensitive ? "" : "i", dct = this.opt.caseSensitive ? [
      "aàáảãạăằắẳẵặâầấẩẫậäåāą",
      "AÀÁẢÃẠĂẰẮẲẴẶÂẦẤẨẪẬÄÅĀĄ",
      "cçćč",
      "CÇĆČ",
      "dđď",
      "DĐĎ",
      "eèéẻẽẹêềếểễệëěēę",
      "EÈÉẺẼẸÊỀẾỂỄỆËĚĒĘ",
      "iìíỉĩịîïī",
      "IÌÍỈĨỊÎÏĪ",
      "lł",
      "LŁ",
      "nñňń",
      "NÑŇŃ",
      "oòóỏõọôồốổỗộơởỡớờợöøō",
      "OÒÓỎÕỌÔỒỐỔỖỘƠỞỠỚỜỢÖØŌ",
      "rř",
      "RŘ",
      "sšśșş",
      "SŠŚȘŞ",
      "tťțţ",
      "TŤȚŢ",
      "uùúủũụưừứửữựûüůū",
      "UÙÚỦŨỤƯỪỨỬỮỰÛÜŮŪ",
      "yýỳỷỹỵÿ",
      "YÝỲỶỸỴŸ",
      "zžżź",
      "ZŽŻŹ"
    ] : [
      "aàáảãạăằắẳẵặâầấẩẫậäåāąAÀÁẢÃẠĂẰẮẲẴẶÂẦẤẨẪẬÄÅĀĄ",
      "cçćčCÇĆČ",
      "dđďDĐĎ",
      "eèéẻẽẹêềếểễệëěēęEÈÉẺẼẸÊỀẾỂỄỆËĚĒĘ",
      "iìíỉĩịîïīIÌÍỈĨỊÎÏĪ",
      "lłLŁ",
      "nñňńNÑŇŃ",
      "oòóỏõọôồốổỗộơởỡớờợöøōOÒÓỎÕỌÔỒỐỔỖỘƠỞỠỚỜỢÖØŌ",
      "rřRŘ",
      "sšśșşSŠŚȘŞ",
      "tťțţTŤȚŢ",
      "uùúủũụưừứửữựûüůūUÙÚỦŨỤƯỪỨỬỮỰÛÜŮŪ",
      "yýỳỷỹỵÿYÝỲỶỸỴŸ",
      "zžżźZŽŻŹ"
    ];
    let handled = [];
    str.split("").forEach((ch) => {
      dct.every((dct2) => {
        if (dct2.indexOf(ch) !== -1) {
          if (handled.indexOf(dct2) > -1) {
            return false;
          }
          str = str.replace(
            new RegExp(`[${dct2}]`, `gm${sens}`),
            `[${dct2}]`
          );
          handled.push(dct2);
        }
        return true;
      });
    });
    return str;
  }
  /**
   * Creates a regular expression string that merges whitespace characters
   * including subsequent ones into a single pattern, one or multiple
   * whitespaces
   * @param  {string} str - The search term to be used
   * @return {string}
   * @access protected
   */
  createMergedBlanksRegExp(str) {
    return str.replace(/[\s]+/gmi, "[\\s]+");
  }
  /**
   * Creates a regular expression string to match the specified string with
   * the defined accuracy. As in the regular expression of "exactly" can be
   * a group containing a blank at the beginning, all regular expressions will
   * be created with two groups. The first group can be ignored (may contain
   * the said blank), the second contains the actual match
   * @param  {string} str - The searm term to be used
   * @return {str}
   * @access protected
   */
  createAccuracyRegExp(str) {
    const chars = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~¡¿";
    let acc = this.opt.accuracy, val = typeof acc === "string" ? acc : acc.value, ls = typeof acc === "string" ? [] : acc.limiters, lsJoin = "";
    ls.forEach((limiter) => {
      lsJoin += `|${this.escapeStr(limiter)}`;
    });
    switch (val) {
      case "partially":
      default:
        return `()(${str})`;
      case "complementary":
        lsJoin = "\\s" + (lsJoin ? lsJoin : this.escapeStr(chars));
        return `()([^${lsJoin}]*${str}[^${lsJoin}]*)`;
      case "exactly":
        return `(^|\\s${lsJoin})(${str})(?=$|\\s${lsJoin})`;
    }
  }
  /**
   * @typedef Mark~separatedKeywords
   * @type {object.<string>}
   * @property {array.<string>} keywords - The list of keywords
   * @property {number} length - The length
   */
  /**
   * Returns a list of keywords dependent on whether separate word search
   * was defined. Also it filters empty keywords
   * @param {array} sv - The array of keywords
   * @return {Mark~separatedKeywords}
   * @access protected
   */
  getSeparatedKeywords(sv) {
    let stack = [];
    sv.forEach((kw) => {
      if (!this.opt.separateWordSearch) {
        if (kw.trim() && stack.indexOf(kw) === -1) {
          stack.push(kw);
        }
      } else {
        kw.split(" ").forEach((kwSplitted) => {
          if (kwSplitted.trim() && stack.indexOf(kwSplitted) === -1) {
            stack.push(kwSplitted);
          }
        });
      }
    });
    return {
      // sort because of https://git.io/v6USg
      "keywords": stack.sort((a, b) => {
        return b.length - a.length;
      }),
      "length": stack.length
    };
  }
  /**
   * Check if a value is a number
   * @param {number|string} value - the value to check;
   * numeric strings allowed
   * @return {boolean}
   * @access protected
   */
  isNumeric(value) {
    return Number(parseFloat(value)) == value;
  }
  /**
   * @typedef Mark~rangeObject
   * @type {object}
   * @property {number} start - The start position within the composite value
   * @property {number} length - The length of the string to mark within the
   * composite value.
   */
  /**
   * @typedef Mark~setOfRanges
   * @type {object[]}
   * @property {Mark~rangeObject}
   */
  /**
   * Returns a processed list of integer offset indexes that do not overlap
   * each other, and remove any string values or additional elements
   * @param {Mark~setOfRanges} array - unprocessed raw array
   * @return {Mark~setOfRanges} - processed array with any invalid entries
   * removed
   * @throws Will throw an error if an array of objects is not passed
   * @access protected
   */
  checkRanges(array) {
    if (!Array.isArray(array) || Object.prototype.toString.call(array[0]) !== "[object Object]") {
      this.log("markRanges() will only accept an array of objects");
      this.opt.noMatch(array);
      return [];
    }
    const stack = [];
    let last2 = 0;
    array.sort((a, b) => {
      return a.start - b.start;
    }).forEach((item) => {
      let { start, end, valid } = this.callNoMatchOnInvalidRanges(item, last2);
      if (valid) {
        item.start = start;
        item.length = end - start;
        stack.push(item);
        last2 = end;
      }
    });
    return stack;
  }
  /**
   * @typedef Mark~validObject
   * @type {object}
   * @property {number} start - The start position within the composite value
   * @property {number} end - The calculated end position within the composite
   * value.
   * @property {boolean} valid - boolean value indicating that the start and
   * calculated end range is valid
   */
  /**
    * Initial validation of ranges for markRanges. Preliminary checks are done
    * to ensure the start and length values exist and are not zero or non-
    * numeric
    * @param {Mark~rangeObject} range - the current range object
    * @param {number} last - last index of range
    * @return {Mark~validObject}
    * @access protected
    */
  callNoMatchOnInvalidRanges(range, last2) {
    let start, end, valid = false;
    if (range && typeof range.start !== "undefined") {
      start = parseInt(range.start, 10);
      end = start + parseInt(range.length, 10);
      if (this.isNumeric(range.start) && this.isNumeric(range.length) && end - last2 > 0 && end - start > 0) {
        valid = true;
      } else {
        this.log(
          `Ignoring invalid or overlapping range: ${JSON.stringify(range)}`
        );
        this.opt.noMatch(range);
      }
    } else {
      this.log(`Ignoring invalid range: ${JSON.stringify(range)}`);
      this.opt.noMatch(range);
    }
    return {
      start,
      end,
      valid
    };
  }
  /**
   * Check valid range for markRanges. Check ranges with access to the context
   * string. Range values are double checked, lengths that extend the mark
   * beyond the string length are limitied and ranges containing only
   * whitespace are ignored
   * @param {Mark~rangeObject} range - the current range object
   * @param {number} originalLength - original length of the context string
   * @param {string} string - current content string
   * @return {Mark~validObject}
   * @access protected
   */
  checkWhitespaceRanges(range, originalLength, string) {
    let end, valid = true, max = string.length, offset = originalLength - max, start = parseInt(range.start, 10) - offset;
    start = start > max ? max : start;
    end = start + parseInt(range.length, 10);
    if (end > max) {
      end = max;
      this.log(`End range automatically set to the max value of ${max}`);
    }
    if (start < 0 || end - start < 0 || start > max || end > max) {
      valid = false;
      this.log(`Invalid range: ${JSON.stringify(range)}`);
      this.opt.noMatch(range);
    } else if (string.substring(start, end).replace(/\s+/g, "") === "") {
      valid = false;
      this.log("Skipping whitespace only range: " + JSON.stringify(range));
      this.opt.noMatch(range);
    }
    return {
      start,
      end,
      valid
    };
  }
  /**
   * @typedef Mark~getTextNodesDict
   * @type {object.<string>}
   * @property {string} value - The composite value of all text nodes
   * @property {object[]} nodes - An array of objects
   * @property {number} nodes.start - The start position within the composite
   * value
   * @property {number} nodes.end - The end position within the composite
   * value
   * @property {HTMLElement} nodes.node - The DOM text node element
   */
  /**
   * Callback
   * @callback Mark~getTextNodesCallback
   * @param {Mark~getTextNodesDict}
   */
  /**
   * Calls the callback with an object containing all text nodes (including
   * iframe text nodes) with start and end positions and the composite value
   * of them (string)
   * @param {Mark~getTextNodesCallback} cb - Callback
   * @access protected
   */
  getTextNodes(cb) {
    let val = "", nodes = [];
    this.iterator.forEachNode(NodeFilter.SHOW_TEXT, (node) => {
      nodes.push({
        start: val.length,
        end: (val += node.textContent).length,
        node
      });
    }, (node) => {
      if (this.matchesExclude(node.parentNode)) {
        return NodeFilter.FILTER_REJECT;
      } else {
        return NodeFilter.FILTER_ACCEPT;
      }
    }, () => {
      cb({
        value: val,
        nodes
      });
    });
  }
  /**
   * Checks if an element matches any of the specified exclude selectors. Also
   * it checks for elements in which no marks should be performed (e.g.
   * script and style tags) and optionally already marked elements
   * @param  {HTMLElement} el - The element to check
   * @return {boolean}
   * @access protected
   */
  matchesExclude(el) {
    return DOMIterator.matches(el, this.opt.exclude.concat([
      // ignores the elements itself, not their childrens (selector *)
      "script",
      "style",
      "title",
      "head",
      "html"
    ]));
  }
  /**
   * Wraps the instance element and class around matches that fit the start
   * and end positions within the node
   * @param  {HTMLElement} node - The DOM text node
   * @param  {number} start - The position where to start wrapping
   * @param  {number} end - The position where to end wrapping
   * @return {HTMLElement} Returns the splitted text node that will appear
   * after the wrapped text node
   * @access protected
   */
  wrapRangeInTextNode(node, start, end) {
    const hEl = !this.opt.element ? "mark" : this.opt.element, startNode = node.splitText(start), ret = startNode.splitText(end - start);
    let repl = document.createElement(hEl);
    repl.setAttribute("data-markjs", "true");
    if (this.opt.className) {
      repl.setAttribute("class", this.opt.className);
    }
    repl.textContent = startNode.textContent;
    startNode.parentNode.replaceChild(repl, startNode);
    return ret;
  }
  /**
   * @typedef Mark~wrapRangeInMappedTextNodeDict
   * @type {object.<string>}
   * @property {string} value - The composite value of all text nodes
   * @property {object[]} nodes - An array of objects
   * @property {number} nodes.start - The start position within the composite
   * value
   * @property {number} nodes.end - The end position within the composite
   * value
   * @property {HTMLElement} nodes.node - The DOM text node element
   */
  /**
   * Each callback
   * @callback Mark~wrapMatchesEachCallback
   * @param {HTMLElement} node - The wrapped DOM element
   * @param {number} lastIndex - The last matching position within the
   * composite value of text nodes
   */
  /**
   * Filter callback
   * @callback Mark~wrapMatchesFilterCallback
   * @param {HTMLElement} node - The matching text node DOM element
   */
  /**
   * Determines matches by start and end positions using the text node
   * dictionary even across text nodes and calls
   * {@link Mark#wrapRangeInTextNode} to wrap them
   * @param  {Mark~wrapRangeInMappedTextNodeDict} dict - The dictionary
   * @param  {number} start - The start position of the match
   * @param  {number} end - The end position of the match
   * @param  {Mark~wrapMatchesFilterCallback} filterCb - Filter callback
   * @param  {Mark~wrapMatchesEachCallback} eachCb - Each callback
   * @access protected
   */
  wrapRangeInMappedTextNode(dict, start, end, filterCb, eachCb) {
    dict.nodes.every((n, i) => {
      const sibl = dict.nodes[i + 1];
      if (typeof sibl === "undefined" || sibl.start > start) {
        if (!filterCb(n.node)) {
          return false;
        }
        const s = start - n.start, e = (end > n.end ? n.end : end) - n.start, startStr = dict.value.substr(0, n.start), endStr = dict.value.substr(e + n.start);
        n.node = this.wrapRangeInTextNode(n.node, s, e);
        dict.value = startStr + endStr;
        dict.nodes.forEach((k, j) => {
          if (j >= i) {
            if (dict.nodes[j].start > 0 && j !== i) {
              dict.nodes[j].start -= e;
            }
            dict.nodes[j].end -= e;
          }
        });
        end -= e;
        eachCb(n.node.previousSibling, n.start);
        if (end > n.end) {
          start = n.end;
        } else {
          return false;
        }
      }
      return true;
    });
  }
  /**
   * Filter callback before each wrapping
   * @callback Mark~wrapMatchesFilterCallback
   * @param {string} match - The matching string
   * @param {HTMLElement} node - The text node where the match occurs
   */
  /**
   * Callback for each wrapped element
   * @callback Mark~wrapMatchesEachCallback
   * @param {HTMLElement} element - The marked DOM element
   */
  /**
   * Callback on end
   * @callback Mark~wrapMatchesEndCallback
   */
  /**
   * Wraps the instance element and class around matches within single HTML
   * elements in all contexts
   * @param {RegExp} regex - The regular expression to be searched for
   * @param {number} ignoreGroups - A number indicating the amount of RegExp
   * matching groups to ignore
   * @param {Mark~wrapMatchesFilterCallback} filterCb
   * @param {Mark~wrapMatchesEachCallback} eachCb
   * @param {Mark~wrapMatchesEndCallback} endCb
   * @access protected
   */
  wrapMatches(regex, ignoreGroups, filterCb, eachCb, endCb) {
    const matchIdx = ignoreGroups === 0 ? 0 : ignoreGroups + 1;
    this.getTextNodes((dict) => {
      dict.nodes.forEach((node) => {
        node = node.node;
        let match;
        while ((match = regex.exec(node.textContent)) !== null && match[matchIdx] !== "") {
          if (!filterCb(match[matchIdx], node)) {
            continue;
          }
          let pos = match.index;
          if (matchIdx !== 0) {
            for (let i = 1; i < matchIdx; i++) {
              pos += match[i].length;
            }
          }
          node = this.wrapRangeInTextNode(
            node,
            pos,
            pos + match[matchIdx].length
          );
          eachCb(node.previousSibling);
          regex.lastIndex = 0;
        }
      });
      endCb();
    });
  }
  /**
   * Callback for each wrapped element
   * @callback Mark~wrapMatchesAcrossElementsEachCallback
   * @param {HTMLElement} element - The marked DOM element
   */
  /**
   * Filter callback before each wrapping
   * @callback Mark~wrapMatchesAcrossElementsFilterCallback
   * @param {string} match - The matching string
   * @param {HTMLElement} node - The text node where the match occurs
   */
  /**
   * Callback on end
   * @callback Mark~wrapMatchesAcrossElementsEndCallback
   */
  /**
   * Wraps the instance element and class around matches across all HTML
   * elements in all contexts
   * @param {RegExp} regex - The regular expression to be searched for
   * @param {number} ignoreGroups - A number indicating the amount of RegExp
   * matching groups to ignore
   * @param {Mark~wrapMatchesAcrossElementsFilterCallback} filterCb
   * @param {Mark~wrapMatchesAcrossElementsEachCallback} eachCb
   * @param {Mark~wrapMatchesAcrossElementsEndCallback} endCb
   * @access protected
   */
  wrapMatchesAcrossElements(regex, ignoreGroups, filterCb, eachCb, endCb) {
    const matchIdx = ignoreGroups === 0 ? 0 : ignoreGroups + 1;
    this.getTextNodes((dict) => {
      let match;
      while ((match = regex.exec(dict.value)) !== null && match[matchIdx] !== "") {
        let start = match.index;
        if (matchIdx !== 0) {
          for (let i = 1; i < matchIdx; i++) {
            start += match[i].length;
          }
        }
        const end = start + match[matchIdx].length;
        this.wrapRangeInMappedTextNode(dict, start, end, (node) => {
          return filterCb(match[matchIdx], node);
        }, (node, lastIndex) => {
          regex.lastIndex = lastIndex;
          eachCb(node);
        });
      }
      endCb();
    });
  }
  /**
   * Callback for each wrapped element
   * @callback Mark~wrapRangeFromIndexEachCallback
   * @param {HTMLElement} element - The marked DOM element
   * @param {Mark~rangeObject} range - the current range object; provided
   * start and length values will be numeric integers modified from the
   * provided original ranges.
   */
  /**
   * Filter callback before each wrapping
   * @callback Mark~wrapRangeFromIndexFilterCallback
   * @param {HTMLElement} node - The text node which includes the range
   * @param {Mark~rangeObject} range - the current range object
   * @param {string} match - string extracted from the matching range
   * @param {number} counter - A counter indicating the number of all marks
   */
  /**
   * Callback on end
   * @callback Mark~wrapRangeFromIndexEndCallback
   */
  /**
   * Wraps the indicated ranges across all HTML elements in all contexts
   * @param {Mark~setOfRanges} ranges
   * @param {Mark~wrapRangeFromIndexFilterCallback} filterCb
   * @param {Mark~wrapRangeFromIndexEachCallback} eachCb
   * @param {Mark~wrapRangeFromIndexEndCallback} endCb
   * @access protected
   */
  wrapRangeFromIndex(ranges, filterCb, eachCb, endCb) {
    this.getTextNodes((dict) => {
      const originalLength = dict.value.length;
      ranges.forEach((range, counter) => {
        let { start, end, valid } = this.checkWhitespaceRanges(
          range,
          originalLength,
          dict.value
        );
        if (valid) {
          this.wrapRangeInMappedTextNode(dict, start, end, (node) => {
            return filterCb(
              node,
              range,
              dict.value.substring(start, end),
              counter
            );
          }, (node) => {
            eachCb(node, range);
          });
        }
      });
      endCb();
    });
  }
  /**
   * Unwraps the specified DOM node with its content (text nodes or HTML)
   * without destroying possibly present events (using innerHTML) and
   * normalizes the parent at the end (merge splitted text nodes)
   * @param  {HTMLElement} node - The DOM node to unwrap
   * @access protected
   */
  unwrapMatches(node) {
    const parent = node.parentNode;
    let docFrag = document.createDocumentFragment();
    while (node.firstChild) {
      docFrag.appendChild(node.removeChild(node.firstChild));
    }
    parent.replaceChild(docFrag, node);
    if (!this.ie) {
      parent.normalize();
    } else {
      this.normalizeTextNode(parent);
    }
  }
  /**
   * Normalizes text nodes. It's a workaround for the native normalize method
   * that has a bug in IE (see attached link). Should only be used in IE
   * browsers as it's slower than the native method.
   * @see {@link http://tinyurl.com/z5asa8c}
   * @param {HTMLElement} node - The DOM node to normalize
   * @access protected
   */
  normalizeTextNode(node) {
    if (!node) {
      return;
    }
    if (node.nodeType === 3) {
      while (node.nextSibling && node.nextSibling.nodeType === 3) {
        node.nodeValue += node.nextSibling.nodeValue;
        node.parentNode.removeChild(node.nextSibling);
      }
    } else {
      this.normalizeTextNode(node.firstChild);
    }
    this.normalizeTextNode(node.nextSibling);
  }
  /**
   * Callback when finished
   * @callback Mark~commonDoneCallback
   * @param {number} totalMatches - The number of marked elements
   */
  /**
   * @typedef Mark~commonOptions
   * @type {object.<string>}
   * @property {string} [element="mark"] - HTML element tag name
   * @property {string} [className] - An optional class name
   * @property {string[]} [exclude] - An array with exclusion selectors.
   * Elements matching those selectors will be ignored
   * @property {boolean} [iframes=false] - Whether to search inside iframes
   * @property {Mark~commonDoneCallback} [done]
   * @property {boolean} [debug=false] - Wheter to log messages
   * @property {object} [log=window.console] - Where to log messages (only if
   * debug is true)
   */
  /**
   * Callback for each marked element
   * @callback Mark~markRegExpEachCallback
   * @param {HTMLElement} element - The marked DOM element
   */
  /**
   * Callback if there were no matches
   * @callback Mark~markRegExpNoMatchCallback
   * @param {RegExp} regexp - The regular expression
   */
  /**
   * Callback to filter matches
   * @callback Mark~markRegExpFilterCallback
   * @param {HTMLElement} textNode - The text node which includes the match
   * @param {string} match - The matching string for the RegExp
   * @param {number} counter - A counter indicating the number of all marks
   */
  /**
   * These options also include the common options from
   * {@link Mark~commonOptions}
   * @typedef Mark~markRegExpOptions
   * @type {object.<string>}
   * @property {Mark~markRegExpEachCallback} [each]
   * @property {Mark~markRegExpNoMatchCallback} [noMatch]
   * @property {Mark~markRegExpFilterCallback} [filter]
   */
  /**
   * Marks a custom regular expression
   * @param  {RegExp} regexp - The regular expression
   * @param  {Mark~markRegExpOptions} [opt] - Optional options object
   * @access public
   */
  markRegExp(regexp, opt) {
    this.opt = opt;
    this.log(`Searching with expression "${regexp}"`);
    let totalMatches = 0, fn = "wrapMatches";
    const eachCb = (element) => {
      totalMatches++;
      this.opt.each(element);
    };
    if (this.opt.acrossElements) {
      fn = "wrapMatchesAcrossElements";
    }
    this[fn](regexp, this.opt.ignoreGroups, (match, node) => {
      return this.opt.filter(node, match, totalMatches);
    }, eachCb, () => {
      if (totalMatches === 0) {
        this.opt.noMatch(regexp);
      }
      this.opt.done(totalMatches);
    });
  }
  /**
   * Callback for each marked element
   * @callback Mark~markEachCallback
   * @param {HTMLElement} element - The marked DOM element
   */
  /**
   * Callback if there were no matches
   * @callback Mark~markNoMatchCallback
   * @param {RegExp} term - The search term that was not found
   */
  /**
   * Callback to filter matches
   * @callback Mark~markFilterCallback
   * @param {HTMLElement} textNode - The text node which includes the match
   * @param {string} match - The matching term
   * @param {number} totalCounter - A counter indicating the number of all
   * marks
   * @param {number} termCounter - A counter indicating the number of marks
   * for the specific match
   */
  /**
   * @typedef Mark~markAccuracyObject
   * @type {object.<string>}
   * @property {string} value - A accuracy string value
   * @property {string[]} limiters - A custom array of limiters. For example
   * <code>["-", ","]</code>
   */
  /**
   * @typedef Mark~markAccuracySetting
   * @type {string}
   * @property {"partially"|"complementary"|"exactly"|Mark~markAccuracyObject}
   * [accuracy="partially"] - Either one of the following string values:
   * <ul>
   *   <li><i>partially</i>: When searching for "lor" only "lor" inside
   *   "lorem" will be marked</li>
   *   <li><i>complementary</i>: When searching for "lor" the whole word
   *   "lorem" will be marked</li>
   *   <li><i>exactly</i>: When searching for "lor" only those exact words
   *   will be marked. In this example nothing inside "lorem". This value
   *   is equivalent to the previous option <i>wordBoundary</i></li>
   * </ul>
   * Or an object containing two properties:
   * <ul>
   *   <li><i>value</i>: One of the above named string values</li>
   *   <li><i>limiters</i>: A custom array of string limiters for accuracy
   *   "exactly" or "complementary"</li>
   * </ul>
   */
  /**
   * @typedef Mark~markWildcardsSetting
   * @type {string}
   * @property {"disabled"|"enabled"|"withSpaces"}
   * [wildcards="disabled"] - Set to any of the following string values:
   * <ul>
   *   <li><i>disabled</i>: Disable wildcard usage</li>
   *   <li><i>enabled</i>: When searching for "lor?m", the "?" will match zero
   *   or one non-space character (e.g. "lorm", "loram", "lor3m", etc). When
   *   searching for "lor*m", the "*" will match zero or more non-space
   *   characters (e.g. "lorm", "loram", "lor123m", etc).</li>
   *   <li><i>withSpaces</i>: When searching for "lor?m", the "?" will
   *   match zero or one space or non-space character (e.g. "lor m", "loram",
   *   etc). When searching for "lor*m", the "*" will match zero or more space
   *   or non-space characters (e.g. "lorm", "lore et dolor ipsum", "lor: m",
   *   etc).</li>
   * </ul>
   */
  /**
   * @typedef Mark~markIgnorePunctuationSetting
   * @type {string[]}
   * @property {string} The strings in this setting will contain punctuation
   * marks that will be ignored:
   * <ul>
   *   <li>These punctuation marks can be between any characters, e.g. setting
   *   this option to <code>["'"]</code> would match "Worlds", "World's" and
   *   "Wo'rlds"</li>
   *   <li>One or more apostrophes between the letters would still produce a
   *   match (e.g. "W'o''r'l'd's").</li>
   *   <li>A typical setting for this option could be as follows:
   *   <pre>ignorePunctuation: ":;.,-–—‒_(){}[]!'\"+=".split(""),</pre> This
   *   setting includes common punctuation as well as a minus, en-dash,
   *   em-dash and figure-dash
   *   ({@link https://en.wikipedia.org/wiki/Dash#Figure_dash ref}), as well
   *   as an underscore.</li>
   * </ul>
   */
  /**
   * These options also include the common options from
   * {@link Mark~commonOptions}
   * @typedef Mark~markOptions
   * @type {object.<string>}
   * @property {boolean} [separateWordSearch=true] - Whether to search for
   * each word separated by a blank instead of the complete term
   * @property {boolean} [diacritics=true] - If diacritic characters should be
   * matched. ({@link https://en.wikipedia.org/wiki/Diacritic Diacritics})
   * @property {object} [synonyms] - An object with synonyms. The key will be
   * a synonym for the value and the value for the key
   * @property {Mark~markAccuracySetting} [accuracy]
   * @property {Mark~markWildcardsSetting} [wildcards]
   * @property {boolean} [acrossElements=false] - Whether to find matches
   * across HTML elements. By default, only matches within single HTML
   * elements will be found
   * @property {boolean} [ignoreJoiners=false] - Whether to ignore word
   * joiners inside of key words. These include soft-hyphens, zero-width
   * space, zero-width non-joiners and zero-width joiners.
   * @property {Mark~markIgnorePunctuationSetting} [ignorePunctuation]
   * @property {Mark~markEachCallback} [each]
   * @property {Mark~markNoMatchCallback} [noMatch]
   * @property {Mark~markFilterCallback} [filter]
   */
  /**
   * Marks the specified search terms
   * @param {string|string[]} [sv] - Search value, either a search string or
   * an array containing multiple search strings
   * @param  {Mark~markOptions} [opt] - Optional options object
   * @access public
   */
  mark(sv, opt) {
    this.opt = opt;
    let totalMatches = 0, fn = "wrapMatches";
    const {
      keywords: kwArr,
      length: kwArrLen
    } = this.getSeparatedKeywords(typeof sv === "string" ? [sv] : sv), sens = this.opt.caseSensitive ? "" : "i", handler = (kw) => {
      let regex = new RegExp(this.createRegExp(kw), `gm${sens}`), matches2 = 0;
      this.log(`Searching with expression "${regex}"`);
      this[fn](regex, 1, (term, node) => {
        return this.opt.filter(node, kw, totalMatches, matches2);
      }, (element) => {
        matches2++;
        totalMatches++;
        this.opt.each(element);
      }, () => {
        if (matches2 === 0) {
          this.opt.noMatch(kw);
        }
        if (kwArr[kwArrLen - 1] === kw) {
          this.opt.done(totalMatches);
        } else {
          handler(kwArr[kwArr.indexOf(kw) + 1]);
        }
      });
    };
    if (this.opt.acrossElements) {
      fn = "wrapMatchesAcrossElements";
    }
    if (kwArrLen === 0) {
      this.opt.done(totalMatches);
    } else {
      handler(kwArr[0]);
    }
  }
  /**
   * Callback for each marked element
   * @callback Mark~markRangesEachCallback
   * @param {HTMLElement} element - The marked DOM element
   * @param {array} range - array of range start and end points
   */
  /**
   * Callback if a processed range is invalid, out-of-bounds, overlaps another
   * range, or only matches whitespace
   * @callback Mark~markRangesNoMatchCallback
   * @param {Mark~rangeObject} range - a range object
   */
  /**
   * Callback to filter matches
   * @callback Mark~markRangesFilterCallback
   * @param {HTMLElement} node - The text node which includes the range
   * @param {array} range - array of range start and end points
   * @param {string} match - string extracted from the matching range
   * @param {number} counter - A counter indicating the number of all marks
   */
  /**
   * These options also include the common options from
   * {@link Mark~commonOptions}
   * @typedef Mark~markRangesOptions
   * @type {object.<string>}
   * @property {Mark~markRangesEachCallback} [each]
   * @property {Mark~markRangesNoMatchCallback} [noMatch]
   * @property {Mark~markRangesFilterCallback} [filter]
   */
  /**
   * Marks an array of objects containing a start with an end or length of the
   * string to mark
   * @param  {Mark~setOfRanges} rawRanges - The original (preprocessed)
   * array of objects
   * @param  {Mark~markRangesOptions} [opt] - Optional options object
   * @access public
   */
  markRanges(rawRanges, opt) {
    this.opt = opt;
    let totalMatches = 0, ranges = this.checkRanges(rawRanges);
    if (ranges && ranges.length) {
      this.log(
        "Starting to mark with the following ranges: " + JSON.stringify(ranges)
      );
      this.wrapRangeFromIndex(
        ranges,
        (node, range, match, counter) => {
          return this.opt.filter(node, range, match, counter);
        },
        (element, range) => {
          totalMatches++;
          this.opt.each(element, range);
        },
        () => {
          this.opt.done(totalMatches);
        }
      );
    } else {
      this.opt.done(totalMatches);
    }
  }
  /**
   * Removes all marked elements inside the context with their HTML and
   * normalizes the parent at the end
   * @param  {Mark~commonOptions} [opt] - Optional options object
   * @access public
   */
  unmark(opt) {
    this.opt = opt;
    let sel = this.opt.element ? this.opt.element : "*";
    sel += "[data-markjs]";
    if (this.opt.className) {
      sel += `.${this.opt.className}`;
    }
    this.log(`Removal selector "${sel}"`);
    this.iterator.forEachNode(NodeFilter.SHOW_ELEMENT, (node) => {
      this.unwrapMatches(node);
    }, (node) => {
      const matchesSel = DOMIterator.matches(node, sel), matchesExclude = this.matchesExclude(node);
      if (!matchesSel || matchesExclude) {
        return NodeFilter.FILTER_REJECT;
      } else {
        return NodeFilter.FILTER_ACCEPT;
      }
    }, this.opt.done);
  }
};
function Mark2(ctx) {
  const instance = new Mark$1(ctx);
  this.mark = (sv, opt) => {
    instance.mark(sv, opt);
    return this;
  };
  this.markRegExp = (sv, opt) => {
    instance.markRegExp(sv, opt);
    return this;
  };
  this.markRanges = (sv, opt) => {
    instance.markRanges(sv, opt);
    return this;
  };
  this.unmark = (opt) => {
    instance.unmark(opt);
    return this;
  };
  return this;
}
var __assign = function() {
  __assign = Object.assign || function __assign2(t) {
    for (var s, i = 1, n = arguments.length; i < n; i++) {
      s = arguments[i];
      for (var p in s) if (Object.prototype.hasOwnProperty.call(s, p)) t[p] = s[p];
    }
    return t;
  };
  return __assign.apply(this, arguments);
};
function __awaiter(thisArg, _arguments, P, generator) {
  function adopt(value) {
    return value instanceof P ? value : new P(function(resolve) {
      resolve(value);
    });
  }
  return new (P || (P = Promise))(function(resolve, reject) {
    function fulfilled(value) {
      try {
        step(generator.next(value));
      } catch (e) {
        reject(e);
      }
    }
    function rejected(value) {
      try {
        step(generator["throw"](value));
      } catch (e) {
        reject(e);
      }
    }
    function step(result) {
      result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected);
    }
    step((generator = generator.apply(thisArg, [])).next());
  });
}
function __generator(thisArg, body) {
  var _ = { label: 0, sent: function() {
    if (t[0] & 1) throw t[1];
    return t[1];
  }, trys: [], ops: [] }, f, y, t, g;
  return g = { next: verb(0), "throw": verb(1), "return": verb(2) }, typeof Symbol === "function" && (g[Symbol.iterator] = function() {
    return this;
  }), g;
  function verb(n) {
    return function(v) {
      return step([n, v]);
    };
  }
  function step(op) {
    if (f) throw new TypeError("Generator is already executing.");
    while (g && (g = 0, op[0] && (_ = 0)), _) try {
      if (f = 1, y && (t = op[0] & 2 ? y["return"] : op[0] ? y["throw"] || ((t = y["return"]) && t.call(y), 0) : y.next) && !(t = t.call(y, op[1])).done) return t;
      if (y = 0, t) op = [op[0] & 2, t.value];
      switch (op[0]) {
        case 0:
        case 1:
          t = op;
          break;
        case 4:
          _.label++;
          return { value: op[1], done: false };
        case 5:
          _.label++;
          y = op[1];
          op = [0];
          continue;
        case 7:
          op = _.ops.pop();
          _.trys.pop();
          continue;
        default:
          if (!(t = _.trys, t = t.length > 0 && t[t.length - 1]) && (op[0] === 6 || op[0] === 2)) {
            _ = 0;
            continue;
          }
          if (op[0] === 3 && (!t || op[1] > t[0] && op[1] < t[3])) {
            _.label = op[1];
            break;
          }
          if (op[0] === 6 && _.label < t[1]) {
            _.label = t[1];
            t = op;
            break;
          }
          if (t && _.label < t[2]) {
            _.label = t[2];
            _.ops.push(op);
            break;
          }
          if (t[2]) _.ops.pop();
          _.trys.pop();
          continue;
      }
      op = body.call(thisArg, _);
    } catch (e) {
      op = [6, e];
      y = 0;
    } finally {
      f = t = 0;
    }
    if (op[0] & 5) throw op[1];
    return { value: op[0] ? op[1] : void 0, done: true };
  }
}
function __values(o) {
  var s = typeof Symbol === "function" && Symbol.iterator, m = s && o[s], i = 0;
  if (m) return m.call(o);
  if (o && typeof o.length === "number") return {
    next: function() {
      if (o && i >= o.length) o = void 0;
      return { value: o && o[i++], done: !o };
    }
  };
  throw new TypeError(s ? "Object is not iterable." : "Symbol.iterator is not defined.");
}
function __read(o, n) {
  var m = typeof Symbol === "function" && o[Symbol.iterator];
  if (!m) return o;
  var i = m.call(o), r, ar = [], e;
  try {
    while ((n === void 0 || n-- > 0) && !(r = i.next()).done) ar.push(r.value);
  } catch (error) {
    e = { error };
  } finally {
    try {
      if (r && !r.done && (m = i["return"])) m.call(i);
    } finally {
      if (e) throw e.error;
    }
  }
  return ar;
}
typeof SuppressedError === "function" ? SuppressedError : function(error, suppressed, message) {
  var e = new Error(message);
  return e.name = "SuppressedError", e.error = error, e.suppressed = suppressed, e;
};
var ENTRIES = "ENTRIES";
var KEYS = "KEYS";
var VALUES = "VALUES";
var LEAF = "";
var TreeIterator = (
  /** @class */
  function() {
    function TreeIterator2(set, type) {
      var node = set._tree;
      var keys = Array.from(node.keys());
      this.set = set;
      this._type = type;
      this._path = keys.length > 0 ? [{ node, keys }] : [];
    }
    TreeIterator2.prototype.next = function() {
      var value = this.dive();
      this.backtrack();
      return value;
    };
    TreeIterator2.prototype.dive = function() {
      if (this._path.length === 0) {
        return { done: true, value: void 0 };
      }
      var _a2 = last$1(this._path), node = _a2.node, keys = _a2.keys;
      if (last$1(keys) === LEAF) {
        return { done: false, value: this.result() };
      }
      var child = node.get(last$1(keys));
      this._path.push({ node: child, keys: Array.from(child.keys()) });
      return this.dive();
    };
    TreeIterator2.prototype.backtrack = function() {
      if (this._path.length === 0) {
        return;
      }
      var keys = last$1(this._path).keys;
      keys.pop();
      if (keys.length > 0) {
        return;
      }
      this._path.pop();
      this.backtrack();
    };
    TreeIterator2.prototype.key = function() {
      return this.set._prefix + this._path.map(function(_a2) {
        var keys = _a2.keys;
        return last$1(keys);
      }).filter(function(key) {
        return key !== LEAF;
      }).join("");
    };
    TreeIterator2.prototype.value = function() {
      return last$1(this._path).node.get(LEAF);
    };
    TreeIterator2.prototype.result = function() {
      switch (this._type) {
        case VALUES:
          return this.value();
        case KEYS:
          return this.key();
        default:
          return [this.key(), this.value()];
      }
    };
    TreeIterator2.prototype[Symbol.iterator] = function() {
      return this;
    };
    return TreeIterator2;
  }()
);
var last$1 = function(array) {
  return array[array.length - 1];
};
var fuzzySearch = function(node, query, maxDistance) {
  var results = /* @__PURE__ */ new Map();
  if (query === void 0)
    return results;
  var n = query.length + 1;
  var m = n + maxDistance;
  var matrix = new Uint8Array(m * n).fill(maxDistance + 1);
  for (var j = 0; j < n; ++j)
    matrix[j] = j;
  for (var i = 1; i < m; ++i)
    matrix[i * n] = i;
  recurse(node, query, maxDistance, results, matrix, 1, n, "");
  return results;
};
var recurse = function(node, query, maxDistance, results, matrix, m, n, prefix) {
  var e_1, _a2;
  var offset = m * n;
  try {
    key: for (var _b = __values(node.keys()), _c = _b.next(); !_c.done; _c = _b.next()) {
      var key = _c.value;
      if (key === LEAF) {
        var distance = matrix[offset - 1];
        if (distance <= maxDistance) {
          results.set(prefix, [node.get(key), distance]);
        }
      } else {
        var i = m;
        for (var pos = 0; pos < key.length; ++pos, ++i) {
          var char = key[pos];
          var thisRowOffset = n * i;
          var prevRowOffset = thisRowOffset - n;
          var minDistance = matrix[thisRowOffset];
          var jmin = Math.max(0, i - maxDistance - 1);
          var jmax = Math.min(n - 1, i + maxDistance);
          for (var j = jmin; j < jmax; ++j) {
            var different = char !== query[j];
            var rpl = matrix[prevRowOffset + j] + +different;
            var del = matrix[prevRowOffset + j + 1] + 1;
            var ins = matrix[thisRowOffset + j] + 1;
            var dist = matrix[thisRowOffset + j + 1] = Math.min(rpl, del, ins);
            if (dist < minDistance)
              minDistance = dist;
          }
          if (minDistance > maxDistance) {
            continue key;
          }
        }
        recurse(node.get(key), query, maxDistance, results, matrix, i, n, prefix + key);
      }
    }
  } catch (e_1_1) {
    e_1 = { error: e_1_1 };
  } finally {
    try {
      if (_c && !_c.done && (_a2 = _b.return)) _a2.call(_b);
    } finally {
      if (e_1) throw e_1.error;
    }
  }
};
var SearchableMap = (
  /** @class */
  function() {
    function SearchableMap2(tree, prefix) {
      if (tree === void 0) {
        tree = /* @__PURE__ */ new Map();
      }
      if (prefix === void 0) {
        prefix = "";
      }
      this._size = void 0;
      this._tree = tree;
      this._prefix = prefix;
    }
    SearchableMap2.prototype.atPrefix = function(prefix) {
      var e_1, _a2;
      if (!prefix.startsWith(this._prefix)) {
        throw new Error("Mismatched prefix");
      }
      var _b = __read(trackDown(this._tree, prefix.slice(this._prefix.length)), 2), node = _b[0], path = _b[1];
      if (node === void 0) {
        var _c = __read(last(path), 2), parentNode = _c[0], key = _c[1];
        try {
          for (var _d = __values(parentNode.keys()), _e = _d.next(); !_e.done; _e = _d.next()) {
            var k = _e.value;
            if (k !== LEAF && k.startsWith(key)) {
              var node_1 = /* @__PURE__ */ new Map();
              node_1.set(k.slice(key.length), parentNode.get(k));
              return new SearchableMap2(node_1, prefix);
            }
          }
        } catch (e_1_1) {
          e_1 = { error: e_1_1 };
        } finally {
          try {
            if (_e && !_e.done && (_a2 = _d.return)) _a2.call(_d);
          } finally {
            if (e_1) throw e_1.error;
          }
        }
      }
      return new SearchableMap2(node, prefix);
    };
    SearchableMap2.prototype.clear = function() {
      this._size = void 0;
      this._tree.clear();
    };
    SearchableMap2.prototype.delete = function(key) {
      this._size = void 0;
      return remove(this._tree, key);
    };
    SearchableMap2.prototype.entries = function() {
      return new TreeIterator(this, ENTRIES);
    };
    SearchableMap2.prototype.forEach = function(fn) {
      var e_2, _a2;
      try {
        for (var _b = __values(this), _c = _b.next(); !_c.done; _c = _b.next()) {
          var _d = __read(_c.value, 2), key = _d[0], value = _d[1];
          fn(key, value, this);
        }
      } catch (e_2_1) {
        e_2 = { error: e_2_1 };
      } finally {
        try {
          if (_c && !_c.done && (_a2 = _b.return)) _a2.call(_b);
        } finally {
          if (e_2) throw e_2.error;
        }
      }
    };
    SearchableMap2.prototype.fuzzyGet = function(key, maxEditDistance) {
      return fuzzySearch(this._tree, key, maxEditDistance);
    };
    SearchableMap2.prototype.get = function(key) {
      var node = lookup(this._tree, key);
      return node !== void 0 ? node.get(LEAF) : void 0;
    };
    SearchableMap2.prototype.has = function(key) {
      var node = lookup(this._tree, key);
      return node !== void 0 && node.has(LEAF);
    };
    SearchableMap2.prototype.keys = function() {
      return new TreeIterator(this, KEYS);
    };
    SearchableMap2.prototype.set = function(key, value) {
      if (typeof key !== "string") {
        throw new Error("key must be a string");
      }
      this._size = void 0;
      var node = createPath(this._tree, key);
      node.set(LEAF, value);
      return this;
    };
    Object.defineProperty(SearchableMap2.prototype, "size", {
      /**
       * @see https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Map/size
       */
      get: function() {
        if (this._size) {
          return this._size;
        }
        this._size = 0;
        var iter = this.entries();
        while (!iter.next().done)
          this._size += 1;
        return this._size;
      },
      enumerable: false,
      configurable: true
    });
    SearchableMap2.prototype.update = function(key, fn) {
      if (typeof key !== "string") {
        throw new Error("key must be a string");
      }
      this._size = void 0;
      var node = createPath(this._tree, key);
      node.set(LEAF, fn(node.get(LEAF)));
      return this;
    };
    SearchableMap2.prototype.fetch = function(key, initial) {
      if (typeof key !== "string") {
        throw new Error("key must be a string");
      }
      this._size = void 0;
      var node = createPath(this._tree, key);
      var value = node.get(LEAF);
      if (value === void 0) {
        node.set(LEAF, value = initial());
      }
      return value;
    };
    SearchableMap2.prototype.values = function() {
      return new TreeIterator(this, VALUES);
    };
    SearchableMap2.prototype[Symbol.iterator] = function() {
      return this.entries();
    };
    SearchableMap2.from = function(entries) {
      var e_3, _a2;
      var tree = new SearchableMap2();
      try {
        for (var entries_1 = __values(entries), entries_1_1 = entries_1.next(); !entries_1_1.done; entries_1_1 = entries_1.next()) {
          var _b = __read(entries_1_1.value, 2), key = _b[0], value = _b[1];
          tree.set(key, value);
        }
      } catch (e_3_1) {
        e_3 = { error: e_3_1 };
      } finally {
        try {
          if (entries_1_1 && !entries_1_1.done && (_a2 = entries_1.return)) _a2.call(entries_1);
        } finally {
          if (e_3) throw e_3.error;
        }
      }
      return tree;
    };
    SearchableMap2.fromObject = function(object) {
      return SearchableMap2.from(Object.entries(object));
    };
    return SearchableMap2;
  }()
);
var trackDown = function(tree, key, path) {
  var e_4, _a2;
  if (path === void 0) {
    path = [];
  }
  if (key.length === 0 || tree == null) {
    return [tree, path];
  }
  try {
    for (var _b = __values(tree.keys()), _c = _b.next(); !_c.done; _c = _b.next()) {
      var k = _c.value;
      if (k !== LEAF && key.startsWith(k)) {
        path.push([tree, k]);
        return trackDown(tree.get(k), key.slice(k.length), path);
      }
    }
  } catch (e_4_1) {
    e_4 = { error: e_4_1 };
  } finally {
    try {
      if (_c && !_c.done && (_a2 = _b.return)) _a2.call(_b);
    } finally {
      if (e_4) throw e_4.error;
    }
  }
  path.push([tree, key]);
  return trackDown(void 0, "", path);
};
var lookup = function(tree, key) {
  var e_5, _a2;
  if (key.length === 0 || tree == null) {
    return tree;
  }
  try {
    for (var _b = __values(tree.keys()), _c = _b.next(); !_c.done; _c = _b.next()) {
      var k = _c.value;
      if (k !== LEAF && key.startsWith(k)) {
        return lookup(tree.get(k), key.slice(k.length));
      }
    }
  } catch (e_5_1) {
    e_5 = { error: e_5_1 };
  } finally {
    try {
      if (_c && !_c.done && (_a2 = _b.return)) _a2.call(_b);
    } finally {
      if (e_5) throw e_5.error;
    }
  }
};
var createPath = function(node, key) {
  var e_6, _a2;
  var keyLength = key.length;
  outer: for (var pos = 0; node && pos < keyLength; ) {
    try {
      for (var _b = (e_6 = void 0, __values(node.keys())), _c = _b.next(); !_c.done; _c = _b.next()) {
        var k = _c.value;
        if (k !== LEAF && key[pos] === k[0]) {
          var len = Math.min(keyLength - pos, k.length);
          var offset = 1;
          while (offset < len && key[pos + offset] === k[offset])
            ++offset;
          var child_1 = node.get(k);
          if (offset === k.length) {
            node = child_1;
          } else {
            var intermediate = /* @__PURE__ */ new Map();
            intermediate.set(k.slice(offset), child_1);
            node.set(key.slice(pos, pos + offset), intermediate);
            node.delete(k);
            node = intermediate;
          }
          pos += offset;
          continue outer;
        }
      }
    } catch (e_6_1) {
      e_6 = { error: e_6_1 };
    } finally {
      try {
        if (_c && !_c.done && (_a2 = _b.return)) _a2.call(_b);
      } finally {
        if (e_6) throw e_6.error;
      }
    }
    var child = /* @__PURE__ */ new Map();
    node.set(key.slice(pos), child);
    return child;
  }
  return node;
};
var remove = function(tree, key) {
  var _a2 = __read(trackDown(tree, key), 2), node = _a2[0], path = _a2[1];
  if (node === void 0) {
    return;
  }
  node.delete(LEAF);
  if (node.size === 0) {
    cleanup(path);
  } else if (node.size === 1) {
    var _b = __read(node.entries().next().value, 2), key_1 = _b[0], value = _b[1];
    merge(path, key_1, value);
  }
};
var cleanup = function(path) {
  if (path.length === 0) {
    return;
  }
  var _a2 = __read(last(path), 2), node = _a2[0], key = _a2[1];
  node.delete(key);
  if (node.size === 0) {
    cleanup(path.slice(0, -1));
  } else if (node.size === 1) {
    var _b = __read(node.entries().next().value, 2), key_2 = _b[0], value = _b[1];
    if (key_2 !== LEAF) {
      merge(path.slice(0, -1), key_2, value);
    }
  }
};
var merge = function(path, key, value) {
  if (path.length === 0) {
    return;
  }
  var _a2 = __read(last(path), 2), node = _a2[0], nodeKey = _a2[1];
  node.set(nodeKey + key, value);
  node.delete(nodeKey);
};
var last = function(array) {
  return array[array.length - 1];
};
var _a;
var OR = "or";
var AND = "and";
var AND_NOT = "and_not";
var MiniSearch = (
  /** @class */
  function() {
    function MiniSearch2(options) {
      if ((options === null || options === void 0 ? void 0 : options.fields) == null) {
        throw new Error('MiniSearch: option "fields" must be provided');
      }
      var autoVacuum = options.autoVacuum == null || options.autoVacuum === true ? defaultAutoVacuumOptions : options.autoVacuum;
      this._options = __assign(__assign(__assign({}, defaultOptions), options), { autoVacuum, searchOptions: __assign(__assign({}, defaultSearchOptions), options.searchOptions || {}), autoSuggestOptions: __assign(__assign({}, defaultAutoSuggestOptions), options.autoSuggestOptions || {}) });
      this._index = new SearchableMap();
      this._documentCount = 0;
      this._documentIds = /* @__PURE__ */ new Map();
      this._idToShortId = /* @__PURE__ */ new Map();
      this._fieldIds = {};
      this._fieldLength = /* @__PURE__ */ new Map();
      this._avgFieldLength = [];
      this._nextId = 0;
      this._storedFields = /* @__PURE__ */ new Map();
      this._dirtCount = 0;
      this._currentVacuum = null;
      this._enqueuedVacuum = null;
      this._enqueuedVacuumConditions = defaultVacuumConditions;
      this.addFields(this._options.fields);
    }
    MiniSearch2.prototype.add = function(document2) {
      var e_1, _a2, e_2, _b, e_3, _c;
      var _d = this._options, extractField = _d.extractField, tokenize = _d.tokenize, processTerm = _d.processTerm, fields = _d.fields, idField = _d.idField;
      var id = extractField(document2, idField);
      if (id == null) {
        throw new Error('MiniSearch: document does not have ID field "'.concat(idField, '"'));
      }
      if (this._idToShortId.has(id)) {
        throw new Error("MiniSearch: duplicate ID ".concat(id));
      }
      var shortDocumentId = this.addDocumentId(id);
      this.saveStoredFields(shortDocumentId, document2);
      try {
        for (var fields_1 = __values(fields), fields_1_1 = fields_1.next(); !fields_1_1.done; fields_1_1 = fields_1.next()) {
          var field = fields_1_1.value;
          var fieldValue = extractField(document2, field);
          if (fieldValue == null)
            continue;
          var tokens = tokenize(fieldValue.toString(), field);
          var fieldId = this._fieldIds[field];
          var uniqueTerms = new Set(tokens).size;
          this.addFieldLength(shortDocumentId, fieldId, this._documentCount - 1, uniqueTerms);
          try {
            for (var tokens_1 = (e_2 = void 0, __values(tokens)), tokens_1_1 = tokens_1.next(); !tokens_1_1.done; tokens_1_1 = tokens_1.next()) {
              var term = tokens_1_1.value;
              var processedTerm = processTerm(term, field);
              if (Array.isArray(processedTerm)) {
                try {
                  for (var processedTerm_1 = (e_3 = void 0, __values(processedTerm)), processedTerm_1_1 = processedTerm_1.next(); !processedTerm_1_1.done; processedTerm_1_1 = processedTerm_1.next()) {
                    var t = processedTerm_1_1.value;
                    this.addTerm(fieldId, shortDocumentId, t);
                  }
                } catch (e_3_1) {
                  e_3 = { error: e_3_1 };
                } finally {
                  try {
                    if (processedTerm_1_1 && !processedTerm_1_1.done && (_c = processedTerm_1.return)) _c.call(processedTerm_1);
                  } finally {
                    if (e_3) throw e_3.error;
                  }
                }
              } else if (processedTerm) {
                this.addTerm(fieldId, shortDocumentId, processedTerm);
              }
            }
          } catch (e_2_1) {
            e_2 = { error: e_2_1 };
          } finally {
            try {
              if (tokens_1_1 && !tokens_1_1.done && (_b = tokens_1.return)) _b.call(tokens_1);
            } finally {
              if (e_2) throw e_2.error;
            }
          }
        }
      } catch (e_1_1) {
        e_1 = { error: e_1_1 };
      } finally {
        try {
          if (fields_1_1 && !fields_1_1.done && (_a2 = fields_1.return)) _a2.call(fields_1);
        } finally {
          if (e_1) throw e_1.error;
        }
      }
    };
    MiniSearch2.prototype.addAll = function(documents) {
      var e_4, _a2;
      try {
        for (var documents_1 = __values(documents), documents_1_1 = documents_1.next(); !documents_1_1.done; documents_1_1 = documents_1.next()) {
          var document_1 = documents_1_1.value;
          this.add(document_1);
        }
      } catch (e_4_1) {
        e_4 = { error: e_4_1 };
      } finally {
        try {
          if (documents_1_1 && !documents_1_1.done && (_a2 = documents_1.return)) _a2.call(documents_1);
        } finally {
          if (e_4) throw e_4.error;
        }
      }
    };
    MiniSearch2.prototype.addAllAsync = function(documents, options) {
      var _this = this;
      if (options === void 0) {
        options = {};
      }
      var _a2 = options.chunkSize, chunkSize = _a2 === void 0 ? 10 : _a2;
      var acc = { chunk: [], promise: Promise.resolve() };
      var _b = documents.reduce(function(_a3, document2, i) {
        var chunk2 = _a3.chunk, promise2 = _a3.promise;
        chunk2.push(document2);
        if ((i + 1) % chunkSize === 0) {
          return {
            chunk: [],
            promise: promise2.then(function() {
              return new Promise(function(resolve) {
                return setTimeout(resolve, 0);
              });
            }).then(function() {
              return _this.addAll(chunk2);
            })
          };
        } else {
          return { chunk: chunk2, promise: promise2 };
        }
      }, acc), chunk = _b.chunk, promise = _b.promise;
      return promise.then(function() {
        return _this.addAll(chunk);
      });
    };
    MiniSearch2.prototype.remove = function(document2) {
      var e_5, _a2, e_6, _b, e_7, _c;
      var _d = this._options, tokenize = _d.tokenize, processTerm = _d.processTerm, extractField = _d.extractField, fields = _d.fields, idField = _d.idField;
      var id = extractField(document2, idField);
      if (id == null) {
        throw new Error('MiniSearch: document does not have ID field "'.concat(idField, '"'));
      }
      var shortId = this._idToShortId.get(id);
      if (shortId == null) {
        throw new Error("MiniSearch: cannot remove document with ID ".concat(id, ": it is not in the index"));
      }
      try {
        for (var fields_2 = __values(fields), fields_2_1 = fields_2.next(); !fields_2_1.done; fields_2_1 = fields_2.next()) {
          var field = fields_2_1.value;
          var fieldValue = extractField(document2, field);
          if (fieldValue == null)
            continue;
          var tokens = tokenize(fieldValue.toString(), field);
          var fieldId = this._fieldIds[field];
          var uniqueTerms = new Set(tokens).size;
          this.removeFieldLength(shortId, fieldId, this._documentCount, uniqueTerms);
          try {
            for (var tokens_2 = (e_6 = void 0, __values(tokens)), tokens_2_1 = tokens_2.next(); !tokens_2_1.done; tokens_2_1 = tokens_2.next()) {
              var term = tokens_2_1.value;
              var processedTerm = processTerm(term, field);
              if (Array.isArray(processedTerm)) {
                try {
                  for (var processedTerm_2 = (e_7 = void 0, __values(processedTerm)), processedTerm_2_1 = processedTerm_2.next(); !processedTerm_2_1.done; processedTerm_2_1 = processedTerm_2.next()) {
                    var t = processedTerm_2_1.value;
                    this.removeTerm(fieldId, shortId, t);
                  }
                } catch (e_7_1) {
                  e_7 = { error: e_7_1 };
                } finally {
                  try {
                    if (processedTerm_2_1 && !processedTerm_2_1.done && (_c = processedTerm_2.return)) _c.call(processedTerm_2);
                  } finally {
                    if (e_7) throw e_7.error;
                  }
                }
              } else if (processedTerm) {
                this.removeTerm(fieldId, shortId, processedTerm);
              }
            }
          } catch (e_6_1) {
            e_6 = { error: e_6_1 };
          } finally {
            try {
              if (tokens_2_1 && !tokens_2_1.done && (_b = tokens_2.return)) _b.call(tokens_2);
            } finally {
              if (e_6) throw e_6.error;
            }
          }
        }
      } catch (e_5_1) {
        e_5 = { error: e_5_1 };
      } finally {
        try {
          if (fields_2_1 && !fields_2_1.done && (_a2 = fields_2.return)) _a2.call(fields_2);
        } finally {
          if (e_5) throw e_5.error;
        }
      }
      this._storedFields.delete(shortId);
      this._documentIds.delete(shortId);
      this._idToShortId.delete(id);
      this._fieldLength.delete(shortId);
      this._documentCount -= 1;
    };
    MiniSearch2.prototype.removeAll = function(documents) {
      var e_8, _a2;
      if (documents) {
        try {
          for (var documents_2 = __values(documents), documents_2_1 = documents_2.next(); !documents_2_1.done; documents_2_1 = documents_2.next()) {
            var document_2 = documents_2_1.value;
            this.remove(document_2);
          }
        } catch (e_8_1) {
          e_8 = { error: e_8_1 };
        } finally {
          try {
            if (documents_2_1 && !documents_2_1.done && (_a2 = documents_2.return)) _a2.call(documents_2);
          } finally {
            if (e_8) throw e_8.error;
          }
        }
      } else if (arguments.length > 0) {
        throw new Error("Expected documents to be present. Omit the argument to remove all documents.");
      } else {
        this._index = new SearchableMap();
        this._documentCount = 0;
        this._documentIds = /* @__PURE__ */ new Map();
        this._idToShortId = /* @__PURE__ */ new Map();
        this._fieldLength = /* @__PURE__ */ new Map();
        this._avgFieldLength = [];
        this._storedFields = /* @__PURE__ */ new Map();
        this._nextId = 0;
      }
    };
    MiniSearch2.prototype.discard = function(id) {
      var _this = this;
      var shortId = this._idToShortId.get(id);
      if (shortId == null) {
        throw new Error("MiniSearch: cannot discard document with ID ".concat(id, ": it is not in the index"));
      }
      this._idToShortId.delete(id);
      this._documentIds.delete(shortId);
      this._storedFields.delete(shortId);
      (this._fieldLength.get(shortId) || []).forEach(function(fieldLength, fieldId) {
        _this.removeFieldLength(shortId, fieldId, _this._documentCount, fieldLength);
      });
      this._fieldLength.delete(shortId);
      this._documentCount -= 1;
      this._dirtCount += 1;
      this.maybeAutoVacuum();
    };
    MiniSearch2.prototype.maybeAutoVacuum = function() {
      if (this._options.autoVacuum === false) {
        return;
      }
      var _a2 = this._options.autoVacuum, minDirtFactor = _a2.minDirtFactor, minDirtCount = _a2.minDirtCount, batchSize = _a2.batchSize, batchWait = _a2.batchWait;
      this.conditionalVacuum({ batchSize, batchWait }, { minDirtCount, minDirtFactor });
    };
    MiniSearch2.prototype.discardAll = function(ids) {
      var e_9, _a2;
      var autoVacuum = this._options.autoVacuum;
      try {
        this._options.autoVacuum = false;
        try {
          for (var ids_1 = __values(ids), ids_1_1 = ids_1.next(); !ids_1_1.done; ids_1_1 = ids_1.next()) {
            var id = ids_1_1.value;
            this.discard(id);
          }
        } catch (e_9_1) {
          e_9 = { error: e_9_1 };
        } finally {
          try {
            if (ids_1_1 && !ids_1_1.done && (_a2 = ids_1.return)) _a2.call(ids_1);
          } finally {
            if (e_9) throw e_9.error;
          }
        }
      } finally {
        this._options.autoVacuum = autoVacuum;
      }
      this.maybeAutoVacuum();
    };
    MiniSearch2.prototype.replace = function(updatedDocument) {
      var _a2 = this._options, idField = _a2.idField, extractField = _a2.extractField;
      var id = extractField(updatedDocument, idField);
      this.discard(id);
      this.add(updatedDocument);
    };
    MiniSearch2.prototype.vacuum = function(options) {
      if (options === void 0) {
        options = {};
      }
      return this.conditionalVacuum(options);
    };
    MiniSearch2.prototype.conditionalVacuum = function(options, conditions) {
      var _this = this;
      if (this._currentVacuum) {
        this._enqueuedVacuumConditions = this._enqueuedVacuumConditions && conditions;
        if (this._enqueuedVacuum != null) {
          return this._enqueuedVacuum;
        }
        this._enqueuedVacuum = this._currentVacuum.then(function() {
          var conditions2 = _this._enqueuedVacuumConditions;
          _this._enqueuedVacuumConditions = defaultVacuumConditions;
          return _this.performVacuuming(options, conditions2);
        });
        return this._enqueuedVacuum;
      }
      if (this.vacuumConditionsMet(conditions) === false) {
        return Promise.resolve();
      }
      this._currentVacuum = this.performVacuuming(options);
      return this._currentVacuum;
    };
    MiniSearch2.prototype.performVacuuming = function(options, conditions) {
      return __awaiter(this, void 0, void 0, function() {
        var initialDirtCount, batchSize, batchWait_1, i, _a2, _b, _c, term, fieldsData, fieldsData_1, fieldsData_1_1, _d, fieldId, fieldIndex, fieldIndex_1, fieldIndex_1_1, _e, shortId, e_10_1;
        var e_10, _f, e_11, _g, e_12, _h;
        return __generator(this, function(_j) {
          switch (_j.label) {
            case 0:
              initialDirtCount = this._dirtCount;
              if (!this.vacuumConditionsMet(conditions)) return [3, 10];
              batchSize = options.batchSize || defaultVacuumOptions.batchSize;
              batchWait_1 = options.batchWait || defaultVacuumOptions.batchWait;
              i = 1;
              _j.label = 1;
            case 1:
              _j.trys.push([1, 7, 8, 9]);
              _a2 = __values(this._index), _b = _a2.next();
              _j.label = 2;
            case 2:
              if (!!_b.done) return [3, 6];
              _c = __read(_b.value, 2), term = _c[0], fieldsData = _c[1];
              try {
                for (fieldsData_1 = (e_11 = void 0, __values(fieldsData)), fieldsData_1_1 = fieldsData_1.next(); !fieldsData_1_1.done; fieldsData_1_1 = fieldsData_1.next()) {
                  _d = __read(fieldsData_1_1.value, 2), fieldId = _d[0], fieldIndex = _d[1];
                  try {
                    for (fieldIndex_1 = (e_12 = void 0, __values(fieldIndex)), fieldIndex_1_1 = fieldIndex_1.next(); !fieldIndex_1_1.done; fieldIndex_1_1 = fieldIndex_1.next()) {
                      _e = __read(fieldIndex_1_1.value, 1), shortId = _e[0];
                      if (this._documentIds.has(shortId)) {
                        continue;
                      }
                      if (fieldIndex.size <= 1) {
                        fieldsData.delete(fieldId);
                      } else {
                        fieldIndex.delete(shortId);
                      }
                    }
                  } catch (e_12_1) {
                    e_12 = { error: e_12_1 };
                  } finally {
                    try {
                      if (fieldIndex_1_1 && !fieldIndex_1_1.done && (_h = fieldIndex_1.return)) _h.call(fieldIndex_1);
                    } finally {
                      if (e_12) throw e_12.error;
                    }
                  }
                }
              } catch (e_11_1) {
                e_11 = { error: e_11_1 };
              } finally {
                try {
                  if (fieldsData_1_1 && !fieldsData_1_1.done && (_g = fieldsData_1.return)) _g.call(fieldsData_1);
                } finally {
                  if (e_11) throw e_11.error;
                }
              }
              if (this._index.get(term).size === 0) {
                this._index.delete(term);
              }
              if (!(i % batchSize === 0)) return [3, 4];
              return [4, new Promise(function(resolve) {
                return setTimeout(resolve, batchWait_1);
              })];
            case 3:
              _j.sent();
              _j.label = 4;
            case 4:
              i += 1;
              _j.label = 5;
            case 5:
              _b = _a2.next();
              return [3, 2];
            case 6:
              return [3, 9];
            case 7:
              e_10_1 = _j.sent();
              e_10 = { error: e_10_1 };
              return [3, 9];
            case 8:
              try {
                if (_b && !_b.done && (_f = _a2.return)) _f.call(_a2);
              } finally {
                if (e_10) throw e_10.error;
              }
              return [
                7
                /*endfinally*/
              ];
            case 9:
              this._dirtCount -= initialDirtCount;
              _j.label = 10;
            case 10:
              return [4, null];
            case 11:
              _j.sent();
              this._currentVacuum = this._enqueuedVacuum;
              this._enqueuedVacuum = null;
              return [
                2
                /*return*/
              ];
          }
        });
      });
    };
    MiniSearch2.prototype.vacuumConditionsMet = function(conditions) {
      if (conditions == null) {
        return true;
      }
      var minDirtCount = conditions.minDirtCount, minDirtFactor = conditions.minDirtFactor;
      minDirtCount = minDirtCount || defaultAutoVacuumOptions.minDirtCount;
      minDirtFactor = minDirtFactor || defaultAutoVacuumOptions.minDirtFactor;
      return this.dirtCount >= minDirtCount && this.dirtFactor >= minDirtFactor;
    };
    Object.defineProperty(MiniSearch2.prototype, "isVacuuming", {
      /**
       * Is `true` if a vacuuming operation is ongoing, `false` otherwise
       */
      get: function() {
        return this._currentVacuum != null;
      },
      enumerable: false,
      configurable: true
    });
    Object.defineProperty(MiniSearch2.prototype, "dirtCount", {
      /**
       * The number of documents discarded since the most recent vacuuming
       */
      get: function() {
        return this._dirtCount;
      },
      enumerable: false,
      configurable: true
    });
    Object.defineProperty(MiniSearch2.prototype, "dirtFactor", {
      /**
       * A number between 0 and 1 giving an indication about the proportion of
       * documents that are discarded, and can therefore be cleaned up by vacuuming.
       * A value close to 0 means that the index is relatively clean, while a higher
       * value means that the index is relatively dirty, and vacuuming could release
       * memory.
       */
      get: function() {
        return this._dirtCount / (1 + this._documentCount + this._dirtCount);
      },
      enumerable: false,
      configurable: true
    });
    MiniSearch2.prototype.has = function(id) {
      return this._idToShortId.has(id);
    };
    MiniSearch2.prototype.getStoredFields = function(id) {
      var shortId = this._idToShortId.get(id);
      if (shortId == null) {
        return void 0;
      }
      return this._storedFields.get(shortId);
    };
    MiniSearch2.prototype.search = function(query, searchOptions) {
      var e_13, _a2;
      if (searchOptions === void 0) {
        searchOptions = {};
      }
      var rawResults = this.executeQuery(query, searchOptions);
      var results = [];
      try {
        for (var rawResults_1 = __values(rawResults), rawResults_1_1 = rawResults_1.next(); !rawResults_1_1.done; rawResults_1_1 = rawResults_1.next()) {
          var _b = __read(rawResults_1_1.value, 2), docId = _b[0], _c = _b[1], score = _c.score, terms = _c.terms, match = _c.match;
          var quality = terms.length || 1;
          var result = {
            id: this._documentIds.get(docId),
            score: score * quality,
            terms: Object.keys(match),
            queryTerms: terms,
            match
          };
          Object.assign(result, this._storedFields.get(docId));
          if (searchOptions.filter == null || searchOptions.filter(result)) {
            results.push(result);
          }
        }
      } catch (e_13_1) {
        e_13 = { error: e_13_1 };
      } finally {
        try {
          if (rawResults_1_1 && !rawResults_1_1.done && (_a2 = rawResults_1.return)) _a2.call(rawResults_1);
        } finally {
          if (e_13) throw e_13.error;
        }
      }
      if (query === MiniSearch2.wildcard && searchOptions.boostDocument == null && this._options.searchOptions.boostDocument == null) {
        return results;
      }
      results.sort(byScore);
      return results;
    };
    MiniSearch2.prototype.autoSuggest = function(queryString, options) {
      var e_14, _a2, e_15, _b;
      if (options === void 0) {
        options = {};
      }
      options = __assign(__assign({}, this._options.autoSuggestOptions), options);
      var suggestions = /* @__PURE__ */ new Map();
      try {
        for (var _c = __values(this.search(queryString, options)), _d = _c.next(); !_d.done; _d = _c.next()) {
          var _e = _d.value, score = _e.score, terms = _e.terms;
          var phrase = terms.join(" ");
          var suggestion = suggestions.get(phrase);
          if (suggestion != null) {
            suggestion.score += score;
            suggestion.count += 1;
          } else {
            suggestions.set(phrase, { score, terms, count: 1 });
          }
        }
      } catch (e_14_1) {
        e_14 = { error: e_14_1 };
      } finally {
        try {
          if (_d && !_d.done && (_a2 = _c.return)) _a2.call(_c);
        } finally {
          if (e_14) throw e_14.error;
        }
      }
      var results = [];
      try {
        for (var suggestions_1 = __values(suggestions), suggestions_1_1 = suggestions_1.next(); !suggestions_1_1.done; suggestions_1_1 = suggestions_1.next()) {
          var _f = __read(suggestions_1_1.value, 2), suggestion = _f[0], _g = _f[1], score = _g.score, terms = _g.terms, count = _g.count;
          results.push({ suggestion, terms, score: score / count });
        }
      } catch (e_15_1) {
        e_15 = { error: e_15_1 };
      } finally {
        try {
          if (suggestions_1_1 && !suggestions_1_1.done && (_b = suggestions_1.return)) _b.call(suggestions_1);
        } finally {
          if (e_15) throw e_15.error;
        }
      }
      results.sort(byScore);
      return results;
    };
    Object.defineProperty(MiniSearch2.prototype, "documentCount", {
      /**
       * Total number of documents available to search
       */
      get: function() {
        return this._documentCount;
      },
      enumerable: false,
      configurable: true
    });
    Object.defineProperty(MiniSearch2.prototype, "termCount", {
      /**
       * Number of terms in the index
       */
      get: function() {
        return this._index.size;
      },
      enumerable: false,
      configurable: true
    });
    MiniSearch2.loadJSON = function(json, options) {
      if (options == null) {
        throw new Error("MiniSearch: loadJSON should be given the same options used when serializing the index");
      }
      return this.loadJS(JSON.parse(json), options);
    };
    MiniSearch2.getDefault = function(optionName) {
      if (defaultOptions.hasOwnProperty(optionName)) {
        return getOwnProperty(defaultOptions, optionName);
      } else {
        throw new Error('MiniSearch: unknown option "'.concat(optionName, '"'));
      }
    };
    MiniSearch2.loadJS = function(js, options) {
      var e_16, _a2, e_17, _b, e_18, _c;
      var index = js.index, documentCount = js.documentCount, nextId = js.nextId, documentIds = js.documentIds, fieldIds = js.fieldIds, fieldLength = js.fieldLength, averageFieldLength = js.averageFieldLength, storedFields = js.storedFields, dirtCount = js.dirtCount, serializationVersion = js.serializationVersion;
      if (serializationVersion !== 1 && serializationVersion !== 2) {
        throw new Error("MiniSearch: cannot deserialize an index created with an incompatible version");
      }
      var miniSearch = new MiniSearch2(options);
      miniSearch._documentCount = documentCount;
      miniSearch._nextId = nextId;
      miniSearch._documentIds = objectToNumericMap(documentIds);
      miniSearch._idToShortId = /* @__PURE__ */ new Map();
      miniSearch._fieldIds = fieldIds;
      miniSearch._fieldLength = objectToNumericMap(fieldLength);
      miniSearch._avgFieldLength = averageFieldLength;
      miniSearch._storedFields = objectToNumericMap(storedFields);
      miniSearch._dirtCount = dirtCount || 0;
      miniSearch._index = new SearchableMap();
      try {
        for (var _d = __values(miniSearch._documentIds), _e = _d.next(); !_e.done; _e = _d.next()) {
          var _f = __read(_e.value, 2), shortId = _f[0], id = _f[1];
          miniSearch._idToShortId.set(id, shortId);
        }
      } catch (e_16_1) {
        e_16 = { error: e_16_1 };
      } finally {
        try {
          if (_e && !_e.done && (_a2 = _d.return)) _a2.call(_d);
        } finally {
          if (e_16) throw e_16.error;
        }
      }
      try {
        for (var index_1 = __values(index), index_1_1 = index_1.next(); !index_1_1.done; index_1_1 = index_1.next()) {
          var _g = __read(index_1_1.value, 2), term = _g[0], data = _g[1];
          var dataMap = /* @__PURE__ */ new Map();
          try {
            for (var _h = (e_18 = void 0, __values(Object.keys(data))), _j = _h.next(); !_j.done; _j = _h.next()) {
              var fieldId = _j.value;
              var indexEntry = data[fieldId];
              if (serializationVersion === 1) {
                indexEntry = indexEntry.ds;
              }
              dataMap.set(parseInt(fieldId, 10), objectToNumericMap(indexEntry));
            }
          } catch (e_18_1) {
            e_18 = { error: e_18_1 };
          } finally {
            try {
              if (_j && !_j.done && (_c = _h.return)) _c.call(_h);
            } finally {
              if (e_18) throw e_18.error;
            }
          }
          miniSearch._index.set(term, dataMap);
        }
      } catch (e_17_1) {
        e_17 = { error: e_17_1 };
      } finally {
        try {
          if (index_1_1 && !index_1_1.done && (_b = index_1.return)) _b.call(index_1);
        } finally {
          if (e_17) throw e_17.error;
        }
      }
      return miniSearch;
    };
    MiniSearch2.prototype.executeQuery = function(query, searchOptions) {
      var _this = this;
      if (searchOptions === void 0) {
        searchOptions = {};
      }
      if (query === MiniSearch2.wildcard) {
        return this.executeWildcardQuery(searchOptions);
      }
      if (typeof query !== "string") {
        var options_1 = __assign(__assign(__assign({}, searchOptions), query), { queries: void 0 });
        var results_1 = query.queries.map(function(subquery) {
          return _this.executeQuery(subquery, options_1);
        });
        return this.combineResults(results_1, options_1.combineWith);
      }
      var _a2 = this._options, tokenize = _a2.tokenize, processTerm = _a2.processTerm, globalSearchOptions = _a2.searchOptions;
      var options = __assign(__assign({ tokenize, processTerm }, globalSearchOptions), searchOptions);
      var searchTokenize = options.tokenize, searchProcessTerm = options.processTerm;
      var terms = searchTokenize(query).flatMap(function(term) {
        return searchProcessTerm(term);
      }).filter(function(term) {
        return !!term;
      });
      var queries = terms.map(termToQuerySpec(options));
      var results = queries.map(function(query2) {
        return _this.executeQuerySpec(query2, options);
      });
      return this.combineResults(results, options.combineWith);
    };
    MiniSearch2.prototype.executeQuerySpec = function(query, searchOptions) {
      var e_19, _a2, e_20, _b;
      var options = __assign(__assign({}, this._options.searchOptions), searchOptions);
      var boosts = (options.fields || this._options.fields).reduce(function(boosts2, field) {
        var _a3;
        return __assign(__assign({}, boosts2), (_a3 = {}, _a3[field] = getOwnProperty(options.boost, field) || 1, _a3));
      }, {});
      var boostDocument = options.boostDocument, weights = options.weights, maxFuzzy = options.maxFuzzy, bm25params = options.bm25;
      var _c = __assign(__assign({}, defaultSearchOptions.weights), weights), fuzzyWeight = _c.fuzzy, prefixWeight = _c.prefix;
      var data = this._index.get(query.term);
      var results = this.termResults(query.term, query.term, 1, data, boosts, boostDocument, bm25params);
      var prefixMatches;
      var fuzzyMatches;
      if (query.prefix) {
        prefixMatches = this._index.atPrefix(query.term);
      }
      if (query.fuzzy) {
        var fuzzy = query.fuzzy === true ? 0.2 : query.fuzzy;
        var maxDistance = fuzzy < 1 ? Math.min(maxFuzzy, Math.round(query.term.length * fuzzy)) : fuzzy;
        if (maxDistance)
          fuzzyMatches = this._index.fuzzyGet(query.term, maxDistance);
      }
      if (prefixMatches) {
        try {
          for (var prefixMatches_1 = __values(prefixMatches), prefixMatches_1_1 = prefixMatches_1.next(); !prefixMatches_1_1.done; prefixMatches_1_1 = prefixMatches_1.next()) {
            var _d = __read(prefixMatches_1_1.value, 2), term = _d[0], data_1 = _d[1];
            var distance = term.length - query.term.length;
            if (!distance) {
              continue;
            }
            fuzzyMatches === null || fuzzyMatches === void 0 ? void 0 : fuzzyMatches.delete(term);
            var weight = prefixWeight * term.length / (term.length + 0.3 * distance);
            this.termResults(query.term, term, weight, data_1, boosts, boostDocument, bm25params, results);
          }
        } catch (e_19_1) {
          e_19 = { error: e_19_1 };
        } finally {
          try {
            if (prefixMatches_1_1 && !prefixMatches_1_1.done && (_a2 = prefixMatches_1.return)) _a2.call(prefixMatches_1);
          } finally {
            if (e_19) throw e_19.error;
          }
        }
      }
      if (fuzzyMatches) {
        try {
          for (var _e = __values(fuzzyMatches.keys()), _f = _e.next(); !_f.done; _f = _e.next()) {
            var term = _f.value;
            var _g = __read(fuzzyMatches.get(term), 2), data_2 = _g[0], distance = _g[1];
            if (!distance) {
              continue;
            }
            var weight = fuzzyWeight * term.length / (term.length + distance);
            this.termResults(query.term, term, weight, data_2, boosts, boostDocument, bm25params, results);
          }
        } catch (e_20_1) {
          e_20 = { error: e_20_1 };
        } finally {
          try {
            if (_f && !_f.done && (_b = _e.return)) _b.call(_e);
          } finally {
            if (e_20) throw e_20.error;
          }
        }
      }
      return results;
    };
    MiniSearch2.prototype.executeWildcardQuery = function(searchOptions) {
      var e_21, _a2;
      var results = /* @__PURE__ */ new Map();
      var options = __assign(__assign({}, this._options.searchOptions), searchOptions);
      try {
        for (var _b = __values(this._documentIds), _c = _b.next(); !_c.done; _c = _b.next()) {
          var _d = __read(_c.value, 2), shortId = _d[0], id = _d[1];
          var score = options.boostDocument ? options.boostDocument(id, "", this._storedFields.get(shortId)) : 1;
          results.set(shortId, {
            score,
            terms: [],
            match: {}
          });
        }
      } catch (e_21_1) {
        e_21 = { error: e_21_1 };
      } finally {
        try {
          if (_c && !_c.done && (_a2 = _b.return)) _a2.call(_b);
        } finally {
          if (e_21) throw e_21.error;
        }
      }
      return results;
    };
    MiniSearch2.prototype.combineResults = function(results, combineWith) {
      if (combineWith === void 0) {
        combineWith = OR;
      }
      if (results.length === 0) {
        return /* @__PURE__ */ new Map();
      }
      var operator = combineWith.toLowerCase();
      return results.reduce(combinators[operator]) || /* @__PURE__ */ new Map();
    };
    MiniSearch2.prototype.toJSON = function() {
      var e_22, _a2, e_23, _b;
      var index = [];
      try {
        for (var _c = __values(this._index), _d = _c.next(); !_d.done; _d = _c.next()) {
          var _e = __read(_d.value, 2), term = _e[0], fieldIndex = _e[1];
          var data = {};
          try {
            for (var fieldIndex_2 = (e_23 = void 0, __values(fieldIndex)), fieldIndex_2_1 = fieldIndex_2.next(); !fieldIndex_2_1.done; fieldIndex_2_1 = fieldIndex_2.next()) {
              var _f = __read(fieldIndex_2_1.value, 2), fieldId = _f[0], freqs = _f[1];
              data[fieldId] = Object.fromEntries(freqs);
            }
          } catch (e_23_1) {
            e_23 = { error: e_23_1 };
          } finally {
            try {
              if (fieldIndex_2_1 && !fieldIndex_2_1.done && (_b = fieldIndex_2.return)) _b.call(fieldIndex_2);
            } finally {
              if (e_23) throw e_23.error;
            }
          }
          index.push([term, data]);
        }
      } catch (e_22_1) {
        e_22 = { error: e_22_1 };
      } finally {
        try {
          if (_d && !_d.done && (_a2 = _c.return)) _a2.call(_c);
        } finally {
          if (e_22) throw e_22.error;
        }
      }
      return {
        documentCount: this._documentCount,
        nextId: this._nextId,
        documentIds: Object.fromEntries(this._documentIds),
        fieldIds: this._fieldIds,
        fieldLength: Object.fromEntries(this._fieldLength),
        averageFieldLength: this._avgFieldLength,
        storedFields: Object.fromEntries(this._storedFields),
        dirtCount: this._dirtCount,
        index,
        serializationVersion: 2
      };
    };
    MiniSearch2.prototype.termResults = function(sourceTerm, derivedTerm, termWeight, fieldTermData, fieldBoosts, boostDocumentFn, bm25params, results) {
      var e_24, _a2, e_25, _b, _c;
      if (results === void 0) {
        results = /* @__PURE__ */ new Map();
      }
      if (fieldTermData == null)
        return results;
      try {
        for (var _d = __values(Object.keys(fieldBoosts)), _e = _d.next(); !_e.done; _e = _d.next()) {
          var field = _e.value;
          var fieldBoost = fieldBoosts[field];
          var fieldId = this._fieldIds[field];
          var fieldTermFreqs = fieldTermData.get(fieldId);
          if (fieldTermFreqs == null)
            continue;
          var matchingFields = fieldTermFreqs.size;
          var avgFieldLength = this._avgFieldLength[fieldId];
          try {
            for (var _f = (e_25 = void 0, __values(fieldTermFreqs.keys())), _g = _f.next(); !_g.done; _g = _f.next()) {
              var docId = _g.value;
              if (!this._documentIds.has(docId)) {
                this.removeTerm(fieldId, docId, derivedTerm);
                matchingFields -= 1;
                continue;
              }
              var docBoost = boostDocumentFn ? boostDocumentFn(this._documentIds.get(docId), derivedTerm, this._storedFields.get(docId)) : 1;
              if (!docBoost)
                continue;
              var termFreq = fieldTermFreqs.get(docId);
              var fieldLength = this._fieldLength.get(docId)[fieldId];
              var rawScore = calcBM25Score(termFreq, matchingFields, this._documentCount, fieldLength, avgFieldLength, bm25params);
              var weightedScore = termWeight * fieldBoost * docBoost * rawScore;
              var result = results.get(docId);
              if (result) {
                result.score += weightedScore;
                assignUniqueTerm(result.terms, sourceTerm);
                var match = getOwnProperty(result.match, derivedTerm);
                if (match) {
                  match.push(field);
                } else {
                  result.match[derivedTerm] = [field];
                }
              } else {
                results.set(docId, {
                  score: weightedScore,
                  terms: [sourceTerm],
                  match: (_c = {}, _c[derivedTerm] = [field], _c)
                });
              }
            }
          } catch (e_25_1) {
            e_25 = { error: e_25_1 };
          } finally {
            try {
              if (_g && !_g.done && (_b = _f.return)) _b.call(_f);
            } finally {
              if (e_25) throw e_25.error;
            }
          }
        }
      } catch (e_24_1) {
        e_24 = { error: e_24_1 };
      } finally {
        try {
          if (_e && !_e.done && (_a2 = _d.return)) _a2.call(_d);
        } finally {
          if (e_24) throw e_24.error;
        }
      }
      return results;
    };
    MiniSearch2.prototype.addTerm = function(fieldId, documentId, term) {
      var indexData = this._index.fetch(term, createMap);
      var fieldIndex = indexData.get(fieldId);
      if (fieldIndex == null) {
        fieldIndex = /* @__PURE__ */ new Map();
        fieldIndex.set(documentId, 1);
        indexData.set(fieldId, fieldIndex);
      } else {
        var docs = fieldIndex.get(documentId);
        fieldIndex.set(documentId, (docs || 0) + 1);
      }
    };
    MiniSearch2.prototype.removeTerm = function(fieldId, documentId, term) {
      if (!this._index.has(term)) {
        this.warnDocumentChanged(documentId, fieldId, term);
        return;
      }
      var indexData = this._index.fetch(term, createMap);
      var fieldIndex = indexData.get(fieldId);
      if (fieldIndex == null || fieldIndex.get(documentId) == null) {
        this.warnDocumentChanged(documentId, fieldId, term);
      } else if (fieldIndex.get(documentId) <= 1) {
        if (fieldIndex.size <= 1) {
          indexData.delete(fieldId);
        } else {
          fieldIndex.delete(documentId);
        }
      } else {
        fieldIndex.set(documentId, fieldIndex.get(documentId) - 1);
      }
      if (this._index.get(term).size === 0) {
        this._index.delete(term);
      }
    };
    MiniSearch2.prototype.warnDocumentChanged = function(shortDocumentId, fieldId, term) {
      var e_26, _a2;
      try {
        for (var _b = __values(Object.keys(this._fieldIds)), _c = _b.next(); !_c.done; _c = _b.next()) {
          var fieldName = _c.value;
          if (this._fieldIds[fieldName] === fieldId) {
            this._options.logger("warn", "MiniSearch: document with ID ".concat(this._documentIds.get(shortDocumentId), ' has changed before removal: term "').concat(term, '" was not present in field "').concat(fieldName, '". Removing a document after it has changed can corrupt the index!'), "version_conflict");
            return;
          }
        }
      } catch (e_26_1) {
        e_26 = { error: e_26_1 };
      } finally {
        try {
          if (_c && !_c.done && (_a2 = _b.return)) _a2.call(_b);
        } finally {
          if (e_26) throw e_26.error;
        }
      }
    };
    MiniSearch2.prototype.addDocumentId = function(documentId) {
      var shortDocumentId = this._nextId;
      this._idToShortId.set(documentId, shortDocumentId);
      this._documentIds.set(shortDocumentId, documentId);
      this._documentCount += 1;
      this._nextId += 1;
      return shortDocumentId;
    };
    MiniSearch2.prototype.addFields = function(fields) {
      for (var i = 0; i < fields.length; i++) {
        this._fieldIds[fields[i]] = i;
      }
    };
    MiniSearch2.prototype.addFieldLength = function(documentId, fieldId, count, length) {
      var fieldLengths = this._fieldLength.get(documentId);
      if (fieldLengths == null)
        this._fieldLength.set(documentId, fieldLengths = []);
      fieldLengths[fieldId] = length;
      var averageFieldLength = this._avgFieldLength[fieldId] || 0;
      var totalFieldLength = averageFieldLength * count + length;
      this._avgFieldLength[fieldId] = totalFieldLength / (count + 1);
    };
    MiniSearch2.prototype.removeFieldLength = function(documentId, fieldId, count, length) {
      if (count === 1) {
        this._avgFieldLength[fieldId] = 0;
        return;
      }
      var totalFieldLength = this._avgFieldLength[fieldId] * count - length;
      this._avgFieldLength[fieldId] = totalFieldLength / (count - 1);
    };
    MiniSearch2.prototype.saveStoredFields = function(documentId, doc) {
      var e_27, _a2;
      var _b = this._options, storeFields = _b.storeFields, extractField = _b.extractField;
      if (storeFields == null || storeFields.length === 0) {
        return;
      }
      var documentFields = this._storedFields.get(documentId);
      if (documentFields == null)
        this._storedFields.set(documentId, documentFields = {});
      try {
        for (var storeFields_1 = __values(storeFields), storeFields_1_1 = storeFields_1.next(); !storeFields_1_1.done; storeFields_1_1 = storeFields_1.next()) {
          var fieldName = storeFields_1_1.value;
          var fieldValue = extractField(doc, fieldName);
          if (fieldValue !== void 0)
            documentFields[fieldName] = fieldValue;
        }
      } catch (e_27_1) {
        e_27 = { error: e_27_1 };
      } finally {
        try {
          if (storeFields_1_1 && !storeFields_1_1.done && (_a2 = storeFields_1.return)) _a2.call(storeFields_1);
        } finally {
          if (e_27) throw e_27.error;
        }
      }
    };
    MiniSearch2.wildcard = Symbol("*");
    return MiniSearch2;
  }()
);
var getOwnProperty = function(object, property) {
  return Object.prototype.hasOwnProperty.call(object, property) ? object[property] : void 0;
};
var combinators = (_a = {}, _a[OR] = function(a, b) {
  var e_28, _a2;
  try {
    for (var _b = __values(b.keys()), _c = _b.next(); !_c.done; _c = _b.next()) {
      var docId = _c.value;
      var existing = a.get(docId);
      if (existing == null) {
        a.set(docId, b.get(docId));
      } else {
        var _d = b.get(docId), score = _d.score, terms = _d.terms, match = _d.match;
        existing.score = existing.score + score;
        existing.match = Object.assign(existing.match, match);
        assignUniqueTerms(existing.terms, terms);
      }
    }
  } catch (e_28_1) {
    e_28 = { error: e_28_1 };
  } finally {
    try {
      if (_c && !_c.done && (_a2 = _b.return)) _a2.call(_b);
    } finally {
      if (e_28) throw e_28.error;
    }
  }
  return a;
}, _a[AND] = function(a, b) {
  var e_29, _a2;
  var combined = /* @__PURE__ */ new Map();
  try {
    for (var _b = __values(b.keys()), _c = _b.next(); !_c.done; _c = _b.next()) {
      var docId = _c.value;
      var existing = a.get(docId);
      if (existing == null)
        continue;
      var _d = b.get(docId), score = _d.score, terms = _d.terms, match = _d.match;
      assignUniqueTerms(existing.terms, terms);
      combined.set(docId, {
        score: existing.score + score,
        terms: existing.terms,
        match: Object.assign(existing.match, match)
      });
    }
  } catch (e_29_1) {
    e_29 = { error: e_29_1 };
  } finally {
    try {
      if (_c && !_c.done && (_a2 = _b.return)) _a2.call(_b);
    } finally {
      if (e_29) throw e_29.error;
    }
  }
  return combined;
}, _a[AND_NOT] = function(a, b) {
  var e_30, _a2;
  try {
    for (var _b = __values(b.keys()), _c = _b.next(); !_c.done; _c = _b.next()) {
      var docId = _c.value;
      a.delete(docId);
    }
  } catch (e_30_1) {
    e_30 = { error: e_30_1 };
  } finally {
    try {
      if (_c && !_c.done && (_a2 = _b.return)) _a2.call(_b);
    } finally {
      if (e_30) throw e_30.error;
    }
  }
  return a;
}, _a);
var defaultBM25params = { k: 1.2, b: 0.7, d: 0.5 };
var calcBM25Score = function(termFreq, matchingCount, totalCount, fieldLength, avgFieldLength, bm25params) {
  var k = bm25params.k, b = bm25params.b, d = bm25params.d;
  var invDocFreq = Math.log(1 + (totalCount - matchingCount + 0.5) / (matchingCount + 0.5));
  return invDocFreq * (d + termFreq * (k + 1) / (termFreq + k * (1 - b + b * fieldLength / avgFieldLength)));
};
var termToQuerySpec = function(options) {
  return function(term, i, terms) {
    var fuzzy = typeof options.fuzzy === "function" ? options.fuzzy(term, i, terms) : options.fuzzy || false;
    var prefix = typeof options.prefix === "function" ? options.prefix(term, i, terms) : options.prefix === true;
    return { term, fuzzy, prefix };
  };
};
var defaultOptions = {
  idField: "id",
  extractField: function(document2, fieldName) {
    return document2[fieldName];
  },
  tokenize: function(text) {
    return text.split(SPACE_OR_PUNCTUATION);
  },
  processTerm: function(term) {
    return term.toLowerCase();
  },
  fields: void 0,
  searchOptions: void 0,
  storeFields: [],
  logger: function(level, message) {
    if (typeof (console === null || console === void 0 ? void 0 : console[level]) === "function")
      console[level](message);
  },
  autoVacuum: true
};
var defaultSearchOptions = {
  combineWith: OR,
  prefix: false,
  fuzzy: false,
  maxFuzzy: 6,
  boost: {},
  weights: { fuzzy: 0.45, prefix: 0.375 },
  bm25: defaultBM25params
};
var defaultAutoSuggestOptions = {
  combineWith: AND,
  prefix: function(term, i, terms) {
    return i === terms.length - 1;
  }
};
var defaultVacuumOptions = { batchSize: 1e3, batchWait: 10 };
var defaultVacuumConditions = { minDirtFactor: 0.1, minDirtCount: 20 };
var defaultAutoVacuumOptions = __assign(__assign({}, defaultVacuumOptions), defaultVacuumConditions);
var assignUniqueTerm = function(target, term) {
  if (!target.includes(term))
    target.push(term);
};
var assignUniqueTerms = function(target, source) {
  var e_31, _a2;
  try {
    for (var source_1 = __values(source), source_1_1 = source_1.next(); !source_1_1.done; source_1_1 = source_1.next()) {
      var term = source_1_1.value;
      if (!target.includes(term))
        target.push(term);
    }
  } catch (e_31_1) {
    e_31 = { error: e_31_1 };
  } finally {
    try {
      if (source_1_1 && !source_1_1.done && (_a2 = source_1.return)) _a2.call(source_1);
    } finally {
      if (e_31) throw e_31.error;
    }
  }
};
var byScore = function(_a2, _b) {
  var a = _a2.score;
  var b = _b.score;
  return b - a;
};
var createMap = function() {
  return /* @__PURE__ */ new Map();
};
var objectToNumericMap = function(object) {
  var e_32, _a2;
  var map = /* @__PURE__ */ new Map();
  try {
    for (var _b = __values(Object.keys(object)), _c = _b.next(); !_c.done; _c = _b.next()) {
      var key = _c.value;
      map.set(parseInt(key, 10), object[key]);
    }
  } catch (e_32_1) {
    e_32 = { error: e_32_1 };
  } finally {
    try {
      if (_c && !_c.done && (_a2 = _b.return)) _a2.call(_b);
    } finally {
      if (e_32) throw e_32.error;
    }
  }
  return map;
};
var SPACE_OR_PUNCTUATION = /[\n\r -#%-*,-/:;?@[-\]_{}\u00A0\u00A1\u00A7\u00AB\u00B6\u00B7\u00BB\u00BF\u037E\u0387\u055A-\u055F\u0589\u058A\u05BE\u05C0\u05C3\u05C6\u05F3\u05F4\u0609\u060A\u060C\u060D\u061B\u061E\u061F\u066A-\u066D\u06D4\u0700-\u070D\u07F7-\u07F9\u0830-\u083E\u085E\u0964\u0965\u0970\u09FD\u0A76\u0AF0\u0C77\u0C84\u0DF4\u0E4F\u0E5A\u0E5B\u0F04-\u0F12\u0F14\u0F3A-\u0F3D\u0F85\u0FD0-\u0FD4\u0FD9\u0FDA\u104A-\u104F\u10FB\u1360-\u1368\u1400\u166E\u1680\u169B\u169C\u16EB-\u16ED\u1735\u1736\u17D4-\u17D6\u17D8-\u17DA\u1800-\u180A\u1944\u1945\u1A1E\u1A1F\u1AA0-\u1AA6\u1AA8-\u1AAD\u1B5A-\u1B60\u1BFC-\u1BFF\u1C3B-\u1C3F\u1C7E\u1C7F\u1CC0-\u1CC7\u1CD3\u2000-\u200A\u2010-\u2029\u202F-\u2043\u2045-\u2051\u2053-\u205F\u207D\u207E\u208D\u208E\u2308-\u230B\u2329\u232A\u2768-\u2775\u27C5\u27C6\u27E6-\u27EF\u2983-\u2998\u29D8-\u29DB\u29FC\u29FD\u2CF9-\u2CFC\u2CFE\u2CFF\u2D70\u2E00-\u2E2E\u2E30-\u2E4F\u3000-\u3003\u3008-\u3011\u3014-\u301F\u3030\u303D\u30A0\u30FB\uA4FE\uA4FF\uA60D-\uA60F\uA673\uA67E\uA6F2-\uA6F7\uA874-\uA877\uA8CE\uA8CF\uA8F8-\uA8FA\uA8FC\uA92E\uA92F\uA95F\uA9C1-\uA9CD\uA9DE\uA9DF\uAA5C-\uAA5F\uAADE\uAADF\uAAF0\uAAF1\uABEB\uFD3E\uFD3F\uFE10-\uFE19\uFE30-\uFE52\uFE54-\uFE61\uFE63\uFE68\uFE6A\uFE6B\uFF01-\uFF03\uFF05-\uFF0A\uFF0C-\uFF0F\uFF1A\uFF1B\uFF1F\uFF20\uFF3B-\uFF3D\uFF3F\uFF5B\uFF5D\uFF5F-\uFF65]+/u;
class LRUCache {
  constructor(max = 10) {
    __publicField(this, "max");
    __publicField(this, "cache");
    this.max = max;
    this.cache = /* @__PURE__ */ new Map();
  }
  get(key) {
    let item = this.cache.get(key);
    if (item !== void 0) {
      this.cache.delete(key);
      this.cache.set(key, item);
    }
    return item;
  }
  set(key, val) {
    if (this.cache.has(key))
      this.cache.delete(key);
    else if (this.cache.size === this.max)
      this.cache.delete(this.first());
    this.cache.set(key, val);
  }
  first() {
    return this.cache.keys().next().value;
  }
  clear() {
    this.cache.clear();
  }
}
const _withScopeId = (n) => (pushScopeId("data-v-43c4f204"), n = n(), popScopeId(), n);
const _hoisted_1 = ["aria-owns"];
const _hoisted_2 = { class: "shell" };
const _hoisted_3 = ["title"];
const _hoisted_4 = /* @__PURE__ */ _withScopeId(() => /* @__PURE__ */ createBaseVNode("span", {
  "aria-hidden": "true",
  class: "vpi-search search-icon local-search-icon"
}, null, -1));
const _hoisted_5 = [
  _hoisted_4
];
const _hoisted_6 = { class: "search-actions before" };
const _hoisted_7 = ["title"];
const _hoisted_8 = /* @__PURE__ */ _withScopeId(() => /* @__PURE__ */ createBaseVNode("span", { class: "vpi-arrow-left local-search-icon" }, null, -1));
const _hoisted_9 = [
  _hoisted_8
];
const _hoisted_10 = ["placeholder"];
const _hoisted_11 = { class: "search-actions" };
const _hoisted_12 = ["title"];
const _hoisted_13 = /* @__PURE__ */ _withScopeId(() => /* @__PURE__ */ createBaseVNode("span", { class: "vpi-layout-list local-search-icon" }, null, -1));
const _hoisted_14 = [
  _hoisted_13
];
const _hoisted_15 = ["disabled", "title"];
const _hoisted_16 = /* @__PURE__ */ _withScopeId(() => /* @__PURE__ */ createBaseVNode("span", { class: "vpi-delete local-search-icon" }, null, -1));
const _hoisted_17 = [
  _hoisted_16
];
const _hoisted_18 = ["id", "role", "aria-labelledby"];
const _hoisted_19 = ["aria-selected"];
const _hoisted_20 = ["href", "aria-label", "onMouseenter", "onFocusin"];
const _hoisted_21 = { class: "titles" };
const _hoisted_22 = /* @__PURE__ */ _withScopeId(() => /* @__PURE__ */ createBaseVNode("span", { class: "title-icon" }, "#", -1));
const _hoisted_23 = ["innerHTML"];
const _hoisted_24 = /* @__PURE__ */ _withScopeId(() => /* @__PURE__ */ createBaseVNode("span", { class: "vpi-chevron-right local-search-icon" }, null, -1));
const _hoisted_25 = { class: "title main" };
const _hoisted_26 = ["innerHTML"];
const _hoisted_27 = {
  key: 0,
  class: "excerpt-wrapper"
};
const _hoisted_28 = {
  key: 0,
  class: "excerpt",
  inert: ""
};
const _hoisted_29 = ["innerHTML"];
const _hoisted_30 = /* @__PURE__ */ _withScopeId(() => /* @__PURE__ */ createBaseVNode("div", { class: "excerpt-gradient-bottom" }, null, -1));
const _hoisted_31 = /* @__PURE__ */ _withScopeId(() => /* @__PURE__ */ createBaseVNode("div", { class: "excerpt-gradient-top" }, null, -1));
const _hoisted_32 = {
  key: 0,
  class: "no-results"
};
const _hoisted_33 = { class: "search-keyboard-shortcuts" };
const _hoisted_34 = ["aria-label"];
const _hoisted_35 = /* @__PURE__ */ _withScopeId(() => /* @__PURE__ */ createBaseVNode("span", { class: "vpi-arrow-up navigate-icon" }, null, -1));
const _hoisted_36 = [
  _hoisted_35
];
const _hoisted_37 = ["aria-label"];
const _hoisted_38 = /* @__PURE__ */ _withScopeId(() => /* @__PURE__ */ createBaseVNode("span", { class: "vpi-arrow-down navigate-icon" }, null, -1));
const _hoisted_39 = [
  _hoisted_38
];
const _hoisted_40 = ["aria-label"];
const _hoisted_41 = /* @__PURE__ */ _withScopeId(() => /* @__PURE__ */ createBaseVNode("span", { class: "vpi-corner-down-left navigate-icon" }, null, -1));
const _hoisted_42 = [
  _hoisted_41
];
const _hoisted_43 = ["aria-label"];
const _sfc_main = /* @__PURE__ */ defineComponent({
  __name: "VPLocalSearchBox",
  emits: ["close"],
  setup(__props, { emit: __emit }) {
    var _a2, _b;
    const emit = __emit;
    const el = shallowRef();
    const resultsEl = shallowRef();
    const searchIndexData = shallowRef(localSearchIndex);
    const vitePressData = useData();
    const { activate } = useFocusTrap(el, {
      immediate: true,
      allowOutsideClick: true,
      clickOutsideDeactivates: true,
      escapeDeactivates: true
    });
    const { localeIndex, theme } = vitePressData;
    const searchIndex = computedAsync(
      async () => {
        var _a3, _b2, _c, _d, _e, _f, _g, _h, _i;
        return markRaw(
          MiniSearch.loadJSON(
            (_c = await ((_b2 = (_a3 = searchIndexData.value)[localeIndex.value]) == null ? void 0 : _b2.call(_a3))) == null ? void 0 : _c.default,
            {
              fields: ["title", "titles", "text"],
              storeFields: ["title", "titles"],
              searchOptions: {
                fuzzy: 0.2,
                prefix: true,
                boost: { title: 4, text: 2, titles: 1 },
                ...((_d = theme.value.search) == null ? void 0 : _d.provider) === "local" && ((_f = (_e = theme.value.search.options) == null ? void 0 : _e.miniSearch) == null ? void 0 : _f.searchOptions)
              },
              ...((_g = theme.value.search) == null ? void 0 : _g.provider) === "local" && ((_i = (_h = theme.value.search.options) == null ? void 0 : _h.miniSearch) == null ? void 0 : _i.options)
            }
          )
        );
      }
    );
    const disableQueryPersistence = computed(() => {
      var _a3, _b2;
      return ((_a3 = theme.value.search) == null ? void 0 : _a3.provider) === "local" && ((_b2 = theme.value.search.options) == null ? void 0 : _b2.disableQueryPersistence) === true;
    });
    const filterText = disableQueryPersistence.value ? ref("") : useSessionStorage("vitepress:local-search-filter", "");
    const showDetailedList = useLocalStorage(
      "vitepress:local-search-detailed-list",
      ((_a2 = theme.value.search) == null ? void 0 : _a2.provider) === "local" && ((_b = theme.value.search.options) == null ? void 0 : _b.detailedView) === true
    );
    const disableDetailedView = computed(() => {
      var _a3, _b2, _c;
      return ((_a3 = theme.value.search) == null ? void 0 : _a3.provider) === "local" && (((_b2 = theme.value.search.options) == null ? void 0 : _b2.disableDetailedView) === true || ((_c = theme.value.search.options) == null ? void 0 : _c.detailedView) === false);
    });
    const buttonText = computed(() => {
      var _a3, _b2, _c, _d, _e, _f, _g;
      const options = ((_a3 = theme.value.search) == null ? void 0 : _a3.options) ?? theme.value.algolia;
      return ((_e = (_d = (_c = (_b2 = options == null ? void 0 : options.locales) == null ? void 0 : _b2[localeIndex.value]) == null ? void 0 : _c.translations) == null ? void 0 : _d.button) == null ? void 0 : _e.buttonText) || ((_g = (_f = options == null ? void 0 : options.translations) == null ? void 0 : _f.button) == null ? void 0 : _g.buttonText) || "Search";
    });
    watchEffect(() => {
      if (disableDetailedView.value) {
        showDetailedList.value = false;
      }
    });
    const results = shallowRef([]);
    const enableNoResults = ref(false);
    watch(filterText, () => {
      enableNoResults.value = false;
    });
    const mark = computedAsync(async () => {
      if (!resultsEl.value) return;
      return markRaw(new Mark2(resultsEl.value));
    }, null);
    const cache = new LRUCache(16);
    watchDebounced(
      () => [searchIndex.value, filterText.value, showDetailedList.value],
      async ([index, filterTextValue, showDetailedListValue], old, onCleanup) => {
        var _a3, _b2, _c, _d;
        if ((old == null ? void 0 : old[0]) !== index) {
          cache.clear();
        }
        let canceled = false;
        onCleanup(() => {
          canceled = true;
        });
        if (!index) return;
        results.value = index.search(filterTextValue).slice(0, 16);
        enableNoResults.value = true;
        const mods = showDetailedListValue ? await Promise.all(results.value.map((r) => fetchExcerpt(r.id))) : [];
        if (canceled) return;
        for (const { id, mod } of mods) {
          const mapId = id.slice(0, id.indexOf("#"));
          let map = cache.get(mapId);
          if (map) continue;
          map = /* @__PURE__ */ new Map();
          cache.set(mapId, map);
          const comp = mod.default ?? mod;
          if ((comp == null ? void 0 : comp.render) || (comp == null ? void 0 : comp.setup)) {
            const app = createApp(comp);
            app.config.warnHandler = () => {
            };
            app.provide(dataSymbol, vitePressData);
            Object.defineProperties(app.config.globalProperties, {
              $frontmatter: {
                get() {
                  return vitePressData.frontmatter.value;
                }
              },
              $params: {
                get() {
                  return vitePressData.page.value.params;
                }
              }
            });
            const div = document.createElement("div");
            app.mount(div);
            const headings = div.querySelectorAll("h1, h2, h3, h4, h5, h6");
            headings.forEach((el2) => {
              var _a4;
              const href = (_a4 = el2.querySelector("a")) == null ? void 0 : _a4.getAttribute("href");
              const anchor = (href == null ? void 0 : href.startsWith("#")) && href.slice(1);
              if (!anchor) return;
              let html = "";
              while ((el2 = el2.nextElementSibling) && !/^h[1-6]$/i.test(el2.tagName))
                html += el2.outerHTML;
              map.set(anchor, html);
            });
            app.unmount();
          }
          if (canceled) return;
        }
        const terms = /* @__PURE__ */ new Set();
        results.value = results.value.map((r) => {
          const [id, anchor] = r.id.split("#");
          const map = cache.get(id);
          const text = (map == null ? void 0 : map.get(anchor)) ?? "";
          for (const term in r.match) {
            terms.add(term);
          }
          return { ...r, text };
        });
        await nextTick();
        if (canceled) return;
        await new Promise((r) => {
          var _a4;
          (_a4 = mark.value) == null ? void 0 : _a4.unmark({
            done: () => {
              var _a5;
              (_a5 = mark.value) == null ? void 0 : _a5.markRegExp(formMarkRegex(terms), { done: r });
            }
          });
        });
        const excerpts = ((_a3 = el.value) == null ? void 0 : _a3.querySelectorAll(".result .excerpt")) ?? [];
        for (const excerpt of excerpts) {
          (_b2 = excerpt.querySelector('mark[data-markjs="true"]')) == null ? void 0 : _b2.scrollIntoView({ block: "center" });
        }
        (_d = (_c = resultsEl.value) == null ? void 0 : _c.firstElementChild) == null ? void 0 : _d.scrollIntoView({ block: "start" });
      },
      { debounce: 200, immediate: true }
    );
    async function fetchExcerpt(id) {
      const file = pathToFile(id.slice(0, id.indexOf("#")));
      try {
        if (!file) throw new Error(`Cannot find file for id: ${id}`);
        return { id, mod: await import(
          /*@vite-ignore*/
          file
        ) };
      } catch (e) {
        console.error(e);
        return { id, mod: {} };
      }
    }
    const searchInput = ref();
    const disableReset = computed(() => {
      var _a3;
      return ((_a3 = filterText.value) == null ? void 0 : _a3.length) <= 0;
    });
    function focusSearchInput(select = true) {
      var _a3, _b2;
      (_a3 = searchInput.value) == null ? void 0 : _a3.focus();
      select && ((_b2 = searchInput.value) == null ? void 0 : _b2.select());
    }
    onMounted(() => {
      focusSearchInput();
    });
    function onSearchBarClick(event) {
      if (event.pointerType === "mouse") {
        focusSearchInput();
      }
    }
    const selectedIndex = ref(-1);
    const disableMouseOver = ref(false);
    watch(results, (r) => {
      selectedIndex.value = r.length ? 0 : -1;
      scrollToSelectedResult();
    });
    function scrollToSelectedResult() {
      nextTick(() => {
        const selectedEl = document.querySelector(".result.selected");
        if (selectedEl) {
          selectedEl.scrollIntoView({
            block: "nearest"
          });
        }
      });
    }
    onKeyStroke("ArrowUp", (event) => {
      event.preventDefault();
      selectedIndex.value--;
      if (selectedIndex.value < 0) {
        selectedIndex.value = results.value.length - 1;
      }
      disableMouseOver.value = true;
      scrollToSelectedResult();
    });
    onKeyStroke("ArrowDown", (event) => {
      event.preventDefault();
      selectedIndex.value++;
      if (selectedIndex.value >= results.value.length) {
        selectedIndex.value = 0;
      }
      disableMouseOver.value = true;
      scrollToSelectedResult();
    });
    const router = useRouter();
    onKeyStroke("Enter", (e) => {
      if (e.isComposing) return;
      if (e.target instanceof HTMLButtonElement && e.target.type !== "submit")
        return;
      const selectedPackage = results.value[selectedIndex.value];
      if (e.target instanceof HTMLInputElement && !selectedPackage) {
        e.preventDefault();
        return;
      }
      if (selectedPackage) {
        router.go(selectedPackage.id);
        emit("close");
      }
    });
    onKeyStroke("Escape", () => {
      emit("close");
    });
    const defaultTranslations = {
      modal: {
        displayDetails: "Display detailed list",
        resetButtonTitle: "Reset search",
        backButtonTitle: "Close search",
        noResultsText: "No results for",
        footer: {
          selectText: "to select",
          selectKeyAriaLabel: "enter",
          navigateText: "to navigate",
          navigateUpKeyAriaLabel: "up arrow",
          navigateDownKeyAriaLabel: "down arrow",
          closeText: "to close",
          closeKeyAriaLabel: "escape"
        }
      }
    };
    const translate = createSearchTranslate(defaultTranslations);
    onMounted(() => {
      window.history.pushState(null, "", null);
    });
    useEventListener("popstate", (event) => {
      event.preventDefault();
      emit("close");
    });
    const isLocked = useScrollLock(inBrowser ? document.body : null);
    onMounted(() => {
      nextTick(() => {
        isLocked.value = true;
        nextTick().then(() => activate());
      });
    });
    onBeforeUnmount(() => {
      isLocked.value = false;
    });
    function resetSearch() {
      filterText.value = "";
      nextTick().then(() => focusSearchInput(false));
    }
    function formMarkRegex(terms) {
      return new RegExp(
        [...terms].sort((a, b) => b.length - a.length).map((term) => `(${escapeRegExp(term)})`).join("|"),
        "gi"
      );
    }
    return (_ctx, _cache) => {
      var _a3, _b2, _c, _d;
      return openBlock(), createBlock(Teleport, { to: "body" }, [
        createBaseVNode("div", {
          ref_key: "el",
          ref: el,
          role: "button",
          "aria-owns": ((_a3 = results.value) == null ? void 0 : _a3.length) ? "localsearch-list" : void 0,
          "aria-expanded": "true",
          "aria-haspopup": "listbox",
          "aria-labelledby": "localsearch-label",
          class: "VPLocalSearchBox"
        }, [
          createBaseVNode("div", {
            class: "backdrop",
            onClick: _cache[0] || (_cache[0] = ($event) => _ctx.$emit("close"))
          }),
          createBaseVNode("div", _hoisted_2, [
            createBaseVNode("form", {
              class: "search-bar",
              onPointerup: _cache[4] || (_cache[4] = ($event) => onSearchBarClick($event)),
              onSubmit: _cache[5] || (_cache[5] = withModifiers(() => {
              }, ["prevent"]))
            }, [
              createBaseVNode("label", {
                title: buttonText.value,
                id: "localsearch-label",
                for: "localsearch-input"
              }, _hoisted_5, 8, _hoisted_3),
              createBaseVNode("div", _hoisted_6, [
                createBaseVNode("button", {
                  class: "back-button",
                  title: unref(translate)("modal.backButtonTitle"),
                  onClick: _cache[1] || (_cache[1] = ($event) => _ctx.$emit("close"))
                }, _hoisted_9, 8, _hoisted_7)
              ]),
              withDirectives(createBaseVNode("input", {
                ref_key: "searchInput",
                ref: searchInput,
                "onUpdate:modelValue": _cache[2] || (_cache[2] = ($event) => isRef(filterText) ? filterText.value = $event : null),
                placeholder: buttonText.value,
                id: "localsearch-input",
                "aria-labelledby": "localsearch-label",
                class: "search-input"
              }, null, 8, _hoisted_10), [
                [vModelText, unref(filterText)]
              ]),
              createBaseVNode("div", _hoisted_11, [
                !disableDetailedView.value ? (openBlock(), createElementBlock("button", {
                  key: 0,
                  class: normalizeClass(["toggle-layout-button", { "detailed-list": unref(showDetailedList) }]),
                  type: "button",
                  title: unref(translate)("modal.displayDetails"),
                  onClick: _cache[3] || (_cache[3] = ($event) => selectedIndex.value > -1 && (showDetailedList.value = !unref(showDetailedList)))
                }, _hoisted_14, 10, _hoisted_12)) : createCommentVNode("", true),
                createBaseVNode("button", {
                  class: "clear-button",
                  type: "reset",
                  disabled: disableReset.value,
                  title: unref(translate)("modal.resetButtonTitle"),
                  onClick: resetSearch
                }, _hoisted_17, 8, _hoisted_15)
              ])
            ], 32),
            createBaseVNode("ul", {
              ref_key: "resultsEl",
              ref: resultsEl,
              id: ((_b2 = results.value) == null ? void 0 : _b2.length) ? "localsearch-list" : void 0,
              role: ((_c = results.value) == null ? void 0 : _c.length) ? "listbox" : void 0,
              "aria-labelledby": ((_d = results.value) == null ? void 0 : _d.length) ? "localsearch-label" : void 0,
              class: "results",
              onMousemove: _cache[7] || (_cache[7] = ($event) => disableMouseOver.value = false)
            }, [
              (openBlock(true), createElementBlock(Fragment, null, renderList(results.value, (p, index) => {
                return openBlock(), createElementBlock("li", {
                  key: p.id,
                  role: "option",
                  "aria-selected": selectedIndex.value === index ? "true" : "false"
                }, [
                  createBaseVNode("a", {
                    href: p.id,
                    class: normalizeClass(["result", {
                      selected: selectedIndex.value === index
                    }]),
                    "aria-label": [...p.titles, p.title].join(" > "),
                    onMouseenter: ($event) => !disableMouseOver.value && (selectedIndex.value = index),
                    onFocusin: ($event) => selectedIndex.value = index,
                    onClick: _cache[6] || (_cache[6] = ($event) => _ctx.$emit("close"))
                  }, [
                    createBaseVNode("div", null, [
                      createBaseVNode("div", _hoisted_21, [
                        _hoisted_22,
                        (openBlock(true), createElementBlock(Fragment, null, renderList(p.titles, (t, index2) => {
                          return openBlock(), createElementBlock("span", {
                            key: index2,
                            class: "title"
                          }, [
                            createBaseVNode("span", {
                              class: "text",
                              innerHTML: t
                            }, null, 8, _hoisted_23),
                            _hoisted_24
                          ]);
                        }), 128)),
                        createBaseVNode("span", _hoisted_25, [
                          createBaseVNode("span", {
                            class: "text",
                            innerHTML: p.title
                          }, null, 8, _hoisted_26)
                        ])
                      ]),
                      unref(showDetailedList) ? (openBlock(), createElementBlock("div", _hoisted_27, [
                        p.text ? (openBlock(), createElementBlock("div", _hoisted_28, [
                          createBaseVNode("div", {
                            class: "vp-doc",
                            innerHTML: p.text
                          }, null, 8, _hoisted_29)
                        ])) : createCommentVNode("", true),
                        _hoisted_30,
                        _hoisted_31
                      ])) : createCommentVNode("", true)
                    ])
                  ], 42, _hoisted_20)
                ], 8, _hoisted_19);
              }), 128)),
              unref(filterText) && !results.value.length && enableNoResults.value ? (openBlock(), createElementBlock("li", _hoisted_32, [
                createTextVNode(toDisplayString(unref(translate)("modal.noResultsText")) + ' "', 1),
                createBaseVNode("strong", null, toDisplayString(unref(filterText)), 1),
                createTextVNode('" ')
              ])) : createCommentVNode("", true)
            ], 40, _hoisted_18),
            createBaseVNode("div", _hoisted_33, [
              createBaseVNode("span", null, [
                createBaseVNode("kbd", {
                  "aria-label": unref(translate)("modal.footer.navigateUpKeyAriaLabel")
                }, _hoisted_36, 8, _hoisted_34),
                createBaseVNode("kbd", {
                  "aria-label": unref(translate)("modal.footer.navigateDownKeyAriaLabel")
                }, _hoisted_39, 8, _hoisted_37),
                createTextVNode(" " + toDisplayString(unref(translate)("modal.footer.navigateText")), 1)
              ]),
              createBaseVNode("span", null, [
                createBaseVNode("kbd", {
                  "aria-label": unref(translate)("modal.footer.selectKeyAriaLabel")
                }, _hoisted_42, 8, _hoisted_40),
                createTextVNode(" " + toDisplayString(unref(translate)("modal.footer.selectText")), 1)
              ]),
              createBaseVNode("span", null, [
                createBaseVNode("kbd", {
                  "aria-label": unref(translate)("modal.footer.closeKeyAriaLabel")
                }, "esc", 8, _hoisted_43),
                createTextVNode(" " + toDisplayString(unref(translate)("modal.footer.closeText")), 1)
              ])
            ])
          ])
        ], 8, _hoisted_1)
      ]);
    };
  }
});
const VPLocalSearchBox = /* @__PURE__ */ _export_sfc(_sfc_main, [["__scopeId", "data-v-43c4f204"]]);
export {
  VPLocalSearchBox as default
};
