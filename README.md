MIXAL
=====

![Unit Tests](https://github.com/CyberZHG/MIXAL/workflows/Unit%20Tests/badge.svg)
[![Deploy](https://github.com/CyberZHG/MIXAL/workflows/Deploy/badge.svg)](https://cyberzhg.github.io/MIXAL/)
[![Build Status](https://travis-ci.org/CyberZHG/MIXAL.svg?branch=master)](https://travis-ci.org/CyberZHG/MIXAL)
[![Coverage Status](https://coveralls.io/repos/github/CyberZHG/MIXAL/badge.svg?branch=master)](https://coveralls.io/github/CyberZHG/MIXAL?branch=travis)
[![Version](https://img.shields.io/pypi/v/mixal.svg)](https://pypi.org/project/mixal/)
![Downloads](https://img.shields.io/pypi/dm/mixal.svg)
![License](https://img.shields.io/pypi/l/keras-bert.svg)

\[[中文](https://github.com/CyberZHG/MIXAL/blob/master/README.zh-CN.md)|[English](https://github.com/CyberZHG/MIXAL/blob/master/README.md)\]

A [MIX](https://en.wikipedia.org/wiki/MIX) assembly language simulator.

## Install

Make sure you have a C++ 11 compiler and execute:

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

# Initialize an environment
machine = mixal.Machine()

# The location for register J
end_point = 3500

# Load the assembly codes.
# Note that the location for register J is set to HLT
# to make sure the codes halt eventually
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
# Register I1 denotes the number of integers in the memory buffer
machine.rI1.set(num_numbers)
# Register J stores the returning location
machine.rJ.set(end_point)
for i in range(1001, 1001 + num_numbers):
    val = random.randint(0, 100000)
    # Set random values to memory
    machine.memoryAt(i).set(val)
    max_val = max(max_val, val)
# Execute until the HLT operation
machine.executeUntilHalt()
print('Expected:', max_val)
# Register A stores the final maximum value
print('Actual:', machine.rA.value())
# The units of time for executing the codes, exclude the halt operation.
print('Compute Cost:', machine.elapsed())
```
