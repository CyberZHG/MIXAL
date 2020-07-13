import os
import random
from unittest import TestCase
import mixal


class TestSample(TestCase):

    def setUp(self) -> None:
        self.computer = mixal.Computer()

    def load_codes(self, name):
        current_path = os.path.dirname(os.path.abspath(__file__))
        file_path = os.path.join(current_path, name + '.mix')
        with open(file_path) as reader:
            lines = reader.read().split('\n')
            self.computer.loadCodes(lines)

    def test_16_set_all_zeros_a(self):
        self.load_codes('16_set_all_zeros_a')
        for i in range(100):
            self.computer.memoryAt(i).set(random.randint(1, 100))
        self.computer.executeUntilHalt()
        for i in range(100):
            self.assertEqual(0, self.computer.memoryAt(i).value(), i)
        print('Cost:', self.computer.elapsed())

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
                self.computer.memoryAt(i).set(random.randint(1, 100))
            self.computer.rI2.set(n)
            self.computer.executeUntilHalt()
            for i in range(n + 1):
                self.assertEqual(0, self.computer.memoryAt(i).value(), i)
            for i in range(n + 1, 3000):
                self.assertLess(0, self.computer.memoryAt(i).value(), i)
        print('Cost:', self.computer.elapsed())

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
                self.computer.memoryAt(i).set(random.randint(1, 100))
            self.computer.rI2.set(n)
            self.computer.executeUntilHalt()
            for i in range(n + 1):
                self.assertEqual(0, self.computer.memoryAt(i).value(), i)
            for i in range(n + 1, 3000):
                self.assertLess(0, self.computer.memoryAt(i).value(), i)
        print('Cost:', self.computer.elapsed())

    def test_17_set_all_zeros_with_n_b_official(self):
        self.load_codes('17_set_all_zeros_with_n_b_official')
        n = 2999
        for i in range(3000):
            self.computer.memoryAt(i).set(random.randint(1, 100))
        self.computer.rI2.set(n)
        self.computer.executeUntilHalt()
        for i in range(n + 1):
            self.assertEqual(0, self.computer.memoryAt(i).value(), i)
        for i in range(n + 1, 3000):
            self.assertLess(0, self.computer.memoryAt(i).value(), i)
        print('Cost:', self.computer.elapsed())

    def test_18_number_one(self):
        self.load_codes('18_number_one')
        self.computer.executeUntilHalt()
        self.assertEqual(42, self.computer.elapsed())

    def test_20_set_all_halt(self):
        self.load_codes('20_set_all_halt')
        self.computer.executeUntilHalt()
        for i in range(4000):
            self.assertEqual(133, self.computer.memoryAt(i).value())
        print('Exit:', self.computer.line())
        print('Cost:', self.computer.elapsed())

    def test_21_set_rj(self):
        for _ in range(10):
            target = random.randint(1, 3000)
            randoms = [random.randint(0, 4096) for _ in range(3000)]
            self.load_codes('21_set_rj')
            self.computer.rI4.set(target)
            for i in range(3000):
                self.computer.memoryAt(i).set(randoms[i])
            self.computer.executeUntilHalt()
            self.assertEqual(target, self.computer.rJ.value())
            for i in range(3000):
                self.assertEqual(randoms[i], self.computer.memoryAt(i).value(), (target, i))
        print('Cost:', self.computer.elapsed())

    def test_22_x_13_official(self):
        for x in range(-4, 5):
            self.load_codes('22_x_13_official')
            self.computer.memoryAt(2000).set(x)
            self.computer.executeUntilHalt()
            self.assertEqual(x ** 13, self.computer.rA.value(), x)
        print('Cost:', self.computer.elapsed())

    def test_23_reflect(self):
        self.load_codes('23_reflect')
        self.computer.memoryAt(200).set(False, 1, 22, 33, 44, 5)
        self.computer.executeUntilHalt()
        self.assertEqual('+  5 44 33 22  1', self.computer.rA.getBytesString())
        print('Cost:', self.computer.elapsed())
