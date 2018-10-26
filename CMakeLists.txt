cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(spare-engine)

message(INFO "${CMAKE_CXX_COMPILER_VERSION}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Temporary files (like object files) created while compiling projects.
set(tmp_dir ${CMAKE_BINARY_DIR}/obj)

find_package(assimp REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${ASSIMP_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/dependencies/entt/src)
include_directories(${PROJECT_SOURCE_DIR}/dependencies/glm)

# Remove a trailing space that causes linking errors.
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)

# Source files for the project.
set(SOURCE_FILES
    src/spare/camera.cc
    src/spare/camera.h
    src/spare/engine.cc
    src/spare/engine.h
    src/spare/main.cc
    src/spare/material.cc
    src/spare/material.h
    src/spare/mesh.cc
    src/spare/mesh.h
    src/spare/resource_loader.cc
    src/spare/resource_loader.h
    src/spare/shader.cc
    src/spare/shader.h
    src/spare/shader_program.cc
    src/spare/shader_program.h
    src/spare/spatial.cc
    src/spare/spatial.h
    src/spare/texture.cc
    src/spare/texture.h)

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

add_executable(spare-engine ${SOURCE_FILES})
target_link_libraries(spare-engine
    ${ASSIMP_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${OPENGL_LIBRARY}
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES})