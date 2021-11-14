cmake_minimum_required(VERSION 3.20)

project(CML VERSION 1.1)

add_executable(${PROJECT_NAME} main.cpp)

#adder use logic

option(USE_ADDER "A simple library for add 2 floats" ON)
if (USE_ADDER)
    add_subdirectory(Adder)

    list(APPEND EXTRA_LINK_DIRS "Adder")
    list(APPEND EXTRA_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/Adder")
    list(APPEND EXTRA_LINK_LIBS adder)

    # target_include_directories(${PROJECT_NAME} 
    #     PUBLIC Adder 
    # )

    # target_link_directories(${PROJECT_NAME} 
    #     PRIVATE Adder
    # )
endif()


configure_file(CMLConfig.h.in CMLConfig.h)

#include the binary directory we build into, since we want to include the CMLConfig.h
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR}) 

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
    PUBLIC external/glfw/include
    ${EXTRA_INCLUDE_DIR}
)

target_link_directories(${PROJECT_NAME} 
    PRIVATE external/glfw/src # libglfw3.a 是一个lib文件 在这里路径里，在这里link
    ${EXTRA_LINK_DIRS}
)


target_link_libraries(${PROJECT_NAME} 
    ${EXTRA_LINK_LIBS}
    glfw
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/CMLConfig.h" DESTINATION include)




# Debug Printings
message(" Project Name: " ${PROJECT_NAME})
message("with lib")
