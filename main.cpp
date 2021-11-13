#include <iostream>
// #include "adder.h"
#include <GLFW/glfw3.h>
#include <CMLConfig.h>
#ifdef USE_ADDER
    #include "adder.h"
#endif


int main(int argc, char* argv[]) {
    std::cout << "Hey YP\n";
#ifdef USE_ADDER
    std::cout << "Using adder lib " << add(72.1f, 50.8f) << std::endl;
#else
    std::cout << "Not using adder lib "  << 72.1f + 50.8f << std::endl;
#endif
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