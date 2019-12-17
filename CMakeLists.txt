project("Fish in the Sea" CXX)
cmake_minimum_required(VERSION 3.10)

macro(copy_shader_files)
  message(STATUS "Copying shader files")
  file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/shaders")
  file(GLOB_RECURSE SHADER_FILES "${PROJECT_SOURCE_DIR}/shaders/*.glsl")
  file(COPY ${SHADER_FILES} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/shaders")
endmacro(copy_shader_files)

set(OpenGL_GL_PREFERENCE LEGACY)
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)

copy_shader_files()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
		    
file(GLOB_RECURSE SRC "${PROJECT_SOURCE_DIR}/src/*.cc")

set(IMGUI_PATH "${PROJECT_SOURCE_DIR}/Externals/imgui")
file(GLOB_RECURSE IMGUI_SRC "${IMGUI_PATH}/*.cpp")

include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/Externals)

add_executable(fish_in_the_sea ${SRC} ${IMGUI_SRC})
target_compile_features(fish_in_the_sea PUBLIC cxx_std_17)
target_link_libraries(fish_in_the_sea OpenGL::GL SDL2 SDL2main GLEW)
