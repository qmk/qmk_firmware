#!/usr/bin/env python3
"""Render the Callum keymap for the Aurora Sweep as an SVG diagram."""

from __future__ import annotations

import json
from pathlib import Path
from typing import Dict, List, Tuple

ROOT = Path(__file__).resolve().parents[1]
KEYMAP_PATH = ROOT / "callum.json"
KEYBOARD_JSON_PATH = ROOT / "keyboards" / "splitkb" / "aurora" / "sweep" / "rev1" / "keyboard.json"
OUTPUT_PATH = ROOT / "callum_layout.svg"
LAYOUT_KEY = "LAYOUT_split_3x5_2"

# Descriptive names for layers in the order they appear in the keymap
LAYER_DISPLAY_NAMES = [
    "Default",
    "Symbols",
    "Navigation",
    "Numbers",
    "Function",
]
LAYER_NAME_FALLBACK = {
    "DEF": "Default",
    "SYM": "Symbols",
    "NAV": "Navigation",
    "NUM": "Numbers",
    "FKEYS": "Function",
}

UNIT = 70.0                # spacing between key columns/rows
default_key_w = 56.0
default_key_h = 56.0
corner_radius = 9.0
margin_x = 90.0
margin_top = 110.0
layer_section_extra = 110.0
legend_margin_top = 60.0
legend_line_height = 22.0
margin_bottom = 70.0
font_family = "Inter, 'Helvetica Neue', Arial, sans-serif"

legend_notes: List[str] = []
legend_seen = set()


def add_note(note: str) -> None:
    if not note:
        return
    if note not in legend_seen:
        legend_seen.add(note)
        legend_notes.append(note)


SPECIAL_SYMBOLS: Dict[str, str] = {
    "KC_EXLM": "!",
    "KC_AT": "@",
    "KC_HASH": "#",
    "KC_DLR": "$",
    "KC_PERC": "%",
    "KC_CIRC": "^",
    "KC_AMPR": "&",
    "KC_ASTR": "*",
    "KC_LPRN": "(",
    "KC_RPRN": ")",
    "KC_MINS": "-",
    "KC_UNDS": "_",
    "KC_EQL": "=",
    "KC_PLUS": "+",
    "KC_LBRC": "[",
    "KC_RBRC": "]",
    "KC_LCBR": "{",
    "KC_RCBR": "}",
    "KC_BSLS": "\\",
    "KC_SLSH": "/",
    "KC_QUOT": "'",
    "KC_GRV": "`",
    "KC_COMM": ",",
    "KC_DOT": ".",
    "KC_SCLN": ";",
    "KC_COLN": ":",
    "KC_AM": "&",
    "KC_PIPE": "|",
}

ARROWS = {
    "KC_LEFT": "←",
    "KC_RGHT": "→",
    "KC_UP": "↑",
    "KC_DOWN": "↓",
}

WORDY = {
    "KC_ESC": "Esc",
    "KC_TAB": "Tab",
    "KC_ENT": "Enter",
    "KC_SPC": "Space",
    "KC_DEL": "Delete",
    "KC_BSPC": "Backspace",
}


ComboDef = Dict[str, object]

COMBOS: List[ComboDef] = [
    {
        "keys": ["KC_W", "KC_F"],
        "result": "KC_ESC",
        "description": "Combo: press W + F together → Esc",
    },
]


class LayoutPoint:
    __slots__ = ("index", "x", "y", "w", "h")

    def __init__(self, index: int, data: Dict[str, object]) -> None:
        self.index = index
        self.x = float(data.get("x", 0))
        self.y = float(data.get("y", 0))
        self.w = float(data.get("w", 1))
        self.h = float(data.get("h", 1))


class KeyRender:
    __slots__ = ("lines", "fill", "text_color", "note")

    def __init__(self, lines: List[str], fill: str = "#f8f9fa", text_color: str = "#202124", note: str | None = None) -> None:
        self.lines = lines
        self.fill = fill
        self.text_color = text_color
        self.note = note


def friendly_layer_name(token: str) -> str:
    return LAYER_NAME_FALLBACK.get(token, token.capitalize())


def friendly_symbol(code: str) -> str:
    if code in SPECIAL_SYMBOLS:
        return SPECIAL_SYMBOLS[code]
    if code in ARROWS:
        return ARROWS[code]
    if code in WORDY:
        return WORDY[code]
    if code.startswith("KC_"):
        suffix = code[3:]
        if suffix.startswith("F") and suffix[1:].isdigit():
            return suffix
        if len(suffix) == 1 and suffix.isalpha():
            return suffix.upper()
        if suffix.isdigit():
            return suffix
    return code


def render_info(code: str) -> KeyRender:
    code = code.strip()

    if code == "KC_TRNS":
        note = "Transparent key: inherits from the layer below."
        add_note(note)
        return KeyRender([""], fill="#f2f3f5", text_color="#9aa0a6", note=note)

    if code == "KC_NO":
        note = "Empty slot (KC_NO): no keycode is sent."
        add_note(note)
        return KeyRender(["—"], fill="#f2f3f5", text_color="#c0c4c9", note=note)

    if code.startswith("LT(") and code.endswith(")"):
        inner = code[3:-1]
        layer_token, keycode = [part.strip() for part in inner.split(",", 1)]
        tap_label = friendly_symbol(keycode)
        layer_label = friendly_layer_name(layer_token)
        note = f"Layer-tap: tap for {tap_label}, hold for the {layer_label} layer."
        add_note("Layer-tap keys: tap for the printed key, hold for the noted layer.")
        return KeyRender([tap_label, f"hold→{layer_label}"], fill="#e6f2ff", text_color="#1a73e8", note=note)

    if code.startswith("TD("):
        detail = "Tap-dance thumb key: tap → Tab, hold → Numbers layer, double tap/hold → Function layer."
        add_note(detail)
        return KeyRender(["Tap:Tab", "Hold→Num", "2×→Fn"], fill="#fff3cd", text_color="#b06d00")

    if code.startswith("OS_"):
        mod = code.split("_", 1)[1].capitalize()
        add_note("OS_* keys are one-shot modifiers: tap to arm the modifier for the next key press.")
        return KeyRender(["One-shot", mod], fill="#e8f5e9", text_color="#0b8043")

    if code == "LA_SYM":
        note = "LA_SYM is MO(SYM): hold to momentarily access the Symbols layer."
        add_note(note)
        return KeyRender(["Hold→Sym"], fill="#d9f2ff", text_color="#0b5394", note=note)

    if code == "SW_WIN":
        note = "SW_WIN: macOS Cmd+Tab window switcher (via swapper helper)."
        add_note(note)
        return KeyRender(["Win", "switch"], fill="#f8f9fa")

    if code == "SW_LANG":
        note = "SW_LANG: Control+Space input source switcher."
        add_note(note)
        return KeyRender(["Lang", "switch"], fill="#f8f9fa")

    if code in {"BACK", "FWD", "HOME", "END", "TAB_L", "TAB_R"}:
        add_note("Navigation macros (BACK/FWD/HOME/END/TAB_L/TAB_R) send the shortcuts defined in config.h.")
        labels = {
            "BACK": "Back",
            "FWD": "Forward",
            "HOME": "Home",
            "END": "End",
            "TAB_L": "Tab←",
            "TAB_R": "Tab→",
        }
        return KeyRender([labels[code]])

    if code in {"UNDO", "REDO"}:
        add_note("UNDO / REDO send Cmd+Z and Cmd+Shift+Z respectively.")
        label = "Undo" if code == "UNDO" else "Redo"
        return KeyRender([label])

    if code == "QK_BOOT":
        return KeyRender(["Reset"], fill="#fdecea", text_color="#c5221f", note="QK_BOOT: hold to jump to the bootloader.")

    if code == "KC_ENT":
        return KeyRender(["Enter"])

    if code == "KC_TAB":
        return KeyRender(["Tab"])

    if code == "KC_ESC":
        return KeyRender(["Esc"])

    if code == "KC_DEL":
        return KeyRender(["Delete"])

    if code == "KC_CAPS":
        return KeyRender(["Caps"])

    if code == "KC_MPLY":
        return KeyRender(["Play", "pause"])

    if code == "KC_PGDN":
        return KeyRender(["PgDn"])

    if code == "KC_PGUP":
        return KeyRender(["PgUp"])

    if code == "KC_VOLD":
        return KeyRender(["Vol↓"])

    if code == "KC_VOLU":
        return KeyRender(["Vol↑"])

    if code == "KC_RGHT":
        return KeyRender([ARROWS[code]])

    if code == "KC_LEFT":
        return KeyRender([ARROWS[code]])

    if code == "KC_UP":
        return KeyRender([ARROWS[code]])

    if code == "KC_DOWN":
        return KeyRender([ARROWS[code]])

    if code == "KC_BSPC":
        return KeyRender(["Back", "space"])

    if code.startswith("KC_"):
        label = friendly_symbol(code)
        if label != code:
            return KeyRender([label])

    return KeyRender([code])


def convert() -> None:
    if not KEYMAP_PATH.exists():
        raise SystemExit(f"Keymap JSON not found: {KEYMAP_PATH}")
    keymap = json.loads(KEYMAP_PATH.read_text())
    layout_data = json.loads(KEYBOARD_JSON_PATH.read_text())
    layout_entries = layout_data["layouts"][LAYOUT_KEY]["layout"]

    points = [LayoutPoint(i, entry) for i, entry in enumerate(layout_entries)]
    key_count = len(points)
    layers: List[List[str]] = keymap.get("layers", [])
    if not layers:
        raise SystemExit("No layers found in keymap JSON")
    if any(len(layer) != key_count for layer in layers):
        raise SystemExit("Layer key count does not match layout definition")

    max_x = max(p.x + p.w for p in points)
    max_y = max(p.y + p.h for p in points)

    layer_section_height = max_y * UNIT + default_key_h + layer_section_extra

    combo_indices: List[Tuple[List[int], ComboDef]] = []
    base_layer = layers[0]
    for combo in COMBOS:
        indices = []
        for keycode in combo["keys"]:
            try:
                indices.append(base_layer.index(keycode))
            except ValueError as exc:
                raise SystemExit(f"Combo key {keycode} not found in base layer") from exc
        combo_indices.append((indices, combo))
        add_note(combo["description"])

    combo_key_indices = {idx for indices, _ in combo_indices for idx in indices}

    width = margin_x * 2 + max_x * UNIT + default_key_w

    svg_layers: List[str] = []

    for layer_idx, keys in enumerate(layers):
        layer_name = LAYER_DISPLAY_NAMES[layer_idx] if layer_idx < len(LAYER_DISPLAY_NAMES) else f"Layer {layer_idx}"
        origin_y = margin_top + layer_idx * layer_section_height
        heading_y = origin_y - 26
        svg_layers.append(
            f'<text x="{margin_x:.1f}" y="{heading_y:.1f}" font-size="20" font-weight="600" '
            f'fill="#202124" font-family="{font_family}">Layer {layer_idx + 1}: {layer_name}</text>'
        )
        for idx, code in enumerate(keys):
            point = points[idx]
            x = margin_x + point.x * UNIT + (UNIT - default_key_w) / 2.0
            y = origin_y + point.y * UNIT + (UNIT - default_key_h) / 2.0
            width_px = default_key_w + (point.w - 1) * UNIT
            height_px = default_key_h + (point.h - 1) * UNIT
            info = render_info(code)
            if info.note:
                add_note(info.note)
            fill = info.fill
            stroke = "#5f6368"
            if layer_idx == 0 and idx in combo_key_indices:
                fill = "#ffe0b2"
                stroke = "#f57c00"
            svg_layers.append(
                f'<rect x="{x:.1f}" y="{y:.1f}" width="{width_px:.1f}" height="{height_px:.1f}" '
                f'rx="{corner_radius}" ry="{corner_radius}" fill="{fill}" stroke="{stroke}" stroke-width="1"/>'
            )
            lines = [line for line in info.lines if line]
            if lines:
                center_x = x + width_px / 2.0
                center_y = y + height_px / 2.0
                line_gap = 16.0
                total_height = line_gap * (len(lines) - 1)
                start_y = center_y - total_height / 2.0
                for line_idx, text_line in enumerate(lines):
                    text_y = start_y + line_idx * line_gap
                    svg_layers.append(
                        f'<text x="{center_x:.1f}" y="{text_y:.1f}" font-size="14" fill="{info.text_color}" '
                        f'font-family="{font_family}" text-anchor="middle" dominant-baseline="middle">{text_line}</text>'
                    )

    svg_combos: List[str] = []
    for indices, combo in combo_indices:
        origin_y = margin_top + 0 * layer_section_height
        centers = []
        for idx in indices:
            point = points[idx]
            x = margin_x + point.x * UNIT + (UNIT - default_key_w) / 2.0 + default_key_w / 2.0
            y = origin_y + point.y * UNIT + (UNIT - default_key_h) / 2.0 + default_key_h / 2.0
            centers.append((x, y))
        if len(centers) == 2:
            (x1, y1), (x2, y2) = centers
            svg_combos.append(
                f'<line x1="{x1:.1f}" y1="{y1:.1f}" x2="{x2:.1f}" y2="{y2:.1f}" '
                f'stroke="#f57c00" stroke-width="3" stroke-linecap="round" stroke-dasharray="6 6"/>'
            )
            label_x = (x1 + x2) / 2.0
            label_y = min(y1, y2) - 24.0
            result_text = friendly_symbol(combo["result"])
            svg_combos.append(
                f'<text x="{label_x:.1f}" y="{label_y:.1f}" font-size="14" font-weight="600" '
                f'fill="#f57c00" font-family="{font_family}" text-anchor="middle">{result_text}</text>'
            )
        add_note(combo["description"])

    legend_start_y = margin_top + len(layers) * layer_section_height + legend_margin_top

    height = legend_start_y + legend_line_height * max(len(legend_notes), 1) + margin_bottom

    svg_parts: List[str] = [
        f'<svg xmlns="http://www.w3.org/2000/svg" width="{width:.0f}" height="{height:.0f}" '
        f'viewBox="0 0 {width:.0f} {height:.0f}" role="img">',
        f'<rect width="100%" height="100%" fill="#ffffff"/>',
        f'<text x="{width / 2:.1f}" y="{margin_top - 60:.1f}" font-size="26" font-weight="700" '
        f'fill="#202124" font-family="{font_family}" text-anchor="middle">Callum Keymap – Aurora Sweep</text>',
        f'<text x="{width / 2:.1f}" y="{margin_top - 30:.1f}" font-size="16" '
        f'fill="#5f6368" font-family="{font_family}" text-anchor="middle">Layers and combo overview</text>',
    ]

    svg_parts.extend(svg_combos)
    svg_parts.extend(svg_layers)

    if legend_notes:
        svg_parts.append(
            f'<text x="{margin_x:.1f}" y="{legend_start_y - 24:.1f}" font-size="20" font-weight="600" '
            f'fill="#202124" font-family="{font_family}">Notes</text>'
        )
        for idx, note in enumerate(legend_notes):
            y = legend_start_y + idx * legend_line_height
            svg_parts.append(
                f'<text x="{margin_x:.1f}" y="{y:.1f}" font-size="15" fill="#3c4043" '
                f'font-family="{font_family}">• {note}</text>'
            )

    svg_parts.append('</svg>')

    OUTPUT_PATH.write_text("\n".join(svg_parts))
    print(f"SVG written to {OUTPUT_PATH}")


if __name__ == "__main__":
    convert()
