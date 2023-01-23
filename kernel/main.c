#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#include "frame_buffer_config.h"
#include "graphics.h"
#include "font.h"
#include "console.h"

struct Console console;

int printk(const char *format, ...)
{
  va_list ap;
  int result;
  char s[1024];

  va_start(ap, format);
  result = vsprintf(s, format, ap);
  va_end(ap);

  PutString(&console, s);
  return result;
}

const struct PixelColor kDesktopBGColor = {128, 128, 128};
const struct PixelColor kDesktopFGColor = {255, 255, 255};

// #@@range_begin(mosue_cursor_shape)
#define kMouseCursorWidth 15
#define kMouseCursorHeight 24
const char mouse_cursor_shape[kMouseCursorHeight][kMouseCursorWidth + 1] = {
  "@              ",
  "@@             ",
  "@.@            ",
  "@..@           ",
  "@...@          ",
  "@....@         ",
  "@.....@        ",
  "@......@       ",
  "@.......@      ",
  "@........@     ",
  "@.........@    ",
  "@..........@   ",
  "@...........@  ",
  "@............@ ",
  "@......@@@@@@@@",
  "@......@       ",
  "@....@@.@      ",
  "@...@ @.@      ",
  "@..@   @.@     ",
  "@.@    @.@     ",
  "@@      @.@    ",
  "@       @.@    ",
  "         @.@   ",
  "         @@@   ",
};

void KernelMain(const struct FrameBufferConfig *frame_buffer_config) 
{
  const struct PixelColor white = {255, 255, 255};
  const struct PixelColor black = {0, 0, 0};
  const struct PixelColor gray = {128, 128, 128};
  
  const struct IntVector2D ul_p = {0, 0};
  const struct IntVector2D lr_p = {frame_buffer_config->horizontal_resolution, 
                                   frame_buffer_config->vertical_resolution};

  for(int x=0; x < frame_buffer_config->horizontal_resolution; ++x){
    for(int y=0; y < frame_buffer_config->vertical_resolution; ++y) {
      WritePixel(frame_buffer_config, x, y, &white);
    }
  }
  
  InitConsole(&console, frame_buffer_config, &black, &white);
  FillRectangle(frame_buffer_config, &ul_p, &lr_p, &gray);
  printk("Welcome to awkrailOS!\n");

  for(int dy =0; dy < kMouseCursorHeight; ++dy) {
    for(int dx=0; dx < kMouseCursorWidth; ++dx) {
      if(mouse_cursor_shape[dy][dx] == '@') {
        WritePixel(frame_buffer_config, 200+dx, 100+dy, &black);
      } else if (mouse_cursor_shape[dy][dx] == '.') {
        WritePixel(frame_buffer_config, 200+dx, 100+dy, &white);
      }
    }
  }

  while (1) __asm__("hlt");
}
