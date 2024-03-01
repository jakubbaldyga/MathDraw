cmake_minimum_required(VERSION 3.8.0)
project(MathDraw)

set(BUILD_SHARED_LIBS ON)

include(FetchContent)
message(STATUS, ${cmake_runtime_output_directory})
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

FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
)
FetchContent_MakeAvailable(sfml)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(SFML_LIBRARIES sfml-graphics sfml-window sfml-system)
else()
	set(SFML_LIBRARIES sfml-graphics-d sfml-window-d sfml-system-d)
endif()
    
FetchContent_Declare(
    libtorch
    URL https://download.pytorch.org/libtorch/cpu/libtorch-win-shared-with-deps-2.0.1%2Bcpu.zip
)
FetchContent_MakeAvailable(libtorch)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${libtorch_SOURCE_DIR})
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS})
find_package(Torch REQUIRED)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)

include_directories(src/Utilities)
include_directories(src/AI)
include_directories(res/)

set(BACKEND_SOURCES
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

    src/Utilities/Utilties.hpp
    src/Utilities/Strings.hpp
    src/Utilities/Strings.cpp
)

set(CLI_SOURCES
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
)

set(APP_SOURCES
    src/GUI/WindowManager.hpp
    src/GUI/WindowManager.cpp

    src/GUI/AIOutput/AIOutput.hpp
    src/GUI/AIOutput/AIOutput.cpp

    src/GUI/ContentImage/ContentImage.hpp
    src/GUI/ContentImage/ContentImage.cpp
   
    src/GUI/Tools/Tool/Tool.hpp

    src/GUI/Tools/DrawTool/DrawTool.cpp
    src/GUI/Tools/DrawTool/DrawTool.hpp
    
    src/GUI/Tools/BucketTool/BucketTool.cpp
    src/GUI/Tools/BucketTool/BucketTool.hpp
)

#copy dlls and required resources#########
file(GLOB TORCH_DLLS "${libtorch_SOURCE_DIR}/lib/*.dll")
file(GLOB SFML_DLLS "${sfml_BINARY_DIR}/bin/*.dll" "${sfml_BINARY_DIR}/bin/Release/*.dll")

file(GLOB CATCH2_DLLS "${Catch2_BINARY_DIR}/src/*.dll" "${Catch2_BINARY_DIR}/src/Release/*.dll")

foreach(DLL ${TORCH_DLLS} ${SFML_DLLS} ${CATCH2_DLLS})
	message(STATUS, ${DLL})
    file(COPY ${DLL} DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})
endforeach()

set(RES "${CMAKE_SOURCE_DIR}/res/model.pt"
        "${CMAKE_SOURCE_DIR}/res/font.ttf"
)
message(STATUS, ${CMAKE_SOURCE_DIR})
foreach(RESOURCE ${RES})
    file(COPY ${RESOURCE} DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})
endforeach()
############################################

add_executable(MathDrawCLI ${BACKEND_SOURCES} ${CLI_SOURCES} "src/CLIMain.cpp")
target_link_libraries(MathDrawCLI ${TORCH_LIBRARIES} ${SFML_LIBRARIES} argparse)
set_property(TARGET MathDrawCLI PROPERTY CXX_STANDARD 20)

add_executable(MathDrawApp ${BACKEND_SOURCES} ${APP_SOURCES} "src/AppMain.cpp")
target_link_libraries(MathDrawApp ${TORCH_LIBRARIES} ${SFML_LIBRARIES} argparse)
set_property(TARGET MathDrawApp PROPERTY CXX_STANDARD 20)

## testing ##
enable_testing()

# Set up tests
add_executable(MathDrawTest ${BACKEND_SOURCES} "tests/Tests.cpp")
target_link_libraries(MathDrawTest ${TORCH_LIBRARIES} ${SFML_LIBRARIES} argparse Catch2::Catch2WithMain)
set_property(TARGET MathDrawTest PROPERTY CXX_STANDARD 20)

add_executable(MathDrawFunctionalityTest ${BACKEND_SOURCES} "tests/FunctionalityTest.cpp")
target_link_libraries(MathDrawFunctionalityTest ${TORCH_LIBRARIES} ${SFML_LIBRARIES} argparse Catch2::Catch2WithMain)
set_property(TARGET MathDrawFunctionalityTest PROPERTY CXX_STANDARD 20)

# Set up tests
add_test(
    NAME MathDrawTest
    COMMAND $<TARGET_FILE:MathDrawTest>
)

add_test(
    NAME MathDrawFunctionalityTest
    COMMAND $<TARGET_FILE:MathDrawFunctionalityTest>
)

set(RES 
	"${CMAKE_SOURCE_DIR}/res/")
message(STATUS, ${CMAKE_SOURCE_DIR})
foreach(RESOURCE ${RES})
    file(COPY ${RESOURCE} DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/res)
    file(COPY ${RESOURCE} DESTINATION ${CMAKE_BINARY_DIR}/res)
endforeach()
############################################