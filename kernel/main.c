#include <stdint.h>
#include <stddef.h>
#include "frame_buffer_config.h"

struct PixelColor 
{
  uint8_t r, g, b;
};

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

void KernelMain(const struct FrameBufferConfig *frame_buffer_config) 
{
  void (*WritePixel)(const struct FrameBufferConfig *config,
                     int x, int y, const struct PixelColor *c);
  if(frame_buffer_config->pixel_format == kPixelRGBResv8BitPerColor) {
    WritePixel = WriteRGBPixel;
  } else if (frame_buffer_config->pixel_format == kPixelBGRResv8BitPerColor) {
    WritePixel = WriteBGRPixel;
  }

  const struct PixelColor white = {255, 255, 255};
  const struct PixelColor green = {0, 255, 0};

  for(int x=0; x < frame_buffer_config->horizontal_resolution; ++x){
    for(int y=0; y < frame_buffer_config->vertical_resolution; ++y) {
      WritePixel(frame_buffer_config, x, y, &white);
    }
  }

  for(int x=0; x < 200; ++x) {
    for(int y=0; y<100; ++y) {
      WritePixel(frame_buffer_config, 100+x, 100+y, &green);
    }
  }
  while (1) __asm__("hlt");
}
