cmake_minimum_required(VERSION 3.12) # Increased for better Python/Target support
project(programacion1 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Default to Release if no build type is specified (Standard practice)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose build type" FORCE)
endif()

# Find SDL2
find_package(SDL2 REQUIRED)

# Define source files
set(SOURCES
    main.c
    gui.c
    src/glad.c
    busqueda.c
    utilidades.c
    reader.c
)

add_executable(programacion1 ${SOURCES})

# Modern approach: Include directories specific to the target
target_include_directories(programacion1 PRIVATE 
    include 
    ${SDL2_INCLUDE_DIRS}
)

# Link libraries
# SDL2::SDL2 is the modern imported target that handles headers/libs automatically
target_link_libraries(programacion1 PRIVATE SDL2::SDL2main SDL2::SDL2)

if(UNIX)
    target_link_libraries(programacion1 PRIVATE m)
endif()

if(WIN32)
    # This handles the DLL copying automatically for shared builds
    # Works with MSYS2, MinGW, and Visual Studio
    add_custom_command(TARGET programacion1 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:programacion1>
        $<TARGET_FILE_DIR:programacion1>
        COMMAND_EXPAND_LISTS
    )
    
    # Hide the console window on Windows for GUI apps (Optional)
    # set_target_properties(programacion1 PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

# Copy assets
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/dataset.csv" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
