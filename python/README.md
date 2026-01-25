# mixal

[![PyPI version](https://img.shields.io/pypi/v/mixal)](https://pypi.org/project/mixal/)
[![Python Build & Test](https://github.com/CyberZHG/MIXAL/actions/workflows/python-build-test.yml/badge.svg)](https://github.com/CyberZHG/MIXAL/actions/workflows/python-build-test.yml)
![](https://visitor-badge.laobi.icu/badge?page_id=cyberzhg.mixal)

Python bindings for the MIXAL emulator - a MIX assembly language emulator implementing the MIX computer architecture from Donald Knuth's *"The Art of Computer Programming"*.

## Installation

```bash
pip install mixal
```

> **Note:** Requires CMake for building from source.

## Quick Start

```python
import mixal

# Create a MIX computer instance
computer = mixal.Computer()

# Load MIXAL assembly code
computer.load_codes("""
        ORIG 3000
        ENTA 42
        ADD  =100=
        HLT
""")

# Execute until halt
computer.execute_until_halt()

# Read results
print(computer.rA.value())  # 142
print(computer.elapsed())   # Execution time in cycles
```

## API Reference

### Computer

The main class representing the MIX virtual machine.

```python
computer = mixal.Computer()
```

#### Registers

| Attribute | Type | Description |
|-----------|------|-------------|
| `rA` | `Register5` | Accumulator (5 bytes + sign) |
| `rX` | `Register5` | Extension register (5 bytes + sign) |
| `rI1` - `rI6` | `Register2` | Index registers (2 bytes + sign) |
| `rJ` | `Register2` | Jump address register (2 bytes, always positive) |

#### Methods

| Method | Description |
|--------|-------------|
| `load_codes(code)` | Load and assemble MIXAL source code |
| `execute_until_halt()` | Run until HLT instruction |
| `execute_single()` | Execute one instruction |
| `memory_at(addr)` | Access memory word at address (0-3999) |
| `get_device_word_at(device, index)` | Access I/O device buffer |
| `elapsed()` | Get total execution time in cycles |
| `reset()` | Reset computer to initial state |

### Register5 (ComputerWord)

5-byte register used for rA, rX, and memory words.

```python
word = computer.rA  # or computer.memory_at(1000)

# Set value
word.set(12345)
word.set_characters("HELLO")
word.set_bytes(False, 1, 2, 3, 4, 5)  # sign + 5 bytes

# Get value
word.value()           # Integer value
word.float_value()     # Float interpretation
word.get_characters()  # Character string (5 chars)
word.get_bytes_string() # Byte representation
```

### Register2

2-byte register used for rI1-rI6 and rJ.

```python
reg = computer.rI1

reg.set(100)
reg.set_bytes(False, 1, 2)  # sign + 2 bytes
reg.value()
```

## Examples

### Finding Maximum Value (Algorithm M from TAOCP)

```python
import random
import mixal

computer = mixal.Computer()

computer.load_codes("""
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

# Setup test data
n = 100
computer.rI1.set(n)
computer.rJ.set(3500)

max_val = 0
for i in range(1001, 1001 + n):
    val = random.randint(0, 100000)
    computer.memory_at(i).set(val)
    max_val = max(max_val, val)

computer.execute_until_halt()

assert computer.rA.value() == max_val
print(f"Maximum: {computer.rA.value()}")
print(f"Cycles: {computer.elapsed()}")
```

### I/O Operations

```python
import mixal

computer = mixal.Computer()

# Card reader (16) -> Card punch (17)
computer.load_codes("""
        ORIG 3000
        IN   100(16)
LIN     JBUS LIN(16)
        OUT  100(17)
LOUT    JBUS LOUT(17)
""")

# Set input
computer.get_device_word_at(16, 0).set_characters("HELLO")

computer.execute_until_halt()

# Read output
output = computer.get_device_word_at(17, 0).get_characters()
print(output)  # "HELLO"
```

### Arithmetic Operations

```python
import mixal

computer = mixal.Computer()

computer.load_codes("""
        ORIG 3000
        ENTA 1000
        MUL  =3=
        HLT
""")

computer.execute_until_halt()

# After MUL, result is in rA:rX (10 bytes)
print(f"rA = {computer.rA.value()}")
print(f"rX = {computer.rX.value()}")
```

## I/O Device Reference

| Index | Device | Block Size |
|-------|--------|------------|
| 0-7 | Magnetic tape units | 100 words |
| 8-15 | Disk/drum units | 100 words |
| 16 | Card reader | 16 words |
| 17 | Card punch | 16 words |
| 18 | Line printer | 24 words |
| 19 | Terminal | 14 words |
| 20 | Paper tape | 14 words |

## Development

```bash
# Clone repository
git clone https://github.com/CyberZHG/MIXAL.git
cd MIXAL

# Install in development mode
pip install -e ".[test]"

# Run tests
pytest -v python/tests

# Code formatting
black python/
isort python/
flake8 python/
```

## Links

- [GitHub Repository](https://github.com/CyberZHG/MIXAL)
- [Online Emulator](https://cyberzhg.github.io/MIXAL/)
- [npm Package (JavaScript)](https://www.npmjs.com/package/mixal-emulator)
