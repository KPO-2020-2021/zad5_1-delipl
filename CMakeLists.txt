# This file specifies how the project should be built, using CMake.
# If you are unfamiliar with CMake, don't worry about all the details.
# The sections you might want to edit are marked as such, and 
# the comments should hopefully make most of it clear.
#
# For many purposes, you may not need to change anything about this file.

cmake_minimum_required(VERSION 3.12)

# Set project name, version and laguages here. (change as needed)
# Version numbers are available by including "exampleConfig.h" in 
# the source. See exampleConfig.h.in for some more details.
project(Rotations VERSION 2.0.0.0 LANGUAGES CXX)


# Options: Things you can set via commandline options to cmake (e.g. -DENABLE_LTO=[ON|OFF])
option(ENABLE_WARNINGS_SETTINGS "Allow target_set_warnings to add flags and defines.
                                 Set this to OFF if you want to provide your own warning parameters." ON)
option(ENABLE_LTO "Enable link time optimization" ON)
option(ENABLE_DOCTESTS "Include tests in the library. Setting this to OFF will remove all doctest related code.
                        Tests in tests/*.cpp will still be enabled." ON)

# Include stuff. No change needed.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(ConfigSafeGuards)
include(Colors)
include(CTest)
include(Doctest)
include(Documentation)
include(LTO)
include(Misc)
include(Warnings)

# Check for LTO support.
find_lto(CXX)

# --------------------------------------------------------------------------------
#                         Locate files (change as needed).
# --------------------------------------------------------------------------------
# file(GLOB SOURCES ./src/*.cpp) # All .cpp files in src/
set(SOURCES ./src/Vectors.cpp 
            ./src/Matrixes.cpp
            ./src/Object.cpp
            ./src/SceneObject.cpp
            
            ./src/GnuPlotApi.cpp
            ./src/Scene.cpp

            ./src/Menu.cpp 

        
            
)

file(GLOB TEST_FILES ./tests/*.ut.cpp)       # All .cpp files in tests/

add_library(SOURCES_LIB ${SOURCES})
# --------------------------------------------------------------------------------
#                            Build! (Change as needed)
# --------------------------------------------------------------------------------


# Set the compile options you want (change as needed).
target_set_warnings(SOURCES_LIB ENABLE ALL AS_ERROR ALL DISABLE Annoying)
target_include_directories(SOURCES_LIB PRIVATE ./inc ./prn)


# Add an executable for the file app/main.cpp.
# If you add more executables, copy these lines accordingly.
add_executable(main app/main.cpp)   # Name of exec. and location of file.

target_include_directories(main PRIVATE ./inc ./prn)
target_include_directories (main PRIVATE ./)
target_link_libraries(main PUBLIC SOURCES_LIB)

target_set_warnings(main ENABLE ALL AS_ERROR ALL DISABLE Annoying) # Set warnings (if needed).
target_enable_lto(main optimized)  # enable link-time-optimization if available for non-debug configurations

# Set the properties you require, e.g. what C++ standard to use. Here applied to library and main (change as needed).
set_target_properties(
    ${SOURCES_LIB} main 
    PROPERTIES 
    CXX_STANDARD 17 
    CXX_STANDARD_REQUIRED YES 
    CXX_EXTENSIONS NO
    WORKING_DIRECTORY 	CMAKE_HOME_DIRECTORY
)

# Set up tests (see tests/CMakeLists.txt).
add_subdirectory(./tests)


#  -------------------------------------------------------------------------- #
#                                   Soft Body                                 #
#  -------------------------------------------------------------------------- #
# Add an executable for the file app/main.cpp.
# If you add more executables, copy these lines accordingly.
add_executable(softBody app/softBody.cpp)   # Name of exec. and location of file.

target_include_directories(softBody PRIVATE ./inc ./prn)
target_link_libraries(softBody PUBLIC SOURCES_LIB)

target_set_warnings(main ENABLE ALL AS_ERROR ALL DISABLE Annoying) # Set warnings (if needed).
target_enable_lto(main optimized)  # enable link-time-optimization if available for non-debug configurations

# Set the properties you require, e.g. what C++ standard to use. Here applied to library and main (change as needed).
set_target_properties(
    SOURCES_LIB softBody 
    PROPERTIES 
    CXX_STANDARD 17 
    CXX_STANDARD_REQUIRED YES 
    CXX_EXTENSIONS NO
    WORKING_DIRECTORY  ${PROJECT_SOURCE_DIR}
)

# verbose full described tests (make fulltest)
add_custom_target(app
   main
    WORKING_DIRECTORY  ${PROJECT_SOURCE_DIR})
