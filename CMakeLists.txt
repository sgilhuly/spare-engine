cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 11)

project(spare-engine)

# include our module finders
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Temporary files (like object files) created while compiling projects.
set(tmp_dir ${CMAKE_BINARY_DIR}/obj)

set(dependencies_root "${CMAKE_CURRENT_SOURCE_DIR}/dependencies")

# Include assimp
# set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "")
# add_subdirectory("${dependencies_flatbuffers_dir}" ${tmp_dir}/flatbuffers)

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(assimp REQUIRED)
include_directories(${assimp_INCLUDE_DIRS})

# Source files for project
set(SOURCE_FILES
    src/camera.cpp
    src/camera.h
    src/engine.cpp
    src/engine.h
    src/game_object.cpp
    src/game_object.h
    src/main.cpp
    src/material.cpp
    src/material.h
    src/mesh.cpp
    src/mesh.h
    src/resource_loader.cpp
    src/resource_loader.h
    src/shader.cpp
    src/shader.h
    src/shader_program.cpp
    src/shader_program.h
    src/texture.cpp
    src/texture.h)

# Includes for project
# include_directories(src)

# Add other dependencies
# add_subdirectory("${dependencies_breadboard_dir}" ${tmp_dir}/breadboard)

# add_subdirectory("${dependencies_fplbase_dir}" ${tmp_dir}/fplbase)

# set_compiler_flags_for_external_libraries()
# set(BUILD_CPU_DEMOS OFF CACHE BOOL "")
# set(BUILD_BULLET2_DEMOS OFF CACHE BOOL "")
# set(BUILD_BULLET3 OFF CACHE BOOL "")
# set(BUILD_EXTRAS OFF CACHE BOOL "")
# set(BUILD_UNIT_TESTS OFF CACHE BOOL "")
# set(USE_MSVC_RUNTIME_LIBRARY_DLL ON CACHE BOOL "")
# add_subdirectory("${dependencies_bulletphysics_distr_dir}"
#                  ${tmp_dir}/bulletphysics)
# restore_compiler_flags()

# include_directories(${dependencies_bulletphysics_distr_dir}/src)
# include_directories(${dependencies_flatbuffers_dir}/include)
# include_directories(${dependencies_fplbase_dir}/include)
# include_directories(${dependencies_mathfu_dir}/include)
# include_directories(${dependencies_vectorial_dir}/include)

# include_directories(${PROJECT_SOURCE_DIR}/dependencies/assimp/include)
include_directories(${PROJECT_SOURCE_DIR}/dependencies/glm)

add_executable(spare-engine ${SOURCE_FILES})
target_link_libraries(spare-engine
    ${GLEW_LIBRARY}
    ${SDL2_LIBRARY}
    ${assimp_LIBRARIES})