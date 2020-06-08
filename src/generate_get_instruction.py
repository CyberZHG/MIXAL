OPS = [
    'NOP',
    'LDA',
    'LDX',
]


class Trie(object):

    def __init__(self):
        self.head = [None] * 26

    def add_word(self, word):
        head = self.head
        for ch in word:
            ch = ord(ch) - ord('A')
            if head[ch] is None:
                head[ch] = [None] * 26
            head = head[ch]

    def print_cases(self):
        def _print(head, indent, index, word):
            if all(map(lambda x: x is None, head)):
                print(' ' * indent + 'return Instructions::{};'.format(word))
                return False
            print(' ' * indent + 'switch (std::toupper(name[{}])) {{'.format(index))
            for i in range(len(head)):
                if head[i] is None:
                    continue
                ch = chr(i + ord('A'))
                print(' ' * indent + 'case \'{}\':'.format(ch))
                if _print(head[i], indent + 4, index + 1, word + ch):
                    print(' ' * (indent + 4) + 'break;')
            print(' ' * indent + '}')
            return True
        _print(self.head, indent=4, index=0, word='')
        

if __name__ == '__main__':
    trie = Trie()
    for op in OPS:
        trie.add_word(op)
    trie.print_cases()
