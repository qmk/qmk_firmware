"""Field list view with navigation and search.
"""
from asciimatics.widgets import Frame
from asciimatics.event import KeyboardEvent

from qmk.cli.edit.keymap import Keymap
from qmk.cli.edit.views.view_context import ViewContext
from qmk.cli.edit.views.view_callbacks import ViewCallbacks
from qmk.cli.edit.views.item_scaffolder import ItemScaffolder
from qmk.cli.edit.views.status_display import StatusDisplay
from qmk.cli.edit.views.focus_manager import FocusManager
from qmk.cli.edit.views.search_controller import SearchController
from qmk.cli.edit.views.array_controller import ArrayController
from qmk.cli.edit.views.delete_confirm_dialog import DeleteConfirmDialog
from qmk.cli.edit.views.ui_builder import UIBuilder
from qmk.cli.edit.views.event_router import EventRouter
from qmk.cli.edit.views.frame_helper import FrameHelper


class FieldListView(Frame):
    """Main field list view. Thin shell delegating to collaborators.
    """
    def __init__(self, screen, state, keyboard, registry, keymap=None, config=None, on_quit=None, on_save=None, on_validate=None, on_help=None):
        super().__init__(screen, screen.height, screen.width, has_border=False, title="QMK Edit")
        self.set_theme("bright")
        self._frame_helper = FrameHelper(self)
        ctx = ViewContext(state, keyboard, keymap or Keymap(), registry, config)
        self._ctx = ctx
        self._scaffolder = ItemScaffolder(ctx.state.schema_loader)
        self._status = StatusDisplay(ctx, self._rebuild_ui, frame_helper=self._frame_helper)
        self._focus_mgr = FocusManager()
        callbacks = ViewCallbacks(
            self._rebuild_ui,
            self._status.show,
            self._focus_mgr,
            on_quit=on_quit,
            on_save=on_save,
            on_validate=on_validate,
            on_help=on_help,
        )
        self._search = SearchController(callbacks)
        self._delete_dialog_active = False
        self._array = ArrayController(ctx, callbacks, self._scaffolder, self._show_delete_dialog)
        self._builder = UIBuilder(ctx, self._search)
        self._router = EventRouter(ctx, self._search, self._array, self._focus_mgr, callbacks, add_item_fn=self._on_add_item)
        self._last_focused_widget = None
        self._current_hint = None
        self._rebuild_ui()

    def _rebuild_ui(self):
        """Clear layouts and rebuild all UI from collaborators.
        """
        self._frame_helper.clear_layouts()
        self._frame_helper.reset_focus_index()
        all_fields = self._builder.build(self, self._make_navigate_handler, self._on_add_item, self._status)
        self._focus_mgr.update(self, all_fields, frame_helper=self._frame_helper)
        self._last_focused_widget = None
        self._current_hint = None
        self._frame_helper.set_has_focus(True)
        self.fix()

    def _make_navigate_handler(self, key):
        """Create navigation handler for object/array row click.
        """
        def handler():
            self._ctx.state.navigate_into(key)
            self._search.clear()
            self._rebuild_ui()

        return handler

    def _on_add_item(self):
        """Bridge FocusManager and ArrayController for add item.
        """
        self._array.add_item(self._focus_mgr.focused_array_index())

    def _show_delete_dialog(self, item_index, on_confirm, on_cancel):
        """Show modal delete confirmation dialog.

        Guards against stacking multiple dialogs. Wraps callbacks
        to clear the active flag before delegating.

        Args:
            item_index
                Index of the array item to delete.

            on_confirm
                Callback to invoke when user confirms deletion.

            on_cancel
                Callback to invoke when user cancels.
        """
        if self._delete_dialog_active:
            return

        self._delete_dialog_active = True

        def _on_confirm():
            self._delete_dialog_active = False
            on_confirm()

        def _on_cancel():
            self._delete_dialog_active = False
            on_cancel()

        dialog = DeleteConfirmDialog(self.screen, item_index, _on_confirm, _on_cancel)
        self._scene.add_effect(dialog)

    def show_status(self, message, duration=2.5):
        """Show a temporary status message.
        """
        self._status.show(message, duration)

    def process_event(self, event):
        """Route keyboard events through EventRouter.
        """
        if not isinstance(event, KeyboardEvent):
            return super().process_event(event)
        if hasattr(self, '_handle_desktop_ordering'):
            self._handle_desktop_ordering(event)
        return self._router.route(event, self)

    def default_process_event(self, event):
        """Delegate to Frame's process_event for default handling.
        """
        return super().process_event(event)

    def update(self, frame_no):
        """Update breadcrumb and footer widgets each frame.

        Detects focus changes via identity comparison and recomputes
        the constraint hint only when the focused widget changes.
        """
        self._status.update_breadcrumb_widget(self._frame_helper, self._builder.build_breadcrumb())

        # Recompute hint only when focused widget identity changes
        focused = self._focus_mgr.get_focused_field_widget()
        if focused is not self._last_focused_widget:
            self._last_focused_widget = focused
            self._current_hint = focused.get_hint() if focused else None

        self._status.update_footer_widget(self._frame_helper, self._current_hint)
        return super().update(frame_no)
