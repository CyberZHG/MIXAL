import * as fs from 'fs'
// @ts-ignore
import { executeWithSpec } from "../../wasm/index.js"

const EXAMPLES_FOLDER = "public/examples/"

export function runExample(exampleName: string) {
    const code: string = fs.readFileSync(EXAMPLES_FOLDER + exampleName + ".mix", "utf-8")
    const ioSpecString: string = fs.readFileSync(EXAMPLES_FOLDER + exampleName + ".json", "utf-8")
    const ioSpec = JSON.parse(ioSpecString)
    return executeWithSpec(code, ioSpec)
}