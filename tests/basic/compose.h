// Auto-generated from tests/basic/compose.conf.
// DO NOT EDIT MANUALLY
const ComposeTrie compose_trie = {
.keycode = KC_A,
.child = &(struct ComposeTrie)
    {
    .keycode = KC_B,
    .output = "ccc",
    .sibling = &(struct ComposeTrie)
        {
        .keycode = KC_EQL,
        .output = "123",
        }
    ,
    }
,
}
;