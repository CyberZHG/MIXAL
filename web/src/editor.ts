// Editor
const editor = document.querySelector<HTMLTextAreaElement>("#mixal-editor")!
const highlighted = document.querySelector<HTMLElement>("#mixal-editor-highlighted")!
const lineNumbers = document.querySelector<HTMLDivElement>("#mixal-editor-line-numbers")!
const ioSpecEditor = document.querySelector<HTMLTextAreaElement>("#io-spec-editor")!
const ioSpecHighlighted = document.querySelector<HTMLElement>("#io-spec-highlighted")!
const ioSpecLineNumbers = document.querySelector<HTMLDivElement>("#io-spec-line-numbers")!
const resultsEditor = document.querySelector<HTMLTextAreaElement>("#results-editor")!
const resultsHighlighted = document.querySelector<HTMLElement>("#results-highlighted")!
const resultsLineNumbers = document.querySelector<HTMLDivElement>("#results-line-numbers")!

const MIXAL_KEYWORDS = [
    "NOP", "ADD", "FADD", "SUB", "FSUB",
    "MUL", "FMUL", "DIV", "FDIV", "NUM",
    "CHAR", "HLT", "SLA", "SRA", "SLAX",
    "SRAX", "SLC", "SRC", "MOVE", "LDA",
    "LD1", "LD2", "LD3", "LD4", "LD5",
    "LD6", "LDX", "LDAN", "LD1N", "LD2N",
    "LD3N", "LD4N", "LD5N", "LD6N", "LDXN",
    "STA", "ST1", "ST2", "ST3", "ST4",
    "ST5", "ST6", "STX", "STJ", "STZ",
    "JBUS", "IOC", "IN", "OUT", "JRED",
    "JMP", "JSJ", "JOV", "JNOV", "JL",
    "JE", "JG", "JGE", "JNE", "JLE", "JAN",
    "JAZ", "JAP", "JANN", "JANZ", "JANP",
    "J1N", "J1Z", "J1P", "J1NN", "J1NZ",
    "J1NP", "J2N", "J2Z", "J2P", "J2NN",
    "J2NZ", "J2NP", "J3N", "J3Z", "J3P",
    "J3NN", "J3NZ", "J3NP", "J4N", "J4Z",
    "J4P", "J4NN", "J4NZ", "J4NP", "J5N",
    "J5Z", "J5P", "J5NN", "J5NZ", "J5NP",
    "J6N", "J6Z", "J6P", "J6NN", "J6NZ",
    "J6NP", "JXN", "JXZ", "JXP", "JXNN",
    "JXNZ", "JXNP", "INCA", "DECA", "ENTA",
    "ENNA", "INC1", "DEC1", "ENT1", "ENN1",
    "INC2", "DEC2", "ENT2", "ENN2", "INC3",
    "DEC3", "ENT3", "ENN3", "INC4", "DEC4",
    "ENT4", "ENN4", "INC5", "DEC5", "ENT5",
    "ENN5", "INC6", "DEC6", "ENT6", "ENN6",
    "INCX", "DECX", "ENTX", "ENNX", "CMPA",
    "FCMP", "CMP1", "CMP2", "CMP3", "CMP4",
    "CMP5", "CMP6", "CMPX"]
const MIXAL_KEYWORDS_REGEX = new RegExp(`\\b(${MIXAL_KEYWORDS.join("|")})\\b`, "g")
const MIXAL_PSEUDO_KEYWORDS = ["EQU", "ORIG", "CON", "ALF", "END"]
const MIXAL_PSEUDO_KEYWORDS_REGEX = new RegExp(`\\b(${MIXAL_PSEUDO_KEYWORDS.join("|")})\\b`, "g")

function highlightMIXAL(code: string) : string {
    return code
        .replace(/&/g, '&amp;')
        .replace(/</g, '&lt;')
        .replace(/>/g, '&gt;')
        .replace(/"/g, '&quot;')
        .replace(/'/g, '&#39;')
        .replace(/^((?:\S+[ \t]+|[ \t]+)(?:\S+[ \t]+){2})(\S.*)$/gm, '$1<span class="text-gray-400 italic">$2</span>')
        .replace(/^\*.*$/gm, (match) => {
            return `<span class="text-gray-400 italic">${match}</span>`
        })
        .replace(MIXAL_KEYWORDS_REGEX, (match) => {
            return `<span class="text-blue-700 font-bold">${match}</span>`
        })
        .replace(MIXAL_PSEUDO_KEYWORDS_REGEX, (match) => {
            return `<span class="text-blue-600 font-bold">${match}</span>`
        })
}

function updateLineNumbers(editor: HTMLTextAreaElement, element: HTMLDivElement) {
    const lines = editor.value.split('\n').length
    let html = ''
    for (let i = 1; i <= lines; i++) {
        html += i + '\n'
    }
    element.textContent = html + '\n'
}

function syncEditor() {
    highlighted.innerHTML = highlightMIXAL(editor.value) + '\n\n'
    updateLineNumbers(editor, lineNumbers)
}

editor.addEventListener('input', () => {
    syncEditor()
})

editor.addEventListener('scroll', () => {
    const pre = highlighted.parentElement!
    pre.scrollTop = editor.scrollTop
    pre.scrollLeft = editor.scrollLeft
    lineNumbers.scrollTop = editor.scrollTop
})

editor.addEventListener('keydown', (e: KeyboardEvent) => {
    const start = editor.selectionStart
    const end = editor.selectionEnd
    const value = editor.value
    if (e.key == "Enter") {
        e.preventDefault()
        const before = value.slice(0, start)
        const after = value.slice(end)
        const lineStart = before.lastIndexOf('\n') + 1
        const currentLine = before.slice(lineStart)
        const indentMatch = currentLine.match(/^\S*(?:\s+)?/)
        const currentIndent = indentMatch ? indentMatch[0] : ''
        const insertText = '\n' + ' '.repeat(currentIndent.length)
        editor.value = before + insertText + after
        editor.selectionStart = editor.selectionEnd = start + insertText.length
        editor.dispatchEvent(new Event('input'))
    }
})

function highlightJSON(code: string): string {
    const escaped = code
        .replace(/&/g, '&amp;')
        .replace(/</g, '&lt;')
        .replace(/>/g, '&gt;')
    return escaped.replace(
        /("(\\u[\da-fA-F]{4}|\\[^u]|[^\\"])*"(?:\s*:)?|\b(true|false|null)\b|-?\d+(?:\.\d+)?(?:[eE][+-]?\d+)?)/g,
        (match) => {
            let cls = "font-bold "
            if (/^"/.test(match)) {
                cls += /:$/.test(match) ? 'text-blue-800' : 'text-green-700'
            } else if (/true|false/.test(match)) {
                cls += 'text-purple-800'
            } else if (/null/.test(match)) {
                cls += 'text-gray-500'
            } else {
                cls += 'text-yellow-600'
            }
            return `<span class="${cls}">${match}</span>`
        }
    )
}

function syncJSONEditor(editor: HTMLTextAreaElement, highlighted: HTMLElement, lineNumbers: HTMLDivElement) {
    highlighted.innerHTML = highlightJSON(editor.value) + '\n\n'
    updateLineNumbers(editor, lineNumbers)
}

ioSpecEditor.addEventListener('input', () => {
    syncJSONEditor(ioSpecEditor, ioSpecHighlighted, ioSpecLineNumbers)
})

ioSpecEditor.addEventListener('scroll', () => {
    const pre = ioSpecHighlighted.parentElement!
    pre.scrollTop = ioSpecEditor.scrollTop
    pre.scrollLeft = ioSpecEditor.scrollLeft
    ioSpecLineNumbers.scrollTop = ioSpecEditor.scrollTop
})

ioSpecEditor.addEventListener('keydown', (e: KeyboardEvent) => {
    const start = ioSpecEditor.selectionStart
    const end = ioSpecEditor.selectionEnd
    const value = ioSpecEditor.value
    if (e.key == "Enter") {
        e.preventDefault()
        const before = value.slice(0, start)
        const after = value.slice(end)
        const lineStart = before.lastIndexOf('\n') + 1
        const currentLine = before.slice(lineStart)
        const indentMatch = currentLine.match(/^\s*/)
        const currentIndent = indentMatch ? indentMatch[0] : ''
        const shouldIndent = currentLine.trim().endsWith('{') || currentLine.trim().endsWith('[')
        const newIndent = shouldIndent ? currentIndent + "  " : currentIndent
        const insertText = '\n' + newIndent
        ioSpecEditor.value = before + insertText + after
        ioSpecEditor.selectionStart = ioSpecEditor.selectionEnd = start + insertText.length
        ioSpecEditor.dispatchEvent(new Event('input'))
    } else if (e.key == "Tab") {
        e.preventDefault()
        const before = value.slice(0, start)
        const after = value.slice(end)
        if (e.shiftKey) {
            if (before.endsWith("  ")) {
                ioSpecEditor.value = before.slice(0, -2) + after
                ioSpecEditor.selectionStart = ioSpecEditor.selectionEnd = start - 2
            } else if (before.endsWith(" ")) {
                ioSpecEditor.value = before.slice(0, -1) + after
                ioSpecEditor.selectionStart = ioSpecEditor.selectionEnd = start - 1
            }
        } else {
            ioSpecEditor.value = before + "  " + after
            ioSpecEditor.selectionStart = ioSpecEditor.selectionEnd = start + 2
        }
        ioSpecEditor.dispatchEvent(new Event('input'))
    } else if (e.key == '{' || e.key == '[') {
        e.preventDefault()
        const before = value.slice(0, start)
        const lineStart = before.lastIndexOf('\n') + 1
        const currentLine = before.slice(lineStart)
        const indentMatch = currentLine.match(/^\s*/)
        const currentIndent = indentMatch ? indentMatch[0] : ''
        const pair = e.key === '{' ? '{}' : '[]'
        const insert = pair[0] + '\n' + currentIndent + '  \n' + currentIndent + pair[1]
        ioSpecEditor.value = value.slice(0, start) + insert + value.slice(start)
        ioSpecEditor.selectionStart = ioSpecEditor.selectionEnd = start + currentIndent.length + 4
        ioSpecEditor.dispatchEvent(new Event('input'))
    }
})

resultsEditor.addEventListener('input', () => {
    syncJSONEditor(resultsEditor, resultsHighlighted, resultsLineNumbers)
})

resultsEditor.addEventListener('scroll', () => {
    const pre = resultsHighlighted.parentElement!
    pre.scrollTop = resultsEditor.scrollTop
    pre.scrollLeft = resultsEditor.scrollLeft
    resultsLineNumbers.scrollTop = resultsEditor.scrollTop
})
