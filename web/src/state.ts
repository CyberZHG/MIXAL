import 'cross-fetch/polyfill'

const editor = document.querySelector<HTMLTextAreaElement>("#mixal-editor")!
const ioSpecEditor = document.querySelector<HTMLTextAreaElement>("#io-spec-editor")!

export async function loadState() {
    const queryString: string = window.location.search
    const urlParams = new URLSearchParams(queryString)
    if (urlParams.has("example")) {
        const example = urlParams.get("example")!
        const codeResponse = await fetch(`/MIXAL/examples/${example}.mix`)
        if (codeResponse.ok) {
            editor.value = await codeResponse.text()
            editor.dispatchEvent(new Event("input"))
        }
        const ioSpecResponse = await fetch(`/MIXAL/examples/${example}.json`)
        if (ioSpecResponse.ok) {
            ioSpecEditor.value = await ioSpecResponse.text()
            ioSpecEditor.dispatchEvent(new Event("input"))
        }
        if (codeResponse.ok && ioSpecResponse.ok) {
            return;
        }
    }

    const locationHash = window.location.hash.replace(/^#/, "")
    if (locationHash.length != 0) {
        const state = JSON.parse(decodeURIComponent(
            Array.from(atob(locationHash))
                .map(c => `%${c.charCodeAt(0).toString(16).padStart(2, "0")}`)
                .join("")))
        editor.value = state["code"]
        editor.dispatchEvent(new Event("input"))
        ioSpecEditor.value = state["io"]
        ioSpecEditor.dispatchEvent(new Event("input"))
    }
}

function removeQueryString(url: string): string {
    const urlObject = new URL(url)
    urlObject.search = ""
    return urlObject.toString()
}

export function saveState() {
    const state = {
        "code": editor.value,
        "io": ioSpecEditor.value,
    }
    const encoded = btoa(
        encodeURIComponent(JSON.stringify(state)).replace(
            /%([0-9A-F]{2})/g,
            (_, p1) => String.fromCharCode(parseInt(p1, 16))
        ))
    window.history.replaceState(null, '', removeQueryString(window.location.href))
    window.location.hash = `#${encoded}`
}
