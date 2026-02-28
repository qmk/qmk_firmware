"""Help dialog for displaying keybinding reference.
"""
from asciimatics.widgets import Frame, Layout, Label, TextBox
from asciimatics.event import KeyboardEvent
from asciimatics.screen import Screen

# Column width for key display strings in the help content
_KEY_COLUMN_WIDTH = 20


def build_help_content(keymap):
    """Build the keybinding help text from a Keymap instance.

    Produces a multi-line string with all keybindings grouped by
    section: General, Navigation, Search, and Arrays.

    Args:
        keymap
            Keymap instance for resolving display names.

    Returns:
        Multi-line string with all keybindings grouped by section.
    """
    lines = ['Keybindings', '']

    # General section -- save, validate, quit, help
    lines.append('General')
    lines.append('  %s%s' % (keymap.get_display('save').ljust(_KEY_COLUMN_WIDTH), 'Save'))
    lines.append('  %s%s' % (keymap.get_display('validate').ljust(_KEY_COLUMN_WIDTH), 'Validate'))
    lines.append('  %s%s' % (keymap.get_display('quit').ljust(_KEY_COLUMN_WIDTH), 'Quit'))
    lines.append('  %s%s' % (keymap.get_display('help').ljust(_KEY_COLUMN_WIDTH), 'Help'))
    lines.append('')

    # Navigation section -- arrows, enter, back
    lines.append('Navigation')
    lines.append('  %s%s' % ('Up/Down'.ljust(_KEY_COLUMN_WIDTH), 'Navigate fields'))
    lines.append('  %s%s' % ('Enter'.ljust(_KEY_COLUMN_WIDTH), 'Edit / Enter'))
    lines.append('  %s%s' % (keymap.get_display('back').ljust(_KEY_COLUMN_WIDTH), 'Back'))
    lines.append('')

    # Search section -- start and exit
    lines.append('Search')
    lines.append('  %s%s' % ('/'.ljust(_KEY_COLUMN_WIDTH), 'Start search'))
    lines.append('  %s%s' % ('Esc'.ljust(_KEY_COLUMN_WIDTH), 'Exit search'))
    lines.append('')

    # Arrays section -- add, delete, move
    lines.append('Arrays')
    lines.append('  %s%s' % (keymap.get_display('add_item').ljust(_KEY_COLUMN_WIDTH), 'Add item'))
    lines.append('  %s%s' % (keymap.get_display('delete_item').ljust(_KEY_COLUMN_WIDTH), 'Delete item'))
    lines.append('  %s%s' % (keymap.get_display('move_up').ljust(_KEY_COLUMN_WIDTH), 'Move up'))
    lines.append('  %s%s' % (keymap.get_display('move_down').ljust(_KEY_COLUMN_WIDTH), 'Move down'))

    return '\n'.join(lines)


class HelpDialog(Frame):
    """Modal dialog displaying keybinding help.
    """
    def __init__(self, screen, keymap, on_close=None):
        """Initialize the help dialog.

        Args:
            screen
                Asciimatics Screen instance.
            keymap
                Keymap instance for resolving display names.
            on_close
                Optional callback when dialog is dismissed.
        """
        height = min(screen.height - 4, 26)
        width = min(screen.width - 4, 60)

        super().__init__(screen, height, width, has_border=True, title="Help", reduce_cpu=True, is_modal=True)

        self._on_close = on_close

        # Main content area with keybinding reference
        layout = Layout([100], fill_frame=True)
        self.add_layout(layout)

        content = build_help_content(keymap)
        text_box = TextBox(height=height - 4, as_string=True, line_wrap=True, readonly=True)
        text_box.value = content
        layout.add_widget(text_box)

        # Hint at the bottom
        hint_layout = Layout([100])
        self.add_layout(hint_layout)
        hint_layout.add_widget(Label("Press Enter or Esc to close"))

        self.fix()

    def _on_ok(self):
        """Dismiss the dialog and invoke the on_close callback.
        """
        self._scene.remove_effect(self)
        if self._on_close:
            self._on_close()

    def process_event(self, event):
        """Process keyboard events for shortcuts.

        Args:
            event
                Asciimatics event to process.

        Returns:
            Event processing result from parent class.
        """
        if isinstance(event, KeyboardEvent):
            if event.key_code in (Screen.KEY_ESCAPE, ord('\n'), ord('\r')):
                self._on_ok()
                return None

        return super().process_event(event)
