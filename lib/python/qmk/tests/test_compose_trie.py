import qmk.cli.compose


def test_multiple_inserts_accepted():
    trie = qmk.cli.compose.ComposeTrie()
    trie.insert(['KC_A', 'KC_B'], 'ab')
    trie.insert(['KC_A', 'KC_C'], 'ac')
    # No throw!


def test_throws_on_super_sequence_insert():
    trie = qmk.cli.compose.ComposeTrie()
    trie.insert(['KC_A', 'KC_B'], 'ab')
    try:
        trie.insert(['KC_A', 'KC_B', 'KC_C'], 'abc')
    except qmk.cli.compose.ComposeSequencePrefixCollision as e:
        assert e.args[0] == ['KC_A', 'KC_B']
        pass
    else:
        assert False


def test_throws_on_sub_sequence_insert():
    trie = qmk.cli.compose.ComposeTrie()
    trie.insert(['KC_A', 'KC_B', 'KC_C'], 'abc')
    try:
        trie.insert(['KC_A', 'KC_B'], 'ab')
    except qmk.cli.compose.ComposeSequencePrefixCollision as e:
        assert e.args[0] == ['KC_A', 'KC_B']
        pass
    else:
        assert False