cmake_minimum_required(VERSION 3.0)
project(test_opengl)

set(CMAKE_VERBOSE_MAKEFILE OFF)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# glfw和glew的头文件目录，这是我的路径，你可以换成你自己的
include_directories(/opt/homebrew/include)
add_subdirectory(glad/)
aux_source_directory("./" SRCS)

set(CMAKE_CXX_FLAGS "-g -std=c++11 -Wformat")

# glew的库目录路径
# link_directories(/opt/homebrew/Cellar/glew/2.2.0_1/lib)
# glfw的库目录路径
link_directories(/opt/homebrew/Cellar/glfw/3.3.3/lib)

add_executable(test_opengl ${SRCS} ${HDRS} ${GLAD_SRC})

# 指定glew库
# target_link_libraries(test_opengl GLEW)
# 指定glfw库
target_link_libraries(test_opengl GLFW glad)
