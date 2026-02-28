"""Callback interface for view collaborators.

Provides the mechanism collaborators use to communicate back to the
parent view without holding a direct reference to it.
"""


class ViewCallbacks:
    """Callback bundle passed to collaborators for view communication.

    Args:
        rebuild_fn
            No-arg callable that triggers a full UI rebuild.

        show_status_fn
            Callable taking (message, duration=2.5) to display a
            temporary status message.

        focus_manager
            FocusManager instance for controlling widget focus.

        on_quit
            Optional no-arg callable for quit action.

        on_save
            Optional no-arg callable for save action.

        on_validate
            Optional no-arg callable for validate action.

        on_help
            Optional no-arg callable for help action.
    """
    def __init__(self, rebuild_fn, show_status_fn, focus_manager, on_quit=None, on_save=None, on_validate=None, on_help=None):
        self.rebuild = rebuild_fn
        self.show_status = show_status_fn
        self.focus = focus_manager
        self.on_quit = on_quit
        self.on_save = on_save
        self.on_validate = on_validate
        self.on_help = on_help
