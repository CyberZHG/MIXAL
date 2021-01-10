import MixalWASMModule from './wasm/MixalWASM.js';

const MixalWASM = await MixalWASMModule();

const ComputerWord = MixalWASM.ComputerWord;
const Register5 = ComputerWord;
const Register2 = MixalWASM.Register2;
const Computer = MixalWASM.Computer;
Computer.prototype.loadCodes = function(code, addHalt = true) {
    this._loadCodes(code, addHalt);
};

export {
    ComputerWord,
    Register5,
    Register2,
    Computer,
};
