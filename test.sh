#!/usr/bin/env bash
pycodestyle --max-line-length=120 mixal tests && \
    nosetests --nocapture --with-coverage --cover-erase --cover-html --cover-html-dir=htmlcov --with-doctest --cover-package=mixal
