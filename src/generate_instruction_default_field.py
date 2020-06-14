FIELDS = {
    'FADD': 6,
    'FSUB': 6,
    'FMUL': 6,
    'FDIV': 6,
    'NUM': 0, 'CHAR': 1, 'HLT': 2,
    'SLA': 0, 'SRA': 1, 'SLAX': 2, 'SRAX': 3, 'SLC': 4, 'SRC': 5,
    'STJ': 2,
    'JMP': 0, 'JSJ': 1, 'JOV': 2, 'JNOV': 3, 'JL': 4, 'JE': 5, 'JG': 6, 'JGE': 7, 'JNE': 8, 'JLE': 9,
    'JAN': 0, 'JAZ': 1, 'JAP': 2, 'JANN': 3, 'JANZ': 4, 'JANP': 5,
    'J1N': 0, 'J1Z': 1, 'J1P': 2, 'J1NN': 3, 'J1NZ': 4, 'J1NP': 5,
    'J2N': 0, 'J2Z': 1, 'J2P': 2, 'J2NN': 3, 'J2NZ': 4, 'J2NP': 5,
    'J3N': 0, 'J3Z': 1, 'J3P': 2, 'J3NN': 3, 'J3NZ': 4, 'J3NP': 5,
    'J4N': 0, 'J4Z': 1, 'J4P': 2, 'J4NN': 3, 'J4NZ': 4, 'J4NP': 5,
    'J5N': 0, 'J5Z': 1, 'J5P': 2, 'J5NN': 3, 'J5NZ': 4, 'J5NP': 5,
    'J6N': 0, 'J6Z': 1, 'J6P': 2, 'J6NN': 3, 'J6NZ': 4, 'J6NP': 5,
    'JXN': 0, 'JXZ': 1, 'JXP': 2, 'JXNN': 3, 'JXNZ': 4, 'JXNP': 5,
    'INCA': 0, 'DECA': 1, 'ENTA': 2, 'ENNA': 3,
    'INC1': 0, 'DEC1': 1, 'ENT1': 2, 'ENN1': 3,
    'INC2': 0, 'DEC2': 1, 'ENT2': 2, 'ENN2': 3,
    'INC3': 0, 'DEC3': 1, 'ENT3': 2, 'ENN3': 3,
    'INC4': 0, 'DEC4': 1, 'ENT4': 2, 'ENN4': 3,
    'INC5': 0, 'DEC5': 1, 'ENT5': 2, 'ENN5': 3,
    'INC6': 0, 'DEC6': 1, 'ENT6': 2, 'ENN6': 3,
    'INCX': 0, 'DECX': 1, 'ENTX': 2, 'ENNX': 3,
    'FCMP': 6,
}


class Trie(object):

    def __init__(self):
        self.head = {}

    def add_word(self, word, field):
        head = self.head
        for ch in word:
            if ch not in head:
                head[ch] = [-1, {}]
            if ch == '#':
                head[ch][0] = field
            head = head[ch][1]

    def print_cases(self):
        def _print(head, indent, index, field):
            if len(head) == 0:
                print(' ' * indent + 'return {};'.format(field))
                return False
            print(' ' * indent + 'switch (charAt({})) {{'.format(index))
            for ch in sorted(head.keys()):
                print(' ' * indent + 'case \'{}\':'.format(ch))
                if _print(head[ch][1], indent + 4, index + 1, head[ch][0]):
                    print(' ' * (indent + 4) + 'break;')
            print(' ' * indent + '}')
            return True

        _print(self.head, indent=4, index=0, field=-1)


if __name__ == '__main__':
    trie = Trie()
    for op, field in FIELDS.items():
        trie.add_word(op + '#', field)
    trie.print_cases()
