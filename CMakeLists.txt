cmake_minimum_required(VERSION 3.25)
project(FluxEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
file(GLOB_RECURSE ENGINE_SOURCES "engine/src/*.cpp")

# Wszystkie binarki i biblioteki w tym samym folderze build/windows
set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin/windows")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})

add_library(FluxEngine SHARED ${ENGINE_SOURCES})

find_package(Vulkan REQUIRED)
target_include_directories(FluxEngine PUBLIC engine/src)
target_include_directories(FluxEngine PUBLIC ${Vulkan_INCLUDE_DIRS})
target_compile_definitions(FluxEngine PRIVATE FLUX_EXPORT)
target_link_libraries(FluxEngine PUBLIC ${Vulkan_LIBRARIES})

if(WIN32)
    set_target_properties(FluxEngine PROPERTIES
        WINDOWS_EXPORT_ALL_SYMBOLS ON
    )
endif()

# Sandbox
add_executable(Sandbox sandbox/src/main.cpp)
target_link_libraries(Sandbox PRIVATE FluxEngine)
target_link_libraries(Sandbox PRIVATE FluxEngine)

# Kopiowanie DLL obok exe
if(WIN32)
    add_custom_command(TARGET Sandbox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:FluxEngine>
        $<TARGET_FILE_DIR:Sandbox>
    )
endif()

# Studio
add_executable(Studio studio/src/main.cpp)
target_link_libraries(Studio PRIVATE FluxEngine)
target_link_libraries(Studio PRIVATE FluxEngine)

if(WIN32)
    add_custom_command(TARGET Studio POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:FluxEngine>
        $<TARGET_FILE_DIR:Studio>
    )
endif()

# testGame
add_executable(testGame games/testGame/src/main.cpp)
target_link_libraries(testGame PRIVATE FluxEngine)
target_link_libraries(testGame PRIVATE FluxEngine)

if(WIN32)
    add_custom_command(TARGET testGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:FluxEngine>
        $<TARGET_FILE_DIR:testGame>
    )
endif()

# Add Catch2
add_subdirectory(extern/Catch2)

# Test executable
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
add_executable(FluxEngineTests ${TEST_SOURCES})
target_link_libraries(FluxEngineTests PRIVATE FluxEngine Catch2::Catch2WithMain)

# Enable CTest
enable_testing()
add_test(NAME FluxEngineTests COMMAND FluxEngineTests)