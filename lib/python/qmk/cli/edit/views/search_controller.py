"""Search state management for the field list view.

Owns the search mode flag, search term, search widget reference,
and pre-search field name. Delegates UI rebuilds to the parent
view through the callbacks interface.
"""


class SearchController:
    """Manages search mode state and field filtering.

    Args:
        callbacks
            ViewCallbacks instance providing rebuild and status methods.
    """
    def __init__(self, callbacks):
        self._callbacks = callbacks
        self._search_mode = False
        self._search_term = ""
        self._search_widget = None
        self._pre_search_field = None

    @property
    def is_active(self):
        """Return True if search mode is active.
        """
        return self._search_mode

    @property
    def search_term(self):
        """Return the current search term string.
        """
        return self._search_term

    @search_term.setter
    def search_term(self, value):
        """Set the search term.
        """
        self._search_term = value

    @property
    def search_widget(self):
        """Return the asciimatics search Text widget, or None.
        """
        return self._search_widget

    @search_widget.setter
    def search_widget(self, widget):
        """Set the search widget (called by UIBuilder after building search bar).
        """
        self._search_widget = widget

    @property
    def pre_search_field(self):
        """Return the field name that was focused before search was activated.
        """
        return self._pre_search_field

    def activate(self, current_field_name):
        """Enter search mode, remembering current focus for restore.

        Sets search mode to active and stores current_field_name
        so focus can be restored when search is deactivated.
        Calls callbacks.rebuild() to show the search bar.

        Args:
            current_field_name
                Name of the field that had focus before search.
        """
        self._search_mode = True
        self._pre_search_field = current_field_name
        self._callbacks.rebuild()

    def deactivate(self, keep_term=False):
        """Exit search mode.

        Clears the search term unless keep_term is True.
        Calls callbacks.rebuild() to hide the search bar.

        Args:
            keep_term
                If True, preserves the current search term.
        """
        self._search_mode = False
        if not keep_term:
            self._search_term = ""
        self._callbacks.rebuild()

    def apply_search_widget_value(self):
        """Sync search_term from the asciimatics Text widget value.

        If the search widget is set, reads its .value attribute
        and stores it as the current search term.
        """
        if self._search_widget is not None:
            self._search_term = self._search_widget.value or ""

    def clear(self):
        """Clear search term and pre_search_field without mode change.

        Does not call rebuild or change search mode. Used when
        navigating into a field to reset search state silently.
        """
        self._search_term = ""
        self._pre_search_field = None

    def matches(self, field_name):
        """Return True if field_name passes the current search filter.

        When no search term is set, all fields match. Otherwise
        performs a case-insensitive substring match.

        Args:
            field_name
                The field name to test against the search term.

        Returns:
            True if the field name matches or no filter is active.
        """
        if not self._search_term:
            return True
        return self._search_term.lower() in field_name.lower()
