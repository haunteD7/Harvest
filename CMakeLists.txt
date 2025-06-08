cmake_minimum_required(VERSION 4.0.2)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCE_FILES
     "src/*.cpp"
)

project(Harvest)

add_executable(Harvest ${SOURCE_FILES})

add_subdirectory(thirdparty/glfw)
target_link_libraries(Harvest PRIVATE glfw)
