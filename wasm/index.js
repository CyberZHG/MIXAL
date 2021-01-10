import MixalWASMModule from './wasm/MixalWASM.js';

const MixalWASM = await MixalWASMModule();

const ComputerWord = MixalWASM.ComputerWord;
const Register5 = ComputerWord;
const Register2 = MixalWASM.Register2;
const Computer = MixalWASM.Computer;
Computer.prototype.loadCodes = function(code, addHalt = true) {
    this._loadCodes(code, addHalt);
};

function executeWithSpec(code, ioSpec) {
    const computer = new Computer();
    computer.loadCodes(code);

    if ("inputs" in ioSpec) {
        const inputSpec = ioSpec.inputs;
        if ("memory" in inputSpec) {
            for (const inputData of inputSpec.memory) {
                const offset = inputData.offset ?? 0;
                const dataType = inputData.type ?? "int";
                const values = inputData.values ?? [];
                if (dataType === "int") {
                    for (const [i, value] of values.entries()) {
                        computer.memoryAt(offset + i).set(value);
                    }
                } else if (dataType === "text") {
                    for (let i = 0; i < values.length; i += 5) {
                        let chars = values.substring(i, i + 5);
                        while (chars.length < 5) {
                            chars += " ";
                        }
                        computer.memoryAt(offset + Math.floor(i / 5)).setCharacters(chars)
                    }
                }
            }
        }
    }
    computer.executeUntilHalt();

    let results = {
        "halt-at-address": computer.line(),
        "execution-time": computer.elapsed(),
        "A": {
            "int": computer.registerA().value(),
            "bytes": computer.registerA().getBytesString(),
            "text": computer.registerA().getCharacters(),
        },
        "X": {
            "int": computer.registerX().value(),
            "bytes": computer.registerX().getBytesString(),
            "text": computer.registerX().getCharacters(),
        },
        "J": computer.registerJ().value(),
        "I1": computer.registerI1().value(),
        "I2": computer.registerI2().value(),
        "I3": computer.registerI3().value(),
        "I4": computer.registerI4().value(),
        "I5": computer.registerI5().value(),
        "I6": computer.registerI6().value(),
    };
    if ("outputs" in ioSpec) {
        const outputSpec = ioSpec.outputs;
        if ("memory" in outputSpec) {
            results["memory"] = [];
            for (const outputData of outputSpec.memory) {
                const offset = outputData.offset ?? 0;
                const length = outputData.length ?? 0;
                const dataType = outputData.type ?? "int";
                const result = {
                    "offset": offset,
                    "type": dataType,
                };
                if (dataType === "int") {
                    result["values"] = []
                    for (let i = 0; i < length; ++i) {
                        result["values"].push(computer.memoryAt(offset + i).value());
                    }
                } else if (dataType === "text") {
                    result["values"] = ""
                    for (let i = 0; i < length; ++i) {
                        result["values"] += computer.memoryAt(offset + i).getCharacters();
                    }
                }
                results["memory"].push(result);
            }
        }
    }
    return results;
}

export {
    executeWithSpec,
    ComputerWord,
    Register5,
    Register2,
    Computer,
};
