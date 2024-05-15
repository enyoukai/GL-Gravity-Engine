cmake_minimum_required( VERSION 3.28 )

project( GL_GRAVITATION )


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/glfw)

add_subdirectory(lib/spdlog)

add_subdirectory(lib/glm)

add_library(glad lib/glad/src/glad.c)
target_include_directories(glad PUBLIC lib/glad/include)

file(GLOB SOURCE_FILES src/*.cpp)

add_executable(GL_GRAVITATION ${SOURCE_FILES})

target_include_directories(GL_GRAVITATION PRIVATE include)

target_link_libraries(GL_GRAVITATION glad)
target_link_libraries(GL_GRAVITATION glfw)
target_link_libraries(GL_GRAVITATION spdlog)
target_link_libraries(GL_GRAVITATION glm)

find_package( OpenGL REQUIRED )
target_link_libraries(GL_GRAVITATION OpenGL::GL)

target_compile_features(GL_GRAVITATION PRIVATE cxx_std_20)