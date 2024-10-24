cmake_minimum_required(VERSION 3.5.0)
project(calyko VERSION 0.1.0 LANGUAGES C)

add_executable(${PROJECT_NAME}
    src/lexer.h
    src/lexer.c
    src/main.c
    src/token_type.h
    src/token_type.c
    src/utils.h
    src/opcode.h
    src/opcode.c
    src/value.h
)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 99)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -std=c99 -pedantic -Wall -Wextra -Werror)
endif()