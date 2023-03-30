/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_UTIL_PHEAP_H
#define _PICO_UTIL_PHEAP_H

#include "pico.h"

#ifdef __cplusplus
extern "C" {
#endif

// PICO_CONFIG: PARAM_ASSERTIONS_ENABLED_PHEAP, Enable/disable assertions in the pheap module, type=bool, default=0, group=pico_util
#ifndef PARAM_ASSERTIONS_ENABLED_PHEAP
#define PARAM_ASSERTIONS_ENABLED_PHEAP 0
#endif

/**
 * \file pheap.h
 * \defgroup util_pheap pheap
 * Pairing Heap Implementation
 * \ingroup pico_util
 *
 * pheap defines a simple pairing heap. The implementation simply tracks array indexes, it is up to
 * the user to provide storage for heap entries and a comparison function.
 *
 * NOTE: This class is not safe for concurrent usage. It should be externally protected. Furthermore
 * if used concurrently, the caller needs to protect around their use of the returned id.
 * For example, ph_remove_and_free_head returns the id of an element that is no longer in the heap.
 * The user can still use this to look at the data in their companion array, however obviously further operations
 * on the heap may cause them to overwrite that data as the id may be reused on subsequent operations
 *
 */
// PICO_CONFIG: PICO_PHEAP_MAX_ENTRIES, Maximum number of entries in the pheap, min=1, max=65534, default=255, group=pico_util
#ifndef PICO_PHEAP_MAX_ENTRIES
#define PICO_PHEAP_MAX_ENTRIES 255
#endif

// public heap_node ids are numbered from 1 (0 means none)
#if PICO_PHEAP_MAX_ENTRIES < 256
typedef uint8_t pheap_node_id_t;
#elif PICO_PHEAP_MAX_ENTRIES < 65535
typedef uint16_t pheap_node_id_t;
#else
#error invalid PICO_PHEAP_MAX_ENTRIES
#endif

typedef struct pheap_node {
    pheap_node_id_t child, sibling, parent;
} pheap_node_t;

/**
 * A user comparator function for nodes in a pairing heap.
 *
 * \return true if a < b in natural order. Note this relative ordering must be stable from call to call.
 */
typedef bool (*pheap_comparator)(void *user_data, pheap_node_id_t a, pheap_node_id_t b);

typedef struct pheap {
    pheap_node_t *nodes;
    pheap_comparator comparator;
    void *user_data;
    pheap_node_id_t max_nodes;
    pheap_node_id_t root_id;
    // we remove from head and add to tail to stop reusing the same ids
    pheap_node_id_t free_head_id;
    pheap_node_id_t free_tail_id;
} pheap_t;

/**
 * Create a pairing heap, which effectively maintains an efficient sorted ordering
 * of nodes. The heap itself stores no user per-node state, it is expected
 * that the user maintains a companion array. A comparator function must
 * be provided so that the heap implementation can determine the relative ordering of nodes
 *
 * \param max_nodes the maximum number of nodes that may be in the heap (this is bounded by
 *                  PICO_PHEAP_MAX_ENTRIES which defaults to 255 to be able to store indexes
 *                  in a single byte).
 * \param comparator the node comparison function
 * \param user_data a user data pointer associated with the heap that is provided in callbacks
 * \return a newly allocated and initialized heap
 */
pheap_t *ph_create(uint max_nodes, pheap_comparator comparator, void *user_data);

/**
 * Removes all nodes from the pairing heap
 * \param heap the heap
 */
void ph_clear(pheap_t *heap);

/**
 * De-allocates a pairing heap
 *
 * Note this method must *ONLY* be called on heaps created by ph_create()
 * \param heap the heap
 */
void ph_destroy(pheap_t *heap);

// internal method
static inline pheap_node_t *ph_get_node(pheap_t *heap, pheap_node_id_t id) {
    assert(id && id <= heap->max_nodes);
    return heap->nodes + id - 1;
}

// internal method
static void ph_add_child_node(pheap_t *heap, pheap_node_id_t parent_id, pheap_node_id_t child_id) {
    pheap_node_t *n = ph_get_node(heap, parent_id);
    assert(parent_id);
    assert(child_id);
    assert(parent_id != child_id);
    pheap_node_t *c = ph_get_node(heap, child_id);
    c->parent = parent_id;
    if (!n->child) {
        n->child = child_id;
    } else {
        c->sibling = n->child;
        n->child = child_id;
    }
}

// internal method
static pheap_node_id_t ph_merge_nodes(pheap_t *heap, pheap_node_id_t a, pheap_node_id_t b) {
    if (!a) return b;
    if (!b) return a;
    if (heap->comparator(heap->user_data, a, b)) {
        ph_add_child_node(heap, a, b);
        return a;
    } else {
        ph_add_child_node(heap, b, a);
        return b;
    }
}

/**
 * Allocate a new node from the unused space in the heap
 *
 * \param heap the heap
 * \return an identifier for the node, or 0 if the heap is full
 */
static inline pheap_node_id_t ph_new_node(pheap_t *heap) {
    if (!heap->free_head_id) return 0;
    pheap_node_id_t id = heap->free_head_id;
    pheap_node_t *hn = ph_get_node(heap, id);
    heap->free_head_id = hn->sibling;
    if (!heap->free_head_id) heap->free_tail_id = 0;
    hn->child = hn->sibling = hn->parent = 0;
    return id;
}

/**
 * Inserts a node into the heap.
 *
 * This method inserts a node (previously allocated by ph_new_node())
 * into the heap, determining the correct order by calling
 * the heap's comparator
 *
 * \param heap the heap
 * \param id the id of the node to insert
 * \return the id of the new head of the pairing heap (i.e. node that compares first)
 */
static inline pheap_node_id_t ph_insert_node(pheap_t *heap, pheap_node_id_t id) {
    assert(id);
    pheap_node_t *hn = ph_get_node(heap, id);
    hn->child = hn->sibling = hn->parent = 0;
    heap->root_id = ph_merge_nodes(heap, heap->root_id, id);
    return heap->root_id;
}

/**
 * Returns the head node in the heap, i.e. the node
 * which compares first, but without removing it from the heap.
 *
 * \param heap the heap
 * \return the current head node id
 */
static inline pheap_node_id_t ph_peek_head(pheap_t *heap) {
    return heap->root_id;
}

/**
 * Remove the head node from the pairing heap. This head node is
 * the node which compares first in the logical ordering provided
 * by the comparator.
 *
 * Note that in the case of free == true, the returned id is no longer
 * allocated and may be re-used by future node allocations, so the caller
 * should retrieve any per node state from the companion array before modifying
 * the heap further.
 *
 * @param heap the heap
 * @param free true if the id is also to be freed; false if not - useful if the caller
 *        may wish to re-insert an item with the same id)
 * @return the old head node id.
 */
pheap_node_id_t ph_remove_head(pheap_t *heap, bool free);

/**
 * Remove the head node from the pairing heap. This head node is
 * the node which compares first in the logical ordering provided
 * by the comparator.
 *
 * Note that the returned id will be freed, and thus may be re-used by future node allocations,
 * so the caller should retrieve any per node state from the companion array before modifying
 * the heap further.
 *
 * @param heap the heap
 * @return the old head node id.
 */
static inline pheap_node_id_t ph_remove_and_free_head(pheap_t *heap) {
    return ph_remove_head(heap, true);
}

/**
 * Remove and free an arbitrary node from the pairing heap. This is a more
 * costly operation than removing the head via ph_remove_and_free_head()
 *
 * @param heap the heap
 * @param id the id of the node to free
 * @return true if the the node was in the heap, false otherwise
 */
bool ph_remove_and_free_node(pheap_t *heap, pheap_node_id_t id);

/**
 * Determine if the heap contains a given node. Note containment refers
 * to whether the node is inserted (ph_insert_node()) vs allocated (ph_new_node())
 *
 * @param heap the heap
 * @param id the id of the node
 * @return true if the heap contains a node with the given id, false otherwise.
 */
static inline bool ph_contains_node(pheap_t *heap, pheap_node_id_t id) {
    return id == heap->root_id || ph_get_node(heap, id)->parent;
}


/**
 * Free a node that is not currently in the heap, but has been allocated
 *
 * @param heap the heap
 * @param id the id of the node
 */
static inline void ph_free_node(pheap_t *heap, pheap_node_id_t id) {
    assert(id && !ph_contains_node(heap, id));
    if (heap->free_tail_id) {
        ph_get_node(heap, heap->free_tail_id)->sibling = id;
    }
    if (!heap->free_head_id) {
        assert(!heap->free_tail_id);
        heap->free_head_id = id;
    }
    heap->free_tail_id = id;
}

/**
 * Print a representation of the heap for debugging
 *
 * @param heap the heap
 * @param dump_key a method to print a node value
 * @param user_data the user data to pass to the dump_key method
 */
void ph_dump(pheap_t *heap, void (*dump_key)(pheap_node_id_t id, void *user_data), void *user_data);

/**
 * Initialize a statically allocated heap (ph_create() using the C heap).
 * The heap member `nodes` must be allocated of size max_nodes.
 *
 * @param heap the heap
 * @param max_nodes the max number of nodes in the heap (matching the size of the heap's nodes array)
 * @param comparator the comparator for the heap
 * @param user_data the user data for the heap.
 */
void ph_post_alloc_init(pheap_t *heap, uint max_nodes, pheap_comparator comparator, void *user_data);

/**
 * Define a statically allocated pairing heap. This must be initialized
 * by ph_post_alloc_init
 */
#define PHEAP_DEFINE_STATIC(name, _max_nodes) \
    static_assert(_max_nodes && _max_nodes < (1u << (8 * sizeof(pheap_node_id_t))), ""); \
    static pheap_node_t name ## _nodes[_max_nodes]; \
    static pheap_t name = { \
            .nodes = name ## _nodes, \
            .max_nodes = _max_nodes \
    };


#ifdef __cplusplus
}
#endif

#endif
