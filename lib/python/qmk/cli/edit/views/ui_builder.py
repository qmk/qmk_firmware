"""UI layout builder for the field list view.

Creates asciimatics Layout, Label, Text, and Button widgets and
adds them to a Frame. Receives callback factories from the Frame
so it can attach click handlers without knowing about navigation
or rebuild logic.
"""
from asciimatics.widgets import Layout, Label, Text, Button

from qmk.cli.edit.widgets import ObjectRow, ArrayRow, ArrayItemRow


class UIBuilder:
    """Builds all UI layouts and widgets for FieldListView.

    Args:
        ctx
            ViewContext instance providing state, keyboard, and registry.

        search_controller
            SearchController instance for search state and filtering.
    """
    def __init__(self, ctx, search_controller):
        self._ctx = ctx
        self._search = search_controller

    def build(self, frame, on_navigate, on_add_click, status_display):
        """Rebuild all layouts on the frame.

        This is the main entry point. It:
        1. Creates header layout with breadcrumb (add to frame).
        2. If search is active, creates search bar layout.
        3. Adds blank label separator.
        4. Creates fill-frame field layout.
        5. Builds field list (object or array mode).
        6. Creates footer layout with keybinding hints.
        7. Returns the all_fields list.

        Args:
            frame
                The asciimatics Frame to populate with layouts.

            on_navigate
                Callable(key) -> Callable. Factory that creates click
                handlers for object/array row navigation.

            on_add_click
                No-arg callable for the array "Add" button.

            status_display
                StatusDisplay instance for footer text generation.

        Returns:
            List of FieldWidget instances that were added.
        """
        header_layout = Layout([100], fill_frame=False)
        frame.add_layout(header_layout)
        header_layout.add_widget(Label(self.build_breadcrumb()))

        self._build_search_bar(frame)

        header_layout.add_widget(Label(""))

        field_layout = Layout([100], fill_frame=True)
        frame.add_layout(field_layout)

        all_fields = self._build_field_list(
            frame,
            field_layout,
            on_navigate,
            on_add_click,
        )

        self._build_footer_layout(frame, status_display)

        return all_fields

    def build_breadcrumb(self):
        """Build breadcrumb navigation string.

        Builds "QMK Edit: keyboards/{keyboard}" + path segments
        joined by " > " + optional " [Modified]" suffix.

        Returns:
            Breadcrumb string showing current navigation path.
        """
        parts = ["QMK Edit: keyboards/%s" % self._ctx.keyboard]

        current_path = self._ctx.state.current_path
        if current_path:
            parts.append(" > ")
            formatted = []
            for segment in current_path:
                if isinstance(segment, int):
                    formatted.append("[%d]" % segment)
                else:
                    formatted.append(segment)
            parts.append(" > ".join(formatted))

        if self._ctx.state.is_modified:
            parts.append(" [Modified]")

        return "".join(parts)

    def _build_search_bar(self, frame):
        """Add search bar layout when search is active.

        Creates a Layout with a Text widget labeled "Search: ",
        sets its value to search_controller.search_term, and sets
        search_controller.search_widget to the Text widget.
        """
        if not self._search.is_active:
            return

        search_layout = Layout([100], fill_frame=False)
        frame.add_layout(search_layout)
        search_widget = Text(label="Search: ", name="search")
        search_widget.value = self._search.search_term
        search_layout.add_widget(search_widget)
        self._search.search_widget = search_widget

    def _build_field_list(self, frame, layout, on_navigate, on_add_click):
        """Build the field list widgets into the given layout.

        Determines array_mode from ctx.state.is_current_level_array().
        If array mode, calls _build_array_list.
        Else, calls _build_object_list.
        If no fields were added and search term exists, adds
        "No matching fields" label.

        Returns:
            List of FieldWidget instances added.
        """
        array_mode = self._ctx.state.is_current_level_array()

        if array_mode:
            all_fields = self._build_array_list(
                layout,
                on_navigate,
                on_add_click,
            )
        else:
            all_fields = self._build_object_list(layout, on_navigate)

        if not all_fields and self._search.search_term:
            layout.add_widget(Label("No matching fields"))

        return all_fields

    def _build_object_list(self, layout, on_navigate):
        """Build field list for object mode.

        Gets properties from ctx.state.get_current_schema() and
        property_order from schema_loader.get_property_order().
        Iterates properties in order, filtering by search term.
        Creates widgets via ctx.registry.create_widget().
        For ObjectRow/ArrayRow widgets, injects on_navigate callback
        before creating the asciimatics widget.

        Returns:
            List of FieldWidget instances added.
        """
        all_fields = []
        properties = self._ctx.state.get_current_schema()
        property_order = self._ctx.state.schema_loader.get_property_order(
            self._ctx.state.current_path,
        )

        for prop_name in property_order:
            if prop_name not in properties:
                continue

            if not self._search.matches(prop_name):
                continue

            prop_schema = properties[prop_name]
            path = self._build_path(prop_name)

            widget = self._ctx.registry.create_widget(
                prop_name,
                prop_schema,
                self._ctx.state,
                path,
            )
            all_fields.append(widget)

            if isinstance(widget, (ObjectRow, ArrayRow)):
                widget.set_on_navigate(on_navigate(prop_name))

            asciimatics_widget = widget.as_asciimatics_widget()
            layout.add_widget(asciimatics_widget)

        return all_fields

    def _build_array_list(self, layout, on_navigate, on_add_click):
        """Build field list for array mode.

        Checks _is_layouts_array() exclusion.
        Gets array_length and item_schema.
        For empty arrays, shows "(empty array)" label.
        Creates ArrayItemRow widgets for each index.
        Injects navigate callback for object items before widget creation.
        Calls _add_new_item_row for add button.

        Returns:
            List of FieldWidget instances added.
        """
        all_fields = []

        if self._is_layouts_array():
            layout.add_widget(Label("Layout editing not yet supported"))
            return all_fields

        array_length = self._ctx.state.get_current_array_length()
        if array_length is None:
            return all_fields

        item_schema = self._ctx.state.schema_loader.get_items_schema(
            self._ctx.state.current_path,
        )
        if item_schema is None:
            return all_fields

        if array_length == 0:
            layout.add_widget(Label("(empty array)"))
        else:
            for index in range(array_length):
                path = self._build_path(index)
                widget = ArrayItemRow(index, item_schema, self._ctx.state, path)
                all_fields.append(widget)

                if item_schema.get('type') == 'object':
                    widget.set_on_navigate(on_navigate(index))

                asciimatics_widget = widget.as_asciimatics_widget()
                layout.add_widget(asciimatics_widget)

        self._add_new_item_row(layout, on_add_click)

        return all_fields

    def _is_layouts_array(self):
        """Check if current path is a layouts array.

        Returns True if path has >= 3 segments and
        path[0] == 'layouts' and path[2] == 'layout'.

        Returns:
            True if this is a layouts array that should not be edited.
        """
        path = self._ctx.state.current_path
        if not path or len(path) < 3:
            return False

        return path[0] == 'layouts' and path[2] == 'layout'

    def _add_new_item_row(self, layout, on_add_click):
        """Add the 'Add new item' button row for arrays.

        Checks _is_at_max_items(). If at max, shows label.
        Otherwise creates Button with on_add_click handler.
        """
        if self._is_at_max_items():
            layout.add_widget(Label("(maximum items reached)"))
            return

        add_button = Button(
            text="[+] Add new item",
            on_click=on_add_click,
            name="add_item",
        )
        layout.add_widget(add_button)

    def _is_at_max_items(self):
        """Check if array has reached maxItems limit.

        Gets parent schema, finds maxItems constraint,
        compares to current array length.

        Returns:
            True if at or above maxItems limit, False otherwise.
        """
        current_path = self._ctx.state.current_path
        if not current_path:
            return False

        parent_path = current_path[:-1] if len(current_path) > 1 else None
        parent_schema = self._ctx.state.schema_loader.get_properties(parent_path)
        array_name = current_path[-1]

        if not parent_schema or array_name not in parent_schema:
            return False

        max_items = parent_schema[array_name].get('maxItems')
        if max_items is None:
            return False

        current_length = self._ctx.state.get_current_array_length()
        return current_length is not None and current_length >= max_items

    def _build_footer_layout(self, frame, status_display):
        """Add footer layout with help shortcut and optional hint.

        Creates a Layout, adds blank label, adds footer text from
        status_display.get_footer_text(). No hint is passed during
        initial build -- hints are injected later via update_footer_widget.
        """
        footer_layout = Layout([100], fill_frame=False)
        frame.add_layout(footer_layout)

        footer_layout.add_widget(Label(""))
        footer_text = status_display.get_footer_text()
        footer_layout.add_widget(Label(footer_text))

    def _build_path(self, prop_name):
        """Build full tuple path for a property.

        Appends prop_name to current_path tuple.

        Args:
            prop_name
                Property name string or integer index.

        Returns:
            Tuple path, e.g. ('usb', 'vid').
        """
        return self._ctx.state.current_path + (prop_name,)
