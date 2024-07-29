#include "snaptap.h"

void add_snap_tap_entry(SNAP_TAP_T **head, uint16_t keycode, uint16_t opposing_keycode)
{
    SNAP_TAP_T *new_entry = (SNAP_TAP_T*)malloc(sizeof(SNAP_TAP_T));
    SNAP_TAP_T *last = *head;

    new_entry->keycode = keycode;
    new_entry->opposing_keycode = opposing_keycode;
    new_entry->next = NULL;

    if (*head == NULL)
    {
        *head = new_entry;
        return;
    }

    while (last->next != NULL)
    {
        last = last->next;
    }

    last->next = new_entry;
}

SNAP_TAP_T *find_snap_tap_entry(SNAP_TAP_T *head, uint16_t keycode)
{
    SNAP_TAP_T *current = head;

    while (current != NULL)
    {
        if (current->keycode == keycode)
        {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

void clear_snap_tap_entries(SNAP_TAP_T **head)
{
    SNAP_TAP_T *current = *head;
    SNAP_TAP_T *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

uint16_t random_delay(uint16_t min, uint16_t max) 
{
    return min + (rand() % (max - min + 1));
}

bool snap_tap_handler(SNAP_TAP_T *head, uint16_t keycode, keyrecord_t *record)
{
    SNAP_TAP_T *entry = find_snap_tap_entry(head, keycode);
    bool default_key = true;
    
    if (entry != NULL)
    {
        SNAP_TAP_T *opposing_entry = find_snap_tap_entry(head, entry->opposing_keycode);

        if (opposing_entry == NULL)
        {
            /* Everything is borken, help plz. */
            return true;
        }

        if (record->event.pressed)
        {
            entry->pressed = true;

            if (opposing_entry->pressed)
            {
                unregister_code(opposing_entry->keycode);
                wait_ms(random_delay(random_delay(2,9), random_delay(24,38)));
            }

            register_code(entry->keycode);
        }
        else
        {
            entry->pressed = false;

            unregister_code(entry->keycode);

            if (opposing_entry->pressed)
            {
                wait_ms(random_delay(random_delay(2,9), random_delay(24,38)));
                register_code(opposing_entry->keycode);
            }

            unregister_code(entry->keycode);
        }

        default_key = false;
    }

    return default_key;
}

bool building_snap_tap = false;
uint16_t keycodes_arr[2] = {0};
uint8_t num_keycodes = 0;

bool snap_tap_wrapper(SNAP_TAP_T *head, uint16_t keycode, keyrecord_t *record)
{
    if (building_snap_tap && record->event.pressed)
    {
        keycodes_arr[num_keycodes] = keycode;
        num_keycodes++;

        if (num_keycodes == 2)
        {
            if (keycodes_arr[0] != keycodes_arr[1] &&
                find_snap_tap_entry(head, keycodes_arr[0]) == NULL &&
                find_snap_tap_entry(head, keycodes_arr[1]) == NULL)
            {
                add_snap_tap_entry(&head, keycodes_arr[0], keycodes_arr[1]);
                add_snap_tap_entry(&head, keycodes_arr[1], keycodes_arr[0]);
            }
            building_snap_tap = false;
        }

        return false;
    }

    if (!snap_tap_handler(head, keycode, record))
    {
        return false;
    }

    switch (keycode)
    {
        case BUILD_SNAPS:
            if (record->event.pressed)
            {
                building_snap_tap = true;
                num_keycodes = 0;
            }
            else
            {
                building_snap_tap = false;
            }
            break;
    default:
        break;
    }

    return true;
}