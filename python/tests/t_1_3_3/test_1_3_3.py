import os
from unittest import TestCase

import mixal


class TestSample(TestCase):

    def setUp(self) -> None:
        self.computer = mixal.Computer()

    def load_codes(self, name):
        current_path = os.path.dirname(os.path.abspath(__file__))
        file_path = os.path.join(current_path, name + ".mix")
        with open(file_path) as reader:
            self.computer.load_codes(reader.read())

    def init_input_device(self, device, text):
        for i in range(0, len(text), 5):
            self.computer.get_device_word_at(device, i // 5).set(text[i : i + 5])

    def test_a_multiply_permutations_in_cycle_form(self):
        self.load_codes("a_multiply_permutations_in_cycle_form")
        input_text = (
            "    (  A    C    F    G  )        (  B    C    D  )        (  A    E    D  )    "
            "    (  F    A    D    E  )        (  B    G    F    A    E  )                  ="
        )
        self.init_input_device(16, input_text)
        self.computer.execute_until_halt()
        output = ""
        for i in range(48, 58):
            output += self.computer.get_device_word_at(18, i).get_chars()
        self.assertEqual("    (  A    D    G  )        (  C    E    B  )    ", output)
        print("Cost:", self.computer.elapsed())

    def test_b_same_effects_as_a(self):
        self.load_codes("b_same_effects_as_a")
        input_text = (
            "    (  A    C    F    G  )        (  B    C    D  )        (  A    E    D  )    "
            "    (  F    A    D    E  )        (  B    G    F    A    E  )                  ="
        )
        self.init_input_device(16, input_text)
        self.computer.execute_until_halt()
        output = ""
        for i in range(48, 58):
            output += self.computer.get_device_word_at(18, i).get_chars()
        self.assertEqual("    (  C    E    B  )        (  D    G    A  )    ", output)
        print("Cost:", self.computer.elapsed())

    def test_i_inverse_in_space(self):
        self.load_codes("i_inverse_in_space")
        self.computer.execute_until_halt()
        expected = [3, 2, 6, 5, 4, 1]
        for i, val in enumerate(expected):
            self.assertEqual(val, self.computer.memory_at(1001 + i).value())
        print("Cost:", self.computer.elapsed())

    def test_j_analogous_to_program_i(self):
        self.load_codes("j_analogous_to_program_i")
        self.computer.execute_until_halt()
        expected = [3, 2, 6, 5, 4, 1]
        for i, val in enumerate(expected):
            self.assertEqual(val, self.computer.memory_at(1001 + i).value())
        print("Cost:", self.computer.elapsed())
