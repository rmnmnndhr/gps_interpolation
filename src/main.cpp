#include <iostream>
#include "core/Application.hpp"



int main(int argc, char* argv[]) {
    Application* application = new Application();

    application->validatePositions();
    
    free(application);
    
}