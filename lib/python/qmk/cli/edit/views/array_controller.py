"""Array item manipulation: add, delete, and move operations.

Delegates focus and rebuild calls through ViewCallbacks. Receives
focused_index as a parameter to every method so it stays decoupled
from focus management. Delete confirmation is handled via a dialog
callback provided at construction time.
"""


class ArrayController:
    """Manages add, delete (with dialog confirmation), and move operations on arrays.

    Args:
        ctx
            ViewContext providing state, keymap, and config access.

        callbacks
            ViewCallbacks for rebuild, show_status, and focus control.

        item_scaffolder
            ItemScaffolder instance for creating new array items.

        show_delete_dialog_fn
            Callable accepting (item_index, on_confirm, on_cancel)
            to display a modal delete confirmation dialog.
    """
    def __init__(self, ctx, callbacks, item_scaffolder, show_delete_dialog_fn):
        self._ctx = ctx
        self._callbacks = callbacks
        self._scaffolder = item_scaffolder
        self._show_delete_dialog_fn = show_delete_dialog_fn

    def add_item(self, focused_index):
        """Insert a new item after the focused index.

        Retrieves the item schema for the current path, scaffolds a
        default item, and inserts it. For object items, navigates into
        the new item. For simple items, focuses on the new item.

        Args:
            focused_index
                Currently focused array index, or None to append.
        """
        item_schema = self._ctx.state.schema_loader.get_items_schema(
            self._ctx.state.current_path,
        )
        if item_schema is None:
            return

        current_length = self._ctx.state.get_current_array_length() or 0
        insert_index = focused_index + 1 if focused_index is not None else current_length

        new_item = self._scaffolder.scaffold(item_schema)
        self._ctx.state.insert_array_item(insert_index, new_item)

        if item_schema.get('type') == 'object':
            self._ctx.state.navigate_into(insert_index)
            self._callbacks.rebuild()
        else:
            self._callbacks.rebuild()
            self._callbacks.focus.focus_on_array_index(insert_index)

    def delete_item(self, focused_index):
        """Begin deletion of an array item via dialog confirmation.

        If no_confirm_delete config is set, deletes immediately.
        Otherwise opens a modal confirmation dialog with callbacks
        for confirm and cancel actions.

        Args:
            focused_index
                Currently focused array index, or None (early return).
        """
        if focused_index is None:
            return

        if self._ctx.config and getattr(self._ctx.config, 'no_confirm_delete', False):
            self._perform_delete(focused_index)
            return

        def on_confirm():
            self._perform_delete(focused_index)

        def on_cancel():
            pass

        self._show_delete_dialog_fn(focused_index, on_confirm, on_cancel)

    def move_item_up(self, focused_index):
        """Swap the focused item with the one above it.

        Args:
            focused_index
                Currently focused array index, or None (early return).
        """
        if focused_index is None or focused_index == 0:
            return

        self._ctx.state.move_array_item(focused_index, focused_index - 1)
        self._callbacks.rebuild()
        self._callbacks.focus.focus_on_array_index(focused_index - 1)
        self._callbacks.show_status("Item moved up")

    def move_item_down(self, focused_index):
        """Swap the focused item with the one below it.

        Args:
            focused_index
                Currently focused array index, or None (early return).
        """
        if focused_index is None:
            return

        array_length = self._ctx.state.get_current_array_length()
        if array_length is None or focused_index >= array_length - 1:
            return

        self._ctx.state.move_array_item(focused_index, focused_index + 1)
        self._callbacks.rebuild()
        self._callbacks.focus.focus_on_array_index(focused_index + 1)
        self._callbacks.show_status("Item moved down")

    def _perform_delete(self, index):
        """Perform the actual deletion of an array item.

        Removes the item, shows status, and adjusts focus to the item
        that shifted into the deleted position (or the new last item).

        Args:
            index
                Index of item to delete.
        """
        self._ctx.state.remove_array_item(index)
        self._callbacks.rebuild()
        self._callbacks.show_status("Item deleted")

        array_length = self._ctx.state.get_current_array_length() or 0
        if array_length > 0:
            focus_index = min(index, array_length - 1)
            self._callbacks.focus.focus_on_array_index(focus_index)
