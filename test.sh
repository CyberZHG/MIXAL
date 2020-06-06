#!/usr/bin/env bash
pycodestyle --max-line-length=120 mixal tests && \
    cpplint --linelength=120 --filter=-build/include_subdir include/*.h src/*.cpp tests/*.cpp && \
    (cd tests/cpp && \
        rm -r coverage && \
        cmake . && \
        make all && \
        ./test && \
        mkdir -p coverage && \
        lcov --directory . --capture --output-file ./coverage/coverage.info && \
        lcov --remove ./coverage/coverage.info "/usr/*" "/Applications/*" "*v1*" "*/deps/*" "tests" -o ./coverage/filtered.info && \
        genhtml ./coverage/filtered.info --branch-coverage --output-directory ./coverage/report) && \
    nosetests --nocapture --with-coverage --cover-erase --cover-html --cover-html-dir=htmlcov --with-doctest --cover-package=mixal
