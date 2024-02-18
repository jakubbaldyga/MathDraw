cmake_minimum_required(VERSION 3.8.0)
project(MathDraw)
set(BUILD_SHARED_LIBS OFF)
# Fetch argparse library
include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 
)
FetchContent_MakeAvailable(Catch2)

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
        URL https://download.pytorch.org/libtorch/cpu/libtorch-win-shared-with-deps-debug-2.0.1%2Bcpu.zip
    )
    FetchContent_MakeAvailable(libtorch)
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${libtorch_SOURCE_DIR})
endif()

find_package(Torch REQUIRED)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)

set(SOURCES
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

    src/GUI/AIOutput.hpp
    src/GUI/ContentImage.hpp
    src/GUI/WindowManager.hpp
    
    src/GUI/Tools/Tool.hpp
    src/GUI/Tools/DrawTool.hpp
)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS})

# Add executable
add_executable(MathDraw ${SOURCES} "src/main.cpp")

target_link_libraries(MathDraw ${TORCH_LIBRARIES} sfml-graphics sfml-window sfml-system argparse)
set_property(TARGET MathDraw PROPERTY CXX_STANDARD 20)

install(TARGETS MathDraw)

# Add executable
add_executable(MathDrawApp ${SOURCES} "src/AppMain.cpp")

target_link_libraries(MathDrawApp ${TORCH_LIBRARIES} sfml-graphics sfml-window sfml-system argparse)
set_property(TARGET MathDrawApp PROPERTY CXX_STANDARD 20)

install(TARGETS MathDrawApp)

enable_testing()
add_executable(MathDrawTest ${SOURCES} "tests/Tests.cpp")

target_link_libraries(MathDrawTest ${TORCH_LIBRARIES} sfml-graphics sfml-window sfml-system argparse Catch2::Catch2WithMain)
set_property(TARGET MathDrawTest PROPERTY CXX_STANDARD 20)