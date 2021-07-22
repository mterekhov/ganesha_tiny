//
//  main.cpp
//  ganesha
//
//  Created by Mihail Terekhov on 22.07.2021.
//

#include <iostream>
#include "ganesha.h"

int main(int argc, const char * argv[]) {
    uint32_t width = 1024;
    uint32_t height = 1024;
    
    spcGanesha::AGanesha ganeshaEngine(width, height, 3);
    ganeshaEngine.tgaFullFilePath = "/Users/ctteremalex/Pictures/shiva.tga";

    spcGanesha::AObj model("/Users/ctteremalex/Development/ganesha/model.obj");
    spcGanesha::TVertexesIndexesList facesList = model.faces();
    std::vector<spcGanesha::TVector> vertexesList = model.vertexes();
    
    for (int32_t i = 0; i < facesList.size(); i++) {
        spcGanesha::TFace face = facesList[i];
        for (int32_t j = 0; j < 3; j++) {
            spcGanesha::TVector v0 = vertexesList[face[j]];
            spcGanesha::TVector v1 = vertexesList[face[j + 1] % 3];
            int32_t x0 = (v0[0] + 1.) * width / 2.;
            int32_t y0 = (v0[1] + 1.) * height / 2.;
            int32_t x1 = (v1[0] + 1.) * width / 2.;
            int32_t y1 = (v1[1] + 1.) * height / 2.;
            ganeshaEngine.drawLine(x0, y0, x1, y1);
        }
    }

    ganeshaEngine.swapBuffers();

    return 0;
}
