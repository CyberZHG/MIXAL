const editor = document.querySelector<HTMLTextAreaElement>("#mixal-editor")!
const ioSpecEditor = document.querySelector<HTMLTextAreaElement>("#io-spec-editor")!

export function loadState() {
    const locationHash = window.location.hash.replace(/^#/, "")
    if (locationHash.length != 0) {
        const state = JSON.parse(decodeURIComponent(
            Array.from(atob(locationHash))
                .map(c => `%${c.charCodeAt(0).toString(16).padStart(2, "0")}`)
                .join("")))
        editor.value = state["code"]
        editor.dispatchEvent(new Event('input', { bubbles: true }))
        ioSpecEditor.value = state["io"]
        ioSpecEditor.dispatchEvent(new Event('input', { bubbles: true }))
    }
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
    window.location.hash = `#${encoded}`
}
