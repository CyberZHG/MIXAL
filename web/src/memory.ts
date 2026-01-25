import json5 from "json5"
import { onRegistersTabEnter, onRegistersTabLeave } from "./registers"
import { onDevicesTabEnter, onDevicesTabLeave } from "./io_devices"

type WordType = "int" | "text" | "bytes" | "merged-bytes"

interface WordState {
    type: WordType
    intValue: string
    sign: string
    bytes: string[]
    addr: string
    mergedBytes: string[]
}

interface MemoryBlock {
    id: string
    offset: string
    words: WordState[]
}

interface OutputBlock {
    id: string
    offset: string
    length: string
    type: "int" | "text" | "bytes" | "float"
}

const ioSpecEditor = document.querySelector<HTMLTextAreaElement>("#io-spec-editor")!
const resultsEditor = document.querySelector<HTMLTextAreaElement>("#results-editor")!

let memoryBlocks: MemoryBlock[] = []
let outputBlocks: OutputBlock[] = []
let blockIdCounter = 0

function generateId(): string {
    return `mem-${++blockIdCounter}`
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

function readMemoryFromIOSpec(): MemoryBlock[] {
    const spec = parseIOSpec()
    const blocks: MemoryBlock[] = []

    if ("memory" in spec) {
        let memorySpec = spec.memory
        if (!Array.isArray(memorySpec)) {
            memorySpec = [memorySpec]
        }
        for (const block of memorySpec as Array<{ offset?: number; values?: unknown[] | string }>) {
            const memBlock: MemoryBlock = {
                id: generateId(),
                offset: String(block.offset ?? 0),
                words: [],
            }
            const values = block.values
            if (Array.isArray(values)) {
                if (typeof values[0] === "string" && values[0].length <= 5 && values.every(v => typeof v === "string")) {
                    for (const v of values) {
                        const word = getDefaultWordState()
                        word.type = "text"
                        word.intValue = v as string
                        memBlock.words.push(word)
                    }
                } else {
                    for (const v of values) {
                        memBlock.words.push(detectWordState(v))
                    }
                }
            } else if (typeof values === "string") {
                for (let i = 0; i < values.length; i += 5) {
                    const word = getDefaultWordState()
                    word.type = "text"
                    word.intValue = values.substring(i, i + 5)
                    memBlock.words.push(word)
                }
            }
            if (memBlock.words.length === 0) {
                memBlock.words.push(getDefaultWordState())
            }
            blocks.push(memBlock)
        }
    }

    return blocks
}

function readOutputsFromIOSpec(): OutputBlock[] {
    const spec = parseIOSpec()
    const blocks: OutputBlock[] = []

    if ("outputs" in spec && spec.outputs && typeof spec.outputs === "object") {
        const outputs = spec.outputs as Record<string, unknown>
        if ("memory" in outputs) {
            let memoryOutputs = outputs.memory
            if (!Array.isArray(memoryOutputs)) {
                memoryOutputs = [memoryOutputs]
            }
            for (const out of memoryOutputs as Array<{ offset?: number; length?: number; type?: string }>) {
                blocks.push({
                    id: generateId(),
                    offset: String(out.offset ?? 0),
                    length: String(out.length ?? 1),
                    type: (out.type as "int" | "text" | "bytes" | "float") ?? "int",
                })
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

function writeMemoryToIOSpec(): void {
    const spec = parseIOSpec()

    if (memoryBlocks.length === 0) {
        delete spec.memory
    } else {
        const memArray = memoryBlocks.map(block => {
            const offset = parseInt(block.offset, 10) || 0
            const values = block.words.map(buildWordValue)
            return { offset, values }
        })
        spec.memory = memArray.length === 1 ? memArray[0] : memArray
    }

    if (outputBlocks.length === 0) {
        if (spec.outputs && typeof spec.outputs === "object") {
            delete (spec.outputs as Record<string, unknown>).memory
            if (Object.keys(spec.outputs as object).length === 0) {
                delete spec.outputs
            }
        }
    } else {
        if (!spec.outputs) {
            spec.outputs = {}
        }
        const outArray = outputBlocks.map(block => ({
            offset: parseInt(block.offset, 10) || 0,
            length: parseInt(block.length, 10) || 1,
            type: block.type,
        }))
        ;(spec.outputs as Record<string, unknown>).memory = outArray.length === 1 ? outArray[0] : outArray
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

function createMemoryBlockHTML(block: MemoryBlock): string {
    const wordsHTML = block.words.map((w, i) => createWordInputHTML(block.id, i, w)).join("")
    return `
    <div class="memory-block border border-gray-300 dark:border-gray-600 rounded p-3 space-y-2" data-block-id="${block.id}">
      <div class="flex items-center gap-2">
        <label class="text-xs font-bold">Offset:</label>
        <input type="number" min="0" max="3999" value="${block.offset}" class="block-offset w-20 px-2 py-1 text-xs font-mono border border-gray-300 dark:border-gray-600 rounded bg-white dark:bg-gray-700">
        <div class="flex-1"></div>
        <button class="word-add px-2 py-1 text-xs bg-green-600 hover:bg-green-700 text-white rounded">+ Word</button>
        <button class="block-delete px-2 py-1 text-xs bg-red-600 hover:bg-red-700 text-white rounded">Delete Block</button>
      </div>
      <div class="words-container space-y-1">${wordsHTML}</div>
    </div>`
}

function createOutputBlockHTML(block: OutputBlock): string {
    return `
    <div class="output-block border border-gray-300 dark:border-gray-600 rounded p-3" data-block-id="${block.id}">
      <div class="flex items-center gap-2 flex-wrap">
        <label class="text-xs font-bold">Offset:</label>
        <input type="number" min="0" max="3999" value="${block.offset}" class="output-offset w-16 px-1 py-1 text-xs font-mono border border-gray-300 dark:border-gray-600 rounded bg-white dark:bg-gray-700">
        <label class="text-xs font-bold">Length:</label>
        <input type="number" min="1" max="4000" value="${block.length}" class="output-length w-16 px-1 py-1 text-xs font-mono border border-gray-300 dark:border-gray-600 rounded bg-white dark:bg-gray-700">
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

function renderMemoryBlocks() {
    const container = document.getElementById("memory-blocks-container")!
    container.innerHTML = memoryBlocks.map(createMemoryBlockHTML).join("")
    attachMemoryBlockListeners()
}

function renderOutputBlocks() {
    const container = document.getElementById("memory-outputs-container")!
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
    for (const block of memoryBlocks) {
        const blockEl = document.querySelector(`[data-block-id="${block.id}"]`)
        if (!blockEl) continue
        block.offset = (blockEl.querySelector(".block-offset") as HTMLInputElement).value
        const wordEls = blockEl.querySelectorAll("[data-word-index]")
        block.words = Array.from(wordEls).map((_, i) => readWordFromDOM(block.id, i))
    }
}

function syncOutputsFromDOM() {
    for (const block of outputBlocks) {
        const blockEl = document.querySelector(`.output-block[data-block-id="${block.id}"]`)
        if (!blockEl) continue
        block.offset = (blockEl.querySelector(".output-offset") as HTMLInputElement).value
        block.length = (blockEl.querySelector(".output-length") as HTMLInputElement).value
        block.type = (blockEl.querySelector(".output-type") as HTMLSelectElement).value as "int" | "text" | "bytes" | "float"
    }
}

function attachMemoryBlockListeners() {
    document.querySelectorAll(".memory-block").forEach(blockEl => {
        const blockId = blockEl.getAttribute("data-block-id")!

        blockEl.querySelector(".block-delete")?.addEventListener("click", () => {
            memoryBlocks = memoryBlocks.filter(b => b.id !== blockId)
            renderMemoryBlocks()
        })

        blockEl.querySelector(".word-add")?.addEventListener("click", () => {
            const block = memoryBlocks.find(b => b.id === blockId)
            if (block) {
                syncBlocksFromDOM()
                block.words.push(getDefaultWordState())
                renderMemoryBlocks()
            }
        })

        blockEl.querySelectorAll(".word-delete").forEach((btn, wordIndex) => {
            btn.addEventListener("click", () => {
                const block = memoryBlocks.find(b => b.id === blockId)
                if (block && block.words.length > 1) {
                    syncBlocksFromDOM()
                    block.words.splice(wordIndex, 1)
                    renderMemoryBlocks()
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
    })
}

function attachOutputBlockListeners() {
    document.querySelectorAll(".output-block").forEach(blockEl => {
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
    const container = document.getElementById("memory-results-container")!
    try {
        const results = json5.parse(resultsEditor.value) || {}
        if (!("memory" in results)) {
            container.innerHTML = '<p class="text-gray-500 text-sm">No memory output</p>'
            return
        }
        let memResults = results.memory
        if (!Array.isArray(memResults)) {
            memResults = [memResults]
        }
        let html = ""
        for (const result of memResults) {
            const offset = result.offset ?? 0
            const type = result.type ?? "int"
            html += `<div class="border border-gray-300 dark:border-gray-600 rounded p-2 mb-2">
                <div class="text-xs font-bold mb-1">Offset: ${offset} | Type: ${type}</div>
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
        container.innerHTML = html
    } catch {
        container.innerHTML = '<p class="text-gray-500 text-sm">No results</p>'
    }
}

export function initMemoryTab(): void {
    const tabCodes = document.getElementById("tab-codes")!
    const tabRegisters = document.getElementById("tab-registers")!
    const tabMemory = document.getElementById("tab-memory")!
    const tabDevices = document.getElementById("tab-devices")!
    const panelCodes = document.getElementById("panel-codes")!
    const panelRegisters = document.getElementById("panel-registers")!
    const panelMemory = document.getElementById("panel-memory")!
    const panelDevices = document.getElementById("panel-devices")!

    function switchToTab(tab: "codes" | "registers" | "memory" | "devices") {
        const wasRegisters = !panelRegisters.classList.contains("hidden")
        const wasMemory = !panelMemory.classList.contains("hidden")
        const wasDevices = !panelDevices.classList.contains("hidden")

        if (wasRegisters && tab !== "registers") {
            onRegistersTabLeave()
        }
        if (wasMemory && tab !== "memory") {
            syncToIOSpec()
        }
        if (wasDevices && tab !== "devices") {
            onDevicesTabLeave()
        }

        [tabCodes, tabRegisters, tabMemory, tabDevices].forEach(t => {
            t.classList.remove("border-blue-500", "text-blue-600", "dark:text-blue-400")
            t.classList.add("border-transparent", "text-gray-500", "dark:text-gray-400")
        })
        ;[panelCodes, panelRegisters, panelMemory, panelDevices].forEach(p => p.classList.add("hidden"))

        if (tab === "codes") {
            tabCodes.classList.add("border-blue-500", "text-blue-600", "dark:text-blue-400")
            tabCodes.classList.remove("border-transparent", "text-gray-500", "dark:text-gray-400")
            panelCodes.classList.remove("hidden")
        } else if (tab === "registers") {
            tabRegisters.classList.add("border-blue-500", "text-blue-600", "dark:text-blue-400")
            tabRegisters.classList.remove("border-transparent", "text-gray-500", "dark:text-gray-400")
            panelRegisters.classList.remove("hidden")
            onRegistersTabEnter()
        } else if (tab === "memory") {
            tabMemory.classList.add("border-blue-500", "text-blue-600", "dark:text-blue-400")
            tabMemory.classList.remove("border-transparent", "text-gray-500", "dark:text-gray-400")
            panelMemory.classList.remove("hidden")
            syncFromIOSpec()
            renderResults()
        } else if (tab === "devices") {
            tabDevices.classList.add("border-blue-500", "text-blue-600", "dark:text-blue-400")
            tabDevices.classList.remove("border-transparent", "text-gray-500", "dark:text-gray-400")
            panelDevices.classList.remove("hidden")
            onDevicesTabEnter()
        }
    }

    function syncFromIOSpec() {
        memoryBlocks = readMemoryFromIOSpec()
        outputBlocks = readOutputsFromIOSpec()
        if (memoryBlocks.length === 0) {
            memoryBlocks = []
        }
        renderMemoryBlocks()
        renderOutputBlocks()
    }

    function syncToIOSpec() {
        syncBlocksFromDOM()
        syncOutputsFromDOM()
        writeMemoryToIOSpec()
    }

    tabCodes.addEventListener("click", () => switchToTab("codes"))
    tabRegisters.addEventListener("click", () => switchToTab("registers"))
    tabMemory.addEventListener("click", () => switchToTab("memory"))
    tabDevices.addEventListener("click", () => switchToTab("devices"))

    document.getElementById("add-memory-block")?.addEventListener("click", () => {
        syncBlocksFromDOM()
        memoryBlocks.push({
            id: generateId(),
            offset: "0",
            words: [getDefaultWordState()],
        })
        renderMemoryBlocks()
    })

    document.getElementById("add-output-block")?.addEventListener("click", () => {
        syncOutputsFromDOM()
        outputBlocks.push({
            id: generateId(),
            offset: "0",
            length: "1",
            type: "int",
        })
        renderOutputBlocks()
    })

    resultsEditor.addEventListener("input", () => {
        if (!panelMemory.classList.contains("hidden")) {
            renderResults()
        }
    })
}
