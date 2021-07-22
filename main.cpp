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
    ganeshaEngine.tgaFullFilePath = "/Users/ctteremalex/Pictures/ganesha.tga";

    spcGanesha::AObj model("/Users/ctteremalex/Development/ganesha/african_head.obj");
    spcGanesha::TVertexesIndexesList trianglesList = model.faces();
    std::vector<spcGanesha::TVector> vertexesList = model.vertexes();
    
    for (int32_t i = 0; i < trianglesList.size(); i++) {
        spcGanesha::TFace triangle = trianglesList[i];
        for (int32_t triangleEdgeIndex = 0; triangleEdgeIndex < 3; triangleEdgeIndex++) {
            spcGanesha::TVector vertex0 = vertexesList[triangle[triangleEdgeIndex]];
            spcGanesha::TVector vertex1 = vertexesList[triangle[(triangleEdgeIndex + 1) % 3]];
            int32_t x0 = (vertex0[0] + 1.) * width / 2.;
            int32_t y0 = (vertex0[1] + 1.) * height / 2.;
            int32_t x1 = (vertex1[0] + 1.) * width / 2.;
            int32_t y1 = (vertex1[1] + 1.) * height / 2.;
            ganeshaEngine.drawLine(x0, y0, x1, y1);
        }
    }

    ganeshaEngine.swapBuffers();

    return 0;
}
