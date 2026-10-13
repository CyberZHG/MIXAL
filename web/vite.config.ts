import { defineConfig } from 'vite'
import { resolve } from 'path'
import tailwindcss from '@tailwindcss/vite'

export default defineConfig({
    base: "/MIXAL",
    build: {
        rolldownOptions: {
            input: {
                main: resolve(import.meta.dirname, 'index.html'),
                examples: resolve(import.meta.dirname, 'examples.html'),
            }
        }
    },
    plugins: [
        tailwindcss(),
    ],
    server: {
        fs: {
            allow: ['..']
        }
    },
})
