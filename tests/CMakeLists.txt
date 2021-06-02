cmake_minimum_required(VERSION 3.12)

# List all files containing tests. (Change as needed)
# file(GLOB TEST_FILES ./*.cpp)       # All .cpp files in tests/


set(TEST_MAIN unit_tests)   # Default name for test executable (change if you wish).
set(TEST_RUNNER_PARAMS "")  # Any arguemnts to feed the test runner (change as needed).

# --------------------------------------------------------------------------------
#                         Make Tests (no change needed).
# --------------------------------------------------------------------------------
# add_library(LIB_TEST_FILES OBJECT ${TEST_FILES})
# target_include_directories(TEST_FILES PUBLIC ${PROJECT_SOURCE_DIR}/inc ${PROJECT_SOURCE_DIR}/prn)

add_executable(${TEST_MAIN} ./main.cpp ${TEST_FILES})


target_link_libraries(${TEST_MAIN} PUBLIC  SOURCES_LIB doctest)
target_include_directories(${TEST_MAIN} PUBLIC ../inc ../prn  ${PROJECT_SOURCE_DIR})

set_target_properties(${TEST_MAIN} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
target_set_warnings(${TEST_MAIN} ENABLE ALL AS_ERROR ALL DISABLE Annoying) # Set warnings (if needed).


set_target_properties(${TEST_MAIN} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    WORKING_DIRECTORY  "${PROJECT_SOURCE_DIR}"
)


# Adds a 'coverage' target.
include(CodeCoverage)

# verbose full described tests (make fulltest)
add_custom_target(fulltest
    ${TEST_MAIN} -s
    WORKING_DIRECTORY  ${PROJECT_SOURCE_DIR})

add_custom_target(fulltestDisplay
    ${TEST_MAIN} -x
    WORKING_DIRECTORY  ${PROJECT_SOURCE_DIR})