set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11")

add_executable(${PROJECT_NAME} main.cpp)

#Get Vulkan deps
find_package(Vulkan REQUIRED)

#Get GLFW dependencies
find_package(glfw3 3.2 REQUIRED)

if (VULKAN_FOUND)
    include_directories(${Vulkan_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${Vulkan_LIBRARIES} glfw ${GLFW_LIBRARIES})
endif (VULKAN_FOUND)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_sources(${PROJECT_NAME} PUBLIC logic/gameobject.cpp)
target_sources(${PROJECT_NAME} PUBLIC graphics/renderloop.cpp)
target_sources(${PROJECT_NAME} PUBLIC logic/transform.cpp)
