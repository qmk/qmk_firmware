"""QMK CLI compose trie compiler
"""

from argparse import FileType
from milc import cli
import shlex


class ComposeTrie:
    def __init__(self, indent=0):
        self.keycode = None
        self.output = None
        self.sibling = None
        self.child = None
        self.indent = indent

    def insert(self, keycodes, output):
        if not self.keycode:
            self.keycode = keycodes[0]
        # TODO(agdphd/anyone): Throw if one sequence is a prefix of another
        if len(keycodes) == 1 and self.keycode == keycodes[0]:
            # End of the line! Record the output and exit.
            self.output = output
            return
        if self.keycode == keycodes[0]:
            # We're at the right node at this level. Descend to the child.
            if self.child is None:
                self.child = ComposeTrie(self.indent + 1)
            self.child.insert(keycodes[1:], output)
        else:
            # This isn't the right node at this level. Walk siblings until we find it.
            if self.sibling is None:
                self.sibling = ComposeTrie(self.indent + 1)
            self.sibling.insert(keycodes, output)

    def compile(self):
        indent = self.indent * 4 * ' '
        lines = [f"{indent}{{\n"]
        lines.append(f"{indent}.keycode = {self.keycode},\n")
        if self.output:
            lines.append(f"{indent}.output = {self.output},\n")
        if self.sibling:
            lines.append(f"{indent}.sibling = &(struct ComposeTrie)\n")
            lines.extend(self.sibling.compile())
            lines.append(f"{indent},\n")
        if self.child:
            lines.append(f"{indent}.child = &(struct ComposeTrie)\n")
            lines.extend(self.child.compile())
            lines.append(f"{indent},\n")
        lines.append(f"{indent}}}\n")
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
        trie.insert(keycodes, output)
    lines = trie.compile()
    lines[0] = "const ComposeTrie compose_trie =" + lines[0]
    lines.append(";")
    cli.args.outfile.writelines(lines)
