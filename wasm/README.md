# mixal-emulator

[![npm version](https://img.shields.io/npm/v/mixal-emulator)](https://www.npmjs.com/package/mixal-emulator)
[![WASM Build & Test](https://github.com/CyberZHG/MIXAL/actions/workflows/wasm-build-test.yml/badge.svg)](https://github.com/CyberZHG/MIXAL/actions/workflows/wasm-build-test.yml)
![](https://visitor-badge.laobi.icu/badge?page_id=cyberzhg.mixal)

JavaScript/WebAssembly bindings for the MIXAL emulator - a MIX assembly language emulator implementing the MIX computer architecture from Donald Knuth's *"The Art of Computer Programming"*.

## Installation

```bash
npm install mixal-emulator
```

## Quick Start

```javascript
import { Computer } from 'mixal-emulator';

const computer = new Computer();

computer.loadCodes(`
        ORIG 3000
        ENTA 42
        ADD  =100=
        HLT
`);

computer.executeUntilHalt();

console.log(computer.registerA().value());  // 142
console.log(computer.elapsed());            // Execution cycles
```

## API Reference

### Computer

The main class representing the MIX virtual machine.

```javascript
import { Computer } from 'mixal-emulator';

const computer = new Computer();
```

#### Methods

| Method | Returns | Description |
|--------|---------|-------------|
| `loadCodes(code, addHalt?)` | `void` | Load and assemble MIXAL source |
| `executeUntilHalt()` | `void` | Run until HLT instruction |
| `executeUntilSelfLoop()` | `void` | Run until self-loop detected |
| `executeUntilHaltOrSelfLoop()` | `void` | Run until HLT or self-loop |
| `executeSingle()` | `void` | Execute one instruction |
| `memoryAt(addr)` | `ComputerWord` | Access memory (0-3999) |
| `getDeviceWordAt(device, index)` | `ComputerWord` | Access I/O buffer |
| `line()` | `number` | Current program counter |
| `elapsed()` | `number` | Total execution cycles |
| `reset()` | `void` | Reset to initial state |

#### Register Accessors

| Method | Returns | Description |
|--------|---------|-------------|
| `registerA()` | `Register5` | Accumulator |
| `registerX()` | `Register5` | Extension register |
| `registerI1()` - `registerI6()` | `Register2` | Index registers |
| `registerJ()` | `Register2` | Jump address register |

### ComputerWord (Register5)

5-byte word used for rA, rX, and memory.

```javascript
const word = computer.registerA();

// Setters
word.set(12345);
word.setFloat(3.14);
word.setCharacters("HELLO");
word.setBytes(false, 1, 2, 3, 4, 5);      // sign + 5 bytes
word.setMergedBytes(false, 256, 3, 4, 5); // sign + merged bytes
word.setByteAt(2, 42);                    // Set specific byte

// Getters
word.value();           // number - integer value
word.floatValue();      // number - float interpretation
word.getCharacters();   // string - 5 character string
word.getBytesString();  // string - byte representation
```

### Register2

2-byte register used for index and jump registers.

```javascript
const reg = computer.registerI1();

reg.set(100);
reg.setBytes(false, 1, 2);  // sign + 2 bytes
reg.value();                // number
reg.getBytesString();       // string
```

### Parser

Static utility for parsing MIXAL source lines.

```javascript
import { Parser, ParsedType } from 'mixal-emulator';

const result = Parser.parseLine("LOOP    LDA  100,1(0:3)", "*", true);

console.log(result.parsedType === ParsedType.INSTRUCTION);  // true
console.log(result.rawLocation);   // "LOOP"
console.log(result.operation);     // "LDA"
console.log(result.rawAddress);    // "100"
console.log(result.rawIndex);      // "1"
console.log(result.rawField);      // "0:3"
```

### executeWithSpec

High-level function for executing code with I/O specifications.

```javascript
import { executeWithSpec } from 'mixal-emulator';

const result = executeWithSpec(`
        ORIG 3000
        LDA  1000
        HLT
`, {
    // Input: set memory[1000] = 42
    memory: { offset: 1000, values: [42] },

    // Output specification
    outputs: {
        memory: { offset: 1000, length: 1, type: "int" }
    }
});

console.log(result.A.int);           // Register A value
console.log(result.memory[0].value); // 42
console.log(result["execution-time"]); // Cycles
```

## Examples

### Finding Maximum Value

```javascript
import { Computer } from 'mixal-emulator';

const computer = new Computer();

computer.loadCodes(`
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
`);

// Setup test data
const n = 100;
computer.registerI1().set(n);
computer.registerJ().set(3500);

let maxVal = 0;
for (let i = 1001; i < 1001 + n; i++) {
    const val = Math.floor(Math.random() * 100000);
    computer.memoryAt(i).set(val);
    maxVal = Math.max(maxVal, val);
}

computer.executeUntilHalt();

console.log(`Expected: ${maxVal}`);
console.log(`Actual: ${computer.registerA().value()}`);
console.log(`Cycles: ${computer.elapsed()}`);
```

### I/O Operations

```javascript
import { Computer } from 'mixal-emulator';

const computer = new Computer();

computer.loadCodes(`
        ORIG 3000
        IN   100(16)
LIN     JBUS LIN(16)
        OUT  100(17)
LOUT    JBUS LOUT(17)
`);

// Set card reader input (device 16)
computer.getDeviceWordAt(16, 0).setCharacters("HELLO");

computer.executeUntilHalt();

// Read card punch output (device 17)
const output = computer.getDeviceWordAt(17, 0).getCharacters();
console.log(output);  // "HELLO"
```

### Using executeWithSpec

```javascript
import { executeWithSpec } from 'mixal-emulator';

const result = executeWithSpec(`
        ORIG 3000
        IN   100(16)
LIN     JBUS LIN(16)
        OUT  100(18)
LOUT    JBUS LOUT(18)
`, {
    "card-reader": {
        offset: 0,
        values: "HELLO MIXAL WORLD"
    },
    outputs: {
        "line-printer": {
            offset: 0,
            length: 4,
            type: "text"
        }
    }
});

console.log(result["line-printer"].values);
```

## I/O Device Reference

| Index | Name | Block Size |
|-------|------|------------|
| 0-7 | `magnetic-tape-0` to `magnetic-tape-7` | 100 words |
| 8-15 | `disk-8` to `disk-15` / `drum-8` to `drum-15` | 100 words |
| 16 | `card-reader` | 16 words |
| 17 | `card-punch` | 16 words |
| 18 | `line-printer` | 24 words |
| 19 | `typewriter` | 14 words |
| 20 | `paper-tape` | 14 words |

## TypeScript Support

Full TypeScript definitions are included. Import types directly:

```typescript
import { Computer, ComputerWord, Register2, Parser, ParsedType } from 'mixal-emulator';

const computer: Computer = new Computer();
const reg: ComputerWord = computer.registerA();
```

## Development

```bash
# Clone repository
git clone https://github.com/CyberZHG/MIXAL.git
cd MIXAL/wasm

# Install dependencies
npm install

# Build (requires Emscripten)
npm run build

# Run tests
npm test

# Lint
npm run lint
```

## Browser Usage

For browser environments, ensure your bundler supports WebAssembly. The module uses top-level await.

```html
<script type="module">
import { Computer } from './node_modules/mixal-emulator/index.js';

const computer = new Computer();
// ...
</script>
```

## Links

- [GitHub Repository](https://github.com/CyberZHG/MIXAL)
- [Online Emulator](https://cyberzhg.github.io/MIXAL/)
- [PyPI Package (Python)](https://pypi.org/project/mixal/)
