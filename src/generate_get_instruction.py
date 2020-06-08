OPS = [
    'NOP',
    'LDA',
    'LD1',
    'LD2',
    'LD3',
    'LD4',
    'LD5',
    'LD6',
    'LDX',
]


class Trie(object):

    def __init__(self):
        self.head = {}

    def add_word(self, word):
        head = self.head
        for ch in word:
            if ch not in head:
                head[ch] = {}
            head = head[ch]

    def print_cases(self):
        def _print(head, indent, index, word):
            if len(head) == 0:
                print(' ' * indent + 'return Instructions::{};'.format(word))
                return False
            print(' ' * indent + 'switch (std::toupper(name[{}])) {{'.format(index))
            for ch in sorted(head.keys()):
                print(' ' * indent + 'case \'{}\':'.format(ch))
                if _print(head[ch], indent + 4, index + 1, word + ch):
                    print(' ' * (indent + 4) + 'break;')
            print(' ' * indent + '}')
            return True
        _print(self.head, indent=4, index=0, word='')
        

if __name__ == '__main__':
    trie = Trie()
    for op in OPS:
        trie.add_word(op)
    trie.print_cases()
