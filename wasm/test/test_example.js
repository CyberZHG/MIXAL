import { describe, it } from 'mocha';
import { Computer } from '../index.js';

describe('Example', () => {
    it('example1', async () => {
        // Initialize an environment
        const computer = new Computer();
        // The location for register J
        const endPoint = 3500;
        // Load the assembly codes.
        // Note that the location for register J is set to HLT
        // to make sure the codes halt eventually
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
        ORIG ${endPoint}
        HLT`)
        const numNumbers = 100;
        let maxVal = 0;
        // Register I1 denotes the number of integers in the memory buffer
        computer.registerI1().set(numNumbers);
        // Register J stores the returning location
        computer.registerJ().set(endPoint);
        for (let i = 1001; i < 1001 + numNumbers; ++i) {
            const value = Math.floor(Math.random() * 100000);
            // Set random values to memory
            computer.memoryAt(i).set(value)
            maxVal = Math.max(maxVal, value);
        }
        // Execute until the HLT operation
        computer.executeUntilHalt();
        console.log('Expected:', maxVal);
        // Register A stores the final maximum value
        console.log('Actual:', computer.registerA().value());
        // The units of time for executing the codes, exclude the halt operation.
        console.log('Compute Cost:', computer.elapsed());
    });
    it('example2', async () => {
        // Initialize an environment
        const computer = new Computer()

        // Pre-defined indices for IO devices
        const cardReaderIndex = 16
        const cardPunchIndex = 17

        computer.loadCodes(`
        ORIG 3000
        IN   100(16)
LIN     JBUS LIN(16)
        OUT  100(17)
LOUT    JBUS LOUT(17)`)
        // Set the initial value of input device
        computer.getDeviceWordAt(cardReaderIndex, 0).setCharacters('PRIME')
        computer.executeUntilHalt()
        // Check the output text of the output device
        console.log(computer.getDeviceWordAt(cardPunchIndex, 0).getCharacters())
    });
});
