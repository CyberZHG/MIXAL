#!/usr/bin/env bash
python setup.py install &&
    pycodestyle --max-line-length=120 tests &&
    nosetests --nocapture --with-coverage --cover-erase --cover-html --cover-html-dir=htmlcov --with-doctest --cover-package=mixal
