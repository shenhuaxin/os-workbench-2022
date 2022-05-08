#include <am.h>
#include <amdev.h>
#include <klib.h>
#include <klib-macros.h>

void splash();
void draw_tile(int x, int y, int w, int h, uint32_t color);
void print_key();
static inline void puts(const char *s) {
  for (; *s; s++) putch(*s);
}


void wait_for_frame();
void ppu_cycle();
void psg_detect_key();
void splash_color(uint32_t color);
