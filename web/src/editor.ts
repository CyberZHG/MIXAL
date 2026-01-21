// @ts-ignore
import { Parser, ParsedType } from "../../wasm/index.js"

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

const PSEUDO_OPS = new Set(["EQU", "ORIG", "CON", "ALF", "END"])

function escapeHtml(text: string): string {
    return text
        .replace(/&/g, '&amp;')
        .replace(/</g, '&lt;')
        .replace(/>/g, '&gt;')
        .replace(/"/g, '&quot;')
        .replace(/'/g, '&#39;')
}

function highlightMIXALLine(line: string): string {
    try {
        const result = Parser.parseLine(line, "", true)
        if (result.parsedType.value === ParsedType.EMPTY.value && result.commentSpan.start >= 0) {
            return `<span class="text-gray-500 dark:text-gray-400 italic">${escapeHtml(line)}</span>`
        }
        if (result.parsedType.value === ParsedType.EMPTY.value) {
            return escapeHtml(line)
        }
        const spans: { start: number; end: number; cls: string }[] = []
        if (result.locationSpan.start >= 0) {
            spans.push({
                start: result.locationSpan.start,
                end: result.locationSpan.end,
                cls: "text-purple-700 dark:text-purple-400"
            })
        }
        if (result.operationSpan.start >= 0) {
            const isPseudo = PSEUDO_OPS.has(result.operation)
            spans.push({
                start: result.operationSpan.start,
                end: result.operationSpan.end,
                cls: isPseudo
                    ? "text-blue-600 dark:text-blue-400 font-bold"
                    : "text-blue-700 dark:text-blue-500 font-bold"
            })
        }
        if (result.addressSpan.start >= 0) {
            spans.push({
                start: result.addressSpan.start,
                end: result.addressSpan.end,
                cls: "text-green-700 dark:text-green-400"
            })
        }
        if (result.indexSpan.start >= 0) {
            spans.push({
                start: result.indexSpan.start,
                end: result.indexSpan.end,
                cls: "text-yellow-700 dark:text-yellow-400"
            })
        }
        if (result.fieldSpan.start >= 0) {
            spans.push({
                start: result.fieldSpan.start,
                end: result.fieldSpan.end,
                cls: "text-orange-600 dark:text-orange-400"
            })
        }
        if (result.commentSpan.start >= 0) {
            spans.push({
                start: result.commentSpan.start,
                end: result.commentSpan.end,
                cls: "text-gray-500 dark:text-gray-400 italic"
            })
        }
        spans.sort((a, b) => a.start - b.start)
        let output = ""
        let pos = 0
        for (const span of spans) {
            if (pos < span.start) {
                output += escapeHtml(line.substring(pos, span.start))
            }
            const text = escapeHtml(line.substring(span.start, span.end))
            output += `<span class="${span.cls}">${text}</span>`
            pos = span.end
        }
        if (pos < line.length) {
            output += escapeHtml(line.substring(pos))
        }
        return output
    } catch {
        return escapeHtml(line)
    }
}

function highlightMIXAL(code: string): string {
    return code.split('\n').map(highlightMIXALLine).join('\n')
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
                cls += /:$/.test(match) ? 'text-blue-800 dark:text-blue-400' : 'text-green-700 dark:text-green-400'
            } else if (/true|false/.test(match)) {
                cls += 'text-purple-800 dark:text-purple-400'
            } else if (/null/.test(match)) {
                cls += 'text-gray-500 dark:text-gray-400'
            } else {
                cls += 'text-yellow-600 dark:text-yellow-500'
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

function insertText(textarea: HTMLTextAreaElement, text: string) {
    textarea.focus()
    document.execCommand('insertText', false, text)
}

function setTextareaValue(textarea: HTMLTextAreaElement, newValue: string, selStart: number, selEnd: number) {
    textarea.focus()
    textarea.select()
    document.execCommand('insertText', false, newValue)
    textarea.selectionStart = selStart
    textarea.selectionEnd = selEnd
}

ioSpecEditor.addEventListener('keydown', (e: KeyboardEvent) => {
    const start = ioSpecEditor.selectionStart
    const end = ioSpecEditor.selectionEnd
    const value = ioSpecEditor.value
    if (e.key == "Enter") {
        e.preventDefault()
        const before = value.slice(0, start)
        const lineStart = before.lastIndexOf('\n') + 1
        const currentLine = before.slice(lineStart)
        const indentMatch = currentLine.match(/^\s*/)
        const currentIndent = indentMatch ? indentMatch[0] : ''
        const shouldIndent = currentLine.trim().endsWith('{') || currentLine.trim().endsWith('[')
        const newIndent = shouldIndent ? currentIndent + "  " : currentIndent
        const insertTextStr = '\n' + newIndent
        insertText(ioSpecEditor, insertTextStr)
        ioSpecEditor.dispatchEvent(new Event('input'))
    } else if (e.key == "Tab") {
        e.preventDefault()
        const before = value.slice(0, start)
        const selected = value.slice(start, end)
        const after = value.slice(end)

        // Check if selection spans multiple lines
        if (selected.includes('\n')) {
            // Multi-line indentation
            const lineStart = before.lastIndexOf('\n') + 1
            const lineEnd = end + (after.indexOf('\n') === -1 ? after.length : after.indexOf('\n'))
            const selectedLines = value.slice(lineStart, lineEnd)

            let newLines: string
            let newSelStart: number
            let newSelEnd: number

            if (e.shiftKey) {
                // Dedent: remove up to 2 spaces from each line start
                newLines = selectedLines.replace(/^( {1,2})/gm, '')
                const firstLineReduction = selectedLines.match(/^( {1,2})/) ? selectedLines.match(/^( {1,2})/)![1].length : 0
                newSelStart = Math.max(lineStart, start - firstLineReduction)
                newSelEnd = lineStart + newLines.length - (after.indexOf('\n') === -1 ? after.length : after.indexOf('\n'))
            } else {
                // Indent: add 2 spaces to each line start
                newLines = selectedLines.replace(/^/gm, '  ')
                newSelStart = start + 2
                newSelEnd = lineStart + newLines.length - (after.indexOf('\n') === -1 ? after.length : after.indexOf('\n'))
            }

            const newValue = value.slice(0, lineStart) + newLines + value.slice(lineEnd)
            setTextareaValue(ioSpecEditor, newValue, newSelStart, newSelEnd)
        } else {
            // Single line or no selection
            if (e.shiftKey) {
                if (before.endsWith("  ")) {
                    const newValue = before.slice(0, -2) + selected + after
                    setTextareaValue(ioSpecEditor, newValue, start - 2, end - 2)
                } else if (before.endsWith(" ")) {
                    const newValue = before.slice(0, -1) + selected + after
                    setTextareaValue(ioSpecEditor, newValue, start - 1, end - 1)
                }
            } else {
                insertText(ioSpecEditor, "  ")
            }
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
        insertText(ioSpecEditor, insert)
        // Position cursor on the middle line
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
