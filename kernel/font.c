#include "font.h"

const uint8_t kFontA[16] = {
  0b00000000,
  0b00011000,
  0b00011000,
  0b00011000,
  0b00011000,
  0b00100100,
  0b00100100,
  0b00100100,
  0b00100100,
  0b01111110,
  0b01000010,
  0b01000010,
  0b01000010,
  0b11100111,
  0b00000000,
};

void WriteAscii(const struct FrameBufferConfig *config,
                int x, int y, char c, 
                const struct PixelColor *color) 
{
  if (c != 'A')
    return;

  for(int dy=0; dy < 16; ++dy) {
    for(int dx=0; dx < 8; ++dx) {
      if((kFontA[dy] << dx) & 0x80u) {
        WritePixel(config, x+dx, y+dy, color);
      }
    }
  }
}
