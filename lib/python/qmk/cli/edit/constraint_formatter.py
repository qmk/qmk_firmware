"""Constraint hint formatting for field validation display.

Pure function module that converts schema constraints and enum
values into human-readable hint strings. No framework dependencies.
"""

# Known regex patterns mapped to friendly labels.
PATTERN_LABELS = {
    '^0x[0-9A-F]{4}$': 'format: 0xNNNN',
    '^0x[0-9A-F]{2}$': 'format: 0xNN',
    '^[A-K]\\d{1,2}$': 'pin: A0-K99',
    '^GP\\d{1,2}$': 'pin: GP0-GP99',
    '^LINE_PIN\\d{1,2}$': 'pin: LINE_PIN0-99',
    '^[0-9]{1,2}\\.[0-9]\\.[0-9]$': 'version: N.N.N',
    '^[a-z][a-z0-9_]*$': 'snake_case',
    '^[0-9a-z_]*$': 'lowercase alphanumeric',
}

# Enum values beyond this count are truncated with a total suffix.
MAX_ENUM_DISPLAY = 5


def format_hint(constraints, enum_values=None):
    """Return constraint hint string, or None if no constraints.

    Args:
        constraints
            Dict with optional keys: minimum, maximum, minLength,
            maxLength, pattern. From SchemaLoader.get_constraints().

        enum_values
            List of allowed values, or None. From
            SchemaLoader.get_enum_values().

    Returns:
        Hint string like '0-255' or 'one of: a, b, c', or None.
    """
    # Enum values take priority -- return immediately if present.
    if enum_values:
        return _format_enum(enum_values)

    parts = []

    # Integer range constraints
    _append_range(parts, constraints, 'minimum', 'maximum', '')

    # String length constraints
    _append_range(parts, constraints, 'minLength', 'maxLength', ' chars')

    # Pattern constraint
    pattern = constraints.get('pattern')
    if pattern is not None:
        label = PATTERN_LABELS.get(pattern, 'pattern: %s' % pattern)
        parts.append(label)

    if not parts:
        return None

    return ', '.join(parts)


def _format_enum(values):
    """Format an enum value list as a hint string.

    Truncates to MAX_ENUM_DISPLAY values, appending a total count
    suffix when the full list is longer.

    Args:
        values
            List of allowed values (may be non-string).

    Returns:
        Hint string like 'one of: a, b, c'.
    """
    str_values = [str(v) for v in values]
    if len(str_values) <= MAX_ENUM_DISPLAY:
        return 'one of: %s' % ', '.join(str_values)

    truncated = ', '.join(str_values[:MAX_ENUM_DISPLAY])
    return 'one of: %s, ... (%d total)' % (truncated, len(str_values))


def _append_range(parts, constraints, min_key, max_key, suffix):
    """Append a range or bound hint to parts if present.

    Handles three cases: both min+max, min only, max only.

    Args:
        parts
            List to append hint string to.

        constraints
            Dict of constraint key/value pairs.

        min_key
            Key name for the minimum bound (e.g. 'minimum', 'minLength').

        max_key
            Key name for the maximum bound (e.g. 'maximum', 'maxLength').

        suffix
            Unit suffix appended after the value (e.g. ' chars', '').
    """
    min_val = constraints.get(min_key)
    max_val = constraints.get(max_key)

    if min_val is not None and max_val is not None:
        parts.append('%s-%s%s' % (min_val, max_val, suffix))
    elif min_val is not None:
        parts.append('>= %s%s' % (min_val, suffix))
    elif max_val is not None:
        parts.append('<= %s%s' % (max_val, suffix))
