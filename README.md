MIXAL
=====

![C++ Tests](https://github.com/CyberZHG/MIXAL/workflows/C++%20Tests/badge.svg)
![Python Tests](https://github.com/CyberZHG/MIXAL/workflows/Python%20Tests/badge.svg)
[![Version](https://img.shields.io/pypi/v/mixal.svg)](https://pypi.org/project/mixal/)
![Downloads](https://img.shields.io/pypi/dm/mixal.svg)
![License](https://img.shields.io/pypi/l/keras-bert.svg)

## Install

```bash
pip install mixal
```

For MacOS users, you may need to use:

```bash
MACOSX_DEPLOYMENT_TARGET=10.9 pip install mixal
```

## Sample

A sample code that finds the maximum value:

```python
import random
import mixal

machine = mixal.Machine()

end_point = 3500

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
    '        ORIG {}'.format(end_point),
    '        HLT',
])

num_numbers, max_val = 100, 0
machine.rI1().set(num_numbers)
machine.rJ.set(end_point)
for i in range(1001, 1001 + num_numbers):
    val = random.randint(0, 100000)
    machine.memoryAt(i).set(val)
    max_val = max(max_val, val)
machine.executeUntilHalt()
print('Expected:', max_val)
print('Actual:', machine.rA.value())
print('Compute Cost:', machine.elapsed())
```
