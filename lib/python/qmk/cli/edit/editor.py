"""Main editor orchestration and TUI.
"""
# TODO(unassigned): Write integration tests for editor controller once testing infrastructure supports headless asciimatics testing

import contextlib
import copy
import curses
import json
import os
import sys
import traceback

import hjson

from asciimatics.scene import Scene
from asciimatics.screen import Screen
from asciimatics.exceptions import ResizeScreenError, StopApplication

from milc import cli

from qmk.cli.edit.schema_loader import SchemaLoader
from qmk.cli.edit.file_manager import FileManager
from qmk.cli.edit.state import EditorState
from qmk.cli.edit.widgets import create_default_registry
from qmk.cli.edit.keymap import Keymap
from qmk.cli.edit.config import EditorConfig
from jsonschema.exceptions import SchemaError

from qmk.cli.edit.views import FieldListView, ErrorDialog, ConfirmDialog, HelpDialog


class EditorController:
    """Controller managing editor state and view transitions.
    """
    def __init__(self, screen, state, keyboard, registry, file_manager, keymap=None, config=None):
        """Initialize the editor controller.

        Args:
            screen
                Asciimatics Screen instance.
            state
                EditorState instance.
            keyboard
                Keyboard name.
            registry
                WidgetRegistry instance.
            file_manager
                FileManager instance.
            keymap
                Keymap instance, or None for default.
            config
                EditorConfig instance, or None for defaults.
        """
        self._screen = screen
        self._state = state
        self._keyboard = keyboard
        self._registry = registry
        self._file_manager = file_manager
        self._keymap = keymap if keymap is not None else Keymap()
        self._config = config if config is not None else EditorConfig()
        self._current_view = None
        self._scene = None

    def create_view(self):
        """Create the current view based on editor state.

        Returns:
            FieldListView instance configured for current state.
        """
        view = FieldListView(
            self._screen,
            self._state,
            self._keyboard,
            self._registry,
            self._keymap,
            self._config,
            on_quit=lambda: self._handle_quit(view),
            on_save=lambda: self._handle_save(view),
            on_validate=lambda: self._handle_validate(view),
            on_help=lambda: self._handle_help(view),
        )
        self._current_view = view
        return view

    def set_scene(self, scene):
        """Store reference to the running scene for dialog overlays.

        Args:
            scene
                The Scene instance containing the main view.
        """
        self._scene = scene

    def _perform_save(self, view):
        """Perform save operation with validation.

        Args:
            view
                Current FieldListView instance.

        Returns:
            True if save succeeded, False otherwise.
        """
        errors = self._file_manager.validate(self._state.working_data)
        if errors:
            self._show_error_dialog(errors)
            return False

        try:
            self._file_manager.save(self._state.working_data)
            cli.log.info('{fg_green}Saved to:{style_reset_all} %s', self._file_manager.file_path)
            self._state.original_data = copy.deepcopy(self._state.working_data)
            view.show_status("Saved successfully")
            return True
        except PermissionError:
            error_msg = 'Permission denied. Check file permissions for: %s' % self._file_manager.file_path
            self._show_error_dialog([{'path': str(self._file_manager.file_path), 'message': error_msg}])
            return False
        except OSError as e:
            error_msg = 'Failed to save file. %s' % str(e)
            self._show_error_dialog([{'path': str(self._file_manager.file_path), 'message': error_msg}])
            return False

    def _handle_save(self, view):
        """Handle save action with validation.

        Args:
            view
                Current FieldListView instance.
        """
        self._perform_save(view)

    def _handle_quit(self, view):
        """Handle quit action with unsaved changes check.

        Args:
            view
                Current FieldListView instance.
        """
        if not self._state.is_modified:
            raise StopApplication("User quit")

        self._show_confirm_dialog(view)

    def _handle_validate(self, view):
        """Validate working data and show results.

        Args:
            view
                Current FieldListView instance.
        """
        try:
            errors = self._file_manager.validate(self._state.working_data)
        except SchemaError as e:
            self._show_error_dialog([{'path': 'Schema', 'message': str(e)}])
            return

        if errors:
            self._show_error_dialog(errors)
        else:
            view.show_status("No errors found")

    def _handle_help(self, view):
        """Show keybinding help dialog.

        Args:
            view
                Current FieldListView instance.
        """
        dialog = HelpDialog(self._screen, self._keymap)
        self._scene.add_effect(dialog)

    def _on_confirm_close(self, view, action):
        """Handle confirm dialog result.

        Args:
            view
                Current FieldListView instance.
            action
                Action string: 'save', 'discard', or 'cancel'.
        """
        if action == 'cancel':
            return

        if action == 'save':
            if not self._perform_save(view):
                return

        raise StopApplication("User quit")

    def _show_error_dialog(self, errors):
        """Show error dialog as overlay on current scene.

        Args:
            errors
                List of error dicts with 'path' and 'message' keys.
        """
        dialog = ErrorDialog(self._screen, errors)
        self._scene.add_effect(dialog)

    def _show_confirm_dialog(self, view):
        """Show confirm dialog as overlay on current scene.

        Args:
            view
                Current FieldListView instance.
        """
        def on_close(action):
            self._on_confirm_close(view, action)

        dialog = ConfirmDialog(self._screen, on_close)
        self._scene.add_effect(dialog)


def _validate_screen_size(screen):
    """Check if terminal is large enough for the editor.

    Args:
        screen
            Asciimatics Screen instance.

    Raises:
        StopApplication
            If terminal is smaller than 80x24.
    """
    if screen.width < 80 or screen.height < 24:
        cli.log.error('{fg_red}Terminal too small{style_reset_all}')
        cli.log.error('The editor requires at least 80x24 characters.')
        cli.log.error('Current size: %dx%d', screen.width, screen.height)
        cli.log.error('Please resize your terminal and try again.')
        raise StopApplication("Terminal too small")


def _init_editor_components(keyboard):
    """Initialize all editor components.

    Args:
        keyboard
            Keyboard name like 'handwired/pytest/basic'.

    Returns:
        Tuple of (schema_loader, file_manager, state, registry, keymap).
    """
    schema_loader = SchemaLoader()
    file_manager = FileManager(keyboard, schema_store=schema_loader.schema_store)
    data = file_manager.load()
    state = EditorState(data, schema_loader)
    registry = create_default_registry()
    keymap = Keymap()
    return schema_loader, file_manager, state, registry, keymap


def _run_screen_loop(run_screen):
    """Run the screen loop, handling resize and stop events.

    Args:
        run_screen
            Callable(screen, scene) that sets up and plays the screen.

    Returns:
        0 on success, 1 on terminal-too-small error.
    """
    last_scene = None
    while True:
        try:
            Screen.wrapper(run_screen, catch_interrupt=True, arguments=[last_scene])
            return 0
        except ResizeScreenError as e:
            last_scene = e.scene
        except StopApplication as e:
            if "Terminal too small" in str(e):
                return 1
            return 0


@contextlib.contextmanager
def _bypass_milc_streams():
    """Temporarily replace sys.stdout/sys.stderr with the raw interpreter streams.

    MILC wraps sys.stdout and sys.stderr with its own logging-aware
    objects.  The curses-based TUI needs the real file descriptors, so
    this context manager swaps in sys.__stdout__ / sys.__stderr__ for
    the duration of the block and restores the MILC wrappers on exit.
    """
    saved_stdout = sys.stdout
    saved_stderr = sys.stderr
    sys.stdout = sys.__stdout__
    sys.stderr = sys.__stderr__
    try:
        yield
    finally:
        sys.stdout = saved_stdout
        sys.stderr = saved_stderr


def run_editor(keyboard, config=None):
    """Run the keyboard editor TUI.

    Args:
        keyboard
            Keyboard name like 'handwired/pytest/basic'.
        config
            EditorConfig instance, or None for defaults.

    Returns:
        0 on success, 1 on error.
    """
    if config is None:
        config = EditorConfig()

    with _bypass_milc_streams():
        os.environ.setdefault('ESCDELAY', '25')
        curses.set_escdelay(25)

        try:
            _, file_manager, state, registry, keymap = _init_editor_components(keyboard)

            def run_screen(screen, scene):
                _validate_screen_size(screen)
                controller = EditorController(screen, state, keyboard, registry, file_manager, keymap, config)
                view = controller.create_view()
                main_scene = Scene([view], -1)
                controller.set_scene(main_scene)
                screen.play([main_scene], stop_on_resize=True)

            return _run_screen_loop(run_screen)

        except StopApplication:
            return 0
        except (OSError, SchemaError, hjson.HjsonDecodeError, json.JSONDecodeError) as e:
            cli.log.error('Error running editor:\n%s', traceback.format_exc())
            return 1
