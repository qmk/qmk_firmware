# Copyright 2022 QMK
# SPDX-License-Identifier: GPL-2.0-or-later
from typing import List


class XAPClient:
    """XAP device discovery
    """
    @staticmethod
    def devices(search: str = None) -> List[dict]:
        """Find compatible XAP devices

        Args:
            search: optional search string to filter results by
        """
        def _is_xap_usage(x):
            return x['usage_page'] == 0xFF51 and x['usage'] == 0x0058

        def _is_filtered_device(x):
            name = '%04x:%04x' % (x['vendor_id'], x['product_id'])
            return name.lower().startswith(search.lower())

        # lazy import to avoid compile issues
        import hid

        devices = filter(_is_xap_usage, hid.enumerate())
        if search:
            devices = filter(_is_filtered_device, devices)

        return list(devices)

    def connect(self, device: dict):
        """Connect to a given XAP device
        Args:
            device: item from a previous `XAPClient.devices()` call
        """
        from .device import XAPDevice

        return XAPDevice(device)
