"""Integration tests for the edit TUI.

Tests use the headless Canvas pattern: MagicMock(spec=Screen) + Canvas
to exercise FieldListView without a real terminal. All assertions target
EditorState (working_data, current_path, is_modified), never canvas pixels.
"""
import copy
import json
import os

# ORIG_CWD must be set before any qmk imports.
os.environ['ORIG_CWD'] = os.getcwd()

from unittest.mock import MagicMock  # noqa: E402

from asciimatics.event import KeyboardEvent  # noqa: E402
from asciimatics.scene import Scene  # noqa: E402
from asciimatics.screen import Screen, Canvas  # noqa: E402

from qmk.cli.edit.config import EditorConfig  # noqa: E402
from qmk.cli.edit.editor import EditorController  # noqa: E402
from qmk.cli.edit.file_manager import FileManager  # noqa: E402
from qmk.cli.edit.schema_loader import SchemaLoader  # noqa: E402
from qmk.cli.edit.state import EditorState  # noqa: E402
from qmk.cli.edit.widgets import create_default_registry  # noqa: E402
from qmk.cli.edit.views.confirm_dialog import ConfirmDialog  # noqa: E402
from qmk.cli.edit.views.error_dialog import ErrorDialog  # noqa: E402
from qmk.cli.edit.views.field_list import FieldListView  # noqa: E402

# Load default test data at module level.
_test_data_path = os.path.join(
    os.environ['ORIG_CWD'], 'lib', 'python', 'qmk', 'tests', 'minimal_info.json',
)
with open(_test_data_path) as _f:
    _DEFAULT_DATA = json.load(_f)


def make_test_view(data=None, schema_path=None):
    """Create a headless FieldListView for testing.

    Args:
        data
            JSON dict for EditorState. Defaults to _DEFAULT_DATA contents
            (deep copied).

        schema_path
            Unused, reserved for future override. Schema always loaded
            via SchemaLoader().

    Returns:
        Tuple of (view, state, canvas, scene).
    """
    if data is None:
        data = copy.deepcopy(_DEFAULT_DATA)

    screen = MagicMock(spec=Screen)
    screen.height = 30
    screen.width = 100
    screen.colours = 8
    screen.unicode_aware = False
    canvas = Canvas(screen, 30, 100, 0, 0)

    schema_loader = SchemaLoader()
    state = EditorState(data, schema_loader)
    registry = create_default_registry()

    view = FieldListView(canvas, state, 'handwired/pytest/basic', registry)
    scene = Scene([view], -1)
    view.reset()

    return (view, state, canvas, scene)


def process_keys(form, keys):
    """Simulate keyboard input on a form.

    Args:
        form
            An asciimatics Frame instance.

        keys
            List of int key codes or str values (each char typed
            individually).
    """
    for item in keys:
        if isinstance(item, int):
            form.process_event(KeyboardEvent(item))
        elif isinstance(item, str):
            for ch in item:
                form.process_event(KeyboardEvent(ord(ch)))


def test_load_and_render():
    """FieldListView loads data and renders without error."""
    view, state, canvas, scene = make_test_view()

    assert 'keyboard_name' in state.working_data
    assert 'maintainer' in state.working_data
    assert 'layouts' in state.working_data
    assert state.working_data['keyboard_name'] == 'tester'
    assert state.working_data['maintainer'] == 'qmk'

    view.update(0)

    assert state.current_path == ()
    assert state.is_modified is False


def test_edit_text_field():
    """Typing into a text field updates state.working_data."""
    view, state, canvas, scene = make_test_view()

    # Tab focuses keyboard_folder (first focusable widget after header).
    # Type 'hello' into that field.
    process_keys(view, [Screen.KEY_TAB, 'hello'])

    assert state.working_data['keyboard_folder'] == 'hello'
    assert state.is_modified is True
    assert state.working_data['keyboard_name'] == 'tester'


def test_navigation():
    """Enter navigates into an object, Escape navigates back."""
    view, state, canvas, scene = make_test_view()

    assert state.current_path == ()

    # Tab 8 times to reach the first object row (apa102).
    tabs = [Screen.KEY_TAB] * 8
    process_keys(view, tabs)

    # Enter navigates into the object.
    process_keys(view, [ord('\n')])
    assert state.current_path == ('apa102',)

    # Escape navigates back to root.
    process_keys(view, [Screen.KEY_ESCAPE])
    assert state.current_path == ()


def _make_array_test_view(data, array_path, config=None):
    """Create a headless view pre-navigated into an array.

    Navigates state into the array before creating the FieldListView,
    so the view renders in array mode rather than object mode.

    Args:
        data
            JSON dict with array data already populated.

        array_path
            String key of the array to navigate into.

        config
            Optional EditorConfig for behavioral overrides.

    Returns:
        Tuple of (view, state, canvas, scene).
    """
    screen = MagicMock(spec=Screen)
    screen.height = 30
    screen.width = 100
    screen.colours = 8
    screen.unicode_aware = False
    canvas = Canvas(screen, 30, 100, 0, 0)

    schema_loader = SchemaLoader()
    state = EditorState(data, schema_loader)
    registry = create_default_registry()

    state.navigate_into(array_path)

    view = FieldListView(
        canvas, state, 'handwired/pytest/basic', registry, config=config,
    )
    scene = Scene([view], -1)
    view.reset()

    return (view, state, canvas, scene)


def test_array_add_item():
    """Ctrl+N adds a scaffolded item to the current array."""
    data = copy.deepcopy(_DEFAULT_DATA)
    data['community_layouts'] = ['ortho_1x1']

    view, state, canvas, scene = _make_array_test_view(data, 'community_layouts')

    assert state.get_current_array_length() == 1

    # Tab to focus an array item, then Ctrl+N to add.
    process_keys(view, [Screen.KEY_TAB, Screen.ctrl('n')])

    assert state.get_current_array_length() == 2
    assert len(state.working_data['community_layouts']) == 2
    assert state.working_data['community_layouts'][0] == 'ortho_1x1'
    # ItemScaffolder returns '' for string-typed array items.
    assert state.working_data['community_layouts'][1] == ''
    assert state.is_modified is True


def test_array_delete_item():
    """Ctrl+D deletes the focused array item when no_confirm_delete is set."""
    data = copy.deepcopy(_DEFAULT_DATA)
    data['community_layouts'] = ['ortho_1x1', 'numpad_1x1']

    config = EditorConfig(no_confirm_delete=True)
    view, state, canvas, scene = _make_array_test_view(
        data, 'community_layouts', config=config,
    )

    assert state.get_current_array_length() == 2

    # Tab to focus an array item, then Ctrl+D to delete.
    process_keys(view, [Screen.KEY_TAB, Screen.ctrl('d')])

    assert state.get_current_array_length() == 1
    assert state.is_modified is True
    assert state.working_data['community_layouts'] == ['ortho_1x1']


def test_array_move_item():
    """Move-up and move-down reorder items; boundary moves are no-ops."""
    data = copy.deepcopy(_DEFAULT_DATA)
    data['community_layouts'] = ['alpha', 'beta', 'gamma']

    view, state, canvas, scene = _make_array_test_view(data, 'community_layouts')

    # Tab to focus item at index 1 (beta).
    process_keys(view, [Screen.KEY_TAB])

    # Move down: beta swaps with gamma.
    process_keys(view, [Screen.ctrl('j')])
    assert state.working_data['community_layouts'] == ['alpha', 'gamma', 'beta']
    assert state.is_modified is True

    # Move up: beta swaps back with gamma.
    process_keys(view, [Screen.ctrl('k')])
    assert state.working_data['community_layouts'] == ['alpha', 'beta', 'gamma']

    # Move up again: beta is now at index 0 after the swap above,
    # so move up from index 1 puts it at 0; one more move up is a no-op.
    process_keys(view, [Screen.ctrl('k')])
    assert state.working_data['community_layouts'] == ['beta', 'alpha', 'gamma']

    process_keys(view, [Screen.ctrl('k')])
    assert state.working_data['community_layouts'] == ['beta', 'alpha', 'gamma']


def test_edit_numeric_array_item():
    """Typing a number into an integer array item stores an int in state."""
    data = copy.deepcopy(_DEFAULT_DATA)
    data['bootmagic'] = {'matrix': [0, 1]}

    screen = MagicMock(spec=Screen)
    screen.height = 30
    screen.width = 100
    screen.colours = 8
    screen.unicode_aware = False
    canvas = Canvas(screen, 30, 100, 0, 0)

    schema_loader = SchemaLoader()
    state = EditorState(data, schema_loader)
    registry = create_default_registry()

    state.navigate_into('bootmagic')
    state.navigate_into('matrix')

    view = FieldListView(canvas, state, 'handwired/pytest/basic', registry)
    scene = Scene([view], -1)  # noqa: F841
    view.reset()

    # Select all existing text in first array item and replace with '42'.
    # Ctrl+A selects all, then typing replaces.
    process_keys(view, [Screen.ctrl('a'), '42'])

    assert state.working_data['bootmagic']['matrix'][0] == 42
    assert isinstance(state.working_data['bootmagic']['matrix'][0], int)
    assert state.is_modified is True

    # Type non-numeric input: value should revert to 42 (not corrupted).
    process_keys(view, [Screen.ctrl('a'), 'abc'])
    assert state.working_data['bootmagic']['matrix'][0] == 42


def make_controller_view(data=None, validate_errors=None):
    """Create a headless view with EditorController for save/quit testing.

    Args:
        data
            JSON dict for EditorState. Defaults to deep copy of _DEFAULT_DATA.

        validate_errors
            List of error dicts that FileManager.validate() returns.
            Defaults to [] (no errors, validation passes).

    Returns:
        Tuple of (view, state, scene, file_manager_mock).
    """
    if data is None:
        data = copy.deepcopy(_DEFAULT_DATA)
    if validate_errors is None:
        validate_errors = []

    screen = MagicMock(spec=Screen)
    screen.height = 30
    screen.width = 100
    screen.colours = 8
    screen.unicode_aware = False
    canvas = Canvas(screen, 30, 100, 0, 0)

    schema_loader = SchemaLoader()
    state = EditorState(data, schema_loader)
    registry = create_default_registry()

    file_manager = MagicMock(spec=FileManager)
    file_manager.validate.return_value = validate_errors
    file_manager.save.return_value = None

    controller = EditorController(
        canvas, state, 'handwired/pytest/basic', registry, file_manager,
    )
    view = controller.create_view()
    scene = Scene([view], -1)
    controller.set_scene(scene)
    view.reset()

    return (view, state, scene, file_manager)


def test_save_valid():
    """Ctrl+S triggers validate then save when data is valid."""
    view, state, scene, file_manager = make_controller_view()

    # Modify data so save is meaningful.
    process_keys(view, [Screen.KEY_TAB, 'X'])
    assert state.is_modified is True

    # Press Ctrl+S to save.
    process_keys(view, [Screen.ctrl('s')])

    assert file_manager.validate.called is True
    assert file_manager.save.called is True
    assert file_manager.save.call_args[0][0] == state.working_data
    assert not any(isinstance(e, ErrorDialog) for e in scene.effects)
    assert state.is_modified is False


def test_save_validation_error():
    """Ctrl+S with invalid data shows ErrorDialog, does NOT call save."""
    view, state, scene, file_manager = make_controller_view(
        validate_errors=[{'path': 'keyboard_name', 'message': 'Invalid value'}],
    )

    # Press Ctrl+S to attempt save.
    process_keys(view, [Screen.ctrl('s')])

    assert file_manager.validate.called is True
    assert file_manager.save.called is False
    assert any(isinstance(e, ErrorDialog) for e in scene.effects)


def test_quit_unsaved_changes():
    """Pressing 'q' with unsaved changes shows ConfirmDialog."""
    view, state, scene, file_manager = make_controller_view()

    # Modify data so changes are unsaved.
    process_keys(view, [Screen.KEY_TAB, 'Z'])
    assert state.is_modified is True

    # Press quit key.
    process_keys(view, [ord('q')])

    assert any(isinstance(e, ConfirmDialog) for e in scene.effects)
    assert file_manager.save.called is False
