#include <string_view>
#include <cmath>

#include "aganesha.h"
#include "atgaexporter.h"

namespace spcGanesha {

uint32_t AGanesha::bufferSize() const {
    return colorsPerPixel * frameWidth * frameHeight;
}

AGanesha::AGanesha(const uint32_t frameBufferWidth, const uint32_t frameBufferHeight, const uint8_t frameBufferColorsPerPixel) : frameWidth(frameBufferWidth), frameHeight(frameBufferHeight), colorsPerPixel(frameBufferColorsPerPixel) {
    uint32_t frameSizeInBytes = bufferSize();
    onScreenFrameBufferData = new uint8_t[frameSizeInBytes];
    memset(onScreenFrameBufferData, 0, frameSizeInBytes);
    
    backFrameBufferData = new uint8_t[frameSizeInBytes];
    memset(backFrameBufferData, 0, frameSizeInBytes);
    
    drawColor = new uint8_t[colorsPerPixel];
    memset(drawColor, 0xFF, colorsPerPixel);
}

AGanesha::~AGanesha() {
    delete [] onScreenFrameBufferData;
    delete [] backFrameBufferData;
    delete [] drawColor;
}

void AGanesha::pickColor(const uint8_t *color) {
    memcpy(drawColor, color, colorsPerPixel);
}

void AGanesha::drawLine(int32_t x0, int32_t y0, int32_t x1, int32_t y1) {
    if (x0 > frameWidth ||
        y0 > frameHeight) {
        return;
    }

    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }

    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int32_t dx = x1 - x0;
    int32_t dy = y1 - y0;
    int32_t derror2 = std::abs(dy) * 2;
    int32_t error2 = 0;
    int32_t y = y0;
    for (int32_t x = x0; x <= x1; x++) {
        if (steep) {
            paintPixel(drawColor, y, x);
        } else {
            paintPixel(drawColor, x, y);
        }
        error2 += derror2;

        if (error2 > dx) {
            y += (y1 > y0 ? 1 : -1);
            error2 -= dx * 2;
        }
    }
}

void AGanesha::paintPixel(const uint8_t *color, const uint32_t pixelXCoord, const uint32_t pixelYCoord) {
    uint32_t pixelIndex = colorsPerPixel * (pixelYCoord * frameWidth + pixelXCoord);
    for (uint32_t i = 0; i < colorsPerPixel; i++) {
        backFrameBufferData[pixelIndex + i] = color[i];
    }
}

void AGanesha::swapBuffers() {
    memcpy(onScreenFrameBufferData, backFrameBufferData, bufferSize());
    
    ATGAExporter tgaSaver;
    tgaSaver.exportData(tgaFullFilePath, onScreenFrameBufferData, frameWidth, frameHeight);
}

}
