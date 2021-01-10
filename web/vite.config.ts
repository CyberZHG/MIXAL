import { defineConfig } from 'vite'
import { resolve } from 'path'
import tailwindcss from '@tailwindcss/vite'

export default defineConfig({
    base: "/MIXAL",
    build: {
        rollupOptions: {
            input: {
                main: resolve(__dirname, 'index.html'),
                examples: resolve(__dirname, 'examples.html'),
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
    esbuild: {
        supported: {
            'top-level-await': true
        },
    },
    optimizeDeps: {
        esbuildOptions: {
            supported: {
                "top-level-await": true
            },
        },
    },
})
