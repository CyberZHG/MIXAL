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