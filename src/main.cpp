#include <iostream>

#include "CameraApi.h"

int main(int argc, char* argv[]) {
    std::cout << "hello world" << std::endl;

    std::cout << "res: " << CameraSdkInit(0) << std::endl;
    
    std::cout << "hello world" << std::endl;

    return 0;
}
