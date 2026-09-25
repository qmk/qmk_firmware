# XAP python3 bindings

## Example
```python
from xap_client import XAPClient

# List Available Devices
devices = XAPClient.devices()
selected = devices[0]

# Connect then run commands
with XAPClient().connect(selected) as dev:
    print(dev.version())
```

## API

TODO
