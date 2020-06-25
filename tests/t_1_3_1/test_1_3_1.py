import os
import random
from unittest import TestCase
import mixal


class TestSample(TestCase):

    def setUp(self) -> None:
        self.machine = mixal.Machine()

    def load_codes(self, name):
        current_path = os.path.dirname(os.path.abspath(__file__))
        file_path = os.path.join(current_path, name + '.mix')
        with open(file_path) as reader:
            self.machine.loadCodes(reader.read().split('\n'))

    def test_16_set_all_zeros_a(self):
        self.load_codes('16_set_all_zeros_a')
        for i in range(100):
            self.machine.memoryAt(i).set(random.randint(1, 100))
        self.machine.executeUntilHalt()
        for i in range(100):
            self.assertEqual(0, self.machine.memoryAt(i).value(), i)
        print('Cost:', self.machine.elapsed())

    def test_17_set_all_zeros_with_n_a(self):
        max_case_num = 10
        for cases in range(max_case_num):
            self.load_codes('17_set_all_zeros_with_n_a')
            n = 0
            if cases == max_case_num - 1:
                n = 2999
            elif cases > 0:
                n = random.randint(0, 3000)
            for i in range(3000):
                self.machine.memoryAt(i).set(random.randint(1, 100))
            self.machine.rI2().set(n)
            self.machine.executeUntilHalt()
            for i in range(n + 1):
                self.assertEqual(0, self.machine.memoryAt(i).value(), i)
            for i in range(n + 1, 3000):
                self.assertLess(0, self.machine.memoryAt(i).value(), i)
        print('Cost:', self.machine.elapsed())

    def test_17_set_all_zeros_with_n_b(self):
        max_case_num = 10
        for cases in range(max_case_num):
            self.load_codes('17_set_all_zeros_with_n_b')
            n = 0
            if cases == max_case_num - 1:
                n = 2999
            elif cases > 0:
                n = random.randint(0, 3000)
            for i in range(3000):
                self.machine.memoryAt(i).set(random.randint(1, 100))
            self.machine.rI2().set(n)
            self.machine.executeUntilHalt()
            for i in range(n + 1):
                self.assertEqual(0, self.machine.memoryAt(i).value(), i)
            for i in range(n + 1, 3000):
                self.assertLess(0, self.machine.memoryAt(i).value(), i)
        print('Cost:', self.machine.elapsed())

    def test_17_set_all_zeros_with_n_b_official(self):
        self.load_codes('17_set_all_zeros_with_n_b_official')
        n = 2999
        for i in range(3000):
            self.machine.memoryAt(i).set(random.randint(1, 100))
        self.machine.rI2().set(n)
        self.machine.executeUntilHalt()
        for i in range(n + 1):
            self.assertEqual(0, self.machine.memoryAt(i).value(), i)
        for i in range(n + 1, 3000):
            self.assertLess(0, self.machine.memoryAt(i).value(), i)
        print('Cost:', self.machine.elapsed())

    def test_18_number_one(self):
        self.load_codes('18_number_one')
        self.machine.executeUntilHalt()
        self.assertEqual(42, self.machine.elapsed())

    def test_20_set_all_halt(self):
        self.load_codes('20_set_all_halt')
        self.machine.executeUntilHalt()
        for i in range(4000):
            self.assertEqual(133, self.machine.memoryAt(i).value())
        print('Exit:', self.machine.line())
        print('Cost:', self.machine.elapsed())
