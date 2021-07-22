#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "aobj.h"

//=============================================================================

namespace spcGanesha
{

//=============================================================================

AObj::AObj(const std::string& objFileFullPath) {
    readData(objFileFullPath);
}

AObj::~AObj() {
    
}

TVertexesIndexesList AObj::faces() const {
    return  facesList;
}

std::vector<TVector> AObj::vertexes() const {
    return vertexesList;
}

void AObj::readData(const std::string objFile) {
    std::ifstream fileStream;
    fileStream.open(objFile, std::ifstream::in);
    if (fileStream.fail()) {
        return;
    }
    
    std::string line;
    while (!fileStream.eof()) {
        std::getline(fileStream, line);
        std::istringstream stringStream(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            stringStream >> trash;
            TVector newVertex;
            for (int32_t i = 0; i < 3; i++) {
                float vertex = 0;
                stringStream >> vertex;
                newVertex.push_back(vertex);
            }
            vertexesList.push_back(newVertex);
            continue;
        }
        
        if (!line.compare(0, 2, "f ")) {
            TFace newFace;
            int32_t itrash;
            int32_t vertexIndex;
            stringStream >> trash;
            while (stringStream >> vertexIndex >> trash >> itrash >> trash >> itrash) {
                vertexIndex--; // in wavefront obj all indices start at 1, not zero
                newFace.push_back(vertexIndex);
            }
            facesList.push_back(newFace);
        }
    }
    
    std::cerr << "# v# " << vertexesList.size() << " f# "  << facesList.size() << std::endl;
}

//=============================================================================

};  //  namespace spcGanesha
