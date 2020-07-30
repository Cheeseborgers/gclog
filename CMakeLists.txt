cmake_minimum_required(VERSION 3.16)
project(Gclog)

set(CMAKE_CXX_STANDARD 20)
include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# Enable cache system
include(cmake/Cache.cmake)

# Standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# Sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# Enable doxygen
include(cmake/Doxygen.cmake)
enable_doxygen()

# Allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)
option(ENABLE_TESTING "Enable Test Builds" ON)
option(ENABLE_FUZZING "Enable Fuzzing Builds" OFF)

# Set up some extra Conan dependencies based on our needs
# before loading Conan
set(CONAN_EXTRA_REQUIRES "")
set(CONAN_EXTRA_OPTIONS "")

include(cmake/Conan.cmake)
run_conan()

if (ENABLE_TESTING)
    enable_testing()
    message(
            "Building Tests. Be sure to check out test/constexpr_tests for constexpr testing"
    )
    add_subdirectory(test)
endif ()

if (ENABLE_FUZZING)
    message(
            "Building Fuzz Tests, using fuzzing sanitizer https://www.llvm.org/docs/LibFuzzer.html"
    )
    add_subdirectory(fuzz_test)
endif ()

add_executable(Gclog main.cpp Logger.hpp)

target_link_libraries(Gclog
        PRIVATE
        project_options
        project_warnings
        )
