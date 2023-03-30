/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdlib.h>
#include "pico/util/pheap.h"

pheap_t *ph_create(uint max_nodes, pheap_comparator comparator, void *user_data) {
    invalid_params_if(PHEAP, !max_nodes || max_nodes >= (1u << (8 * sizeof(pheap_node_id_t))));
    pheap_t *heap = calloc(1, sizeof(pheap_t));
    heap->nodes = calloc(max_nodes, sizeof(pheap_node_t));
    ph_post_alloc_init(heap, max_nodes, comparator, user_data);
    return heap;
}

void ph_post_alloc_init(pheap_t *heap, uint max_nodes, pheap_comparator comparator, void *user_data) {
    invalid_params_if(PHEAP, !max_nodes || max_nodes >= (1u << (8 * sizeof(pheap_node_id_t))));
    heap->max_nodes = (pheap_node_id_t) max_nodes;
    heap->comparator = comparator;
    heap->user_data = user_data;
    ph_clear(heap);
}

void ph_clear(pheap_t *heap) {
    heap->root_id = 0;
    heap->free_head_id = 1;
    heap->free_tail_id = heap->max_nodes;
    for(pheap_node_id_t i = 1; i < heap->max_nodes; i++) {
        ph_get_node(heap, i)->sibling = (pheap_node_id_t)(i + 1);
    }
    ph_get_node(heap, heap->max_nodes)->sibling = 0;
}

void ph_destroy(pheap_t *heap) {
    free(heap->nodes);
    free(heap);
}

pheap_node_id_t ph_merge_two_pass(pheap_t *heap, pheap_node_id_t id) {
    if (!id || !ph_get_node(heap, id)->sibling) {
        return id;
    } else {
        pheap_node_id_t a, b, new_node;
        a = id;
        b = ph_get_node(heap, id)->sibling;
        new_node = ph_get_node(heap, b)->sibling;
        ph_get_node(heap, a)->sibling = ph_get_node(heap, b)->sibling = 0;
        return ph_merge_nodes(heap, ph_merge_nodes(heap, a, b), ph_merge_two_pass(heap, new_node));
    }
}

static pheap_node_id_t ph_remove_any_head(pheap_t *heap, pheap_node_id_t root_id, bool free) {
    assert(root_id);
//    printf("Removing head %d (parent %d sibling %d)\n", root_id, ph_get_node(heap, root_id)->parent, ph_get_node(heap, root_id)->sibling);
    assert(!ph_get_node(heap, root_id)->sibling);
    assert(!ph_get_node(heap, root_id)->parent);
    pheap_node_id_t new_root_id = ph_merge_two_pass(heap, ph_get_node(heap, root_id)->child);
    if (free) {
        if (heap->free_tail_id) {
            ph_get_node(heap, heap->free_tail_id)->sibling = root_id;
        }
        if (!heap->free_head_id) {
            assert(!heap->free_tail_id);
            heap->free_head_id = root_id;
        }
        heap->free_tail_id = root_id;
    }
    if (new_root_id) ph_get_node(heap, new_root_id)->parent = 0;
    ph_get_node(heap, root_id)->sibling = 0;
    return new_root_id;
}

pheap_node_id_t ph_remove_head(pheap_t *heap, bool free) {
    pheap_node_id_t old_root_id = ph_peek_head(heap);
    heap->root_id = ph_remove_any_head(heap, old_root_id, free);
    return old_root_id;
}

bool ph_remove_and_free_node(pheap_t *heap, pheap_node_id_t id) {
    // 1) trivial cases
    if (!id) return false;
    if (id == heap->root_id) {
        ph_remove_and_free_head(heap);
        return true;
    }
    // 2) unlink the node from the tree
    pheap_node_t *node = ph_get_node(heap, id);
    if (!node->parent) return false; // not in tree
    pheap_node_t *parent = ph_get_node(heap, node->parent);
    if (parent->child == id) {
        parent->child = node->sibling;
    } else {
        pheap_node_id_t prev_sibling_id = parent->child;
        bool __unused found = false;
        do {
            pheap_node_t *prev_sibling = ph_get_node(heap, prev_sibling_id);
            if (prev_sibling->sibling == id) {
                prev_sibling->sibling = node->sibling;
                found = true;
                break;
            }
            prev_sibling_id = prev_sibling->sibling;
        } while (prev_sibling_id);
        assert(found);
    }
    node->sibling = node->parent = 0;
//    ph_dump(heap, NULL, NULL);
    // 3) remove it from the head of its own subtree
    pheap_node_id_t new_sub_tree = ph_remove_any_head(heap, id, true);
    assert(new_sub_tree != heap->root_id);
    heap->root_id = ph_merge_nodes(heap, heap->root_id, new_sub_tree);
    return true;
}

static uint ph_dump_node(pheap_t *heap, pheap_node_id_t id, void (*dump_key)(pheap_node_id_t, void *), void *user_data, uint indent) {
    uint count = 0;
    if (id) {
        count++;
        for (uint i = 0; i < indent * 2; i++) {
            putchar(' ');
        }
        pheap_node_t *node = ph_get_node(heap, id);
        printf("%d (c=%d s=%d p=%d) ", id, node->child, node->sibling, node->parent);
        if (dump_key) dump_key(id, user_data);
        printf("\n");
        count += ph_dump_node(heap, node->child, dump_key, user_data, indent + 1);
        count += ph_dump_node(heap, node->sibling, dump_key, user_data, indent);
    }
    return count;
}

void ph_dump(pheap_t *heap, void (*dump_key)(pheap_node_id_t, void *), void *user_data) {
    uint count = ph_dump_node(heap, heap->root_id, dump_key, user_data, 0);
    printf("node_count %d\n", count);
}