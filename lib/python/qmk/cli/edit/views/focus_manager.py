"""Focus management collaborator for FieldListView.

Encapsulates focus querying (which field is focused, what array index)
and manipulation (move focus to a specific field or array index). The
FocusManager is updated after each UI rebuild with the fresh widget list
and frame reference.
"""
from qmk.cli.edit.widgets import ArrayItemRow
from qmk.cli.edit.views.frame_helper import FrameHelper


class FocusManager:
    """Manages widget focus state for FieldListView.

    This collaborator requires a Frame reference because switch_focus is
    a Frame method. The frame reference is passed via update() after each
    rebuild rather than in __init__, keeping the constructor simple for
    testing.
    """
    def __init__(self):
        """Initialize focus manager with empty state.
        """
        self._frame = None
        self._all_fields = []

    def update(self, frame, all_fields, frame_helper=None):
        """Called after each rebuild with fresh widget list.

        Stores the frame reference and the all_fields list for
        subsequent focus queries and manipulations. Accepts an
        optional FrameHelper; creates one if not provided.

        Args:
            frame
                The asciimatics Frame instance.

            all_fields
                List of FieldWidget instances currently displayed.

            frame_helper
                Optional FrameHelper instance. If None, creates
                a new one wrapping the given frame.
        """
        self._frame = frame
        self._all_fields = all_fields
        self._frame_helper = frame_helper if frame_helper is not None else FrameHelper(frame)

    def focused_field_name(self):
        """Return name of currently focused field, or None.

        Gets the frame's focussed_widget (British spelling per asciimatics),
        iterates _all_fields to find the FieldWidget whose asciimatics_widget
        matches the focused asciimatics widget.

        Returns:
            String name of focused field, or None if no match found.
        """
        widget = self.get_focused_field_widget()
        return widget.name if widget else None

    def focused_array_index(self):
        """Return index of focused array item, or None.

        Checks the frame's _has_focus flag first. If the frame does not
        have focus, returns None. Otherwise finds the focused FieldWidget
        and returns its index if it is an ArrayItemRow instance.

        Returns:
            Integer index of focused array item, or None.
        """
        # Guard added for standalone usage where _frame may be None.
        if self._frame is None or not self._frame_helper.has_focus():
            return None

        widget = self.get_focused_field_widget()
        if isinstance(widget, ArrayItemRow):
            return widget.index
        return None

    def focus_on_array_index(self, index):
        """Move focus to array item at the given index.

        Guards against out-of-bounds indices and missing widget references
        before delegating to _find_and_focus_widget.

        Args:
            index
                Array index to focus on.
        """
        if index < 0 or index >= len(self._all_fields):
            return

        target_widget = self._all_fields[index]
        if target_widget.asciimatics_widget is None:
            return

        self._find_and_focus_widget(target_widget.asciimatics_widget)

    def focus_on_field_by_name(self, name):
        """Move focus to the field matching the given property name.

        Iterates _all_fields to find a widget with a matching name
        property. Guards against missing widget references before
        delegating to _find_and_focus_widget.

        Args:
            name
                Property name to focus on.
        """
        for widget in self._all_fields:
            if widget.name != name:
                continue
            if widget.asciimatics_widget is None:
                return
            self._find_and_focus_widget(widget.asciimatics_widget)
            return

    def _find_and_focus_widget(self, asciimatics_widget):
        """Find the fill-frame layout containing the widget and switch focus.

        Uses FrameHelper to find the layout with fill_frame == True,
        then scans the first column of that layout to find the widget
        index, and calls switch_focus on the frame.

        Args:
            asciimatics_widget
                The asciimatics widget to focus on.
        """
        field_layout = self._frame_helper.find_fill_frame_layout()

        if field_layout is None:
            return

        column = self._frame_helper.get_layout_column_widgets(field_layout, 0)
        for widget_index, col_widget in enumerate(column):
            if col_widget is asciimatics_widget:
                self._frame.switch_focus(field_layout, 0, widget_index)
                return

    def get_focused_field_widget(self):
        """Return the FieldWidget matching the currently focused asciimatics widget.

        Returns:
            FieldWidget instance, or None if no field is focused.
        """
        if self._frame is None:
            return None

        focused_widget = self._frame.focussed_widget
        if focused_widget is None:
            return None

        for widget in self._all_fields:
            if widget.asciimatics_widget is not None and widget.asciimatics_widget is focused_widget:
                return widget
        return None
