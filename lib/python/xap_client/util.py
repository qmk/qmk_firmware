def u32toBCD(val):  # noqa: N802
    """Create BCD string
    """
    return f'{val>>24}.{val>>16 & 0xFF}.{val & 0xFFFF}'
