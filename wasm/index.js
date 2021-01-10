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
                let values = inputData.values ?? [];
                if (dataType === "int") {
                    for (const [i, value] of values.entries()) {
                        computer.memoryAt(offset + i).set(value);
                    }
                } else if (dataType === "text") {
                    if (Object.prototype.toString.call(values) === '[object Array]') {
                        values = values.join("");
                    }
                    for (let i = 0; i < values.length; i += 5) {
                        let chars = values.substring(i, i + 5);
                        if (chars.length < 5) {
                            chars += " ".repeat(5 - chars.length);
                        }
                        computer.memoryAt(offset + Math.floor(i / 5)).setCharacters(chars);
                    }
                }
            }
        }
        if ("card_reader" in inputSpec || "device_16" in inputSpec) {
            const inputData = inputSpec.card_reader ?? inputSpec.device_16;
            const offset = inputData.offset ?? 0;
            const dataType = inputData.type ?? "text";
            let values = inputData.values ?? "";
            if (dataType === "text") {
                if (Object.prototype.toString.call(values) === '[object Array]') {
                    values = values.join("");
                }
                for (let i = 0; i < values.length; i += 5) {
                    let chars = values.substring(i, i + 5);
                    if (chars.length < 5) {
                        chars += " ".repeat(5 - chars.length);
                    }
                    computer.getDeviceWordAt(16, offset + Math.floor(i / 5)).setCharacters(chars);
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
        "J": {
            "int": computer.registerJ().value(),
            "bytes": computer.registerJ().getBytesString(),
        },
        "I1": {
            "int": computer.registerI1().value(),
            "bytes": computer.registerI1().getBytesString(),
        },
        "I2": {
            "int": computer.registerI2().value(),
            "bytes": computer.registerI2().getBytesString(),
        },
        "I3": {
            "int": computer.registerI3().value(),
            "bytes": computer.registerI3().getBytesString(),
        },
        "I4": {
            "int": computer.registerI4().value(),
            "bytes": computer.registerI4().getBytesString(),
        },
        "I5": {
            "int": computer.registerI5().value(),
            "bytes": computer.registerI5().getBytesString(),
        },
        "I6": {
            "int": computer.registerI6().value(),
            "bytes": computer.registerI6().getBytesString(),
        },
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
        if ("line_printer" in outputSpec || "device_18" in outputSpec) {
            const outputData = outputSpec.line_printer ?? outputSpec.device_18;
            const offset = outputData.offset ?? 0;
            const length = outputData.length ?? 0;
            const dataType = outputData.type ?? "text";
            const result = {
                "offset": offset,
                "type": dataType,
            };
            if (dataType === "text") {
                let outputText = "";
                for (let i = 0; i < length; ++i) {
                    if (i !== 0 && offset + i % 16 === 0) {
                        outputText += "\n";
                    }
                    outputText += computer.getDeviceWordAt(18, offset + i).getCharacters();
                }
                result["values"] = outputText.split("\n");
            }
            results["line_printer"] = result;
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
