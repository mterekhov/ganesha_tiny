#ifndef SPCGANESHA_AOBJ_H
#define SPCGANESHA_AOBJ_H

//=============================================================================

#include <string>

#include "ganeshatypes.h"

//=============================================================================

namespace spcGanesha
{

//=============================================================================

class AObj {
  public:
    AObj(const std::string& objFileFullPath);
    ~AObj();
    
    TVertexesIndexesList faces() const;
    std::vector<TVector> vertexes() const;
    
private:
    std::vector<TVector> vertexesList;
    TVertexesIndexesList facesList;

    void readData(const std::string objFile);
};

//=============================================================================

};  //  namespace spcGanesha

#endif  //  SPCGANESHA_AOBJ_H
