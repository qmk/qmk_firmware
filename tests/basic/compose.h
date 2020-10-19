// Auto-generated from tests/basic/compose.conf.
// DO NOT EDIT MANUALLY
const FLASHMEM ComposeTrie* const compose_trie = &(const FLASHMEM struct ComposeTrie) {
.keycode = KC_A,
.child = &(const FLASHMEM struct ComposeTrie)
    {
    .keycode = KC_B,
    .output = (const FLASHMEM char[]) {"ccc"},
    .sibling = &(const FLASHMEM struct ComposeTrie)
        {
        .keycode = KC_EQL,
        .output = (const FLASHMEM char[]) {"123"},
        }
    ,
    }
,
}
;