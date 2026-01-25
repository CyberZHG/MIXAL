# MIXAL Emulator

[![C++ Unit Tests](https://github.com/CyberZHG/MIXAL/actions/workflows/cpp-unit-tests.yml/badge.svg)](https://github.com/CyberZHG/MIXAL/actions/workflows/cpp-unit-tests.yml)
[![Python Build & Test](https://github.com/CyberZHG/MIXAL/actions/workflows/python-build-test.yml/badge.svg)](https://github.com/CyberZHG/MIXAL/actions/workflows/python-build-test.yml)
[![WASM Build & Test](https://github.com/CyberZHG/MIXAL/actions/workflows/wasm-build-test.yml/badge.svg)](https://github.com/CyberZHG/MIXAL/actions/workflows/wasm-build-test.yml)
[![Deploy Pages](https://github.com/CyberZHG/MIXAL/actions/workflows/deploy-pages.yml/badge.svg)](https://github.com/CyberZHG/MIXAL/actions/workflows/deploy-pages.yml)
[![Coverage Status](https://coveralls.io/repos/github/CyberZHG/MIXAL/badge.svg?branch=main)](https://coveralls.io/github/CyberZHG/MIXAL?branch=main)
[![PyPI version](https://img.shields.io/pypi/v/mixal)](https://pypi.org/project/mixal/)
[![npm version](https://img.shields.io/npm/v/mixal-emulator)](https://www.npmjs.com/package/mixal-emulator)
![](https://visitor-badge.laobi.icu/badge?page_id=cyberzhg.mixal)

A [MIX](https://en.wikipedia.org/wiki/MIX) assembly language emulator implementing the MIX computer architecture from Donald Knuth's *"The Art of Computer Programming"*.

**[Try the Online Emulator](https://cyberzhg.github.io/MIXAL/)**

## Features

- Complete MIX instruction set implementation
- MIXAL assembler with symbol table support
- Execution timing/cost tracking
- Multiple platform bindings:
  - **Python** package via [PyPI](https://pypi.org/project/mixal/)
  - **JavaScript/WASM** module via [npm](https://www.npmjs.com/package/mixal-emulator)
  - **C++** core library

## Installation

### Python

```bash
pip install mixal
```

> Requires CMake for building from source.

### JavaScript / Node.js

```bash
npm install mixal-emulator
```

### Building from Source

```bash
# Clone the repository
git clone https://github.com/CyberZHG/MIXAL.git
cd MIXAL

# Configure and build
cmake -B build -DMIXAL_ENABLE_TESTS=ON
cmake --build build

# Run tests
ctest --test-dir build --output-on-failure
```

## Quick Start

### Python Example: Finding Maximum Value

```python
import random
import mixal

# Initialize the MIX computer
computer = mixal.Computer()

# Load MIXAL assembly program (Algorithm M from TAOCP)
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

# Setup: store random values in memory
num_numbers, max_val = 100, 0
computer.rI1.set(num_numbers)
computer.rJ.set(3500)

for i in range(1001, 1001 + num_numbers):
    val = random.randint(0, 100000)
    computer.memory_at(i).set(val)
    max_val = max(max_val, val)

# Execute
computer.execute_until_halt()

# Results
print(f'Expected: {max_val}')
print(f'Actual:   {computer.rA.value()}')
print(f'Cycles:   {computer.elapsed()}')
```

### I/O Device Example

```python
import mixal

computer = mixal.Computer()

# Load program that reads from card reader and writes to card punch
computer.load_codes("""
        ORIG 3000
        IN   100(16)
LIN     JBUS LIN(16)
        OUT  100(17)
LOUT    JBUS LOUT(17)
""")

# Set input data (device 16 = card reader)
computer.get_device_word_at(16, 0).set('HELLO')

computer.execute_until_halt()

# Read output (device 17 = card punch)
print(computer.get_device_word_at(17, 0).get_chars())
```

### JavaScript Example

```javascript
import { Computer } from 'mixal-emulator';

const computer = new Computer();

computer.loadCodes([
    '        ORIG 3000',
    '        ENTA 42',
    '        HLT',
]);

computer.executeUntilHalt();
console.log(computer.rA.value()); // 42
```

## API Reference

### Core Classes

| Class | Description |
|-------|-------------|
| `Computer` | Main MIX virtual machine |
| `Register5` | 5-byte register (rA, rX) |
| `Register2` | 2-byte register (rI1-rI6, rJ) |
| `ComputerWord` | Memory word representation |

### Key Methods

| Method | Description |
|--------|-------------|
| `load_codes(lines)` | Load and assemble MIXAL source |
| `execute_until_halt()` | Run until HLT instruction |
| `execute_single()` | Execute one instruction |
| `memory_at(addr)` | Access memory at address |
| `elapsed()` | Get execution time units |

### I/O Device Indices

| Index | Device |
|-------|--------|
| 0-7 | Tape units |
| 8-15 | Disk units |
| 16 | Card reader |
| 17 | Card punch |
| 18 | Line printer |
| 19 | Terminal |
| 20 | Paper tape |

## Development

### Project Structure

```
MIXAL/
├── include/          # C++ headers
├── src/              # C++ implementation
├── python/           # Python bindings (pybind11)
├── wasm/             # WebAssembly bindings (Emscripten)
├── web/              # Online emulator (TypeScript/Vite)
└── tests/            # C++ unit tests
```

### Running Tests

```bash
# C++ tests
cmake -B build -DMIXAL_ENABLE_TESTS=ON
cmake --build build
ctest --test-dir build

# Python tests
pip install -e ".[test]"
pytest -v python/tests

# WASM tests
cd wasm && npm test

# Web UI tests
cd web && npm test
```

## References

- Knuth, D. E. *The Art of Computer Programming, Volume 1: Fundamental Algorithms* (3rd ed.)
- [MIX on Wikipedia](https://en.wikipedia.org/wiki/MIX)
