import random
from unittest import TestCase
import mixal


class TestSample(TestCase):

    def setUp(self) -> None:
        self.computer = mixal.Computer()

    def test_sample(self):
        self.computer.loadCodes("""
X       EQU  1000
        ORIG 3000
MAXIMUM STJ  EXIT
INIT    ENT3 0,1
        JMP  CHANGEM
LOOP    CMPA X,3
        JGE  *+3
CHANGEM ENT2 0,3
        LDA  X,3
        DEC3 1
        J3P  LOOP
EXIT    JMP  *
        ORIG 3500
        HLT
        """)

        n, max_val = 100, 0
        self.computer.rI1.set(n)
        self.computer.rJ.set(3500)
        values = []
        for i in range(1001, 1001 + n):
            val = random.randint(0, 100000)
            self.computer.memoryAt(i).set(val)
            max_val = max(max_val, val)
            values.append(val)
        self.computer.executeUntilHalt()
        self.assertEqual(max_val, self.computer.rA.value(), str(values))

    def test_basic_io(self):
        card_reader_index = 16
        card_punch_index = 17

        self.computer.loadCodes(f"""
        ORIG 3000
        IN   100({card_reader_index})
LIN     JBUS LIN({card_reader_index})
        OUT  100({card_punch_index})
LOUT    JBUS LOUT({card_punch_index})
        """)
        self.computer.getDeviceWordAt(card_reader_index, 0).set('PRIME')
        self.computer.executeUntilHalt()
        print(self.computer.getDeviceWordAt(card_punch_index, 0).getCharacters())
