cmake_minimum_required(VERSION 3.0.0)
project(yttrium VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)

option(YTR_BUILD_EXECUTABLE "Build an executable with some very simple testing stuff. Generally don't use this" OFF)
option(YTR_BUILD_LIBRARY "Only add stuff needed to use this as a library" ON)


if(${YTR_BUILD_EXECUTABLE})
	add_executable(yttrium)
	#target_sources(yttrium PRIVATE main.cpp test.cpp)
endif()
if(${YTR_BUILD_LIBRARY})
	add_library(yttrium)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/GLRenderer/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/renderer/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/Window/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/world/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/MFLoader/CMakeLists.txt)



target_include_directories(yttrium PUBLIC .)

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
if (GLEW_FOUND)
    #target_link_libraries(infiniteExplorer ${GLEW_LIBRARIES})
    message("glew libraries: ${GLEW_LIBRARIES}")
    target_link_libraries(yttrium glfw)
else()
    target_link_libraries(yttrium GL GLEW)
endif()

#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
