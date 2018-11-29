cmake_minimum_required(VERSION 3.7)
SET(projectname ottoengine)
project(${projectname} VERSION 1.0
                  DESCRIPTION "Vulkan real-time strategy game engine"
                  LANGUAGES CXX)
set(EXECUTABLE_OUTPUT_PATH "bin")
add_subdirectory(src)
