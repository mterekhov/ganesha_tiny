#ifndef SPCSHIVA_ASHIVA_H
#define SPCSHIVA_ASHIVA_H

//=============================================================================

#include <string>

//=============================================================================

namespace spcShiva
{

//=============================================================================

class AShiva {
public:
    AShiva(const uint32_t frameBufferWidth, const uint32_t frameBufferHeight, const uint8_t frameBufferColorsPerPixel);
    ~AShiva();
    
    std::string tgaFullFilePath;
    
    void pickColor(const uint8_t *color);
    void drawLine(const uint32_t x0, const uint32_t y0, const uint32_t x1, const uint32_t y1);
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

};  //  namespace spcShiva

#endif  //  SPCSHIVA_ASHIVA_H
