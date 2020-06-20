import random
from unittest import TestCase
import mixal


class TestSample(TestCase):

    def setUp(self) -> None:
        self.machine = mixal.Machine()

    def test_sample(self):
        self.machine.loadCodes([
            'X       EQU  1000',
            '        ORIG 3000',
            'MAXIMUM STJ  EXIT',
            'INIT    ENT3 0,1',
            '        JMP  CHANGEM',
            'LOOP    CMPA X,3',
            '        JGE  *+3',
            'CHANGEM ENT2 0,3',
            '        LDA  X,3',
            '        DEC3 1',
            '        J3P  LOOP',
            'EXIT    JMP  *',
        ])
        n, max_val = 100, 0
        self.machine.rI1().set(n)
        self.machine.rJ.set(3009)
        for i in range(1000, 1000 + n):
            val = random.randint(0, 100000)
            self.machine.memoryAt(i).set(val)
            max_val = max(max_val, val)
        self.machine.executeUntilSelfLoop()
        self.assertEqual(max_val, self.machine.rA.value())
