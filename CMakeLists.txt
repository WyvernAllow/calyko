﻿cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project(calyko VERSION 0.1.0)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

add_subdirectory(deps/glm)
add_subdirectory(deps/spdlog)
add_subdirectory(deps/stb_image_write)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glm
    spdlog
    stb_image_write
)