'''QMK CLI compose trie compiler
'''

from argparse import FileType
from milc import cli
import shlex


class ComposeSequencePrefixCollision(Exception):
    """Raised when one configured compose sequence is a prefix of another."""
    pass


class ComposeTrie:
    """Prefix trie for storing compose sequences.
    
    Implementation deliberately mirrors the one in process_compose.h since the
    goal is to compile to C source that statically initializes a trie at
    keyboard boot time.
    """
    def __init__(self, indent=0):
        self.keycode = None
        self.output = None
        self.sibling = None
        self.child = None
        self.indent = indent

    def insert(self, keycodes, output, prefix=None):
        """Add a new compose sequence to the trie.
        
        NOTE: Called recursively to descend the trie during insertion.
        """
        if not prefix:
            prefix = []

        if not self.keycode:
            self.keycode = keycodes[0]

        if self.keycode != keycodes[0]:
            # This isn't the right node at this level. Walk siblings until we find it.
            if self.sibling is None:
                self.sibling = ComposeTrie(self.indent + 1)
            self.sibling.insert(keycodes, output, prefix)
            return

        prefix.append(keycodes[0])

        if len(keycodes) == 1 and self.keycode == keycodes[0]:
            # End of the line! Throw if another sequence has this prefix.
            if self.child:
                raise ComposeSequencePrefixCollision(prefix)
            # Otherwise, record the output and exit.
            self.output = output

        # If another sequence ended here, throw.
        elif self.output:
            raise ComposeSequencePrefixCollision(prefix)

        # Otherwise, we're at the right node at this level. Descend to the child.
        else:
            if self.child is None:
                self.child = ComposeTrie(self.indent + 1)
            self.child.insert(keycodes[1:], output, prefix)

        prefix.pop()

    # TODO(unassigned/agdphd): Write integration tests that validate C code.
    def compile(self):
        """Build C source that statically initializes a ComposeTrie."""
        indent = self.indent * 4 * ' '
        lines = [f'{indent}{{\n']
        lines.append(f'{indent}.keycode = {self.keycode},\n')
        if self.output:
            lines.append(f'{indent}.output = "{self.output}",\n'.replace("\\", "\\\\"))
        if self.sibling:
            lines.append(f'{indent}.sibling = &(struct ComposeTrie)\n')
            lines.extend(self.sibling.compile())
            lines.append(f'{indent},\n')
        if self.child:
            lines.append(f'{indent}.child = &(struct ComposeTrie)\n')
            lines.extend(self.child.compile())
            lines.append(f'{indent},\n')
        lines.append(f'{indent}}}\n')
        return lines


@cli.argument('outfile', arg_only=True, type=FileType('w'), help='Output file for compose trie C code')
@cli.argument('infile', arg_only=True, type=FileType('r'), help='Compose key configuration to compile')
@cli.subcommand('Compile a compose key trie.')
def compose(cli):
    trie = ComposeTrie()
    for line in cli.args.infile:
        parsed_line = shlex.split(line, comments=True)
        if len(parsed_line) < 2:
            continue
        *keycodes, output = parsed_line
        try:
            trie.insert(keycodes, output)
        except ComposeSequencePrefixCollision as e:
            cli.log.error(f'Compose sequence {e.args[0]} is a prefix of another sequence. Aborting.')
            return False
    lines = [f'// Auto-generated from {cli.args.infile.name}.\n', '// DO NOT EDIT MANUALLY\n', 'const ComposeTrie compose_trie = ']
    lines.extend(trie.compile())
    lines.append(';')
    cli.args.outfile.writelines(lines)
