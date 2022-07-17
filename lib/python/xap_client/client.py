"""XAP Client
"""
import hid


class XAPClient:
    @staticmethod
    def list(search=None):
        """Find compatible XAP devices
        """
        def _is_xap_usage(x):
            return x['usage_page'] == 0xFF51 and x['usage'] == 0x0058

        def _is_filtered_device(x):
            name = '%04x:%04x' % (x['vendor_id'], x['product_id'])
            return name.lower().startswith(search.lower())

        devices = filter(_is_xap_usage, hid.enumerate())
        if search:
            devices = filter(_is_filtered_device, devices)

        return list(devices)

    def connect(self, dev):
        """Connect to a given XAP device
        """
        from .device import XAPDevice

        return XAPDevice(dev)
