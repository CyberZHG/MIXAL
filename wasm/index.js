import MixalWASMModule from './wasm/MixalWASM.js';

const MixalWASM = await MixalWASMModule();

const ComputerWord = MixalWASM.ComputerWord;
const Register5 = ComputerWord;
const Register2 = MixalWASM.Register2;
const Computer = MixalWASM.Computer;
Computer.prototype.loadCodes = function(code, addHalt = true) {
    this._loadCodes(code, addHalt);
};

let DEVICE_NAME_MAPPING = {};
let RANDOM_ACCESS_NAMES = [];

function initDeviceMappingArray() {
    if (Object.keys(DEVICE_NAME_MAPPING).length !== 0) {
        return;
    }
    DEVICE_NAME_MAPPING = {
        "magnetic_tape": 0,
        "disk": 8,
        "drum": 8,
        "card_reader": 16,
        "card_punch": 17,
        "line_printer": 18,
        "typewriter": 19,
        "paper_tape": 20,
    };
    for (let i = 0; i <= 20; ++i) {
        if (i <= 8) {
            DEVICE_NAME_MAPPING[`magnetic_tape_${i}`] = i;
            DEVICE_NAME_MAPPING[`disk_${8 + i}`] = 8 + i;
            DEVICE_NAME_MAPPING[`drum_${8 + i}`] = 8 + i;
        }
        DEVICE_NAME_MAPPING[`device_${i}`] = i;
    }
    for (const name of Object.keys(DEVICE_NAME_MAPPING)) {
        DEVICE_NAME_MAPPING[name.replaceAll("_", "-")] = DEVICE_NAME_MAPPING[name];
    }
    RANDOM_ACCESS_NAMES = ["memory", ...Object.keys(DEVICE_NAME_MAPPING)];
}

function executeWithSpec(code, ioSpec) {
    const TEXT_DEVICES = [
        "device_16", "device_18", "device_19", "card_reader", "line_printer", "typewriter",
        "device-16", "device-18", "device-19", "card-reader", "line-printer",
    ];
    const AUTO_WRAP_DEVICES = [
        "device_18", "line_printer",
        "device-18", "line-printer",
    ]

    const computer = new Computer();
    computer.loadCodes(code);
    initDeviceMappingArray();

    // Register inputs
    for (let registerName of ["A", "X"]) {
        if (registerName in ioSpec) {
            const register = computer[`register${registerName}`]();
            const inputData = ioSpec[registerName];
            if (typeof inputData === "number") {
                register.set(inputData);
            } else if (typeof inputData === "string") {
                register.setCharacters(inputData);
            } else if (Object.prototype.toString.call(inputData) === '[object Array]') {
                if (inputData.length === 6) {
                    register.setBytes(inputData[0], inputData[1], inputData[2], inputData[3], inputData[4], inputData[5]);
                } else if (inputData.length === 5) {
                    register.setMergedBytes(inputData[0], inputData[1], inputData[2], inputData[3], inputData[4]);
                }
            }
        }
    }
    for (let registerName of ["J", "I1", "I2", "I3", "I4", "I5", "I6"]) {
        if (registerName in ioSpec) {
            const register = computer[`register${registerName}`]();
            const inputData = ioSpec[registerName];
            if (typeof inputData === "number") {
                register.set(inputData);
            }
        }
    }
    // Memory & device inputs
    for (const name of RANDOM_ACCESS_NAMES) {
        if (name in ioSpec) {
            const wordAt = (index) => {
                if (name === "memory") {
                    return computer.memoryAt(index);
                }
                return computer.getDeviceWordAt(DEVICE_NAME_MAPPING[name], index);
            };
            if (Object.prototype.toString.call(ioSpec[name]) !== '[object Array]') {
                ioSpec[name] = [ioSpec[name]];
            }
            for (const inputData of ioSpec[name]) {
                const offset = inputData.offset ?? 0;
                let values = inputData.values ?? [];
                if (values.length === 0) {
                    continue;
                }
                if (typeof values[0] === "number") {
                    for (const [i, value] of values.entries()) {
                        wordAt(offset + i).set(value);
                    }
                } else if (typeof values === "string" || typeof values[0] === "string") {
                    if (Object.prototype.toString.call(values) === '[object Array]') {
                        values = values.join("");
                    }
                    for (let i = 0; i < values.length; i += 5) {
                        let chars = values.substring(i, i + 5);
                        if (chars.length < 5) {
                            chars += " ".repeat(5 - chars.length);
                        }
                        wordAt(offset + Math.floor(i / 5)).setCharacters(chars);
                    }
                } else if (Object.prototype.toString.call(values[0]) === '[object Array]') {
                    for (const [i, value] of values.entries()) {
                        if (value.length === 6) {
                            wordAt(offset + i).setBytes(value[0], value[1], value[2], value[3], value[4], value[5]);
                        } else {
                            wordAt(offset + i).setMergedBytes(value[0], value[1], value[2], value[3], value[4]);
                        }
                    }
                }
            }
        }
    }

    computer.executeUntilHaltOrSelfLoop();

    let results = {
        "program-counter": computer.line(),
        "execution-time": computer.elapsed(),
    }
    // Output register values
    for (const registerName of ["A", "X"]) {
        const register = computer[`register${registerName}`]();
        results[registerName] = {
            "int": register.value(),
            "bytes": register.getBytesString(),
            "text": register.getCharacters(),
        };
    }
    for (const registerName of ["J", "I1", "I2", "I3", "I4", "I5", "I6"]) {
        const register = computer[`register${registerName}`]();
        results[registerName] = {
            "int": register.value(),
            "bytes": register.getBytesString(),
        };
    }
    // Output memory & device values
    const outputSpec = ioSpec.outputs;
    if (outputSpec) {
        for (const name of RANDOM_ACCESS_NAMES) {
            if (name in outputSpec) {
                let isSingleOutput = false;
                if ((Object.prototype.toString.call(outputSpec[name]) !== '[object Array]')) {
                    isSingleOutput = true;
                    outputSpec[name] = [outputSpec[name]];
                }
                const wordAt = (index) => {
                    if (name === "memory") {
                        return computer.memoryAt(index);
                    }
                    return computer.getDeviceWordAt(DEVICE_NAME_MAPPING[name], index);
                };
                results[name] = [];
                for (const outputData of outputSpec[name]) {
                    const offset = outputData.offset ?? 0;
                    const length = outputData.length ?? 1;
                    const singleValue = typeof outputData.length === "undefined";
                    const dataType = outputData.type ?? (TEXT_DEVICES.includes(name) ? "text" : "int");
                    const result = {
                        "offset": offset,
                        "type": dataType,
                    };
                    if (dataType === "int") {
                        result["values"] = []
                        for (let i = 0; i < length; ++i) {
                            result["values"].push(wordAt(offset + i).value());
                        }
                    } else if (dataType === "text") {
                        result["values"] = ""
                        const autoWrap = outputData["auto-wrap"] ?? false
                        for (let i = 0; i < length; ++i) {
                            if (autoWrap && i !== 0 && i % 16 === 0 && (AUTO_WRAP_DEVICES.includes(name))) {
                                result["values"] += "\n";
                            }
                            result["values"] += wordAt(offset + i).getCharacters();
                        }
                        if (autoWrap && AUTO_WRAP_DEVICES.includes(name)) {
                            if (result["values"].includes("\n")) {
                                result["values"] = result["values"].split("\n");
                            }
                        }
                    } else if (dataType === "bytes") {
                        result["values"] = []
                        for (let i = 0; i < length; ++i) {
                            result["values"].push(wordAt(offset + i).getBytesString());
                        }
                    }
                    if (singleValue) {
                        result["value"] = result["values"][0];
                        delete result["values"]
                    }
                    results[name].push(result);
                }
                if (isSingleOutput) {
                    results[name] = results[name][0];
                }
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
