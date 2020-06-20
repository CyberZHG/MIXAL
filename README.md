MIXAL
=====

## Sample

A sample code that finds the maximum value:

```python
import random
import mixal

machine = mixal.Machine()

machine.loadCodes([
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
machine.rI1().set(n)
machine.rJ.set(3009)
for i in range(1000, 1000 + n):
    val = random.randint(0, 100000)
    machine.memoryAt(i).set(val)
    max_val = max(max_val, val)
machine.executeUntilSelfLoop()
print(machine.rA.value())
```