"""Parse arbitrary math equations in a safe way.

Gratefully copied from https://stackoverflow.com/a/9558001
"""
import ast
import operator
from functools import lru_cache

# supported operators
operators = {
    ast.Add: operator.add,
    ast.Sub: operator.sub,
    ast.Mult: operator.mul,
    ast.Div: operator.truediv,
    ast.Pow: operator.pow,
    ast.BitXor: operator.xor,
    ast.USub: operator.neg,
}


@lru_cache(maxsize=0)
def compute(expr):
    """Parse a mathematical expression and return the answer.

    >>> compute('2^6')
    4
    >>> compute('2**6')
    64
    >>> compute('1 + 2*3**(4^5) / (6 + -7)')
    -5.0
    """
    return _eval(ast.parse(expr, mode='eval').body)


@lru_cache(maxsize=0)
def _eval(node):
    if isinstance(node, ast.Num):  # <number>
        return node.n
    elif isinstance(node, ast.BinOp):  # <left> <operator> <right>
        return operators[type(node.op)](_eval(node.left), _eval(node.right))
    elif isinstance(node, ast.UnaryOp):  # <operator> <operand> e.g., -1
        return operators[type(node.op)](_eval(node.operand))
    else:
        raise TypeError(node)
