#!/usr/bin/env bash
swig -Iinclude -python -c++ -outdir src -o src/mixal_wrap.cxx include/mixal.i && mv src/mixal.py ./
