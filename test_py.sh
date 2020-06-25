#!/usr/bin/env bash
python setup.py install &&
    pycodestyle --max-line-length=120 tests &&
    nosetests --nocapture --cover-package=mixal
