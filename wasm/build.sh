#!/usr/bin/env bash

emcmake cmake .. -B wasm -DMIXAL_BIND_ES=ON
(cd wasm && emmake make MixalWASM)
