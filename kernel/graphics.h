#pragma once

#include "frame_buffer_config.h"

struct PixelColor 
{
  uint8_t r, g, b;
};

void WriteRGBPixel(const struct FrameBufferConfig *config,
                   int x, int y, const struct PixelColor *c);

void WriteBGRPixel(const struct FrameBufferConfig *config,
                   int x, int y, const struct PixelColor *c);

void WritePixel(const struct FrameBufferConfig *config,
                int x, int y, const struct PixelColor *c);
