"""Editor state management.
"""
import copy


class EditorState:
    """Manages editor data and navigation state.

    Paths are tuples of string keys and int indices, e.g. ('usb', 'vid')
    or ('encoder', 'rotary', 0).
    """
    def __init__(self, original_data, schema_loader):
        """Initialize with loaded JSON and parsed schema.

        Args:
            original_data
                Original keyboard data dictionary.
            schema_loader
                SchemaLoader instance.
        """
        self.original_data = copy.deepcopy(original_data)
        self.working_data = copy.deepcopy(original_data)
        self.schema_loader = schema_loader
        self.navigation_path = ()

    @property
    def is_modified(self):
        """Return True if working_data differs from original_data.
        """
        return self.working_data != self.original_data

    @property
    def current_path(self):
        """Return current navigation path as tuple.
        """
        return self.navigation_path

    def get(self, path):
        """Get value at path from working_data.

        Args:
            path
                Tuple of keys and int indices, e.g. ('usb', 'vid').

        Returns:
            Value at path, or None if not found.
        """
        if not path:
            return None

        value = self.working_data
        for key in path:
            if isinstance(value, dict) and key in value:
                value = value[key]
            elif isinstance(value, list) and isinstance(key, int):
                if 0 <= key < len(value):
                    value = value[key]
                else:
                    return None
            else:
                return None

        return value

    def _traverse_parent(self, path_tuple):
        """Read-only traversal to the parent of the target key.

        Does not create intermediate dicts. Returns None if any
        intermediate key is missing or out of range.

        Args:
            path_tuple
                Tuple of path segments. The last element is the target key.

        Returns:
            The parent container, or None if the path is invalid.
        """
        target = self.working_data
        for key in path_tuple[:-1]:
            if isinstance(target, dict) and key in target:
                target = target[key]
            elif isinstance(target, list) and isinstance(key, int):
                if 0 <= key < len(target):
                    target = target[key]
                else:
                    return None
            else:
                return None
        return target

    def _traverse_or_create_parent(self, path_tuple):
        """Creating traversal to the parent of the target key.

        Creates intermediate dicts for missing dict keys. Returns None
        if a list index is out of range.

        Args:
            path_tuple
                Tuple of path segments. The last element is the target key.

        Returns:
            The parent container, or None if the path is invalid.
        """
        target = self.working_data
        for key in path_tuple[:-1]:
            if isinstance(target, dict):
                if key not in target:
                    target[key] = {}
                target = target[key]
            elif isinstance(target, list) and isinstance(key, int):
                if 0 <= key < len(target):
                    target = target[key]
                else:
                    return None
            else:
                return None
        return target

    def _set_at_target(self, target, last_key, value):
        """Assign value into target container at last_key.

        Args:
            target
                Dict or list to assign into.
            last_key
                String key for dicts or int index for lists.
            value
                Value to assign, or None to delete a dict key.

        Raises:
            ValueError
                When attempting to set None for array element.
        """
        if isinstance(target, dict):
            if value is None:
                if last_key in target:
                    del target[last_key]
            else:
                target[last_key] = value
        elif isinstance(target, list) and isinstance(last_key, int):
            if 0 <= last_key < len(target):
                if value is None:
                    raise ValueError('Cannot set array element to None. Use remove_array_item instead.')
                target[last_key] = value

    def set(self, path, value):
        """Set value at path in working_data.

        Use value=None to unset/remove a field (dict keys only).

        Args:
            path
                Tuple of keys and int indices, e.g. ('usb', 'vid').
            value
                Value to set, or None to remove dict key.

        Raises:
            ValueError
                When attempting to set None for array element. Use remove_array_item instead.
        """
        if not path:
            return

        if value is None and self.get(path) is None:
            return

        target = self._traverse_or_create_parent(path)

        if target is None:
            return

        self._set_at_target(target, path[-1], value)

    def navigate_into(self, key):
        """Push key onto navigation path.

        Args:
            key
                String key (for objects) or integer index (for arrays) to navigate into.
        """
        self.navigation_path = self.navigation_path + (key,)

    def navigate_back(self):
        """Pop from navigation path.

        Returns:
            The popped key (string or int), or None if already at root.
        """
        if not self.navigation_path:
            return None

        popped = self.navigation_path[-1]
        self.navigation_path = self.navigation_path[:-1]
        return popped

    def get_current_schema(self):
        """Return the schema fragment for current navigation level.
        """
        return self.schema_loader.get_properties(self.navigation_path)

    def _get_value_at_navigation_path(self):
        """Navigate to the value at current navigation path.

        Returns:
            Value at navigation path, or None if path is invalid.
        """
        if not self.navigation_path:
            return self.working_data
        return self.get(self.navigation_path)

    def get_current_data(self):
        """Return the working_data fragment for current navigation level.
        """
        value = self._get_value_at_navigation_path()
        if value is None:
            return {}
        return value

    def is_current_level_array(self):
        """Return True if current navigation level is an array.

        Checks both the data and the schema. If the data doesn't exist
        at the current path, falls back to the schema definition.

        Returns:
            True if current level is a list, False otherwise.
        """
        value = self._get_value_at_navigation_path()
        if isinstance(value, list):
            return True

        # If the value doesn't exist or isn't a list, check the schema
        if value is None and self.navigation_path:
            return self.schema_loader.is_array_at_path(self.navigation_path)

        return False

    def get_current_array_length(self):
        """Return number of items if current level is an array.

        Returns:
            Number of items in array, or None if not an array.
            Returns 0 if array doesn't exist in data but schema defines it as array.
        """
        value = self._get_value_at_navigation_path()
        if isinstance(value, list):
            return len(value)

        # If value doesn't exist, check if schema says it's an array
        if value is None and self.navigation_path:
            if self.schema_loader.is_array_at_path(self.navigation_path):
                return 0

        return None

    def insert_array_item(self, index, value):
        """Insert value at index in current array.

        Creates the array if it doesn't exist but schema defines it as array type.

        Args:
            index
                Index to insert at (0-based).
            value
                Value to insert.
        """
        target = self._get_value_at_navigation_path()
        if isinstance(target, list):
            target.insert(index, value)
        elif target is None and self.navigation_path:
            # Array doesn't exist in data - create it if schema says it's an array
            if self.schema_loader.is_array_at_path(self.navigation_path):
                self._create_array_at_current_path()
                target = self._get_value_at_navigation_path()
                if isinstance(target, list):
                    target.insert(index, value)

    def _create_array_at_current_path(self):
        """Create an empty array at the current navigation path.

        Traverses the path and creates parent objects as needed.
        """
        if not self.navigation_path:
            return

        # Navigate to parent, creating objects as needed
        target = self.working_data
        for key in self.navigation_path[:-1]:
            if isinstance(target, dict):
                if key not in target:
                    target[key] = {}
                target = target[key]
            elif isinstance(target, list) and isinstance(key, int):
                if 0 <= key < len(target):
                    target = target[key]
                else:
                    return
            else:
                return

        # Set the final key to an empty array
        final_key = self.navigation_path[-1]
        if isinstance(target, dict):
            target[final_key] = []

    def remove_array_item(self, index):
        """Remove item at index from current array.

        Args:
            index
                Index to remove (0-based).
        """
        target = self._get_value_at_navigation_path()
        if isinstance(target, list) and 0 <= index < len(target):
            del target[index]

    def move_array_item(self, from_index, to_index):
        """Move item from one index to another in current array.

        Args:
            from_index
                Source index (0-based).
            to_index
                Destination index (0-based).
        """
        if from_index == to_index:
            return

        target = self._get_value_at_navigation_path()
        if isinstance(target, list):
            if 0 <= from_index < len(target) and 0 <= to_index < len(target):
                item = target.pop(from_index)
                target.insert(to_index, item)

    def reset(self):
        """Discard changes, reset working_data to original.
        """
        self.working_data = copy.deepcopy(self.original_data)
