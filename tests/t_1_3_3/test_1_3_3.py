import os
from unittest import TestCase
import mixal


class TestSample(TestCase):

    def setUp(self) -> None:
        self.computer = mixal.Computer()

    def load_codes(self, name):
        current_path = os.path.dirname(os.path.abspath(__file__))
        file_path = os.path.join(current_path, name + '.mix')
        with open(file_path) as reader:
            self.computer.loadCodes(reader.read())

    def init_input_device(self, device, text):
        for i in range(0, len(text), 5):
            self.computer.getDeviceWordAt(device, i // 5).set(text[i:i + 5])

    def test_a_multiply_permutations_in_cycle_form(self):
        self.load_codes('a_multiply_permutations_in_cycle_form')
        input_text = '    (  A    C    F    G  )        (  B    C    D  )        (  A    E    D  )    ' \
                     '    (  F    A    D    E  )        (  B    G    F    A    E  )                  ='
        self.init_input_device(16, input_text)
        self.computer.executeUntilHalt()
        output = ''
        for i in range(48, 58):
            output += self.computer.getDeviceWordAt(18, i).getCharacters()
        self.assertEqual('    (  A    D    G  )        (  C    E    B  )    ', output)
        print('Cost:', self.computer.elapsed())
