#pragma once

#include <stddef.h>
#include <stdint.h>
#include "graphics.h"

void WriteAscii(const struct FrameBufferConfig *config,
                int x, int y, char c,
                const struct PixelColor *color);
