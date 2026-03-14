"""Abstraction layer for asciimatics private attribute access.

Centralizes all access to asciimatics internal/private attributes
(`_layouts`, `_focus`, `_has_focus`, `_columns`) into a single module.
This confines the coupling to asciimatics internals so that if the
library changes its private API, only this file needs to be updated.

Public asciimatics APIs (`Label.text`, `Layout.fill_frame`,
`Frame.focussed_widget`, `Frame.switch_focus`) are used directly
by consumers and do not need wrapping here.
"""


class FrameHelper:
    """Wraps asciimatics Frame private attribute access.

    All methods that touch `frame._layouts`, `frame._focus`,
    `frame._has_focus`, or `layout._columns` live here. Consumers
    call these methods instead of reaching into private attributes.

    Args:
        frame
            The asciimatics Frame instance to wrap.
    """
    def __init__(self, frame):
        """Store the frame reference.
        """
        self._frame = frame

    def clear_layouts(self):
        """Remove all layouts from the frame.

        Wraps `frame._layouts` (private list). Pops all items
        in a while loop so asciimatics sees an empty list rather
        than a replaced reference.
        """
        while self._frame._layouts:
            self._frame._layouts.pop()

    def reset_focus_index(self):
        """Reset the frame's internal focus counter to zero.

        Wraps `frame._focus` (private int). This must be reset
        after clearing layouts to avoid stale focus indices.
        """
        self._frame._focus = 0

    def has_focus(self):
        """Return whether the frame currently has focus.

        Wraps `frame._has_focus` (private bool). Used by
        FocusManager to guard focus queries.
        """
        return self._frame._has_focus

    def set_has_focus(self, value):
        """Set the frame's focus ownership flag.

        Wraps ``frame._has_focus`` (private bool). Called during
        UI rebuilds to restore focus ownership after a modal dialog
        has blurred the frame, ensuring ``fix()`` resolves focus to
        a layout with live widgets.
        """
        self._frame._has_focus = value

    def find_fill_frame_layout(self):
        """Return the layout with fill_frame=True, or None.

        Iterates `frame._layouts` (private list) and checks each
        layout's `fill_frame` public property. Returns the first
        match or None if no layout fills the frame.
        """
        for layout in self._frame._layouts:
            if layout.fill_frame:
                return layout
        return None

    def get_layout_column_widgets(self, layout, column=0):
        """Return the widget list for a layout column.

        Wraps `layout._columns` (private list of lists). Returns
        an empty list if the column index is out of range.

        Args:
            layout
                The asciimatics Layout instance.

            column
                Column index within the layout. Defaults to 0.
        """
        if column < 0 or column >= len(layout._columns):
            return []
        return layout._columns[column]

    def get_layout_by_index(self, index):
        """Return a layout by index, or None if out of range.

        Wraps `frame._layouts` (private list) with bounds checking.
        Supports negative indices (e.g. -1 for last layout).

        Args:
            index
                Integer index into the layouts list.
        """
        layouts = self._frame._layouts
        try:
            return layouts[index]
        except IndexError:
            return None

    def get_layout_count(self):
        """Return the number of layouts in the frame.

        Wraps `len(frame._layouts)` (private list).
        """
        return len(self._frame._layouts)

    def update_label_text(self, label_widget, new_text):
        """Set a label widget's text to a new value.

        Uses the public `Label.text` property (available in
        asciimatics 1.15.0+). This replaces direct access to
        the private `_text` attribute.

        Args:
            label_widget
                The asciimatics Label widget to update.

            new_text
                The new text string to display.
        """
        label_widget.text = new_text

    def get_label_text(self, label_widget):
        """Return a label widget's current text.

        Uses the public `Label.text` property (available in
        asciimatics 1.15.0+). This replaces direct access to
        the private `_text` attribute.

        Args:
            label_widget
                The asciimatics Label widget to read.

        Returns:
            The label's current text string.
        """
        return label_widget.text
