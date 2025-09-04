cmake_minimum_required(VERSION 3.10)

project(Square_Fight VERSION 1.0)

#Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Optional compile flags
add_compile_options(-Wall -Werror -g -pedantic)

# Gather all cpp files from src/
file(GLOB SOURCES "src/*.cpp")

# Add executable
add_executable(Square_Fight "${SOURCES}")

# Include directory for headers
target_include_directories(Square_Fight PUBLIC "${CMAKE_SOURCE_DIR}/include")

# Optional defines
<<<<<<< HEAD
#target_compile_definitions(Square_Fight PRIVATE MEMTRACE=1)
#target_compile_definitions(Square_Fight PRIVATE CPORTA=1)
=======
target_compile_definitions(Square_Fight PRIVATE MEMTRACE=1)
target_compile_definitions(Square_Fight PRIVATE CPORTA=1)
>>>>>>> a04c523 (Idk :3)

# Find SDL3
find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)

# Link SDL libraries
target_link_libraries(Square_Fight PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf)

# Rename output
set_target_properties(Square_Fight PROPERTIES OUTPUT_NAME "Square Fight")

# Copy maps folder content to executable dir
add_custom_command(TARGET Square_Fight POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets/maps $<TARGET_FILE_DIR:Square_Fight>
)

# Copy fonts folder content to executable dir
add_custom_command(TARGET Square_Fight POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets/fonts $<TARGET_FILE_DIR:Square_Fight>
)
