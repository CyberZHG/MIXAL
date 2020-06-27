#!/usr/bin/env bash
python -m cpplint --linelength=120 --filter=-build/include_subdir,-legal/copyright,-readability/fn_size,-runtime/threadsafe_fn include/*.h src/*.cpp tests/cpp/*.cpp && \
    (cd tests/cpp && \
        find . -name "*.gcda" -delete && \
        cmake -DCMAKE_BUILD_TYPE=Debug . && \
        make all && \
        ./test && \
        mkdir -p coverage && \
        lcov --directory . --capture --output-file ./coverage/coverage.info && \
        lcov --remove ./coverage/coverage.info "/usr/*" "/Applications/*" "*v1*" "*/deps/*" "tests" -o ./coverage/filtered.info && \
        genhtml ./coverage/filtered.info --branch-coverage --output-directory ./coverage/report)
