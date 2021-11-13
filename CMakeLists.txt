cmake_minimum_required(VERSION 3.20)

project(CML VERSION 1.0)

configure_file(CMLConfig.h.in CMLConfig.h)

add_executable(${PROJECT_NAME} main.cpp)

#include the binary directory we build into, since we want to include the CMLConfig.h
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR}) 

add_subdirectory(Adder)

# ---------------DOWNLOAD ALL THE SUBMODULES ---------------
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if (GIT_SUBMODULE)
        message(STATUS "Submodule update")
        # run commands directly 
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMODULE_RESULT)
        if (NOT GIT_SUBMODULE_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMODULE_RESULT}, please check submodules")
        endif()
    endif()
endif()
# ---------------CEHCK ALL THE SUBMODULES ---------------
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt")
    message(FATAL_ERROR "The glfw submodules was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules")
endif()





add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME} 
    PUBLIC Adder 
    PUBLIC external/glfw/include
)

target_link_directories(${PROJECT_NAME} 
    PRIVATE Adder
    PRIVATE external/glfw/src # libglfw3.a 是一个lib文件 在这里路径里，在这里link
)


target_link_libraries(${PROJECT_NAME} 
    adder
    glfw
)
# Debug Printings
message(" Project Name: " ${PROJECT_NAME})
message("with lib")
