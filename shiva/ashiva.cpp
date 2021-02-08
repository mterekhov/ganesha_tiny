//
//  AShiva.cpp
//  shiva
//
//  Created by Mihail Terekhov on 08.02.2021.
//

#include <algorithm>
#include <utility>

#include "ashiva.h"
#include "atgaexporter.h"

namespace spcShiva {

uint32_t AShiva::bufferSize() const {
    return colorsPerPixel * frameWidth * frameHeight;
}

AShiva::AShiva(const uint32_t frameBufferWidth, const uint32_t frameBufferHeight, const uint8_t frameBufferColorsPerPixel) : frameWidth(frameBufferWidth), frameHeight(frameBufferHeight), colorsPerPixel(frameBufferColorsPerPixel) {
    uint32_t frameSizeInBytes = bufferSize();
    onScreenFrameBufferData = new uint8_t[frameSizeInBytes];
    memset(onScreenFrameBufferData, 0, frameSizeInBytes);
    
    backFrameBufferData = new uint8_t[frameSizeInBytes];
    memset(backFrameBufferData, 0, frameSizeInBytes);
    
    drawColor = new uint8_t[colorsPerPixel];
    memset(drawColor, 0xFF, colorsPerPixel);
}

AShiva::~AShiva() {
    delete [] onScreenFrameBufferData;
    delete [] backFrameBufferData;
    delete [] drawColor;
}

void AShiva::pickColor(const uint8_t *color) {
    memcpy(drawColor, color, colorsPerPixel);
}

void AShiva::drawLine(const uint32_t x0, const uint32_t y0, const uint32_t x1, const uint32_t y1) {
    if (x0 > frameWidth ||
        y0 > frameHeight) {
        return;
    }
    
    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) { // if the line is steep, we transpose the image
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    
    if (x0 > x1) { // make it left-to-right
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    
    for (uint32_t x = x0; x <= x1; x++) {
        float t = (x - x0) / static_cast<float>(x1 - x0);
        uint32_t y = y0 * (1. - t) + y1 * t;
        if (steep) {
            paintPixel(drawColor, y, x);
        } else {
            paintPixel(drawColor, x, y);
        }
    }
    
//    for (uint32_t x = x0; x <= x1; x++) {
//        uint32_t y = y0 * (1. - t) + y1 * t;
//        paintPixel(drawColor, x, y);
//    }
}

void AShiva::paintPixel(const uint8_t *color, const uint32_t pixelXCoord, const uint32_t pixelYCoord) {
    uint32_t pixelIndex = colorsPerPixel * (pixelYCoord * frameWidth + pixelXCoord);
    for (uint32_t i = 0; i < colorsPerPixel; i++) {
        backFrameBufferData[pixelIndex + i] = color[i];
    }
}

void AShiva::swapBuffers() {
    memcpy(onScreenFrameBufferData, backFrameBufferData, bufferSize());
    
    ATGAExporter tgaSaver;
    tgaSaver.exportData(tgaFullFilePath, onScreenFrameBufferData, frameWidth, frameHeight);
}

}
