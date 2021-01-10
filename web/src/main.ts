import { loadState, saveState } from "./state.ts"
// @ts-ignore
import { executeWithSpec } from "../../wasm/index.js"
import json5 from "json5"

const editor = document.querySelector<HTMLTextAreaElement>("#mixal-editor")!
const ioSpecEditor = document.querySelector<HTMLTextAreaElement>("#io-spec-editor")!
const resultsEditor = document.querySelector<HTMLTextAreaElement>("#results-editor")!
const buttonExecute = document.querySelector<HTMLButtonElement>("#button-execute")!

loadState()

buttonExecute.addEventListener("click", () => {
    saveState()
    try {
        const ioSpec = json5.parse(ioSpecEditor.value)
        let results = executeWithSpec(editor.value, ioSpec)
        resultsEditor.value = JSON.stringify(results, null, 2)
    } catch (error) {
        if (error instanceof Error) {
            resultsEditor.value = error.message
        } else {
            resultsEditor.value = "" + error
        }
    }
    resultsEditor.dispatchEvent(new Event('input', { bubbles: true }))
})
