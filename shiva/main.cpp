//
//  main.cpp
//  shiva
//
//  Created by Mihail Terekhov on 08.02.2021.
//

#include <iostream>

#include "ashiva.h"

int main(int argc, const char * argv[]) {
    spcShiva::AShiva shivaEngine(52, 41, 3);
    shivaEngine.tgaFullFilePath = "/Users/ctteremalex/Pictures/shiva.tga";
    
    shivaEngine.drawLine(10, 10, 20, 20);
    shivaEngine.drawLine(10, 10, 10, 30);

    shivaEngine.swapBuffers();
    
    return 0;
}
