cmake_minimum_required(VERSION 3.25)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE SOURCE_FILES
     "src/*.cpp"
)

project(Harvest)

add_executable(Harvest ${SOURCE_FILES})
target_include_directories(Harvest PRIVATE thirdparty)

add_subdirectory(thirdparty/glfw)
target_link_libraries(Harvest PRIVATE glfw)

add_subdirectory(thirdparty/glad)
target_link_libraries(Harvest PRIVATE glad)
