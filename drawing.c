//void DRV_Display_DrawPixel(uint16_t x, uint16_t y, uint32_t rgbCode)
#include "drawing.h"
#include "display.h"

uint32_t ColorToRGBCode(Color color) {
uint32_t RGB_Code = 0;

// Compose the RGB_Code using the Color structure values (color.red, color.green, color.blue)
RGB_Code |= 255;                                         // Alpha
RGB_Code |= ((uint32_t)color.red << 8)     & 0x0000FF00; // Red
RGB_Code |= ((uint32_t)color.green << 16)  & 0x00FF0000; // Green
RGB_Code |= ((uint32_t)color.blue  << 24)  & 0xFF000000; // Blue

    return RGB_Code;
}

void DRV_DrawHorizontalLine(Pixel start, int16_t length, Color color) {
    for (int i = start.x; i < start.x+length; i++) {
        DRV_Display_DrawPixel(i, start.y,ColorToRGBCode(color));
    }
}

void DRV_DrawVerticalLine(Pixel start, int16_t length, Color color) {
    for (int i = start.y; i < start.y+length; i++) {
        DRV_Display_DrawPixel(start.x, i,ColorToRGBCode(color));
    }
}
