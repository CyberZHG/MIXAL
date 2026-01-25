import json5 from "json5"

type Register5Type = "int" | "text" | "bytes" | "merged-bytes"
type Register2Type = "int" | "bytes"

interface Register5State {
    type: Register5Type
    intValue: string
    sign: string
    bytes: string[]
    addr: string
    mergedBytes: string[]
}

interface Register2State {
    type: Register2Type
    intValue: string
    sign: string
    bytes: string[]
}

interface RegisterState {
    A: Register5State
    X: Register5State
    I1: Register2State
    I2: Register2State
    I3: Register2State
    I4: Register2State
    I5: Register2State
    I6: Register2State
    J: Register2State
}

const ioSpecEditor = document.querySelector<HTMLTextAreaElement>("#io-spec-editor")!
const resultsEditor = document.querySelector<HTMLTextAreaElement>("#results-editor")!

function getDefaultRegister5State(): Register5State {
    return {
        type: "int",
        intValue: "0",
        sign: "+",
        bytes: ["0", "0", "0", "0", "0"],
        addr: "0",
        mergedBytes: ["0", "0", "0"],
    }
}

function getDefaultRegister2State(): Register2State {
    return {
        type: "int",
        intValue: "0",
        sign: "+",
        bytes: ["0", "0"],
    }
}

function getDefaultState(): RegisterState {
    return {
        A: getDefaultRegister5State(),
        X: getDefaultRegister5State(),
        I1: getDefaultRegister2State(),
        I2: getDefaultRegister2State(),
        I3: getDefaultRegister2State(),
        I4: getDefaultRegister2State(),
        I5: getDefaultRegister2State(),
        I6: getDefaultRegister2State(),
        J: getDefaultRegister2State(),
    }
}

function parseIOSpec(): Record<string, unknown> {
    try {
        return json5.parse(ioSpecEditor.value) || {}
    } catch {
        return {}
    }
}

function detectRegister5State(value: unknown): Register5State {
    const state = getDefaultRegister5State()
    if (typeof value === "number") {
        state.type = "int"
        state.intValue = String(value)
    } else if (typeof value === "string") {
        state.type = "text"
        state.intValue = value
    } else if (Array.isArray(value)) {
        if (value.length === 6) {
            state.type = "bytes"
            state.sign = value[0] === "-" ? "-" : "+"
            state.bytes = value.slice(1).map(String)
        } else if (value.length === 5) {
            state.type = "merged-bytes"
            state.sign = value[0] === "-" ? "-" : "+"
            state.addr = String(value[1])
            state.mergedBytes = value.slice(2).map(String)
        }
    }
    return state
}

function detectRegister2State(value: unknown): Register2State {
    const state = getDefaultRegister2State()
    if (typeof value === "number") {
        state.type = "int"
        state.intValue = String(value)
    } else if (Array.isArray(value) && value.length === 3) {
        state.type = "bytes"
        state.sign = value[0] === "-" ? "-" : "+"
        state.bytes = value.slice(1).map(String)
    }
    return state
}

export function readRegistersFromIOSpec(): RegisterState {
    const state = getDefaultState()
    const spec = parseIOSpec()

    for (const name of ["A", "X"] as const) {
        if (name in spec) {
            state[name] = detectRegister5State(spec[name])
        }
    }

    for (const name of ["I1", "I2", "I3", "I4", "I5", "I6", "J"] as const) {
        if (name in spec) {
            state[name] = detectRegister2State(spec[name])
        }
    }

    return state
}

function buildRegister5Value(state: Register5State): unknown {
    if (state.type === "int") {
        const num = parseInt(state.intValue, 10)
        return isNaN(num) ? 0 : num
    }
    if (state.type === "text") {
        return state.intValue
    }
    if (state.type === "bytes") {
        return [
            state.sign,
            ...state.bytes.map(b => {
                const n = parseInt(b, 10)
                return isNaN(n) ? 0 : n
            })
        ]
    }
    if (state.type === "merged-bytes") {
        const addr = parseInt(state.addr, 10)
        return [
            state.sign,
            isNaN(addr) ? 0 : addr,
            ...state.mergedBytes.map(b => {
                const n = parseInt(b, 10)
                return isNaN(n) ? 0 : n
            })
        ]
    }
    return 0
}

function buildRegister2Value(state: Register2State): unknown {
    if (state.type === "int") {
        const num = parseInt(state.intValue, 10)
        return isNaN(num) ? 0 : num
    }
    if (state.type === "bytes") {
        return [
            state.sign,
            ...state.bytes.map(b => {
                const n = parseInt(b, 10)
                return isNaN(n) ? 0 : n
            })
        ]
    }
    return 0
}

function isRegister5Zero(state: Register5State): boolean {
    if (state.type === "int") {
        return parseInt(state.intValue, 10) === 0 || state.intValue.trim() === ""
    }
    if (state.type === "text") {
        return state.intValue.trim() === "" || state.intValue === "     "
    }
    if (state.type === "bytes") {
        return state.bytes.every(b => parseInt(b, 10) === 0 || b.trim() === "")
    }
    if (state.type === "merged-bytes") {
        const addrZero = parseInt(state.addr, 10) === 0 || state.addr.trim() === ""
        const bytesZero = state.mergedBytes.every(b => parseInt(b, 10) === 0 || b.trim() === "")
        return addrZero && bytesZero
    }
    return true
}

function isRegister2Zero(state: Register2State): boolean {
    if (state.type === "int") {
        return parseInt(state.intValue, 10) === 0 || state.intValue.trim() === ""
    }
    if (state.type === "bytes") {
        return state.bytes.every(b => parseInt(b, 10) === 0 || b.trim() === "")
    }
    return true
}

export function writeRegistersToIOSpec(state: RegisterState): void {
    const spec = parseIOSpec()

    for (const name of ["A", "X"] as const) {
        const reg = state[name]
        if (isRegister5Zero(reg)) {
            delete spec[name]
        } else {
            spec[name] = buildRegister5Value(reg)
        }
    }

    for (const name of ["I1", "I2", "I3", "I4", "I5", "I6", "J"] as const) {
        const reg = state[name]
        if (isRegister2Zero(reg)) {
            delete spec[name]
        } else {
            spec[name] = buildRegister2Value(reg)
        }
    }

    ioSpecEditor.value = JSON.stringify(spec, null, 2)
    ioSpecEditor.dispatchEvent(new Event("input", { bubbles: true }))
}

export function readResultsRegisters(): Record<string, { int?: number; float?: number; bytes?: string; text?: string }> {
    try {
        const results = json5.parse(resultsEditor.value) || {}
        const output: Record<string, { int?: number; float?: number; bytes?: string; text?: string }> = {}
        for (const name of ["A", "X", "I1", "I2", "I3", "I4", "I5", "I6", "J"]) {
            if (name in results) {
                output[name] = results[name]
            }
        }
        return output
    } catch {
        return {}
    }
}

function updateRegister5InputVisibility(name: string, type: Register5Type) {
    const intDiv = document.getElementById(`reg-${name}-input-int`)!
    const textDiv = document.getElementById(`reg-${name}-input-text`)!
    const bytesDiv = document.getElementById(`reg-${name}-input-bytes`)!
    const mergedDiv = document.getElementById(`reg-${name}-input-merged`)!

    intDiv.classList.add("hidden")
    textDiv.classList.add("hidden")
    bytesDiv.classList.add("hidden")
    mergedDiv.classList.add("hidden")

    if (type === "int") {
        intDiv.classList.remove("hidden")
    } else if (type === "text") {
        textDiv.classList.remove("hidden")
    } else if (type === "bytes") {
        bytesDiv.classList.remove("hidden")
    } else if (type === "merged-bytes") {
        mergedDiv.classList.remove("hidden")
    }
}

function updateRegister2InputVisibility(name: string, type: Register2Type) {
    const intDiv = document.getElementById(`reg-${name}-input-int`)!
    const bytesDiv = document.getElementById(`reg-${name}-input-bytes`)!

    intDiv.classList.add("hidden")
    bytesDiv.classList.add("hidden")

    if (type === "int") {
        intDiv.classList.remove("hidden")
    } else if (type === "bytes") {
        bytesDiv.classList.remove("hidden")
    }
}

function readRegister5FromUI(name: string): Register5State {
    const typeSelect = document.getElementById(`reg-${name}-type`) as HTMLSelectElement
    const valueInput = document.getElementById(`reg-${name}-value`) as HTMLInputElement
    const textInput = document.getElementById(`reg-${name}-text`) as HTMLInputElement
    const signSelect = document.getElementById(`reg-${name}-sign`) as HTMLSelectElement
    const signSelectM = document.getElementById(`reg-${name}-sign-m`) as HTMLSelectElement
    const addrInput = document.getElementById(`reg-${name}-addr`) as HTMLInputElement

    const type = typeSelect.value as Register5Type
    const state: Register5State = {
        type,
        intValue: type === "text" ? textInput.value : valueInput.value,
        sign: type === "merged-bytes" ? signSelectM.value : signSelect.value,
        bytes: [1, 2, 3, 4, 5].map(i => {
            const input = document.getElementById(`reg-${name}-b${i}`) as HTMLInputElement
            return input.value
        }),
        addr: addrInput.value,
        mergedBytes: [3, 4, 5].map(i => {
            const input = document.getElementById(`reg-${name}-b${i}m`) as HTMLInputElement
            return input.value
        }),
    }
    return state
}

function readRegister2FromUI(name: string): Register2State {
    const typeSelect = document.getElementById(`reg-${name}-type`) as HTMLSelectElement
    const valueInput = document.getElementById(`reg-${name}-value`) as HTMLInputElement
    const signSelect = document.getElementById(`reg-${name}-sign`) as HTMLSelectElement

    const type = typeSelect.value as Register2Type
    const state: Register2State = {
        type,
        intValue: valueInput.value,
        sign: signSelect.value,
        bytes: [1, 2].map(i => {
            const input = document.getElementById(`reg-${name}-b${i}`) as HTMLInputElement
            return input.value
        }),
    }
    return state
}

function writeRegister5ToUI(name: string, state: Register5State) {
    const typeSelect = document.getElementById(`reg-${name}-type`) as HTMLSelectElement
    const valueInput = document.getElementById(`reg-${name}-value`) as HTMLInputElement
    const textInput = document.getElementById(`reg-${name}-text`) as HTMLInputElement
    const signSelect = document.getElementById(`reg-${name}-sign`) as HTMLSelectElement
    const signSelectM = document.getElementById(`reg-${name}-sign-m`) as HTMLSelectElement
    const addrInput = document.getElementById(`reg-${name}-addr`) as HTMLInputElement

    typeSelect.value = state.type
    if (state.type === "text") {
        textInput.value = state.intValue
    } else {
        valueInput.value = state.intValue
    }
    signSelect.value = state.sign
    signSelectM.value = state.sign
    addrInput.value = state.addr

    for (let i = 0; i < 5; i++) {
        const input = document.getElementById(`reg-${name}-b${i + 1}`) as HTMLInputElement
        input.value = state.bytes[i] || "0"
    }
    for (let i = 0; i < 3; i++) {
        const input = document.getElementById(`reg-${name}-b${i + 3}m`) as HTMLInputElement
        input.value = state.mergedBytes[i] || "0"
    }

    updateRegister5InputVisibility(name, state.type)
}

function writeRegister2ToUI(name: string, state: Register2State) {
    const typeSelect = document.getElementById(`reg-${name}-type`) as HTMLSelectElement
    const valueInput = document.getElementById(`reg-${name}-value`) as HTMLInputElement
    const signSelect = document.getElementById(`reg-${name}-sign`) as HTMLSelectElement

    typeSelect.value = state.type
    valueInput.value = state.intValue
    signSelect.value = state.sign

    for (let i = 0; i < 2; i++) {
        const input = document.getElementById(`reg-${name}-b${i + 1}`) as HTMLInputElement
        input.value = state.bytes[i] || "0"
    }

    updateRegister2InputVisibility(name, state.type)
}

export function initRegistersTab(): void {
    const tabCodes = document.getElementById("tab-codes")!
    const tabRegisters = document.getElementById("tab-registers")!
    const panelCodes = document.getElementById("panel-codes")!
    const panelRegisters = document.getElementById("panel-registers")!

    function switchToTab(tab: "codes" | "registers") {
        if (tab === "codes") {
            tabCodes.classList.add("border-blue-500", "text-blue-600", "dark:text-blue-400")
            tabCodes.classList.remove("border-transparent", "text-gray-500", "dark:text-gray-400")
            tabRegisters.classList.remove("border-blue-500", "text-blue-600", "dark:text-blue-400")
            tabRegisters.classList.add("border-transparent", "text-gray-500", "dark:text-gray-400")
            panelCodes.classList.remove("hidden")
            panelRegisters.classList.add("hidden")
        } else {
            tabRegisters.classList.add("border-blue-500", "text-blue-600", "dark:text-blue-400")
            tabRegisters.classList.remove("border-transparent", "text-gray-500", "dark:text-gray-400")
            tabCodes.classList.remove("border-blue-500", "text-blue-600", "dark:text-blue-400")
            tabCodes.classList.add("border-transparent", "text-gray-500", "dark:text-gray-400")
            panelRegisters.classList.remove("hidden")
            panelCodes.classList.add("hidden")
            syncFromIOSpec()
            syncResultsDisplay()
        }
    }

    function syncFromIOSpec() {
        const state = readRegistersFromIOSpec()
        for (const name of ["A", "X"] as const) {
            writeRegister5ToUI(name, state[name])
        }
        for (const name of ["I1", "I2", "I3", "I4", "I5", "I6", "J"] as const) {
            writeRegister2ToUI(name, state[name])
        }
    }

    function syncToIOSpec() {
        const state = getDefaultState()
        for (const name of ["A", "X"] as const) {
            state[name] = readRegister5FromUI(name)
        }
        for (const name of ["I1", "I2", "I3", "I4", "I5", "I6", "J"] as const) {
            state[name] = readRegister2FromUI(name)
        }
        writeRegistersToIOSpec(state)
    }

    function syncResultsDisplay() {
        const results = readResultsRegisters()
        for (const name of ["A", "X"]) {
            const intEl = document.getElementById(`result-${name}-int`)!
            const floatEl = document.getElementById(`result-${name}-float`)!
            const bytesEl = document.getElementById(`result-${name}-bytes`)!
            const textEl = document.getElementById(`result-${name}-text`)!
            if (results[name]) {
                intEl.textContent = String(results[name].int ?? "")
                floatEl.textContent = String(results[name].float ?? "")
                bytesEl.textContent = results[name].bytes ?? ""
                textEl.textContent = results[name].text ?? ""
            } else {
                intEl.textContent = ""
                floatEl.textContent = ""
                bytesEl.textContent = ""
                textEl.textContent = ""
            }
        }
        for (const name of ["I1", "I2", "I3", "I4", "I5", "I6", "J"]) {
            const intEl = document.getElementById(`result-${name}-int`)!
            const bytesEl = document.getElementById(`result-${name}-bytes`)!
            if (results[name]) {
                intEl.textContent = String(results[name].int ?? "")
                bytesEl.textContent = results[name].bytes ?? ""
            } else {
                intEl.textContent = ""
                bytesEl.textContent = ""
            }
        }
    }

    tabCodes.addEventListener("click", () => {
        syncToIOSpec()
        switchToTab("codes")
    })

    tabRegisters.addEventListener("click", () => {
        switchToTab("registers")
    })

    for (const name of ["A", "X"]) {
        const typeSelect = document.getElementById(`reg-${name}-type`) as HTMLSelectElement
        typeSelect.addEventListener("change", () => {
            updateRegister5InputVisibility(name, typeSelect.value as Register5Type)
        })
    }

    for (const name of ["I1", "I2", "I3", "I4", "I5", "I6", "J"]) {
        const typeSelect = document.getElementById(`reg-${name}-type`) as HTMLSelectElement
        typeSelect.addEventListener("change", () => {
            updateRegister2InputVisibility(name, typeSelect.value as Register2Type)
        })
    }

    resultsEditor.addEventListener("input", () => {
        if (!panelRegisters.classList.contains("hidden")) {
            syncResultsDisplay()
        }
    })
}
