MIXAL Emulator
==============

A [MIX](https://en.wikipedia.org/wiki/MIX) assembly language emulator.

[Online MIXAL Emulator](https://cyberzhg.github.io/MIXAL/)

## Install

Python (requires `cmake`): 

```bash
pip install mixal
```

NPM:

```bash
node i mixal-emulator
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
computer.load_codes([
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
    computer.memory_at(i).set(val)
    max_val = max(max_val, val)
# Execute until the HLT operation
computer.execute_until_halt()
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

computer.load_codes("""
        ORIG 3000
        IN   100(16)
LIN     JBUS LIN(16)
        OUT  100(17)
LOUT    JBUS LOUT(17)
        """)
# Set the initial value of input device
computer.get_device_word_at(card_reader_index, 0).set('PRIME')
computer.execute_until_halt()
# Check the output text of the output device
print(computer.get_device_word_at(card_punch_index, 0).get_characters())
```

