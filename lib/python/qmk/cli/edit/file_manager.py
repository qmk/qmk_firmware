"""File manager for keyboard JSON files.
"""

import json

import referencing
import referencing.jsonschema
from jsonschema import Draft202012Validator

import qmk.path
from qmk.json_encoders import InfoJSONEncoder
from qmk.json_schema import compile_schema_store, json_load


class FileManager:
    """Handles loading and saving keyboard JSON files."""
    def __init__(self, keyboard, schema_store=None):
        """Initialize with keyboard name/path.

        Args:
            keyboard
                Keyboard name like 'handwired/pytest/basic'.

            schema_store
                Pre-compiled schema store dict (schema_id -> schema_dict).
                If None, compiles via compile_schema_store() as fallback.
        """
        self.keyboard = keyboard
        self._file_path = None

        if schema_store is None:
            schema_store = compile_schema_store()
        self._validator = self._build_validator(schema_store)

    def _build_validator(self, schema_store):
        """Build a Draft202012Validator from a schema store.

        Args:
            schema_store
                Dict mapping schema_id to schema_dict.

        Returns:
            A Draft202012Validator for the qmk.keyboard.v1 schema.
        """
        keyboard_schema = schema_store["qmk.keyboard.v1"]
        resources = [(schema_id, referencing.Resource.from_contents(
            schema,
            default_specification=referencing.jsonschema.DRAFT202012,
        )) for schema_id, schema in schema_store.items()]
        registry = referencing.Registry().with_resources(resources)
        return Draft202012Validator(keyboard_schema, registry=registry)

    @property
    def file_path(self):
        """Return Path to the keyboard's keyboard.json or info.json."""
        if self._file_path:
            return self._file_path

        keyboard_dir = qmk.path.keyboard(self.keyboard)
        keyboard_json = keyboard_dir / "keyboard.json"
        info_json = keyboard_dir / "info.json"

        if keyboard_json.exists():
            self._file_path = keyboard_json
        elif info_json.exists():
            self._file_path = info_json
        else:
            self._file_path = keyboard_json

        return self._file_path

    def load(self):
        """Load and return JSON data using hjson.

        Returns:
            Dictionary of keyboard data, or empty dict if file doesn't exist.
        """
        if not self.file_path.exists():
            return {}

        return json_load(self.file_path)

    def save(self, data):
        """Save data using InfoJSONEncoder format.

        Args:
            data
                Dictionary of keyboard data to save.
        """
        self.file_path.parent.mkdir(parents=True, exist_ok=True)

        with open(self.file_path, "w", encoding="utf-8") as f:
            f.write(json.dumps(data, cls=InfoJSONEncoder, sort_keys=False))
            f.write("\n")

    def validate(self, data):
        """Validate data against keyboard schema.

        Args:
            data
                Dictionary of keyboard data to validate.

        Returns:
            List of error dicts: [{'path': '...', 'message': '...'}, ...].
            Empty list if valid.
        """
        errors = []
        for error in self._validator.iter_errors(data):
            path = ".".join(str(p) for p in error.absolute_path)
            errors.append({"path": path if path else "<root>", "message": error.message})

        return errors
