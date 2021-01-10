declare module 'mixal' {

    export class ComputerWord {
        constructor()
        set(value: number): void
        setCharacters(value: string): void
        setByteAt(index: number, value: number): void
        setBytes(negative: boolean, byte1: number, byte2: number, byte3: number, byte4: number, byte5: number): void
        setMergedBytes(negative: boolean, byte12: number, byte3: number, byte4: number, byte5: number): void
        value(): number
        getCharacters(): string
        getBytesString(): string
    }

    export type Register5 = ComputerWord

    export class Register2 {
        constructor()
        set(value: number): void
        value(): number
    }

    export class Computer {
        constructor()
        registerA(): Register5
        registerX(): Register5
        registerI1(): Register2
        registerI2(): Register2
        registerI3(): Register2
        registerI4(): Register2
        registerI5(): Register2
        registerI6(): Register2
        registerJ(): Register2
        reset(): void
        _loadCodes(code: string, addHalt: boolean): void
        loadCodes(code: string, addHalt?: boolean): void
        memoryAt(index: number): ComputerWord
        getDeviceWordAt(device: number, index: number): ComputerWord
        executeSingle(): void
        executeUntilSelfLoop(): void
        executeUntilHalt(): void
        getDeviceWordAt(device: number, index: number): ComputerWord
        line(): number
        elapsed(): number
    }

    export function executeWithSpec(code: string, ioSpec: Record<string, Record<string, any>>): Record<string, any>

}
