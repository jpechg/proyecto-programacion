cmake_minimum_required(VERSION 3.10)
project(programacion1 C)

set(CMAKE_C_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

find_package(SDL2 REQUIRED)

include_directories(include ${SDL2_INCLUDE_DIRS})

set(SOURCES
    main.c
    gui.c
    src/glad.c
    utilidades.c
    reader.c
)

add_executable(programacion1 ${SOURCES})

if(UNIX)
    set(MATH_LIB m)
endif()

# ${CMAKE_DL_LIBS} handles '-ldl' portably
target_link_libraries(programacion1 ${SDL2_LIBRARIES} ${CMAKE_DL_LIBS} m)

if(WIN32)
    # This command copies all necessary DLLs to your build folder after every build
    add_custom_command(TARGET programacion1 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy -t 
        "$<TARGET_FILE_DIR:programacion1>" 
        "$<TARGET_RUNTIME_DLLS:programacion1>"
        COMMAND_EXPAND_LISTS
    )
endif()

