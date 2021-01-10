cmake_minimum_required(VERSION 4.0)
project(MIXAL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(MIXAL_ENABLE_TESTS "Build tests" OFF)
option(MIXAL_ENABLE_STRICT "Use strict compile options" OFF)
option(MIXAL_ENABLE_COVERAGE "Enable coverage reporting" OFF)
option(MIXAL_BIND_PYTHON "Enable PYTHON binding" OFF)
option(MIXAL_BIND_ES "Enable ECMAScript binding" OFF)

if(APPLE)
    set(ENV{PKG_CONFIG_PATH} "/opt/homebrew/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}")
endif()

include(FetchContent)

FetchContent_Declare(
        UChar
        GIT_REPOSITORY https://github.com/CyberZHG/UChar.git
        GIT_TAG v1.1.0
)

FetchContent_MakeAvailable(UChar)

if(MIXAL_ENABLE_STRICT)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        add_compile_options(
                -Wall
                -Wextra
                -Werror
                -Wpedantic
                -Wmissing-include-dirs
                -Wundef
                -Wredundant-decls
        )
    endif()
endif()

if(MIXAL_ENABLE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        add_compile_options(--coverage -O0 -g -fno-elide-constructors -fno-default-inline)
        add_link_options(--coverage)
    endif()
endif()

add_library(MIXAL STATIC
        include/errors.h
        include/expression.h
        src/expression.cpp
        src/atomic.cpp
        include/flags.h
        src/flags.cpp
        include/instructions.h
        src/instructions.cpp
        include/io.h
        src/io.cpp
        include/machine.h
        src/machine.cpp
        src/machine_address_transfer.cpp
        src/machine_arithmetic.cpp
        src/machine_comparison.cpp
        src/machine_conversion.cpp
        src/machine_io.cpp
        src/machine_jump.cpp
        src/machine_load.cpp
        src/machine_misc.cpp
        src/machine_pseudo.cpp
        src/machine_store.cpp
        include/memory.h
        src/memory.cpp
        include/parser.h
        src/parser.cpp
        include/registers.h
        src/registers.cpp
)

target_include_directories(MIXAL
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(MIXAL
        PRIVATE UChar
)

if(MIXAL_ENABLE_TESTS)
    enable_testing()

    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG v1.17.0
    )

    FetchContent_MakeAvailable(googletest)

    add_executable(runTests
            tests/main.cpp
            tests/test_atomic.cpp
            tests/test_expression.cpp
            tests/test_instructions.cpp
            tests/test_machine.cpp
            tests/test_machine_address_transfer.cpp
            tests/test_machine_arithmetic.cpp
            tests/test_machine_comparison.cpp
            tests/test_machine_conversion.cpp
            tests/test_machine_evaluate.cpp
            tests/test_machine_io.cpp
            tests/test_machine_jump.cpp
            tests/test_machine_load.cpp
            tests/test_machine_load_codes.cpp
            tests/test_machine_misc.cpp
            tests/test_machine_pseudo.cpp
            tests/test_machine_store.cpp
            tests/test_memory.cpp
            tests/test_parse.cpp
            tests/test_registers.cpp
    )

    target_link_libraries(runTests
            PRIVATE MIXAL
            PRIVATE gtest gtest_main
    )

    add_test(NAME MixalTests COMMAND runTests)
endif ()

if(MIXAL_BIND_PYTHON)
    include(FetchContent)
    FetchContent_Declare(
            pybind11
            GIT_REPOSITORY https://github.com/pybind/pybind11.git
            GIT_TAG v3.0
    )
    FetchContent_MakeAvailable(pybind11)

    pybind11_add_module(_core
            python/binding.cpp
    )
    target_link_libraries(_core
            PRIVATE MIXAL
    )
    install(TARGETS _core
            LIBRARY DESTINATION mixal)
    install(FILES python/wrapper/__init__.py DESTINATION mixal)
endif()

if (MIXAL_BIND_ES)

    add_executable(MixalWASM
            wasm/binding.cpp)

    target_link_libraries(MixalWASM
            PRIVATE MIXAL
    )

    target_compile_options(MixalWASM PRIVATE "-O3")

    set_target_properties(MixalWASM PROPERTIES SUFFIX ".js")

    target_link_options(MixalWASM PRIVATE
            "--bind"
            "-sMODULARIZE=1"
            "-sEXPORT_ES6=1"
            "-sEXPORT_NAME=MIXALWASMModule"
            "-sNO_DISABLE_EXCEPTION_CATCHING"
    )
endif ()