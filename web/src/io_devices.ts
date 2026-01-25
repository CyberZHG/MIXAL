import json5 from "json5"

type WordType = "int" | "text" | "bytes" | "merged-bytes"

interface WordState {
    type: WordType
    intValue: string
    sign: string
    bytes: string[]
    addr: string
    mergedBytes: string[]
}

interface DeviceBlock {
    id: string
    device: string
    offset: string
    isTextDevice: boolean
    textValue: string
    words: WordState[]
}

interface OutputBlock {
    id: string
    device: string
    offset: string
    length: string
    type: "int" | "text" | "bytes" | "float"
}

const DEVICE_OPTIONS = [
    { value: "magnetic-tape-0", label: "Magnetic Tape 0", isText: false },
    { value: "magnetic-tape-1", label: "Magnetic Tape 1", isText: false },
    { value: "magnetic-tape-2", label: "Magnetic Tape 2", isText: false },
    { value: "magnetic-tape-3", label: "Magnetic Tape 3", isText: false },
    { value: "magnetic-tape-4", label: "Magnetic Tape 4", isText: false },
    { value: "magnetic-tape-5", label: "Magnetic Tape 5", isText: false },
    { value: "magnetic-tape-6", label: "Magnetic Tape 6", isText: false },
    { value: "magnetic-tape-7", label: "Magnetic Tape 7", isText: false },
    { value: "disk-8", label: "Disk 8", isText: false },
    { value: "disk-9", label: "Disk 9", isText: false },
    { value: "disk-10", label: "Disk 10", isText: false },
    { value: "disk-11", label: "Disk 11", isText: false },
    { value: "disk-12", label: "Disk 12", isText: false },
    { value: "disk-13", label: "Disk 13", isText: false },
    { value: "disk-14", label: "Disk 14", isText: false },
    { value: "disk-15", label: "Disk 15", isText: false },
    { value: "card-reader", label: "Card Reader (16)", isText: true },
    { value: "card-punch", label: "Card Punch (17)", isText: false },
    { value: "line-printer", label: "Line Printer (18)", isText: true },
    { value: "typewriter", label: "Typewriter (19)", isText: true },
    { value: "paper-tape", label: "Paper Tape (20)", isText: false },
]

const TEXT_DEVICES = ["card-reader", "line-printer", "typewriter"]

const ioSpecEditor = document.querySelector<HTMLTextAreaElement>("#io-spec-editor")!
const resultsEditor = document.querySelector<HTMLTextAreaElement>("#results-editor")!

let deviceBlocks: DeviceBlock[] = []
let outputBlocks: OutputBlock[] = []
let blockIdCounter = 0

function generateId(): string {
    return `dev-${++blockIdCounter}`
}

function isTextDevice(device: string): boolean {
    return TEXT_DEVICES.includes(device)
}

function getDefaultWordState(): WordState {
    return {
        type: "int",
        intValue: "0",
        sign: "+",
        bytes: ["0", "0", "0", "0", "0"],
        addr: "0",
        mergedBytes: ["0", "0", "0"],
    }
}

function parseIOSpec(): Record<string, unknown> {
    try {
        return json5.parse(ioSpecEditor.value) || {}
    } catch {
        return {}
    }
}

function detectWordState(value: unknown): WordState {
    const state = getDefaultWordState()
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

function readDevicesFromIOSpec(): DeviceBlock[] {
    const spec = parseIOSpec()
    const blocks: DeviceBlock[] = []

    for (const opt of DEVICE_OPTIONS) {
        const deviceName = opt.value
        if (deviceName in spec) {
            let deviceSpec = spec[deviceName]
            if (!Array.isArray(deviceSpec)) {
                deviceSpec = [deviceSpec]
            }
            for (const block of deviceSpec as Array<{ offset?: number; values?: unknown[] | string }>) {
                const isText = isTextDevice(deviceName)
                const devBlock: DeviceBlock = {
                    id: generateId(),
                    device: deviceName,
                    offset: String(block.offset ?? 0),
                    isTextDevice: isText,
                    textValue: "",
                    words: [],
                }

                const values = block.values
                if (isText) {
                    if (typeof values === "string") {
                        devBlock.textValue = values
                    } else if (Array.isArray(values) && values.every(v => typeof v === "string")) {
                        devBlock.textValue = (values as string[]).join("\n")
                    } else if (Array.isArray(values)) {
                        devBlock.textValue = (values as string[]).join("")
                    }
                } else {
                    if (Array.isArray(values)) {
                        if (typeof values[0] === "string" && values.every(v => typeof v === "string")) {
                            for (const v of values) {
                                const word = getDefaultWordState()
                                word.type = "text"
                                word.intValue = v as string
                                devBlock.words.push(word)
                            }
                        } else {
                            for (const v of values) {
                                devBlock.words.push(detectWordState(v))
                            }
                        }
                    } else if (typeof values === "string") {
                        for (let i = 0; i < values.length; i += 5) {
                            const word = getDefaultWordState()
                            word.type = "text"
                            word.intValue = values.substring(i, i + 5)
                            devBlock.words.push(word)
                        }
                    }
                    if (devBlock.words.length === 0) {
                        devBlock.words.push(getDefaultWordState())
                    }
                }
                blocks.push(devBlock)
            }
        }
    }

    return blocks
}

function readOutputsFromIOSpec(): OutputBlock[] {
    const spec = parseIOSpec()
    const blocks: OutputBlock[] = []

    if ("outputs" in spec && spec.outputs && typeof spec.outputs === "object") {
        const outputs = spec.outputs as Record<string, unknown>
        for (const opt of DEVICE_OPTIONS) {
            const deviceName = opt.value
            if (deviceName in outputs) {
                let deviceOutputs = outputs[deviceName]
                if (!Array.isArray(deviceOutputs)) {
                    deviceOutputs = [deviceOutputs]
                }
                for (const out of deviceOutputs as Array<{ offset?: number; length?: number; type?: string }>) {
                    blocks.push({
                        id: generateId(),
                        device: deviceName,
                        offset: String(out.offset ?? 0),
                        length: String(out.length ?? 1),
                        type: (out.type as "int" | "text" | "bytes" | "float") ?? (isTextDevice(deviceName) ? "text" : "int"),
                    })
                }
            }
        }
    }

    return blocks
}

function buildWordValue(state: WordState): unknown {
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

function writeDevicesToIOSpec(): void {
    const spec = parseIOSpec()

    for (const opt of DEVICE_OPTIONS) {
        delete spec[opt.value]
    }

    const grouped: Record<string, Array<{ offset: number; values: unknown }>> = {}
    for (const block of deviceBlocks) {
        if (!grouped[block.device]) {
            grouped[block.device] = []
        }
        const offset = parseInt(block.offset, 10) || 0
        let values: unknown
        if (block.isTextDevice) {
            values = block.textValue
        } else {
            values = block.words.map(buildWordValue)
        }
        grouped[block.device].push({ offset, values })
    }

    for (const [device, blocks] of Object.entries(grouped)) {
        spec[device] = blocks.length === 1 ? blocks[0] : blocks
    }

    if (!spec.outputs) {
        spec.outputs = {}
    }
    const outputs = spec.outputs as Record<string, unknown>
    for (const opt of DEVICE_OPTIONS) {
        delete outputs[opt.value]
    }

    const groupedOutputs: Record<string, Array<{ offset: number; length: number; type: string }>> = {}
    for (const block of outputBlocks) {
        if (!groupedOutputs[block.device]) {
            groupedOutputs[block.device] = []
        }
        groupedOutputs[block.device].push({
            offset: parseInt(block.offset, 10) || 0,
            length: parseInt(block.length, 10) || 1,
            type: block.type,
        })
    }

    for (const [device, blocks] of Object.entries(groupedOutputs)) {
        outputs[device] = blocks.length === 1 ? blocks[0] : blocks
    }

    if (Object.keys(outputs).length === 0) {
        delete spec.outputs
    }

    ioSpecEditor.value = JSON.stringify(spec, null, 2)
    ioSpecEditor.dispatchEvent(new Event("input", { bubbles: true }))
}

function createWordInputHTML(blockId: string, wordIndex: number, word: WordState): string {
    const wid = `${blockId}-w${wordIndex}`
    return `
    <div class="flex items-center gap-1 p-2 bg-gray-50 dark:bg-gray-800 rounded" data-word-index="${wordIndex}">
      <select id="${wid}-type" class="w-24 px-1 py-1 text-xs border border-gray-300 dark:border-gray-600 rounded bg-white dark:bg-gray-700">
        <option value="int" ${word.type === "int" ? "selected" : ""}>Integer</option>
        <option value="text" ${word.type === "text" ? "selected" : ""}>Text</option>
        <option value="bytes" ${word.type === "bytes" ? "selected" : ""}>Bytes</option>
        <option value="merged-bytes" ${word.type === "merged-bytes" ? "selected" : ""}>Addr&Bytes</option>
      </select>
      <div id="${wid}-input-int" class="flex-1 flex gap-1 ${word.type === "int" ? "" : "hidden"}">
        <input id="${wid}-value" type="number" min="-1073741823" max="1073741823" value="${word.intValue}" class="flex-1 px-1 py-1 text-xs font-mono border border-gray-300 dark:border-gray-600 rounded bg-white dark:bg-gray-700">
      </div>
      <div id="${wid}-input-text" class="flex-1 flex gap-1 ${word.type === "text" ? "" : "hidden"}">
        <input id="${wid}-text" type="text" maxlength="5" value="${word.type === "text" ? word.intValue : ""}" placeholder="ABCDE" class="flex-1 px-1 py-1 text-xs font-mono border border-gray-300 dark:border-gray-600 rounded bg-white dark:bg-gray-700">
      </div>
      <div id="${wid}-input-bytes" class="flex-1 flex gap-1 ${word.type === "bytes" ? "" : "hidden"}">
        <select id="${wid}-sign" class="w-10 px-1 py-1 text-xs font-mono border border-gray-300 dark:border-gray-600 rounded bg-white dark:bg-gray-700">
          <option value="+" ${word.sign === "+" ? "selected" : ""}>+</option>
          <option value="-" ${word.sign === "-" ? "selected" : ""}>-</option>
        </select>
        ${[0,1,2,3,4].map(i => `<input id="${wid}-b${i+1}" type="number" min="0" max="63" value="${word.bytes[i]}" class="w-10 px-1 py-1 text-xs font-mono border border-gray-300 dark:border-gray-600 rounded bg-white dark:bg-gray-700 text-center">`).join("")}
      </div>
      <div id="${wid}-input-merged" class="flex-1 flex gap-1 ${word.type === "merged-bytes" ? "" : "hidden"}">
        <select id="${wid}-sign-m" class="w-10 px-1 py-1 text-xs font-mono border border-gray-300 dark:border-gray-600 rounded bg-white dark:bg-gray-700">
          <option value="+" ${word.sign === "+" ? "selected" : ""}>+</option>
          <option value="-" ${word.sign === "-" ? "selected" : ""}>-</option>
        </select>
        <input id="${wid}-addr" type="number" min="0" max="4095" value="${word.addr}" class="w-14 px-1 py-1 text-xs font-mono border border-gray-300 dark:border-gray-600 rounded bg-white dark:bg-gray-700 text-center">
        ${[0,1,2].map(i => `<input id="${wid}-b${i+3}m" type="number" min="0" max="63" value="${word.mergedBytes[i]}" class="w-10 px-1 py-1 text-xs font-mono border border-gray-300 dark:border-gray-600 rounded bg-white dark:bg-gray-700 text-center">`).join("")}
      </div>
      <button class="word-delete px-2 py-1 text-xs text-red-600 hover:text-red-800 dark:text-red-400" title="Delete word">&times;</button>
    </div>`
}

function escapeHtmlAttr(str: string): string {
    return str.replace(/&/g, "&amp;").replace(/"/g, "&quot;").replace(/</g, "&lt;").replace(/>/g, "&gt;")
}

function createDeviceBlockHTML(block: DeviceBlock): string {
    const deviceOptions = DEVICE_OPTIONS.map(opt =>
        `<option value="${opt.value}" ${block.device === opt.value ? "selected" : ""}>${opt.label}</option>`
    ).join("")

    if (block.isTextDevice) {
        return `
        <div class="device-block border border-gray-300 dark:border-gray-600 rounded p-3 space-y-2" data-block-id="${block.id}">
          <div class="flex items-center gap-2">
            <label class="text-xs font-bold">Device:</label>
            <select class="block-device flex-1 px-2 py-1 text-xs border border-gray-300 dark:border-gray-600 rounded bg-white dark:bg-gray-700">
              ${deviceOptions}
            </select>
            <button class="block-delete px-2 py-1 text-xs bg-red-600 hover:bg-red-700 text-white rounded">Delete</button>
          </div>
          <div class="flex items-center gap-2">
            <label class="text-xs font-bold">Offset:</label>
            <input type="number" min="0" value="${block.offset}" class="block-offset w-20 px-2 py-1 text-xs font-mono border border-gray-300 dark:border-gray-600 rounded bg-white dark:bg-gray-700">
            <span class="text-xs text-gray-500">(each line = 1 record)</span>
          </div>
          <textarea class="block-text w-full h-24 px-2 py-1 text-xs font-mono border border-gray-300 dark:border-gray-600 rounded bg-white dark:bg-gray-700 whitespace-pre" placeholder="Enter text">${escapeHtmlAttr(block.textValue)}</textarea>
        </div>`
    } else {
        const wordsHTML = block.words.map((w, i) => createWordInputHTML(block.id, i, w)).join("")
        return `
        <div class="device-block border border-gray-300 dark:border-gray-600 rounded p-3 space-y-2" data-block-id="${block.id}">
          <div class="flex items-center gap-2">
            <label class="text-xs font-bold">Device:</label>
            <select class="block-device flex-1 px-2 py-1 text-xs border border-gray-300 dark:border-gray-600 rounded bg-white dark:bg-gray-700">
              ${deviceOptions}
            </select>
            <button class="block-delete px-2 py-1 text-xs bg-red-600 hover:bg-red-700 text-white rounded">Delete</button>
          </div>
          <div class="flex items-center gap-2">
            <label class="text-xs font-bold">Offset:</label>
            <input type="number" min="0" value="${block.offset}" class="block-offset w-20 px-2 py-1 text-xs font-mono border border-gray-300 dark:border-gray-600 rounded bg-white dark:bg-gray-700">
            <div class="flex-1"></div>
            <button class="word-add px-2 py-1 text-xs bg-green-600 hover:bg-green-700 text-white rounded">+ Word</button>
          </div>
          <div class="words-container space-y-1">${wordsHTML}</div>
        </div>`
    }
}

function createOutputBlockHTML(block: OutputBlock): string {
    const deviceOptions = DEVICE_OPTIONS.map(opt =>
        `<option value="${opt.value}" ${block.device === opt.value ? "selected" : ""}>${opt.label}</option>`
    ).join("")

    return `
    <div class="output-block border border-gray-300 dark:border-gray-600 rounded p-3" data-block-id="${block.id}">
      <div class="flex items-center gap-2 flex-wrap">
        <label class="text-xs font-bold">Device:</label>
        <select class="output-device px-1 py-1 text-xs border border-gray-300 dark:border-gray-600 rounded bg-white dark:bg-gray-700">
          ${deviceOptions}
        </select>
        <label class="text-xs font-bold">Offset:</label>
        <input type="number" min="0" value="${block.offset}" class="output-offset w-14 px-1 py-1 text-xs font-mono border border-gray-300 dark:border-gray-600 rounded bg-white dark:bg-gray-700">
        <label class="text-xs font-bold">Length:</label>
        <input type="number" min="1" value="${block.length}" class="output-length w-14 px-1 py-1 text-xs font-mono border border-gray-300 dark:border-gray-600 rounded bg-white dark:bg-gray-700">
        <label class="text-xs font-bold">Type:</label>
        <select class="output-type px-1 py-1 text-xs border border-gray-300 dark:border-gray-600 rounded bg-white dark:bg-gray-700">
          <option value="int" ${block.type === "int" ? "selected" : ""}>Int</option>
          <option value="float" ${block.type === "float" ? "selected" : ""}>Float</option>
          <option value="text" ${block.type === "text" ? "selected" : ""}>Text</option>
          <option value="bytes" ${block.type === "bytes" ? "selected" : ""}>Bytes</option>
        </select>
        <button class="output-delete px-2 py-1 text-xs text-red-600 hover:text-red-800 dark:text-red-400">&times;</button>
      </div>
    </div>`
}

function renderDeviceBlocks() {
    const container = document.getElementById("device-blocks-container")!
    container.innerHTML = deviceBlocks.map(createDeviceBlockHTML).join("")
    attachDeviceBlockListeners()
}

function renderOutputBlocks() {
    const container = document.getElementById("device-outputs-container")!
    container.innerHTML = outputBlocks.map(createOutputBlockHTML).join("")
    attachOutputBlockListeners()
}

function readWordFromDOM(blockId: string, wordIndex: number): WordState {
    const wid = `${blockId}-w${wordIndex}`
    const typeSelect = document.getElementById(`${wid}-type`) as HTMLSelectElement
    const type = typeSelect.value as WordType

    const state: WordState = {
        type,
        intValue: "",
        sign: "+",
        bytes: ["0", "0", "0", "0", "0"],
        addr: "0",
        mergedBytes: ["0", "0", "0"],
    }

    if (type === "int") {
        state.intValue = (document.getElementById(`${wid}-value`) as HTMLInputElement).value
    } else if (type === "text") {
        state.intValue = (document.getElementById(`${wid}-text`) as HTMLInputElement).value
    } else if (type === "bytes") {
        state.sign = (document.getElementById(`${wid}-sign`) as HTMLSelectElement).value
        for (let i = 0; i < 5; i++) {
            state.bytes[i] = (document.getElementById(`${wid}-b${i+1}`) as HTMLInputElement).value
        }
    } else if (type === "merged-bytes") {
        state.sign = (document.getElementById(`${wid}-sign-m`) as HTMLSelectElement).value
        state.addr = (document.getElementById(`${wid}-addr`) as HTMLInputElement).value
        for (let i = 0; i < 3; i++) {
            state.mergedBytes[i] = (document.getElementById(`${wid}-b${i+3}m`) as HTMLInputElement).value
        }
    }

    return state
}

function syncBlocksFromDOM() {
    for (const block of deviceBlocks) {
        const blockEl = document.querySelector(`[data-block-id="${block.id}"]`)
        if (!blockEl) continue
        const newDevice = (blockEl.querySelector(".block-device") as HTMLSelectElement).value
        const newIsText = isTextDevice(newDevice)

        block.device = newDevice
        block.offset = (blockEl.querySelector(".block-offset") as HTMLInputElement).value

        if (block.isTextDevice) {
            block.textValue = (blockEl.querySelector(".block-text") as HTMLTextAreaElement)?.value ?? ""
        } else {
            const wordEls = blockEl.querySelectorAll("[data-word-index]")
            block.words = Array.from(wordEls).map((_, i) => readWordFromDOM(block.id, i))
        }

        if (block.isTextDevice !== newIsText) {
            block.isTextDevice = newIsText
            if (newIsText) {
                block.textValue = ""
                block.words = []
            } else {
                block.textValue = ""
                block.words = [getDefaultWordState()]
            }
        }
    }
}

function syncOutputsFromDOM() {
    for (const block of outputBlocks) {
        const blockEl = document.querySelector(`.output-block[data-block-id="${block.id}"]`)
        if (!blockEl) continue
        block.device = (blockEl.querySelector(".output-device") as HTMLSelectElement).value
        block.offset = (blockEl.querySelector(".output-offset") as HTMLInputElement).value
        block.length = (blockEl.querySelector(".output-length") as HTMLInputElement).value
        block.type = (blockEl.querySelector(".output-type") as HTMLSelectElement).value as "int" | "text" | "bytes" | "float"
    }
}

function attachDeviceBlockListeners() {
    document.querySelectorAll("#device-blocks-container .device-block").forEach(blockEl => {
        const blockId = blockEl.getAttribute("data-block-id")!
        const block = deviceBlocks.find(b => b.id === blockId)
        if (!block) return

        blockEl.querySelector(".block-delete")?.addEventListener("click", () => {
            deviceBlocks = deviceBlocks.filter(b => b.id !== blockId)
            renderDeviceBlocks()
        })

        blockEl.querySelector(".block-device")?.addEventListener("change", (e) => {
            const wasText = block.isTextDevice
            syncBlocksFromDOM()
            const newDevice = (e.target as HTMLSelectElement).value
            const newIsText = isTextDevice(newDevice)
            if (wasText !== newIsText) {
                renderDeviceBlocks()
            }
        })

        if (!block.isTextDevice) {
            blockEl.querySelector(".word-add")?.addEventListener("click", () => {
                syncBlocksFromDOM()
                block.words.push(getDefaultWordState())
                renderDeviceBlocks()
            })

            blockEl.querySelectorAll(".word-delete").forEach((btn, wordIndex) => {
                btn.addEventListener("click", () => {
                    if (block.words.length > 1) {
                        syncBlocksFromDOM()
                        block.words.splice(wordIndex, 1)
                        renderDeviceBlocks()
                    }
                })
            })

            blockEl.querySelectorAll("[data-word-index]").forEach((_, wordIndex) => {
                const wid = `${blockId}-w${wordIndex}`
                const typeSelect = document.getElementById(`${wid}-type`) as HTMLSelectElement
                typeSelect?.addEventListener("change", () => {
                    const type = typeSelect.value as WordType
                    document.getElementById(`${wid}-input-int`)?.classList.toggle("hidden", type !== "int")
                    document.getElementById(`${wid}-input-text`)?.classList.toggle("hidden", type !== "text")
                    document.getElementById(`${wid}-input-bytes`)?.classList.toggle("hidden", type !== "bytes")
                    document.getElementById(`${wid}-input-merged`)?.classList.toggle("hidden", type !== "merged-bytes")
                })
            })
        }
    })
}

function attachOutputBlockListeners() {
    document.querySelectorAll("#device-outputs-container .output-block").forEach(blockEl => {
        const blockId = blockEl.getAttribute("data-block-id")!
        blockEl.querySelector(".output-delete")?.addEventListener("click", () => {
            outputBlocks = outputBlocks.filter(b => b.id !== blockId)
            renderOutputBlocks()
        })
    })
}

function escapeHtml(text: string): string {
    return text
        .replace(/&/g, "&amp;")
        .replace(/</g, "&lt;")
        .replace(/>/g, "&gt;")
        .replace(/"/g, "&quot;")
        .replace(/'/g, "&#39;")
        .replace(/ /g, "&nbsp;")
}

function formatValue(v: unknown, type: string): string {
    if (type === "text" && typeof v === "string") {
        return escapeHtml(v)
    }
    return String(v)
}

function renderResults() {
    const container = document.getElementById("device-results-container")!
    try {
        const results = json5.parse(resultsEditor.value) || {}
        let html = ""

        for (const opt of DEVICE_OPTIONS) {
            const deviceName = opt.value
            if (!(deviceName in results)) continue

            let devResults = results[deviceName]
            if (!Array.isArray(devResults)) {
                devResults = [devResults]
            }

            for (const result of devResults) {
                const offset = result.offset ?? 0
                const type = result.type ?? "int"
                html += `<div class="border border-gray-300 dark:border-gray-600 rounded p-2 mb-2">
                    <div class="text-xs font-bold mb-1">${opt.label} | Offset: ${offset} | Type: ${type}</div>
                    <div class="font-mono text-xs break-all">`
                if ("value" in result) {
                    html += `<span class="bg-gray-100 dark:bg-gray-700 px-1 rounded">${formatValue(result.value, type)}</span>`
                } else if ("values" in result) {
                    if (Array.isArray(result.values)) {
                        html += result.values.map((v: unknown, i: number) =>
                            `<span class="bg-gray-100 dark:bg-gray-700 px-1 rounded mr-1 mb-1 inline-block">[${offset + i}] ${formatValue(v, type)}</span>`
                        ).join("")
                    } else {
                        html += `<span class="bg-gray-100 dark:bg-gray-700 px-1 rounded">${formatValue(result.values, type)}</span>`
                    }
                }
                html += `</div></div>`
            }
        }

        if (html === "") {
            container.innerHTML = '<p class="text-gray-500 text-sm">No device output</p>'
        } else {
            container.innerHTML = html
        }
    } catch {
        container.innerHTML = '<p class="text-gray-500 text-sm">No results</p>'
    }
}

export function onDevicesTabEnter(): void {
    deviceBlocks = readDevicesFromIOSpec()
    outputBlocks = readOutputsFromIOSpec()
    renderDeviceBlocks()
    renderOutputBlocks()
    renderResults()
}

export function onDevicesTabLeave(): void {
    syncBlocksFromDOM()
    syncOutputsFromDOM()
    writeDevicesToIOSpec()
}

export function initDevicesTab(): void {
    const panelDevices = document.getElementById("panel-devices")!

    document.getElementById("add-device-block")?.addEventListener("click", () => {
        syncBlocksFromDOM()
        deviceBlocks.push({
            id: generateId(),
            device: "card-reader",
            offset: "0",
            isTextDevice: true,
            textValue: "",
            words: [],
        })
        renderDeviceBlocks()
    })

    document.getElementById("add-device-output")?.addEventListener("click", () => {
        syncOutputsFromDOM()
        outputBlocks.push({
            id: generateId(),
            device: "card-reader",
            offset: "0",
            length: "1",
            type: "text",
        })
        renderOutputBlocks()
    })

    resultsEditor.addEventListener("input", () => {
        if (!panelDevices.classList.contains("hidden")) {
            renderResults()
        }
    })
}
