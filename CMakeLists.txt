cmake_minimum_required(VERSION 3.8.0)
project(MathDraw)

# Fetch argparse library
include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)

# Fetch sfml library
FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
)
FetchContent_MakeAvailable(sfml)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    FetchContent_Declare(
        libtorch
        URL https://download.pytorch.org/libtorch/cpu/libtorch-win-shared-with-deps-2.0.1%2Bcpu.zip
    )
    FetchContent_MakeAvailable(libtorch)
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${libtorch_SOURCE_DIR})
else()
    FetchContent_Declare(
        libtorch
        URL https://download.pytorch.org/libtorch/cpu/libtorch-win-shared-with-deps-debug-2.1.2%2Bcpu.zip
    )
    FetchContent_MakeAvailable(libtorch)
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${libtorch_SOURCE_DIR})
endif()

find_package(Torch REQUIRED)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)

set(SOURCES
    src/main.cpp
    src/AI/AI.hpp
    src/AI/AI.cpp
    src/AI/Net/Net.hpp
    src/AI/Net/Net.cpp
    src/AI/PixelTraversal/PixelTraversal.hpp
    src/AI/PixelTraversal/PixelTraversal.cpp
    src/AI/ResizeImage/ResizeImage.hpp
    src/AI/ResizeImage/ResizeImage.cpp
    src/AI/ScaleImage/ScaleImage.hpp
    src/AI/ScaleImage/ScaleImage.cpp
    src/Parser/Parser.hpp
    src/Parser/Parser.cpp
    src/Parser/SubCommand/SubCommand.hpp
    src/Parser/SubCommand/SubCommand.cpp
    src/Parser/RecogniseSubCommand/RecogniseSubCommand.hpp
    src/Parser/RecogniseSubCommand/RecogniseSubCommand.cpp
    src/Parser/HiddenSubCommands/HiddenSubCommand.hpp
    src/Parser/HiddenSubCommands/HiddenSubCommand.cpp
    src/Parser/HiddenSubCommands/ResizeSubCommand/ResizeSubCommand.hpp
    src/Parser/HiddenSubCommands/ResizeSubCommand/ResizeSubCommand.cpp
    src/Parser/HiddenSubCommands/ScaleSubCommand/ScaleSubCommand.hpp
    src/Parser/HiddenSubCommands/ScaleSubCommand/ScaleSubCommand.cpp
    src/Parser/HiddenSubCommands/TraverseSubCommand/TraverseSubCommand.hpp
    src/Parser/HiddenSubCommands/TraverseSubCommand/TraverseSubCommand.cpp
    src/Utilities/Utilties.hpp
    src/Utilities/Strings.hpp
    src/Utilities/Strings.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

# Add executable
add_executable(MathDraw ${SOURCES})

target_link_libraries(MathDraw "${TORCH_LIBRARIES}" sfml-graphics sfml-window sfml-system argparse)
set_property(TARGET MathDraw PROPERTY CXX_STANDARD 20)