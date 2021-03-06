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

Following is a piece of sample code that finds the maximum value. There are upper-case letters in the names of functions and attributes as the codes were written with C++.

```python
import random
import mixal

# Initialize an environment
computer = mixal.Computer()

# The location for register J
end_point = 3500

# Load the assembly codes.
# Note that the location for register J is set to HLT
# to make sure the codes halt eventually
computer.loadCodes([
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
computer.rI1.set(num_numbers)
# Register J stores the returning location
computer.rJ.set(end_point)
for i in range(1001, 1001 + num_numbers):
    val = random.randint(0, 100000)
    # Set random values to memory
    computer.memoryAt(i).set(val)
    max_val = max(max_val, val)
# Execute until the HLT operation
computer.executeUntilHalt()
print('Expected:', max_val)
# Register A stores the final maximum value
print('Actual:', computer.rA.value())
# The units of time for executing the codes, exclude the halt operation.
print('Compute Cost:', computer.elapsed())
```

# IO Devices

There are several pre-defined IO devices in the environment. You can set the initial values of the input devices before the execution. Following is the code that reads one word from the input device and writes the same one to the output device.

```python
import mixal

# Initialize an environment
computer = mixal.Computer()

# Pre-defined indices for IO devices
card_reader_index = 16
card_punch_index = 17

computer.loadCodes("""
        ORIG 3000
        IN   100(16)
LIN     JBUS LIN(16)
        OUT  100(17)
LOUT    JBUS LOUT(17)
        """)
# Set the initial value of input device
computer.getDeviceWordAt(card_reader_index, 0).set('PRIME')
computer.executeUntilHalt()
# Check the output text of the output device
print(computer.getDeviceWordAt(card_punch_index, 0).getCharacters())
```

