"""Status message management and footer text generation.

Owns the status message state and expiry timer, and generates
footer text with help shortcut and optional constraint hint.
"""
import time

# Layout indices for accessing Frame._layouts.
# These are used because asciimatics Frame doesn't provide a public API
# for layout access. Tested with asciimatics 1.x.
_HEADER_LAYOUT_INDEX = 0
_FOOTER_LAYOUT_INDEX = -1
_FOOTER_TEXT_WIDGET_INDEX = 1  # Second widget in footer (after blank line)


class StatusDisplay:
    """Manages status messages and footer hint text.

    Args:
        ctx
            ViewContext instance providing state and keymap access.

        rebuild_fn
            No-arg callable that triggers a full UI rebuild.
    """
    def __init__(self, ctx, rebuild_fn, frame_helper=None):
        self._ctx = ctx
        self._rebuild_fn = rebuild_fn
        self._frame_helper = frame_helper
        self._status_message = None
        self._status_expires = 0

    def show(self, message, duration=2.5):
        """Show status message by updating footer label in-place.

        Sets the status message and its expiry time, then updates
        the footer widget directly without triggering a rebuild.

        Args:
            message
                Text to display in the footer area.

            duration
                Seconds to display the message. Defaults to 2.5.
        """
        self._status_message = message
        self._status_expires = time.time() + duration

        if self._frame_helper is None:
            return

        if self._frame_helper.get_layout_count() < 3:
            return

        footer_layout = self._frame_helper.get_layout_by_index(_FOOTER_LAYOUT_INDEX)
        if footer_layout is None:
            return

        footer_widgets = self._frame_helper.get_layout_column_widgets(footer_layout, 0)
        if not footer_widgets or len(footer_widgets) <= _FOOTER_TEXT_WIDGET_INDEX:
            return

        footer_widget = footer_widgets[_FOOTER_TEXT_WIDGET_INDEX]
        self._frame_helper.update_label_text(footer_widget, message)

    def get_footer_text(self, hint=None):
        """Return footer string with help shortcut and optional hint.

        If a status message is active and not expired, returns it.
        Otherwise returns '{help_display} Help' optionally followed
        by ' | {hint}'.

        Args:
            hint
                Optional constraint hint string to append.

        Returns:
            Footer text string.
        """
        if self._status_message and time.time() < self._status_expires:
            return self._status_message

        base = "%s Help" % self._ctx.keymap.get_display("help")
        if hint:
            return base + " | " + hint
        return base

    def check_expiry(self):
        """Clear expired message. Returns True if footer needs update.

        Returns:
            True if the message was expired and cleared, False otherwise.
        """
        if not self._status_message:
            return False

        if time.time() >= self._status_expires:
            self._status_message = None
            return True

        return False

    def update_footer_widget(self, frame_helper, hint):
        """Update footer label in-place with current help + hint text.

        Skips the update when a status message is still active.
        Otherwise computes the footer text and writes it to the
        widget, clearing any expired status message first.

        Args:
            frame_helper
                FrameHelper instance for accessing layouts and widgets.

            hint
                Optional constraint hint string, or None.
        """
        if self._status_message and time.time() < self._status_expires:
            return

        self._status_message = None

        new_text = self.get_footer_text(hint)

        if frame_helper.get_layout_count() < 3:
            return

        footer_layout = frame_helper.get_layout_by_index(_FOOTER_LAYOUT_INDEX)
        if footer_layout is None:
            return

        footer_widgets = frame_helper.get_layout_column_widgets(footer_layout, 0)
        if not footer_widgets:
            return

        if len(footer_widgets) <= _FOOTER_TEXT_WIDGET_INDEX:
            return

        footer_widget = footer_widgets[_FOOTER_TEXT_WIDGET_INDEX]
        if frame_helper.get_label_text(footer_widget) != new_text:
            frame_helper.update_label_text(footer_widget, new_text)

    def update_breadcrumb_widget(self, frame_helper, breadcrumb_text):
        """Update breadcrumb label in-place if changed.

        Finds the header layout and checks if the first widget's
        text differs from breadcrumb_text. If so, updates it.

        Args:
            frame_helper
                FrameHelper instance for accessing layouts and widgets.

            breadcrumb_text
                New breadcrumb string to display.
        """
        if frame_helper.get_layout_count() == 0:
            return

        header_layout = frame_helper.get_layout_by_index(_HEADER_LAYOUT_INDEX)
        if header_layout is None:
            return

        widgets = frame_helper.get_layout_column_widgets(header_layout, 0)
        if not widgets:
            return

        breadcrumb_widget = widgets[0]
        current_text = frame_helper.get_label_text(breadcrumb_widget)
        if current_text != breadcrumb_text:
            frame_helper.update_label_text(breadcrumb_widget, breadcrumb_text)
