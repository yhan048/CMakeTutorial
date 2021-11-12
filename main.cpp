#include <iostream>

// float add(float a, float b);
// #include "Adder/adder.h"
#include "adder.h"
#include <GLFW/glfw3.h>
#include <CMLConfig.h>

int main(int argc, char* argv[]) {
    std::cout << "Hey YP\n";
    std::cout << add(50, 50.0) << std::endl;
    std::cout << argv[0] << " Version " << CML_VERSION_MAJOR << "." << CML_VERSION_MINOR << std::endl;


    GLFWwindow* window;

    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit( EXIT_FAILURE );
    }

    window = glfwCreateWindow( 300, 300, "Gears", NULL, NULL );
    if (!window)
    {
        fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    // Main loop
    while( !glfwWindowShouldClose(window) )
    {
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    
    return 0;
}