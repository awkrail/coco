#include "graphics.h"

void WriteRGBPixel(const struct FrameBufferConfig *config,
                  int x, int y, const struct PixelColor *c)
{
  const int pixel_position = config->pixels_per_scan_line * y + x;
  uint8_t *p = &config->frame_buffer[4 * pixel_position];
  p[0] = c->r;
  p[1] = c->g;
  p[2] = c->b;
}

void WriteBGRPixel(const struct FrameBufferConfig *config,
                  int x, int y, const struct PixelColor *c)
{
  const int pixel_position = config->pixels_per_scan_line * y + x;
  uint8_t *p = &config->frame_buffer[4 * pixel_position];
  p[0] = c->b;
  p[1] = c->g;
  p[2] = c->r;
}

void WritePixel(const struct FrameBufferConfig *config,
                int x, int y, const struct PixelColor *color)
{
  switch(config->pixel_format) {
    case kPixelRGBResv8BitPerColor:
      WriteRGBPixel(config, x, y, color);
      break;
    case kPixelBGRResv8BitPerColor:
      WriteBGRPixel(config, x, y, color);
      break;
    default:
      break;
  }
}
