# Secure

The secure feature aims to prevent unwanted interaction without user intervention.

?> Secure does **not** currently implement encryption/decryption/etc and should not be a replacement where a strong hardware/software based solution is required.

### Unlock sequence

To unlock, the user must perform a set of actions. This can optionally be configured to be multiple keys.

* While unlocking all keyboard input is ignored
* Incorrect attempts will revert back to the previously locked state

### Automatic Locking

Once unlocked, the keyboard will revert back to a locked state after the configured timeout.
The timeout can be refreshed by using the `secure_activity_event` function, for example from one of the various [hooks](custom_quantum_functions.md).

## Usage

Add the following to your `rules.mk`:

```make
SECURE_ENABLE = yes
```

## Keycodes

| Key                 |Aliases  | Description                                                                    |
|---------------------|---------|--------------------------------------------------------------------------------|
| `QK_SECURE_LOCK`    |`SE_LOCK`| Revert back to a locked state                                                  |
| `QK_SECURE_UNLOCK`  |`SE_UNLK`| Forces unlock without performing a unlock sequence                             |
| `QK_SECURE_TOGGLE`  |`SE_TOGG`| Toggle directly between locked and unlock without performing a unlock sequence |
| `QK_SECURE_REQUEST` |`SE_REQ` | Request that user perform the unlock sequence                                  |

## Configuration

| Define                  | Default        | Description                                                                     |
|-------------------------|----------------|---------------------------------------------------------------------------------|
|`SECURE_UNLOCK_TIMEOUT`  | `5000`         | Timeout for the user to perform the configured unlock sequence - `0` to disable |
|`SECURE_IDLE_TIMEOUT`    | `60000`        | Timeout while unlocked before returning to locked - `0` to disable              |
|`SECURE_UNLOCK_SEQUENCE` | `{ { 0, 0 } }` | Array of matrix locations describing a sequential sequence of keypresses        |

## Functions

| Function                  | Description                                                                |
|---------------------------|----------------------------------------------------------------------------|
| `secure_is_locked()`      | Check if the device is currently locked                                    |
| `secure_is_unlocking()`   | Check if an unlock sequence is currently in progress                       |
| `secure_is_unlocked()`    | Check if the device is currently unlocked                                  |
| `secure_lock()`           | Lock down the device                                                       |
| `secure_unlock()`         | Force unlock the device - bypasses user unlock sequence                    |
| `secure_request_unlock()` | Begin listening for an unlock sequence                                     |
| `secure_activity_event()` | Flag that user activity has happened and the device should remain unlocked |
