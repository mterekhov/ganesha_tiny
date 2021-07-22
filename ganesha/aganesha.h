#ifndef SPCGANESHA_AGANESHA_H
#define SPCGANESHA_AGANESHA_H

//=============================================================================

#include <string>

//=============================================================================

namespace spcGanesha
{

//=============================================================================

class AGanesha {
public:
    AGanesha(const uint32_t frameBufferWidth, const uint32_t frameBufferHeight, const uint8_t frameBufferColorsPerPixel);
    ~AGanesha();
    
    std::string tgaFullFilePath;
    
    void pickColor(const uint8_t *color);
    void drawLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1);
    void swapBuffers();
    
private:
    uint32_t colorsPerPixel;
    uint8_t *drawColor;

    uint8_t *onScreenFrameBufferData;
    uint8_t *backFrameBufferData;
    uint32_t frameWidth;
    uint32_t frameHeight;

    uint32_t bufferSize() const;
    void paintPixel(const uint8_t *color, const uint32_t pixelXCoord, const uint32_t pixelYCoord);

};

//=============================================================================

};  //  namespace spcGanesha

#endif  //  SPCGANESHA_AGANESHA_H
