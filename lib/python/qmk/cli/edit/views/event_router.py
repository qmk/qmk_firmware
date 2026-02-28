"""Event routing for keyboard events in the field list view.

Routes KeyboardEvent objects to the correct handler based on the
current editor mode (search, array, or normal). Does not import
from asciimatics; receives events and delegates.
"""


class EventRouter:
    """Routes keyboard events to the appropriate handler.

    Routing priority:
    1. Quit key (if on_quit set) -> quit callback
    2. Save key (if on_save set) -> save callback
    3. Search mode active -> search event handling
    4. Validate key (if on_validate set) -> validate callback
    5. Help key (if on_help set) -> help callback
    6. Back key -> navigation / search clear
    7. Search key (non-array) -> activate search
    8. Array mode -> array-specific handling
    9. Default -> pass to Frame's process_event

    Args:
        ctx
            ViewContext providing state, keymap, and config.

        search_controller
            SearchController for search mode state.

        array_controller
            ArrayController for array item operations.

        focus_manager
            FocusManager for querying focused widget state.

        callbacks
            ViewCallbacks for rebuild, status, and focus.

        add_item_fn
            Callable for adding array items, bridging
            FocusManager and ArrayController through the view.
    """
    def __init__(self, ctx, search_controller, array_controller, focus_manager, callbacks, add_item_fn=None):
        self._ctx = ctx
        self._search = search_controller
        self._array = array_controller
        self._focus = focus_manager
        self._callbacks = callbacks
        self._add_item_fn = add_item_fn

    def route(self, event, view):
        """Route a KeyboardEvent to the correct handler.

        Args:
            event
                KeyboardEvent to process.

            view
                The FieldListView for calling default_process_event.

        Returns:
            Event result, or None if consumed.
        """
        if self._callbacks.on_quit and self._ctx.keymap.matches("quit", event.key_code):
            self._callbacks.on_quit()
            return None

        if self._callbacks.on_save and self._ctx.keymap.matches("save", event.key_code):
            self._callbacks.on_save()
            return None

        if self._search.is_active:
            return self._route_search_event(event, view)

        if self._callbacks.on_validate and self._ctx.keymap.matches("validate", event.key_code):
            self._callbacks.on_validate()
            return None

        if self._callbacks.on_help and self._ctx.keymap.matches("help", event.key_code):
            self._callbacks.on_help()
            return None

        if self._ctx.keymap.matches("back", event.key_code):
            self._handle_back_navigation()
            return None

        if (self._ctx.keymap.matches("search", event.key_code) and not self._ctx.state.is_current_level_array()):
            self._search.activate(self._focus.focused_field_name())
            return None

        if self._ctx.state.is_current_level_array():
            return self._route_array_event(event, view)

        return view.default_process_event(event)

    def _route_search_event(self, event, view):
        """Route events when in search mode.

        Back key exits search discarding term. Select key applies
        the widget value and exits search keeping the term. All
        other keys pass through to default processing, then sync
        the search widget value.

        Args:
            event
                KeyboardEvent to process.

            view
                The FieldListView for default event processing.

        Returns:
            Event result, or None if consumed.
        """
        if self._ctx.keymap.matches("back", event.key_code):
            self._search.deactivate(keep_term=False)
            return None

        if self._ctx.keymap.matches("select", event.key_code):
            self._search.apply_search_widget_value()
            self._search.deactivate(keep_term=True)
            return None

        result = view.default_process_event(event)
        self._search.apply_search_widget_value()
        return result

    def _route_array_event(self, event, view):
        """Route events in array mode.

        Handles add, delete, move up, and move down. Unrecognized
        keys fall through to default processing.

        Args:
            event
                KeyboardEvent to process.

            view
                The FieldListView for default event processing.

        Returns:
            Event result, or None if consumed.
        """
        if self._ctx.keymap.matches("add_item", event.key_code):
            self._add_item_fn()
            return None

        if self._ctx.keymap.matches("delete_item", event.key_code):
            self._array.delete_item(self._focus.focused_array_index())
            return None

        if self._ctx.keymap.matches("move_up", event.key_code):
            self._array.move_item_up(self._focus.focused_array_index())
            return None

        if self._ctx.keymap.matches("move_down", event.key_code):
            self._array.move_item_down(self._focus.focused_array_index())
            return None

        return view.default_process_event(event)

    def _handle_back_navigation(self):
        """Handle the back key: navigate up or clear search term.

        1. Try navigate_back(). If it returns a value, clear search,
           rebuild, and focus on the popped segment.
        2. Otherwise, if a search term exists, clear it, rebuild,
           and restore the pre-search focus.
        """
        popped = self._ctx.state.navigate_back()
        if popped is not None:
            self._search.clear()
            self._callbacks.rebuild()
            if isinstance(popped, int):
                self._callbacks.focus.focus_on_array_index(popped)
            else:
                self._callbacks.focus.focus_on_field_by_name(popped)
            return

        if self._search.search_term:
            restore_field = self._search.pre_search_field
            self._search.clear()
            self._callbacks.rebuild()
            if restore_field:
                self._callbacks.focus.focus_on_field_by_name(restore_field)
