#include <stdint.h>
#include <stddef.h>

#include "frame_buffer_config.h"
#include "graphics.h"
#include "font.h"

void KernelMain(const struct FrameBufferConfig *frame_buffer_config) 
{
  const struct PixelColor white = {255, 255, 255};
  const struct PixelColor green = {0, 255, 0};
  const struct PixelColor black = {0, 0, 0};

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

  int i = 0;
  for(char c = '!'; c <= '~'; ++c, ++i) {
    WriteAscii(frame_buffer_config, 8 * i, 50, c, &black);
  }
  while (1) __asm__("hlt");
}
